package main

import (
    "fmt" // пакет для форматированного ввода вывода
    "net/http" // пакет для поддержки HTTP протокола
    "strings" // пакет для работы с  UTF-8 строками
    "log" // пакет для логирования
    "github.com/RealJK/rss-parser-go"
)

func HomeRouterHandler(w http.ResponseWriter, r *http.Request) {
    r.ParseForm() //анализ аргументов,
    fmt.Println(r.Form)  // ввод информации о форме на стороне сервера
    fmt.Println("path", r.URL.Path)
    fmt.Println("scheme", r.URL.Scheme)
    fmt.Println(r.Form["url_long"])
    for k, v := range r.Form {
        fmt.Println("key:", k)
        fmt.Println("val:", strings.Join(v, ""))
    }
    rssObject, err := rss.ParseRSS("http://blagnews.ru/rss_vk.xml")
    if err != nil {

        fmt.Fprintf(w,"<div style='text-align:center;' >Title           : %s\n</h1>", rssObject.Channel.Title)
        fmt.Fprintf(w,"<h1>Generator       : %s\n</h1>", rssObject.Channel.Generator)
        fmt.Fprintf(w,"<h1>PubDate         : %s\n</h1>", rssObject.Channel.PubDate)
        fmt.Fprintf(w,"<h1>LastBuildDate   : %s\n</h1>", rssObject.Channel.LastBuildDate)
        fmt.Fprintf(w,"<h1>Description     : %s\n</h1>", rssObject.Channel.Description)

        fmt.Fprintf(w,"<h1>Number of Items : %d\n</h1>", len(rssObject.Channel.Items))

    for v := range rssObject.Channel.Items {
        item := rssObject.Channel.Items[v]
            fmt.Println()
        fmt.Fprintf(w,"<h1>Item Number : %d\n</h1>", v)
        fmt.Fprintf(w,"<h1>Title       : %s\n</h1>", item.Title)
        fmt.Fprintf(w,"<h1>Link        : %s\n</h1>", item.Link)
        fmt.Fprintf(w,"<h1>Description : %s\n</h1>", item.Description)
        fmt.Fprintf(w,"<h1>Guid        : %s\n</h1>", item.Guid.Value)
        }
    }
}

func main() {
    http.HandleFunc("/", HomeRouterHandler) // установим роутер
    err := http.ListenAndServe(":9000", nil) // задаем слушать порт
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
