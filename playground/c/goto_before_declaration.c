#include <stdio.h>

int main(void){
int count = 0;
start_declare:;
int us = 0;

printf("%d\n",us);//no undefined behavior
++count;
++us;
if(count==5) return 0;
goto start_declare;

}


