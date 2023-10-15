package kuplrg

object Implementation extends Template {

  import Expr.*

  def interp(expr: Expr): Value = expr match
    case Num(number)          => number
    case Add(l, r)            => interp(l) + interp(r)
    case Mul(l, r)            => interp(l) * interp(r)

  def countNums(expr: Expr): Int = expr match
  case Num(number)            => 1
  case Add(l, r)              => countNums(l) + countNums(r)
  case Mul(l, r)              => countNums(l) + countNums(r)
}
