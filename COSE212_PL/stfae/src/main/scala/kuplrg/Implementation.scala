package kuplrg

object Implementation extends Template {

  import Expr.*
  import Value.*
  import Type.*

  def isSubType(ty: Type, targetTy: Type): Boolean = (ty, targetTy) match
    case (BotT, _)                                        => true
    case (_, TopT)                                        => true
    case (ArrowT(lpty, lrty), ArrowT(rpty, rRty))         => isSubType(rpty, lpty) && isSubType(lrty, rRty)
    case (RecordT(lfs), RecordT(rfs))                     => rfs.map((key, value) => lfs.get(key) match
                                                                  case Some(ty)       => ty == value || isSubType(ty, value)
                                                                  case None           => false
                                                              ).foldLeft(true)(_ && _)
    case (lty, rty)                                       => lty == rty

  def mustSubType(ty: Type, targetTy: Type): Unit =
    if (!isSubType(ty, targetTy)) error(s"type mismatch: not a subtype")

  def mustValid(ty: Type, tenv: TypeEnv): Type = ty match
    case NumT                             => NumT
    case ArrowT(paramTy, retTy)           => ArrowT(mustValid(paramTy, tenv), mustValid(retTy, tenv))
    case RecordT(fields)                  => RecordT(fields.keys.zip(fields.values.map(mustValid(_, tenv))).toMap)
    case BotT                             => BotT
    case TopT                             => TopT

  def typeCheck(expr: Expr, tenv: TypeEnv): Type = expr match
    case Num(_)                           => NumT
    case Add(left, right)                 => mustSubType(typeCheck(left, tenv), NumT); mustSubType(typeCheck(right, tenv), NumT); NumT
    case Mul(left, right)                 => mustSubType(typeCheck(left, tenv), NumT); mustSubType(typeCheck(right, tenv), NumT); NumT
    case Id(name)                         => tenv.getOrElse(name, error(s"unknown type"))
    case Val(name, tyOpt, init, body) => tyOpt match
      case Some(ty)                       => mustSubType(typeCheck(init, tenv), ty); typeCheck(body, tenv + (name -> ty))
      case None                           => typeCheck(body, tenv + (name -> typeCheck(init, tenv)))
    case Fun(param, ty, body)             => val pty = mustValid(ty, tenv); ArrowT(pty, typeCheck(body, tenv + (param -> pty)))
    case App(fun, arg) => typeCheck(fun, tenv) match
      case ArrowT(pty, rty)               => mustSubType(typeCheck(arg, tenv), pty); rty
      case _                              => error(s"type mismatch: not an arrow type")
    case Record(fs)                       => RecordT(fs.map((attr, expr) => (attr -> typeCheck(expr, tenv))).toMap)
    case Access(record, field) => typeCheck(record, tenv) match
      case RecordT(fs)                    => fs.getOrElse(field, error(s"unknown field"))
      case _                              => error(s"type mismatch: not a record type")
    case Exit                             => BotT

  def interp(expr: Expr, env: Env): Value = expr match
    case Num(n)                           => NumV(n)
    case Add(left, right) => (interp(left, env), interp(right, env)) match
      case (NumV(lv), NumV(rv))           => NumV(lv + rv)
      case _                              => error(s"invalid operation")
    case Mul(left, right) => (interp(left, env), interp(right, env)) match
      case (NumV(lv), NumV(rv))           => NumV(lv * rv)
      case _                              => error(s"invalid operation")
    case Val(name, tyOpt, init, body)     => interp(body, env + (name -> interp(init, env)))
    case Fun(param, ty, body)             => CloV(param, body, env)
    case Id(name)                         => env.getOrElse(name, error(s"free identifier"))
    case App(fun, arg) => interp(fun, env) match
      case CloV(param, body, fenv)        => interp(body, fenv + (param -> interp(arg, env)))
      case _                              => error(s"not a function")
    case Record(fields)                   => RecordV(fields.map((name, expr) => (name -> interp(expr, env))).toMap)
    case Access(record, field) => interp(record, env) match
      case RecordV(fields)                => fields.getOrElse(field, error(s"no such field"))
      case _                              => error(s"not a record")
    case Exit                             => error(s"ERROR: Bot")

}
