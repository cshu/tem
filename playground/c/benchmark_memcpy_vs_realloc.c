#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define si 0x1000000
int main(void){
	clock_t begin, end;
	double time_spent;
	unsigned *pc=NULL;
	//time_t t;
	while(1){
	free(pc);
	pc = malloc(si);
	pc[0]=1;pc[1]=2;pc[2]=3;
	switch(getchar()){
		case 'm':{//obviously faster!!! mingw-w64 on windows server 2008 r2
			begin = clock();
			//t=time(NULL);
			unsigned *ptem = malloc((size_t)si*2);
			if(ptem==NULL) continue;
			memcpy(ptem,pc,3*sizeof(unsigned));
			free(pc);
			pc = ptem;
			break;}
		case 'r':{
			begin = clock();
			//t=time(NULL);
			unsigned *ptem = realloc(pc,(size_t)si*2);
			if(ptem==NULL) continue;
			pc = ptem;
			break;}
		case 'q':
			free(pc);
			return 0;
		default:
			puts("other char got");
			continue;
	}
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n",time_spent);
	}
}

