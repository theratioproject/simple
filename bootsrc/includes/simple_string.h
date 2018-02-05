
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


#ifndef simple_stsimple_h
#define simple_stsimple_h
/* Data */
typedef struct String {
	char *cStr  ;
	int nSize  ;
	/* Note : nSize is (Allocation Size - 1) */
} String ;
/* Functions */

SIMPLE_API String * simple_stsimple_new_gc ( void *pState,const char *str ) ;

SIMPLE_API String * simple_stsimple_new2_gc ( void *pState,const char *str,int nStrSize ) ;

SIMPLE_API String * simple_stsimple_delete_gc ( void *pState,String *pString ) ;

SIMPLE_API int simple_stsimple_size ( String *pString ) ;

SIMPLE_API void simple_stsimple_set_gc ( void *pState,String *pString,const char *str ) ;

SIMPLE_API void simple_stsimple_set2_gc ( void *pState,String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_stsimple_add_gc ( void *pState,String *pString,const char *str ) ;

SIMPLE_API void simple_stsimple_add2_gc ( void *pState,String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_stsimple_print ( String *pString ) ;

SIMPLE_API void simple_stsimple_setfromint_gc ( void *pState,String *pString,int x ) ;

SIMPLE_API char * simple_stsimple_lower ( char *cStr ) ;

SIMPLE_API char * simple_stsimple_upper ( char *cStr ) ;

SIMPLE_API char * simple_stsimple_lower2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_stsimple_upper2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_stsimple_find_gc ( void *pState,char *cStr1,char *cStr2 ) ;

SIMPLE_API char * simple_stsimple_find2_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_stsimple_find3_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

void simple_stsimple_test ( void ) ;
/* Macro */
#define simple_stsimple_tolower(x) simple_stsimple_lower(x->cStr)
#define simple_stsimple_toupper(x) simple_stsimple_upper(x->cStr)
#define simple_stsimple_get(x) (x->cStr)
/* Functions without state pointer */

SIMPLE_API String * simple_stsimple_new2 ( const char *str,int nStrSize ) ;

SIMPLE_API String * simple_stsimple_new ( const char *str ) ;

SIMPLE_API void simple_stsimple_add ( String *pString,const char *str ) ;

SIMPLE_API void simple_stsimple_add2 ( String *pString,const char *str,int nStrSize ) ;

SIMPLE_API void simple_stsimple_set ( String *pString,const char *str ) ;

SIMPLE_API void simple_stsimple_set2 ( String *pString,const char *str,int nStrSize ) ;

SIMPLE_API char * simple_stsimple_find ( char *cStr1,char *cStr2 ) ;

SIMPLE_API char * simple_stsimple_find2 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_stsimple_find3 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API String * simple_stsimple_delete ( String *pString ) ;

SIMPLE_API void simple_stsimple_setfromint ( String *pString,int x ) ;
#endif
