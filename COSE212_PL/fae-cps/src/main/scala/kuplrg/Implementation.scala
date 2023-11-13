package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Cont.*

  type BOp = (BigInt, BigInt) => BigInt
  def numBOp(x: String)(op: BOp)(l: Value, r: Value): Value = (l, r) match
    case (NumV(l), NumV(r))                         => NumV(op(l, r))
    case (l, r)                                     => error(s"invalid operation ${l.str} $x ${r.str}")

  val numAdd: (Value, Value) => Value = numBOp("+")(_ + _)
  val numMul: (Value, Value) => Value = numBOp("*")(_ * _)

  def interpCPS(expr: Expr, env: Env, k: Value => Value): Value = expr match
    // numbers
    case Num(number: BigInt)                        => k(NumV(number))
    // additions
    case Add(left: Expr, right: Expr)               => interpCPS(left, env, lv => {
                                                          interpCPS(right, env, rv => k(numAdd(lv, rv)))
                                                        })
    // multiplications
    case Mul(left: Expr, right: Expr)               => interpCPS(left, env, lv => {
                                                          interpCPS(right, env, rv => k(numMul(lv, rv)))
                                                        })
    // identifier lookups
    case Id(name: String)                           => k(env.getOrElse(name, error(s"free identifier")))
    // anonymous (lambda) functions
    case Fun(param: String, body: Expr)             => k(CloV(param, body, env))
    // function applications
    case App(fun: Expr, arg: Expr)                  => interpCPS(fun, env, fv => fv match
                                                          case CloV(p, b, fenv) => interpCPS(arg, env, av
                                                                                    => interpCPS(b, fenv + (p -> av), k))
                                                          case _                => error(s"not a function")
                                                        )

  def reduce(k: Cont, s: Stack): (Cont, Stack) = (k, s) match
    case (EmptyK, s)                                     => (EmptyK, s)
    case (EvalK(env: Env, expr: Expr, k: Cont), s) => expr match
      // numbers
      case Num(number: BigInt)                      => (k, NumV(number) :: s)
      // additions
      case Add(left: Expr, right: Expr)             => (EvalK(env, left, EvalK(env, right, AddK(k))), s)
      // multiplications
      case Mul(left: Expr, right: Expr)             => (EvalK(env, left, EvalK(env, right, MulK(k))), s)
      // identifier lookups
      case Id(name: String)                         => (k, env.getOrElse(name, error(s"free identifier")) :: s)
      // anonymous (lambda) functions
      case Fun(param: String, body: Expr)           => (k, CloV(param, body, env) :: s)
      // function applications
      case App(fun: Expr, arg: Expr)                => (EvalK(env, fun, EvalK(env, arg, AppK(k))), s)
    case (AddK(k: Cont), r :: l :: s)               => (k, numAdd(l, r) :: s)
    case (MulK(k: Cont), r :: l :: s)               => (k, numMul(l, r) :: s)
    case (AppK(k: Cont), arg :: f :: s) => f match
      case CloV(p, b, fenv)                         => (EvalK(fenv + (p -> arg), b, k), s)
      case _                                        => error(s"not a function")
}
