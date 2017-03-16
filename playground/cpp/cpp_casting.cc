#include <stdio.h>

int main(void){
	void *pvoidv = NULL;
	const unsigned cunsignedv = 0;
	unsigned unsignedv = 0;
	const unsigned *pcunsignedv = NULL;
	unsigned *punsignedv = NULL;
	unsigned char *pucv = NULL;
	unsigned char ucv = 0;
	float flv = 0;
	intptr_t inttv=0;
	//unsignedv = const_cast<unsigned>(cunsignedv);		//doesn't compile!
	//punsignedv = const_cast<unsigned *>(pcunsignedv);	//compiles!
	//pucv = static_cast<unsigned char *>(punsignedv);	//doesn't compile!
	//pvoidv = static_cast<void *>(punsignedv);		//compiles!
	//punsignedv = static_cast<unsigned *>(pvoidv);		//compiles!
	//ucv = static_cast<unsigned char>(unsignedv);		//compiles!
	//unsignedv = static_cast<unsigned>(ucv);		//compiles!
	//ucv = static_cast<unsigned char>(flv);		//compiles!
	//inttv = static_cast<intptr_t>(pvoidv);		//doesn't compile!
	//inttv = reinterpret_cast<intptr_t>(pvoidv);		//compiles!
	//punsignedv = pvoidv;					//only compiles as c!
	//pucv = reinterpret_cast<unsigned char *>(punsignedv);	//compiles!
}


