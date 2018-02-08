
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
	register_block("callDynamiclibrary",simple_vm_dll_loadlib);
	register_block("closeDynamiclibrary",simple_vm_dll_closelib);
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
		pFunc = (loadlibfuncptr) GetDLLFunc(handle, "init_simple_lib") ;
		if ( pFunc == NULL ) {
			printf( "\nLibrary File : %s", file_real_name(SIMPLE_API_GETSTRING(1)) ) ;
			SIMPLE_API_ERROR("The dynamic library doesn't contain the init_simple_lib() function!");
			return ;
		}
		simple_list_deletearray_gc(sState,sState->c_blocks);
		(*pFunc)(sState) ;
		simple_list_genarray_gc(sState,sState->c_blocks);
		simple_list_genhashtable2_gc(sState,sState->c_blocks);
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

/* User Interface - Commands Implementation (Faster) - Because we don't have functions call */

void simple_vm_see ( VM *vm )
{
	Item *pItem  ;
	char cStr[100]  ;
	List *list  ;
	char *cString  ;
	int x  ;
	if ( vm->nFuncExecute > 0 ) {
		vm->nFuncExecute-- ;
	}
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		cString = SIMPLE_VM_STACK_READC ;
		if ( strlen(cString) != (unsigned int) SIMPLE_VM_STACK_STRINGSIZE ) {
			for ( x = 0 ; x < SIMPLE_VM_STACK_STRINGSIZE ; x++ ) {
				printf( "%c",cString[x] ) ;
			}
		} else {
			printf( "%s",cString ) ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			list = simple_list_getlist((List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_VALUE);
			if ( simple_vm_oop_isobject(list) ) {
				simple_vm_oop_printobj(vm,list);
			} else {
				simple_list_print(list);
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			list = simple_item_getlist(pItem) ;
			if ( simple_vm_oop_isobject(list) ) {
				simple_vm_oop_printobj(vm,list);
			} else {
				simple_list_print(list);
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		simple_vm_numtostring(vm,SIMPLE_VM_STACK_READN,cStr);
		printf( "%s",cStr ) ;
	}
	SIMPLE_VM_STACK_POP ;
	simple_vm_freestack(vm);
	fflush(stdout);
}

void simple_vm_give ( VM *vm )
{
	int x  ;
	char cLine[256]  ;
	List *pVar  ;
	Item *pItem  ;
	/* Get Input From the User and save it in the variable */
	fgets(cLine , 256 , stdin );
	/* Remove New Line */
	for ( x = 0 ; x <= 255 ; x++ ) {
		if ( cLine[x] == '\n' ) {
			cLine[x] = '\0' ;
			break ;
		}
	}
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			simple_list_setint_gc(vm->sState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_STRING);
			simple_list_setstsimple_gc(vm->sState,pVar, SIMPLE_VAR_VALUE, cLine);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			simple_item_settype_gc(vm->sState,pItem,ITEMTYPE_STRING);
			simple_string_set_gc(vm->sState,simple_item_getstring(pItem),cLine);
		}
	}
}

/* User Interface Functions (Another implementation) - Flexibile (We can replace functions in Simple Code) */

void simple_vmlib_see ( void *pPointer )
{
	char *cString  ;
	int x  ;
	char cStr[100]  ;
	List *list  ;
	VM *vm  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_ISSTRING(1) ) {
		cString = SIMPLE_API_GETSTRING(1) ;
		if ( strlen(cString) != (unsigned int) SIMPLE_API_GETSTRINGSIZE(1) ) {
			for ( x = 0 ; x < SIMPLE_API_GETSTRINGSIZE(1) ; x++ ) {
				printf( "%c",cString[x] ) ;
			}
		} else {
			printf( "%s",cString ) ;
		}
	}
	else if ( SIMPLE_API_ISNUMBER(1) ) {
		simple_vm_numtostring(vm,SIMPLE_API_GETNUMBER(1),cStr);
		printf( "%s",cStr ) ;
	}
	else if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1);
		if ( simple_vm_oop_isobject(list) ) {
			simple_vm_oop_printobj(vm,list);
		} else {
			simple_list_print(list);
		}
	}
	fflush(stdout);
}

void simple_vmlib_give ( void *pPointer )
{
	int x  ;
	char cLine[256]  ;
	/* Get Input From the User and save it in the variable */
	fgets(cLine , 256 , stdin );
	/* Remove New Line */
	for ( x = 0 ; x <= 255 ; x++ ) {
		if ( cLine[x] == '\n' ) {
			cLine[x] = '\0' ;
			break ;
		}
	}
	SIMPLE_API_RETSTRING(cLine);
}


