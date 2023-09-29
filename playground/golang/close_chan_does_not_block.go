package main

//note close does not block. Unlike normal write. Normal write can block till another thread reads

import "time"


func main(){
	chTest := make(chan bool)
	go func(chToClose chan bool){
		close(chToClose)
		println(`closed`)
	}(chTest)
	time.Sleep(5 * time.Second)
	println(`begin read`)
	<-chTest
	println(`end read`)
}
