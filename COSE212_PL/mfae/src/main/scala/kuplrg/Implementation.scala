package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def malloc(mem: Mem): Addr = mem.keySet.maxOption.fold(0)(_ + 1)

  def interp(expr: Expr, env: Env, mem: Mem): (Value, Mem) = expr match
    // number
    case Num(number: BigInt)                          => (NumV(number), mem)
    // addition
    case Add(left: Expr, right: Expr) =>
      val (lv, updated) = interp(left, env, mem)
      val (rv, res_mem) = interp(right, env, updated)
      (lv, rv) match
        case (NumV(l), NumV(r))                       => (NumV(l + r), res_mem)
        case _                                        => error(s"invalid operation")
    // multiplication
    case Mul(left: Expr, right: Expr) =>
      val (lv, updated) = interp(left, env, mem)
      val (rv, res_mem) = interp(right, env, updated)
      (lv, rv) match
        case (NumV(l), NumV(r))                       => (NumV(l * r), res_mem)
        case _                                        => error(s"invalid operation")
    // mutable variable definition
    case Var(name: String, init: Expr, body: Expr)    =>
      val (initV, imem) = interp(init, env, mem)
      val newAddr: Addr = malloc(imem)
      interp(body, env + (name -> newAddr), imem + (newAddr -> initV))
    // identifier lookup
    case Id(name: String)                             => (mem(env.getOrElse(name, error(s"free identifier"))), mem)
    // anonymous (lambda) function
    case Fun(param: String, body: Expr)               => (CloV(param, body, env), mem)
    // function application
    case App(fun: Expr, arg: Expr) => interp(fun, env, mem) match
      case (CloV(param, body, fenv), fmem)            =>
        val (argV, argMem) = interp(arg, env, fmem)
        val newAddr: Addr = malloc(argMem)
        interp(body, fenv + (param -> newAddr), argMem + (newAddr -> argV))
      case _                                          => error(s"not a function")

    // variable assignment
    case Assign(name: String, expr: Expr)             =>
      val (newV, newMem) = interp(expr, env, mem)
      val addr: Addr = env.getOrElse(name, error(s"free identifier"))
      (newV, mem + (addr -> newV))
    // sequence
    case Seq(left: Expr, right: Expr)                 =>
      val (lV, lmem) = interp(left, env, mem)
      interp(right, env, lmem)

  def interpCBR(expr: Expr, env: Env, mem: Mem): (Value, Mem) = expr match
    // number
    case Num(number: BigInt)                          => (NumV(number), mem)
    // addition
    case Add(left: Expr, right: Expr) =>
      val (lv, updated) = interpCBR(left, env, mem)
      val (rv, res_mem) = interpCBR(right, env, updated)
      (lv, rv) match
        case (NumV(l), NumV(r))                       => (NumV(l + r), res_mem)
        case _                                        => error(s"invalid operation")
    // multiplication
    case Mul(left: Expr, right: Expr) =>
      val (lv, updated) = interpCBR(left, env, mem)
      val (rv, res_mem) = interpCBR(right, env, updated)
      (lv, rv) match
        case (NumV(l), NumV(r))                       => (NumV(l * r), res_mem)
        case _                                        => error(s"invalid operation")
    // mutable variable definition
    case Var(name: String, init: Expr, body: Expr)    =>
      val (initV, imem) = interpCBR(init, env, mem)
      val newAddr: Addr = malloc(imem)
      interpCBR(body, env + (name -> newAddr), imem + (newAddr -> initV))
    // identifier lookup
    case Id(name: String)                             => (mem(env.getOrElse(name, error(s"free identifier"))), mem)
    // anonymous (lambda) function
    case Fun(param: String, body: Expr)               => (CloV(param, body, env), mem)
    // function application
    case App(fun: Expr, arg: Expr) => interpCBR(fun, env, mem) match
      case (CloV(param, body, fenv), fmem) => arg match
        case Id(name)                                 =>
          val addr: Addr = env.getOrElse(name, error(s"free identifier"))
          interpCBR(body, fenv + (param -> addr), fmem)
        case _                                        =>
          val (argV, argMem) = interp(arg, env, fmem)
          val newAddr: Addr = malloc(argMem)
          interpCBR(body, fenv + (param -> newAddr), argMem + (newAddr -> argV))
      case _                                          => error(s"not a function")
    // variable assignment
    case Assign(name: String, expr: Expr)             =>
      val (newV, newMem) = interpCBR(expr, env, mem)
      val addr: Addr = env.getOrElse(name, error(s"free identifier"))
      (newV, mem + (addr -> newV))
    // sequence
    case Seq(left: Expr, right: Expr)                 =>
      val (lV, lmem) = interpCBR(left, env, mem)
      interpCBR(right, env, lmem)

}
