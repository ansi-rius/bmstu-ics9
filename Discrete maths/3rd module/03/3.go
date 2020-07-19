package main

import (
        "fmt"
)

type Vertex struct {
        i int
	parent *Vertex
	depth int
}

func DFS(mass [][]int, begin int, m int, n int, Num [][]int, NumNew [][]int, Str [][]string, StrNew[][]string) ([][]int, [][]string, int){
	used := make([]bool, n)
	stack := newStack(n)
	sizeStack := 0
	arr := make([] int, n)
	count := 0
	stack[sizeStack] = begin
	sizeStack++
	for sizeStack > 0 {
		sizeStack--
		v := stack[sizeStack]
		if !used[v] {
			used[v] = true
			//fmt.Println("arr[",v,"] = ",used[v])
			arr[v] = count
			//fmt.Println("cc arr[",v,"] = ",arr[v])
			count++
		}
		for i := m - 1; i > -1; i-- {
			u := mass[v][i]
			if !used[u] {
				stack[sizeStack] = u
				sizeStack++
			}
		}
	}
	/*for i := 0; i < n; i++ {
		fmt.Println("used[",i,"] = ",arr[i])
	}
	fmt.Println("co = ", count)*/
	NumNew, StrNew = Change(arr, used,  Num, NumNew, count, m, Str, StrNew, n)
	return NumNew, StrNew, count
}

func newStack(n int) []int  {
	stack := make([]int, n*n)
	return stack
}

func Search(used []int, f int) (int) {
	for i := range used {
		if used[i] == f {
			return i
		}
	}
	return 0
}

func Search1(Qn []int, qn int) (bool) {
	var eq bool
	if Qn[qn] != -1 {
		eq = true
	}
	/*for i:= range Qn {
		if Qn[i] == qn {
			eq = true
		}
	}*/
	return eq
}

func Change(used []int, b []bool, mass [][]int, NumNew [][]int, k int, m int, Str [][]string, StrNew [][]string, n int) ([][]int, [][]string) {

	for i := 0; i < n; i++ {
		if b[i] {
			StrNew[used[i]] = Str[i]
			for j := 0; j < m; j++ {
				NumNew[used[i]][j] = used[mass[i][j]]
			}
		}
	}
	/*fmt.Println("aaaaaaaaaa")
	for i := 0; i < k; i++ {
		for j := 0; j < m; j++ {
			fmt.Print(NumNew[i][j], " ")
		}
		fmt.Println()
	}
	fmt.Println("aaaaaaaaaa")*/
	return NumNew, StrNew
}

func Find(x *Vertex) (*Vertex) {
	var root *Vertex
	if (x.parent == x) {
		root = x
		return root
	} else {
		x.parent = Find(x.parent)
		root = x.parent
		return root
	}
}

func Union(x *Vertex, y *Vertex) {
	var rootX = Find(x)
	var rootY = Find(y)
	if rootX.depth < rootY.depth {
		rootX.parent = rootY
	} else {
		rootY.parent = rootX
		if rootX.depth == rootY.depth && rootX != rootY {
			rootX.depth = rootX.depth + 1
		}
	}
}

func Split(n int, m int, delta [][]int, fi [][]string, pi []int) (int, []int){
	var mn= n
	var eq bool
	Q := make([]Vertex, n)

	for q:=0; q < n; q++ {
		Q[q].i = q
		Q[q].parent = &Q[q]
		Q[q].depth = 0
	}
	for q1:=0; q1<n; q1++ {
		for q2:=0; q2<n; q2++ {
			if pi[Q[q1].i] == pi[Q[q2].i] && Find(&Q[q1]) != Find(&Q[q2]) {
				eq = true
				for x:=0; x<m; x++ {
					var w1 = delta[Q[q1].i][x]
					var w2 = delta[Q[q2].i][x]
					if pi[w1] != pi[w2] {
						eq = false
						break
					}
				}
				if eq {
					Union(&Q[q1], &Q[q2])
					mn--
				}
			}
		}
	}
	for q:=0; q<n; q++ {
		pi[Q[q].i] = Find(&Q[q]).i
	}
	return mn, pi
}

func Split1(n int, m int, NumNew [][]int, StrNew [][]string) (int, []int) {
	var eq bool
	var mn = n
	pi := make([]int, n)
	Q := make([]Vertex, n)

	for q:=0; q < n; q++ {
		Q[q].i = q
		Q[q].parent = &Q[q]
		Q[q].depth = 0
	}

	for q1:=0; q1<n; q1++ {
		for q2:=0; q2<n; q2++ {
			if Find(&Q[q1]) != Find(&Q[q2]) {
				eq = true
				for x:=0; x<m; x++ {
					if StrNew[q1][x] != StrNew[q2][x] {
						eq = false
						break
					}
				}
				if eq {
					Union(&Q[q1], &Q[q2])
					mn--
				}
			}
		}
	}
	for q:=0; q<n; q++ {
		pi[Q[q].i] = Find(&Q[q]).i
		//fmt.Print("pi = ",pi[Q[q].i], " ")
	}
	return mn, pi
}

func AufenkampHohn(n int, m int, NumNew [][]int, StrNew [][]string) ([][]int, [][]string, []int){
	m_res, pi := Split1(n, m, NumNew, StrNew)
	var m_res1 int
	for {
		m_res1, pi = Split(n, m, NumNew, StrNew, pi)
		if m_res == m_res1 {
			break
		}
		m_res = m_res1
	}
	/*fmt.Println("pi:")
	for i := 0; i < n; i++ {
		fmt.Print(pi[i], " ")
	}
	fmt.Println()*/

	Qn := make([]int, n)

	delta := make([][]int, n)
	fi := make([][]string, n)
	for i:=0; i<n; i++ {
		delta[i] = make([]int, m)
		fi[i] = make([]string, m)
	}
	c := 0
	//eq := make([]bool, n)
	for i :=0; i < n ;i++ {
		Qn[i] = -1
	}
	help := make([]bool, n)
	for q:=0; q<n; q++ {
		var qn = pi[q]
		if !Search1(Qn, qn) {
			//if !eq[qn]{
			// eq[qn] = true
			c++
			Qn[q] = q
			for x:=0; x<m; x++ {
				help[qn] = true
				delta[qn][x] = pi[NumNew[q][x]]
				//fmt.Print(delta[qn][x], " ")
				fi[qn][x] = StrNew[q][x]
			}
			//fmt.Println()
		}
	}
	return delta, fi, pi
}

func main() {
	var n, m, q, k int

	fmt.Scan(&n)
	fmt.Scan(&m)
	fmt.Scan(&q)
	//n = 3; m = 2; q = 1

	Num := make([][]int, n)
	Str := make([][]string, n)
	NumNew := make([][]int, n)
	StrNew := make([][]string, n)
	//used := make([]int, n)
	help := make([]int, n)
	for i:=0; i<n; i++ {
		Num[i] = make([]int, m)
		NumNew[i] = make([]int, m)
		Str[i] = make([]string, m)
		StrNew[i] = make([]string, m)
	}
	for i:=0; i<n; i++ {
		for j:=0; j<m; j++ {
			fmt.Scan(&Num[i][j])
		}
	}
	for i:=0; i<n; i++ {
		for j:=0; j<m; j++ {
			fmt.Scan(&Str[i][j])
		}
	}

	Num, Str, help = AufenkampHohn(n, m, Num, Str)

	NumNew, StrNew, k = DFS(Num, help[q], m, n, Num, NumNew, Str, StrNew)
	
	n = k
	//все, связанное с выводом
	alphabet := make([]byte, 27)
	q = 0
	for i:=0; i<27; i++ {
		alphabet[i] = (byte) (i+97)
	}
	fmt.Println("digraph {")
	fmt.Println("    rankdir = LR")
	fmt.Println("    dummy [label = \"\" , shape = none]")
	for i:=0; i<n; i++ {
		fmt.Println("    ",i," [shape = circle]")
	}
	fmt.Println("    dummy -> ", q)
	for i:=0; i<n; i++ {
		for j:=0; j<m; j++ {
			//fmt.Println("    ",q," -> ",goMatrix_delta[i][j]," [label = \"",array[j],"(",exitMatrix_fi[i][j],")\"]")
			fmt.Printf("     %d -> %d [label = \"%c(%s)\"]",i,NumNew[i][j],alphabet[j], StrNew[i][j])
			fmt.Println()
		}
		q++
	}
	fmt.Println("}")
} 