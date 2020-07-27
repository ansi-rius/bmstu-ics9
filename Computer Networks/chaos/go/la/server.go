package main
 
import (
    "github.com/gliderlabs/ssh"
    "log"
    "os/exec"
    "golang.org/x/crypto/ssh"
)
 
func execute(cmd []string) string {
    out, err := exec.Command(cmd[0], cmd[1:]...).Output()
    if err != nil {
        log.Println(err)
    }
    return string(out)
}
 
func handlerGoSSH(s ssh.Session) {
    cmd := s.Command()
    var line string
    for _, s := range cmd {
        line += " " + s
    }
    response1 := runCommand(line, "lab_15_2018", "SDJ2iud3", "lab.posevin.com:22")
    response2 := runCommand(line, "lab2_15_2018", "SDJ2iud3", "lab2.posevin.com:22")
    if response1 != "" {
        _, err := s.Write([]byte(response1))
        if err != nil {
            log.Println(err)
        }
    }
    if response2 != "" {
        _, err := s.Write([]byte(response2))
        if err != nil {
            log.Println(err)
        }
    }
}
 
 func runCommand(command, user, password, host string) string {
    sshConfig := &ssh.ClientConfig{
        User:            user,
        Auth:            []ssh.AuthMethod{ssh.Password(password)},
        HostKeyCallback: ssh.InsecureIgnoreHostKey(),
    }
 
    client, err := ssh.Dial("tcp", host, sshConfig)
    if err != nil {
        panic(err)
    }
    defer client.Close()
    session, err := client.NewSession()
    if err != nil {
        panic(err)
    }
    defer session.Close()
    if command == "exit\n" {
        return ""
    }
    out, err := session.Output(command)
    if err != nil {
        panic(err)
    }
    return string(out)
}
//func handlerOpenSSH(s ssh.Session) {
//  term := terminal.NewTerminal(s, "> ")
//  for {
//      line, err := term.ReadLine()
//      if err != nil {
//          log.Println(err)
//          break
//      }
//      cmd := strings.Split(line, " ")
//      if cmd[0] == "exit" {
//          break
//      }
//      response := execute(cmd)
//      if response != "" {
//          _, err := term.Write(append([]byte(response), '\n'))
//          if err != nil {
//              log.Println(err)
//              break
//          }
//      }
//  }
//  log.Println("terminal closed")
//}
 
func main() {
    //log.Fatal(ssh.ListenAndServe("localhost:2001", handlerOpenSSH,
    log.Fatal(ssh.ListenAndServe("localhost:2000", handlerGoSSH,
        ssh.PasswordAuth(func(ctx ssh.Context, pass string) bool {
            return pass == "password"
        }),
    ))
}