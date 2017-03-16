#include <stdio.h>

int SomeFunc(){
return 4;
}

int main(void) {    unsigned char *parr;
    if (1){
        size_t length = SomeFunc();
        unsigned char arr[length];
        arr[1]=65;
        parr = arr;
    }
        printf("%d\n",parr[1]);
        printf("%c\n",parr[1]);
        printf("%d\n",parr[1]);
        printf("%c\n",parr[1]);
        printf("%d\n",'A');
        printf("%c\n",'A');
	return 0;
}
