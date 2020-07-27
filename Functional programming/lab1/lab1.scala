
var flatten: (List[List[Int]], Int => Boolean) => List[Int] =
{
    case (Nil, p) => Nil
    case (x :: xs, p) if (p(x.length)) => x ::: flatten(xs, p)
    case (x :: xs, p) => flatten(xs, p)
}

val list = List(List(1, 2, 3), List(1, 2), List(1, 2, 3))

val res = flatten(list, (x: Int) => x == 3)
//res: List[Int] = List(1, 2, 3, 1, 2, 3)

val res = flatten(list, (x: Int) => x == 1)
//List[Int] = List()

val res = flatten(list, (x: Int) => x == 2)
//res: List[Int] = List(1, 2)