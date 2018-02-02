
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


#ifndef simple_objfile_h
#define simple_objfile_h
/*
**  Data 
**  Functions 
*/

void simple_objfile_writefile ( RingState *pRingState ) ;

void simple_objfile_writelist ( List *pList,FILE *fObj ) ;

int simple_objfile_readfile ( RingState *pRingState,char *cFileName ) ;

int simple_objfile_readstring ( RingState *pRingState,char *cString ) ;

int simple_objfile_readfromsource ( RingState *pRingState,char *cSource,int nSourceType ) ;

int simple_objfile_processfile ( RingState *pRingState,char *cFileName,List *pListFunctions,List  *pListClasses,List  *pListPackages,List  *pListCode,List  *pListStack ) ;

int simple_objfile_processstring ( RingState *pRingState,char *cContent,List *pListFunctions,List  *pListClasses,List  *pListPackages,List  *pListCode,List  *pListStack ) ;

void simple_objfile_updateclassespointers ( RingState *pRingState ) ;

void simple_objfile_xorstring ( char *cString,int nStringSize,char *cKey,int nKeySize ) ;

void simple_objfile_readc ( RingState *pRingState,char **cSource,char *cDest,int nCount ) ;

char simple_objfile_getc ( RingState *pRingState,char **cSource ) ;
/* MACRO */
/* Object File Source */
#define SIMPLE_OBJFILE_READFROMFILE 1
#define SIMPLE_OBJFILE_READFROMSTRING 2
#endif
