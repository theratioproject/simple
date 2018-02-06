
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
/* String As Array */

void simple_vm_stsimple_pushv ( VM *vm )
{
	char *newstr  ;
	char cStr[2]  ;
	newstr = (char *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	cStr[0] = newstr[0] ;
	cStr[1] = '\0' ;
	SIMPLE_VM_STACK_PUSHCVALUE(cStr);
}

void simple_vm_stsimple_assignment ( VM *vm )
{
	String *cStr1  ;
	char *newstr  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		cStr1 = simple_string_new_gc(vm->pSimpleState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( simple_string_size(cStr1) == 1 ) {
			newstr = (char *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			newstr[0] = simple_string_get(cStr1)[0] ;
			simple_string_delete_gc(vm->pSimpleState,cStr1);
			return ;
		} else {
			simple_string_delete_gc(vm->pSimpleState,cStr1);
			simple_vm_error(vm,SIMPLE_VM_ERROR_VALUEMORETHANONECHAR);
			return ;
		}
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_VARISNOTSTRING);
		return ;
	}
}

void simple_vm_stsimple_index ( VM *vm, String *pString, double nNum1 )
{
	char *newstr  ;
	/* We will push a pointer of the sub char to the stack */
	if ( nNum1 < 0 || nNum1 > simple_string_size(pString) ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
		return ;
	}
	newstr = pString->cStr ;
	newstr = newstr + ((int) (nNum1 - 1) ) ;
	SIMPLE_VM_STACK_PUSHPVALUE(newstr);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_SUBSTRING ;
}

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
