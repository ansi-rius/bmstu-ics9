// Класс SuperStack[T], представляющий неизменяемый стек с операциями
// push, pop и empty, реализованный через список. В случае, если
// T - числовой тип, для стека должны быть также доступны операции min и
// max, работающие за константное время.

//2 вариант

class SuperStack[T] {
  private var elements: List[T] = Nil

  def push(x: T) {
    elements = x :: elements
  }

  def peek: T = elements.head

  def pop: T = {
    val currentTop = peek
    elements = elements.tail
    currentTop
  }

  def empty: Boolean = {
    if (elements == Nil) true else false
  }

  def max(a: Max[T]) : T = {
    a.max(elements)
  }

  def min(a: Min[T]) : T = {
    a.min(elements)
  }
}

abstract class Max[T] {
  def max(l: List[T]): T
}

object Max {
  object int extends Max[Int] {
    override def max(l: List[Int]): Int = {
      l.max
    }
  }
  object double extends Max[Double] {
    override def max(l: List[Double]): Double = {
      l.max
    }
  } //что делать с оверрайдами на остальные численные типы, как писать AnyVal
}

abstract class Min[T] {
  def min(l: List[T]): T
}

object Min {
  object int extends Min[Int] {
    override def min(l: List[Int]): Int = {
      l.min
    }
  }
  object double extends Min[Double] {
    override def min(l: List[Double]): Double = {
      l.min
    }
  }
}

object Lab2 {
  def main(args: Array[String]) {
    println("Test 1: ")
    val stack1 = new SuperStack[Int]
    println(stack1.empty)
    stack1.push(1)
    stack1.push(2)
    //println(stack1.pop)
    println(stack1.empty)
    //println(stack1.min)
    println(stack1.max(Max.int))
    println()

    println("Test 2: ")
    val stack2 = new SuperStack[String]
    println(stack2.empty)
    stack2.push("One")
    stack2.push("Two")
    println(stack2.pop)
    println(stack2.empty)

  }
}