#include<stdlib.h>
int main(void){
char *cc = (void *)NULL;//compiles in C, but not in C++
char *ccc = NULL;//this compiles in both C and C++, it's okay to use NULL (instead of nullptr), but be careful when you use it as overloaded function param (NULL is int in C++? so not a pointer type?)
}
