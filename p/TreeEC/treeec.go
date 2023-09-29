package main

import (
	"fmt"
	"io/fs"
	"os"
	"path/filepath"
	"runtime/debug"
	//rs "golangrs"
)

type MainCtx struct {
	ExitStatusCode int
}

func main() {
	ctx := &MainCtx{}
	defer func() {
		if r := recover(); r != nil {
			fmt.Println(r)
			fmt.Println("DEBUG STACK:\n" + string(debug.Stack())) //this is copy-pasted from rs.LogWithStackIfValueIsNotNil
			ctx.ExitStatusCode = 1
		}
		os.Exit(ctx.ExitStatusCode)
	}()
	var err error
	cmd1 := os.Args[1] //todo check bounds first
	//fmt.Println(os.Args[0])
	//fmt.Println(cmd1)
	err = filepath.WalkDir(cmd1, func(path string, dirent fs.DirEntry, errRelatedToPath error) error {
		//note if cmd1 is ".", then the first `path` is really ".", while other `path` strings do NOT start with "."
		//note it seems path does not contain trailing slash for folders
		if errRelatedToPath != nil {
			fmt.Println(errRelatedToPath)
			ctx.ExitStatusCode = 1
			return fs.SkipAll
		}
		//
		if dirent.IsDir() {
			fmt.Println("d " + path)
		} else {
			fmt.Println("- " + path)
		}
			//fmt.Println("basename " + dirent.Name())
		return nil
	})
	if err != nil {
		fmt.Println(err)
		ctx.ExitStatusCode = 1
	}
}
