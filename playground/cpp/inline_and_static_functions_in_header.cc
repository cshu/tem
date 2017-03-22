#include "inline_and_static_functions_in_header.h"
void seehere(void);
int main(void){
	printit();
	printit2();
	printit3();
	fn<int>();
	seehere();
	puts("done");
}
