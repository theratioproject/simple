
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
	char *str  ;
	int size  ;
	/* Note : nSize is (Allocation Size - 1) */
} String ;
/* Blocks */

SIMPLE_API String * simple_string_new_gc ( void *pState,const char *str ) ;

SIMPLE_API String * simple_string_new2_gc ( void *pState,const char *str,int str_size ) ;

SIMPLE_API String * simple_string_delete_gc ( void *pState,String *string ) ;

SIMPLE_API int simple_string_size ( String *string ) ;

SIMPLE_API void simple_string_set_gc ( void *pState,String *string,const char *str ) ;

SIMPLE_API void simple_string_set2_gc ( void *pState,String *string,const char *str,int str_size ) ;

SIMPLE_API void simple_string_add_gc ( void *pState,String *string,const char *str ) ;

SIMPLE_API void simple_string_add2_gc ( void *pState,String *string,const char *str,int str_size ) ;

SIMPLE_API void simple_string_print ( String *string ) ;

SIMPLE_API void simple_string_setfromint_gc ( void *pState,String *string,int x ) ;

SIMPLE_API char * simple_string_lower ( char *cStr ) ;

SIMPLE_API char * simple_string_upper ( char *cStr ) ;

SIMPLE_API char * simple_string_lower2 ( char *cStr,int str_size ) ;

SIMPLE_API char * simple_string_upper2 ( char *cStr,int str_size ) ;

SIMPLE_API char * simple_string_find_gc ( void *pState,char *string_one,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2_gc ( void *pState,char *string_one,int str_size1,char *cStr2,int str_size2 ) ;

SIMPLE_API char * simple_string_find3_gc ( void *pState,char *string_one,int str_size1,char *cStr2,int str_size2 ) ;

void simple_string_test ( void ) ;
/* Macro */
#define simple_string_tolower(x) simple_string_lower(x->str)
#define simple_string_toupper(x) simple_string_upper(x->str)
#define simple_string_get(x) (x->str)
/* Blocks without state pointer */

SIMPLE_API String * simple_string_new2 ( const char *str,int str_size ) ;

SIMPLE_API String * simple_string_new ( const char *str ) ;

SIMPLE_API void simple_string_add ( String *string,const char *str ) ;

SIMPLE_API void simple_string_add2 ( String *string,const char *str,int str_size ) ;

SIMPLE_API void simple_string_set ( String *string,const char *str ) ;

SIMPLE_API void simple_string_set2 ( String *string,const char *str,int str_size ) ;

SIMPLE_API char * simple_string_find ( char *string_one,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2 ( char *string_one,int str_size1,char *cStr2,int str_size2 ) ;

SIMPLE_API char * simple_string_find3 ( char *string_one,int str_size1,char *cStr2,int str_size2 ) ;

SIMPLE_API String * simple_string_delete ( String *string ) ;

SIMPLE_API void simple_string_setfromint ( String *string,int x ) ;
#endif
