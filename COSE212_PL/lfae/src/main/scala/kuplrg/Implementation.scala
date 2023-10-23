package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def strict(v: Value): Value = v match
    case ExprV(expr, env)                => strict(interp(expr, env))
    case _                               => v

  type BOp = (BigInt, BigInt) => BigInt
  def NumBOp(x: String)(op: BOp)(l: Value, r: Value): Value = (strict(l), strict(r)) match
    case (NumV(l), NumV(r))                               => NumV(op(l, r))
    case _                                                => error(s"invalid operation: ${l.str} ${x} ${r.str}")

  def interp(expr: Expr, env: Env): Value = expr match
    // numbers
    case Num(number: BigInt)                  => NumV(number)
    // additions
    case Add(left: Expr, right: Expr) => NumBOp("+")(_ + _)(interp(left, env), interp(right, env))
    // multiplications
    case Mul(left: Expr, right: Expr) => NumBOp("*")(_ * _)(interp(left, env), interp(right, env))
    // identifier lookups
    case Id(name: String)                     => env.getOrElse(name, error(s"free identifier"))
    // anonymous (lambda) functions
    case Fun(param: String, body: Expr)       => CloV(param, body, env)
    // function applications
    case App(fun: Expr, arg: Expr) => strict(interp(fun, env)) match
      case CloV(p, b, fenv)                       => interp(b, fenv + (p -> ExprV(arg, env)))
      case _                                      => error(s"not a function")
}
