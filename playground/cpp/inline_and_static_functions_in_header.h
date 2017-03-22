#pragma once

#include <stdio.h>



struct st{};

template<int> int tf();
template<> inline int tf<1>() {return 2;}//doesn't compile without inline

template<class T>
void fn(void){
	T o;
	printf("%p\n",(void *)&o);
}

static int g1=1;

inline void printit(void){
	static int s1=1;
	++g1;
	++s1;
	printf("%d\n",s1);
	printf("%d\n",g1);//undefined behavior! prints differently for -O0 and -O3.
}

static int g2=1;
static inline void printit2(void){
	static int s2=1;
	++g2;
	++s2;
	printf("%d\n",s2);
	printf("%d\n",g2);
}

static int g3=1;
static void printit3(void){
	static int s3=1;
	++g3;
	++s3;
	printf("%d\n",s3);
	printf("%d\n",g3);
}
