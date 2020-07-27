package main

import (
    "fmt"
    "github.com/RealJK/rss-parser-go"
)

func main() {

    rssObject, err := rss.ParseRSS("http://blagnews.ru/rss_vk.xml")
    if err != nil {

	    fmt.Printf("Title           : %s\n", rssObject.Channel.Title)
		fmt.Printf("Generator       : %s\n", rssObject.Channel.Generator)
		fmt.Printf("PubDate         : %s\n", rssObject.Channel.PubDate)
		fmt.Printf("LastBuildDate   : %s\n", rssObject.Channel.LastBuildDate)
		fmt.Printf("Description     : %s\n", rssObject.Channel.Description)

		fmt.Printf("Number of Items : %d\n", len(rssObject.Channel.Items))

	for v := range rssObject.Channel.Items {
		item := rssObject.Channel.Items[v]
			fmt.Println()
		fmt.Printf("Item Number : %d\n", v)
		fmt.Printf("Title       : %s\n", item.Title)
		fmt.Printf("Link        : %s\n", item.Link)
		fmt.Printf("Description : %s\n", item.Description)
		fmt.Printf("Guid        : %s\n", item.Guid.Value)
		}
    }
}
