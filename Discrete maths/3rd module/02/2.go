package main

import "fmt"


func main() {
	var n,m,q int
	fmt.Scan(&n)
	fmt.Scan(&m)
	fmt.Scan(&q)

	goMatrix_delta := make([][]int, n)
	exitMatrix_fi := make([][]string, n)
	alphabet := make([]byte, 27)

	for i:=0; i<27; i++ {
		alphabet[i] = (byte) (i+97)
	}

	for i := 0; i < n; i++ {
		goMatrix_delta[i] = make([]int, m)
		exitMatrix_fi[i] = make([]string, m)
	}

	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scan(&goMatrix_delta[i][j])
		}
	}
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Scan(&exitMatrix_fi[i][j])
		}
	}

	/*for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Print(goMatrix_delta[i][j], " ")
		}
		fmt.Println()
	}
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			fmt.Print(exitMatrix_fi[i][j], " ")
		}
		fmt.Println()
	}*/

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
			fmt.Printf("     %d -> %d [label = \"%c(%s)\"]",i,goMatrix_delta[i][j],alphabet[j],exitMatrix_fi[i][j])
			fmt.Println()
		}
		q++
	}
	fmt.Println("}")
}