package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def interp(expr: Expr, env: Env): Value = expr match
    // numbers
    case Num(number: BigInt)                                          => NumV(number)
    // booleans
    case Bool(bool: Boolean)                                          => BoolV(bool)
    // identifier lookups
    case Id(name: String)                                             => env.getOrElse(name, error(s"free identifier"))
    // addition
    case Add(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => NumV(l + r)
      case (l, r)                                                     => error(s"invalid operation")
    // multiplication
    case Mul(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => NumV(l * r)
      case (l, r)                                                     => error(s"invalid operation")
    // division
    case Div(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => if (r != 0) NumV(l / r) else error(s"invalid operation")
      case (l, r)                                                     => error(s"invalid operation")
    // modulo
    case Mod(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => if (r != 0) NumV(l % r) else error(s"invalid operation")
      case (l, r)                                                     => error(s"invalid operation")
    // equal-to
    case Eq(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => BoolV(l == r)
      case (l, r)                                                     => error(s"invalid operation")
    // less-than
    case Lt(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                                         => BoolV(l < r)
      case (l, r)                                                     => error(s"invalid operation")
    // anonymous (lambda) functions
    case Fun(param: String, body: Expr)                               => CloV(param, body, () => env)
    // recursive functions
    case Rec(name: String, param: String, body: Expr, scope: Expr)    =>
      lazy val newEnv: Env = env + (name -> CloV(param, body, () => newEnv))
      interp(scope, newEnv)
    // function applications
    case App(fun: Expr, arg: Expr) => interp(fun, env) match
      case CloV(p, b, fenv)                                           => interp(b, fenv() + (p -> interp(arg, env)))
      case v                                                          => error(s"not a function")
    // conditional
    case If(cond: Expr, thenExpr: Expr, elseExpr: Expr) => interp(cond, env) match
      case BoolV(bool)                                                => if (bool) interp(thenExpr, env) else interp(elseExpr, env)
      case v                                                          => error(s"not a boolean")
}
