
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


#include "../includes/simple.h"
/* Blocks */

SIMPLE_API String * simple_string_new_gc ( void *pState,const char *str )
{
	int x  ;
	x = strlen( str ) ;
	return simple_string_new2_gc(pState,str,x) ;
}

SIMPLE_API String * simple_string_new2_gc ( void *pState,const char *str,int str_size )
{
	String *pString  ;
	int x  ;
	pString = (struct String *) simple_state_malloc(pState,sizeof(struct String));
	if ( pString == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pString->cStr = (char *) simple_state_malloc(pState,str_size+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy String */
	for ( x = 0 ; x < str_size ; x++ ) {
		pString->cStr[x] = str[x] ;
	}
	pString->cStr[str_size] = '\0' ;
	pString->nSize = str_size ;
	return pString ;
}

SIMPLE_API String * simple_string_delete_gc ( void *pState,String *pString )
{
	assert(pString != NULL);
	simple_state_free(pState,pString->cStr);
	pString->cStr = NULL ;
	simple_state_free(pState,pString);
	return NULL ;
}

SIMPLE_API int simple_string_size ( String *pString )
{
	assert(pString != NULL);
	return pString->nSize ;
}

SIMPLE_API void simple_string_set_gc ( void *pState,String *pString,const char *str )
{
	int x  ;
	assert(pString != NULL);
	x = strlen( str ) ;
	simple_string_set2_gc(pState,pString,str,x);
}

SIMPLE_API void simple_string_set2_gc ( void *pState,String *pString,const char *str,int str_size )
{
	int x  ;
	assert(pString != NULL);
	assert(pString->cStr != NULL);
	simple_state_free(pState,pString->cStr);
	pString->cStr = (char *) simple_state_malloc(pState,str_size+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy String */
	for ( x = 0 ; x < str_size ; x++ ) {
		pString->cStr[x] = str[x] ;
	}
	pString->cStr[str_size] = '\0' ;
	pString->nSize = str_size ;
}

SIMPLE_API void simple_string_add_gc ( void *pState,String *pString,const char *str )
{
	int x  ;
	x = strlen( str ) ;
	simple_string_add2_gc(pState,pString,str,x);
}

SIMPLE_API void simple_string_add2_gc ( void *pState,String *pString,const char *str,int str_size )
{
	int x  ;
	int x2  ;
	char *cStr  ;
	assert(pString != NULL);
	x2 = str_size+simple_string_size(pString) ;
	cStr = pString->cStr ;
	pString->cStr = (char *) simple_state_malloc(pState,x2+1);
	if ( pString->cStr  == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Copy String */
	for ( x = 0 ; x < simple_string_size(pString) ; x++ ) {
		pString->cStr[x] = cStr[x] ;
	}
	for ( x = 0 ; x < str_size ; x++ ) {
		pString->cStr[x+simple_string_size(pString)] = str[x] ;
	}
	pString->cStr[x2] = '\0' ;
	pString->nSize = x2 ;
	simple_state_free(pState,cStr);
}

SIMPLE_API void simple_string_print ( String *pString )
{
	assert(pString != NULL);
	printf( "%s \n",pString->cStr ) ;
}

SIMPLE_API void simple_string_setfromint_gc ( void *pState,String *pString,int x )
{
	char cStr[20]  ;
	assert(pString != NULL);
	sprintf( cStr , "%d" , x ) ;
	simple_string_set_gc(pState,pString,cStr);
}

SIMPLE_API char * simple_string_lower ( char *cStr )
{
    if( NOT_CASE_SENSITIVE ){
        unsigned int x  ;
        for ( x = 0 ; x < strlen(cStr) ; x++ ) {
            if ( isalpha(cStr[x]) ) {
                    cStr[x] = tolower( cStr[x] );
            }
        }
    }
    return cStr ;
}

SIMPLE_API char * simple_string_lower2 ( char *cStr,int str_size )
{
	int x  ;
	for ( x = 0 ; x < str_size ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = tolower( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_string_upper ( char *cStr )
{
	unsigned int x  ;
	for ( x = 0 ; x < strlen(cStr) ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = toupper( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_string_upper2 ( char *cStr,int str_size )
{
	int x  ;
	for ( x = 0 ; x < str_size ; x++ ) {
		if ( isalpha(cStr[x]) ) {
			cStr[x] = toupper( cStr[x] );
		}
	}
	return cStr ;
}

SIMPLE_API char * simple_string_find_gc ( void *pState,char *string_one,char *cStr2 )
{
	return simple_string_find2_gc(pState,string_one,strlen(string_one),cStr2,strlen(cStr2)) ;
}

SIMPLE_API char * simple_string_find2_gc ( void *pState,char *string_one,int str_size1,char *cStr2,int str_size2 )
{
	int nPos,x  ;
	nPos = 0 ;
	if ( (str_size1 - str_size2) < 0 ) {
		return NULL ;
	}
	while ( nPos <= (str_size1 - str_size2) ) {
		x = 0 ;
		while ( (x < str_size2) && (string_one[nPos+x] == cStr2[x] ) ) {
			x++ ;
		}
		if ( x == str_size2 ) {
			return string_one+nPos ;
		}
		nPos++ ;
	}
	return NULL ;
}

SIMPLE_API char * simple_string_find3_gc ( void *pState,char *string_one,int str_size1,char *cStr2,int str_size2 )
{
	int nPos,x  ;
	char *cStr3  ;
	char *cStr4  ;
	char *pOutput  ;
	/* This block is not case sensitive and work on a copy from string_one and cStr2 */
	nPos = 0 ;
	if ( (str_size1 - str_size2) < 0 ) {
		return NULL ;
	}
	/* Copy Strings and convert to lower case */
	cStr3 = (char *) simple_state_malloc(pState,str_size1+1);
	cStr4 = (char *) simple_state_malloc(pState,str_size2+1);
	if ( (cStr3==NULL) || (cStr4==NULL) ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 0 ; x <= str_size1 ; x++ ) {
		cStr3[x] = string_one[x] ;
	}
	for ( x = 0 ; x <= str_size2 ; x++ ) {
		cStr4[x] = cStr2[x] ;
	}
	simple_string_lower2(cStr3,str_size1);
	simple_string_lower2(cStr4,str_size2);
	pOutput = NULL ;
	while ( nPos <= (str_size1 - str_size2) ) {
		x = 0 ;
		while ( (x < str_size2) && (cStr3[nPos+x] == cStr4[x] ) ) {
			x++ ;
		}
		if ( x == str_size2 ) {
			pOutput = string_one+nPos ;
			break ;
		}
		nPos++ ;
	}
	/* Free Memory */
	simple_state_free(pState,cStr3);
	simple_state_free(pState,cStr4);
	return pOutput ;
}

void simple_string_test ( void )
{
	#define nMaxValue 10
	String *mystr[nMaxValue]  ;
	int x  ;
	String *pString  ;
	for ( x = 0 ; x < nMaxValue ; x++ ) {
		mystr[x] = simple_string_new("Wow Really i like the c language so much");
		simple_string_print(mystr[x]);
	}
	for ( x = 0 ; x < nMaxValue ; x++ ) {
		mystr[x] = simple_string_delete(mystr[x]);
	}
	/* Test String Add */
	pString = simple_string_new("Hello ");
	simple_string_add(pString,"World");
	printf( "\nTest String Add , Output = %s\n",simple_string_get(pString) ) ;
	simple_string_add(pString," Welcome to the C programming language");
	printf( "\nTest String Add , Output = %s\n",simple_string_get(pString) ) ;
	simple_string_delete(pString);
	/* Test String to Lower */
	pString = simple_string_new("Welcome to my StrinG");
	printf( "Test string to lower \n" ) ;
	printf( "%s\n",simple_string_tolower(pString) ) ;
	simple_string_delete(pString);
	getchar();
}
/* Blocks without state pointer */

SIMPLE_API String * simple_string_new2 ( const char *str,int str_size )
{
	return simple_string_new2_gc(NULL,str,str_size) ;
}

SIMPLE_API String * simple_string_new ( const char *str )
{
	return simple_string_new_gc(NULL,str) ;
}

SIMPLE_API void simple_string_add ( String *pString,const char *str )
{
	simple_string_add_gc(NULL,pString,str);
}

SIMPLE_API void simple_string_add2 ( String *pString,const char *str,int str_size )
{
	simple_string_add2_gc(NULL,pString,str,str_size);
}

SIMPLE_API void simple_string_set ( String *pString,const char *str )
{
	simple_string_set_gc(NULL,pString,str);
}

SIMPLE_API void simple_string_set2 ( String *pString,const char *str,int str_size )
{
	simple_string_set2_gc(NULL,pString,str,str_size);
}

SIMPLE_API char * simple_string_find ( char *string_one,char *cStr2 )
{
	return simple_string_find_gc(NULL,string_one,cStr2) ;
}

SIMPLE_API char * simple_string_find2 ( char *string_one,int str_size1,char *cStr2,int str_size2 )
{
	return simple_string_find2_gc(NULL,string_one,str_size1,cStr2,str_size2) ;
}

SIMPLE_API char * simple_string_find3 ( char *string_one,int str_size1,char *cStr2,int str_size2 )
{
	return simple_string_find3_gc(NULL,string_one,str_size1,cStr2,str_size2) ;
}

SIMPLE_API String * simple_string_delete ( String *pString )
{
	return simple_string_delete_gc(NULL,pString) ;
}

SIMPLE_API void simple_string_setfromint ( String *pString,int x )
{
	simple_string_setfromint_gc(NULL,pString,x);
}
