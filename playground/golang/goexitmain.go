package main

import (
	"runtime"
	"time"
)

func main(){
	defer func(){println("you see me first")}()
	go func(){
		time.Sleep(5 * time.Second)
		println("you see me later")
	}()
	time.Sleep(1 * time.Second)
	runtime.Goexit()//at last a fatal error (Goexit is usually intended for non-main goroutines?)
	println("you cannot see me")
}
