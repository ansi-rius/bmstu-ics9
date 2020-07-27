package main

import (
  "fmt"
  "golang.org/x/crypto/ssh"
)

func main() {

	config := &ssh.ClientConfig{
    	User: "lab_02_2018",
    	Auth: []ssh.AuthMethod{
      		ssh.Password("DKJHfjd4483"),
    	},
        HostKeyCallback: ssh.InsecureIgnoreHostKey(),
  	}

  	connection, err := ssh.Dial("tcp", "lab.posevin.com:22", config)
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