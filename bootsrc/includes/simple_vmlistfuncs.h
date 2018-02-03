
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


#ifndef simple_vmlistfuncs_h
#define simple_vmlistfuncs_h
/* Load Functions */

void simple_vm_listfuncs_loadfunctions ( SimpleState *pSimpleState ) ;
/* List Functions */

void simple_vmlib_list ( void *pPointer ) ;

void simple_vmlib_find ( void *pPointer ) ;

void simple_vmlib_max ( void *pPointer ) ;

void simple_vmlib_min ( void *pPointer ) ;

void simple_vmlib_insert ( void *pPointer ) ;

void simple_vmlib_sort ( void *pPointer ) ;

void simple_vmlib_binarysearch ( void *pPointer ) ;

void simple_vmlib_reverse ( void *pPointer ) ;
#endif
