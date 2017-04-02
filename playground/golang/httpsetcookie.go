package main

import (
    _"fmt"
    "net/http"
)

func handler(w http.ResponseWriter, r *http.Request) {
    //fmt.Fprintf(w, "Hi there, I love %s!", r.URL.Path[1:])
    w.Header().Set("Access-Control-Allow-Origin","http://stackoverflow.com");
    w.Header().Set("Access-Control-Allow-Credentials","true");
    w.Header().Set("Access-Control-Allow-Headers","Content-Type");
    w.Header().Set("Set-Cookie","PGID=q4itgrppqn4crgc1uu5o0f8hb6; expires=Sun, 03-Jan-2027 08:00:29 GMT; Max-Age=315360000; path=/; HttpOnly");
    w.WriteHeader(200)
}

func main() {
    http.HandleFunc("/", handler)
    //fmt.Println("rdy")
    http.ListenAndServe(":8080", nil)
    //fmt.Println("done")
}
