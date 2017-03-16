#include<stdio.h>

int main(void){
puts("1");
goto yy;//this doesn't compile in c++

{
const char *cc="cc";

{
yy:
puts("in");
}

}

while(0){
mm:
puts("mm");
}

}


