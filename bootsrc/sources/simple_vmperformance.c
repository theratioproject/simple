/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* For Better Performance */

void simple_vm_pushp ( VM *vm )
{
	SIMPLE_VM_STACK_PUSHP ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	simple_list_addint_gc(vm->sState,vm->aLoadAddressScope,SIMPLE_VARSCOPE_GLOBAL);
}

void simple_vm_pushplocal ( VM *vm )
{
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != vm->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_LOADADDRESS ;
		simple_list_deliteminsidelist(vm->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		simple_list_deliteminsidelist(vm->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		vm->nPC-- ;
		return ;
	}
	SIMPLE_VM_STACK_PUSHPVALUE(SIMPLE_VM_IR_READPVALUE(3)) ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	simple_list_addint_gc(vm->sState,vm->aLoadAddressScope,SIMPLE_VARSCOPE_LOCAL);
}

void simple_vm_incp ( VM *vm )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + 1);
}

void simple_vm_pushpv ( VM *vm )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	vm->nSP++ ;
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHCVAR ;
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHNVAR ;
	}
}

void simple_vm_incjump ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC ) == 0 ) {
		simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
	}
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Change Instruction for Performance */
	if ( vm->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace ICO_INCJUMP with IncPJUMP for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMPSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMP ;
		}
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( vm->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace ICO_INCJUMP with IncLPJUMP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_INCLPJUMP ;
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(3),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(4),simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)));
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
		simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum2 +nNum1);
	/* Jump */
	vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_incpjump ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_inclpjump ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != vm->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_INCJUMP ;
		simple_list_deliteminsidelist(vm->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		simple_list_deliteminsidelist(vm->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		vm->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(3) ;
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_jumpvarlenum ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
	}
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Change Instruction for Performance */
	if ( vm->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace JumpVarLENum with JumpVarPLENum for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUMSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUM ;
		}
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( vm->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace JumpVarLENum with JumpVarLPLENum for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLPLENUM ;
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(4),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(5),simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 2 ;
		simple_list_addpointer_gc(vm->sState,SIMPLE_VM_IR_LIST,SIMPLE_VM_STACK_READP);
		simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)));
		#endif
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
		simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_jumpvarplenum ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_jumpvarlplenum ( VM *vm )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(5)  != vm->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLENUM ;
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		vm->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(4) ;
	nNum1 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(vm,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_loadblockp ( VM *vm )
{
	List *list  ;
	vm->nBlockExecute++ ;
	vm->nBlockExecute2++ ;
	list = simple_list_newlist_gc(vm->sState,vm->pBlockCallList);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READIVALUE(3));
	simple_list_addstring_gc(vm->sState,list,SIMPLE_VM_IR_READC);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READIVALUE(2));
	simple_list_addint_gc(vm->sState,list,vm->nSP);
	simple_list_newlist_gc(vm->sState,list);
	simple_list_addpointer_gc(vm->sState,list,vm->file_name);
	vm->cPrevFileName = vm->file_name ;
	vm->file_name = (char *) SIMPLE_VM_IR_READPVALUE(4) ;
	simple_list_addpointer_gc(vm->sState,list,vm->file_name);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READIVALUE(5));
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READIVALUE(6));
	simple_vm_saveloadaddressscope(vm);
}
/* For Loop Optimization When Step = 1 */

void simple_vm_incpjumpstep1 ( VM *vm )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We Don't Check Data Type */
	nNum1 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,nNum1 + 1);
	/* Jump */
	vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_jumpvarplenumstep1 ( VM *vm )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We don't Check Data type */
	nNum1 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	if ( nNum1 > SIMPLE_VM_IR_READDVALUE(2) ) {
		/* Jump */
		vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
	}
}

void simple_vm_jump ( VM *vm )
{
	SIMPLE_VM_JUMP ;
}

void simple_vm_jumpzero ( VM *vm )
{
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  == 0 ) {
			simple_vm_jump(vm);
		}
	}
	SIMPLE_VM_STACK_POP ;
}

void simple_vm_jumpfor ( VM *vm )
{
	double nNum1,nNum2,nNum3  ;
	/* Check Data */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	nNum2 = simple_list_getdouble(vm->aForStep,simple_list_getsize(vm->aForStep));
	/* Check Data */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum3 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum3 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	/*
	**  nNum2 = Step value that can be positive or negative 
	**  nNum1 = Items Count , nNum3 = Index 
	*/
	if ( nNum2 < 0 ) {
		if ( ! ( nNum3 >= nNum1 ) ) {
			simple_vm_jump(vm);
		}
	}
	else {
		if ( ! ( nNum3 <= nNum1 ) ) {
			simple_vm_jump(vm);
		}
	}
}

void simple_vm_jumpone ( VM *vm )
{
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  != 0 ) {
			simple_vm_jump(vm);
		}
	}
	SIMPLE_VM_STACK_POP ;
}

void simple_vm_jumpone2 ( VM *vm )
{
	/* Add 1, required for jump in many 'OR' in conditions */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  != 0 ) {
			simple_vm_jump(vm);
			return ;
		}
	}
	SIMPLE_VM_STACK_POP ;
	SIMPLE_VM_STACK_PUSHNVALUE(0);
}

void simple_vm_jumpzero2 ( VM *vm )
{
	/* Add 1, required for jump in many 'AND' in conditions */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN  == 0 ) {
			simple_vm_jump(vm);
			return ;
		}
	}
	SIMPLE_VM_STACK_POP ;
	SIMPLE_VM_STACK_PUSHNVALUE(1);
}
