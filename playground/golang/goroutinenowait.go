package main

import (
	"time"
)

func main() {
	go func(){
		time.Sleep(5 * time.Second)
	}()
	//note intuitively "When that function invocation returns, the program exits. It does not wait for other (non-main) goroutines to complete." (though it's common in real world, C++ does not clearly specify the behavior when main returns?)
	time.Sleep(1 * time.Second)
}

