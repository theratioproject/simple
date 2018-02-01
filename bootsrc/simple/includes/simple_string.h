/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_string_h
#define simple_string_h
/* Data */
typedef struct Stsimple {
	char *cStr  ;
	int nSize  ;
	/* Note : nSize is (Allocation Size - 1) */
} Stsimple ;
/* Functions */

SIMPLE_API Stsimple * simple_string_new_gc ( void *pState,const char *str ) ;

SIMPLE_API Stsimple * simple_string_new2_gc ( void *pState,const char *str,int nStrSize ) ;

SIMPLE_API Stsimple * simple_string_delete_gc ( void *pState,Stsimple *pStsimple ) ;

SIMPLE_API int simple_string_size ( Stsimple *pStsimple ) ;

SIMPLE_API void simple_string_set_gc ( void *pState,Stsimple *pStsimple,const char *str ) ;

SIMPLE_API void simple_string_set2_gc ( void *pState,Stsimple *pStsimple,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_add_gc ( void *pState,Stsimple *pStsimple,const char *str ) ;

SIMPLE_API void simple_string_add2_gc ( void *pState,Stsimple *pStsimple,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_print ( Stsimple *pStsimple ) ;

SIMPLE_API void simple_string_setfromint_gc ( void *pState,Stsimple *pStsimple,int x ) ;

SIMPLE_API char * simple_string_lower ( char *cStr ) ;

SIMPLE_API char * simple_string_upper ( char *cStr ) ;

SIMPLE_API char * simple_string_lower2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_string_upper2 ( char *cStr,int nStrSize ) ;

SIMPLE_API char * simple_string_find_gc ( void *pState,char *cStr1,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_string_find3_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

void simple_string_test ( void ) ;
/* Macro */
#define simple_string_tolower(x) simple_string_lower(x->cStr)
#define simple_string_toupper(x) simple_string_upper(x->cStr)
#define simple_string_get(x) (x->cStr)
/* Functions without state pointer */

SIMPLE_API Stsimple * simple_string_new2 ( const char *str,int nStrSize ) ;

SIMPLE_API Stsimple * simple_string_new ( const char *str ) ;

SIMPLE_API void simple_string_add ( Stsimple *pStsimple,const char *str ) ;

SIMPLE_API void simple_string_add2 ( Stsimple *pStsimple,const char *str,int nStrSize ) ;

SIMPLE_API void simple_string_set ( Stsimple *pStsimple,const char *str ) ;

SIMPLE_API void simple_string_set2 ( Stsimple *pStsimple,const char *str,int nStrSize ) ;

SIMPLE_API char * simple_string_find ( char *cStr1,char *cStr2 ) ;

SIMPLE_API char * simple_string_find2 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API char * simple_string_find3 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

SIMPLE_API Stsimple * simple_string_delete ( Stsimple *pStsimple ) ;

SIMPLE_API void simple_string_setfromint ( Stsimple *pStsimple,int x ) ;
#endif
