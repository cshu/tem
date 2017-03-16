#include <stdio.h>



int main(void){
#define COMMA ,
#define conc3(x,y,z) puts("==============1=============");x  puts("==============2=============");y  puts("==============3=============");z puts("==============4=============");
#define xconc3(c) conc3(c)
#define m(r,l1,l2,l3)\
puts(r);puts("blk 1");\
l1\
,\
puts(r);puts("blk 2");\
l2\
,\
puts(r);puts("blk 3");\
l3
#define xm(x,y) m(x,y)
	xconc3(xm("a",xm("b",xm("c",COMMA COMMA))))
}
//it works!

