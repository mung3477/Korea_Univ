package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*

  def interp(expr: Expr, env: Env): Value = expr match
    // unit
    case EUnit                                              => UnitV
    // numbers
    case ENum(number: BigInt)                               => NumV(number)
    // booleans
    case EBool(bool: Boolean)                               => BoolV(bool)
    // identifier lookups
    case EId(name: String)                                  => env.getOrElse(name, error(s"free identifier"))
    // addition
    case EAdd(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                               => NumV(l + r)
      case (l, v)                                           => error(s"invalid operation")
    // multiplication
    case EMul(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                               => NumV(l * r)
      case (l, v)                                           => error(s"invalid operation")
    // division
    case EDiv(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r)) => NumV(r) match
        case NumV(0)                                        => error(s"invalid operation")
        case v                                              => NumV(l / r)
      case (l, v)                                           => error(s"invalid operation")
    // modulo
    case EMod(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r)) => NumV(r) match
        case NumV(0)                                        => error(s"invalid operation")
        case v                                              => NumV(l % r)
      case (l, v)                                           => error(s"invalid operation")
    // equal-to
    case EEq(left: Expr, right: Expr) => BoolV(eq(interp(left, env), interp(right, env)))
    // less-than
    case ELt(left: Expr, right: Expr) => (interp(left, env), interp(right, env)) match
      case (NumV(l), NumV(r))                               => BoolV(l < r)
      case (l, v)                                           => error(s"invalid operation")
    // conditional
    case EIf(cond: Expr, thenExpr: Expr, elseExpr: Expr) => interp(cond, env) match
      case BoolV(b)                                         => if (b) interp(thenExpr, env) else interp(elseExpr, env)
      case v                                                => error(s"not a boolean")
    // empty list
    case ENil                                               => NilV
    // list cons
    case ECons(head: Expr, tail: Expr)                      => ConsV(interp(head, env), interp(tail, env))
    // list head
    case EHead(list: Expr) => interp(list, env) match
      case ConsV(h, _)                                      => h
      case NilV                                             => error(s"empty list")
      case _                                                => error(s"not a list")
    // list tail
    case ETail(list: Expr) => interp(list, env) match
      case ConsV(_, t)                                      => t
      case NilV                                             => error(s"empty list")
      case _                                                => error(s"not a list")
    // list length
    case ELength(list: Expr)                                => NumV(length(interp(list, env)))
    // list map function
    case EMap(list: Expr, fun: Expr)                        => map(interp(list, env), interp(fun, env))
    // list flatMap function
    case EFlatMap(list: Expr, fun: Expr)                    => join(map(interp(list, env), interp(fun, env)))
    // list filter function
    case EFilter(list: Expr, fun: Expr)                     => filter(interp(list, env), interp(fun, env))
    // tuple
    case ETuple(exprs: List[Expr])                          => TupleV(exprs.map(expr => interp(expr, env)))
    // tuple projection
    case EProj(tuple: Expr, index: Int) => interp(tuple, env) match
      case TupleV(values)                                   => if (index <= values.length) values(index - 1) else error(s"out of bounds")
      case _                                                => error(s"not a tuple")
    // variable definition
    case EVal(name: String, value: Expr, scope: Expr)       => interp(scope, env + (name -> interp(value, env)))
    // lambda function
    case EFun(params: List[String], body: Expr)             => CloV(params, body, () => env)
    // mutually recursive function
    case ERec(defs: List[FunDef], scope: Expr)              =>
      lazy val newEnv: Env = defs.foldLeft(env)((l, fundef) => l + (fundef.name -> CloV(fundef.params, fundef.body, () => newEnv)))
      interp(scope, newEnv)
    // function application
    case EApp(fun: Expr, args: List[Expr])                  => app(interp(fun, env), args.map(arg => interp(arg, env)))



  def eq(left: Value, right: Value): Boolean = (left, right) match
    case (UnitV, UnitV)                                     => true
    case (NumV(l), NumV(r))                                 => l == r
    case (BoolV(l), BoolV(r))                               => l == r
    case (NilV, NilV)                                       => true
    case (ConsV(h, t), ConsV(h2, t2))                       => eq(h, h2) && eq(t, t2)
    case (NilV, ConsV(_, _))                                => false
    case (ConsV(_, _), NilV)                                => false
    case (TupleV(l), TupleV(r))                             => l.equals(r)
    case _                                                  => error(s"invalid operation")

  def length(list: Value): BigInt = list match
    case (NilV)                                             => 0
    case (ConsV(_, t))                                      => 1 + length(t)
    case _                                                  => error(s"not a list")

  def map(list: Value, fun: Value): Value = (list, fun) match
    case (NilV, _)                                          => NilV
    case (ConsV(h, t), CloV(_, _, _))                       => ConsV(app(fun, List(h)), map(t, fun))
    case (ConsV(h, t), _)                                   => error(s"not a function")
    case _                                                  => error(s"not a list")

  def join(list: Value): Value = list match
    case NilV                                               => NilV
    case ConsV(NilV, t)                                     => join(t)
    case ConsV(ConsV(h, t), t2)                             => ConsV(h, join(ConsV(t, t2)))
    case _                                                  => error(s"not a list")

  def filter(list: Value, fun: Value): Value = (list, fun) match
    case (NilV, _)                                          => NilV
    case (ConsV(h, t), f) => app(f, List(h)) match
      case BoolV(bool)                                      => if (bool) ConsV(h, filter(t, f)) else filter(t, f)
      case _                                                => error(s"not a boolean")
    case _                                                  => error(s"not a list")

  def app(fun: Value, args: List[Value]): Value = (fun, args) match
    case (CloV(params, body, env), args) => (params.length <= args.length) match
      case true                                             => interp(body, (params zip args.take(params.length)).map((k, v) => k -> v).foldLeft(env())(_ + _))
      case false                                            => interp(body, (params zip (args ++ List.fill(params.length - args.length)(UnitV))).map((k, v) => k -> v).foldLeft(env())(_ + _) )
    case (_, _)                                             => error(s"not a function")
}
