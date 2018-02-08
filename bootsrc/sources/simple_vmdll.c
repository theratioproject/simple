
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
#include "../includes/simple_vmdll.h"
/* Functions */

void simple_vm_dll_loadfunctions ( SimpleState *sState )
{
	simple_vm_funcregister("loadlib",simple_vm_dll_loadlib);
	simple_vm_funcregister("closelib",simple_vm_dll_closelib);
}

void simple_vm_dll_loadlib ( void *pPointer )
{
	LpHandleType handle  ;
	const char *cDLL  ;
	loadlibfuncptr pFunc  ;
	VM *vm  ;
	SimpleState *sState  ;
	vm = (VM *) pPointer ;
	sState = vm->sState ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cDLL = SIMPLE_API_GETSTRING(1);
		handle = LoadDLL(cDLL);
		if ( handle == NULL ) {
			printf( "\nLibrary File : %s",SIMPLE_API_GETSTRING(1) ) ;
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_LIBLOADERROR);
			return ;
		}
		pFunc = (loadlibfuncptr) GetDLLFunc(handle, "ringlib_init") ;
		if ( pFunc == NULL ) {
			printf( "\nLibrary File : %s",SIMPLE_API_GETSTRING(1) ) ;
			SIMPLE_API_ERROR("The dynamic library doesn't contain the ringlib_init() function!");
			return ;
		}
		simple_list_deletearray_gc(sState,sState->pSimpleCFunctions);
		(*pFunc)(sState) ;
		simple_list_genarray_gc(sState,sState->pSimpleCFunctions);
		simple_list_genhashtable2_gc(sState,sState->pSimpleCFunctions);
		SIMPLE_API_RETCPOINTER(handle,"DLL");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_dll_closelib ( void *pPointer )
{
	LpHandleType handle  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		handle = SIMPLE_API_GETCPOINTER(1,"DLL") ;
		CloseDLL(handle);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
