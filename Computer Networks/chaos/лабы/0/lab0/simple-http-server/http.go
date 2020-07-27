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

        fmt.Fprintf(w,"Title           : %s\n", rssObject.Channel.Title)
        fmt.Fprintf(w,"Generator       : %s\n", rssObject.Channel.Generator)
        fmt.Fprintf(w,"PubDate         : %s\n", rssObject.Channel.PubDate)
        fmt.Fprintf(w,"LastBuildDate   : %s\n", rssObject.Channel.LastBuildDate)
        fmt.Fprintf(w,"Description     : %s\n", rssObject.Channel.Description)

        fmt.Fprintf(w,"Number of Items : %d\n", len(rssObject.Channel.Items))

    for v := range rssObject.Channel.Items {
        item := rssObject.Channel.Items[v]
            fmt.Println()
        fmt.Fprintf(w,"Item Number : %d\n", v)
        fmt.Fprintf(w,"Title       : %s\n", item.Title)
        fmt.Fprintf(w,"Link        : %s\n", item.Link)
        fmt.Fprintf(w,"Description : %s\n", item.Description)
        fmt.Fprintf(w,"Guid        : %s\n", item.Guid.Value)
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
