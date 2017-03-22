//1. it generate code, e.g. header files
//2. it checks code file to ensure it doesn't contains unexpected code
//3. it checks code file to ensure it matches generated code exactly, so you don't need to overwrite it with generated code
#define NEWLINE_END_CHAR_HEX 0a//\n
#define NEWLINE_END_CHAR_STR HEX_AS_LITERAL(NEWLINE_END_CHAR_HEX)
#define NEWLINE_END_CHAR_INT HEX_AS_INTEGER(NEWLINE_END_CHAR_HEX)

#define NO_NEED_TO_AVERT_RACES

//remove
#define __STDC_FORMAT_MACROS
#include <stdint.h>
#include <inttypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "cpprs.h"
#include "cpprs_stdout_as_log.h"
#include "code_generator_n_validator.h"
int main(int argc, char **argv){
if(argc!=2){LOG_ERROR_LITERALs("argv not right") return 1;}
char *codeStr;
size_t codeLen;
#define L_FILENAMESTR (argv[1])
READ_WHOLE_FILE_WITH_NUL_APPENDEDu(readCode_,codeStr,codeLen,L_FILENAMESTR,{LOG_ERROR_LITERALs("io failed");return 1;},{LOG_ERROR_LITERALs("empty file");return 1;},)
struct pvoid_with_pend_n_capacity generated;
SET_PEND_MALLOC_PVOID_WITH_PEND_CAs(generated.,codeLen,{LOG_ERROR_LITERALs("malloc failed") goto fail_free_codeStr;},)
#define LITERAL_APPENDED_TO_FILENAME "_literal2hex"
{
	char *newFilenameStr = IMPLICIT_STATIC_CAST(char *,malloc(strlen(L_FILENAMESTR)+sizeof LITERAL_APPENDED_TO_FILENAME));
	if(NULL==newFilenameStr){LOG_ERROR_LITERALs("malloc failed") goto fail_free_generatedStr;}
	EXPAND_TO_FUNC_N_ARGS(MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDEDu,cpyHead_,generated.,LITERAL_COMMA_LEN(LITERAL_THIS_IS_A_GENERATED_FILE),AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("malloc failed") goto fail_free;},)
	{
		char *savePoint = IMPLICIT_STATIC_CAST(char *,generated.pend);
#	define BEGINNINGOFLINE "#define"
		char *pStr = codeStr;
		goto start_search;
		for(;;){
			generated.pend=savePoint;
			start_search:;
			pStr = strstr(pStr,BEGINNINGOFLINE);
			if(NULL==pStr)break;
			if(pStr!=codeStr && pStr[-1]!=NEWLINE_END_CHAR_INT){
				pStr+=sizeof BEGINNINGOFLINE-1;
				goto start_search;
			}
			pStr+=sizeof BEGINNINGOFLINE-1;
			if(!isblank(*pStr)) goto start_search;//just continue, not {pStr++; continue;}, bc *pStr can be NUL, the terminator.
			pStr++;
			pStr+=strspn(pStr," \t");
			size_t lenOfId = strspn(pStr,LITERAL_0to9_AtoZ_atoz "_");
			if(!lenOfId) goto start_search;
#		define LITERAL_APPENDED_TO_ID "_LITERAL2HEX \""
			EXPAND_TO_FUNC_N_ARGS(MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDEDu,cpyDefine_,generated.,LITERAL_COMMA_LEN("#define "),AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("mem alloc failed") goto fail_free;},)
			MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDED_N_SET_SOURCE_PTRu(cpyIdentifier_,generated.,pStr,lenOfId,AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("mem alloc failed") goto fail_free;},)
			EXPAND_TO_FUNC_N_ARGS(MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDEDu,cpySuffix_,generated.,LITERAL_COMMA_LEN(LITERAL_APPENDED_TO_ID),AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("mem alloc failed") goto fail_free;},)
			pStr+=strspn(pStr," \t");
			if(*pStr!='\"') continue;
			pStr++;
			for(;;){
				if(*pStr!='\\'){
					if(*pStr!='\"') break;
					EXPAND_TO_FUNC_N_ARGS(MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDEDu,cpyLF_,generated.,LITERAL_COMMA_LEN("\"\n"),AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("mem alloc failed") goto fail_free;},)
					savePoint=IMPLICIT_STATIC_CAST(char *,generated.pend); pStr++; goto start_search;
				}
				pStr++;
				if(*pStr!='x') break;
				pStr++;
				if(!isxdigit(pStr[0]) || !isxdigit(pStr[1])) break;
				MEMCPY_TO_THE_END_OF_PVOID_WITH_PEND_CA_N_REALLOC_IF_NEEDED_N_SET_SOURCE_PTRu(cpyByt_,generated.,pStr,2,AT_LEAST_ONE_N_HALF_OF__B_PLUS_C__AS_MULTIPLE_OF_D,sizeof(char),{LOG_ERROR_LITERALs("mem alloc failed") goto fail_free;},)//todo you might want to use tolower/toupper for only one case(lower/upper), though it's probably not important bc once your .h file is generated, all programs use the same .h file so case doesn't matter
			}
		}

		free(codeStr);
		{
			char *pDot = strrchr(L_FILENAMESTR,'.');
			if(NULL==pDot){
				strcpy(newFilenameStr,L_FILENAMESTR);
				strcat(newFilenameStr,LITERAL_APPENDED_TO_FILENAME);
			}else{
				memcpy(newFilenameStr,L_FILENAMESTR,pDot-L_FILENAMESTR);
				memcpy(newFilenameStr+(pDot-L_FILENAMESTR),LITERAL_COMMA_LEN(LITERAL_APPENDED_TO_FILENAME));
				strcpy(newFilenameStr+(pDot-L_FILENAMESTR)+(sizeof LITERAL_APPENDED_TO_FILENAME-1),pDot);
			}
		}
		WRITE_WHOLE_FILE_IF_FILE_NOT_FOUND_OR_MEMCMPu(write_,newFilenameStr,generated.obj,((size_t)(savePoint-(char *)generated.obj)),{LOG_ERROR_LITERALs("checking and writing file failed.") goto fail_free_newFilenameStr_generated;},{puts("Code generated and written.");},{puts("No need to overwrite, generated code exists.");});
	}
	free(newFilenameStr);
	FREE_PVOID_WITH_PEND_CA(generated.);
	return 0;

	fail_free_newFilenameStr_generated:
	free(newFilenameStr);
	FREE_PVOID_WITH_PEND_CA(generated.);
	return 1;

	fail_free:
	free(newFilenameStr);
}
fail_free_generatedStr:
FREE_PVOID_WITH_PEND_CA(generated.);
fail_free_codeStr:
free(codeStr);
return 1;


}
