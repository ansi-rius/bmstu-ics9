package main

import (
	"github.com/gliderlabs/ssh"
	"io"
	"log"
	"fmt"
)

func checkPass(ctx ssh.Context, password string) bool {

	if ctx.User() == "max" {
		if password == "123" {
			return true
		}
		return false
	}
	return false
}

func main() {

	ssh.Handle(func(s ssh.Session) {

		fmt.Println("connected")
		user := s.User()
		fmt.Println(user)
		fmt.Println(s.Environ())
		fmt.Println(s.Command())
		fmt.Println(s.LocalAddr())
		fmt.Println(s.RemoteAddr())
		io.WriteString(s, "Hello " + user + "\n")
		//term := terminal.NewTerminal(s, "> ")
		//
		//for {
		//
		//	line, err := term.ReadLine()
		//	if err != nil {
		//		break
		//	}
		//
		//	var out bytes.Buffer
		//	cmd := exec.Command(line)
		//	cmd.Stdout = &out
		//	cmd.Run()
		//	term.Write(out.Bytes())
		//}

		log.Println("terminal closed")
	})

	log.Println("starting ssh server on port: 10054")
	log.Fatal(ssh.ListenAndServe(":10054", nil, ssh.PasswordAuth(checkPass)))
}
