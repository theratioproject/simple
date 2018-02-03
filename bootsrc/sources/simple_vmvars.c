
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
/*
**  Variables 
**  Memory is a List and each item inside the list is another List (Represent Scope) 
**  The Variable is a List contains ( Name , Type , Value , [Pointer Type] ) 
**  When we find varaible or create new varaible we push variable pointer to the stack 
*/

void simple_vm_newscope ( VM *pVM )
{
	pVM->pActiveMem = simple_list_newlist_gc(pVM->pRingState,pVM->pMem);
	/* Save Local Scope Information */
	pVM->nScopeID++ ;
	simple_list_addint_gc(pVM->pRingState,pVM->aScopeID,pVM->nScopeID);
	pVM->nActiveScopeID = pVM->nScopeID ;
}

int simple_vm_findvar ( VM *pVM,const char *cStr )
{
	int x,nPos,nMax1  ;
	List *pList,*pList2  ;
	assert(pVM->pMem);
	nMax1 = simple_list_getsize(pVM->pMem);
	/* The scope of the search result */
	pVM->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	if ( nMax1 > 0 ) {
		/* Loop to search in each Scope */
		for ( x = 1 ; x <= 3 ; x++ ) {
			/* 1 = last scope (function) , 2 = Object State , 3 = global scope */
			if ( x == 1 ) {
				pList = pVM->pActiveMem ;
			}
			else if ( x == 2 ) {
				/* IF obj.attribute - we did the search in local scope - pass others */
				if ( pVM->nGetSetProperty == 1 ) {
					continue ;
				}
				if ( simple_list_getsize(pVM->pObjState) == 0 ) {
					continue ;
				}
				/* Search in Object State */
				pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)) ;
				pList = (List *) simple_list_getpointer(pList,SIMPLE_OBJSTATE_SCOPE) ;
				if ( pList == NULL ) {
					continue ;
				}
				/* Pass Braces for Class Init() method */
				if ( (simple_list_getsize(pVM->pObjState) > pVM->nCallClassInit) && (pVM->nCallClassInit) ) {
					pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)-pVM->nCallClassInit) ;
					pList = (List *) simple_list_getpointer(pList,SIMPLE_OBJSTATE_SCOPE) ;
					if ( pList == NULL ) {
						continue ;
					}
				}
			} else {
				/* IF obj.attribute - we did the search in local scope - pass others */
				if ( pVM->nGetSetProperty == 1 ) {
					continue ;
				}
				pList = simple_vm_getglobalscope(pVM);
			}
			if ( simple_list_getsize(pList) < 10 ) {
				/* Search Using Linear Search */
				nPos = simple_list_findstring(pList,cStr,1);
				if ( nPos != 0 ) {
					if ( simple_list_islist(pList,nPos) ) {
						pList2 = simple_list_getlist(pList,nPos);
						return simple_vm_findvar2(pVM,x,pList2,cStr) ;
					}
				}
			}
			else {
				/* Search Using the HashTable */
				if ( pList->pHashTable == NULL ) {
					simple_list_genhashtable2_gc(pVM->pRingState,pList);
				}
				pList2 = (List *) simple_hashtable_findpointer(pList->pHashTable,cStr);
				if ( pList2 != NULL ) {
					return simple_vm_findvar2(pVM,x,pList2,cStr) ;
				}
			}
		}
	}
	return 0 ;
}

int simple_vm_findvar2 ( VM *pVM,int x,List *pList2,const char *cStr )
{
	int nPC,nType,lPrivateError  ;
	Item *pItem  ;
	List *pList, *pThis  ;
	/*
	**  Now We have the variable List 
	**  The Scope of the search result 
	*/
	if ( ( x == 1 ) && (pVM->pActiveMem == simple_vm_getglobalscope(pVM)) ) {
		x = SIMPLE_VARSCOPE_GLOBAL ;
	}
	else if ( (x == 1) && (pVM->pActiveMem != simple_list_getlist(pVM->pMem,simple_list_getsize(pVM->pMem))) ) {
		x = SIMPLE_VARSCOPE_NEWOBJSTATE ;
	}
	pVM->nVarScope = x ;
	pVM->nSP++ ;
	if ( simple_list_getint(pList2,SIMPLE_VAR_TYPE) == SIMPLE_VM_POINTER ) {
		if ( pVM->nFirstAddress  == 1 ) {
			SIMPLE_VM_STACK_SETPVALUE(pList2);
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
			return 1 ;
		}
		SIMPLE_VM_STACK_SETPVALUE(simple_list_getpointer(pList2,SIMPLE_VAR_VALUE ));
		SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(pList2,SIMPLE_VAR_PVALUETYPE) ;
		/*
		**  Here we don't know the correct scope of the result 
		**  becauase a global variable may be a reference to local variable 
		**  And this case happens with setter/getter of the attributes using executeCode() 
		**  Here we avoid this change if the variable name is "Self" to return self by reference 
		*/
		if ( strcmp(cStr,"self") != 0 ) {
			pVM->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
		}
	} else {
		/* Check Private Attributes */
		if ( simple_list_getint(pList2,SIMPLE_VAR_PRIVATEFLAG) == 1 ) {
			/* We check that we are not in the class region too (defining the private attribute then reusing it) */
			if ( ! ( (pVM->nVarScope == SIMPLE_VARSCOPE_NEWOBJSTATE) &&  (pVM->nInClassRegion == 1) ) ) {
				if ( simple_vm_oop_callmethodinsideclass(pVM) == 0 ) {
					lPrivateError = 1 ;
					/* Pass Braces for Class Init() to be sure we are inside a method or not */
					if ( (simple_list_getsize(pVM->pObjState) > pVM->nCallClassInit) && (pVM->nCallClassInit) ) {
						pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState) - pVM->nCallClassInit) ;
						if ( (simple_list_getsize(pList) == 4) && (pVM->nCallMethod == 0) ) {
							/* Here we have a method, So we avoid the private attribute error! */
							lPrivateError = 0 ;
						}
					}
					if ( lPrivateError ) {
						simple_vm_error2(pVM,SIMPLE_VM_ERROR_USINGPRIVATEATTRIBUTE,cStr);
						return 0 ;
					}
				}
			}
		}
		SIMPLE_VM_STACK_SETPVALUE(pList2);
		SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
		/* Check Setter/Getter for Public Attributes */
		if ( pVM->nGetSetProperty == 1 ) {
			/* Avoid executing Setter/Getter when we use self.attribute and this.attribute */
			pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
			if ( pThis != NULL ) {
				if ( simple_list_getpointer(pThis,SIMPLE_VAR_VALUE ) == pVM->pGetSetObject ) {
					return 1 ;
				}
			}
			simple_vm_oop_setget(pVM,pList2);
		}
		else if ( ( x == SIMPLE_VARSCOPE_OBJSTATE ) && ( simple_vm_oop_callmethodinsideclass(pVM) == 0 ) ) {
			/* Accessing Object Attribute Using { } */
			if ( simple_list_getsize(pVM->aBraceObjects) > 0 ) {
				pList = simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects));
				/* Pass braces { } for class init() method */
				if ( pVM->nCallClassInit ) {
					/*
					**  Here simple_vm_oop_callmethodinsideclass(pVM) will return 0 because of class init() calling 
					**  This check can be done here or in simple_vm_oop_callmethodinsideclass() 
					*/
					return 1 ;
				}
				/* Get Object List */
				pList = (List *) simple_list_getpointer(pList,SIMPLE_ABRACEOBJECTS_BRACEOBJECT);
				nType = simple_vm_oop_objtypefromobjlist(pList);
				/* Set Object Pointer & Type */
				if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
					pList = simple_vm_oop_objvarfromobjlist(pList);
					pVM->pGetSetObject = pList ;
				}
				else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
					pItem = simple_vm_oop_objitemfromobjlist(pList);
					pVM->pGetSetObject = pItem ;
				}
				pVM->nGetSetObjType = nType ;
				/* Change Assignment Instruction to SetProperty */
				if ( SIMPLE_VM_IR_PARACOUNT >= 4 ) {
					if ( SIMPLE_VM_IR_READIVALUE(3) != 0 ) {
						nPC = pVM->nPC ;
						pVM->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
						SIMPLE_VM_IR_LOAD ;
						SIMPLE_VM_IR_OPCODE = ICO_SETPROPERTY ;
						pVM->nPC = nPC ;
						SIMPLE_VM_IR_UNLOAD ;
						/* Avoid AssignmentPointer , we don't have assignment */
						pVM->nNOAssignment = 1 ;
					}
				}
				simple_vm_oop_setget(pVM,pList2);
			}
		}
	}
	return 1 ;
}

void simple_vm_newvar ( VM *pVM,const char *cStr )
{
	List *pList  ;
	assert(pVM->pActiveMem);
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	pVM->nSP++ ;
	SIMPLE_VM_STACK_SETPVALUE(pList);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Set the scope of the new variable */
	if ( (simple_list_getsize(pVM->pMem) == 1) && (pVM->pActiveMem == simple_list_getlist(pVM->pMem,SIMPLE_MEMORY_GLOBALSCOPE)) ) {
		pVM->nVarScope = SIMPLE_VARSCOPE_GLOBAL ;
	}
	else if ( pVM->pActiveMem == simple_list_getlist(pVM->pMem,simple_list_getsize(pVM->pMem)) ) {
		pVM->nVarScope = SIMPLE_VARSCOPE_LOCAL ;
	} else {
		pVM->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	}
	/* Add Scope to aLoadAddressScope */
	simple_list_addint_gc(pVM->pRingState,pVM->aLoadAddressScope,pVM->nVarScope);
}

List * simple_vm_newvar2 ( VM *pVM,const char *cStr,List *pParent )
{
	List *pList  ;
	/* This function is called by all of the other functions that create new varaibles */
	pList = simple_list_newlist_gc(pVM->pRingState,pParent);
	simple_list_addstsimple_gc(pVM->pRingState,pList,cStr);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_NULL);
	simple_list_addstsimple_gc(pVM->pRingState,pList,"NULL");
	/* Pointer Type */
	simple_list_addint_gc(pVM->pRingState,pList,0);
	/* Private Flag */
	simple_list_addint_gc(pVM->pRingState,pList,0);
	/* Add Pointer to the HashTable */
	if ( pParent->pHashTable == NULL ) {
		pParent->pHashTable = simple_hashtable_new();
	}
	simple_hashtable_newpointer(pParent->pHashTable,cStr,pList);
	return pList ;
}

void simple_vm_addnewnumbervar ( VM *pVM,const char *cStr,double x )
{
	List *pList  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
	simple_list_setdouble_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,x);
}

void simple_vm_addnewstringvar ( VM *pVM,const char *cStr,const char *cStr2 )
{
	List *pList  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
	simple_list_setstsimple_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,cStr2);
}

void simple_vm_addnewstringvar2 ( VM *pVM,const char *cStr,const char *cStr2,int nStrSize )
{
	List *pList  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
	simple_list_setstring2_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,cStr2,nStrSize);
}

void simple_vm_addnewpointervar ( VM *pVM,const char *cStr,void *x,int y )
{
	List *pList  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
	simple_list_setpointer_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,x);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_PVALUETYPE,y);
	/* Reference Counting */
	simple_vm_gc_checknewreference(x,y);
}

void simple_vm_newtempvar ( VM *pVM,const char *cStr, List *TempList )
{
	List *pList  ;
	pList = simple_vm_newvar2(pVM,cStr,TempList);
	pVM->nSP++ ;
	SIMPLE_VM_STACK_SETPVALUE(pList);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
}

List * simple_vm_newtempvar2 ( VM *pVM,const char *cStr,List *pList3 )
{
	List *pList,*pList2  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pTempMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE);
	pList2 = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	simple_list_deleteallitems_gc(pVM->pRingState,pList2);
	simple_list_copy(pList2,pList3);
	return pList ;
}

void simple_vm_addnewcpointervar ( VM *pVM,const char *cStr,void *pPointer,const char *cStr2 )
{
	List *pList, *pList2  ;
	pList = simple_vm_newvar2(pVM,cStr,pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE);
	pList2 = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	/* Add Pointer */
	simple_list_addpointer_gc(pVM->pRingState,pList2,pPointer);
	/* Add Type */
	simple_list_addstsimple_gc(pVM->pRingState,pList2,cStr2);
	/* Add Status Number */
	simple_list_addint_gc(pVM->pRingState,pList2,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
}

void simple_vm_deletescope ( VM *pVM )
{
	if ( simple_list_getsize(pVM->pMem) < 2 ) {
		printf( SIMPLE_NOSCOPE ) ;
		exit(0);
	}
	/* Check References */
	simple_vm_gc_checkreferences(pVM);
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pMem,simple_list_getsize(pVM->pMem));
	pVM->pActiveMem = simple_list_getlist(pVM->pMem,simple_list_getsize(pVM->pMem));
	/* Delete Local Scope information */
	simple_list_deleteitem_gc(pVM->pRingState,pVM->aScopeID,simple_list_getsize(pVM->aScopeID));
	pVM->nActiveScopeID = simple_list_getint(pVM->aScopeID,simple_list_getsize(pVM->aScopeID)) ;
}
/* Custom Global Scope */

void simple_vm_newglobalscope ( VM *pVM )
{
	pVM->pActiveMem = simple_list_newlist_gc(pVM->pRingState,pVM->aGlobalScopes);
	simple_list_addpointer_gc(pVM->pRingState,pVM->aActiveGlobalScopes,pVM->pActiveMem);
	simple_vm_addglobalvariables(pVM);
}

void simple_vm_endglobalscope ( VM *pVM )
{
	simple_list_deletelastitem_gc(pVM->pRingState,pVM->aActiveGlobalScopes);
	if ( simple_list_getsize(pVM->aActiveGlobalScopes) == 0 ) {
		pVM->pActiveMem = simple_list_getlist(pVM->pMem,1);
	}
	else {
		pVM->pActiveMem = (List *) simple_list_getpointer(pVM->aActiveGlobalScopes,simple_list_getsize(pVM->aActiveGlobalScopes));
	}
}

void simple_vm_setglobalscope ( VM *pVM )
{
	pVM->nCurrentGlobalScope = SIMPLE_VM_IR_READI ;
}

List * simple_vm_getglobalscope ( VM *pVM )
{
	List *pList  ;
	if ( pVM->nCurrentGlobalScope == 0 ) {
		pList = simple_list_getlist(pVM->pMem,1);
	}
	else {
		pList = simple_list_getlist(pVM->aGlobalScopes,pVM->nCurrentGlobalScope);
	}
	return pList ;
}
