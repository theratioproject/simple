/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Save/Restore State - Used by Try/Catch/Done & Loop/Exit */

void simple_vm_savestate ( VM *pVM,List *pList )
{
	List *pThis  ;
	pList = simple_list_newlist_gc(pVM->pRingState,pList);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pMem));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pFuncCallList));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncExecute);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nSP);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncSP);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pObjState));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aBraceObjects));
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pBraceObject);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->cFileName);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aPCBlockFlag));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nBlockFlag);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aScopeNewObj));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aActivePackage));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aScopeID));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nActiveScopeID);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pExitMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pLoopMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pTry));
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pActiveMem);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nListStart);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pNestedLists);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nInsideBraceFlag);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aForStep));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aBeforeObjState));
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->aPCBlockFlag);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nLineNumber);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nInClassRegion);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nPrivateFlag);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nGetSetProperty);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pGetSetObject);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nGetSetObjType);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pAssignment);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nBeforeEqual);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nNOAssignment);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncExecute2);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nCallClassInit);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->aLoadAddressScope);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(pVM->pRingState,pList,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nCurrentGlobalScope);
}

void simple_vm_restorestate ( VM *pVM,List *pList,int nPos,int nFlag )
{
	List *pThis  ;
	pList = simple_list_getlist(pList,nPos);
	/* Set Scope */
	pVM->pActiveMem = (List *) simple_list_getpointer(pList,19) ;
	/*
	**  Delete Scopes using the correct function 
	**  We need to delete each scope using simple_vm_deletescope() - so don't use simple_vm_backstate 
	**  We also avoid doing this in the Class Region (After class name) 
	**  Because in the class region we don't use pVM->pMEM 
	*/
	if ( ! pVM->nInClassRegion ) {
		while ( simple_list_getlist(pVM->pMem,simple_list_getsize(pVM->pMem)) != pVM->pActiveMem ) {
			simple_vm_deletescope(pVM);
		}
	}
	/* We also return to the function call list */
	simple_vm_backstate(pVM,simple_list_getint(pList,2),pVM->pFuncCallList);
	/* Stack & Executing Functions */
	pVM->nFuncExecute = simple_list_getint(pList,3) ;
	pVM->nSP = simple_list_getint(pList,4) ;
	pVM->nFuncSP = simple_list_getint(pList,5) ;
	/* We also return to the Active Object */
	simple_vm_backstate(pVM,simple_list_getint(pList,6),pVM->pObjState);
	simple_vm_backstate(pVM,simple_list_getint(pList,7),pVM->aBraceObjects);
	pVM->pBraceObject = (List *) simple_list_getpointer(pList,8) ;
	/* FileName & Packages */
	pVM->cFileName = (char *) simple_list_getpointer(pList,9) ;
	/* aPCBlockFlag, aScopeNewObj , aActivePackage & aScopeID */
	if ( ((List *) simple_list_getpointer(pList,25)) != pVM->aPCBlockFlag ) {
		pVM->aPCBlockFlag = simple_list_delete_gc(pVM->pRingState,pVM->aPCBlockFlag);
		pVM->aPCBlockFlag = (List *) simple_list_getpointer(pList,25) ;
	}
	simple_vm_backstate(pVM,simple_list_getint(pList,10),pVM->aPCBlockFlag);
	pVM->nBlockFlag = simple_list_getint(pList,11) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,12),pVM->aScopeNewObj);
	simple_vm_backstate(pVM,simple_list_getint(pList,13),pVM->aActivePackage);
	simple_vm_backstate(pVM,simple_list_getint(pList,14),pVM->aScopeID);
	pVM->nActiveScopeID = simple_list_getint(pList,15) ;
	/* Loop/Exit Mark */
	if ( nFlag != SIMPLE_STATE_EXIT ) {
		simple_vm_backstate(pVM,simple_list_getint(pList,16),pVM->pExitMark);
		simple_vm_backstate(pVM,simple_list_getint(pList,17),pVM->pLoopMark);
		/* For Step */
		simple_vm_backstate(pVM,simple_list_getint(pList,23),pVM->aForStep);
	}
	/* Try/Catch/Done */
	if ( nFlag != SIMPLE_STATE_TRYCATCH ) {
		simple_vm_backstate(pVM,simple_list_getint(pList,18),pVM->pTry);
	}
	/* List Status */
	pVM->nListStart = simple_list_getint(pList,20) ;
	if ( simple_list_getpointer(pList,21) != pVM->pNestedLists ) {
		pVM->pNestedLists = simple_list_delete_gc(pVM->pRingState,pVM->pNestedLists);
		pVM->pNestedLists = (List *) simple_list_getpointer(pList,21) ;
	}
	pVM->nInsideBraceFlag = simple_list_getint(pList,22) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,24),pVM->aBeforeObjState);
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(pVM->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(pVM,(List *) simple_list_getpointer(simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects)),1));
	}
	pVM->nLineNumber = simple_list_getint(pList,26) ;
	pVM->nInClassRegion = simple_list_getint(pList,27) ;
	pVM->nPrivateFlag = simple_list_getint(pList,28) ;
	pVM->nGetSetProperty = simple_list_getint(pList,29) ;
	pVM->pGetSetObject = (void *) simple_list_getpointer(pList,30) ;
	pVM->nGetSetObjType = simple_list_getint(pList,31) ;
	pVM->pAssignment = (void *) simple_list_getpointer(pList,32) ;
	pVM->nBeforeEqual = simple_list_getint(pList,33) ;
	pVM->nNOAssignment = simple_list_getint(pList,34) ;
	pVM->nFuncExecute2 = simple_list_getint(pList,35) ;
	pVM->nCallClassInit = simple_list_getint(pList,36) ;
	pVM->aLoadAddressScope = (List *) simple_list_getpointer(pList,37) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,38),pVM->pLoadAddressScope);
	/* We restore the global scope befor the This variable, because This use global scope */
	pVM->nCurrentGlobalScope = simple_list_getint(pList,41) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(pVM->pRingState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,39));
	simple_list_setint_gc(pVM->pRingState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,40));
}
/* Save/Restore State 2 - Used by Function Call & Return */

void simple_vm_savestate2 ( VM *pVM,List *pList )
{
	List *pThis  ;
	/* Save State */
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pExitMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pLoopMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pTry));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aBraceObjects));
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pBraceObject);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pObjState));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nInsideBraceFlag);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aForStep));
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pActiveMem);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncExecute2);
	pVM->nInsideBraceFlag = 0 ;
	/* Save BlockFlag */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nBlockFlag);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->aPCBlockFlag);
	pVM->nBlockFlag = 0 ;
	pVM->aPCBlockFlag = simple_list_new_gc(pVM->pRingState,0);
	/* Save nPrivateFlag, set it to 0 (public not private) */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nPrivateFlag);
	pVM->nPrivateFlag = 0 ;
	/* Save nCallClassInit */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nCallClassInit);
	pVM->nCallClassInit = 0 ;
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncExecute);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pAssignment);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nInClassRegion);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nActiveScopeID);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aScopeNewObj));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->aScopeID));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nLineNumber);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nBeforeEqual);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nNOAssignment);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nGetSetProperty);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nGetSetObjType);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pGetSetObject);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->aLoadAddressScope);
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pLoadAddressScope));
	/* Save This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_addpointer_gc(pVM->pRingState,pList,simple_list_getpointer(pThis,SIMPLE_VAR_VALUE));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getint(pThis,SIMPLE_VAR_PVALUETYPE));
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nCurrentGlobalScope);
	pVM->nInClassRegion = 0 ;
	pVM->pAssignment = NULL ;
	pVM->nNOAssignment = 0 ;
}

void simple_vm_restorestate2 ( VM *pVM,List *pList,int x )
{
	List *pThis  ;
	/* Restore State */
	simple_vm_backstate(pVM,simple_list_getint(pList,x),pVM->pExitMark);
	simple_vm_backstate(pVM,simple_list_getint(pList,x+1),pVM->pLoopMark);
	simple_vm_backstate(pVM,simple_list_getint(pList,x+2),pVM->pTry);
	simple_vm_backstate(pVM,simple_list_getint(pList,x+3),pVM->aBraceObjects);
	pVM->pBraceObject = (List *) simple_list_getpointer(pList,x+4) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,x+5),pVM->pObjState);
	pVM->nInsideBraceFlag = simple_list_getint(pList,x+6) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,x+7),pVM->aForStep);
	pVM->pActiveMem = (List *) simple_list_getpointer(pList,x+8) ;
	pVM->nFuncExecute2 = simple_list_getint(pList,x+9) ;
	/* Restore BlockFLag */
	pVM->aPCBlockFlag = simple_list_delete_gc(pVM->pRingState,pVM->aPCBlockFlag);
	pVM->nBlockFlag = simple_list_getint(pList,x+10) ;
	pVM->aPCBlockFlag = (List *) simple_list_getpointer(pList,x+11) ;
	/* Restore nPrivateFlag */
	pVM->nPrivateFlag = simple_list_getint(pList,x+12) ;
	/* Restore nCallClassInit */
	pVM->nCallClassInit = simple_list_getint(pList,x+13) ;
	pVM->nFuncExecute = simple_list_getint(pList,x+14) ;
	pVM->pAssignment = (void *) simple_list_getpointer(pList,x+15) ;
	pVM->nInClassRegion = simple_list_getint(pList,x+16) ;
	pVM->nActiveScopeID = simple_list_getint(pList,x+17) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,x+18),pVM->aScopeNewObj);
	simple_vm_backstate(pVM,simple_list_getint(pList,x+19),pVM->aScopeID);
	pVM->nLineNumber = simple_list_getint(pList,x+20) ;
	pVM->nBeforeEqual = simple_list_getint(pList,x+21) ;
	pVM->nNOAssignment = simple_list_getint(pList,x+22) ;
	pVM->nGetSetProperty = simple_list_getint(pList,x+23) ;
	pVM->nGetSetObjType = simple_list_getint(pList,x+24) ;
	pVM->pGetSetObject = (void *) simple_list_getpointer(pList,x+25) ;
	pVM->aLoadAddressScope = (List *) simple_list_getpointer(pList,x+26) ;
	simple_vm_backstate(pVM,simple_list_getint(pList,x+27),pVM->pLoadAddressScope);
	/* Restore global scope, Must be before this because this depend on it */
	pVM->nCurrentGlobalScope = simple_list_getint(pList,x+30) ;
	/* Restore This variable */
	pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
	simple_list_setpointer_gc(pVM->pRingState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,x+28));
	simple_list_setint_gc(pVM->pRingState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,x+29));
	/* Update Self Object if we are inside braces */
	if ( simple_list_getsize(pVM->aBraceObjects) > 0 ) {
		simple_vm_oop_updateselfpointer2(pVM,(List *) simple_list_getpointer(simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects)),1));
	}
}
/* Return to a Specific position in the array, delete all items after that position */

void simple_vm_backstate ( VM *pVM,int x,List *pList )
{
	int nLimit,y  ;
	if ( x < simple_list_getsize(pList) ) {
		nLimit = simple_list_getsize(pList) ;
		for ( y = x + 1 ; y <= nLimit ; y++ ) {
			simple_list_deleteitem_gc(pVM->pRingState,pList,simple_list_getsize(pList));
		}
	}
}
/* Save/Restore Stack */

List * simple_vm_savestack ( VM *pVM )
{
	int nSP  ;
	List *pList, *pList2  ;
	nSP = pVM->nSP ;
	/* Create List */
	pList = simple_list_new_gc(pVM->pRingState,0);
	while ( pVM->nSP  != 0 ) {
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			simple_list_addstsimple_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			simple_list_adddouble_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_READN);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			pList2 = simple_list_newlist_gc(pVM->pRingState,pList);
			simple_list_addpointer_gc(pVM->pRingState,pList2,SIMPLE_VM_STACK_READP);
			simple_list_addint_gc(pVM->pRingState,pList2,SIMPLE_VM_STACK_OBJTYPE);
		}
		SIMPLE_VM_STACK_POP ;
	}
	pVM->nSP = nSP ;
	return pList ;
}

void simple_vm_restorestack ( VM *pVM,List *pList )
{
	int x  ;
	List *pList2  ;
	pVM->nSP = 0 ;
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
