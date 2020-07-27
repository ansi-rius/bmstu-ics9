package main

import (
        "github.com/mgutz/logxi/v1"
        "golang.org/x/net/html"
        "net/http"
        "html/template"
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
func isSpan(node *html.Node, class string) bool {
        return isElem(node, "span") && getAttr(node, "class") == class
}
func readItem(item *html.Node) *Item {
                var str = ""
                if cs := getChildren(item); len(cs) == 7 {
                        for c := item.FirstChild; c != nil; c = c.NextSibling {
                                if isSpan(c, "header__indicators__ticker__val") {
                                       if s := getChildren(c) ; isText(s[0]){
                                        str = s[0].Data
                                        break
                                       }

                                }

                        }
                        return &Item{
                                Ref:   getAttr(item, "href"),
                                Name:  getAttr(item,"title"),
                                Value:  str,
                        }
                }
        return nil
}

type Item struct {
        Ref, Name, Value string
}
type Str struct {
		Title string
		Items []*Item
}


func downloadNews() []*Item {
        log.Info("sending request to rbc.ru")
        if response, err := http.Get("https://www.rbc.ru/story/5bc5ad339a7947d5995fd580"); err != nil {
                log.Error("request to rbc.ru failed", "error", err)
        } else {
                defer response.Body.Close()
                status := response.StatusCode
                log.Info("got response from rbc.ru", "status", status)
                if status == http.StatusOK {
                        if doc, err := html.Parse(response.Body); err != nil {
                                log.Error("invalid HTML from rbc.ru", "error", err)
                        } else {
                                log.Info("HTML from rbc.ru parsed successfully")
                                itms := search(doc)
                                for i:=0; i<len(itms); i++{
                                        log.Info(itms[i].Ref)
                                        log.Info(itms[i].Name)
                                        log.Info(itms[i].Value)
                                        log.Info(" ")
                                }
                                templat(itms)
                                //return search(doc)
                        }
                }

        }
        return nil
}

func search(node *html.Node) []*Item {
        //count := 0
        //here:
        if isDiv(node, "header__indicators__items js-indicators-topline") {

                var items []*Item
                for c := node.FirstChild; c != nil; c = c.NextSibling { 
                                if item := readItem(c); item != nil {
                                        items = append(items, item)
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

func templat(item []*Item) []*Item {
	
	data := Str {
		Title: "Курсы валют",
        Items: item,
    }
    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
 
        tmpl, _ := template.ParseFiles("1.http")
        tmpl.Execute(w, data)
    })
 
    log.Info("Server is listening...")
    http.ListenAndServe(":8181", nil)

    return nil
}



//===================================================================================================



func main() {


log.Info("Downloader started")
downloadNews()



}