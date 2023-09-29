package main

import (
	"fmt"
	"github.com/google/btree"
)

type TrItem struct {
	Key string
	Obj float64
}

func TrItemLessFunc(x, y *TrItem) bool {
	return x.Key < y.Key
}

func main() {
	tr := btree.NewOrderedG[int](32)
	tr.Delete(99)
	tr.DeleteMax()
	tr.DeleteMin()
	var u int
	u, _ = tr.Get(99)
	println(u)
	println(tr.Len())
	tr2 := btree.NewG[*TrItem](32, TrItemLessFunc)
	_, _ = tr2.ReplaceOrInsert(&TrItem{})
	_, _ = tr2.ReplaceOrInsert(&TrItem{Key: `c`, Obj: 3.3})
	_, _ = tr2.ReplaceOrInsert(&TrItem{Key: `a`, Obj: 1.1})
	_, _ = tr2.ReplaceOrInsert(&TrItem{Key: `d`, Obj: 4.4})
	_, _ = tr2.ReplaceOrInsert(&TrItem{Key: `b`, Obj: 2.2})
	tr2.Ascend(func(item *TrItem) bool {
		fmt.Println(item)
		return true
	})
	println(`-`)
	tr2.Ascend(func(item *TrItem) bool {
		fmt.Println(item)
		return false
	})
	println(`-`)
	tr2.Descend(func(item *TrItem) bool {
		fmt.Println(item)
		return true
	})
	println(`-`)
	tr2.Descend(func(item *TrItem) bool {
		fmt.Println(item)
		return false
	})
	println(`all done`)
}
