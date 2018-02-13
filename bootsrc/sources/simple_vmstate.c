
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
/* Save/Restore State - Used by Try/Catch/Done & Loop/Exit */

void simple_vm_savestate ( VM *vm,List *list )
{
	List *pThis  ;
	list = simple_list_newlist_gc(vm->sState,list);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pMem));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pFuncCallList));
	simple_list_addint_gc(vm->sState,list,vm->nFuncExecute);
	simple_list_addint_gc(vm->sState,list,vm->nSP);
	simple_list_addint_gc(vm->sState,list,vm->nFuncSP);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pObjState));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aBraceObjects));
	simple_list_addpointer_gc(vm->sState,list,vm->pBraceObject);
	simple_list_addpointer_gc(vm->sState,list,vm->cFileName);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aPCBlockFlag));
	simple_list_addint_gc(vm->sState,list,vm->nBlockFlag);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aScopeNewObj));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aActiveModules));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aScopeID));
	simple_list_addint_gc(vm->sState,list,vm->nActiveScopeID);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pExitMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pLoopMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pTry));
	simple_list_addpointer_gc(vm->sState,list,vm->pActiveMem);
	simple_list_addint_gc(vm->sState,list,vm->nListStart);
	simple_list_addpointer_gc(vm->sState,list,vm->pNestedLists);
	simple_list_addint_gc(vm->sState,list,vm->nInsideBraceFlag);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aForStep));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aBeforeObjState));
	simple_list_addpointer_gc(vm->sState,list,vm->aPCBlockFlag);
	simple_list_addint_gc(vm->sState,list,vm->nLineNumber);
	simple_list_addint_gc(vm->sState,list,vm->nInClassRegion);
	simple_list_addint_gc(vm->sState,list,vm->nPrivateFlag);
	simple_list_addint_gc(vm->sState,list,vm->nGetSetProperty);
	simple_list_addpointer_gc(vm->sState,list,vm->pGetSetObject);
	simple_list_addint_gc(vm->sState,list,vm->nGetSetObjType);
	simple_list_addpointer_gc(vm->sState,list,vm->pAssignment);
	simple_list_addint_gc(vm->sState,list,vm->nBeforeEqual);
	simple_list_addint_gc(vm->sState,list,vm->nNOAssignment);
	simple_list_addint_gc(vm->sState,list,vm->nFuncExecute2);
	simple_list_addint_gc(vm->sState,list,vm->nCallClassInit);
	simple_list_addpointer_gc(vm->sState,list,vm->aLoadAddressScope);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(vm->sState,list,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(vm->sState,list,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(vm->sState,list,vm->nCurrentGlobalScope);
}

void simple_vm_restorestate ( VM *vm,List *list,int nPos,int nFlag )
{
	List *pThis  ;
	list = simple_list_getlist(list,nPos);
	/* Set Scope */
	vm->pActiveMem = (List *) simple_list_getpointer(list,19) ;
	/*
	**  Delete Scopes using the correct function 
	**  We need to delete each scope using simple_vm_deletescope() - so don't use simple_vm_backstate 
	**  We also avoid doing this in the Class Region (After class name) 
	**  Because in the class region we don't use vm->pMEM 
	*/
	if ( ! vm->nInClassRegion ) {
		while ( simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)) != vm->pActiveMem ) {
			simple_vm_deletescope(vm);
		}
	}
	/* We also return to the function call list */
	simple_vm_backstate(vm,simple_list_getint(list,2),vm->pFuncCallList);
	/* Stack & Executing Functions */
	vm->nFuncExecute = simple_list_getint(list,3) ;
	vm->nSP = simple_list_getint(list,4) ;
	vm->nFuncSP = simple_list_getint(list,5) ;
	/* We also return to the Active Object */
	simple_vm_backstate(vm,simple_list_getint(list,6),vm->pObjState);
	simple_vm_backstate(vm,simple_list_getint(list,7),vm->aBraceObjects);
	vm->pBraceObject = (List *) simple_list_getpointer(list,8) ;
	/* FileName & Moduless */
	vm->cFileName = (char *) simple_list_getpointer(list,9) ;
	/* aPCBlockFlag, aScopeNewObj , aActiveModules & aScopeID */
	if ( ((List *) simple_list_getpointer(list,25)) != vm->aPCBlockFlag ) {
		vm->aPCBlockFlag = simple_list_delete_gc(vm->sState,vm->aPCBlockFlag);
		vm->aPCBlockFlag = (List *) simple_list_getpointer(list,25) ;
	}
	simple_vm_backstate(vm,simple_list_getint(list,10),vm->aPCBlockFlag);
	vm->nBlockFlag = simple_list_getint(list,11) ;
	simple_vm_backstate(vm,simple_list_getint(list,12),vm->aScopeNewObj);
	simple_vm_backstate(vm,simple_list_getint(list,13),vm->aActiveModules);
	simple_vm_backstate(vm,simple_list_getint(list,14),vm->aScopeID);
	vm->nActiveScopeID = simple_list_getint(list,15) ;
	/* Loop/Exit Mark */
	if ( nFlag != SIMPLE_STATE_EXIT ) {
		simple_vm_backstate(vm,simple_list_getint(list,16),vm->pExitMark);
		simple_vm_backstate(vm,simple_list_getint(list,17),vm->pLoopMark);
		/* For Step */
		simple_vm_backstate(vm,simple_list_getint(list,23),vm->aForStep);
	}
	/* Try/Catch/Done */
	if ( nFlag != SIMPLE_STATE_TRYCATCH ) {
		simple_vm_backstate(vm,simple_list_getint(list,18),vm->pTry);
	}
	/* List Status */
	vm->nListStart = simple_list_getint(list,20) ;
	if ( simple_list_getpointer(list,21) != vm->pNestedLists ) {
		vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
		vm->pNestedLists = (List *) simple_list_getpointer(list,21) ;
	}
	vm->nInsideBraceFlag = simple_list_getint(list,22) ;
	simple_vm_backstate(vm,simple_list_getint(list,24),vm->aBeforeObjState);
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(vm,(List *) simple_list_getpointer(simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)),1));
	}
	vm->nLineNumber = simple_list_getint(list,26) ;
	vm->nInClassRegion = simple_list_getint(list,27) ;
	vm->nPrivateFlag = simple_list_getint(list,28) ;
	vm->nGetSetProperty = simple_list_getint(list,29) ;
	vm->pGetSetObject = (void *) simple_list_getpointer(list,30) ;
	vm->nGetSetObjType = simple_list_getint(list,31) ;
	vm->pAssignment = (void *) simple_list_getpointer(list,32) ;
	vm->nBeforeEqual = simple_list_getint(list,33) ;
	vm->nNOAssignment = simple_list_getint(list,34) ;
	vm->nFuncExecute2 = simple_list_getint(list,35) ;
	vm->nCallClassInit = simple_list_getint(list,36) ;
	vm->aLoadAddressScope = (List *) simple_list_getpointer(list,37) ;
	simple_vm_backstate(vm,simple_list_getint(list,38),vm->pLoadAddressScope);
	/* We restore the global scope befor the This variable, because This use global scope */
	vm->nCurrentGlobalScope = simple_list_getint(list,41) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(list,39));
	simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(list,40));
}
/* Save/Restore State 2 - Used by Function Call & Return */

void simple_vm_savestate2 ( VM *vm,List *list )
{
	List *pThis  ;
	/* Save State */
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pExitMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pLoopMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pTry));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aBraceObjects));
	simple_list_addpointer_gc(vm->sState,list,vm->pBraceObject);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pObjState));
	simple_list_addint_gc(vm->sState,list,vm->nInsideBraceFlag);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aForStep));
	simple_list_addpointer_gc(vm->sState,list,vm->pActiveMem);
	simple_list_addint_gc(vm->sState,list,vm->nFuncExecute2);
	vm->nInsideBraceFlag = 0 ;
	/* Save BlockFlag */
	simple_list_addint_gc(vm->sState,list,vm->nBlockFlag);
	simple_list_addpointer_gc(vm->sState,list,vm->aPCBlockFlag);
	vm->nBlockFlag = 0 ;
	vm->aPCBlockFlag = simple_list_new_gc(vm->sState,0);
	/* Save nPrivateFlag, set it to 0 (public not private) */
	simple_list_addint_gc(vm->sState,list,vm->nPrivateFlag);
	vm->nPrivateFlag = 0 ;
	/* Save nCallClassInit */
	simple_list_addint_gc(vm->sState,list,vm->nCallClassInit);
	vm->nCallClassInit = 0 ;
	simple_list_addint_gc(vm->sState,list,vm->nFuncExecute);
	simple_list_addpointer_gc(vm->sState,list,vm->pAssignment);
	simple_list_addint_gc(vm->sState,list,vm->nInClassRegion);
	simple_list_addint_gc(vm->sState,list,vm->nActiveScopeID);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aScopeNewObj));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->aScopeID));
	simple_list_addint_gc(vm->sState,list,vm->nLineNumber);
	simple_list_addint_gc(vm->sState,list,vm->nBeforeEqual);
	simple_list_addint_gc(vm->sState,list,vm->nNOAssignment);
	simple_list_addint_gc(vm->sState,list,vm->nGetSetProperty);
	simple_list_addint_gc(vm->sState,list,vm->nGetSetObjType);
	simple_list_addpointer_gc(vm->sState,list,vm->pGetSetObject);
	simple_list_addpointer_gc(vm->sState,list,vm->aLoadAddressScope);
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(vm->sState,list,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(vm->sState,list,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(vm->sState,list,vm->nCurrentGlobalScope);
	vm->nInClassRegion = 0 ;
	vm->pAssignment = NULL ;
	vm->nNOAssignment = 0 ;
}

void simple_vm_restorestate2 ( VM *vm,List *list,int x )
{
	List *pThis  ;
	/* Restore State */
	simple_vm_backstate(vm,simple_list_getint(list,x),vm->pExitMark);
	simple_vm_backstate(vm,simple_list_getint(list,x+1),vm->pLoopMark);
	simple_vm_backstate(vm,simple_list_getint(list,x+2),vm->pTry);
	simple_vm_backstate(vm,simple_list_getint(list,x+3),vm->aBraceObjects);
	vm->pBraceObject = (List *) simple_list_getpointer(list,x+4) ;
	simple_vm_backstate(vm,simple_list_getint(list,x+5),vm->pObjState);
	vm->nInsideBraceFlag = simple_list_getint(list,x+6) ;
	simple_vm_backstate(vm,simple_list_getint(list,x+7),vm->aForStep);
	vm->pActiveMem = (List *) simple_list_getpointer(list,x+8) ;
	vm->nFuncExecute2 = simple_list_getint(list,x+9) ;
	/* Restore BlockFLag */
	vm->aPCBlockFlag = simple_list_delete_gc(vm->sState,vm->aPCBlockFlag);
	vm->nBlockFlag = simple_list_getint(list,x+10) ;
	vm->aPCBlockFlag = (List *) simple_list_getpointer(list,x+11) ;
	/* Restore nPrivateFlag */
	vm->nPrivateFlag = simple_list_getint(list,x+12) ;
	/* Restore nCallClassInit */
	vm->nCallClassInit = simple_list_getint(list,x+13) ;
	vm->nFuncExecute = simple_list_getint(list,x+14) ;
	vm->pAssignment = (void *) simple_list_getpointer(list,x+15) ;
	vm->nInClassRegion = simple_list_getint(list,x+16) ;
	vm->nActiveScopeID = simple_list_getint(list,x+17) ;
	simple_vm_backstate(vm,simple_list_getint(list,x+18),vm->aScopeNewObj);
	simple_vm_backstate(vm,simple_list_getint(list,x+19),vm->aScopeID);
	vm->nLineNumber = simple_list_getint(list,x+20) ;
	vm->nBeforeEqual = simple_list_getint(list,x+21) ;
	vm->nNOAssignment = simple_list_getint(list,x+22) ;
	vm->nGetSetProperty = simple_list_getint(list,x+23) ;
	vm->nGetSetObjType = simple_list_getint(list,x+24) ;
	vm->pGetSetObject = (void *) simple_list_getpointer(list,x+25) ;
	vm->aLoadAddressScope = (List *) simple_list_getpointer(list,x+26) ;
	simple_vm_backstate(vm,simple_list_getint(list,x+27),vm->pLoadAddressScope);
	/* Restore global scope, Must be before this because this depend on it */
	vm->nCurrentGlobalScope = simple_list_getint(list,x+30) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(list,x+28));
	simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(list,x+29));
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(vm,(List *) simple_list_getpointer(simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)),1));
	}
}
/* Return to a Specific position in the array, delete all items after that position */

void simple_vm_backstate ( VM *vm,int x,List *list )
{
	int nLimit,y  ;
	if ( x < simple_list_getsize(list) ) {
		nLimit = simple_list_getsize(list) ;
		for ( y = x + 1 ; y <= nLimit ; y++ ) {
			simple_list_deleteitem_gc(vm->sState,list,simple_list_getsize(list));
		}
	}
}
/* Save/Restore Stack */

List * simple_vm_savestack ( VM *vm )
{
	int nSP  ;
	List *list, *list2  ;
	nSP = vm->nSP ;
	/* Create List */
	list = simple_list_new_gc(vm->sState,0);
	while ( vm->nSP  != 0 ) {
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			simple_list_addstring_gc(vm->sState,list,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			simple_list_adddouble_gc(vm->sState,list,SIMPLE_VM_STACK_READN);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			list2 = simple_list_newlist_gc(vm->sState,list);
			simple_list_addpointer_gc(vm->sState,list2,SIMPLE_VM_STACK_READP);
			simple_list_addint_gc(vm->sState,list2,SIMPLE_VM_STACK_OBJTYPE);
		}
		SIMPLE_VM_STACK_POP ;
	}
	vm->nSP = nSP ;
	return list ;
}

void simple_vm_restorestack ( VM *vm,List *list )
{
	int x  ;
	List *list2  ;
	vm->nSP = 0 ;
	if ( simple_list_getsize(list) == 0 ) {
		return ;
	}
	for ( x = simple_list_getsize(list) ; x >= 1 ; x-- ) {
		if ( simple_list_isstring(list,x) ) {
			SIMPLE_VM_STACK_PUSHCVALUE(simple_list_getstring(list,x));
		}
		else if ( simple_list_isnumber(list,x) ) {
			SIMPLE_VM_STACK_PUSHNVALUE(simple_list_getdouble(list,x));
		}
		else if ( simple_list_islist(list,x) ) {
			list2 = simple_list_getlist(list,x);
			SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(list2,1));
			SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(list2,2) ;
		}
	}
}
