/* Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Stack and Variables */

void simple_vm_pushv ( VM *pVM )
{
	List *pVar  ;
	List *pList  ;
	if ( pVM->nSP <= pVM->nFuncSP ) {
		/* Happens after using EVAL() in this case we avoid PUSHV */
		return ;
	}
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_SUBSTSIMPLE ) {
		simple_vm_stsimple_pushv(pVM);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		simple_vm_listpushv(pVM);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			/* Check NULL Value */
			if ( pVM->nInClassRegion == 0 ) {
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
						if ( strcmp(simple_list_getstring(pVar,SIMPLE_VAR_VALUE),"NULL") == 0 ) {
							simple_vm_error2(pVM,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
							if ( simple_list_getlist(pVM->pActiveMem,simple_list_getsize(pVM->pActiveMem)) == pVar ) {
								/* Delete the Item from the HashTable */
								simple_hashtable_deleteitem(pVM->pActiveMem->pHashTable,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
								simple_list_deletelastitem_gc(pVM->pRingState,pVM->pActiveMem);
							}
							return ;
						}
					}
				}
			}
			/* We don't use POP, because PUSHCVAR and PUSHNVAR don't do SP++ */
			if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
				SIMPLE_VM_STACK_PUSHCVAR ;
			}
			else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
				SIMPLE_VM_STACK_PUSHNVAR ;
			}
			else if ( simple_list_islist(pVar,SIMPLE_VAR_VALUE) ) {
				/* Support using { } to access object after object name */
				pList = simple_list_getlist(pVar,SIMPLE_VAR_VALUE) ;
				simple_vm_oop_setbraceobj(pVM,pList);
			}
		}
	}
}

void simple_vm_loadaddress ( VM *pVM )
{
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
		/* Support for private attributes */
		simple_list_setint_gc(pVM->pRingState,(List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_PRIVATEFLAG,pVM->nPrivateFlag);
	}
	/* Don't change instruction if it's LoadAFirst */
	if ( pVM->nFirstAddress == 1 ) {
		return ;
	}
	if ( pVM->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace LoadAddress with PUSHP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHP ;
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( pVM->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace LoadAddress with PUSHPLOCAL for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHPLOCAL ;
		simple_vm_newbytecodeitem(pVM,3);
		simple_vm_newbytecodeitem(pVM,4);
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(3),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 2 ;
		simple_list_addpointer_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,SIMPLE_VM_STACK_READP);
		simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)));
		#endif
	}
	/* Add Result Scope to aLoadAddressScope Array */
	simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,pVM->nVarScope);
}

void simple_vm_assignment ( VM *pVM )
{
	List *pVar,*pList  ;
	String *cStr1, *pString  ;
	double nNum1  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_PREVOBJTYPE == SIMPLE_OBJTYPE_SUBSTSIMPLE ) {
		if ( pVM->nBeforeEqual == 0 ) {
			simple_vm_stsimple_assignment(pVM);
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		}
	}
	else if ( SIMPLE_VM_STACK_PREVOBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		simple_vm_listassignment(pVM);
	}
	else if ( SIMPLE_VM_STACK_PREVOBJTYPE ==SIMPLE_OBJTYPE_VARIABLE ) {
		if ( (SIMPLE_VM_STACK_ISSTSIMPLE) && (pVM->nBeforeEqual <= 1 ) ) {
			cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE);
			SIMPLE_VM_STACK_POP ;
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			if ( pVM->nBeforeEqual == 0 ) {
				simple_list_setint_gc(pVM->pRingState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_STSIMPLE);
				simple_list_setstring2_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			} else {
				/* Check NULL Variable */
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					simple_vm_error2(pVM,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
					return ;
				}
				if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
					pString = simple_list_getstringobject(pVar,SIMPLE_VAR_VALUE);
					simple_stsimple_add2_gc(pVM->pRingState,pString,simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
				}
				else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
					simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) +simple_vm_stringtonum(pVM,simple_stsimple_get(cStr1)));
				}
			}
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum1 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_POP ;
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			if ( pVM->nBeforeEqual == 0 ) {
				simple_list_setint_gc(pVM->pRingState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_NUMBER);
				simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , nNum1);
			} else {
				/* Check NULL Variable */
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					simple_vm_error2(pVM,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
					return ;
				}
				simple_vm_beforeequallist(pVM,pVar,nNum1);
			}
		}
		else if ( (SIMPLE_VM_STACK_ISPOINTER) && (pVM->nBeforeEqual == 0 ) ) {
			if ( (SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE) || (SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM) ) {
				/* Get The Source List */
				if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
					pVar = simple_list_getlist((List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_VALUE);
				} else {
					pItem = (Item *) SIMPLE_VM_STACK_READP ;
					pVar = simple_item_getlist(pItem);
				}
				pList = simple_list_new_gc(pVM->pRingState,0);
				simple_list_copy(pList,pVar);
				/*
				**  We use (Temp) List - to avoid problems when coping from parent list to child list 
				**  Simulate C Pointer copy on the original list because we works on the temp list 
				*/
				simple_vm_list_simpointercopy(pVM,pVar);
				SIMPLE_VM_STACK_POP ;
				pVar = (List *) SIMPLE_VM_STACK_READP ;
				SIMPLE_VM_STACK_POP ;
				simple_list_setint_gc(pVM->pRingState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_LIST);
				simple_list_setlist_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE);
				simple_vm_list_copy(pVM,simple_list_getlist(pVar,SIMPLE_VAR_VALUE),pList);
				/* Update self object pointer */
				if ( simple_vm_oop_isobject(simple_list_getlist(pVar,SIMPLE_VAR_VALUE)) ) {
					simple_vm_oop_updateselfpointer(pVM,simple_list_getlist(pVar,SIMPLE_VAR_VALUE),SIMPLE_OBJTYPE_VARIABLE,pVar);
				}
				simple_list_delete_gc(pVM->pRingState,pList);
			}
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		}
	}
	else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_ASSIGNNOTVARIABLE);
	}
	pVM->nBeforeEqual = 0 ;
	/* Clear Assignment Pointer */
	pVM->pAssignment = NULL ;
}

void simple_vm_inc ( VM *pVM )
{
	List *pVar  ;
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC ) == 0 ) {
		simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	if ( ( simple_list_getsize(pVM->pMem) == 1 )  && (pVM->pActiveMem == simple_vm_getglobalscope(pVM)) ) {
		/* Replace ICO_INC with IncP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_INCP ;
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	simple_list_setdouble_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + 1);
}

void simple_vm_loadapushv ( VM *pVM )
{
	List *pVar  ;
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
	}
	if ( ( simple_list_getsize(pVM->pMem) == 1 )  && (pVM->pActiveMem == simple_vm_getglobalscope(pVM)) ) {
		/* Replace LoadAPushV with PUSHPV for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHPV ;
		simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHCVAR ;
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHNVAR ;
	}
}

void simple_vm_newline ( VM *pVM )
{
	pVM->nLineNumber = SIMPLE_VM_IR_READI ;
	simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_NEWLINE);
}

void simple_vm_freestack ( VM *pVM )
{
	int nSP  ;
	List *pList  ;
	/* Clear Assignment Pointer */
	pVM->pAssignment = NULL ;
	/* Clear Load Address Result Scope Array */
	simple_list_deleteallitems_gc(pVM->pRingState,pVM->aLoadAddressScope);
	/* In the class region */
	if ( pVM->nInClassRegion ) {
		/*
		**  Description 
		**  In the class Region we don't free stack to support Object + New Object 
		**  So we can add objects quickly to lists and access them using braces { } 
		**  But If we did this only we may get stack overflow if we did some work in the class region like 
		**  Using Switch (Which use duplication) or calling functions without storing the output using Assignment 
		**  To solve this situation we Use SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER 
		**  So we can support Object + New Object and avoid Stack Overflow too! 
		**  This feature is GREAT in the language where we can quickly move applications from 
		**  Using procedural programming and global variables to Classes and Object Attributes 
		*/
		pList = simple_list_getlist(pVM->aScopeNewObj,simple_list_getsize(pVM->aScopeNewObj));
		nSP = simple_list_getint(pList,SIMPLE_ASCOPENEWOBJ_SP) ;
		if ( pVM->nSP > nSP + SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER ) {
			pVM->nSP = nSP+SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER ;
		}
		return ;
	}
	if ( ( simple_list_getsize(pVM->pFuncCallList) == 0 ) && (pVM->nInsideBraceFlag == 0) ) {
		pVM->nSP = 0 ;
		pVM->nFuncSP = 0 ;
		/* Clear General Temp Memory */
		simple_list_deleteallitems_gc(pVM->pRingState,pVM->pTempMem);
	} else {
		if ( pVM->nInsideBraceFlag == 0 ) {
			pVM->nSP = pVM->nFuncSP ;
		}
		else {
			simple_vm_oop_bracestack(pVM);
		}
	}
}

void simple_vm_setreference ( VM *pVM )
{
	List *pList  ;
	int nType  ;
	void *pPointer  ;
	/*
	**  Check if we have value (string/number) not variable 
	**  In this case we need assignment 
	*/
	if ( ! SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_assignment(pVM);
		return ;
	}
	/* Read Source */
	pPointer = SIMPLE_VM_STACK_READP ;
	nType = SIMPLE_VM_STACK_OBJTYPE ;
	SIMPLE_VM_STACK_POP ;
	/* Read Destination */
	pList = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Reference Counting to Destination before copy from Source */
	simple_vm_gc_checkupdatereference(pList);
	/* Copy by reference */
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
	simple_list_setpointer_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,pPointer);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_PVALUETYPE,nType);
	/* Reference Counting (To Source After copy to Destination) */
	simple_vm_gc_checknewreference(pPointer,nType);
}

void simple_vm_list_copy ( VM *pVM,List *pNewList, List *pList )
{
	int x  ;
	List *pNewList2  ;
	assert(pList != NULL);
	/* Copy Items */
	if ( simple_list_getsize(pList) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		if ( simple_list_isint(pList,x) ) {
			simple_list_addint_gc(pVM->pRingState,pNewList,simple_list_getint(pList,x));
		}
		else if ( simple_list_isdouble(pList,x) ) {
			simple_list_adddouble_gc(pVM->pRingState,pNewList,simple_list_getdouble(pList,x));
		}
		else if ( simple_list_isstring(pList,x) ) {
			simple_list_addstring2_gc(pVM->pRingState,pNewList,simple_list_getstring(pList,x),simple_list_getstringsize(pList,x));
		}
		else if ( simple_list_ispointer(pList,x) ) {
			simple_list_addpointer_gc(pVM->pRingState,pNewList,simple_list_getpointer(pList,x));
		}
		else if ( simple_list_islist(pList,x) ) {
			pNewList2 = simple_list_newlist_gc(pVM->pRingState,pNewList);
			simple_vm_list_copy(pVM,pNewList2,simple_list_getlist(pList,x));
		}
	}
	/* Check if the List if a C Pointer List */
	if ( simple_list_getsize(pList) == SIMPLE_CPOINTER_LISTSIZE ) {
		if ( simple_list_ispointer(pList,SIMPLE_CPOINTER_POINTER)  && simple_list_isstring(pList,SIMPLE_CPOINTER_TYPE) && simple_list_isint(pList,SIMPLE_CPOINTER_STATUS) ) {
			/* Check value to avoid adding the pointer to the C Pointer list again */
			if ( simple_list_getint(pList,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTCOPIED ) {
				/* Mark C Pointer List As Copied */
				simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
				simple_list_setint_gc(pVM->pRingState,pNewList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
				/* Add the pointer to the C Poiners List */
				if ( simple_list_findpointer(pVM->aCPointers,simple_list_getpointer(pList,SIMPLE_CPOINTER_POINTER)) == 0 ) {
					simple_list_addpointer_gc(pVM->pRingState,pVM->aCPointers,simple_list_getpointer(pList,SIMPLE_CPOINTER_POINTER));
				}
			}
			else if ( simple_list_getint(pList,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTASSIGNED ) {
				/* Mark the C Pointer List as Not Copied */
				simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
				simple_list_setint_gc(pVM->pRingState,pNewList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
			}
		}
	}
}

void simple_vm_list_simpointercopy ( VM *pVM,List *pList )
{
	int x  ;
	assert(pList != NULL);
	/* Copy Items */
	if ( simple_list_getsize(pList) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		if ( simple_list_islist(pList,x) ) {
			simple_vm_list_simpointercopy(pVM,simple_list_getlist(pList,x));
		}
	}
	/* Check if the List if a C Pointer List */
	if ( simple_list_getsize(pList) == SIMPLE_CPOINTER_LISTSIZE ) {
		if ( simple_list_ispointer(pList,SIMPLE_CPOINTER_POINTER)  && simple_list_isstring(pList,SIMPLE_CPOINTER_TYPE) && simple_list_isint(pList,SIMPLE_CPOINTER_STATUS) ) {
			/* Check value to avoid adding the pointer to the C Pointer list again */
			if ( simple_list_getint(pList,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTCOPIED ) {
				/* Mark C Pointer List As Copied */
				simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
			}
			else if ( simple_list_getint(pList,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTASSIGNED ) {
				/* Mark the C Pointer List as Not Copied */
				simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
			}
		}
	}
}

void simple_vm_beforeequallist ( VM *pVM,List *pVar,double nNum1 )
{
	String *pString  ;
	char cStr[100]  ;
	if ( simple_list_isdouble(pVar,SIMPLE_VAR_VALUE) ) {
		if ( pVM->nBeforeEqual == 1 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + nNum1);
		} else if ( pVM->nBeforeEqual == 2 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) - nNum1);
		} else if ( pVM->nBeforeEqual == 3 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) * nNum1);
		} else if ( pVM->nBeforeEqual == 4 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) / nNum1);
		} else if ( pVM->nBeforeEqual == 5 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , fmod(simple_list_getdouble(pVar,SIMPLE_VAR_VALUE), nNum1));
		} else if ( pVM->nBeforeEqual == 6 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) & (int) nNum1);
		} else if ( pVM->nBeforeEqual == 7 ) {
			simple_list_setdouble(pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) | (int) nNum1);
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) | (int) nNum1);
		} else if ( pVM->nBeforeEqual == 8 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ^ (int) nNum1);
		} else if ( pVM->nBeforeEqual == 9 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) << (int) nNum1);
		} else if ( pVM->nBeforeEqual == 10 ) {
			simple_list_setdouble_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) >> (int) nNum1);
		}
	}
	else if ( (simple_list_isstring(pVar,SIMPLE_VAR_VALUE) == 1) && (pVM->nBeforeEqual == 1) ) {
		pString = simple_list_getstringobject(pVar,SIMPLE_VAR_VALUE);
		simple_stsimple_add_gc(pVM->pRingState,pString,simple_vm_numtostring(pVM,nNum1,cStr));
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_beforeequalitem ( VM *pVM,Item *pItem,double nNum1 )
{
	String *pString  ;
	char cStr[100]  ;
	if ( simple_item_isdouble(pItem) ) {
		if ( pVM->nBeforeEqual == 1 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,simple_item_getdouble(pItem) + nNum1);
		} else if ( pVM->nBeforeEqual == 2 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,simple_item_getdouble(pItem) - nNum1);
		} else if ( pVM->nBeforeEqual == 3 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,simple_item_getdouble(pItem) * nNum1);
		} else if ( pVM->nBeforeEqual == 4 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,simple_item_getdouble(pItem) / nNum1);
		} else if ( pVM->nBeforeEqual == 5 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,fmod(simple_item_getdouble(pItem) , nNum1));
		} else if ( pVM->nBeforeEqual == 6 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,(int) simple_item_getdouble(pItem) & (int) nNum1);
		} else if ( pVM->nBeforeEqual == 7 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,(int) simple_item_getdouble(pItem) | (int) nNum1);
		} else if ( pVM->nBeforeEqual == 8 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,(int) simple_item_getdouble(pItem) ^ (int) nNum1);
		} else if ( pVM->nBeforeEqual == 9 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,(int) simple_item_getdouble(pItem) << (int) nNum1);
		} else if ( pVM->nBeforeEqual == 10 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem ,(int) simple_item_getdouble(pItem) >> (int) nNum1);
		}
	}
	else if ( (simple_item_isstring(pItem) == 1)  && (pVM->nBeforeEqual == 1) ) {
		pString = simple_item_getstring(pItem);
		simple_stsimple_add_gc(pVM->pRingState,pString,simple_vm_numtostring(pVM,nNum1,cStr));
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_plusplus ( VM *pVM )
{
	List *pList  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pList = (List *) SIMPLE_VM_STACK_READP ;
			if ( simple_list_isdouble(pList,SIMPLE_VAR_VALUE) ) {
				simple_list_setdouble_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,simple_list_getdouble(pList,SIMPLE_VAR_VALUE)+1);
				return ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			if ( simple_item_isdouble(pItem) ) {
				simple_item_setdouble_gc(pVM->pRingState,pItem,simple_item_getdouble(pItem)+1);
				return ;
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(SIMPLE_VM_STACK_READN + 1);
		return ;
	}
	simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
}

void simple_vm_minusminus ( VM *pVM )
{
	List *pList  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pList = (List *) SIMPLE_VM_STACK_READP ;
			if ( simple_list_isdouble(pList,SIMPLE_VAR_VALUE) ) {
				simple_list_setdouble_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,simple_list_getdouble(pList,SIMPLE_VAR_VALUE)-1);
				return ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			if ( simple_item_isdouble(pItem) ) {
				simple_item_setdouble_gc(pVM->pRingState,pItem,simple_item_getdouble(pItem)-1);
				return ;
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(SIMPLE_VM_STACK_READN - 1);
		return ;
	}
	simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
}

void simple_vm_assignmentpointer ( VM *pVM )
{
	List *pList, *pList2  ;
	Item *pItem  ;
	int x  ;
	if ( pVM->nNOAssignment == 0 ) {
		pVM->pAssignment = SIMPLE_VM_STACK_READP ;
		/* Check trying to change the self pointer */
		pList = NULL ;
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			if ( simple_list_islist((List *) pVM->pAssignment,SIMPLE_VAR_VALUE) ) {
				pList = simple_list_getlist((List *) pVM->pAssignment,SIMPLE_VAR_VALUE) ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) pVM->pAssignment ;
			if ( simple_item_gettype(pItem) == ITEMTYPE_LIST ) {
				pList = simple_item_getlist(pItem) ;
			}
			else {
				return ;
			}
		}
		else {
			return ;
		}
		if ( simple_vm_oop_isobject(pList)  && (simple_list_getsize(pVM->pObjState) > 0 ) ) {
			/* We loop to prevent passing self to function that destory the self */
			for ( x = 1 ; x <= simple_list_getsize(pVM->pObjState) ; x++ ) {
				pList2 = simple_list_getlist(pVM->pObjState,x);
				if ( simple_list_getpointer(pList,SIMPLE_OBJECT_OBJECTDATA) == simple_list_getpointer(pList2,SIMPLE_OBJSTATE_SCOPE) ) {
					simple_vm_error(pVM,SIMPLE_VM_ERROR_TRYINGTOMODIFYTHESELFPOINTER);
					return ;
				}
			}
		}
	}
	else {
		pVM->nNOAssignment = 0 ;
	}
}

void simple_vm_freeloadaddressscope ( VM *pVM )
{
	/* Clear Load Address Result Scope Array */
	simple_list_deleteallitems_gc(pVM->pRingState,pVM->aLoadAddressScope);
}
