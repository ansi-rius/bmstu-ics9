package main

import (
 "fmt"
 "net"
 "os"
)

const (
 CONN_HOST = "lab.posevin.com"
 CONN_PORT = "9202"
 CONN_TYPE = "tcp"
)

var count=0;

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
 num :=make([]byte, 1024)
 _, err := conn.Read(num)
 if err != nil {
   fmt.Println("panic")
 }
 for count < ((int)(num[0])) {
   // Make a buffer to hold incoming data.
   buf := make([]byte, (10*1024))
   // Read the incoming connection into the buffer.
   n, err := conn.Read(buf)
   if (string(buf[n-1])) == "*" {conn.Close()}
   if err != nil {
     fmt.Println("Error reading:", err.Error())
   }
   fmt.Println(string(buf))
   // Send a response back to person contacting us.
   conn.Write([]byte("Message received "+(string(count))))
   //conn.Write(count)
   count=count+1
   //fmt.Println("Client say: "+string(buf))
 }
 // Close the connection when you're done with it.
 conn.Close()

}
