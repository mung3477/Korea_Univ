package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def malloc(mem: Mem): Addr = mem.keySet.maxOption.fold(0)(_ + 1)

  def interp(expr: Expr, env: Env, mem: Mem): (Value, Mem) = expr match
    // number
    case Num(number: BigInt)                    => (NumV(number), mem)
    // addition
    case Add(left: Expr, right: Expr)           =>
      val (lV, mem2) = interp(left, env, mem)
      val (rV, mem3) = interp(right, env, mem2)
      (lV, rV) match
        case (NumV(l), NumV(r))                 => (NumV(l + r), mem3)
        case _                                  => error(s"invalid operation")
    // multiplication
    case Mul(left: Expr, right: Expr) =>
      val (lV, mem2) = interp(left, env, mem)
      val (rV, mem3) = interp(right, env, mem2)
      (lV, rV) match
        case (NumV(l), NumV(r))                 => (NumV(l * r), mem3)
        case _                                  => error(s"invalid operation")
    // identifier lookup
    case Id(name: String)                       => (env.getOrElse(name, error(s"free identifier")), mem)
    // anonymous (lambda) function
    case Fun(param: String, body: Expr)         => (CloV(param, body, env), mem)
    // function application
    case App(fun: Expr, arg: Expr) => interp(fun, env, mem) match
      case (CloV(param, body, fenv), mem2)      =>
        val (argV, mem3) = interp(arg, env, mem2)
        interp(body, fenv + (param -> argV), mem3)
      case _                                    => error(s"not a function")
    // box creation
    case NewBox(content: Expr)                  =>
      val (cv, mem2) = interp(content, env, mem)
      val newAddr: Addr = malloc(mem2)
      (BoxV(newAddr), mem2 + (newAddr -> cv))
    // box content getter
    case GetBox(box: Expr) =>
      val (bv, mem2) = interp(box, env, mem)
      bv match
        case (BoxV(addr))                          => (mem2(addr), mem2)
        case _                                     => error(s"not a box")
    // box content setter
    case SetBox(box: Expr, content: Expr) =>
      val (bv, mem2) = interp(box, env, mem)
      bv match
        case (BoxV(addr))                          =>
          val (cv, mem3) = interp(content, env, mem2)
          (cv, mem3 + (addr -> cv))
        case _                                     => error(s"not a box")
    // sequence
    case Seq(left: Expr, right: Expr) =>
      val (_, mem2) = interp(left, env, mem)
      interp(right, env, mem2)
}
