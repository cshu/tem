package main

import (
	"os"
)
func main(){
	for i:=len(os.Args)-1;i>=0;i--{
		os.Stdout.WriteString(os.Args[i])
		os.Stdout.WriteString("\n\n")
	}
}
