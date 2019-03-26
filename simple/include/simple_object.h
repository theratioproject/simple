
/* 
	Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_object.c
 * Author: Azeez Adewale
 *
 * Created on January 11, 2019, 10:54 AM
 */

#ifndef simple_object_h
#define simple_object_h
/*
**  Data 
**  Functions 
*/

//#define DEBUG_OBJFILE

#define SIMPLE_OBJECT_HEAD_SIZE 11 
#define SIMPLE_OBJECT_HEAD "simple0.4.0"
#define SIMPLE_OBJECT_KEY "simple"
#define SIMPLE_OBJECT_KEY_SIZE 6

void simple_object_writefile ( SimpleState *sState ) ;

void simple_object_writelist ( List *pList,FILE *fp ) ;

int simple_object_readfile ( SimpleState *sState,char *file_name ) ;

int simple_object_readstring ( SimpleState *sState,char *string ) ;

int simple_object_readfromsource ( SimpleState *sState,char *source,int source_type ) ;

int simple_object_processfile ( SimpleState *sState,char *file_name,List *blocks_list,List  *classes_list,List  *pListPackages,List  *code_list,List  *stack_list ) ;

int simple_object_processstring ( SimpleState *sState,char *content,List *blocks_list,List  *classes_list,List  *pListPackages,List  *code_list,List  *stack_list ) ;

void simple_object_updatepointers ( SimpleState *sState ) ;

void simple_object_xorstring ( char *string,int string_size,char *key,int key_size ) ;

void simple_object_readc ( SimpleState *sState,char **source,char *dest,int count ) ;

char simple_object_getc ( SimpleState *sState,char **source ) ;

/* MACRO */
/* Object File Source */
#define SIMPLE_OBJECT_FROMFILE 1
#define SIMPLE_OBJECT_FROMSTRING 2
#endif
