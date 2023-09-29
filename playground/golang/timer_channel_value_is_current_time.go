package main

//just want to confirm Timer channel really provides the time of "Right Now"

import "time"


func main(){
	testTimer := time.NewTimer(5 * time.Second)
	println(time.Now().Unix())
	timeFromCh := <-testTimer.C
	println(time.Now().Unix())//print the same value (or very close value) as timeFromCh
	println(timeFromCh.Unix())
}
