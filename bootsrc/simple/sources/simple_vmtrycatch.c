/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Try Catch Done */

void simple_vm_try ( VM *pVM )
{
	List *pList  ;
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pTry);
	simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_IR_READI);
	simple_vm_savestate(pVM,pList);
	pVM->nActiveCatch = 0 ;
}

void simple_vm_catch ( VM *pVM,const char *cError )
{
	List *pList  ;
	pList = simple_list_getlist(pVM->pTry,simple_list_getsize(pVM->pTry));
	pVM->nPC = simple_list_getint(pList,1) ;
	simple_vm_restorestate(pVM,pList,2,SIMPLE_STATE_TRYCATCH);
	/* Define variable cCatchError to contain the error message */
	simple_list_setstsimple_gc(pVM->pRingState,simple_list_getlist(simple_vm_getglobalscope(pVM),6),3,cError);
	/* Tell C-API caller (CALL command) that catch happens! */
	pVM->nActiveCatch = 1 ;
	/* Catch Statements must be executed without try effects */
	simple_vm_done(pVM);
}

void simple_vm_done ( VM *pVM )
{
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pTry,simple_list_getsize(pVM->pTry));
}
