/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_stsimple_h
#define simple_stsimple_h
/* Data */
typedef struct Stsimple {
	char *cStr  ;
	int nSize  ;
	/* Note : nSize is (Allocation Size - 1) */
} Stsimple ;
/* Functions */

RING_API Stsimple * simple_stsimple_new_gc ( void *pState,const char *str ) ;

RING_API Stsimple * simple_stsimple_new2_gc ( void *pState,const char *str,int nStrSize ) ;

RING_API Stsimple * simple_stsimple_delete_gc ( void *pState,Stsimple *pStsimple ) ;

RING_API int simple_stsimple_size ( Stsimple *pStsimple ) ;

RING_API void simple_stsimple_set_gc ( void *pState,Stsimple *pStsimple,const char *str ) ;

RING_API void simple_stsimple_set2_gc ( void *pState,Stsimple *pStsimple,const char *str,int nStrSize ) ;

RING_API void simple_stsimple_add_gc ( void *pState,Stsimple *pStsimple,const char *str ) ;

RING_API void simple_stsimple_add2_gc ( void *pState,Stsimple *pStsimple,const char *str,int nStrSize ) ;

RING_API void simple_stsimple_print ( Stsimple *pStsimple ) ;

RING_API void simple_stsimple_setfromint_gc ( void *pState,Stsimple *pStsimple,int x ) ;

RING_API char * simple_stsimple_lower ( char *cStr ) ;

RING_API char * simple_stsimple_upper ( char *cStr ) ;

RING_API char * simple_stsimple_lower2 ( char *cStr,int nStrSize ) ;

RING_API char * simple_stsimple_upper2 ( char *cStr,int nStrSize ) ;

RING_API char * simple_stsimple_find_gc ( void *pState,char *cStr1,char *cStr2 ) ;

RING_API char * simple_stsimple_find2_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

RING_API char * simple_stsimple_find3_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

void simple_stsimple_test ( void ) ;
/* Macro */
#define simple_stsimple_tolower(x) simple_stsimple_lower(x->cStr)
#define simple_stsimple_toupper(x) simple_stsimple_upper(x->cStr)
#define simple_stsimple_get(x) (x->cStr)
/* Functions without state pointer */

RING_API Stsimple * simple_stsimple_new2 ( const char *str,int nStrSize ) ;

RING_API Stsimple * simple_stsimple_new ( const char *str ) ;

RING_API void simple_stsimple_add ( Stsimple *pStsimple,const char *str ) ;

RING_API void simple_stsimple_add2 ( Stsimple *pStsimple,const char *str,int nStrSize ) ;

RING_API void simple_stsimple_set ( Stsimple *pStsimple,const char *str ) ;

RING_API void simple_stsimple_set2 ( Stsimple *pStsimple,const char *str,int nStrSize ) ;

RING_API char * simple_stsimple_find ( char *cStr1,char *cStr2 ) ;

RING_API char * simple_stsimple_find2 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

RING_API char * simple_stsimple_find3 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 ) ;

RING_API Stsimple * simple_stsimple_delete ( Stsimple *pStsimple ) ;

RING_API void simple_stsimple_setfromint ( Stsimple *pStsimple,int x ) ;
#endif
