package main //client
 
import (
    "time"
    "flag"
    "net"
    "strings"
    "fmt"
    "github.com/RealJK/rss-parser-go"
    "os"
)

func main() {
    servAddr := "lab.posevin.com:9202"
    tcpAddr, err := net.ResolveTCPAddr("tcp", servAddr)
 
    if err != nil {
        println("ResolveTCPAddr failed:", err.Error())
        os.Exit(1)
    }
 
    conn, err := net.DialTCP("tcp", nil, tcpAddr)

    write_to_server("!end!",conn,tcpAddr)
    
    give_news(conn,tcpAddr)
 
    conn.Close()
}
 
func give_news(conn net.Conn,tcpAddr *net.TCPAddr){
    rssObject, _ := rss.ParseRSS("http://blagnews.xml")

    for v := range rssObject.Channel.Items {
        conn, _ = net.DialTCP("tcp", nil, tcpAddr)
        i := rssObject.Channel.Items[v].Description
        strs := strings.SplitAfter(i,">")
        strs = strings.SplitAfter(strs[1]," ")
        for _,rr := range strs {
            write_to_server(rr,conn,tcpAddr)
        }
        write_to_server("!end!",conn,tcpAddr)
        reply := make([]byte, 1024)
        conn.Read(reply)
        time.Sleep(3000 * time.Millisecond)
        fmt.Printf("reply from server №%d = %s\n",count , string(reply))
        count++
    }
}
var count=0
func write_to_server(str string ,conn net.Conn,tcpAddr *net.TCPAddr){
        conn, _ = net.DialTCP("tcp", nil, tcpAddr)
        conn.Write([]byte(str))
//      time.Sleep(100 * time.Millisecond)
        conn.Close()
}