/* Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* End Program / Exit from Loop / Loop (Continue) */

void simple_vm_bye ( VM *pVM )
{
	/* Check if the ringvm_evalinscope() function is active */
	if ( pVM->nEvalInScope >= 1 ) {
		puts(SIMPLE_VM_ERROR_BADCOMMAND);
		return ;
	}
	pVM->nPC = simple_list_getsize(pVM->pCode) + 1 ;
}

void simple_vm_exitmark ( VM *pVM )
{
	List *pList  ;
	/* Exit Mark */
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pExitMark);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READI);
	simple_vm_savestate(pVM,pList);
	/* Loop Mark */
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pLoopMark);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READIVALUE(2));
	simple_vm_savestate(pVM,pList);
}

void simple_vm_popexitmark ( VM *pVM )
{
	/* POP Exit Mark */
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pExitMark,simple_list_getsize(pVM->pExitMark));
	/* POP Loop Mark */
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pLoopMark,simple_list_getsize(pVM->pLoopMark));
}

void simple_vm_exit ( VM *pVM,int nType )
{
	List *pList,*pActiveList  ;
	int x,y,nStep  ;
	/* Check if the ringvm_evalinscope() function is active */
	if ( pVM->nEvalInScope >= 1 ) {
		puts(SIMPLE_VM_ERROR_BADCOMMAND);
		return ;
	}
	nStep = 0 ;
	/* Set Active List */
	if ( nType == 1 ) {
		pActiveList = pVM->pExitMark ;
	} else {
		pActiveList = pVM->pLoopMark ;
	}
	/* Get the Number from the Stack */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nStep = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_LOOPNUMBEROUTSIDERANGE);
	}
	if ( simple_list_getsize(pActiveList) > 0 ) {
		x = simple_list_getsize(pActiveList) ;
		/* Do Operation */
		if ( (nStep > 0) && (nStep <= simple_list_getsize(pActiveList) ) ) {
			x = simple_list_getsize(pActiveList) - nStep + 1 ;
			for ( y = x + 1 ; y <= simple_list_getsize(pActiveList) ; y++ ) {
				simple_list_deleteitem_gc(pVM->pRingState,pActiveList,y);
			}
		} else {
			if ( nType == 1 ) {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_EXITNUMBEROUTSIDERANGE);
			} else {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_LOOPNUMBEROUTSIDERANGE);
			}
			return ;
		}
		pList = simple_list_getlist(pActiveList,x);
		pVM->nPC = simple_list_getint(pList,1) ;
		simple_vm_restorestate(pVM,pList,2,SIMPLE_STATE_EXIT);
	} else {
		if ( nType == 1 ) {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_EXITWITHOUTLOOP);
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_LOOPWITHOUTLOOP);
		}
		return ;
	}
}
/* For Loop - Step */

void simple_vm_stepnumber ( VM *pVM )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		simple_list_adddouble_gc(pVM->pRingState,pVM->aForStep,SIMPLE_VM_STACK_READN);
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		simple_list_adddouble_gc(pVM->pRingState,pVM->aForStep,nNum1);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_FORSTEPDATATYPE);
	}
}

void simple_vm_popstep ( VM *pVM )
{
	simple_list_deleteitem_gc(pVM->pRingState,pVM->aForStep,simple_list_getsize(pVM->aForStep));
}
