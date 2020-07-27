package main

import (
    "fmt" // пакет для форматированного ввода вывода
    "net/http" // пакет для поддержки HTTP протокола
    "strings" // пакет для работы с  UTF-8 строками
    "log" // пакет для логирования
    "github.com/RealJK/rss-parser-go"
    //"sort"
    "html/template"
)

type Result struct {
            Title string
            Message string
            Date rss.RSSDate
        }

func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {
    r.ParseForm() //args analysis 
    fmt.Println(r.Form)  // entering information about form on server's side
    fmt.Println("path", r.URL.Path)
    fmt.Println("scheme", r.URL.Scheme)
    fmt.Println(r.Form["url_long"])
    for k, v := range r.Form {
        fmt.Println("key:", k)
        fmt.Println("val:", strings.Join(v, ""))
    }
    rssObject, _ := rss.ParseRSS("http://www.polit.ru/rss/index.xml")
    mas := rssObject.Channel.Items
    rssObject, _ = rss.ParseRSS("https://lenta.ru/rss/news")
    mas = append(mas, rssObject.Channel.Items...)
    rssObject, _ = rss.ParseRSS("http://rusvesna.su/rss.xml")
    mas = append(mas, rssObject.Channel.Items...)
    //sort.SliceStable(mas, func(i, j int) bool {return mas[i].PubDate < mas[j].PubDate})

    for v := range mas {
        item := mas[v]
        data := Result{
            Title: item.Title,
            Message: item.Description,
            Date: item.PubDate,
        }

        tmpl, _ := template.ParseFiles("1.http")
    tmpl.Execute(w, data)
    }

}

func main() {
    http.HandleFunc("/", HomeRouterHandler) // set router
    err := http.ListenAndServe(":9002", nil) // listening port
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
