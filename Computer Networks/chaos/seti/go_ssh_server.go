package main


import (
	"bytes"
	//"code.google.com/p/go.crypto/ssh"
	"github.com/gliderlabs/ssh"
	"fmt"
	"io"
	"io/ioutil"
	"os"
	"time"
	"log"
)

type SignerContainer struct {
	signers []ssh.Signer
}

func (t *SignerContainer) Key(i int) (key ssh.PublicKey, err error) {
	if i >= len(t.signers) {
		return
	}
	key = t.signers[i].PublicKey()
	return
}

func (t *SignerContainer) Sign(i int, rand io.Reader, data []byte) (sig []byte, err error) {
	if i >= len(t.signers) {
		return
	}
	sig, err = t.signers[i].Sign(rand, data)
	return
}

func makeSigner(keyname string) (signer ssh.Signer, err error) {
	fp, err := os.Open(keyname)
	if err != nil {
		return
	}
	defer fp.Close()

	buf, _ := ioutil.ReadAll(fp)
	signer, _ = ssh.ParsePrivateKey(buf)
	return
}

func makeKeyring() ssh.ClientAuth {
	signers := []ssh.Signer{}
	keys := []string{os.Getenv("HOME") + "/.ssh/id_rsa", os.Getenv("HOME") + "/.ssh/id_dsa"}

	for _, keyname := range keys {
		signer, err := makeSigner(keyname)
		if err == nil {
			signers = append(signers, signer)
		}
	}

	return ssh.ClientAuthKeyring(&SignerContainer{signers})
}

func executeCmd(cmd, hostname string, config *ssh.ClientConfig) string {
	conn, _ := ssh.Dial("tcp", hostname+":22", config)
	session, _ := conn.NewSession()
	defer session.Close()

	var stdoutBuf bytes.Buffer
	session.Stdout = &stdoutBuf
	session.Run(cmd)

	return hostname + ": " + stdoutBuf.String()
}

func main() {
	cmd := os.Args[1]// first arg - which cmd will be used everywhere
	hosts := os.Args[2:] //other args - list of servs

	results := make(chan string, 10) //results here
	timeout := time.After(5 * time.Second)
	config := &ssh.ClientConfig{
		User: os.Getenv("LOGNAME"),
		Auth: []ssh.ClientAuth{makeKeyring()},
	}

	for _, hostname := range hosts {
		go func(hostname string) {
			results <- executeCmd(cmd, hostname, config)
		}(hostname)
	}
	// obtain results from all servs or time out
	for i := 0; i < len(hosts); i++ {
		select {
		case res := <-results:
			fmt.Print(res)
		case <-timeout:
			fmt.Println("Timed out!")
			return
		}
	}

	ssh.Handle(func(s ssh.Session) {
         io.WriteString(s, "Hello world\n")
     })  

     log.Fatal(ssh.ListenAndServe(":2222", nil))
}
