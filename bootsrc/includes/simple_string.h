
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: thecarisma
 *
 * Created on July 10, 2017, 1:10 PM
 */


#ifndef simple_string_h
#define simple_string_h
/* Data */
typedef struct String {
	char *cStr  ;
	int nSize  ;
	/* Note : nSize is (Allocation Size - 1) */
} String ;
/* Functions */

SIMPLE_API String * simple_string_new_gc ( void *pState,const char *str ) ;

SIMPLE_API String * simple_string_new2_gc ( void *pState,const char *str,int nStrSize ) ;

SIMPLE_API String * simple_string_delete_gc ( void *pState,String *pString ) ;

SIMPLE_API int simple_string_size ( String *pString ) ;

SIMPLE_API void simple_string_set_gc ( void *pState,String *pString,const char *str ) ;

SIMPLE_API void simple_string_set2_gc ( void *pState,String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_add_gc ( void *pState,String *pString,const char *str ) ;

SIMPLE_API void simple_string_add2_gc ( void *pState,String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_print ( String *pString ) ;

SIMPLE_API void simple_string_setfromint_gc ( void *pState,String *pString,int x ) ;

SIMPLE_API char * simple_string_lower ( char *cStr ) ;

SIMPLE_API char * simple_string_upper ( char *cStr ) ;

SIMPLE_API char * simple_string_lower2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_string_upper2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_string_find_gc ( void *pState,char *string_one,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2_gc ( void *pState,char *string_one,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_string_find3_gc ( void *pState,char *string_one,int nStrSize1,char *cStr2,int nStrSize2 ) ;

void simple_string_test ( void ) ;
/* Macro */
#define simple_string_tolower(x) simple_string_lower(x->cStr)
#define simple_string_toupper(x) simple_string_upper(x->cStr)
#define simple_string_get(x) (x->cStr)
/* Functions without state pointer */

SIMPLE_API String * simple_string_new2 ( const char *str,int nStrSize ) ;

SIMPLE_API String * simple_string_new ( const char *str ) ;

SIMPLE_API void simple_string_add ( String *pString,const char *str ) ;

SIMPLE_API void simple_string_add2 ( String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_set ( String *pString,const char *str ) ;

SIMPLE_API void simple_string_set2 ( String *pString,const char *str,int nStrSize ) ;

SIMPLE_API char * simple_string_find ( char *string_one,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2 ( char *string_one,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_string_find3 ( char *string_one,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API String * simple_string_delete ( String *pString ) ;

SIMPLE_API void simple_string_setfromint ( String *pString,int x ) ;
#endif
