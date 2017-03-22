


#include <type_traits>
#include <cassert>
#include <iostream>

typedef int32_t i32ty;

void oio(int cc){//might not compile
	std::cout<<'c';
}
void oio(int32_t cc){
	std::cout<<'u';
}
void oio(i32ty cc){//doesn't compile
	std::cout<<'u';
}

void oio(char16_t cc){//this compiles
	std::cout<<'c';
}
void oio(uint_least16_t cc){
	std::cout<<'u';
}

int main(void){
	std::cout<<std::is_same<char16_t,uint_least16_t>::value;
	oio((char16_t)12);
	oio((uint_least16_t)12);
}
