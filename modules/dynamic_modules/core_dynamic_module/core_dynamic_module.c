
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   mathic.h 
 * Author: thecarisma
 *
 * Created on Febuary 7, 2018, 3:23 AM
 */

#include "../../../simple/includes/simple.h"
#include "core_dynamic_module.h"

#ifdef _WIN32
	#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
	/* Error and Warn */
    register_block("__throw",error_throw);
    /* Conversion */
    register_block("stringToCHex",conversion_string_to_chex);
    register_block("stringToList",conversion_string_to_list);
}

void error_stack_trace(void *pointer)
{
	String *string  ;
	pString = simple_string_new_gc(((VM *) pointer)->sState,"");
	simple_string_add_gc(((VM *) pointer)->sState,string,"\\*.*");
	int x,lBlockCall,is_last_block  ;
	List *list  ;
	const char *cFile  ;
	VM *vm = ((VM *) pointer);
	/* Print the Error Message */
	printf( "\nLine %d -> %s \n",vm->nLineNumber,SIMPLE_API_GETSTRING(1) ) ;
	/* Print Calling Information */
	lBlockCall = 0 ; is_last_block = 1 ;
	for ( x = simple_list_getsize(vm->pBlockCallList) ; x >= 1 ; x-- ) {
		list = simple_list_getlist(vm->pBlockCallList,x);
		/*
		**  If we have ICO_LoadBlock but not ICO_CALL then we need to pass 
		**  ICO_LOADBLOCK is executed, but still ICO_CALL is not executed! 
		*/
		if ( simple_list_getsize(list) < SIMPLE_BLOCKCL_CALLERPC ) {
			continue ;
		}
		if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_SCRIPT ) {
			/*
			**  Prepare Message 
			**  In 
			*/
			if (is_last_block == 1) { printf("\tat "); is_last_block = 0; } else { printf("at "); }
			/* Method or Block */
			/*if ( simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK) ) {
				printf( "method " ) ;
			}
			else {
				printf( "block " ) ;
			}*/
			/* Block Name */
			printf( "%s",simple_list_getstring(list,SIMPLE_BLOCKCL_NAME) ) ;
			/* Adding () */
			printf( "() in file " ) ;
			/* File Name */
			if ( lBlockCall == 1 ) {
				cFile = (const char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_NEWFILENAME) ;
			}
			else {
				if ( vm->nInClassRegion ) {
					cFile = vm->cFileNameInClassRegion ;
				}
				else {
					cFile = vm->file_name ;
				}
			}
			printf( "%s",file_real_name(cFile) ) ;
			/* Called From */
			printf( "\n\tat line %d ",simple_list_getint(list,SIMPLE_BLOCKCL_LINENUMBER) ) ;
			lBlockCall = 1 ;
		}
		else {
			//printf( "\tin %s ",file_real_name(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME)) ) ;
		}
	}
	if ( lBlockCall ) {
		printf( "in file %s ",file_real_name(simple_list_getstring(vm->sState->files_list,1) )) ;
	}
	else {
		if ( vm->nInClassRegion ) {
			cFile = vm->cFileNameInClassRegion ;
		}
		else {
			cFile = file_real_name(vm->file_name) ;
		}
		printf( "\tin file %s ",cFile ) ;
	}
}

void error_throw(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		simple_vm_showerrormessage(((VM *) pointer),SIMPLE_API_GETSTRING(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void conversion_string_to_chex ( void *pointer )
{
	char str[3]  ;
	unsigned char *cString  ;
	int x,nMax  ;
	char *cString2  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cString = (unsigned char *) SIMPLE_API_GETSTRING(1) ;
		nMax = SIMPLE_API_GETSTRINGSIZE(1) ;
		cString2 = (char *) simple_state_malloc(((VM *) pointer)->sState,nMax*5);
		if ( cString2 == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		for ( x = 1 ; x <= nMax ; x++ ) {
			sprintf( str , "%x" , (unsigned int) cString[x-1] ) ;
			/* Separator */
			cString2[(x-1)*5] = ',' ;
			cString2[(x-1)*5+1] = '0' ;
			cString2[(x-1)*5+2] = 'x' ;
			cString2[(x-1)*5+3] = str[0] ;
			if ( str[1] != '\0' ) {
				cString2[((x-1)*5)+4] = str[1] ;
			} else {
				cString2[((x-1)*5)+4] = ' ' ;
			}
		}
		/* Pass the first letter to avoid the first comma */
		cString2++ ;
		SIMPLE_API_RETSTRING2(cString2,nMax*5-1);
		/* When we call free() we use the original pointer */
		cString2-- ;
		simple_state_free(((VM *) pointer)->sState,cString2);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void conversion_string_to_list ( void *pointer )
{
	char *str  ;
	int x,size,start  ;
	List *list  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		str = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		start = 0 ;
		list = SIMPLE_API_NEWLIST ;
		for ( x = 0 ; x < size ; x++ ) {
			if ( str[x] == '\n' ) {
				if ( x > start ) {
					if ( str[x-1] == '\r' ) {
						simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,x-start-1);
					}
					else {
						simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,x-start);
					}
				} else {
					simple_list_addstring_gc(((VM *) pointer)->sState,list,"");
				}
				start = x+1 ;
			}
		}
		if ( size > start ) {
			simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,size-start);
		}
		SIMPLE_API_RETLIST(list);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

