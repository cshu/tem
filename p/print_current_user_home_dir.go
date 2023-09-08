package main

import(
	"os/user"
	"log"
)

func main() {
	usr, err := user.Current()
	if err!=nil{
		log.Fatalln(err)
	}
	fmt.Println(usr.HomeDir)
}

