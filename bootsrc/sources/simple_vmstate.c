
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

void simple_vm_savestate ( VM *vm,List *pList )
{
	List *pThis  ;
	pList = simple_list_newlist_gc(vm->sState,pList);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pMem));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pFuncCallList));
	simple_list_addint_gc(vm->sState,pList,vm->nFuncExecute);
	simple_list_addint_gc(vm->sState,pList,vm->nSP);
	simple_list_addint_gc(vm->sState,pList,vm->nFuncSP);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pObjState));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aBraceObjects));
	simple_list_addpointer_gc(vm->sState,pList,vm->pBraceObject);
	simple_list_addpointer_gc(vm->sState,pList,vm->cFileName);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aPCBlockFlag));
	simple_list_addint_gc(vm->sState,pList,vm->nBlockFlag);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aScopeNewObj));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aActiveModules));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aScopeID));
	simple_list_addint_gc(vm->sState,pList,vm->nActiveScopeID);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pExitMark));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pLoopMark));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pTry));
	simple_list_addpointer_gc(vm->sState,pList,vm->pActiveMem);
	simple_list_addint_gc(vm->sState,pList,vm->nListStart);
	simple_list_addpointer_gc(vm->sState,pList,vm->pNestedLists);
	simple_list_addint_gc(vm->sState,pList,vm->nInsideBraceFlag);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aForStep));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aBeforeObjState));
	simple_list_addpointer_gc(vm->sState,pList,vm->aPCBlockFlag);
	simple_list_addint_gc(vm->sState,pList,vm->nLineNumber);
	simple_list_addint_gc(vm->sState,pList,vm->nInClassRegion);
	simple_list_addint_gc(vm->sState,pList,vm->nPrivateFlag);
	simple_list_addint_gc(vm->sState,pList,vm->nGetSetProperty);
	simple_list_addpointer_gc(vm->sState,pList,vm->pGetSetObject);
	simple_list_addint_gc(vm->sState,pList,vm->nGetSetObjType);
	simple_list_addpointer_gc(vm->sState,pList,vm->pAssignment);
	simple_list_addint_gc(vm->sState,pList,vm->nBeforeEqual);
	simple_list_addint_gc(vm->sState,pList,vm->nNOAssignment);
	simple_list_addint_gc(vm->sState,pList,vm->nFuncExecute2);
	simple_list_addint_gc(vm->sState,pList,vm->nCallClassInit);
	simple_list_addpointer_gc(vm->sState,pList,vm->aLoadAddressScope);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(vm->sState,pList,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(vm->sState,pList,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(vm->sState,pList,vm->nCurrentGlobalScope);
}

void simple_vm_restorestate ( VM *vm,List *pList,int nPos,int nFlag )
{
	List *pThis  ;
	pList = simple_list_getlist(pList,nPos);
	/* Set Scope */
	vm->pActiveMem = (List *) simple_list_getpointer(pList,19) ;
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
	simple_vm_backstate(vm,simple_list_getint(pList,2),vm->pFuncCallList);
	/* Stack & Executing Functions */
	vm->nFuncExecute = simple_list_getint(pList,3) ;
	vm->nSP = simple_list_getint(pList,4) ;
	vm->nFuncSP = simple_list_getint(pList,5) ;
	/* We also return to the Active Object */
	simple_vm_backstate(vm,simple_list_getint(pList,6),vm->pObjState);
	simple_vm_backstate(vm,simple_list_getint(pList,7),vm->aBraceObjects);
	vm->pBraceObject = (List *) simple_list_getpointer(pList,8) ;
	/* FileName & Moduless */
	vm->cFileName = (char *) simple_list_getpointer(pList,9) ;
	/* aPCBlockFlag, aScopeNewObj , aActiveModules & aScopeID */
	if ( ((List *) simple_list_getpointer(pList,25)) != vm->aPCBlockFlag ) {
		vm->aPCBlockFlag = simple_list_delete_gc(vm->sState,vm->aPCBlockFlag);
		vm->aPCBlockFlag = (List *) simple_list_getpointer(pList,25) ;
	}
	simple_vm_backstate(vm,simple_list_getint(pList,10),vm->aPCBlockFlag);
	vm->nBlockFlag = simple_list_getint(pList,11) ;
	simple_vm_backstate(vm,simple_list_getint(pList,12),vm->aScopeNewObj);
	simple_vm_backstate(vm,simple_list_getint(pList,13),vm->aActiveModules);
	simple_vm_backstate(vm,simple_list_getint(pList,14),vm->aScopeID);
	vm->nActiveScopeID = simple_list_getint(pList,15) ;
	/* Loop/Exit Mark */
	if ( nFlag != SIMPLE_STATE_EXIT ) {
		simple_vm_backstate(vm,simple_list_getint(pList,16),vm->pExitMark);
		simple_vm_backstate(vm,simple_list_getint(pList,17),vm->pLoopMark);
		/* For Step */
		simple_vm_backstate(vm,simple_list_getint(pList,23),vm->aForStep);
	}
	/* Try/Catch/Done */
	if ( nFlag != SIMPLE_STATE_TRYCATCH ) {
		simple_vm_backstate(vm,simple_list_getint(pList,18),vm->pTry);
	}
	/* List Status */
	vm->nListStart = simple_list_getint(pList,20) ;
	if ( simple_list_getpointer(pList,21) != vm->pNestedLists ) {
		vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
		vm->pNestedLists = (List *) simple_list_getpointer(pList,21) ;
	}
	vm->nInsideBraceFlag = simple_list_getint(pList,22) ;
	simple_vm_backstate(vm,simple_list_getint(pList,24),vm->aBeforeObjState);
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(vm,(List *) simple_list_getpointer(simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)),1));
	}
	vm->nLineNumber = simple_list_getint(pList,26) ;
	vm->nInClassRegion = simple_list_getint(pList,27) ;
	vm->nPrivateFlag = simple_list_getint(pList,28) ;
	vm->nGetSetProperty = simple_list_getint(pList,29) ;
	vm->pGetSetObject = (void *) simple_list_getpointer(pList,30) ;
	vm->nGetSetObjType = simple_list_getint(pList,31) ;
	vm->pAssignment = (void *) simple_list_getpointer(pList,32) ;
	vm->nBeforeEqual = simple_list_getint(pList,33) ;
	vm->nNOAssignment = simple_list_getint(pList,34) ;
	vm->nFuncExecute2 = simple_list_getint(pList,35) ;
	vm->nCallClassInit = simple_list_getint(pList,36) ;
	vm->aLoadAddressScope = (List *) simple_list_getpointer(pList,37) ;
	simple_vm_backstate(vm,simple_list_getint(pList,38),vm->pLoadAddressScope);
	/* We restore the global scope befor the This variable, because This use global scope */
	vm->nCurrentGlobalScope = simple_list_getint(pList,41) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,39));
	simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,40));
}
/* Save/Restore State 2 - Used by Function Call & Return */

void simple_vm_savestate2 ( VM *vm,List *pList )
{
	List *pThis  ;
	/* Save State */
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pExitMark));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pLoopMark));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pTry));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aBraceObjects));
	simple_list_addpointer_gc(vm->sState,pList,vm->pBraceObject);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pObjState));
	simple_list_addint_gc(vm->sState,pList,vm->nInsideBraceFlag);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aForStep));
	simple_list_addpointer_gc(vm->sState,pList,vm->pActiveMem);
	simple_list_addint_gc(vm->sState,pList,vm->nFuncExecute2);
	vm->nInsideBraceFlag = 0 ;
	/* Save BlockFlag */
	simple_list_addint_gc(vm->sState,pList,vm->nBlockFlag);
	simple_list_addpointer_gc(vm->sState,pList,vm->aPCBlockFlag);
	vm->nBlockFlag = 0 ;
	vm->aPCBlockFlag = simple_list_new_gc(vm->sState,0);
	/* Save nPrivateFlag, set it to 0 (public not private) */
	simple_list_addint_gc(vm->sState,pList,vm->nPrivateFlag);
	vm->nPrivateFlag = 0 ;
	/* Save nCallClassInit */
	simple_list_addint_gc(vm->sState,pList,vm->nCallClassInit);
	vm->nCallClassInit = 0 ;
	simple_list_addint_gc(vm->sState,pList,vm->nFuncExecute);
	simple_list_addpointer_gc(vm->sState,pList,vm->pAssignment);
	simple_list_addint_gc(vm->sState,pList,vm->nInClassRegion);
	simple_list_addint_gc(vm->sState,pList,vm->nActiveScopeID);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aScopeNewObj));
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->aScopeID));
	simple_list_addint_gc(vm->sState,pList,vm->nLineNumber);
	simple_list_addint_gc(vm->sState,pList,vm->nBeforeEqual);
	simple_list_addint_gc(vm->sState,pList,vm->nNOAssignment);
	simple_list_addint_gc(vm->sState,pList,vm->nGetSetProperty);
	simple_list_addint_gc(vm->sState,pList,vm->nGetSetObjType);
	simple_list_addpointer_gc(vm->sState,pList,vm->pGetSetObject);
	simple_list_addpointer_gc(vm->sState,pList,vm->aLoadAddressScope);
	simple_list_addint_gc(vm->sState,pList,simple_list_getsize(vm->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(vm->sState,pList,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(vm->sState,pList,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(vm->sState,pList,vm->nCurrentGlobalScope);
	vm->nInClassRegion = 0 ;
	vm->pAssignment = NULL ;
	vm->nNOAssignment = 0 ;
}

void simple_vm_restorestate2 ( VM *vm,List *pList,int x )
{
	List *pThis  ;
	/* Restore State */
	simple_vm_backstate(vm,simple_list_getint(pList,x),vm->pExitMark);
	simple_vm_backstate(vm,simple_list_getint(pList,x+1),vm->pLoopMark);
	simple_vm_backstate(vm,simple_list_getint(pList,x+2),vm->pTry);
	simple_vm_backstate(vm,simple_list_getint(pList,x+3),vm->aBraceObjects);
	vm->pBraceObject = (List *) simple_list_getpointer(pList,x+4) ;
	simple_vm_backstate(vm,simple_list_getint(pList,x+5),vm->pObjState);
	vm->nInsideBraceFlag = simple_list_getint(pList,x+6) ;
	simple_vm_backstate(vm,simple_list_getint(pList,x+7),vm->aForStep);
	vm->pActiveMem = (List *) simple_list_getpointer(pList,x+8) ;
	vm->nFuncExecute2 = simple_list_getint(pList,x+9) ;
	/* Restore BlockFLag */
	vm->aPCBlockFlag = simple_list_delete_gc(vm->sState,vm->aPCBlockFlag);
	vm->nBlockFlag = simple_list_getint(pList,x+10) ;
	vm->aPCBlockFlag = (List *) simple_list_getpointer(pList,x+11) ;
	/* Restore nPrivateFlag */
	vm->nPrivateFlag = simple_list_getint(pList,x+12) ;
	/* Restore nCallClassInit */
	vm->nCallClassInit = simple_list_getint(pList,x+13) ;
	vm->nFuncExecute = simple_list_getint(pList,x+14) ;
	vm->pAssignment = (void *) simple_list_getpointer(pList,x+15) ;
	vm->nInClassRegion = simple_list_getint(pList,x+16) ;
	vm->nActiveScopeID = simple_list_getint(pList,x+17) ;
	simple_vm_backstate(vm,simple_list_getint(pList,x+18),vm->aScopeNewObj);
	simple_vm_backstate(vm,simple_list_getint(pList,x+19),vm->aScopeID);
	vm->nLineNumber = simple_list_getint(pList,x+20) ;
	vm->nBeforeEqual = simple_list_getint(pList,x+21) ;
	vm->nNOAssignment = simple_list_getint(pList,x+22) ;
	vm->nGetSetProperty = simple_list_getint(pList,x+23) ;
	vm->nGetSetObjType = simple_list_getint(pList,x+24) ;
	vm->pGetSetObject = (void *) simple_list_getpointer(pList,x+25) ;
	vm->aLoadAddressScope = (List *) simple_list_getpointer(pList,x+26) ;
	simple_vm_backstate(vm,simple_list_getint(pList,x+27),vm->pLoadAddressScope);
	/* Restore global scope, Must be before this because this depend on it */
	vm->nCurrentGlobalScope = simple_list_getint(pList,x+30) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,x+28));
	simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,x+29));
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(vm,(List *) simple_list_getpointer(simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)),1));
	}
}
/* Return to a Specific position in the array, delete all items after that position */

void simple_vm_backstate ( VM *vm,int x,List *pList )
{
	int nLimit,y  ;
	if ( x < simple_list_getsize(pList) ) {
		nLimit = simple_list_getsize(pList) ;
		for ( y = x + 1 ; y <= nLimit ; y++ ) {
			simple_list_deleteitem_gc(vm->sState,pList,simple_list_getsize(pList));
		}
	}
}
/* Save/Restore Stack */

List * simple_vm_savestack ( VM *vm )
{
	int nSP  ;
	List *pList, *pList2  ;
	nSP = vm->nSP ;
	/* Create List */
	pList = simple_list_new_gc(vm->sState,0);
	while ( vm->nSP  != 0 ) {
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			simple_list_addstring_gc(vm->sState,pList,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			simple_list_adddouble_gc(vm->sState,pList,SIMPLE_VM_STACK_READN);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			pList2 = simple_list_newlist_gc(vm->sState,pList);
			simple_list_addpointer_gc(vm->sState,pList2,SIMPLE_VM_STACK_READP);
			simple_list_addint_gc(vm->sState,pList2,SIMPLE_VM_STACK_OBJTYPE);
		}
		SIMPLE_VM_STACK_POP ;
	}
	vm->nSP = nSP ;
	return pList ;
}

void simple_vm_restorestack ( VM *vm,List *pList )
{
	int x  ;
	List *pList2  ;
	vm->nSP = 0 ;
	if ( simple_list_getsize(pList) == 0 ) {
		return ;
	}
	for ( x = simple_list_getsize(pList) ; x >= 1 ; x-- ) {
		if ( simple_list_isstring(pList,x) ) {
			SIMPLE_VM_STACK_PUSHCVALUE(simple_list_getstring(pList,x));
		}
		else if ( simple_list_isnumber(pList,x) ) {
			SIMPLE_VM_STACK_PUSHNVALUE(simple_list_getdouble(pList,x));
		}
		else if ( simple_list_islist(pList,x) ) {
			pList2 = simple_list_getlist(pList,x);
			SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(pList2,1));
			SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(pList2,2) ;
		}
	}
}
