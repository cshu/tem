#include <inttypes.h>
#include <stdio.h>

int main(void){
	unsigned u = 0;
	signed s = -1;
	long long llbuf = u+s;
	unsigned long long ullbuf = u+s;
	printf("%lld\n",llbuf);
	printf("%llu\n",ullbuf);
}

