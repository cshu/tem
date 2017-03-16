#include <stdio.h>

int main(void){
#define m(a,b) puts(a);puts(b);
#define xm(c) m(c)
#define ss "aa","bb"
	xm(ss);//it works!
}

