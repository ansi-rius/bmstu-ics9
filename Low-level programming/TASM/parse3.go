package main

import (
        "github.com/mgutz/logxi/v1"
	"golang.org/x/net/html"
        "net/http"
)

func getChildren(node *html.Node) []*html.Node {
        var children []*html.Node
        for c := node.FirstChild; c != nil; c = c.NextSibling {
                children = append(children, c)
        }
        return children
}

func getAttr(node *html.Node, key string) string {
        for _, attr := range node.Attr {
                if attr.Key == key {
                        return attr.Val
                }
        }
        return ""
}

func isText(node *html.Node) bool {
        return node != nil && node.Type == html.TextNode
}

func isElem(node *html.Node, tag string) bool {
        return node != nil && node.Type == html.ElementNode && node.Data == tag
}

func isDiv(node *html.Node, class string) bool {
        return isElem(node, "div") && getAttr(node, "class") == class
}

func readItem(item *html.Node) *Item {
        if a := item.FirstChild; isElem(a, "a") {
                if cs := getChildren(a); len(cs) == 2 && isElem(cs[0], "time") && isText(cs[1]) {
                        return &Item{
                                Ref:   getAttr(a, "href"),
                                Time:  getAttr(cs[0], "title"),
                                Title: cs[1].Data,
                        }
                }
        }
        return nil
}

type Item struct {
        Ref, Time, Title string
}


func downloadNews() []*Item {
        log.Info("sending request to lenta.ru")
        if response, err := http.Get("http://lenta.ru"); err != nil {
                log.Error("request to lenta.ru failed", "error", err)
        } else {
                defer response.Body.Close()
                status := response.StatusCode
                log.Info("got response from lenta.ru", "status", status)
                if status == http.StatusOK {
                        if doc, err := html.Parse(response.Body); err != nil {
                                log.Error("invalid HTML from lenta.ru", "error", err)
                        } else {
                                log.Info("HTML from lenta.ru parsed successfully")
                                itms := search(doc)
				for i:=0; i<len(itms); i++{
					log.Info(itms[i].Ref+" "+itms[i].Time+" "+itms[i].Title)
				}
				return search(doc)
                        }
                }
        }
        return nil
}

func search(node *html.Node) []*Item {
        count := 0
        here:
        if isDiv(node, "span4") {
                if count == 0 {
                        count++
                        goto here
                }
                var items []*Item
                for c := node.FirstChild; c != nil; c = c.NextSibling {
                        if isDiv(c, "item") {
                                if item := readItem(c); item != nil {
                                        items = append(items, item)
                                }
                        }
                }
                return items
        }
        for c := node.FirstChild; c != nil; c = c.NextSibling {
                if items := search(c); items != nil {
                        return items
                }
        }
        return nil
}





//===================================================================================================



func main() {


log.Info("Downloader started")
downloadNews()



}
