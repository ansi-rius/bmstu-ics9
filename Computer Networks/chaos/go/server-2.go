package main

import (
	"log"
	"os/exec"
	"strings"

	"github.com/gliderlabs/ssh"
	"golang.org/x/crypto/ssh/terminal"
)

var server = "localhost:2223"

func handleCommand(command string, args ...string) []byte {
	output, err := exec.Command(command, args...).Output()

	if err == nil {
		return append(output, '\n')
	}

	log.Fatal("Error while handleCommand ", err)
	return nil
}

func sendMessage(term *terminal.Terminal, text []byte) {
	term.Write(text)
}

func handleUserInput(term *terminal.Terminal) {
	for {
		line, err := term.ReadLine()

		if err != nil {
			log.Fatal("Error while reading ", err)
			break
		}

		input := strings.Split(line, " ")
		command := input[0]
		args := input[1:]

		switch command {
		case "server":
			sendMessage(term, append([]byte(server), '\n'))
		default:
			sendMessage(term, handleCommand(command, args...))
		}
	}

	log.Println("Terminal closed")
}

func handleSession(session ssh.Session) {
	term := terminal.NewTerminal(session, "> ")
	handleUserInput(term)
}

func main() {
	log.Println("Starting ssh server: ", server)
	log.Fatal(ssh.ListenAndServe(":2223", handleSession))
}
