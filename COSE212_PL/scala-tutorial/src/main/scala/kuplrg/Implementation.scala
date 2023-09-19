package kuplrg

object Implementation extends Template {

  def sqsum(x: Int, y: Int): Int = x * x + y * y

  def concat(left: String, right: String): String = left + right

  def subN(n: Int): Int => Int = (x: Int) => x - n

  def twice(f: Int => Int): Int => Int = (x: Int) => f(f(x))

  def compose(f: Int => Int, g: Int => Int): Int => Int = (x: Int) => f(g(x))

  def sumOnlyOdd(l: List[Int]): Int = l.filter(_ % 2 == 1).foldLeft(0)(_ + _)

  def foldWith(f: (Int, Int) => Int): List[Int] => Int = (l: List[Int]) => l.foldLeft(0){ (x: Int, y: Int) => f(x, y)}

  def toSet(l: List[Int], from: Int): Set[Int] = l.drop(from).foldLeft(Set())(_ + _)

  def getOrZero(map: Map[String, Int], key: String): Int = map.get(key).getOrElse(0)

  def setMinus(s1: Set[Int], s2: Set[Int]): Set[Int] = s1.diff(s2)

  // ---------------------------------------------------------------------------
  // Trees
  // ---------------------------------------------------------------------------
  import Tree.*

  def has(value: Int): Tree => Boolean = (t: Tree) => t match
    case Leaf(v)          => v == value
    case Branch(l, v, r)  => v == value || has(value)(l) || has(value)(r)

  def maxDepthOf(value: Int): Tree => Option[Int] = (t: Tree) => t match
    case Leaf(v)          => if (v == value) Some(0) else None
    case Branch(l, v, r)  => if (v == value) Some(0) else {
      val lMaxDepth: Option[Int] = maxDepthOf(value)(l)
      val rMaxDepth: Option[Int] = maxDepthOf(value)(r)
      val ret:Option[Int] = if (lMaxDepth == None) rMaxDepth else if (rMaxDepth == None) lMaxDepth else if (rMaxDepth.get > lMaxDepth.get) rMaxDepth else lMaxDepth
      ret.map(_ + 1)
    }

  def mul(t: Tree): Int = t match
    case Leaf(v)          => v
    case Branch(l, v, r)  => v * mul(l) * mul(r)

  def countLeaves(t: Tree): Int = t match
    case Leaf(_)          => 1
    case Branch(l, _, r)  => countLeaves(l) + countLeaves(r)

  def postOrder(t: Tree): List[Int] = t match
    case Leaf(v)          => List(v)
    case Branch(l, v, r)  => postOrder(l) ++ postOrder(r) ++ List(v)

  // ---------------------------------------------------------------------------
  // Boolean Expressions
  // ---------------------------------------------------------------------------
  import BE.*

  def countLiterals(expr: BE): Int = expr match
    case True         => 1
    case False        => 1
    case And(l, r)    => countLiterals(l) + countLiterals(r)
    case Or(l, r)     => countLiterals(l) + countLiterals(r)
    case Not(expr)    => countLiterals(expr)

  def countNots(expr: BE): Int = expr match
    case True         => 0
    case False        => 0
    case And(l, r)    => countNots(l) + countNots(r)
    case Or(l, r)     => countNots(l) + countNots(r)
    case Not(expr)    => 1 + countNots(expr)

  def depth(expr: BE): Int = expr match
    case True         => 0
    case False        => 0
    case And(l, r)    => (depth(l) max depth(r)) + 1
    case Or(l, r)     => (depth(l) max depth(r)) + 1
    case Not(expr)    => 1 + depth(expr)

  def getString(expr: BE): String = expr match
    case True         => "true"
    case False        => "false"
    case And(l, r)    => "(" + getString(l) + " & " + getString(r) + ")"
    case Or(l, r)     => "(" + getString(l) + " | " + getString(r) + ")"
    case Not(expr)    => "!" + getString(expr)

  def eval(expr: BE): Boolean = expr match
    case True         => true
    case False        => false
    case And(l, r)    => eval(l) && eval(r)
    case Or(l, r)     => eval(l) || eval(r)
    case Not(expr)    => !eval(expr)
}
