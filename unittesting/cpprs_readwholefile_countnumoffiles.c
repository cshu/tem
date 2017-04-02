#define NO_NEED_TO_AVERT_RACES



#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <windows.h>
#include <dirent.h>
#include "cpprs.h"
#include "cpprs_stdout_as_log.h"


char defArr[0x10000];
int main(void){
	char *defBuf;
	size_t fileLength;
	unsigned unsignedBuf;

	#define utf8filenm "\xE5\x8D\x80"//chinese character, code point x5340 / 21312
	READ_WHOLE_FILEu(readwholefile_,defBuf,fileLength,utf8filenm ".txt",{
		LOG_ERRORs
		return 1;
	},{
		LOG_ERRORs//empty file
		return 1;
	},{
		LOG_ERRORs
		return 1;
	},)
	assert(!memcmp(defBuf,"123\r\n",5));
	free(defBuf);

	COUNT_NUM_OF_FILESu(countNumOfFiles_,utf8filenm,unsignedBuf,{
		LOG_ERRORs
		return 1;
	},)
	assert(unsignedBuf==1);

	puts("ALL DONE");
}
