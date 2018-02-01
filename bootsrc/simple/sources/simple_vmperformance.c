/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* For Better Performance */

void simple_vm_pushp ( VM *pVM )
{
	SIMPLE_VM_STACK_PUSHP ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_GLOBAL);
}

void simple_vm_pushplocal ( VM *pVM )
{
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_LOADADDRESS ;
		simple_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		simple_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	SIMPLE_VM_STACK_PUSHPVALUE(SIMPLE_VM_IR_READPVALUE(3)) ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_LOCAL);
}

void simple_vm_incp ( VM *pVM )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + 1);
}

void simple_vm_pushpv ( VM *pVM )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	pVM->nSP++ ;
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHCVAR ;
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHNVAR ;
	}
}

void simple_vm_incjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC ) == 0 ) {
		simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Change Instruction for Performance */
	if ( pVM->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace ICO_INCJUMP with IncPJUMP for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMPSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMP ;
		}
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( pVM->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace ICO_INCJUMP with IncLPJUMP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_INCLPJUMP ;
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(3),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)));
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
		simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 +nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_incpjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_inclpjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_INCJUMP ;
		simple_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		simple_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(3) ;
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_jumpvarlenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Change Instruction for Performance */
	if ( pVM->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace JumpVarLENum with JumpVarPLENum for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUMSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUM ;
		}
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( pVM->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace JumpVarLENum with JumpVarLPLENum for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLPLENUM ;
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(5),simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 2 ;
		simple_list_addpointer_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,SIMPLE_VM_STACK_READP);
		simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)));
		#endif
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
		simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_jumpvarplenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_jumpvarlplenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(5)  != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLENUM ;
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		simple_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(4) ;
	nNum1 = simple_list_getdouble(pVM->aForStep,simple_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_vm_stringtonum(pVM,simple_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	if ( nNum1 < 0 ) {
		if ( ! (nNum2 >= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	} else {
		if ( ! (nNum2 <= SIMPLE_VM_IR_READDVALUE(2)) ) {
			/* Jump */
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
		}
	}
}

void simple_vm_loadfuncp ( VM *pVM )
{
	List *pList  ;
	pVM->nFuncExecute++ ;
	pVM->nFuncExecute2++ ;
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pFuncCallList);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(3));
	simple_list_addstsimple_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READC);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(2));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nSP);
	simple_list_newlist_gc(pVM->pRingState,pList);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->cFileName);
	pVM->cPrevFileName = pVM->cFileName ;
	pVM->cFileName = (char *) SIMPLE_VM_IR_READPVALUE(4) ;
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->cFileName);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(5));
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(6));
	simple_vm_saveloadaddressscope(pVM);
}
/* For Loop Optimization When Step = 1 */

void simple_vm_incpjumpstep1 ( VM *pVM )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We Don't Check Data Type */
	nNum1 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum1 + 1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void simple_vm_jumpvarplenumstep1 ( VM *pVM )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We don't Check Data type */
	nNum1 = simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	if ( nNum1 > SIMPLE_VM_IR_READDVALUE(2) ) {
		/* Jump */
		pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
	}
}
