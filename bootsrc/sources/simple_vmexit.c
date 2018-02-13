/* Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* End Program / Exit from Loop / Loop (Continue) */

void simple_vm_bye ( VM *vm )
{
	/* Check if the ringvm_evalinscope() function is active */
	if ( vm->nEvalInScope >= 1 ) {
		puts(SIMPLE_VM_ERROR_BADCOMMAND);
		return ;
	}
	vm->nPC = simple_list_getsize(vm->pCode) + 1 ;
}

void simple_vm_exitmark ( VM *vm )
{
	List *list  ;
	/* Exit Mark */
	list = simple_list_newlist_gc(vm->sState,vm->pExitMark);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READI);
	simple_vm_savestate(vm,list);
	/* Loop Mark */
	list = simple_list_newlist_gc(vm->sState,vm->pLoopMark);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READIVALUE(2));
	simple_vm_savestate(vm,list);
}

void simple_vm_popexitmark ( VM *vm )
{
	/* POP Exit Mark */
	simple_list_deleteitem_gc(vm->sState,vm->pExitMark,simple_list_getsize(vm->pExitMark));
	/* POP Loop Mark */
	simple_list_deleteitem_gc(vm->sState,vm->pLoopMark,simple_list_getsize(vm->pLoopMark));
}

void simple_vm_exit ( VM *vm,int nType )
{
	List *list,*pActiveList  ;
	int x,y,nStep  ;
	/* Check if the ringvm_evalinscope() function is active */
	if ( vm->nEvalInScope >= 1 ) {
		puts(SIMPLE_VM_ERROR_BADCOMMAND);
		return ;
	}
	nStep = 0 ;
	/* Set Active List */
	if ( nType == 1 ) {
		pActiveList = vm->pExitMark ;
	} else {
		pActiveList = vm->pLoopMark ;
	}
	/* Get the Number from the Stack */
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nStep = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
	}
	else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_LOOPNUMBEROUTSIDERANGE);
	}
	if ( simple_list_getsize(pActiveList) > 0 ) {
		x = simple_list_getsize(pActiveList) ;
		/* Do Operation */
		if ( (nStep > 0) && (nStep <= simple_list_getsize(pActiveList) ) ) {
			x = simple_list_getsize(pActiveList) - nStep + 1 ;
			for ( y = x + 1 ; y <= simple_list_getsize(pActiveList) ; y++ ) {
				simple_list_deleteitem_gc(vm->sState,pActiveList,y);
			}
		} else {
			if ( nType == 1 ) {
				simple_vm_error(vm,SIMPLE_VM_ERROR_EXITNUMBEROUTSIDERANGE);
			} else {
				simple_vm_error(vm,SIMPLE_VM_ERROR_LOOPNUMBEROUTSIDERANGE);
			}
			return ;
		}
		list = simple_list_getlist(pActiveList,x);
		vm->nPC = simple_list_getint(list,1) ;
		simple_vm_restorestate(vm,list,2,SIMPLE_STATE_EXIT);
	} else {
		if ( nType == 1 ) {
			simple_vm_error(vm,SIMPLE_VM_ERROR_EXITWITHOUTLOOP);
		} else {
			simple_vm_error(vm,SIMPLE_VM_ERROR_LOOPWITHOUTLOOP);
		}
		return ;
	}
}
/* For Loop - Step */

void simple_vm_stepnumber ( VM *vm )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		simple_list_adddouble_gc(vm->sState,vm->aForStep,SIMPLE_VM_STACK_READN);
		SIMPLE_VM_STACK_POP ;
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		simple_list_adddouble_gc(vm->sState,vm->aForStep,nNum1);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_FORSTEPDATATYPE);
	}
}

void simple_vm_popstep ( VM *vm )
{
	simple_list_deleteitem_gc(vm->sState,vm->aForStep,simple_list_getsize(vm->aForStep));
}

void simple_vm_dup ( VM *vm )
{
	String *pString  ;
	double nNum1  ;
	void *pointer  ;
	int nType  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		pString = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_PUSHCVALUE(simple_string_get(pString));
		simple_string_delete_gc(vm->sState,pString);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_PUSHNVALUE(nNum1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		pointer = SIMPLE_VM_STACK_READP ;
		nType = SIMPLE_VM_STACK_OBJTYPE ;
		SIMPLE_VM_STACK_PUSHPVALUE(pointer);
		SIMPLE_VM_STACK_OBJTYPE = nType ;
	}
}

void simple_vm_range ( VM *vm )
{
	double nNum1,nNum2  ;
	int x  ;
	char cStr[2]  ;
	String *pString1,*pString2  ;
	List *pVar  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_POP ;
			/* Create List Variable */
			pVar = simple_vm_range_newlist(vm);
			/* Create List */
			if ( nNum2 <= nNum1 ) {
				for ( x = nNum2 ; x <= nNum1 ; x++ ) {
					simple_list_adddouble_gc(vm->sState,pVar,x);
				}
			}
			else {
				for ( x = nNum2 ; x >= nNum1 ; x-- ) {
					simple_list_adddouble_gc(vm->sState,pVar,x);
				}
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		pString1 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( simple_string_size(pString1) == 1 ) {
			if ( SIMPLE_VM_STACK_ISSTRING ) {
				pString2 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
				SIMPLE_VM_STACK_POP ;
				if ( simple_string_size(pString2)  == 1 ) {
					cStr[1] = '\0' ;
					nNum1 = pString1->cStr[0] ;
					nNum2 = pString2->cStr[0] ;
					/* Create List Variable */
					pVar = simple_vm_range_newlist(vm);
					/* Create List */
					if ( nNum2 <= nNum1 ) {
						for ( x = nNum2 ; x <= nNum1 ; x++ ) {
							cStr[0] = (char) x ;
							simple_list_addstring_gc(vm->sState,pVar,cStr);
						}
					}
					else {
						for ( x = nNum2 ; x >= nNum1 ; x-- ) {
							cStr[0] = (char) x ;
							simple_list_addstring_gc(vm->sState,pVar,cStr);
						}
					}
				}
				simple_string_delete_gc(vm->sState,pString2);
			}
		}
		simple_string_delete_gc(vm->sState,pString1);
	}
}

List * simple_vm_range_newlist ( VM *vm )
{
	char cVarName[50]  ;
	List *pVar  ;
	/* Create List Variable */
	sprintf( cVarName , "n_sys_var_%d" , vm->nPC ) ;
	if ( simple_vm_findvar(vm, cVarName  ) == 0 ) {
		simple_vm_newvar(vm,cVarName);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	simple_list_setint_gc(vm->sState,pVar,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,pVar,SIMPLE_VAR_VALUE);
	simple_list_deleteallitems_gc(vm->sState,simple_list_getlist(pVar,SIMPLE_VAR_VALUE));
	pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
	return pVar ;
}
