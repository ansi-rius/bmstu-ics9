package main

import (
	"github.com/jlaffaye/ftp"
	"fmt"
)


func main() {

	client, err := ftp.Dial("students.yss.su:21")
	if err != nil {
	  	panic(err)
	}

	if err := client.Login("ftpiu9", "1234567890"); err != nil {
	  	panic(err)
	}

	entries, _ := client.List("")

	for _, entry := range entries {
  		name := entry.Name
  		fmt.Println(name)
  		reader, err := client.Retr(name)
  		if err != nil {
    		panic(err)
    		continue
  		}
  		buf := make([]byte, 1024)
  		reader.Read(buf)
  		fmt.Println(string(buf))
  		return
	}
}