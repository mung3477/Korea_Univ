package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Type.*

  def mustSame(lty: Type, rty: Type): Unit =
    if (lty != rty) error(s"type error")


  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case Num(number)                                        => NumT
    case Add(left, right)                                   => {
                                                                  mustSame(typeCheck(left, tenv), NumT)
                                                                  mustSame(typeCheck(right, tenv), NumT)
                                                                  NumT
                                                              }
    case Mul(left, right)                                   => {
                                                                  mustSame(typeCheck(left, tenv), NumT)
                                                                  mustSame(typeCheck(right, tenv), NumT)
                                                                  NumT
                                                              }
    case Val(name, init, body)                              => typeCheck(body, tenv + (name -> typeCheck(init, tenv)))
    case Id(name)                                           => tenv.getOrElse(name, error(s"type error"))
    case Fun(param, ty, body)                               => ArrowT(ty, typeCheck(body, tenv + (param -> ty)))
    case App(fun, arg) => typeCheck(fun, tenv) match
      case ArrowT(pty, rty)                                 => {
                                                                  mustSame(pty, typeCheck(arg, tenv))
                                                                  rty
                                                              }
      case _                                                => error(s"type error")


  def interp(expr: Expr, env: Env): Value = expr match
    case Num(number)                                        => NumV(number)
    case Add(left, right) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                               => NumV(l + r)
      case _                                                => error(s"invalid operation")
    case Mul(left, right) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                               => NumV(l * r)
      case _                                                => error(s"invalid operation")
    case Val(name, init, body)                              => interp(body, env + (name -> interp(init, env)))
    case Fun(param, pty, body)                              => CloV(param, body, env)
    case Id(name)                                           => env.getOrElse(name, error(s"free identifier"))
    case App(fun, arg) => interp(fun, env) match
      case CloV(param, body, fenv)                          => interp(body, fenv + (param -> interp(arg, env)))
      case _                                                => error(s"invalid operation")
}
