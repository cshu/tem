#include <stdio.h>

double retdoub(void){
	puts("func called");
	return 1.1;
}

int main(void){
	double dd = retdoub();
	size_t xx = sizeof(retdoub());
	size_t yy = sizeof retdoub();
	printf("%u\n",(unsigned)xx);
	printf("%u\n",(unsigned)yy);
}
