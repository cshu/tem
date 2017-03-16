#include <stdio.h>
#define MM(ins) puts("mm begin"); ins puts("mm end");

int main(void){
	MM(MM(MM(puts("inserted");)))//it works!
}



