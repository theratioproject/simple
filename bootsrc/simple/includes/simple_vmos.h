/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_vmos_h
#define simple_vmos_h
/* Functions */

void simple_vm_os_loadfunctions ( RingState *pRingState ) ;

void simple_vm_os_ismsdos ( void *pPointer ) ;

void simple_vm_os_iswindows ( void *pPointer ) ;

void simple_vm_os_iswindows64 ( void *pPointer ) ;

void simple_vm_os_isunix ( void *pPointer ) ;

void simple_vm_os_ismacosx ( void *pPointer ) ;

void simple_vm_os_islinux ( void *pPointer ) ;

void simple_vm_os_isfreebsd ( void *pPointer ) ;

void simple_vm_os_isandroid ( void *pPointer ) ;

void simple_vm_os_windowsnl ( void *pPointer ) ;

void simple_vm_os_currentdir ( void *pPointer ) ;

void simple_vm_os_exefilename ( void *pPointer ) ;

void simple_vm_os_chdir ( void *pPointer ) ;

void simple_vm_os_exefolder ( void *pPointer ) ;
/* Constants */
#define SIMPLE_VM_POINTER_LIBNAME "os"
#endif
