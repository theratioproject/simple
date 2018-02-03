
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
/* Try Catch Done */

void simple_vm_try ( VM *vm )
{
	List *pList  ;
	pList = simple_list_newlist_gc(vm->pSimpleState,vm->pTry);
	simple_list_addint_gc(vm->pSimpleState,pList,SIMPLE_VM_IR_READI);
	simple_vm_savestate(vm,pList);
	vm->nActiveCatch = 0 ;
}

void simple_vm_catch ( VM *vm,const char *cError )
{
	List *pList  ;
	pList = simple_list_getlist(vm->pTry,simple_list_getsize(vm->pTry));
	vm->nPC = simple_list_getint(pList,1) ;
	simple_vm_restorestate(vm,pList,2,SIMPLE_STATE_TRYCATCH);
	/* Define variable __err__ to contain the error message */
	simple_list_setstsimple_gc(vm->pSimpleState,simple_list_getlist(simple_vm_getglobalscope(vm),6),3,cError);
	/* Tell C-API caller (CALL command) that catch happens! */
	vm->nActiveCatch = 1 ;
	/* Catch Statements must be executed without try effects */
	simple_vm_done(vm);
}

void simple_vm_done ( VM *vm )
{
	simple_list_deleteitem_gc(vm->pSimpleState,vm->pTry,simple_list_getsize(vm->pTry));
}
