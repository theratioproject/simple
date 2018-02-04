
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
	if ( nNum1 < 1 || nNum1 > simple_string_size(pString) ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
		return ;
	}
	newstr = pString->cStr ;
	newstr = newstr + ((int) (nNum1 - 1) ) ;
	SIMPLE_VM_STACK_PUSHPVALUE(newstr);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_SUBSTRING ;
}
