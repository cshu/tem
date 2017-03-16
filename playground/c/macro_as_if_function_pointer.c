#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "independent_rt_c_cpp.h"
#include "portable_rt_platform.h"
int main(void){
	struct pvoid_with_size_n_capacity sbuf;
	sbuf.obj = malloc(16);
	memset(sbuf.obj,'\0',16);
	sbuf.si = 16;
	sbuf.cap = 16;
	APPEND_TO_PVOID_WITH_SI_CA_N_REALLOC_IF_NEEDEDs(sbuf.,65,unsigned char *,AT_LEAST_ONE_N_HALF_OF_X_AS_MULTIPLE_OF_Y,{},{
		printf("%" LENGTH_MODIFIER_SIZE_T "u,%" LENGTH_MODIFIER_SIZE_T "u",sbuf.si,sbuf.cap);
		
	})
}


