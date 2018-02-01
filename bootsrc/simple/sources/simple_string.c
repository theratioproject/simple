/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Functions */

SIMPLE_API char * simple_stsimple_new_gc ( void *pState,const char *str )
{
	int x  ;
	x = strlen( str ) ;
	return simple_stsimple_new2_gc(pState,str,x) ;
}

SIMPLE_API char * simple_stsimple_new2_gc ( void *pState,const char *str,int nStrSize )
{
	char *pString  ;
	int x  ;
	pString = (struct char *) simple_state_malloc(pState,sizeof(struct char));
	if ( pString == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pString->cStr = (char *) simple_state_malloc(pState,nStrSize+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy char */
	for ( x = 0 ; x < nStrSize ; x++ ) {
		pString->cStr[x] = str[x] ;
	}
	pString->cStr[nStrSize] = '\0' ;
	pString->nSize = nStrSize ;
	return pString ;
}

SIMPLE_API char * simple_stsimple_delete_gc ( void *pState,char *pString )
{
	assert(pString != NULL);
	simple_state_free(pState,pString->cStr);
	pString->cStr = NULL ;
	simple_state_free(pState,pString);
	return NULL ;
}

SIMPLE_API int simple_stsimple_size ( char *pString )
{
	assert(pString != NULL);
	return pString->nSize ;
}

SIMPLE_API void simple_stsimple_set_gc ( void *pState,char *pString,const char *str )
{
	int x  ;
	assert(pString != NULL);
	x = strlen( str ) ;
	simple_stsimple_set2_gc(pState,pString,str,x);
}

SIMPLE_API void simple_stsimple_set2_gc ( void *pState,char *pString,const char *str,int nStrSize )
{
	int x  ;
	assert(pString != NULL);
	assert(pString->cStr != NULL);
	simple_state_free(pState,pString->cStr);
	pString->cStr = (char *) simple_state_malloc(pState,nStrSize+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy char */
	for ( x = 0 ; x < nStrSize ; x++ ) {
		pString->cStr[x] = str[x] ;
	}
	pString->cStr[nStrSize] = '\0' ;
	pString->nSize = nStrSize ;
}

SIMPLE_API void simple_stsimple_add_gc ( void *pState,char *pString,const char *str )
{
	int x  ;
	x = strlen( str ) ;
	simple_stsimple_add2_gc(pState,pString,str,x);
}

SIMPLE_API void simple_stsimple_add2_gc ( void *pState,char *pString,const char *str,int nStrSize )
{
	int x  ;
	int x2  ;
	char *cStr  ;
	assert(pString != NULL);
	x2 = nStrSize+simple_stsimple_size(pString) ;
	cStr = pString->cStr ;
	pString->cStr = (char *) simple_state_malloc(pState,x2+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy char */
	for ( x = 0 ; x < simple_stsimple_size(pString) ; x++ ) {
		pString->cStr[x] = cStr[x] ;
	}
	for ( x = 0 ; x < nStrSize ; x++ ) {
		pString->cStr[x+simple_stsimple_size(pString)] = str[x] ;
	}
	pString->cStr[x2] = '\0' ;
	pString->nSize = x2 ;
	simple_state_free(pState,cStr);
}

SIMPLE_API void simple_stsimple_print ( char *pString )
{
	assert(pString != NULL);
	printf( "%s \n",pString->cStr ) ;
}

SIMPLE_API void simple_stsimple_setfromint_gc ( void *pState,char *pString,int x )
{
	char cStr[20]  ;
	assert(pString != NULL);
	sprintf( cStr , "%d" , x ) ;
	simple_stsimple_set_gc(pState,pString,cStr);
}

SIMPLE_API char * simple_stsimple_lower ( char *cStr )
{
	unsigned int x  ;
	for ( x = 0 ; x < strlen(cStr) ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = tolower( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_stsimple_lower2 ( char *cStr,int nStrSize )
{
	int x  ;
	for ( x = 0 ; x < nStrSize ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = tolower( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_stsimple_upper ( char *cStr )
{
	unsigned int x  ;
	for ( x = 0 ; x < strlen(cStr) ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = toupper( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_stsimple_upper2 ( char *cStr,int nStrSize )
{
	int x  ;
	for ( x = 0 ; x < nStrSize ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = toupper( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_stsimple_find_gc ( void *pState,char *cStr1,char *cStr2 )
{
	return simple_stsimple_find2_gc(pState,cStr1,strlen(cStr1),cStr2,strlen(cStr2)) ;
}

SIMPLE_API char * simple_stsimple_find2_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 )
{
	int nPos,x  ;
	nPos = 0 ;
	if ( (nStrSize1 - nStrSize2) < 0 ) {
		return NULL ;
	}
	while ( nPos <= (nStrSize1 - nStrSize2) ) {
		x = 0 ;
		while ( (x < nStrSize2) && (cStr1[nPos+x] == cStr2[x] ) ) {
			x++ ;
		}
		if ( x == nStrSize2 ) {
			return cStr1+nPos ;
		}
		nPos++ ;
	}
	return NULL ;
}

SIMPLE_API char * simple_stsimple_find3_gc ( void *pState,char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 )
{
	int nPos,x  ;
	char *cStr3  ;
	char *cStr4  ;
	char *pOutput  ;
	/* This function is not case sensitive and work on a copy from cStr1 and cStr2 */
	nPos = 0 ;
	if ( (nStrSize1 - nStrSize2) < 0 ) {
		return NULL ;
	}
	/* Copy Strings and convert to lower case */
	cStr3 = (char *) simple_state_malloc(pState,nStrSize1+1);
	cStr4 = (char *) simple_state_malloc(pState,nStrSize2+1);
	if ( (cStr3==NULL) || (cStr4==NULL) ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 0 ; x <= nStrSize1 ; x++ ) {
		cStr3[x] = cStr1[x] ;
	}
	for ( x = 0 ; x <= nStrSize2 ; x++ ) {
		cStr4[x] = cStr2[x] ;
	}
	simple_stsimple_lower2(cStr3,nStrSize1);
	simple_stsimple_lower2(cStr4,nStrSize2);
	pOutput = NULL ;
	while ( nPos <= (nStrSize1 - nStrSize2) ) {
		x = 0 ;
		while ( (x < nStrSize2) && (cStr3[nPos+x] == cStr4[x] ) ) {
			x++ ;
		}
		if ( x == nStrSize2 ) {
			pOutput = cStr1+nPos ;
			break ;
		}
		nPos++ ;
	}
	/* Free Memory */
	simple_state_free(pState,cStr3);
	simple_state_free(pState,cStr4);
	return pOutput ;
}

void simple_stsimple_test ( void )
{
	#define nMaxValue 10
	char *mystr[nMaxValue]  ;
	int x  ;
	char *pString  ;
	for ( x = 0 ; x < nMaxValue ; x++ ) {
		mystr[x] = simple_stsimple_new("Wow Really i like the c language so much");
		simple_stsimple_print(mystr[x]);
	}
	for ( x = 0 ; x < nMaxValue ; x++ ) {
		mystr[x] = simple_stsimple_delete(mystr[x]);
	}
	/* Test char Add */
	pString = simple_stsimple_new("Hello ");
	simple_stsimple_add(pString,"World");
	printf( "\nTest char Add , Output = %s\n",simple_stsimple_get(pString) ) ;
	simple_stsimple_add(pString," Welcome to the C programming language");
	printf( "\nTest char Add , Output = %s\n",simple_stsimple_get(pString) ) ;
	simple_stsimple_delete(pString);
	/* Test char to Lower */
	pString = simple_stsimple_new("Welcome to my StrinG");
	printf( "Test string to lower \n" ) ;
	printf( "%s\n",simple_stsimple_tolower(pString) ) ;
	simple_stsimple_delete(pString);
	getchar();
}
/* Functions without state pointer */

SIMPLE_API char * simple_stsimple_new2 ( const char *str,int nStrSize )
{
	return simple_stsimple_new2_gc(NULL,str,nStrSize) ;
}

SIMPLE_API char * simple_stsimple_new ( const char *str )
{
	return simple_stsimple_new_gc(NULL,str) ;
}

SIMPLE_API void simple_stsimple_add ( char *pString,const char *str )
{
	simple_stsimple_add_gc(NULL,pString,str);
}

SIMPLE_API void simple_stsimple_add2 ( char *pString,const char *str,int nStrSize )
{
	simple_stsimple_add2_gc(NULL,pString,str,nStrSize);
}

SIMPLE_API void simple_stsimple_set ( char *pString,const char *str )
{
	simple_stsimple_set_gc(NULL,pString,str);
}

SIMPLE_API void simple_stsimple_set2 ( char *pString,const char *str,int nStrSize )
{
	simple_stsimple_set2_gc(NULL,pString,str,nStrSize);
}

SIMPLE_API char * simple_stsimple_find ( char *cStr1,char *cStr2 )
{
	return simple_stsimple_find_gc(NULL,cStr1,cStr2) ;
}

SIMPLE_API char * simple_stsimple_find2 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 )
{
	return simple_stsimple_find2_gc(NULL,cStr1,nStrSize1,cStr2,nStrSize2) ;
}

SIMPLE_API char * simple_stsimple_find3 ( char *cStr1,int nStrSize1,char *cStr2,int nStrSize2 )
{
	return simple_stsimple_find3_gc(NULL,cStr1,nStrSize1,cStr2,nStrSize2) ;
}

SIMPLE_API char * simple_stsimple_delete ( char *pString )
{
	return simple_stsimple_delete_gc(NULL,pString) ;
}

SIMPLE_API void simple_stsimple_setfromint ( char *pString,int x )
{
	simple_stsimple_setfromint_gc(NULL,pString,x);
}
