package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def interp(expr: Expr, env: Env): Value = expr match
    // numbers
    case Num(number: BigInt)                          => NumV(number)
    // additions
    case Add(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                         => NumV(l + r)
      case (l, r)                                     => error(s"invalid operation")
    // multiplications
    case Mul(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                         => NumV(l * r)
      case (l, r)                                     => error(s"invalid operation")
    // immutable variable definitions
    case Val(name: String, init: Expr, body: Expr)    => interp(body, env + (name -> interp(init, env)))
    // identifier lookups
    case Id(name: String)                             => env.getOrElse(name, error(s"free identifier"))
    // anonymous (lambda) functions
    case Fun(param: String, body: Expr)               => CloV(param, body, env)
    // function applications
    case App(fun: Expr, arg: Expr) => interp(fun, env) match
      case CloV(param, body, fenv)                    => interp(body, fenv + (param -> interp(arg, env)))
      case v                                          => error(s"not a function")

  def interpDS(expr: Expr, env: Env): Value = expr match
    // numbers
    case Num(number: BigInt)                          => NumV(number)
    // additions
    case Add(left: Expr, right: Expr) => (interpDS(left, env), interpDS(right, env)) match
      case (NumV(l), NumV(r))                         => NumV(l + r)
      case (l, r)                                     => error(s"invalid operation")
    // multiplications
    case Mul(left: Expr, right: Expr) => (interpDS(left, env), interpDS(right, env)) match
      case (NumV(l), NumV(r))                         => NumV(l * r)
      case (l, r)                                     => error(s"invalid operation")
    // immutable variable definitions
    case Val(name: String, init: Expr, body: Expr)    => interpDS(body, env + (name -> interpDS(init, env)))
    // identifier lookups
    case Id(name: String)                             => env.getOrElse(name, error(s"free identifier"))
    // anonymous (lambda) functions
    case Fun(param: String, body: Expr)               => CloV(param, body, env)
    // function applications
    case App(fun: Expr, arg: Expr) => interpDS(fun, env) match
      case CloV(param, body, fenv)                    => interpDS(body, env + (param -> interpDS(arg, env)))
      case v                                          => error(s"not a function")
}
