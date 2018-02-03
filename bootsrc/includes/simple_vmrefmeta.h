
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


#ifndef simple_vmrefmeta_h
#define simple_vmrefmeta_h
/* Functions */

void simple_vm_refmeta_loadfunctions ( SimpleState *pSimpleState ) ;
/* Functions */

void simple_vm_refmeta_locals ( void *pPointer ) ;

void simple_vm_refmeta_globals ( void *pPointer ) ;

void simple_vm_refmeta_functions ( void *pPointer ) ;

void simple_vm_refmeta_cfunctions ( void *pPointer ) ;

void simple_vm_refmeta_islocal ( void *pPointer ) ;

void simple_vm_refmeta_isglobal ( void *pPointer ) ;

void simple_vm_refmeta_isfunction ( void *pPointer ) ;

void simple_vm_refmeta_iscfunction ( void *pPointer ) ;
/* OOP */

void simple_vm_refmeta_moduless ( void *pPointer ) ;

void simple_vm_refmeta_ismodules ( void *pPointer ) ;

void simple_vm_refmeta_classes ( void *pPointer ) ;

void simple_vm_refmeta_isclass ( void *pPointer ) ;

void simple_vm_refmeta_modulesclasses ( void *pPointer ) ;

void simple_vm_refmeta_ismodulesclass ( void *pPointer ) ;

void simple_vm_refmeta_classname ( void *pPointer ) ;

void simple_vm_refmeta_objectid ( void *pPointer ) ;

void simple_vm_refmeta_attributes ( void *pPointer ) ;

void simple_vm_refmeta_methods ( void *pPointer ) ;

void simple_vm_refmeta_isattribute ( void *pPointer ) ;

void simple_vm_refmeta_ismethod ( void *pPointer ) ;

void simple_vm_refmeta_isprivateattribute ( void *pPointer ) ;

void simple_vm_refmeta_isprivatemethod ( void *pPointer ) ;

void simple_vm_refmeta_addattribute ( void *pPointer ) ;

void simple_vm_refmeta_addmethod ( void *pPointer ) ;

void simple_vm_refmeta_getattribute ( void *pPointer ) ;

void simple_vm_refmeta_setattribute ( void *pPointer ) ;

void simple_vm_refmeta_mergemethods ( void *pPointer ) ;

void simple_vm_refmeta_modulesname ( void *pPointer ) ;
/* VM */

void simple_vm_refmeta_ringvmfileslist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmcalllist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmmemorylist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmfunctionslist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmclasseslist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmmodulesslist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmcfunctionslist ( void *pPointer ) ;

void simple_vm_refmeta_ringvmsettrace ( void *pPointer ) ;

void simple_vm_refmeta_ringvmtracedata ( void *pPointer ) ;

void simple_vm_refmeta_ringvmtraceevent ( void *pPointer ) ;

void simple_vm_refmeta_ringvmtracefunc ( void *pPointer ) ;

void simple_vm_refmeta_ringvmscopescount ( void *pPointer ) ;

void simple_vm_refmeta_ringvmevalinscope ( void *pPointer ) ;

void simple_vm_refmeta_ringvmpasserror ( void *pPointer ) ;

void simple_vm_refmeta_ringvmhideerrormsg ( void *pPointer ) ;

void simple_vm_refmeta_ringvmcallfunc ( void *pPointer ) ;
#endif
