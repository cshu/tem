#define NO_NEED_TO_AVERT_RACES

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "cpprs.h"
#include "portable_rt_platform.h"

#if INT_MAX > BUFFER_LEN_FOR_C_SYSTEM_FUNCTION_SAFE
#define COMMANDBUF_LEN BUFFER_LEN_FOR_C_SYSTEM_FUNCTION_SAFE
#else
#define COMMANDBUF_LEN INT_MAX//unlikely?
#endif

static char commandbuf[COMMANDBUF_LEN];


int main (int argc, char **argv){
	PUTS_DATE_TIME_STDC_VERSION_CPLUSPLUSs
#define CONFIG_FILENM argv[1]
	if(argc!=2){
		puts("Need to specify config file"); return RETVALFAILURE;
	}
	//start of loading config (a `separated by LF` text file, each 2 lines are a url for search, as first_line+query+second_line)
	char *configmem;
	size_t configmemlen;
	READ_WHOLE_FILEu(readConfig_,configmem,configmemlen,CONFIG_FILENM,{
		puts("config file failed"); return RETVALFAILURE;
	},{
		puts("config file is empty"); return RETVALFAILURE;
	},)
	if(configmem[configmemlen-1]!='\n')
		{ puts("config file doesn't end with lf, loading failed"); goto start_of_fail;}
	{
		int oddnumoflf=0;
		size_t maxlenof2lines=0;
		for(size_t i=0,mark=0;i<configmemlen;i++) {
			if(configmem[i]=='\n'){
				if(oddnumoflf){
					if(i-mark>maxlenof2lines)
						maxlenof2lines=i-mark;
					mark = i+1;
				}
				oddnumoflf=!oddnumoflf;
			}
			else if(configmem[i]==0){puts("nul char found in config file, loading failed"); goto start_of_fail;}
		}
		if(oddnumoflf){ puts("odd number of lf found in config file, loading failed"); goto start_of_fail;}
		if(COMMANDBUF_LEN<=maxlenof2lines){ puts("buffer is not enough for any queries with criteria"); goto start_of_fail;}

		for(;;){
			ptrdiff_t diffbuf = (char *)memchr(configmem,'\n',configmemlen)-configmem;
			MEMCPY_IF_LEN(commandbuf,configmem,diffbuf);
			time_t timebuf = time(NULL);
			if(!fgets(commandbuf+diffbuf,COMMANDBUF_LEN-diffbuf,stdin)) {puts("EOF encountered or error occurred."); goto start_of_fail;}
			if(difftime(time(NULL),timebuf)<2.0){ puts("inputting too fast. input ignored."); continue;}
			char *cbuf = strchr(commandbuf+diffbuf,'\n');
			if(!cbuf){puts("cannot read to the end of inputted line, maybe buffer is not enough"); while(getchar()!='\n'); continue;}
			if(cbuf==commandbuf+diffbuf) {puts("exiting"); free(configmem); return RETVALSUCCESS;}
			if((uintmax_t)COMMANDBUF_LEN-(uintmax_t)(cbuf-commandbuf-diffbuf)<(uintmax_t)maxlenof2lines){puts("buffer is not enough for this query"); continue;}
			ptrdiff_t cfgoff = diffbuf+1;
			start_search:;
			ptrdiff_t linelen = (char *)MEMCHR_FROM_OFFSET(configmem,'\n',configmemlen,cfgoff) -configmem-cfgoff;
			MEMCPY_IF_LEN(cbuf,configmem+cfgoff,linelen);
			cbuf[linelen]=0;
			system(commandbuf);
			cfgoff +=linelen+1;
			if((uintmax_t)cfgoff==configmemlen) continue;
			linelen = (char *)MEMCHR_FROM_OFFSET(configmem,'\n',configmemlen,cfgoff) -configmem-cfgoff;
			memmove(commandbuf+linelen,commandbuf+diffbuf,cbuf-commandbuf-diffbuf);
			cbuf += linelen-diffbuf; diffbuf = linelen;
			MEMCPY_IF_LEN(commandbuf,configmem+cfgoff,linelen);
			cfgoff +=linelen+1;
			goto start_search;
			//linelen = (char *)MEMCHR_FROM_OFFSET(configmem,'\n',configmemlen,cfgoff) -configmem-cfgoff;
			//MEMCPY_IF_LEN(cbuf,configmem+cfgoff,linelen);
			//cbuf[linelen] = 0;
			//system(commandbuf);
			//cfgoff +=linelen+1;
		}
	}

	start_of_fail:
	free(configmem);
	return RETVALFAILURE;

}

