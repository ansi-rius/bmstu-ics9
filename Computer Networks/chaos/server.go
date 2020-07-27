package main

import (
 "fmt"
 "net/http"
 "net"
 "os"
 "strings"
 "github.com/RealJK/rss-parser-go"
)

const (
 CONN_HOST = "lab.posevin.com"
 CONN_PORT = "9002"
 CONN_TYPE = "tcp"
)

var itms = map[string]string{}

func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {
 r.ParseForm() //arg analysis
 fmt.Println(r.Form) //entering information about form on serv's side
 fmt.Println("path", r.URL.Path)
 fmt.Println("scheme", r.URL.Scheme)
 fmt.Println(r.Form["url_long"])
 for k, v := range r.Form {
   fmt.Println("key:", k)
   fmt.Println("val:", strings.Join(v, ""))
 }
 rssObject, err:=rss.ParseRSS("http://blagnews.ru/rss_vk.xml")

 if err != nil {
   
      itms["Title"]           = rssObject.Channel.Title
      itms["Generator"]       = rssObject.Channel.Generator
      //"PubDate"         : rssObject.Channel.PubDate,
      itms["LastBuildDate"]   = rssObject.Channel.LastBuildDate
      itms["Description"]     = rssObject.Channel.Description
     // "Number of Items" : len(rssObject.Channel.Items),
   
 }
}

func main() {
 http.HandleFunc("/", HomeRouterHandler)
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
   //os.Exit(1)
   conn.Close()
   continue
  }
  // Handle connections in a new goroutine.
  go handleRequest(conn)
 }
}

// Handles incoming requests.
func handleRequest(conn net.Conn) {
 // Make a buffer to hold incoming data.
 for {
   buf := make([]byte, 1024)
   // Read the incoming connection into the buffer.
   n, err := conn.Read(buf)
   if err != nil {
      fmt.Println("Error reading:", err.Error())
      break
    }
    source:=string(buf[0:n])
    target, ok:=itms[source]
    if ok == false{
      target = "undefined"
    }
    fmt.Println(source, ":     ", target)
    // Send a response back to person contacting us.
    conn.Write([]byte("Message received."))
    //conn.Write([]byte(buf))
    //fmt.Println("Client say: "+string(buf))
    // Close the connection when you're done with it.
    //conn.Close()
    conn.Write([]byte(target))
   }
}

