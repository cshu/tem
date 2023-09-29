package main

//import "fmt"

type FooImpl struct {
}

func (fi *FooImpl) Fooo() {
	fi.Voo()
}
func (fi *FooImpl) Voo() {
	println(1)
}

type Bar struct {
	FooImpl
}

func (fi *Bar) Voo() {
	println(22)
}

type Bar2 struct {
	FooImpl
}

func (fi *Bar2) Voo() {
	println(33)
}
func main() {
	b1 := new(Bar)
	b1.Fooo()//this prints 1
}

