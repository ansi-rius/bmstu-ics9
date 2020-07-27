package main

import (
	"fmt"

	"golang.org/x/crypto/ssh"
)

func main() {

	host := "lab.posevin.com"

	cmd := "ls"

	config := &ssh.ClientConfig{
		User:            "lab_18_2018",
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
		Auth: []ssh.AuthMethod{
			ssh.Password("DUDDB880909"),
		},
	}

	addr := fmt.Sprintf("%s:%d", host, 22)
	client, err := ssh.Dial("tcp", addr, config)
	if err != nil {
		panic(err)
	}

	session, err := client.NewSession()
	if err != nil {
		panic(err)
	}
	defer session.Close()

	b, err := session.CombinedOutput(cmd)
	if err != nil {
		panic(err)
	}
	fmt.Print(string(b))
}
