package main

//first 2 are UTC, the 3rd one (time.Now()) is local time, the 4th one is also local time

import "time"
import "fmt"


func main(){
	var tbuf time.Time
	fmt.Println(tbuf.Hour())
	fmt.Println(tbuf.Zone())
	tbuf = time.Time{}
	fmt.Println(tbuf.Hour())
	fmt.Println(tbuf.Zone())
	tbuf = time.Now()
	fmt.Println(tbuf.Hour())
	fmt.Println(tbuf.Zone())
	tbuf = time.UnixMilli(tbuf.UnixMilli())
	fmt.Println(tbuf.Hour())
	fmt.Println(tbuf.Zone())
}
