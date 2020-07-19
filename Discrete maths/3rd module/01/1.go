package main

import (
        "fmt"
)

func DFS(used []int, mass [][]int, ind int, begin int, m int, n int, k *int) {
	for i:=0; i<n; i++ {
		used[i] = -1
	}
	//for i:=0; i<n; i++ {
		//if used[i] == -1 {
			VisitVertex(used, mass, ind, begin, m, n, k)
		//}
	//}
}

func VisitVertex(used []int, mass [][]int, ind int, begin int, m int, n int, k *int) {
	used[begin] = *k
	//fmt.Println(" i = ", ind)
	(*k)++
	for i:=0; i<m; i++ {
		if used[mass[begin][i]] == -1 {
			//ind++
			VisitVertex(used, mass, ind, mass[begin][i], m, n, k)
		}
	}
}

func Search(used []int, f int) (int) {
	for i := range used {
		if used[i] == f {
			return i
		}
	}
	return 0
}

func Change(used []int, mass [][]int, NumNew [][]int, k int, m int, Str [][]string, StrNew [][]string, n int) {
	//fmt.Println("!k = ",k)
	for i:=0; i<n; i++ {
		for j:=0; j<m; j++ {
			if used[i] != -1 {
				NumNew[used[i]][j] = used[mass[i][j]]
			}
		}
	}
	for i := 0; i < k; i++ {
		for j := 0; j < m; j++ {
			fmt.Print(NumNew[i][j], " ")
		}
		fmt.Println()
	}

	for i := 0; i < k; i++ {
		for j:=0; j<m; j++ {
			fmt.Print(Str[Search(used, i)][j], " ")
		}
		fmt.Println()
	}
}

func main() {
	var n, m, q, ind, k int

	fmt.Scan(&n)
	fmt.Scan(&m)
	fmt.Scan(&q)
	//n = 3; m = 2; q = 1

	Num := make([][]int, n)
	Str := make([][]string, n)
	NumNew := make([][]int, n)
	StrNew := make([][]string, n)
	used := make([]int, n)
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

	/*Num[0][0] = 1; Num[0][1] = 0; Num[1][0] = 2; Num[1][1] = 0; Num[2][0] = 2; Num[2][1] = 2
	Str[0][0] = "x"; Str[0][1] = "y"; Str[1][0] = "y"; Str[1][1] = "x"; Str[2][0] = "x"; Str[2][1] = "y"*/

	DFS(used, Num, ind, q, m, n, &k)

	fmt.Print(k, "\n", m, "\n", 0, "\n")

	/*for i := 0; i < n; i++ {
		fmt.Println("used[",i,"] = ",used[i])
	}*/

	Change(used, Num, NumNew, k, m, Str, StrNew, n)
}