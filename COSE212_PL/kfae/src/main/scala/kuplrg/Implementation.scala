package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Cont.*

  type BOp = (BigInt, BigInt) => (BigInt);
  def NumBop(x: String)(op: BOp)(l: Value, r: Value): Value = (l, r) match
    case (NumV(left), NumV(right))              => NumV(op(left, right))
    case _                                      => error(s"invalid operation")

  val NumAdd: (Value, Value) => (Value) = NumBop("+")(_ + _);
  val NumMul: (Value, Value) => (Value) = NumBop("*")(_ * _);

  def reduce(k: Cont, s: Stack): (Cont, Stack) = (k, s) match
    case (EmptyK, s)                            => (EmptyK, s)
    case (EvalK(env, expr, k), s) => expr match
      case Num(number)                          => (k, NumV(number) :: s)
      case Add(l, r)                            => (EvalK(env, l, EvalK(env, r, AddK(k))), s)
      case Mul(l, r)                            => (EvalK(env, l, EvalK(env, r, MulK(k))), s)
      case Id(name)                             => (k, env.getOrElse(name, error(s"free identifier")) :: s)
      case Fun(param, body)                     => (k, CloV(param, body, env) :: s)
      case App(fun, arg)                        => (EvalK(env, fun, EvalK(env, arg, AppK(k))), s)
      case Vcc(name, body)                      => (EvalK(env + (name -> ContV(k, s)), body, k), s)
    case (AddK(k), l :: r :: s)                 => (k, NumAdd(l, r) :: s)
    case (MulK(k), l :: r :: s)                 => (k, NumMul(l, r) :: s)
    case (AppK(k), a :: f :: s) => f match
      case CloV(param, body, fenv)              => (EvalK(fenv + (param -> a), body, k), s)
      case ContV(cont, stack)                   => (cont, a :: stack)
      case _                                    => error(s"not a function")
}
