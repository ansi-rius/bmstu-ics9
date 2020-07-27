package main

import (
	"fmt"

	"golang.org/x/crypto/ssh"
)

func main() {

	var con [2]*ssh.ClientConfig
	var users [2]*ssh.Client

	con[0] = &ssh.ClientConfig{
		User: "lab_18_2018",
		Auth: []ssh.AuthMethod{
			ssh.Password("DUDDB880909"),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	con[1] = &ssh.ClientConfig{
		User: "lab2_18_2018",
		Auth: []ssh.AuthMethod{
			ssh.Password("DUDDB880906"),
		},
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	var err error

	users[0], err = ssh.Dial("tcp", "lab.posevin.com:22", con[0])
	if err != nil {
		panic(err)
	}

	users[1], err = ssh.Dial("tcp", "lab2.posevin.com:22", con[1])
	if err != nil {
		panic(err)
	}

	session0, err := users[0].NewSession()
	if err != nil {
		panic(err)
	}

	defer session0.Close()
	fmt.Print("1 : \n")
	b, err := session0.CombinedOutput("ls")
	if err != nil {
		panic(err)
	}
	fmt.Print(string(b))

	session1, err := users[1].NewSession()
	if err != nil {
		panic(err)
	}
	fmt.Print("2 : \n")
	defer session1.Close()
	b, err = session1.CombinedOutput("ls")
	if err != nil {
		panic(err)
	}
	fmt.Print(string(b))

}
