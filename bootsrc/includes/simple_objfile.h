
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

void simple_objfile_writefile ( SimpleState *state ) ;

void simple_objfile_writelist ( List *pList,FILE *fObj ) ;

int simple_objfile_readfile ( SimpleState *state,char *cFileName ) ;

int simple_objfile_readstring ( SimpleState *state,char *cString ) ;

int simple_objfile_readfromsource ( SimpleState *state,char *cSource,int nSourceType ) ;

int simple_objfile_processfile ( SimpleState *state,char *cFileName,List *pListFunctions,List  *pListClasses,List  *pListModuless,List  *pListCode,List  *pListStack ) ;

int simple_objfile_processstring ( SimpleState *state,char *cContent,List *pListFunctions,List  *pListClasses,List  *pListModuless,List  *pListCode,List  *pListStack ) ;

void simple_objfile_updateclassespointers ( SimpleState *state ) ;

void simple_objfile_xorstring ( char *cString,int nStringSize,char *cKey,int nKeySize ) ;

void simple_objfile_readc ( SimpleState *state,char **cSource,char *cDest,int nCount ) ;

char simple_objfile_getc ( SimpleState *state,char **cSource ) ;
/* MACRO */
/* Object File Source */
#define SIMPLE_OBJFILE_READFROMFILE 1
#define SIMPLE_OBJFILE_READFROMSTRING 2
#endif
