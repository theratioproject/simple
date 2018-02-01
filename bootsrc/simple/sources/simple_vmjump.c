/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Jump Functions */

void simple_vm_jump ( VM *pVM )
{
	SIMPLE_VM_JUMP ;
}

void simple_vm_jumpzero ( VM *pVM )
{
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  == 0 ) {
			simple_vm_jump(pVM);
		}
	}
	SIMPLE_VM_STACK_POP ;
}

void simple_vm_jumpfor ( VM *pVM )
{
	double nNum1,nNum2,nNum3  ;
	/* Check Data */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	nNum2 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum3 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		nNum3 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	/*
	**  nNum2 = Step value that can be positive or negative 
	**  nNum1 = Items Count , nNum3 = Index 
	*/
	if ( nNum2 < 0 ) {
		if ( ! ( nNum3 >= nNum1 ) ) {
			simple_vm_jump(pVM);
		}
	}
	else {
		if ( ! ( nNum3 <= nNum1 ) ) {
			simple_vm_jump(pVM);
		}
	}
}

void simple_vm_jumpone ( VM *pVM )
{
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  != 0 ) {
			simple_vm_jump(pVM);
		}
	}
	SIMPLE_VM_STACK_POP ;
}

void simple_vm_jumpone2 ( VM *pVM )
{
	/* Add 1, required for jump in many 'OR' in conditions */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  != 0 ) {
			simple_vm_jump(pVM);
			return ;
		}
	}
	SIMPLE_VM_STACK_POP ;
	SIMPLE_VM_STACK_PUSHNVALUE(0);
}

void simple_vm_jumpzero2 ( VM *pVM )
{
	/* Add 1, required for jump in many 'AND' in conditions */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  == 0 ) {
			simple_vm_jump(pVM);
			return ;
		}
	}
	SIMPLE_VM_STACK_POP ;
	SIMPLE_VM_STACK_PUSHNVALUE(1);
}
