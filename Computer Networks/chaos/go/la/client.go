package main

import (
  "fmt"
  "golang.org/x/crypto/ssh"
)

func main() {

	config := &ssh.ClientConfig{
    	User: "user",
    	Auth: []ssh.AuthMethod{
      		ssh.Password("password"),
    	},
      HostKeyCallback: ssh.InsecureIgnoreHostKey(),
  	}

  	connection, err := ssh.Dial("tcp", "localhost:2000", config)
  	if err != nil { 
  		panic(err) 
  	}

  	session, err := connection.NewSession()
  	if err != nil {
  		panic(err)
  	}

  	b, err := session.CombinedOutput("ls")
  	if err != nil {
    	panic(err)
  	}
  	fmt.Print(string(b))

  	session.Close()

}