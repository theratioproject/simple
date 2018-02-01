/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Lists */

void simple_vm_liststart ( VM *pVM )
{
	List *pVar,*pList  ;
	int nType  ;
	Item *pItem  ;
	int nCont  ;
	pVar = NULL ;
	pItem = NULL ;
	pVM->nListStart++ ;
	if ( pVM->nListStart == 1 ) {
		/* Check if we need to create temp list when we call function, pass list by value */
		nCont = 0 ;
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			if ( pVM->pAssignment != SIMPLE_VM_STACK_READP ) {
				nCont = 1 ;
			}
			else {
				/* Be Sure that we are modifying Object Attribute (Not Global/Local Variable) */
				if ( pVM->nVarScope == SIMPLE_VARSCOPE_NEWOBJSTATE ) {
					/*
					**  When we access object attribute from braces then create temp. variable for set property operation 
					**  We do this if we are not inside the class region (after the class name where we define attributes) 
					*/
					if ( (simple_list_getsize(pVM->aBraceObjects) > 0) && ( ! simple_vm_oop_callmethodinsideclass(pVM)) && (! pVM->nInClassRegion) ) {
						nCont = 1 ;
					}
				}
			}
		}
		if ( (pVM->nFuncExecute > 0)  || ( nCont == 1 ) ) {
			if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
				simple_vm_createtemplist(pVM);
			} else {
				/* Create the list in the General Temp Memory */
				simple_vm_newtempvar(pVM, SIMPLE_TEMP_VARIABLE ,pVM->pTempMem);
			}
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			nType = SIMPLE_VM_STACK_OBJTYPE ;
			/* Set the Address Scope As Local */
			simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_LOCAL);
		} else {
			if ( SIMPLE_VM_STACK_ISPOINTER == 0 ) {
				/* Create the List in Global Temp Memory. */
				simple_vm_newtempvar(pVM, SIMPLE_TEMP_VARIABLE ,pVM->pTempMem);
				simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,SIMPLE_VARSCOPE_LOCAL);
			}
			nType = SIMPLE_VM_STACK_OBJTYPE ;
			if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
				pItem = (Item *) SIMPLE_VM_STACK_READP ;
			} else {
				pVar = (List *) SIMPLE_VM_STACK_READP ;
			}
			SIMPLE_VM_STACK_POP ;
		}
		if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
			simple_list_setint_gc(pVM->pRingState,pVar, SIMPLE_VAR_TYPE ,SIMPLE_VM_LIST);
			simple_list_setlist_gc(pVM->pRingState,pVar, SIMPLE_VAR_VALUE);
			simple_list_deleteallitems_gc(pVM->pRingState,simple_list_getlist(pVar,SIMPLE_VAR_VALUE));
			simple_list_addpointer_gc(pVM->pRingState,pVM->pNestedLists,simple_list_getlist(pVar,SIMPLE_VAR_VALUE));
		}
		else if ( (nType == SIMPLE_OBJTYPE_LISTITEM) && (pItem != NULL) ) {
			simple_item_settype_gc(pVM->pRingState,pItem,ITEMTYPE_LIST);
			pVar = simple_item_getlist(pItem);
			simple_list_deleteallitems_gc(pVM->pRingState,pVar);
			simple_list_addpointer_gc(pVM->pRingState,pVM->pNestedLists,pVar);
		}
	} else {
		pList = (List *) simple_list_getpointer(pVM->pNestedLists,simple_list_getsize(pVM->pNestedLists));
		simple_list_addpointer_gc(pVM->pRingState,pVM->pNestedLists,simple_list_newlist_gc(pVM->pRingState,pList));
	}
}

void simple_vm_listitem ( VM *pVM )
{
	String *cStr1  ;
	double nNum1  ;
	List *pList,*pList2,*pList3  ;
	Item *pItem  ;
	pList = (List *) simple_list_getpointer(pVM->pNestedLists,simple_list_getsize(pVM->pNestedLists));
	if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		simple_list_addstsimple_gc(pVM->pRingState,pList, simple_stsimple_get(cStr1));
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		simple_list_adddouble_gc(pVM->pRingState,pList, nNum1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pList2 = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			pList2 = simple_list_getlist(pList2,SIMPLE_VAR_VALUE);
			pList3 = simple_list_newlist_gc(pVM->pRingState,pList);
			simple_list_copy(pList3,pList2);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			pList2 = simple_item_getlist(pItem);
			pList3 = simple_list_newlist_gc(pVM->pRingState,pList);
			simple_list_copy(pList3,pList2);
		}
	}
}

void simple_vm_listend ( VM *pVM )
{
	pVM->nListStart-- ;
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pNestedLists,simple_list_getsize(pVM->pNestedLists));
}

void simple_vm_loadindexaddress ( VM *pVM )
{
	double nNum1  ;
	List *pVar  ;
	Item *pItem  ;
	char cStr2[2]  ;
	String *pString  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
				pVar = (List *) SIMPLE_VM_STACK_READP ;
				if ( simple_list_islist(pVar,SIMPLE_VAR_VALUE) ) {
					pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
					/* Check that it's list not object */
					if ( simple_vm_oop_isobject(pVar) == 1 ) {
						simple_vm_expr_npoo(pVM,"[]",nNum1);
						return ;
					}
					SIMPLE_VM_STACK_POP ;
					if ( nNum1 < 1 || nNum1 > simple_list_getsize(pVar) ) {
						simple_vm_error(pVM,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
						return ;
					}
					pItem = simple_list_getitem(pVar,nNum1);
					SIMPLE_VM_STACK_PUSHPVALUE(pItem);
				}
				else if ( simple_list_isstring(pVar,SIMPLE_VAR_VALUE) ) {
					SIMPLE_VM_STACK_POP ;
					if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
						simple_vm_error(pVM,SIMPLE_VM_ERROR_USINGNULLVARIABLE);
						return ;
					}
					pString = simple_list_getstringobject(pVar,SIMPLE_VAR_VALUE) ;
					simple_vm_stsimple_index(pVM,pString,nNum1);
					return ;
				} else {
					SIMPLE_VM_STACK_POP ;
					simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
					return ;
				}
			}
			else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
				pItem = (Item *) SIMPLE_VM_STACK_READP ;
				if ( simple_item_islist(pItem) ) {
					pVar = simple_item_getlist(pItem);
					/* Check that it's list not object */
					if ( simple_vm_oop_isobject(pVar) == 1 ) {
						simple_vm_expr_npoo(pVM,"[]",nNum1);
						return ;
					}
					SIMPLE_VM_STACK_POP ;
					if ( nNum1 < 1 || nNum1 > simple_list_getsize(pVar) ) {
						simple_vm_error(pVM,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
						return ;
					}
					pItem = simple_list_getitem(pVar,nNum1);
					SIMPLE_VM_STACK_PUSHPVALUE(pItem);
				}
				else if ( simple_item_isstring(pItem) ) {
					SIMPLE_VM_STACK_POP ;
					pString = simple_item_getstring(pItem);
					simple_vm_stsimple_index(pVM,pString,nNum1);
					return ;
				} else {
					SIMPLE_VM_STACK_POP ;
					simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
					return ;
				}
			} else {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
				return ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2[0] = SIMPLE_VM_STACK_READC[((int) nNum1)-1] ;
			cStr2[1] = '\0' ;
			SIMPLE_VM_STACK_SETCVALUE(cStr2);
			return ;
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
			return ;
		}
		SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		pString = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		/* Use String to find the item */
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
				pVar = (List *) SIMPLE_VM_STACK_READP ;
				SIMPLE_VM_STACK_POP ;
				if ( simple_list_islist(pVar,SIMPLE_VAR_VALUE) ) {
					pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
					/* Check that it's list not object */
					if ( simple_vm_oop_isobject(pVar) == 1 ) {
						pVM->nSP++ ;
						simple_vm_expr_spoo(pVM,"[]",simple_stsimple_get(pString),simple_stsimple_size(pString));
						return ;
					}
					simple_vm_listgetvalue(pVM,pVar,simple_stsimple_get(pString));
				} else {
					simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
				}
			}
			else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
				pItem = (Item *) SIMPLE_VM_STACK_READP ;
				SIMPLE_VM_STACK_POP ;
				if ( simple_item_islist(pItem) ) {
					pVar = simple_item_getlist(pItem);
					/* Check that it's list not object */
					if ( simple_vm_oop_isobject(pVar) == 1 ) {
						pVM->nSP++ ;
						simple_vm_expr_spoo(pVM,"[]",simple_stsimple_get(pString),simple_stsimple_size(pString));
						return ;
					}
					simple_vm_listgetvalue(pVM,pVar,simple_stsimple_get(pString));
				} else {
					simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
				}
			} else {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
			}
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_OBJECTISNOTLIST);
			/* Don't return here, we need to delete the string to avoid memory leak */
		}
		simple_stsimple_delete_gc(pVM->pRingState,pString);
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
	}
}

void simple_vm_listpushv ( VM *pVM )
{
	Item *pItem  ;
	pItem = (Item *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	/* Push Item Data */
	if ( simple_item_gettype(pItem) == ITEMTYPE_STSIMPLE ) {
		if ( (pVM->nRetItemRef>=1)  && (simple_vm_isstackpointertoobjstate(pVM)==1) ) {
			SIMPLE_VM_STACK_PUSHPVALUE(pItem);
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
			pVM->nRetItemRef-- ;
			return ;
		}
		pVM->nSP++ ;
		SIMPLE_VM_STACK_SETCVALUE2(simple_stsimple_get(simple_item_getstring(pItem)),simple_stsimple_size(simple_item_getstring(pItem)));
	}
	else if ( simple_item_gettype(pItem) == ITEMTYPE_NUMBER ) {
		if ( (pVM->nRetItemRef>=1)  && (simple_vm_isstackpointertoobjstate(pVM)==1) ) {
			SIMPLE_VM_STACK_PUSHPVALUE(pItem);
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
			pVM->nRetItemRef-- ;
			return ;
		}
		SIMPLE_VM_STACK_PUSHNVALUE(simple_item_getnumber(pItem));
	}
	else if ( simple_item_gettype(pItem) == ITEMTYPE_LIST ) {
		if ( (pVM->nRetItemRef>=1)  && (simple_vm_isstackpointertoobjstate(pVM)==1) ) {
			pVM->nRetItemRef-- ;
		}
		SIMPLE_VM_STACK_PUSHPVALUE(pItem);
		SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
		simple_vm_oop_setbraceobj(pVM, (List *) simple_item_getlist(pItem));
	}
}

void simple_vm_listassignment ( VM *pVM )
{
	Item *pItem  ;
	String *cStr1, *pString  ;
	double nNum1  ;
	List *pList,*pVar  ;
	pVar = NULL ;
	if ( (SIMPLE_VM_STACK_ISSTSIMPLE) && (pVM->nBeforeEqual <= 1) ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		assert(cStr1 != NULL);
		SIMPLE_VM_STACK_POP ;
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		assert(pItem != NULL);
		SIMPLE_VM_STACK_POP ;
		if ( pVM->nBeforeEqual == 0 ) {
			simple_item_setstsimple_gc(pVM->pRingState,pItem, simple_stsimple_get(cStr1));
		} else {
			if ( simple_item_isstring(pItem) ) {
				pString = simple_item_getstring(pItem);
				simple_stsimple_add_gc(pVM->pRingState,pString,simple_stsimple_get(cStr1));
			}
			else if ( simple_item_isdouble(pItem) ) {
				simple_item_setdouble_gc(pVM->pRingState,pItem,simple_item_getdouble(pItem)+simple_vm_stringtonum(pVM,simple_stsimple_get(cStr1)));
			}
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		assert(pItem != NULL);
		SIMPLE_VM_STACK_POP ;
		if ( pVM->nBeforeEqual == 0 ) {
			simple_item_setdouble_gc(pVM->pRingState,pItem , nNum1);
		} else {
			simple_vm_beforeequalitem(pVM,pItem,nNum1);
		}
	}
	else if ( (SIMPLE_VM_STACK_ISPOINTER) && (pVM->nBeforeEqual == 0) ) {
		/* Get Source */
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			pVar = simple_item_getlist(pItem);
		}
		SIMPLE_VM_STACK_POP ;
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		SIMPLE_VM_STACK_POP ;
		simple_item_settype_gc(pVM->pRingState,pItem,ITEMTYPE_LIST);
		pList = simple_item_getlist(pItem);
		simple_list_deleteallitems_gc(pVM->pRingState,pList);
		simple_vm_list_copy(pVM,pList,pVar);
		/* Update self object Pointer */
		if ( simple_vm_oop_isobject(pList) ) {
			simple_vm_oop_updateselfpointer(pVM,pList,SIMPLE_OBJTYPE_LISTITEM,pItem);
		}
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
	}
}

void simple_vm_listgetvalue ( VM *pVM,List *pVar,const char *cStr )
{
	int x  ;
	List *pList  ;
	Item *pItem  ;
	const char *cStr2  ;
	if ( simple_list_getsize(pVar) > 0 ) {
		for ( x = 1 ; x <= simple_list_getsize(pVar) ; x++ ) {
			if ( simple_list_islist(pVar,x) ) {
				pList = simple_list_getlist(pVar,x);
				if ( simple_list_getsize(pList)  >= SIMPLE_LISTHASH_SIZE ) {
					if ( simple_list_isstring(pList,SIMPLE_LISTHASH_KEY) ) {
						cStr2 = simple_list_getstring(pList,SIMPLE_LISTHASH_KEY);
						if ( simple_vm_strcmpnotcasesensitive(cStr,cStr2)  == 0 ) {
							pItem = simple_list_getitem(pList,SIMPLE_LISTHASH_VALUE);
							SIMPLE_VM_STACK_PUSHPVALUE(pItem);
							SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
							return ;
						}
					}
				}
			}
		}
	}
	/* Add Item if not found */
	pList = simple_list_newlist_gc(pVM->pRingState,pVar);
	simple_list_addstsimple_gc(pVM->pRingState,pList,cStr);
	simple_list_addstsimple_gc(pVM->pRingState,pList,"");
	pItem = simple_list_getitem(pList,SIMPLE_LISTHASH_VALUE);
	SIMPLE_VM_STACK_PUSHPVALUE(pItem);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;
}

int simple_vm_strcmpnotcasesensitive ( const char *cStr1,const char *cStr2 )
{
	int nNum1  ;
	while ( 1 ) {
		nNum1 = tolower(*cStr1) - tolower(*cStr2) ;
		if ( nNum1 != 0 || !*cStr1 || !*cStr2 ) {
			return nNum1 ;
		}
		cStr1++ ;
		cStr2++ ;
	}
}
