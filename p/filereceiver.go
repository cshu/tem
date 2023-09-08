package main

import (
	"io"
	"os"
	"log"
	"net/http"
)

func handlerfunc(w http.ResponseWriter, r *http.Request) {
	f, err := os.OpenFile("received_out.zip", os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0666)
	if err != nil {
		//log.Fatal(err)
		panic(err)
	}
	defer func() {
		if err := f.Close(); err != nil{
			panic(err)
		}
	}()
	if _, err:=io.Copy(f, r.Body); err!=nil{
		panic(err)
	}
	print("File written.");
}

func main() {
	http.HandleFunc("/", handlerfunc)
	log.Fatal(http.ListenAndServe(":8087", nil))//log.fatal is rarely useful, use panic in most cases
}
