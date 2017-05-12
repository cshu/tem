package main

import (
	"time"
)

func main() {
	go func(){
		panic(1)//terminates process. btw, "A panic cannot be recovered by a different goroutine"
	}()
	time.Sleep(4 * time.Second)
}

