
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
    register_block("__throw",conversion_string_to_chex);
    /* Conversion */
    register_block("stringToCHex",conversion_string_to_chex);
    register_block("stringToList",conversion_string_to_list);
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

