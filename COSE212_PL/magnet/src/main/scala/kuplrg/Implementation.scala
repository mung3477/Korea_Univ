package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Inst.*
  import Control.*

  // ---------------------------------------------------------------------------
  // Problem #1
  // ---------------------------------------------------------------------------
  def reduce(st: State): State = st match

      case State(Nil, v :: Nil, h, mem)                        => State(Nil, v :: Nil, h, mem)

      case State(IEval(env, expr) :: k, s, h, mem) => expr match
        case EUndef                                       => State(k, UndefV :: s, h, mem)
        case ENum(n)                                      => State(k, NumV(n) :: s, h, mem)
        case EBool(b)                                     => State(k, BoolV(b) :: s, h, mem)
        case EAdd(l, r)                                   => State(IEval(env, l) :: IEval(env, r) :: IAdd :: k, s, h, mem)
        case EMul(l, r)                                   => State(IEval(env, l) :: IEval(env, r) :: IMul :: k, s, h, mem)
        case EDiv(l, r)                                   => State(IEval(env, l) :: IEval(env, r) :: IDiv :: k, s, h, mem)
        case EMod(l, r)                                   => State(IEval(env, l) :: IEval(env, r) :: IMod :: k, s, h, mem)
        case EEq(l, r)                                    => State(IEval(env, l) :: IEval(env, r) :: IEq :: k, s, h, mem)
        case ELt(l, r)                                    => State(IEval(env, l) :: IEval(env, r) :: ILt :: k, s, h, mem)
        case EVar(name, init, body)                       => State(IEval(env, init) :: IDef(name :: Nil, env, body):: k, s, h, mem)
        case EId(name)                                    => State(k, mem(lookup(env, name)) :: s, h, mem)
        case EAssign(name, expr)                          => State(IEval(env, expr) :: IWrite(lookup(env, name)) :: k, s, h, mem)
        case ESeq(l, r)                                   => State(IEval(env, l) :: IPop :: IEval(env, r) :: k, s, h, mem)
        case EIf(cond, thenExpr, elseExpr)                => State(IEval(env, cond) :: IJmpIf(KValue(IEval(env, thenExpr) :: k, s, h)) :: IEval(env, elseExpr) :: k, s, h, mem)
        case EWhile(cond, body)                           => {
                                                                val phi_continue = KValue(IPop :: IEval(env, expr) :: k, s, h)
                                                                val phi_break = KValue(k, s, h)
                                                                val h_body = h + (Continue -> phi_continue) + (Break -> phi_break)
                                                                val phi_body = KValue(IEval(env, body) :: IJmp(Continue) :: Nil, s, h_body)
                                                                State(IEval(env, cond) :: IJmpIf(phi_body) :: k, UndefV :: s, h, mem)
                                                            }
        case EBreak                                       => State(IJmp(Break) :: Nil, UndefV :: s, h, mem)
        case EContinue                                    => State(IJmp(Continue) :: Nil, UndefV :: s, h, mem)
        case EFun(params, body)                           => State(k, CloV(params, body, env) :: s, h, mem)
        case EApp(fun, args)                              => State(IEval(env, fun) :: args.map(arg => IEval(env, arg)) ++ (ICall(args.length) :: k), s, h, mem)
        case EReturn(expr)                                => State(IEval(env, expr) :: IReturn :: k, s, h, mem)
        case ETry(body, catchParam, catchExpr)            => {
                                                                val psi_throw = KValue(IDef(List[String](catchParam), env, catchExpr) :: k, s, h)
                                                                val psi_finally = KValue(k, s, h)
                                                                State(IEval(env, body) :: IJmp(Finally) :: Nil, s, h + (Throw -> psi_throw) + (Finally -> psi_finally), mem)
                                                              }
        case EThrow(expr)                                 => State(IEval(env, expr) :: IJmp(Throw) :: Nil, s, h, mem)
        case EGen(params, body)                           => State(k, GenV(params, body, env) :: s, h, mem)
        case EIterNext(iter, None)                        => State(IEval(env, iter) :: IEval(env, EUndef) :: INext:: k, s, h, mem)
        case EIterNext(iter, Some(argValue))              => State(IEval(env, iter) :: IEval(env, argValue) :: INext:: k, s, h, mem)
        case EYield(expr)                                 => State(IEval(env, expr) :: IYield :: Nil, BoolV(false) :: ContV(KValue(k, s, h)) :: s, h, mem)
        case EValueField(result)                          => State(IEval(env, result) :: IValueField :: k, s, h, mem)
        case EDoneField(result)                           => State(IEval(env, result) :: IDoneField :: k, s, h, mem)

      case State(IAdd :: k, NumV(n2) :: NumV(n1) :: s, h, mem) => State(k, NumV(n1 + n2) :: s, h, mem)

      case State(IMul :: k, NumV(n2) :: NumV(n1) :: s, h, mem) => State(k, NumV(n1 * n2) :: s, h, mem)

      case State(IDiv :: k, NumV(n2) :: NumV(n1) :: s, h, mem) => n2 match
        case 0                                            => error(s"division by zero")
        case _                                            => State(k, NumV(n1 / n2) :: s, h, mem)

      case State(IMod :: k, NumV(n2) :: NumV(n1) :: s, h, mem) => n2 match
        case 0                                            => error(s"modulo by zero")
        case _                                            => State(k, NumV(n1 % n2) :: s, h, mem)

      case State(IEq :: k, v2 :: v1 :: s, h, mem)              => State(k, BoolV(eq(v1, v2)) :: s, h, mem)

      case State(ILt :: k, NumV(n2) :: NumV(n1) :: s, h, mem)  => State(k, BoolV(n1 < n2) :: s, h, mem)

      case State(IDef(xs, env, body) :: k, s, h, mem)          => {
                                                                val newAddrs = malloc(mem, xs.length)
                                                                val (paramValues: Stack, s_left: Stack) = s.splitAt(xs.length)
                                                                State(IEval(toMapAndConcat(env, xs, newAddrs), body) :: k, s_left, h, toMapAndConcat(mem, newAddrs, paramValues.reverse))
                                                              }

      case State(IWrite(addr) :: k, v :: s, h, mem)            => State(k, v :: s, h, mem + (addr -> v))

      case State(IPop :: k, v :: s, h, mem)                    => State(k, s, h, mem)

      case State(IJmpIf(KValue(k, s, h)) :: _, BoolV(true) :: _, _, mem) => State(k, s, h, mem)

      case State(IJmpIf(_) :: k, BoolV(false) :: s, h, mem)    => State(k, s, h, mem)

      case State(IJmp(cntl) :: k, v :: s, h, mem) => h.getOrElse(cntl, error(s"No handler implemented")) match
        case KValue(cntl_k, cntl_s, cntl_h)                    => {
                                                                    val hPrime = if (h.contains(Yield)) cntl_h + (Yield -> h(Yield)) else cntl_h
                                                                    State(cntl_k, v :: cntl_s, hPrime, mem)
                                                                  }

      case State(ICall(argSize) :: k, s, h, mem) =>
        val (paramValues: Stack, s_left: Stack) = s.splitAt(argSize)
        s_left match
          case CloV(params, body, fenv) :: s              => {
                                                                val s_body = tailOrPadValue(paramValues, params.length, argSize, UndefV)
                                                                val h_body = h + (Return -> KValue(k, s, h)) - Break - Continue - Yield
                                                                State(IDef(params, fenv, EReturn(body)) :: Nil, s_body, h_body, mem)
                                                              }
          case GenV(params, body, genv) :: s              =>
                                                                val addr = malloc(mem)
                                                                // @todo catchExpr 모르겠음
                                                                val k_body = IPop :: IDef(params, genv, EReturn(ETry(body, "x", EId("x")))) :: Nil
                                                                val s_body = tailOrPadValue(paramValues, params.length, argSize, UndefV)
                                                                val phi_body = ContV(KValue(k_body, s_body, Map[Control, KValue]()))
                                                                State(k, IterV(addr) :: s, h, mem + (addr -> phi_body))

          case _                                          => error(s"invalid operation")


      case State(IReturn :: k, v :: s, h, mem)                 => {
                                                                if (h.contains(Yield)) {
                                                                  val phi_done = ContV(KValue(IReturn :: Nil, Nil, Map[Control, KValue]()))
                                                                  State(IYield :: Nil, v :: BoolV(true) :: phi_done :: s, h, mem)
                                                                }
                                                                else
                                                                  State(IJmp(Return) :: Nil, v :: Nil, h, mem)
                                                              }


      case State(INext :: k, v :: IterV(addr) :: s, h, mem) => mem(addr) match
        case ContV(KValue(kPrime, sPrime, hPrime))        => {
                                                                val phi = KValue(k, IterV(addr) :: s, h)
                                                                val h_body = hPrime + (Yield -> phi) + (Return -> phi)
                                                                State(kPrime, v :: sPrime, h_body, mem)
                                                              }
        case _                                            => error(s"invalid operation")


      case State(IYield :: _, v :: BoolV(b) :: vPrime :: _, h, mem) => h(Yield) match
        case KValue(kPrime, IterV(addr) :: sPrime, hPrime)=> State(kPrime, ResultV(v, b) :: sPrime, hPrime, mem + (addr -> vPrime))
        case _                                            => error(s"invalid operation")


      case State(IValueField :: k, ResultV(v, _) :: s, h, mem) => State(k, v :: s, h, mem)


      case State(IDoneField :: k, ResultV(_, b) :: s, h, mem)  => State(k, BoolV(b) :: s, h, mem)

      case _                                             => error(s"invalid operation")


  // ---------------------------------------------------------------------------
  // Problem #2
  // ---------------------------------------------------------------------------
  def bodyOfSquares: String = "while (from <= to) yield from * from++"

  // ---------------------------------------------------------------------------
  // Helper functions
  // ---------------------------------------------------------------------------
  def malloc(mem: Mem, n: Int): List[Addr] =
    val a = malloc(mem)
    (0 until n).toList.map(a + _)

  def malloc(mem: Mem): Addr = mem.keySet.maxOption.fold(0)(_ + 1)

  def lookup(env: Env, x: String): Addr =
    env.getOrElse(x, error(s"free identifier: $x"))

  def lookup(handler: Handler, x: Control): KValue =
    handler.getOrElse(x, error(s"invalid control operation: $x"))

  def eq(l: Value, r: Value): Boolean = (l, r) match
    case (UndefV, UndefV) => true
    case (NumV(l), NumV(r)) => l == r
    case (BoolV(l), BoolV(r)) => l == r
    case (IterV(l), IterV(r)) => l == r
    case (ResultV(lv, ld), ResultV(rv, rd)) => eq(lv, rv) && ld == rd
    case _ => false
}

  def toMapAndConcat[A, B](prev: Map[A, B], keys: List[A], values: List[B]): Map[A, B] =
      keys.zip(values).map((k, v) => (k -> v)).foldLeft(prev)(_ + _)

  def tailOrPadValue(list: List[Value], targetLen: Int, givenLen: Int, value: Value): List[Value] = {
    if (givenLen >= targetLen)
      list.drop(givenLen - targetLen) ++ Nil
    else
      List.fill(targetLen - givenLen)(value) ++ list ++ Nil
  }
