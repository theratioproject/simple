/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/ring.h"
/* For Better Performance */

void ring_vm_pushp ( VM *pVM )
{
	SIMPLE_VM_STACK_PUSHP ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	ring_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_GLOBAL);
}

void ring_vm_pushplocal ( VM *pVM )
{
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_LOADADDRESS ;
		ring_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		ring_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	SIMPLE_VM_STACK_PUSHPVALUE(SIMPLE_VM_IR_READPVALUE(3)) ;
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Update Scope List */
	ring_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_LOCAL);
}

void ring_vm_incp ( VM *pVM )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) + 1);
}

void ring_vm_pushpv ( VM *pVM )
{
	List *pVar  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	pVM->nSP++ ;
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHCVAR ;
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHNVAR ;
	}
}

void ring_vm_incjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( ring_vm_findvar(pVM, SIMPLE_VM_IR_READC ) == 0 ) {
		ring_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Change Instruction for Performance */
	if ( pVM->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace ICO_INCJUMP with IncPJUMP for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMPSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_INCPJUMP ;
		}
		ring_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( pVM->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace ICO_INCJUMP with IncLPJUMP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_INCLPJUMP ;
		ring_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(3),SIMPLE_VM_STACK_READP);
		ring_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
		ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 +nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void ring_vm_incpjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void ring_vm_inclpjump ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(4) != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_INCJUMP ;
		ring_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(3));
		ring_list_deliteminsidelist(pVM->aNewByteCodeItems,SIMPLE_VM_IR_ITEM(4));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(3) ;
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
		return ;
	}
	ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2 + nNum1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void ring_vm_jumpvarlenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	if ( ring_vm_findvar(pVM, SIMPLE_VM_IR_READC  ) == 0 ) {
		ring_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Change Instruction for Performance */
	if ( pVM->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace JumpVarLENum with JumpVarPLENum for better performance */
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUMSTEP1 ;
		} else {
			SIMPLE_VM_IR_OPCODE = ICO_JUMPVARPLENUM ;
		}
		ring_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( pVM->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace JumpVarLENum with JumpVarLPLENum for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLPLENUM ;
		ring_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),SIMPLE_VM_STACK_READP);
		ring_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(5),ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 2 ;
		ring_list_addpointer_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,SIMPLE_VM_STACK_READP);
		ring_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getint(pVM->aScopeID,ring_list_getsize(pVM->aScopeID)));
		#endif
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
		ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum2);
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
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

void ring_vm_jumpvarplenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
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

void ring_vm_jumpvarlplenum ( VM *pVM )
{
	List *pVar  ;
	double nNum1,nNum2  ;
	/* Check Scope Life Time */
	if ( SIMPLE_VM_IR_READIVALUE(5)  != pVM->nActiveScopeID ) {
		SIMPLE_VM_IR_OPCODE = ICO_JUMPVARLENUM ;
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT - 2 ;
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		ring_list_deleteitem_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,ring_list_getsize(SIMPLE_VM_IR_LIST));
		#endif
		pVM->nPC-- ;
		return ;
	}
	pVar = (List *) SIMPLE_VM_IR_READPVALUE(4) ;
	nNum1 = ring_list_getdouble(pVM->aForStep,ring_list_getsize(pVM->aForStep));
	/* Check Data */
	if ( ring_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_vm_stringtonum(pVM,ring_list_getstring(pVar,SIMPLE_VAR_VALUE));
	}
	else if ( ring_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		nNum2 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	} else {
		ring_vm_error(pVM,SIMPLE_VM_ERROR_FORLOOPDATATYPE);
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

void ring_vm_loadfuncp ( VM *pVM )
{
	List *pList  ;
	pVM->nFuncExecute++ ;
	pVM->nFuncExecute2++ ;
	pList = ring_list_newlist_gc(pVM->pRingState,pVM->pFuncCallList);
	ring_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(3));
	ring_list_addstring_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READC);
	ring_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(2));
	ring_list_addint_gc(pVM->pRingState,pList,pVM->nSP);
	ring_list_newlist_gc(pVM->pRingState,pList);
	ring_list_addpointer_gc(pVM->pRingState,pList,pVM->cFileName);
	pVM->cPrevFileName = pVM->cFileName ;
	pVM->cFileName = (char *) SIMPLE_VM_IR_READPVALUE(4) ;
	ring_list_addpointer_gc(pVM->pRingState,pList,pVM->cFileName);
	ring_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(5));
	ring_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(6));
	ring_vm_saveloadaddressscope(pVM);
}
/* For Loop Optimization When Step = 1 */

void ring_vm_incpjumpstep1 ( VM *pVM )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We Don't Check Data Type */
	nNum1 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	ring_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,nNum1 + 1);
	/* Jump */
	pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
}

void ring_vm_jumpvarplenumstep1 ( VM *pVM )
{
	List *pVar  ;
	double nNum1  ;
	pVar = (List *) SIMPLE_VM_IR_READP ;
	/* We don't Check Data type */
	nNum1 = ring_list_getdouble(pVar,SIMPLE_VAR_VALUE) ;
	if ( nNum1 > SIMPLE_VM_IR_READDVALUE(2) ) {
		/* Jump */
		pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
	}
}
