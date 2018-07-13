
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
    register_block("__stack_trace",error_stack_trace);
    register_block("__warn",error_warn);
    /* Conversion */
    register_block("stringToCHex",conversion_string_to_chex);
    register_block("stringToList",conversion_string_to_list);
}

SIMPLE_API void error_warn(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if (((VM *) pointer)->sState->nWarning) 
			printf("%s",SIMPLE_API_GETSTRING(1));
		return;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void error_stack_trace(void *pointer)
{
	String *string,*string2;
	List *list, *list2;
	int x,lBlockCall,is_last_block  ;
	const char *cFile  ;
	VM *vm;	
	list2 = SIMPLE_API_NEWLIST ;
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	} else {
		vm = ((VM *) pointer);
		/* Print the Error Message */
		string = simple_string_new_gc(((VM *) pointer)->sState,"at line ");
			string2 = simple_string_new_gc(((VM *) pointer)->sState,"");
			simple_string_setfromint_gc(((VM *) pointer)->sState,string2,vm->nLineNumber);
		simple_string_add_gc(((VM *) pointer)->sState,string,string2->str);
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
				simple_string_add_gc(((VM *) pointer)->sState,string," at ");
				simple_string_add_gc(((VM *) pointer)->sState,string,simple_list_getstring(list,SIMPLE_BLOCKCL_NAME));
				/* Adding () */
				simple_string_add_gc(((VM *) pointer)->sState,string,"() in file ");
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
				simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(cFile));
				simple_list_addstring_gc(vm,list2,string->str);
				/* Called From */
				string = simple_string_new_gc(((VM *) pointer)->sState,"at line ");
					string2 = simple_string_new_gc(((VM *) pointer)->sState,"");
					simple_string_setfromint_gc(((VM *) pointer)->sState,string2,simple_list_getint(list,SIMPLE_BLOCKCL_LINENUMBER));
				simple_string_add_gc(((VM *) pointer)->sState,string,string2->str);
				is_last_block = 0; 
				lBlockCall = 1 ;
			}
			else {
				simple_string_add_gc(((VM *) pointer)->sState,string," in ");
				simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME)));
			}
		}
		if ( lBlockCall ) {
			simple_string_add_gc(((VM *) pointer)->sState,string," in file ");
			simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(simple_list_getstring(vm->sState->files_list,1)));
		} else {
			if ( vm->nInClassRegion ) {
				cFile = vm->cFileNameInClassRegion ;
			}
			else {
				cFile = file_real_name(vm->file_name) ;
			}
			simple_string_add_gc(((VM *) pointer)->sState,string," in file ");
			simple_string_add_gc(((VM *) pointer)->sState,string,cFile);
		}
		simple_list_addstring_gc(vm,list2,string->str);
		simple_string_delete_gc(((VM *) pointer)->sState,string);
		simple_string_delete_gc(((VM *) pointer)->sState,string2);
		SIMPLE_API_RETLIST(list2);
		return;
	}
}

SIMPLE_API void error_throw(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if (((VM *) pointer)->sState->skip_error == 0) 
			((VM *) pointer)->sState->skip_error = 1;
		SIMPLE_API_ERROR(SIMPLE_API_GETSTRING(1));
		if (((VM *) pointer)->sState->skip_error == 1) 
			((VM *) pointer)->sState->skip_error = 0;
		return;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void conversion_string_to_chex ( void *pointer )
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

SIMPLE_API void conversion_string_to_list ( void *pointer )
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

