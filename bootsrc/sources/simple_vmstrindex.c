
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_vmstrindex.h
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
	String *string_one  ;
	char *newstr  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( simple_string_size(string_one) == 1 ) {
			newstr = (char *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			newstr[0] = simple_string_get(string_one)[0] ;
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		} else {
			simple_string_delete_gc(vm->sState,string_one);
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
	if ( nNum1 < list_index || nNum1 > simple_string_size(pString) ) {
            simple_vm_error(vm,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
            return ;
	}
	newstr = pString->cStr ;
	newstr = newstr + ((int) (nNum1 - list_index) ) ;
	SIMPLE_VM_STACK_PUSHPVALUE(newstr);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_SUBSTRING ;
}

/* Try Catch Done */

void simple_vm_try ( VM *vm )
{
	List *list  ;
	list = simple_list_newlist_gc(vm->sState,vm->pTry);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READI);
	simple_vm_savestate(vm,list);
	vm->nActiveCatch = 0 ;
}

void simple_vm_catch ( VM *vm,const char *cError )
{
	List *list  ;
	list = simple_list_getlist(vm->pTry,simple_list_getsize(vm->pTry));
	vm->nPC = simple_list_getint(list,1) ;
	simple_vm_restorestate(vm,list,2,SIMPLE_STATE_TRYCATCH);
	/* Define variable __err__ to contain the error message */
	simple_list_setstsimple_gc(vm->sState,simple_list_getlist(simple_vm_getglobalscope(vm),6),3,cError);
	/* Tell C-API caller (CALL command) that catch happens! */
	vm->nActiveCatch = 1 ;
	/* Catch Statements must be executed without try effects */
	simple_vm_finally(vm);
}

void simple_vm_finally ( VM *vm )
{
	simple_list_deleteitem_gc(vm->sState,vm->pTry,simple_list_getsize(vm->pTry));
}
