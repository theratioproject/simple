
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


#ifndef simple_vmdll_h
#define simple_vmdll_h
#ifdef _WIN32
#include <windows.h>
#define LoadDLL(x) LoadLibrary(x)
#define GetDLLFunc GetProcAddress
#define CloseDLL FreeLibrary
typedef HINSTANCE LpHandleType ;
#else
#include <dlfcn.h>
#define LoadDLL(x) dlopen(x, RTLD_LAZY)
#define GetDLLFunc dlsym
#define CloseDLL dlclose
typedef void * LpHandleType ;
#endif
typedef void (*loadlibfuncptr)(SimpleState *) ;

void simple_vm_dll_loadfunctions ( SimpleState *state ) ;

void simple_vm_dll_loadlib ( void *pPointer ) ;

void simple_vm_dll_closelib ( void *pPointer ) ;
#endif
