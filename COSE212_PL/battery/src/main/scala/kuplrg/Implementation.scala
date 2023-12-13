package kuplrg

object Implementation extends Template {

  import Expr.*
  import RecDef.*
  import Value.*
  import Type.*
  import TypeInfo.*

  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case EUnit                                    => UnitT
    case ENum(n)                                  => NumT
    case EBool(b)                                 => BoolT
    case EStr(s)                                  => StrT
    case EId(name)                                => tenv.vars.getOrElse(name, error(s"unknown type ${name} in EId"))
    case EAdd(left, right)                        => mustSame(typeCheck(left, tenv), NumT); mustSame(typeCheck(right, tenv), NumT); NumT
    case EMul(left, right)                        => mustSame(typeCheck(left, tenv), NumT); mustSame(typeCheck(right, tenv), NumT); NumT
    case EDiv(left, right)                        => mustSame(typeCheck(left, tenv), NumT); mustSame(typeCheck(right, tenv), NumT); NumT
    case EMod(left, right)                        => mustSame(typeCheck(left, tenv), NumT); mustSame(typeCheck(right, tenv), NumT); NumT
    case EConcat(left, right)                     => mustSame(typeCheck(left, tenv), StrT); mustSame(typeCheck(right, tenv), StrT); StrT
    case EEq(left, right)                         => mustSame(typeCheck(left, tenv), typeCheck(right, tenv)); BoolT
    case ELt(left, right)                         => mustSame(typeCheck(left, tenv), NumT); mustSame(typeCheck(right, tenv), NumT); BoolT
    case ESeq(left, right)                        => typeCheck(left, tenv); typeCheck(right, tenv)
    case EIf(cond, thenExpr, elseExpr)            =>
                                                      mustSame(typeCheck(cond, tenv), BoolT)
                                                      val thenTy = typeCheck(thenExpr, tenv)
                                                      mustSame(thenTy, typeCheck(elseExpr, tenv));
                                                      thenTy
    case EVal(x, tyOpt, expr, body) => tyOpt match
      case None                                   => typeCheck(body, tenv.addVar(x, typeCheck(expr, tenv)))
      case Some(ty)                               =>
                                                      mustSame(ty, typeCheck(expr, tenv))
                                                      typeCheck(body, tenv.addVar(x, ty))
    case EFun(params, body)                       =>
                                                      params.foreach((param) => mustValid(param.ty, tenv))
                                                      ArrowT(Nil, params.map(p => p.ty), typeCheck(body, tenv.addVars(params.map((param) => param.name -> param.ty))))
    case EApp(fun, tys, args) => typeCheck(fun, tenv) match
      case ArrowT(tvars, paramTys, retTy)         =>
                                                      tys.foreach(mustValid(_, tenv))
                                                      val argTys = args.map(typeCheck(_, tenv))
                                                      val pairedTys = argTys.zip(paramTys)
                                                      val substPairs = tvars.zip(tys).toMap
                                                      pairedTys.foreach((argTy, paramTy) => mustSame(argTy, subst(paramTy, substPairs)))
                                                      subst(retTy, substPairs)
      case _                                      => error(s"${fun.str} is not the arrow type")
    case ERecDefs(defs, body)                     =>
                                                      val finTEnv = defs.foldLeft(tenv)((tenv, recDef) => typeCheckRecDef(recDef, tenv))
                                                      defs.foreach((recDef) => (mustValidRecDef(recDef, finTEnv)))
                                                      mustValid(typeCheck(body, finTEnv), tenv)
    case EMatch(expr, mcases) => typeCheck(expr, tenv) match
      case IdT(name, tys) => tenv.tys.getOrElse(name, error(s"unknown type: ${name} in EMatch IdT")) match
        case TIVar                                => error(s"${name} is not an ADT")
        case TIAdt(tvars, variants)               =>
                                                      val matchNames = mcases.map(_.name).toSet
                                                      val varNames = variants.keySet
                                                      if (matchNames != varNames || matchNames.size != mcases.length) error(s"invalid case")
                                                      val substPairs: Map[String, Type] = tvars.zip(tys).toMap

                                                      val mcasesParams = mcases.map(_.params)
                                                      val varParamTysMCaseOrdered = mcases.map(mcase => variants.find(vart => vart._1 == mcase.name) match { case Some(vart) => vart._2.map(p => p.ty)})

                                                      val paramVarTyPaired: Iterable[(List[String], List[Type])] = mcasesParams.zip(varParamTysMCaseOrdered)
                                                      /*
                                                      println("---------------")
                                                      paramVarTyPaired.foreach(pair => {pair._1.foreach(name => print(name ++ " ")); print(" -> "); pair._2.foreach(ty => print(ty.str ++ " ")); print("\n")})
                                                      println("---------------")
                                                      */
                                                      val t: Iterable[List[(String, Type)]] = paramVarTyPaired.map((params, varTys) => params.zip(varTys.map(subst(_, substPairs))))
                                                      // t.foreach(pairs => { println("---------------"); pairs.foreach(pair => {print(pair._1); print(" -> "); print(pair._2.str ++ " "); print("\n")}); println("---------------")})

                                                      val newTEnvs = t.map(tenv.addVars(_))
                                                      // newTEnvs.foreach(newTEnv => { println("------"); newTEnv.printTypeEnv; println("------")})

                                                      val bodyTypes = mcases.map(mcase => mcase.body).zip(newTEnvs).map((body, newTEnv) =>
                                                      {
                                                      //println("------"); println(body.str); newTEnv.printTypeEnv; println(typeCheck(body, newTEnv)); println("--------");
                                                        typeCheck(body, newTEnv)
                                                      })

                                                      bodyTypes.reduce((lty, rty) => { mustSame(lty, rty); lty })
      case _                                      => error(s"not a variant")
    case EExit(ty, expr)                          => mustSame(typeCheck(expr, tenv), StrT); mustValid(ty, tenv)


  def typeCheckRecDef(recDef: RecDef, tenv: TypeEnv): TypeEnv = recDef match
    case LazyVal(name, ty, init)                  => tenv.addVar((name, ty))
    case RecFun(name, tvars, params, rty, body)   => tenv.addVar((name, ArrowT(tvars, params.map(_.ty), rty)))
    case TypeDef(name, tvars, varts) => tenv.tys.get(name) match
      case Some(_)                                => error(s"type ${name} is already defined")
      case None                                   =>
                                                      val newTEnv_0 = tenv.addTypeName(name, tvars, varts)
                                                      varts.foldLeft(newTEnv_0)((newTEnv, vart) => {
                                                          if (newTEnv.vars.contains(vart.name)) error(s"type ${vart.name} is already defined")
                                                          newTEnv.addVar((vart.name, ArrowT(tvars, vart.params.map(_.ty), IdT(name, tvars.map(tvar => IdT(tvar, Nil))))))
                                                        })

  def interp(expr: Expr, env: Env): Value = expr match
    case EUnit                                    => UnitV
    case ENum(n)                                  => NumV(n)
    case EBool(b)                                 => BoolV(b)
    case EId(name) => env.getOrElse(name, error(s"free identifier")) match
      case ExprV(expr, lazyEnv)                   => interp(expr, lazyEnv())
      case v                                      => v
    case EStr(s)                                  => StrV(s)
    case EAdd(left, right)                        => numBOp(_ + _)(interp(left, env), interp(right, env))
    case EMul(left, right)                        => numBOp(_ * _)(interp(left, env), interp(right, env))
    case EDiv(left, right)                        => nonZeroRBOp(_ / _)(interp(left, env), interp(right, env))
    case EMod(left, right)                        => nonZeroRBOp(_ % _)(interp(left, env), interp(right, env))
    case EConcat(left, right) => (interp(left, env), interp(right, env)) match
      case (StrV(lv), StrV(rv))                   => StrV(lv ++ rv)
      case _                                      => error(s"not a string")
    case EEq(left, right)                         => BoolV(isEqual(interp(left, env), interp(right, env)))
    case ELt(left, right)                         => numCompBOp(_ < _)(interp(left, env), interp(right, env))
    case ESeq(left, right)                        => interp(left, env); interp(right, env)
    case EIf(cond, thenExpr, elseExpr) => interp(cond, env) match
      case BoolV(true)                            => interp(thenExpr, env)
      case BoolV(false)                           => interp(elseExpr, env)
      case _                                      => error(s"not a boolean condition")
    case EVal(x, tyOpt, expr, body)               => interp(body, env + (x -> interp(expr, env)))
    case EFun(params, body)                       => CloV(params.map(p => p.name), body, () => env)
    case EApp(fun, tys, args) => interp(fun, env) match
      case CloV(params, body, lazyFenv)           => interp(body, lazyFenv() ++ params.zip(args.map(arg => interp(arg, env))).toMap)
      case ConstrV(name)                          => VariantV(name, args.map(arg => interp(arg, env)))
      case _                                      => error(s"not a closure or a constructor")
    case ERecDefs(defs, body)                     =>
                                                      lazy val finEnv: Env = defs.foldLeft(env)((prevEnv, recDef) => interpRecDef(recDef, (prevEnv, () => finEnv)))
                                                      interp(body, finEnv)
    case EMatch(expr, mcases) => interp(expr, env) match
      case VariantV(name, values) => mcases.find(mcase => mcase.name == name) match
        case Some(MatchCase(name, params, body))  =>
                                                      if (params.length != values.length) error(s"no match cases")
                                                      interp(body, env ++ params.zip(values))
        case None                                 => error(s"no match cases")
      case _                                      => error(s"not a variant")
    case _                                        => error(s"invalid operation")

  def interpRecDef(recDef: RecDef, envs: (Env, () => Env)): Env = recDef match
    case LazyVal(name, ty, init)                  => envs._1 + (name -> ExprV(init, envs._2))
    case RecFun(name, tvars, params, rty, body)   => envs._1 + (name -> CloV(params.map(_.name), body, envs._2))
    case TypeDef(name, tvars, varts)              => envs._1 ++ varts.map(vart => (vart.name -> ConstrV(vart.name))).toMap

  def mustValid(ty: Type, tenv: TypeEnv): Type = ty match
    case UnitT                                    => UnitT
    case NumT                                     => NumT
    case BoolT                                    => BoolT
    case StrT                                     => StrT
    case IdT(name, tys) => tenv.tys.get(name) match
      case Some(TIAdt(_, _))                      => tys.foreach(mustValid(_, tenv)); IdT(name, tys)
      case Some(TIVar)                            => IdT(name, tys)
      case _                                      => error(s"unknown type ${name} in mustValid IdT")
    case ArrowT(tvars, paramTys, retTy)           =>
                                                      val newTEnv = tenv.addTypeVars(tvars)
                                                      ArrowT(tvars, paramTys.map(mustValid(_, newTEnv)), mustValid(retTy, newTEnv))

  def mustValidRecDef(recDef: RecDef, tenv: TypeEnv): Unit = recDef match
    case LazyVal(name, ty, init)                  => mustSame(mustValid(ty, tenv), typeCheck(init, tenv))
    case RecFun(name, tvars, params, rty, body)   =>
                                                      tvars.foreach(tvar => tenv.tys.get(tvar) match {
                                                        case Some(_)  => error(s"already defined type")
                                                        case None     => ()
                                                      })
                                                      val newTEnv = tenv.addTypeVars(tvars)
                                                      params.foreach(p => mustValid(p.ty, newTEnv))
                                                      mustSame(mustValid(rty, newTEnv), typeCheck(body, newTEnv.addVars(params.map(p => p.name -> p.ty))))
    case TypeDef(name, tvars, varts)              =>
                                                      tvars.foreach(tvar => tenv.tys.get(tvar) match {
                                                        case Some(_)  => error(s"already defined type")
                                                        case None     => ()
                                                      })
                                                      val newTEnv = tenv.addTypeVars(tvars)
                                                      varts.foreach(vart => vart.params.foreach(p => mustValid(p.ty, newTEnv)))

  def subst(targetTy: Type, substPairs: Map[String, Type]): Type = targetTy match
    case UnitT                                    => UnitT
    case NumT                                     => NumT
    case BoolT                                    => BoolT
    case StrT                                     => StrT
    case IdT(name, tys) => tys match
      case Nil                                    => substPairs.getOrElse(name, IdT(name, tys))
      case tys                                    => IdT(name, tys.map(ty => subst(ty, substPairs)))
    case ArrowT(tvars, paramTys, retTy)           =>
                                                      val filteredSubstPairs = substPairs.filter(pair => !tvars.contains(pair._1))
                                                      ArrowT(tvars, paramTys.map(paramTy => subst(paramTy, filteredSubstPairs)), subst(retTy, filteredSubstPairs))

  def isSame(lty: Type, rty: Type): Boolean = (lty, rty) match
    case (UnitT, UnitT)                           => true
    case (NumT, NumT)                             => true
    case (BoolT, BoolT)                           => true
    case (StrT, StrT)                             => true
    case (IdT(lname, ltys), IdT(rname, rtys)) => (ltys, rtys) match
      case (Nil, Nil)                             => true
      case (ltys, rtys)                           => ltys.zip(rtys).map((lty, rty) => isSame(lty, rty)).foldLeft(true)(_ && _)
    case (ArrowT(ltvars, lparamTys, lretTy), ArrowT(rtvars, rparamTys, rretTy)) =>
                                                      if (ltvars.length == rtvars.length && lparamTys.length == rparamTys.length) {
                                                        val pairedTys = lparamTys.zip(rparamTys).toMap + (lretTy -> rretTy)
                                                        val substPairs = rtvars.zip(ltvars.map(ltvar => IdT(ltvar, Nil))).toMap
                                                        pairedTys.map((lty, rty) => isSame(lty, subst(rty, substPairs))).foldLeft(true)(_ && _)
                                                      } else false
    case (_, _)                                   => false

    def mustSame(lty: Type, rty: Type): Unit =
      if (!isSame(lty, rty)) error(s"type mismatch: ${lty.str} is not equal to ${rty.str}")

    def isEqual(lv: Value, rv: Value): Boolean = (lv, rv) match
      case (UnitV, UnitV)                         => true
      case (NumV(l), NumV(r))                     => l == r
      case (BoolV(l), BoolV(r))                   => l == r
      case (StrV(l), StrV(r))                     => l == r
      case (VariantV(lname, lvalues), VariantV(rname, rvalues)) =>
                                                      lvalues.zip(rvalues).map((lvalue, rvalue) => isEqual(lvalue, rvalue)).foldLeft(lname == rname)(_ && _)
      case (_, _)                                 => false

    type BOp = (BigInt, BigInt) => BigInt
    def numBOp(op: BOp)(lv: Value, rv: Value): NumV = (lv, rv) match
      case (NumV(l), NumV(r))                     => NumV(op(l, r))
      case _                                      => error(s"invalid operation")

    def nonZeroRBOp(op: BOp)(lv: Value, rv: Value): NumV = (lv, rv) match
      case (NumV(l), NumV(0))                     => error(s"can't use zero on right term")
      case (NumV(l), NumV(r))                     => NumV(op(l, r))
      case _                                      => error(s"invalid operation")

    type CompOp = (BigInt, BigInt) => Boolean
    def numCompBOp(op: CompOp)(lv: Value, rv: Value): BoolV = (lv, rv) match
      case (NumV(l), NumV(r))                     => BoolV(op(l, r))
      case _                                      => error(s"invalid operation")
}
