//Идеальный "размен" суммы денег минимальным количеством рублёвых купюр и монет.
//Операции: объединение двух разменов (+), пересечение (-), получение количества купюр
//или монет заданного номинала (count)

//2 вариант

import cash.nominals

object cash {
  val nominals = List(5000,2000,1000,500,200,100,50,10,5,2,1) //все возможные номиналы
  def divide(money: Int)={
    val origin: (Int, List[(Int, Int)]) = (money,Nil) //откуда отсчет
    val list = nominals.foldLeft(origin) ((p, n) => { //функция высчитывания кол-ва купюр
      val (x,list) = p
      (x%n, (n,x/n)::list) //остаток от деления на купюру, количество таких купюр
    })
    list._2.toMap
  }
}

class Change private (ax: Map[Int,Int]) {
  val money: Map[Int, Int] = ax
  def this(amount:Int) = this(cash.divide(amount))


  def sum()= nominals.foldLeft(0)((sum, n)=> sum+n*money(n))

  //операция объединения
  def + (v: Change) = new Change(sum()+v.sum())
  //пересечение
  def - (v: Change) = new Change(sum()-v.sum())
  //получение количества
  def count(n: Int): Map[Int,Int] = Map(n-> money(n))
}

object Lab2 {
  def main(args: Array[String]) {
    val sum1 = new Change(5000)
    val sum2 = new Change(1250)
    val sum3 = new Change(1179)
    println(sum1.money.toSeq.sortBy(_._1)) //5000
    println((sum1-sum2).money.toSeq.sortBy(_._1)) //3750 = 2000+1000+500+200+50
    println((sum2+sum3).money.toSeq.sortBy(_._1)) //2429 = 2000+200+200+10+10+5+2+2
    println(sum3.count(2)) // 2
  }
}