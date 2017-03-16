#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main(void){
	//this doesn't work
	//{
	//	unsigned  x = 12;
	//}
	//{
	//	unsigned  x;
	//	printf("%"PRIu32"\n",x);//UB
	//}

	//this works! without curly brackets, the memory usage is much higher!!
	{char x1[148576];}
	{char x2[148576];}
	{char x3[148576];}
	{char x4[148576];}
	{char x5[148576];}
	{char x6[148576];}
	{char x7[148576];}
	{char x8[148576];}
	{char x9[148576];}
	{char x0[148576];}
	{char x11[148576];}//you also try using a 10x bigger value, stack overflows when you don't have curly brackets, yet it works fine when you have curly brackets

;getchar();

}

