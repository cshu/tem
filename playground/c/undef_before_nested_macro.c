#include<stdio.h>
#define CONSTV "show me"
#define PUTSC puts(CONSTV)
#undef CONSTV
int main(void){
	PUTSC;//this doesn't compile!
}


