package main

import (
	"path"
	"path/filepath"
)

func main() {
	println(path.Join("foo", "bar", "hmm"))
	println(filepath.Join("foo", "bar", "hmm"))//using Separator. output can be different!!
}
