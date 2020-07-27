package main

import (
    "net"
    "os"
   // "net/http"
    "github.com/RealJK/rss-parser-go"
    "fmt"
    "strconv"
    //"strings"
)

func HomeRouterHandler(conn net.Conn, tcpAddr *net.TCPAddr) {
/* r.ParseForm() //arg analysis
 fmt.Println(r.Form) //entering information about form on serv's side
 fmt.Println("path", r.URL.Path)
 fmt.Println("scheme", r.URL.Scheme)
 fmt.Println(r.Form["url_long"])
 for k, v := range r.Form {
   fmt.Println("key:", k)
   fmt.Println("val:", strings.Join(v, ""))
 }*/
 rssObject, err:=rss.ParseRSS("http://blagnews.ru/rss_vk.xml")

 if err != nil {
  num := make([]byte, 1024)
  num[0]= (byte)(len(rssObject.Channel.Items))
  _, err := conn.Write([]byte(num))
  if err != nil {
    fmt.Println("panic")
  }
  for v := range rssObject.Channel.Items {
        item := rssObject.Channel.Items[v]
	conn, _ := net.DialTCP("tcp", nil, tcpAddr)
        _, err := conn.Write([]byte(item.Description))
	if err != nil {
	  fmt.Println(err)
	  return
	}
	fmt.Print("reply from server #"+strconv.Itoa(v)+" ")
	buf:=make([]byte, (10*1024))
	n, err:=conn.Read(buf)
	if err != nil {break}
	fmt.Print(string(buf[0:n]))
	fmt.Println()
	conn.Close()
  }
 }
}

func main() {
    //strEcho := "test"
    //http.HandleFunc("/", HomeRouterHandler)
    servAddr := "lab.posevin.com:9202"
    tcpAddr, err := net.ResolveTCPAddr("tcp",servAddr)
    if err != nil {
        println("ResolveTCPAddr failed:", err.Error())
        os.Exit(1)
    }

    conn, err := net.DialTCP("tcp", nil, tcpAddr)
    if err != nil {
        println("Dial failed:", err.Error())
        os.Exit(1)
    }

    /*_, err = conn.Write([]byte(strEcho))
    if err != nil {
        println("Write to server failed:", err.Error())
        os.Exit(1)
    }*/

    HomeRouterHandler(conn, tcpAddr)

    //println("write to server = ", strEcho)

    /*reply := make([]byte, 1024)

    _, err = conn.Read(reply)
    if err != nil {
        println("Write to server failed:", err.Error())
        os.Exit(1)
    }

    println("reply from server=", string(reply))
	*/
    conn.Close()
}
