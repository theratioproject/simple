
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
/* Stack and Variables */

void simple_vm_pushv ( VM *vm )
{
	List *pVar  ;
	List *list  ;
	if ( vm->nSP <= vm->nFuncSP ) {
		/* Happens after using EVAL() in this case we avoid PUSHV */
		return ;
	}
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_SUBSTRING ) {
		simple_vm_stsimple_pushv(vm);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		simple_vm_listpushv(vm);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			/* Check NULL Value */
			if ( vm->nInClassRegion == 0 ) {
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
						if ( strcmp(simple_list_getstring(pVar,SIMPLE_VAR_VALUE),"NULL") == 0 ) {
							simple_vm_error2(vm,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
							if ( simple_list_getlist(vm->pActiveMem,simple_list_getsize(vm->pActiveMem)) == pVar ) {
								/* Delete the Item from the HashTable */
								simple_hashtable_deleteitem(vm->pActiveMem->pHashTable,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
								simple_list_deletelastitem_gc(vm->sState,vm->pActiveMem);
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
				list = simple_list_getlist(pVar,SIMPLE_VAR_VALUE) ;
				simple_vm_oop_setbraceobj(vm,list);
			}
		}
	}
}

void simple_vm_loadaddress ( VM *vm )
{
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
		/* Support for private attributes */
		simple_list_setint_gc(vm->sState,(List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_PRIVATEFLAG,vm->nPrivateFlag);
	}
	/* Don't change instruction if it's LoadAFirst */
	if ( vm->nFirstAddress == 1 ) {
		return ;
	}
	if ( vm->nVarScope == SIMPLE_VARSCOPE_GLOBAL ) {
		/* Replace LoadAddress with PUSHP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHP ;
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	else if ( vm->nVarScope == SIMPLE_VARSCOPE_LOCAL ) {
		/* Replace LoadAddress with PUSHPLOCAL for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHPLOCAL ;
		simple_vm_newbytecodeitem(vm,3);
		simple_vm_newbytecodeitem(vm,4);
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(3),SIMPLE_VM_STACK_READP);
		simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(4),simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)));
		#if SIMPLE_SHOWICFINAL
		SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 2 ;
		simple_list_addpointer_gc(vm->sState,SIMPLE_VM_IR_LIST,SIMPLE_VM_STACK_READP);
		simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)));
		#endif
	}
	/* Add Result Scope to aLoadAddressScope Array */
	simple_list_addint_gc(vm->sState,vm->aLoadAddressScope,vm->nVarScope);
}

void simple_vm_assignment ( VM *vm )
{
	List *pVar,*list  ;
	String *cStr1, *pString  ;
	double nNum1  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_PREVOBJTYPE == SIMPLE_OBJTYPE_SUBSTRING ) {
		if ( vm->nBeforeEqual == 0 ) {
			simple_vm_stsimple_assignment(vm);
		} else {
			simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		}
	}
	else if ( SIMPLE_VM_STACK_PREVOBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		simple_vm_listassignment(vm);
	}
	else if ( SIMPLE_VM_STACK_PREVOBJTYPE ==SIMPLE_OBJTYPE_VARIABLE ) {
		if ( (SIMPLE_VM_STACK_ISSTRING) && (vm->nBeforeEqual <= 1 ) ) {
			cStr1 = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE);
			SIMPLE_VM_STACK_POP ;
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			if ( vm->nBeforeEqual == 0 ) {
				simple_list_setint_gc(vm->sState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_STRING);
				simple_list_setstring2_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , simple_string_get(cStr1),simple_string_size(cStr1));
			} else {
				/* Check NULL Variable */
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					simple_vm_error2(vm,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
					return ;
				}
				if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
					pString = simple_list_getstringobject(pVar,SIMPLE_VAR_VALUE);
					simple_string_add2_gc(vm->sState,pString,simple_string_get(cStr1),simple_string_size(cStr1));
				}
				else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
					simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) +simple_vm_stringtonum(vm,simple_string_get(cStr1)));
				}
			}
			simple_string_delete_gc(vm->sState,cStr1);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum1 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_POP ;
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			if ( vm->nBeforeEqual == 0 ) {
				simple_list_setint_gc(vm->sState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_NUMBER);
				simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , nNum1);
			} else {
				/* Check NULL Variable */
				if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
					simple_vm_error2(vm,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
					return ;
				}
				simple_vm_beforeequallist(vm,pVar,nNum1);
			}
		}
		else if ( (SIMPLE_VM_STACK_ISPOINTER) && (vm->nBeforeEqual == 0 ) ) {
			if ( (SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE) || (SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM) ) {
				/* Get The Source List */
				if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
					pVar = simple_list_getlist((List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_VALUE);
				} else {
					pItem = (Item *) SIMPLE_VM_STACK_READP ;
					pVar = simple_item_getlist(pItem);
				}
				list = simple_list_new_gc(vm->sState,0);
				simple_list_copy(list,pVar);
				/*
				**  We use (Temp) List - to avoid problems when coping from parent list to child list 
				**  Simulate C Pointer copy on the original list because we works on the temp list 
				*/
				simple_vm_list_simpointercopy(vm,pVar);
				SIMPLE_VM_STACK_POP ;
				pVar = (List *) SIMPLE_VM_STACK_READP ;
				SIMPLE_VM_STACK_POP ;
				simple_list_setint_gc(vm->sState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_LIST);
				simple_list_setlist_gc(vm->sState,pVar,SIMPLE_VAR_VALUE);
				simple_vm_list_copy(vm,simple_list_getlist(pVar,SIMPLE_VAR_VALUE),list);
				/* Update self object pointer */
				if ( simple_vm_oop_isobject(simple_list_getlist(pVar,SIMPLE_VAR_VALUE)) ) {
					simple_vm_oop_updateselfpointer(vm,simple_list_getlist(pVar,SIMPLE_VAR_VALUE),SIMPLE_OBJTYPE_VARIABLE,pVar);
				}
				simple_list_delete_gc(vm->sState,list);
			}
		} else {
			simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		}
	}
	else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_ASSIGNNOTVARIABLE);
	}
	vm->nBeforeEqual = 0 ;
	/* Clear Assignment Pointer */
	vm->pAssignment = NULL ;
}

void simple_vm_inc ( VM *vm )
{
	List *pVar  ;
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC ) == 0 ) {
		simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
	}
	if ( ( simple_list_getsize(vm->pMem) == 1 )  && (vm->pActiveMem == simple_vm_getglobalscope(vm)) ) {
		/* Replace ICO_INC with IncP for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_INCP ;
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	simple_list_setdouble_gc(vm->sState,pVar,SIMPLE_VAR_VALUE,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + 1);
}

void simple_vm_loadapushv ( VM *vm )
{
	List *pVar  ;
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC  ) == 0 ) {
		simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
	}
	if ( ( simple_list_getsize(vm->pMem) == 1 )  && (vm->pActiveMem == simple_vm_getglobalscope(vm)) ) {
		/* Replace LoadAPushV with PUSHPV for better performance */
		SIMPLE_VM_IR_OPCODE = ICO_PUSHPV ;
		simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(1),SIMPLE_VM_STACK_READP);
	}
	pVar = (List *) SIMPLE_VM_STACK_READP ;
	if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHCVAR ;
	}
	else if ( simple_list_isnumber(pVar,SIMPLE_VAR_VALUE) ) {
		SIMPLE_VM_STACK_PUSHNVAR ;
	}
}

void simple_vm_newline ( VM *vm )
{
	vm->nLineNumber = SIMPLE_VM_IR_READI ;
	simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_NEWLINE);
}

void simple_vm_freestack ( VM *vm )
{
	int nSP  ;
	List *list  ;
	/* Clear Assignment Pointer */
	vm->pAssignment = NULL ;
	/* Clear Load Address Result Scope Array */
	simple_list_deleteallitems_gc(vm->sState,vm->aLoadAddressScope);
	/* In the class region */
	if ( vm->nInClassRegion ) {
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
		list = simple_list_getlist(vm->aScopeNewObj,simple_list_getsize(vm->aScopeNewObj));
		nSP = simple_list_getint(list,SIMPLE_ASCOPENEWOBJ_SP) ;
		if ( vm->nSP > nSP + SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER ) {
			vm->nSP = nSP+SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER ;
		}
		return ;
	}
	if ( ( simple_list_getsize(vm->pFuncCallList) == 0 ) && (vm->nInsideBraceFlag == 0) ) {
		vm->nSP = 0 ;
		vm->nFuncSP = 0 ;
		/* Clear General Temp Memory */
		simple_list_deleteallitems_gc(vm->sState,vm->pTempMem);
	} else {
		if ( vm->nInsideBraceFlag == 0 ) {
			vm->nSP = vm->nFuncSP ;
		}
		else {
			simple_vm_oop_bracestack(vm);
		}
	}
}

void simple_vm_setreference ( VM *vm )
{
	List *list  ;
	int nType  ;
	void *pPointer  ;
	/*
	**  Check if we have value (string/number) not variable 
	**  In this case we need assignment 
	*/
	if ( ! SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_assignment(vm);
		return ;
	}
	/* Read Source */
	pPointer = SIMPLE_VM_STACK_READP ;
	nType = SIMPLE_VM_STACK_OBJTYPE ;
	SIMPLE_VM_STACK_POP ;
	/* Read Destination */
	list = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Reference Counting to Destination before copy from Source */
	simple_vm_gc_checkupdatereference(list);
	/* Copy by reference */
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
	simple_list_setpointer_gc(vm->sState,list,SIMPLE_VAR_VALUE,pPointer);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_PVALUETYPE,nType);
	/* Reference Counting (To Source After copy to Destination) */
	simple_vm_gc_checknewreference(pPointer,nType);
}

void simple_vm_list_copy ( VM *vm,List *pNewList, List *list )
{
	int x  ;
	List *pNewList2  ;
	assert(list != NULL);
	/* Copy Items */
	if ( simple_list_getsize(list) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		if ( simple_list_isint(list,x) ) {
			simple_list_addint_gc(vm->sState,pNewList,simple_list_getint(list,x));
		}
		else if ( simple_list_isdouble(list,x) ) {
			simple_list_adddouble_gc(vm->sState,pNewList,simple_list_getdouble(list,x));
		}
		else if ( simple_list_isstring(list,x) ) {
			simple_list_addstring2_gc(vm->sState,pNewList,simple_list_getstring(list,x),simple_list_getstringsize(list,x));
		}
		else if ( simple_list_ispointer(list,x) ) {
			simple_list_addpointer_gc(vm->sState,pNewList,simple_list_getpointer(list,x));
		}
		else if ( simple_list_islist(list,x) ) {
			pNewList2 = simple_list_newlist_gc(vm->sState,pNewList);
			simple_vm_list_copy(vm,pNewList2,simple_list_getlist(list,x));
		}
	}
	/* Check if the List if a C Pointer List */
	if ( simple_list_getsize(list) == SIMPLE_CPOINTER_LISTSIZE ) {
		if ( simple_list_ispointer(list,SIMPLE_CPOINTER_POINTER)  && simple_list_isstring(list,SIMPLE_CPOINTER_TYPE) && simple_list_isint(list,SIMPLE_CPOINTER_STATUS) ) {
			/* Check value to avoid adding the pointer to the C Pointer list again */
			if ( simple_list_getint(list,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTCOPIED ) {
				/* Mark C Pointer List As Copied */
				simple_list_setint_gc(vm->sState,list,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
				simple_list_setint_gc(vm->sState,pNewList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
				/* Add the pointer to the C Poiners List */
				if ( simple_list_findpointer(vm->aCPointers,simple_list_getpointer(list,SIMPLE_CPOINTER_POINTER)) == 0 ) {
					simple_list_addpointer_gc(vm->sState,vm->aCPointers,simple_list_getpointer(list,SIMPLE_CPOINTER_POINTER));
				}
			}
			else if ( simple_list_getint(list,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTASSIGNED ) {
				/* Mark the C Pointer List as Not Copied */
				simple_list_setint_gc(vm->sState,list,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
				simple_list_setint_gc(vm->sState,pNewList,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
			}
		}
	}
}

void simple_vm_list_simpointercopy ( VM *vm,List *list )
{
	int x  ;
	assert(list != NULL);
	/* Copy Items */
	if ( simple_list_getsize(list) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		if ( simple_list_islist(list,x) ) {
			simple_vm_list_simpointercopy(vm,simple_list_getlist(list,x));
		}
	}
	/* Check if the List if a C Pointer List */
	if ( simple_list_getsize(list) == SIMPLE_CPOINTER_LISTSIZE ) {
		if ( simple_list_ispointer(list,SIMPLE_CPOINTER_POINTER)  && simple_list_isstring(list,SIMPLE_CPOINTER_TYPE) && simple_list_isint(list,SIMPLE_CPOINTER_STATUS) ) {
			/* Check value to avoid adding the pointer to the C Pointer list again */
			if ( simple_list_getint(list,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTCOPIED ) {
				/* Mark C Pointer List As Copied */
				simple_list_setint_gc(vm->sState,list,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_COPIED);
			}
			else if ( simple_list_getint(list,SIMPLE_CPOINTER_STATUS) == SIMPLE_CPOINTERSTATUS_NOTASSIGNED ) {
				/* Mark the C Pointer List as Not Copied */
				simple_list_setint_gc(vm->sState,list,SIMPLE_CPOINTER_STATUS,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
			}
		}
	}
}

void simple_vm_beforeequallist ( VM *vm,List *pVar,double nNum1 )
{
	String *pString  ;
	char cStr[100]  ;
	if ( simple_list_isdouble(pVar,SIMPLE_VAR_VALUE) ) {
		if ( vm->nBeforeEqual == 1 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) + nNum1);
		} else if ( vm->nBeforeEqual == 2 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) - nNum1);
		} else if ( vm->nBeforeEqual == 3 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) * nNum1);
		} else if ( vm->nBeforeEqual == 4 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE ,simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) / nNum1);
		} else if ( vm->nBeforeEqual == 5 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , fmod(simple_list_getdouble(pVar,SIMPLE_VAR_VALUE), nNum1));
		} else if ( vm->nBeforeEqual == 6 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) & (int) nNum1);
		} else if ( vm->nBeforeEqual == 7 ) {
			simple_list_setdouble(pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) | (int) nNum1);
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) | (int) nNum1);
		} else if ( vm->nBeforeEqual == 8 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) ^ (int) nNum1);
		} else if ( vm->nBeforeEqual == 9 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) << (int) nNum1);
		} else if ( vm->nBeforeEqual == 10 ) {
			simple_list_setdouble_gc(vm->sState,pVar, SIMPLE_VAR_VALUE , (int) simple_list_getdouble(pVar,SIMPLE_VAR_VALUE) >> (int) nNum1);
		}
	}
	else if ( (simple_list_isstring(pVar,SIMPLE_VAR_VALUE) == 1) && (vm->nBeforeEqual == 1) ) {
		pString = simple_list_getstringobject(pVar,SIMPLE_VAR_VALUE);
		simple_string_add_gc(vm->sState,pString,simple_vm_numtostring(vm,nNum1,cStr));
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_beforeequalitem ( VM *vm,Item *pItem,double nNum1 )
{
	String *pString  ;
	char cStr[100]  ;
	if ( simple_item_isdouble(pItem) ) {
		if ( vm->nBeforeEqual == 1 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,simple_item_getdouble(pItem) + nNum1);
		} else if ( vm->nBeforeEqual == 2 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,simple_item_getdouble(pItem) - nNum1);
		} else if ( vm->nBeforeEqual == 3 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,simple_item_getdouble(pItem) * nNum1);
		} else if ( vm->nBeforeEqual == 4 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,simple_item_getdouble(pItem) / nNum1);
		} else if ( vm->nBeforeEqual == 5 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,fmod(simple_item_getdouble(pItem) , nNum1));
		} else if ( vm->nBeforeEqual == 6 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,(int) simple_item_getdouble(pItem) & (int) nNum1);
		} else if ( vm->nBeforeEqual == 7 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,(int) simple_item_getdouble(pItem) | (int) nNum1);
		} else if ( vm->nBeforeEqual == 8 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,(int) simple_item_getdouble(pItem) ^ (int) nNum1);
		} else if ( vm->nBeforeEqual == 9 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,(int) simple_item_getdouble(pItem) << (int) nNum1);
		} else if ( vm->nBeforeEqual == 10 ) {
			simple_item_setdouble_gc(vm->sState,pItem ,(int) simple_item_getdouble(pItem) >> (int) nNum1);
		}
	}
	else if ( (simple_item_isstring(pItem) == 1)  && (vm->nBeforeEqual == 1) ) {
		pString = simple_item_getstring(pItem);
		simple_string_add_gc(vm->sState,pString,simple_vm_numtostring(vm,nNum1,cStr));
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_plusplus ( VM *vm )
{
	List *list  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			list = (List *) SIMPLE_VM_STACK_READP ;
			if ( simple_list_isdouble(list,SIMPLE_VAR_VALUE) ) {
				simple_list_setdouble_gc(vm->sState,list,SIMPLE_VAR_VALUE,simple_list_getdouble(list,SIMPLE_VAR_VALUE)+1);
				return ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			if ( simple_item_isdouble(pItem) ) {
				simple_item_setdouble_gc(vm->sState,pItem,simple_item_getdouble(pItem)+1);
				return ;
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(SIMPLE_VM_STACK_READN + 1);
		return ;
	}
	simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
}

void simple_vm_minusminus ( VM *vm )
{
	List *list  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			list = (List *) SIMPLE_VM_STACK_READP ;
			if ( simple_list_isdouble(list,SIMPLE_VAR_VALUE) ) {
				simple_list_setdouble_gc(vm->sState,list,SIMPLE_VAR_VALUE,simple_list_getdouble(list,SIMPLE_VAR_VALUE)-1);
				return ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			if ( simple_item_isdouble(pItem) ) {
				simple_item_setdouble_gc(vm->sState,pItem,simple_item_getdouble(pItem)-1);
				return ;
			}
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(SIMPLE_VM_STACK_READN - 1);
		return ;
	}
	simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
}

void simple_vm_assignmentpointer ( VM *vm )
{
	List *list, *list2  ;
	Item *pItem  ;
	int x  ;
	if ( vm->nNOAssignment == 0 ) {
		vm->pAssignment = SIMPLE_VM_STACK_READP ;
		/* Check trying to change the self pointer */
		list = NULL ;
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			if ( simple_list_islist((List *) vm->pAssignment,SIMPLE_VAR_VALUE) ) {
				list = simple_list_getlist((List *) vm->pAssignment,SIMPLE_VAR_VALUE) ;
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) vm->pAssignment ;
			if ( simple_item_gettype(pItem) == ITEMTYPE_LIST ) {
				list = simple_item_getlist(pItem) ;
			}
			else {
				return ;
			}
		}
		else {
			return ;
		}
		if ( simple_vm_oop_isobject(list)  && (simple_list_getsize(vm->pObjState) > 0 ) ) {
			/* We loop to prevent passing self to function that destory the self */
			for ( x = 1 ; x <= simple_list_getsize(vm->pObjState) ; x++ ) {
				list2 = simple_list_getlist(vm->pObjState,x);
				if ( simple_list_getpointer(list,SIMPLE_OBJECT_OBJECTDATA) == simple_list_getpointer(list2,SIMPLE_OBJSTATE_SCOPE) ) {
					simple_vm_error(vm,SIMPLE_VM_ERROR_TRYINGTOMODIFYTHESELFPOINTER);
					return ;
				}
			}
		}
	}
	else {
		vm->nNOAssignment = 0 ;
	}
}

void simple_vm_freeloadaddressscope ( VM *vm )
{
	/* Clear Load Address Result Scope Array */
	simple_list_deleteallitems_gc(vm->sState,vm->aLoadAddressScope);
}
