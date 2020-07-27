package main

import (
//	"strconv"
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
	log.Info(getAttr(node, "class"))
        return isElem(node, "div") && getAttr(node, "class") == class
}

func readItem(item *html.Node) *Item {
       if a := item.FirstChild; isElem(a, "div") && isDiv(a,"tv-widget-idea js-widget-idea js-userlink-popup-anchor" ) {
	//a := item.FirstChild
		log.Info("reading item...")
		cs:=getChildren(a)
//		log.Info("len of Chld = ", strconv.Itoa(len(cs)))
//		log.Info(getAttr(cs[0], "class"))
//		log.Info(getAttr(cs[1], "class"))
//		log.Info(getAttr(cs[7], "class"))
//		log.Info(getAttr(cs[3], "class"))
//		log.Info(getAttr(cs[4], "class"))
//		log.Info(getAttr(cs[5], "class"))
//		log.Info(getAttr(cs[6], "class"))
                if isDiv(cs[1], "tv-widget-idea__title-row") {
                        log.Info("into right Div to collect Title")
			b := getChildren(cs[1])
			//log.Info(strconv.FormatBool(isElem(b[1], "a")))
			log.Info("link = ", getAttr(b[1], "href"))
			//log.Info(strconv.FormatBool(isText(b[0])))
			//log.Info(b[0].Data)
			//log.Info(getAttr(b[0], "title"))
			bb := getChildren(b[1])
			log.Info("1) Title = ", bb[0].Data) //a
			//log.Info(b[0].Data) //why nothing? its text between tags
			 /*return &Item{
                               //  Ref:   getAttr(cs[0], "href"),
                               // Time:  getAttr(cs[0], "title"),
                                Title: b[1].Data,
                        }*/
                }
		if isDiv(cs[7], "tv-widget-idea__author-row") {
			log.Info("into right Div to collect Nickname")
			c:= getChildren(cs[7])
			//log.Info(getAttr(c[1], "class"))
			ah:= getChildren(c[1])
			//log.Info(ah[3].Data)
			ahh:= getChildren(ah[3])
			ahhh:= getChildren(ahh[1])
			log.Info("2) Nickname = ", ahhh[0].Data)
		}
		if isElem(cs[9], "a") {
			log.Info("into right tag to collect text")
			d:= getChildren(cs[9])
			dd:= getChildren(d[1])
			//ddd:= getChildren(dd[1])
			log.Info("3) ", dd[0].Data)
		}
	}
        return nil
}

type Item struct {
        //Ref, Time, Title string
	Title string
}


func downloadNews() []*Item {
        log.Info("sending request to ru.tradingview.com")
        if response, err := http.Get("https://ru.tradingview.com"); err != nil {
                log.Error("request to ru.tradingview.com failed", "error", err)
        } else {
                defer response.Body.Close()
                status := response.StatusCode
                log.Info("got response from ru.tradingview.com", "status", status)
                if status == http.StatusOK {
                        if doc, err := html.Parse(response.Body); err != nil {
                                log.Error("invalid HTML from ru.tradingview.com", "error", err)
                        } else {
                                log.Info("HTML from ru.tradingview.com parsed successfully")
                                itms := search(doc)
				for i:=0; i<len(itms); i++{
					log.Info(itms[i].Title+" ")
				}
				return search(doc)
                        }
                }
        }
        return nil
}

func search(node *html.Node) []*Item {
      //  count := 0
      //  here:
        if isDiv(node, "tv-card-container__ideas") {
		log.Info("into div of items")
                var items []*Item
                for c := node.FirstChild; c != nil; c = c.NextSibling {
                       // if isDiv(c, "tv-feed__item js-cb-item js-feed__item--inited"){
			//      log.Info("lol")
                        //      return nil
                       // }

                        if isDiv(c, "tv-feed__item js_cb_class tv-feed-layout__card-item") {
//                                log.Info("into item")
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
