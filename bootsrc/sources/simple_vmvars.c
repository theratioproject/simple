
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

void simple_vm_newscope ( VM *vm )
{
	vm->pActiveMem = simple_list_newlist_gc(vm->sState,vm->pMem);
	/* Save Local Scope Information */
	vm->nScopeID++ ;
	simple_list_addint_gc(vm->sState,vm->aScopeID,vm->nScopeID);
	vm->nActiveScopeID = vm->nScopeID ;
}

int simple_vm_findvar ( VM *vm,const char *cStr )
{
	int x,nPos,nMax1  ;
	List *list,*list2  ;
	assert(vm->pMem);
	nMax1 = simple_list_getsize(vm->pMem);
	/* The scope of the search result */
	vm->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	if ( nMax1 > 0 ) {
		/* Loop to search in each Scope */
		for ( x = 1 ; x <= 3 ; x++ ) {
			/* 1 = last scope (function) , 2 = Object State , 3 = global scope */
			if ( x == 1 ) {
				list = vm->pActiveMem ;
			}
			else if ( x == 2 ) {
				/* IF obj.attribute - we did the search in local scope - pass others */
				if ( vm->nGetSetProperty == 1 ) {
					continue ;
				}
				if ( simple_list_getsize(vm->pObjState) == 0 ) {
					continue ;
				}
				/* Search in Object State */
				list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)) ;
				list = (List *) simple_list_getpointer(list,SIMPLE_OBJSTATE_SCOPE) ;
				if ( list == NULL ) {
					continue ;
				}
				/* Pass Braces for Class Init() method */
				if ( (simple_list_getsize(vm->pObjState) > vm->nCallClassInit) && (vm->nCallClassInit) ) {
					list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)-vm->nCallClassInit) ;
					list = (List *) simple_list_getpointer(list,SIMPLE_OBJSTATE_SCOPE) ;
					if ( list == NULL ) {
						continue ;
					}
				}
			} else {
				/* IF obj.attribute - we did the search in local scope - pass others */
				if ( vm->nGetSetProperty == 1 ) {
					continue ;
				}
				list = simple_vm_getglobalscope(vm);
			}
			if ( simple_list_getsize(list) < 10 ) {
				/* Search Using Linear Search */
				nPos = simple_list_findstring(list,cStr,1);
				if ( nPos != 0 ) {
					if ( simple_list_islist(list,nPos) ) {
						list2 = simple_list_getlist(list,nPos);
						return simple_vm_findvar2(vm,x,list2,cStr) ;
					}
				}
			}
			else {
				/* Search Using the HashTable */
				if ( list->pHashTable == NULL ) {
					simple_list_genhashtable2_gc(vm->sState,list);
				}
				list2 = (List *) simple_hashtable_findpointer(list->pHashTable,cStr);
				if ( list2 != NULL ) {
					return simple_vm_findvar2(vm,x,list2,cStr) ;
				}
			}
		}
	}
	return 0 ;
}

int simple_vm_findvar2 ( VM *vm,int x,List *list2,const char *cStr )
{
	int nPC,nType,lPrivateError  ;
	Item *pItem  ;
	List *list, *pThis  ;
	/*
	**  Now We have the variable List 
	**  The Scope of the search result 
	*/
	if ( ( x == 1 ) && (vm->pActiveMem == simple_vm_getglobalscope(vm)) ) {
		x = SIMPLE_VARSCOPE_GLOBAL ;
	}
	else if ( (x == 1) && (vm->pActiveMem != simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem))) ) {
		x = SIMPLE_VARSCOPE_NEWOBJSTATE ;
	}
	vm->nVarScope = x ;
	vm->nSP++ ;
	if ( simple_list_getint(list2,SIMPLE_VAR_TYPE) == SIMPLE_VM_POINTER ) {
		if ( vm->nFirstAddress  == 1 ) {
			SIMPLE_VM_STACK_SETPVALUE(list2);
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
			return 1 ;
		}
		SIMPLE_VM_STACK_SETPVALUE(simple_list_getpointer(list2,SIMPLE_VAR_VALUE ));
		SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(list2,SIMPLE_VAR_PVALUETYPE) ;
		/*
		**  Here we don't know the correct scope of the result 
		**  becauase a global variable may be a reference to local variable 
		**  And this case happens with setter/getter of the attributes using executeCode() 
		**  Here we avoid this change if the variable name is "Self" to return self by reference 
		*/
		if ( strcmp(cStr,"self") != 0 ) {
			vm->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
		}
	} else {
		/* Check Private Attributes */
		if ( simple_list_getint(list2,SIMPLE_VAR_PRIVATEFLAG) == 1 ) {
			/* We check that we are not in the class region too (defining the private attribute then reusing it) */
			if ( ! ( (vm->nVarScope == SIMPLE_VARSCOPE_NEWOBJSTATE) &&  (vm->nInClassRegion == 1) ) ) {
				if ( simple_vm_oop_callmethodinsideclass(vm) == 0 ) {
					lPrivateError = 1 ;
					/* Pass Braces for Class Init() to be sure we are inside a method or not */
					if ( (simple_list_getsize(vm->pObjState) > vm->nCallClassInit) && (vm->nCallClassInit) ) {
						list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState) - vm->nCallClassInit) ;
						if ( (simple_list_getsize(list) == 4) && (vm->nCallMethod == 0) ) {
							/* Here we have a method, So we avoid the private attribute error! */
							lPrivateError = 0 ;
						}
					}
					if ( lPrivateError ) {
						simple_vm_error2(vm,SIMPLE_VM_ERROR_USINGPRIVATEATTRIBUTE,cStr);
						return 0 ;
					}
				}
			}
		}
		SIMPLE_VM_STACK_SETPVALUE(list2);
		SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
		/* Check Setter/Getter for Public Attributes */
		if ( vm->nGetSetProperty == 1 ) {
			/* Avoid executing Setter/Getter when we use self.attribute and this.attribute */
			pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
			if ( pThis != NULL ) {
				if ( simple_list_getpointer(pThis,SIMPLE_VAR_VALUE ) == vm->pGetSetObject ) {
					return 1 ;
				}
			}
			simple_vm_oop_setget(vm,list2);
		}
		else if ( ( x == SIMPLE_VARSCOPE_OBJSTATE ) && ( simple_vm_oop_callmethodinsideclass(vm) == 0 ) ) {
			/* Accessing Object Attribute Using { } */
			if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
				list = simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects));
				/* Pass braces { } for class init() method */
				if ( vm->nCallClassInit ) {
					/*
					**  Here simple_vm_oop_callmethodinsideclass(vm) will return 0 because of class init() calling 
					**  This check can be done here or in simple_vm_oop_callmethodinsideclass() 
					*/
					return 1 ;
				}
				/* Get Object List */
				list = (List *) simple_list_getpointer(list,SIMPLE_ABRACEOBJECTS_BRACEOBJECT);
				nType = simple_vm_oop_objtypefromobjlist(list);
				/* Set Object Pointer & Type */
				if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
					list = simple_vm_oop_objvarfromobjlist(list);
					vm->pGetSetObject = list ;
				}
				else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
					pItem = simple_vm_oop_objitemfromobjlist(list);
					vm->pGetSetObject = pItem ;
				}
				vm->nGetSetObjType = nType ;
				/* Change Assignment Instruction to SetProperty */
				if ( SIMPLE_VM_IR_PARACOUNT >= 4 ) {
					if ( SIMPLE_VM_IR_READIVALUE(3) != 0 ) {
						nPC = vm->nPC ;
						vm->nPC = SIMPLE_VM_IR_READIVALUE(3) ;
						SIMPLE_VM_IR_LOAD ;
						SIMPLE_VM_IR_OPCODE = ICO_SETPROPERTY ;
						vm->nPC = nPC ;
						SIMPLE_VM_IR_UNLOAD ;
						/* Avoid AssignmentPointer , we don't have assignment */
						vm->nNOAssignment = 1 ;
					}
				}
				simple_vm_oop_setget(vm,list2);
			}
		}
	}
	return 1 ;
}

void simple_vm_newvar ( VM *vm,const char *cStr )
{
	List *list  ;
	assert(vm->pActiveMem);
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	vm->nSP++ ;
	SIMPLE_VM_STACK_SETPVALUE(list);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
	/* Set the scope of the new variable */
	if ( (simple_list_getsize(vm->pMem) == 1) && (vm->pActiveMem == simple_list_getlist(vm->pMem,SIMPLE_MEMORY_GLOBALSCOPE)) ) {
		vm->nVarScope = SIMPLE_VARSCOPE_GLOBAL ;
	}
	else if ( vm->pActiveMem == simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)) ) {
		vm->nVarScope = SIMPLE_VARSCOPE_LOCAL ;
	} else {
		vm->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	}
	/* Add Scope to aLoadAddressScope */
	simple_list_addint_gc(vm->sState,vm->aLoadAddressScope,vm->nVarScope);
}

List * simple_vm_newvar2 ( VM *vm,const char *cStr,List *pParent )
{
	List *list  ;
	/* This function is called by all of the other functions that create new varaibles */
	list = simple_list_newlist_gc(vm->sState,pParent);
	simple_list_addstring_gc(vm->sState,list,cStr);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_NULL);
	simple_list_addstring_gc(vm->sState,list,"NULL");
	/* Pointer Type */
	simple_list_addint_gc(vm->sState,list,0);
	/* Private Flag */
	simple_list_addint_gc(vm->sState,list,0);
	/* Add Pointer to the HashTable */
	if ( pParent->pHashTable == NULL ) {
		pParent->pHashTable = simple_hashtable_new();
	}
	simple_hashtable_newpointer(pParent->pHashTable,cStr,list);
	return list ;
}

void simple_vm_addnewnumbervar ( VM *vm,const char *cStr,double x )
{
	List *list  ;
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
	simple_list_setdouble_gc(vm->sState,list,SIMPLE_VAR_VALUE,x);
}

void simple_vm_addnewstringvar ( VM *vm,const char *cStr,const char *cStr2 )
{
	List *list  ;
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
	simple_list_setstsimple_gc(vm->sState,list,SIMPLE_VAR_VALUE,cStr2);
}

void simple_vm_addnewstringvar2 ( VM *vm,const char *cStr,const char *cStr2,int nStrSize )
{
	List *list  ;
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
	simple_list_setstring2_gc(vm->sState,list,SIMPLE_VAR_VALUE,cStr2,nStrSize);
}

void simple_vm_addnewpointervar ( VM *vm,const char *cStr,void *x,int y )
{
	List *list  ;
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
	simple_list_setpointer_gc(vm->sState,list,SIMPLE_VAR_VALUE,x);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_PVALUETYPE,y);
	/* Reference Counting */
	simple_vm_gc_checknewreference(x,y);
}

void simple_vm_newtempvar ( VM *vm,const char *cStr, List *Temlist )
{
	List *list  ;
	list = simple_vm_newvar2(vm,cStr,Temlist);
	vm->nSP++ ;
	SIMPLE_VM_STACK_SETPVALUE(list);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
}

List * simple_vm_newtempvar2 ( VM *vm,const char *cStr,List *list3 )
{
	List *list,*list2  ;
	list = simple_vm_newvar2(vm,cStr,vm->pTempMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,list,SIMPLE_VAR_VALUE);
	list2 = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	simple_list_deleteallitems_gc(vm->sState,list2);
	simple_list_copy(list2,list3);
	return list ;
}

void simple_vm_addnewcpointervar ( VM *vm,const char *cStr,void *pPointer,const char *cStr2 )
{
	List *list, *list2  ;
	list = simple_vm_newvar2(vm,cStr,vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,list,SIMPLE_VAR_VALUE);
	list2 = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	/* Add Pointer */
	simple_list_addpointer_gc(vm->sState,list2,pPointer);
	/* Add Type */
	simple_list_addstring_gc(vm->sState,list2,cStr2);
	/* Add Status Number */
	simple_list_addint_gc(vm->sState,list2,SIMPLE_CPOINTERSTATUS_NOTCOPIED);
}

void simple_vm_deletescope ( VM *vm )
{
	if ( simple_list_getsize(vm->pMem) < 2 ) {
		printf( SIMPLE_NOSCOPE ) ;
		exit(0);
	}
	/* Check References */
	simple_vm_gc_checkreferences(vm);
	simple_list_deleteitem_gc(vm->sState,vm->pMem,simple_list_getsize(vm->pMem));
	vm->pActiveMem = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem));
	/* Delete Local Scope information */
	simple_list_deleteitem_gc(vm->sState,vm->aScopeID,simple_list_getsize(vm->aScopeID));
	vm->nActiveScopeID = simple_list_getint(vm->aScopeID,simple_list_getsize(vm->aScopeID)) ;
}
/* Custom Global Scope */

void simple_vm_newglobalscope ( VM *vm )
{
	vm->pActiveMem = simple_list_newlist_gc(vm->sState,vm->aGlobalScopes);
	simple_list_addpointer_gc(vm->sState,vm->aActiveGlobalScopes,vm->pActiveMem);
	simple_vm_addglobalvariables(vm);
}

void simple_vm_endglobalscope ( VM *vm )
{
	simple_list_deletelastitem_gc(vm->sState,vm->aActiveGlobalScopes);
	if ( simple_list_getsize(vm->aActiveGlobalScopes) == 0 ) {
		vm->pActiveMem = simple_list_getlist(vm->pMem,1);
	}
	else {
		vm->pActiveMem = (List *) simple_list_getpointer(vm->aActiveGlobalScopes,simple_list_getsize(vm->aActiveGlobalScopes));
	}
}

void simple_vm_setglobalscope ( VM *vm )
{
	vm->nCurrentGlobalScope = SIMPLE_VM_IR_READI ;
}

List * simple_vm_getglobalscope ( VM *vm )
{
	List *list  ;
	if ( vm->nCurrentGlobalScope == 0 ) {
		list = simple_list_getlist(vm->pMem,1);
	}
	else {
		list = simple_list_getlist(vm->aGlobalScopes,vm->nCurrentGlobalScope);
	}
	return list ;
}
