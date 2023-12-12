package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Type.*

  def mustSame(lty: Type, rty: Type): Unit =
    if (lty != rty) error(s"type error")

  def mustValid(ty: Type, tenv: TypeEnv): Type = ty match
    case NumT                                   => NumT
    case BoolT                                  => BoolT
    case ArrowT(paramTys, retTy)                => ArrowT(paramTys.map(mustValid(_, tenv)), mustValid(retTy, tenv))
    case NameT(name)                            => if (!tenv.tys.contains(name)) error(s"invalid type name"); NameT(name)

  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case Num(number)                            => NumT
    case Bool(boolean)                          => BoolT
    case Add(l, r)                              => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); NumT
    case Mul(l, r)                              => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); NumT
    case Div(l, r)                              => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); NumT
    case Mod(l, r)                              => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); NumT
    case Eq(l, r)                               => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); BoolT
    case Lt(l, r)                               => mustSame(typeCheck(l, tenv), NumT); mustSame(typeCheck(r, tenv), NumT); BoolT
    case Val(name, init, body)                  =>
                                                    val vty = typeCheck(init, tenv);
                                                    typeCheck(body, tenv.addVar((name, vty)))
    case Id(name)                               => tenv.vars.getOrElse(name, error(s"unknown type"))
    case Fun(params, body)                      =>
                                                    val paramTys = params.map(p => mustValid(p.ty, tenv));
                                                    val retTy = typeCheck(body, tenv.addVars(params.map(p => p.name -> p.ty)));
                                                    ArrowT(paramTys, retTy)
    case Rec(x, params, rty, body, scope)       =>
                                                    val paramTys = params.map(p => mustValid(p.ty, tenv))
                                                    mustValid(rty, tenv)
                                                    mustSame(rty, typeCheck(body, tenv.addVar(x -> ArrowT(paramTys, rty)).addVars(params.map(p => p.name -> p.ty))))
                                                    typeCheck(scope, tenv.addVar(x, ArrowT(paramTys, rty)))
    case App(fun, args) => typeCheck(fun, tenv) match
      case ArrowT(paramTys, retTy)              =>
                                                    if (args.length != paramTys.length) error(s"type error")
                                                    val argTys = args.map(typeCheck(_, tenv))
                                                    paramTys.zip(argTys).map((pty, aty) => mustSame(pty, aty))
                                                    retTy
      case _                                    =>  error(s"type error")
    case If(cond, thenExpr, elseExpr) => typeCheck(cond, tenv) match
      case BoolT                                =>
                                                    val thenTy = typeCheck(thenExpr, tenv)
                                                    val elseTy = typeCheck(elseExpr, tenv)
                                                    mustSame(thenTy, elseTy)
                                                    thenTy
      case _                                    =>  error(s"type error")
    case TypeDef(name, ws, body)                =>
                                                    if (tenv.tys.contains(name)) error(s"type is already implemented")
                                                    val newTEnv = tenv.addType(name, ws.map(w => w.name -> w.ptys).toMap)
                                                    for (w <- ws; pty <- w.ptys) mustValid(pty, newTEnv)
                                                    mustValid(typeCheck(
                                                      body,
                                                      newTEnv.addVars(ws.map(w => w.name -> ArrowT(w.ptys, NameT(name))))
                                                    ), tenv)
    case Match(expr, mcases) => typeCheck(expr, tenv) match
      case NameT(name)                          =>
                                                    val adt = tenv.tys.getOrElse(name, error(s"unknown type"))
                                                    val names = mcases.map(_.name).toSet
                                                    if (adt.keySet != names || names.size != mcases.length) error(s"invalid type")
                                                    mcases.map {
                                                      case MatchCase(name, params, body) => typeCheck(body, tenv.addVars(params.zip(adt(name))))
                                                    }.reduce((lty, rty) => { mustSame(lty, rty); lty })
      case _                                    => error(s"not a variant")

  type BOp = (BigInt, BigInt) => BigInt
  def numBOp(Op: BOp)(lv: Value, rv: Value): Value = (lv, rv) match
    case (NumV(l), NumV(r))                     => NumV(Op(l, r))
    case _                                      => error(s"invalid operation")

  def rvNotZeroBOp(Op: BOp)(lv: Value, rv: Value): Value = (lv, rv) match
    case (NumV(l), NumV(r)) => r match
      case 0                                    => error(s"right value can't be zero")
      case r                                    => NumV(Op(l, r))
    case _                                      => error(s"invalid operation")

  type CondOp = (BigInt, BigInt) => Boolean
  def condBOp(Op: CondOp)(lv: Value, rv: Value): Value = (lv, rv) match
    case (NumV(l), NumV(r))                     => BoolV(Op(l, r))
    case _                                      => error(s"invalid operation")

  def interp(expr: Expr, env: Env): Value = expr match
    case Num(n)                                 => NumV(n)
    case Bool(b)                                => BoolV(b)
    case Add(left, right)                       => numBOp(_ + _)(interp(left, env), interp(right, env))
    case Mul(left, right)                       => numBOp(_ * _)(interp(left, env), interp(right, env))
    case Div(left, right)                       => rvNotZeroBOp(_ / _)(interp(left, env), interp(right, env))
    case Mod(left, right)                       => rvNotZeroBOp(_ % _)(interp(left, env), interp(right, env))
    case Eq(left, right)                        => condBOp(_ == _)(interp(left, env), interp(right, env))
    case Lt(left, right)                        => condBOp(_ < _)(interp(left, env), interp(right, env))
    case Val(name, init, body)                  => interp(body, env + (name -> interp(init, env)))
    case Id(name)                               => env.getOrElse(name, error(s"free identifier"))
    case Fun(params, body)                      => CloV(params.map(_.name), body, () => env)
    case Rec(name, params, rty, body, scope)    =>
                                                    lazy val newEnv: Env = env + (name -> CloV(params.map(_.name), body,  () => newEnv))
                                                    interp(scope, newEnv)
    case App(fun, args) => interp(fun, env) match
      case CloV(params, body, fenv)             =>
                                                    val argVs = args.map(interp(_, env))
                                                    val newEnv: Env = fenv() ++ params.zip(argVs).toMap
                                                    interp(body, newEnv)
      case ConstrV(name)                        =>
                                                    val argVs = args.map(interp(_, env))
                                                    VariantV(name, argVs)
      case _                                    => error(s"not a function or a constructor")
    case If(cond, thenExpr, elseExpr) => interp(cond, env) match
      case BoolV(true)                          => interp(thenExpr, env)
      case BoolV(false)                         => interp(elseExpr, env)
      case _                                    => error(s"invalid operation")
    case TypeDef(name, varts, body)             => interp(body, env ++ varts.map(vart => vart.name -> ConstrV(vart.name)))
    case Match(expr, mcases) => interp(expr, env) match
      case VariantV(name, values) => mcases.find(mcase => mcase.name == name && mcase.params.length == values.length) match
        case Some(matched)                      => interp(matched.body, env ++ matched.params.zip(values).toMap)
        case None                               => error(s"no such type implemented")
      case _                                    => error(s"not a variant")
}
