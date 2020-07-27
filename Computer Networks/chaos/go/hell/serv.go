package main

import (
    "flag"
    "log"

    "github.com/goftp/file-driver"
    "github.com/goftp/server"
)

func main() {
    var (
        root = flag.String("root", "/users/anemone", "Root directory to serve")
        user = flag.String("user", "Anemone", "Username for login")
        pass = flag.String("pass", "123456", "Password for login")
        port = flag.Int("port", 2721, "Port")
        host = flag.String("host", "localhost", "Port")
    )
    flag.Parse()
    if *root == "" {
        log.Fatalf("Please set a root to serve with -root")
    }

    factory := &filedriver.FileDriverFactory{
        RootPath: *root,
        Perm:     server.NewSimplePerm("user", "group"),
    }

    opts := &server.ServerOpts{
        Factory:  factory,
        Port:     *port,
        Hostname: *host,
        Auth:     &server.SimpleAuth{Name: *user, Password: *pass},
    }

    log.Printf("Starting ftp server on %v:%v", opts.Hostname, opts.Port)
    log.Printf("Username %v, Password %v", *user, *pass)
    server := server.NewServer(opts)
    err := server.ListenAndServe()
    if err != nil {
        log.Fatal("Error starting server:", err)
    }
}