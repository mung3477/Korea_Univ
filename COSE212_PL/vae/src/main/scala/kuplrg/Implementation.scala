package kuplrg

object Implementation extends Template {

  import Expr.*

  def interp(expr: Expr, env: Env): Value = expr match
    case Num(n)                 => n
    case Add(l, r)              => interp(l, env) + interp(r, env)
    case Mul(l, r)              => interp(l, env) * interp(r, env)
    case Val(name, init, body)  => interp(body, env + (name -> interp(init, env)))
    case Id(x)                  => env.getOrElse(x, error(s"free identifier: $x"))

  def freeIds(expr: Expr): Set[String] = expr match
    case Num(n)                 => Set()
    case Add(l, r)              => freeIds(l) ++ freeIds(r)
    case Mul(l, r)              => freeIds(l) ++ freeIds(r)
    case Val(name, init, body)  => freeIds(body) - name ++ freeIds(init)
    case Id(x)                  => Set(x)

  def bindingIds(expr: Expr): Set[String] = expr match
    case Num(n)                 => Set()
    case Add(l, r)              => bindingIds(l) ++ bindingIds(r)
    case Mul(l, r)              => bindingIds(l) ++ bindingIds(r)
    case Val(name, init, body)  => Set(name) ++ bindingIds(init) ++ bindingIds(body)
    case Id(x)                  => Set()

  /*
    이번 단계에서 추가할 수 있는 bound Id 후보군: 내부에서 freeId 이었던 것들
    추가되는 대상: Val 선언되는 name
  */
  def boundIds(expr: Expr): Set[String] = expr match
    case Num(n)                 => Set()
    case Add(l, r)              => boundIds(l) ++ boundIds(r)
    case Mul(l, r)              => boundIds(l) ++ boundIds(r)
    case Val(name, init, body)  => boundIds(init) ++ boundIds(body) ++ (if (freeIds(body).contains(name)) Set(name) else Set())
    case Id(x)                  => Set()

  /*
    이번 단계에서 추가할 수 있는 shadowed Id 후보군: Val 선언되는 name
    Shadow되는 조건: bindingId
  */
  def shadowedIds(expr: Expr): Set[String] = expr match
    case Num(n)                 => Set()
    case Add(l, r)              => shadowedIds(l) ++ shadowedIds(r)
    case Mul(l, r)              => shadowedIds(l) ++ shadowedIds(r)
    case Val(name, init, body)  => shadowedIds(init) ++ shadowedIds(body) ++ (if (bindingIds(body).contains(name)) Set(name) else Set())
    case Id(x)                  => Set()
}
