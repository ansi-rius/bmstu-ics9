package main

import (
        "fmt"
	)

type Vertex struct {
	mark int
	pair []int
	letter string
	lett string
	num int
	boo bool
}

var k int

func mark(graph []Vertex, N int, M int, ind int) {
	graph[ind].mark = k
	eq := false
	//fmt.Print("k = ", k)
	for i:=0; i<N*M; i++ {
		//eq = false
		if i != ind && i<ind && graph[ind].num == graph[i].num && graph[ind].letter == graph[i].letter {
			//fmt.Print("i == ", i, " ind = ", ind)
			//fmt.Print("!")
			graph[ind].mark = graph[i].mark
			graph[ind].boo= true
			//k--
			eq = true
			//fmt.Println()
		}
	}
	//k++
	if !eq {
		k++
	}
}

func main() {
	var N,K,M int

	fmt.Scan(&M)
	enteralph := make([]string, M)
	for i:=0; i<M; i++ {
		fmt.Scan(&enteralph[i])
	}
	/*for i:=0; i<M; i++ {
		fmt.Print("! ",enteralph[i], " ")
	}*/

	fmt.Scan(&K)
	finalalph := make([]string, K)
	for i:=0; i<K; i++ {
		fmt.Scan(&finalalph[i])
	}
	/*for i:=0; i<K; i++ {
		fmt.Print("! ",finalalph[i], " ")
	}*/

	fmt.Scan(&N)
	//fmt.Println("! ",N)
	Num := make([][]int, N)
	Str := make([][]string, N)
	for i:=0; i<N; i++ {
		Num[i] = make([]int, M)
		Str[i] = make([]string, M)
	}

	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			fmt.Scan(&Num[i][j])
		}
	}
	for i := 0; i < N; i++ {
		for j := 0; j < M; j++ {
			fmt.Scan(&Str[i][j])
		}
	}

	graph := make([]Vertex, N*M)
	for i:=0; i<N*M; i++ {
		graph[i].pair = append(graph[i].pair, 0)
		graph[i].pair = append(graph[i].pair, 0)
		//fmt.Print(len(graph[i].pair))
	}
	s :=0
	for i:=0; i<N; i++ {
		for j:=0; j<M; j++ {
			//fmt.Print("s = ", s, " ")
			graph[s].letter = Str[i][j]
			graph[s].pair[0] = i
			graph[s].pair[1] = Num[i][j]
			graph[s].num = Num[i][j]
			graph[s].lett = enteralph[j]
			s++
		}
	}
	k = 0
	for i:=0; i<N*M; i++ {
		mark(graph, N, M, i)
	}

	fmt.Println("digraph {")
	fmt.Println("	    rankdir = LR")

	for i:=0; i<N*M; i++ {
		//fmt.Println(graph[i].mark, "  ", i)
		if !graph[i].boo {
			fmt.Print("        ",graph[i].mark, " [label = \"(", graph[i].num, ",", graph[i].letter, ")\"]")
			fmt.Println()
			start := graph[i].pair[1]
			//fmt.Println(start)
			for j := 0; j < N*M; j++ {
				if start == graph[j].pair[0] {
					fmt.Print("        ", graph[i].mark, " -> ", graph[j].mark, " [label = \"", graph[j].lett, "\"]")
					fmt.Println()
				}
			}
		}
	}

	fmt.Println("}")
}
