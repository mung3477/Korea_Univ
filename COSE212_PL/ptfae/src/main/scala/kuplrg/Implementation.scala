package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Type.*

  def isSame(lty: Type, rty: Type): Boolean = (lty, rty) match
    case (NumT, NumT)                               => true
    case (ArrowT(lpty, lrty), ArrowT(rpty, rrty))   => isSame(lpty, rpty) && isSame(lrty, rrty)
    case (VarT(lname), VarT(rname))                 => lname == rname
    case (PolyT(lname, lty), PolyT(rname, rty))     => isSame(lty, subst(rty, rname, VarT(lname)))
    case _                                          => false

  def mustSame(lty: Type, rty: Type): Unit =
    if (!isSame(lty, rty)) error(s"type mismatch")

  def mustValid(ty: Type, tenv: TypeEnv): Type = ty match
    case NumT                                       => NumT
    case ArrowT(paramTy, rty)                       => ArrowT(mustValid(paramTy, tenv), mustValid(rty, tenv))
    case VarT(name)                                 =>
                                                        if (!tenv.tys.contains(name)) error(s"unknown type")
                                                        VarT(name)
    case PolyT(name, ty)                            => PolyT(name, mustValid(ty, tenv.addType(name)))

  def subst(bodyTy: Type, name: String, ty: Type): Type = bodyTy match
    case NumT                                       => NumT
    case ArrowT(paramTy, rty)                       => ArrowT(subst(paramTy, name, ty), subst(rty, name, ty))
    case VarT(x)                                    => if (x == name) ty else VarT(x)
    case PolyT(x, bodyTy)                           => if (x == name) PolyT(x, bodyTy) else PolyT(x, subst(bodyTy, name, ty))

  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case Num(n)                                     => NumT
    case Add(l, r)                                  =>
                                                        mustSame(typeCheck(l, tenv), NumT)
                                                        mustSame(typeCheck(r, tenv), NumT)
                                                        NumT
    case Mul(l, r)                                  =>
                                                        mustSame(typeCheck(l, tenv), NumT)
                                                        mustSame(typeCheck(r, tenv), NumT)
                                                        NumT
    case Val(name, init, body)                      => typeCheck(body, tenv.addVar(name -> typeCheck(init, tenv)))
    case Id(name)                                   => tenv.vars.getOrElse(name, error(s"unknown type"))
    case Fun(param, ty, body)                       =>
                                                        val pty = mustValid(ty, tenv)
                                                        ArrowT(pty, typeCheck(body, tenv.addVar(param ->  pty)))
    case App(fun, arg) => typeCheck(fun, tenv) match
      case ArrowT(paramTy, rty)                     =>
                                                        val argTy = typeCheck(arg, tenv)
                                                        mustSame(paramTy, argTy)
                                                        rty
      case _                                        => error(s"not a function")
    case TypeAbs(name, body)                        =>
                                                        if (tenv.tys.contains(name)) error(s"type is already defined")
                                                        PolyT(name, typeCheck(body, tenv.addType(name)))
    case TypeApp(expr, ty) => typeCheck(expr, tenv) match
      case PolyT(name, bodyTy)                      => subst(bodyTy, name, mustValid(ty, tenv))
      case _                                        => error(s"not a polymorphic type")

  type BOp = (BigInt, BigInt) => BigInt
  def numBOp(Op: BOp)(lv: Value, rv: Value) = (lv, rv) match
    case (NumV(l), NumV(r))                         => NumV(Op(l, r))
    case _                                          => error(s"invalid operation")

  def interp(expr: Expr, env: Env): Value = expr match
    case Num(n)                                     => NumV(n)
    case Add(left, right)                           => numBOp(_ + _)(interp(left, env), interp(right, env))
    case Mul(left, right)                           => numBOp(_ * _)(interp(left, env), interp(right, env))
    case Val(name, init, body)                      => interp(body, env + (name -> interp(init, env)))
    case Fun(param, ty, body)                       => CloV(param, body, env)
    case Id(name)                                   => env.getOrElse(name, error(s"free identifier"))
    case App(fun, arg) => interp(fun, env) match
      case CloV(param, body, fenv)                  => interp(body, fenv + (param -> interp(arg, env)))
      case _                                        => error(s"not a function")
    case TypeAbs(name, body)                        => TypeAbsV(name, body, env)
    case TypeApp(expr, ty) => interp(expr, env) match
      case TypeAbsV(name, body, tyAbsEnv)           => interp(body, tyAbsEnv)
      case _                                        => error(s"not a type abstraction")

}
