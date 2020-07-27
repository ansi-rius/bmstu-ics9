package main
import (
    "net"
    "os"
    "github.com/RealJK/rss-parser-go"
    "fmt"
)


func main() {
   // strEcho := "STOP!!"
    servAddr := "lab.posevin.com:10009"
    tcpAddr, err := net.ResolveTCPAddr("tcp", servAddr)
    if err != nil {
        println("ResolveTCPAddr failed:", err.Error())
        os.Exit(1)
    }

    conn, err := net.DialTCP("tcp", nil, tcpAddr)
    if err != nil {
        println("Dial failed:", err.Error())
        os.Exit(1)
    }

    rssObject, err := rss.ParseRSS("http://blagnews.ru/rss_vk.xml")
    if err != nil {
    for v := range rssObject.Channel.Items {
	item := rssObject.Channel.Items[v]
	_,err := conn.Write([]byte(string(item.Description)))
    //_, err = conn.Write([]byte(strEcho))
    if err != nil {
        fmt.Println("Write to server failed:", err.Error())
        os.Exit(1)
    }
  //  println("write to server = ", strEcho)
    fmt.Println("Reply from server :")
    reply := make([]byte, (1024 * 10))
    _,err = conn.Read(reply)
 //   fmt.Println(string(reply[0:S]))
    if err != nil {
        break
    }
    fmt.Println(string(reply)+"Title: "+ item.Title )

   // println("reply from server=", string(reply))
}
}
//    conn.Write([]byte(strEcho))
    conn.Close()
}
