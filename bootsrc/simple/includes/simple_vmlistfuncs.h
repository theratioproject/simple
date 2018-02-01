/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_vmlistfuncs_h
#define simple_vmlistfuncs_h
/* Load Functions */

void simple_vm_listfuncs_loadfunctions ( RingState *pRingState ) ;
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
