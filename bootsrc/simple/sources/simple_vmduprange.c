/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Duplication & Range */

void simple_vm_dup ( VM *pVM )
{
	char *pString  ;
	double nNum1  ;
	void *pPointer  ;
	int nType  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		pString = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_PUSHCVALUE(simple_stsimple_get(pString));
		simple_stsimple_delete_gc(pVM->pRingState,pString);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_PUSHNVALUE(nNum1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		pPointer = SIMPLE_VM_STACK_READP ;
		nType = SIMPLE_VM_STACK_OBJTYPE ;
		SIMPLE_VM_STACK_PUSHPVALUE(pPointer);
		SIMPLE_VM_STACK_OBJTYPE = nType ;
	}
}

void simple_vm_range ( VM *pVM )
{
	double nNum1,nNum2  ;
	int x  ;
	char cStr[2]  ;
	char *pString1,*pString2  ;
	List *pVar  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_POP ;
			/* Create List Variable */
			pVar = simple_vm_range_newlist(pVM);
			/* Create List */
			if ( nNum2 <= nNum1 ) {
				for ( x = nNum2 ; x <= nNum1 ; x++ ) {
					simple_list_adddouble_gc(pVM->pRingState,pVar,x);
				}
			}
			else {
				for ( x = nNum2 ; x >= nNum1 ; x-- ) {
					simple_list_adddouble_gc(pVM->pRingState,pVar,x);
				}
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		pString1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( simple_stsimple_size(pString1) == 1 ) {
			if ( SIMPLE_VM_STACK_ISSTRING ) {
				pString2 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
				SIMPLE_VM_STACK_POP ;
				if ( simple_stsimple_size(pString2)  == 1 ) {
					cStr[1] = '\0' ;
					nNum1 = pString1->cStr[0] ;
					nNum2 = pString2->cStr[0] ;
					/* Create List Variable */
					pVar = simple_vm_range_newlist(pVM);
					/* Create List */
					if ( nNum2 <= nNum1 ) {
						for ( x = nNum2 ; x <= nNum1 ; x++ ) {
							cStr[0] = (char) x ;
							simple_list_addstsimple_gc(pVM->pRingState,pVar,cStr);
						}
					}
					else {
						for ( x = nNum2 ; x >= nNum1 ; x-- ) {
							cStr[0] = (char) x ;
							simple_list_addstsimple_gc(pVM->pRingState,pVar,cStr);
						}
					}
				}
				simple_stsimple_delete_gc(pVM->pRingState,pString2);
			}
		}
		simple_stsimple_delete_gc(pVM->pRingState,pString1);
	}
}

List * simple_vm_range_newlist ( VM *pVM )
{
	char cVarName[50]  ;
	List *pVar  ;
	/* Create List Variable */
	sprintf( cVarName , "n_sys_var_%d" , pVM->nPC ) ;
	if ( simple_vm_findvar(pVM, cVarName  ) == 0 ) {
		simple_vm_newvar(pVM,cVarName);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	simple_list_setint_gc(pVM->pRingState,pVar,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE);
	simple_list_deleteallitems_gc(pVM->pRingState,simple_list_getlist(pVar,SIMPLE_VAR_VALUE));
	pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
	return pVar ;
}
