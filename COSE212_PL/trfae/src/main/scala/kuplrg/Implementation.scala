package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Type.*

  def mustSame(lty: Type, rty: Type): Unit =
    if (lty != rty) error(s"type error")

  def mustNumT(left: Expr, right: Expr, tenv: TypeEnv): Unit =
    mustSame(typeCheck(left, tenv), NumT)
    mustSame(typeCheck(right, tenv), NumT)

  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case Num(num)                                 =>  NumT
    case Bool(bool)                               =>  BoolT
    case Add(left, right)                         =>  mustNumT(left, right, tenv)
                                                      NumT

    case Mul(left, right)                         =>  mustNumT(left, right, tenv)
                                                      NumT

    case Div(left, right)                         =>  mustNumT(left, right, tenv)
                                                      NumT

    case Mod(left, right)                         =>  mustNumT(left, right, tenv)
                                                      NumT

    case Eq(left, right)                          =>  mustNumT(left, right, tenv)
                                                      BoolT

    case Lt(left, right)                          =>  mustNumT(left, right, tenv)
                                                      BoolT

    case Val(name, init, body)                    =>  {
                                                        val pty = typeCheck(init, tenv)
                                                        typeCheck(body, tenv + (name -> pty))
                                                      }

    case Id(name)                                 => tenv.getOrElse(name, error(s"free identifier"))

    case Fun(param, pty, body)                    => ArrowT(pty, typeCheck(body, tenv + (param -> pty)))

    case App(fun, arg) => typeCheck(fun, tenv) match
      case ArrowT(pty, rty)                       => {
                                                      mustSame(pty, typeCheck(arg, tenv))
                                                      rty
                                                    }
      case _                                      => error(s"type error")

    case Rec(x, p, pty, rty, body, scope)         => {
                                                      mustSame(rty, typeCheck(body, tenv + (p -> pty) + (x -> ArrowT(pty, rty))))
                                                      typeCheck(scope, tenv + (x -> ArrowT(pty, rty)))
                                                    }
    case If(cond, thenExpr, elseExpr)             => {
                                                      mustSame(typeCheck(cond, tenv), BoolT)
                                                      val thenty = typeCheck(thenExpr, tenv)
                                                      val elsety = typeCheck(elseExpr, tenv)
                                                      mustSame(thenty, elsety)
                                                      thenty
                                                    }

  type NumBOp = (BigInt, BigInt) => BigInt
  type NumCmp = (BigInt, BigInt) => Boolean

  def numBOp(op: NumBOp)(l: Value, r: Value): Value = (l, r) match
    case (NumV(left), NumV(right))                => NumV(op(left, right))
    case _                                        => error(s"invalid operation")

  def numRightNonZeroBOp(op: NumBOp)(l: Value, r: Value): Value = (l, r) match
    case (NumV(left), NumV(right)) => right match
      case 0                                      => error(s"Second operand should not be zero")
      case _                                      => NumV(op(left, right))
    case _                                        => error(s"invalid operation")

  def numCmp(op: NumCmp)(l: Value, r: Value): Value = (l, r) match
    case (NumV(left), NumV(right))                => BoolV(op(left, right))
    case _                                        => error(s"invalid operation")


  val numAdd: (l: Value, r: Value) => Value = numBOp(_ + _)
  val numMul: (l: Value, r: Value) => Value = numBOp(_ * _)
  val numDiv: (l: Value, r: Value) => Value = numRightNonZeroBOp(_ / _)
  val numMod: (l: Value, r: Value) => Value = numRightNonZeroBOp(_ % _)
  val numEq: (l: Value, r: Value) => Value = numCmp(_ == _)
  val numLt: (l: Value, r: Value) => Value = numCmp(_ < _)


  def interp(expr: Expr, env: Env): Value = expr match
    case Num(num)                                 => NumV(num)
    case Bool(bool)                               => BoolV(bool)
    case Add(left, right)                         => numAdd(interp(left, env), interp(right, env))
    case Mul(left, right)                         => numMul(interp(left, env), interp(right, env))
    case Div(left, right)                         => numDiv(interp(left, env), interp(right, env))
    case Mod(left, right)                         => numMod(interp(left, env), interp(right, env))
    case Eq(left, right)                          => numEq(interp(left, env), interp(right, env))
    case Lt(left, right)                          => numLt(interp(left, env), interp(right, env))
    case Val(name, init, body)                    => interp(body, env + (name -> interp(init, env)))
    case Id(name)                                 => env.getOrElse(name, error(s"free identifier"))
    case Fun(p, pty, body)                        => CloV(p, body, () => env)
    case App(fun, arg) => interp(fun, env) match
      case CloV(p, body, fenv)                    => interp(body, fenv() + (p -> interp(arg, env)))
      case _                                      => error(s"not a function")
    case Rec(x, p, pty, rty, body, scope)         => {
                                                      lazy val renv: Env = env + (x -> CloV(p, body, () => renv))
                                                      interp(scope, renv)
                                                    }
    case If(cond, thenExpr, elseExpr) => interp(cond, env) match
      case BoolV(true)                            => interp(thenExpr, env)
      case BoolV(false)                           => interp(elseExpr, env)

}
