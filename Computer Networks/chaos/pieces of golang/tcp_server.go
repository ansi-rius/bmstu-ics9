package main

import (
 "fmt"
 "net"
 "os"
)

const (
 CONN_HOST = "lab.posevin.com"
 CONN_PORT = "10009"
 CONN_TYPE = "tcp"
)

func main() {
 // Listen for incoming connections.
 l, err := net.Listen(CONN_TYPE, CONN_HOST + ":" + CONN_PORT)
 if err != nil {
  fmt.Println("Error listening:", err.Error())
  os.Exit(1)
 }
 // Close the listener when the application closes.
 defer l.Close()

 fmt.Println("Listening on " + CONN_HOST + ":" + CONN_PORT)
 for {
  // Listen for an incoming connection.
  conn, err := l.Accept()
  if err != nil {
   fmt.Println("Error accepting: ", err.Error())
   os.Exit(1)
  }
  // Handle connections in a new goroutine.
  go handleRequest(conn)
 }
}

// Handles incoming requests.
func handleRequest(conn net.Conn) {
// Make a buffer to hold incoming data.
 for true{
 buf := make([]byte, (1024 * 10))
 // Read the incoming connection into the buffer.
 _, err := conn.Read(buf)
if err != nil {
if err.Error() == "EOF"{break}
fmt.Println("Error reading:", err.Error())
 }
 // Send a response back to person contacting us.
 conn.Write([]byte("Message received."))
 fmt.Println(string(buf))

 // Close the connection when you're done with it.
}
conn.Close();
}
