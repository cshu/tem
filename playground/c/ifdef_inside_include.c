
#include <stdio.h>

//it works!

int main(void){

#include "ifdef_inside_include_included.h"
#define TWOTWO
#include "ifdef_inside_include_included.h"
#undef TWOTWO
#include "ifdef_inside_include_included.h"
}



