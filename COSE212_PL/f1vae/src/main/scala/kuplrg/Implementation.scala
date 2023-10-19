package kuplrg

object Implementation extends Template {

  import Expr.*

  def interp(expr: Expr, env: Env, fenv: FEnv): Value = expr match
    // numbers
    case Num(number: BigInt)                          => number
    // additions
    case Add(left: Expr, right: Expr)                 => interp(left, env, fenv) + interp(right, env, fenv)
    // multiplications
    case Mul(left: Expr, right: Expr)                 => interp(left, env, fenv) * interp(right, env, fenv)
    // immutable variable definitions
    case Val(name: String, init: Expr, body: Expr)    => interp(body, env + (name->interp(init, env, fenv)), fenv)
    // identifier lookups
    case Id(name: String)                             => env.getOrElse(name, error(s"free identifier"))
    // function applications
    case App(fname: String, arg: Expr)                =>
      val fdef: FunDef = fenv.getOrElse(fname, error(s"unknown function"))
      interp(fdef.body, Map(fdef.param->interp(arg, env, fenv)), fenv)

  def interpDS(expr: Expr, env: Env, fenv: FEnv): Value = expr match
     // numbers
    case Num(number: BigInt)                          => number
    // additions
    case Add(left: Expr, right: Expr)                 => interpDS(left, env, fenv) + interpDS(right, env, fenv)
    // multiplications
    case Mul(left: Expr, right: Expr)                 => interpDS(left, env, fenv) * interpDS(right, env, fenv)
    // immutable variable definitions
    case Val(name: String, init: Expr, body: Expr)    => interpDS(body, env + (name -> interpDS(init, env, fenv)), fenv)
    // identifier lookups
    case Id(name: String)                             => env.getOrElse(name, error(s"free identifier"))
    // function applications
    case App(fname: String, arg: Expr)                =>
      val fdef: FunDef = fenv.getOrElse(fname, error(s"unknown function"))
      interpDS(fdef.body, env + (fdef.param -> interpDS(arg, env, fenv)), fenv)

}
