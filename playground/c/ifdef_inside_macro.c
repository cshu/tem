#include <stdio.h>

//THIS DOESN'T COMPILE! # CHAR CANNOT BE USED INSIDE DEFINE

#define multilinedef \
puts("one");\
#ifdef TWOTWO \
puts("two");\
#endif \
puts("three");




int main(void){
#define TWOTWO
multilinedef

}



