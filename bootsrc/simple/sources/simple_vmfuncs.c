/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Functions */

int simple_vm_loadfunc ( VM *pVM )
{
	return simple_vm_loadfunc2(pVM,SIMPLE_VM_IR_READC,1) ;
}

int simple_vm_loadfunc2 ( VM *pVM,const char *cStr,int nPerformance )
{
	List *pList,*pList2,*pList3  ;
	int y  ;
	/* nFuncExecute is used also by See command while nFuncExecute2 is not */
	pVM->nFuncExecute++ ;
	pVM->nFuncExecute2++ ;
	/* Search */
	for ( y = 2 ; y >= 1 ; y-- ) {
		/* For OOP Support - Search in the Class Methods */
		if ( y == 2 ) {
			/* Exit if we are  ( not inside class (no active object) ) or we call method after object name */
			if ( ( simple_list_getsize(pVM->pObjState) == 0 ) || ( pVM->nCallMethod == 1 ) ) {
				continue ;
			}
			pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState));
			/* Pass Braces for Class Init() method */
			if ( (simple_list_getsize(pVM->pObjState) > 1) && (pVM->nCallClassInit) ) {
				if ( strcmp(cStr,"init") != 0 ) {
					pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)-1) ;
				}
			}
			pList = (List *) simple_list_getpointer(pList,SIMPLE_OBJSTATE_METHODS);
			if ( pList == NULL ) {
				continue ;
			}
		}
		else {
			/* pFunctionsMap is a list of lists (Functions in the program) */
			pList = pVM->pFunctionsMap ;
		}
		if ( simple_list_gethashtable(pList) == NULL ) {
			simple_list_genhashtable2_gc(pVM->pRingState,pList);
		}
		pList2 = (List *) simple_hashtable_findpointer(simple_list_gethashtable(pList),cStr);
		if ( pList2 != NULL ) {
			/* Error when the method is private */
			if ( simple_list_getint(pList2,SIMPLE_FUNCMAP_PRIVATEFLAG) == 1 ) {
				if ( simple_vm_oop_callmethodinsideclass(pVM) == 0 ) {
					simple_vm_error2(pVM,SIMPLE_VM_ERROR_CALLINGPRIVATEMETHOD,cStr);
					return 0 ;
				}
			}
			pList3 = simple_list_newlist_gc(pVM->pRingState,pVM->pFuncCallList);
			simple_list_addint_gc(pVM->pRingState,pList3,SIMPLE_FUNCTYPE_SCRIPT);
			/* Add the function name */
			simple_list_addstsimple_gc(pVM->pRingState,pList3,cStr);
			simple_list_addint_gc(pVM->pRingState,pList3,simple_list_getint(pList2,SIMPLE_FUNCMAP_PC));
			simple_list_addint_gc(pVM->pRingState,pList3,pVM->nSP);
			/* Create Temp Memory */
			simple_list_newlist_gc(pVM->pRingState,pList3);
			/* File Name */
			simple_list_addpointer_gc(pVM->pRingState,pList3,pVM->cFileName);
			pVM->cPrevFileName = pVM->cFileName ;
			pVM->cFileName = simple_list_getstring(pList2,SIMPLE_FUNCMAP_FILENAME) ;
			simple_list_addpointer_gc(pVM->pRingState,pList3,pVM->cFileName);
			/* Method or Function */
			if ( (y == 1) && (pVM->nCallMethod != 1) ) {
				simple_list_addint_gc(pVM->pRingState,pList3,0);
			} else {
				simple_list_addint_gc(pVM->pRingState,pList3,1);
			}
			/* Line Number */
			simple_list_addint_gc(pVM->pRingState,pList3,pVM->nLineNumber);
			if ( (strcmp(cStr,"main") != 0 ) && (pVM->nCallMethod != 1) && (y != 2) && (nPerformance == 1) ) {
				/*
				**  We check that we will convert Functions only, not methods 
				**  Replace Instruction with ICO_LOADFUNCP for better performance 
				*/
				SIMPLE_VM_IR_OPCODE = ICO_LOADFUNCP ;
				/*
				**  Leave the first parameter (contains the function name as wanted) 
				**  Create the items 
				*/
				simple_vm_newbytecodeitem(pVM,2);
				simple_vm_newbytecodeitem(pVM,3);
				simple_vm_newbytecodeitem(pVM,4);
				simple_vm_newbytecodeitem(pVM,5);
				simple_vm_newbytecodeitem(pVM,6);
				#if SIMPLE_SHOWICFINAL
				/* Update generated code list, so the new items could appear */
				SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 5 ;
				simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getint(pList2,SIMPLE_FUNCMAP_PC));
				simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,SIMPLE_FUNCTYPE_SCRIPT);
				simple_list_addpointer_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getstring(pList2,SIMPLE_FUNCMAP_FILENAME));
				simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getint(pList3,SIMPLE_FUNCCL_METHODORFUNC));
				simple_list_addint_gc(pVM->pRingState,SIMPLE_VM_IR_LIST,simple_list_getint(pList3,SIMPLE_FUNCCL_LINENUMBER));
				#endif
				simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(2),simple_list_getint(pList2,SIMPLE_FUNCMAP_PC));
				simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(3),SIMPLE_FUNCTYPE_SCRIPT);
				simple_item_setpointer_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(4),simple_list_getstring(pList2,SIMPLE_FUNCMAP_FILENAME));
				simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(5),simple_list_getint(pList3,SIMPLE_FUNCCL_METHODORFUNC));
				simple_item_setint_gc(pVM->pRingState,SIMPLE_VM_IR_ITEM(6),simple_list_getint(pList3,SIMPLE_FUNCCL_LINENUMBER));
			}
			/* Add aLoadAddressScope pointer to pLoadAddressScope */
			simple_vm_saveloadaddressscope(pVM);
			return 1 ;
		}
	}
	/* For OOP Support - Check Method not found! */
	if ( pVM->nCallMethod == 1 ) {
		/* Pass The Call Instruction and the AfterCallMethod Instruction */
		pVM->nPC += 2 ;
		/* Decrement FuncExecute Counter */
		pVM->nFuncExecute-- ;
		pVM->nFuncExecute2-- ;
		simple_vm_error2(pVM,SIMPLE_VM_ERROR_METHODNOTFOUND,cStr);
		return 0 ;
	}
	/* Find Function in C Functions List */
	pList = (List *) simple_hashtable_findpointer(simple_list_gethashtable(pVM->pCFunctionsList),cStr);
	if ( pList != NULL ) {
		pList2 = simple_list_newlist_gc(pVM->pRingState,pVM->pFuncCallList);
		simple_list_addint_gc(pVM->pRingState,pList2,SIMPLE_FUNCTYPE_C);
		simple_list_addstsimple_gc(pVM->pRingState,pList2,cStr);
		simple_list_addfuncpointer_gc(pVM->pRingState,pList2,simple_list_getfuncpointer(pList,SIMPLE_FUNCMAP_PC));
		simple_list_addint_gc(pVM->pRingState,pList2,pVM->nSP);
		/* Create Temp Memory */
		simple_list_newlist_gc(pVM->pRingState,pList2);
		/*
		**  File Name 
		**  The old source file name 
		*/
		simple_list_addpointer_gc(pVM->pRingState,pList2,pVM->cFileName);
		/* The new source file name */
		simple_list_addpointer_gc(pVM->pRingState,pList2,pVM->cFileName);
		/* Method or Function */
		simple_list_addint_gc(pVM->pRingState,pList2,0);
		/* Line Number */
		simple_list_addint_gc(pVM->pRingState,pList2,pVM->nLineNumber);
		/* Add aLoadAddressScope pointer to pLoadAddressScope */
		simple_vm_saveloadaddressscope(pVM);
		return 1 ;
	}
	/* Avoid Error if it is automatic call to the main function */
	if ( pVM->nCallMainFunction == 0 ) {
		if ( strcmp(cStr,"main") == 0 ) {
			return 0 ;
		}
	}
	/*
	**  Pass The Call Instruction 
	**  We need this when we execute braceerror() 
	**  In this case, no parameters and the call instruction is directly after the load function instruction 
	**  So it's correct to use pVM->nPC++ 
	*/
	pVM->nPC++ ;
	/*
	**  Display Error Message 
	**  Decrement FuncExecute Counter 
	*/
	pVM->nFuncExecute-- ;
	pVM->nFuncExecute2-- ;
	simple_vm_error2(pVM,SIMPLE_VM_ERROR_FUNCNOTFOUND,cStr);
	return 0 ;
}

void simple_vm_call ( VM *pVM )
{
	List *pList  ;
	/* Check if we call method using ObjName.MethodName() */
	if ( SIMPLE_VM_IR_PARACOUNT == 3 ) {
		if ( SIMPLE_VM_IR_READIVALUE(2) ) {
			/*
			**  Now we make the object state visible by moving it from aBeforeObjState to pObjState 
			**  We do this here and not in LoadMethod to avoid accessing the object state when passing parameters 
			**  This fix a problem when we pass the self object to avoid passing ObjName that comes before the method 
			*/
			if ( simple_list_getsize(pVM->aBeforeObjState) > 0 ) {
				pList = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
				simple_list_copy_gc(pVM->pRingState,pList,simple_list_getlist(pVM->aBeforeObjState,simple_list_getsize(pVM->aBeforeObjState)));
				simple_list_deleteitem_gc(pVM->pRingState,pVM->aBeforeObjState,simple_list_getsize(pVM->aBeforeObjState));
			}
		}
	}
	simple_vm_call2(pVM);
}

void simple_vm_call2 ( VM *pVM )
{
	List *pList, *pActiveMem  ;
	int x,nSP,nMax1,nFuncEx  ;
	/* Decrement FuncExecute Counter */
	if ( pVM->nFuncExecute > 0 ) {
		pVM->nFuncExecute-- ;
		pVM->nFuncExecute2-- ;
	}
	/* Restore aLoadAddressScope from pLoadAddressScope */
	simple_vm_restoreloadaddressscope(pVM);
	pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
	/* Calling Method from brace */
	if ( simple_list_getsize(pList) >= SIMPLE_FUNCCL_METHODORFUNC ) {
		/* The first test to be sure it's not a C Function Call */
		if ( simple_list_getint(pList,SIMPLE_FUNCCL_METHODORFUNC) == 1 ) {
			simple_vm_oop_callmethodfrombrace(pVM);
		}
	}
	/* Store the Caller Position */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nPC);
	/* Store FuncExe Counter Value */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nFuncExecute);
	nFuncEx = pVM->nFuncExecute ;
	pVM->nFuncExecute = 0 ;
	/* Call Function */
	if ( simple_list_getint(pList,SIMPLE_FUNCCL_TYPE) == SIMPLE_FUNCTYPE_SCRIPT ) {
		/* Store List information to allow calling function from list item and creating lists from that funct */
		simple_list_addint_gc(pVM->pRingState,pList,pVM->nListStart);
		simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pNestedLists);
		pVM->nListStart = 0 ;
		pVM->pNestedLists = simple_list_new_gc(pVM->pRingState,0);
		pVM->nPC = simple_list_getint(pList,SIMPLE_FUNCCL_PC) ;
		/* Save State */
		simple_vm_savestate2(pVM,pList);
		/* Avoid accessing object data or methods */
		if ( simple_list_getint(pList,SIMPLE_FUNCCL_METHODORFUNC) == 0 ) {
			pList = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
			simple_list_addpointer_gc(pVM->pRingState,pList,NULL);
			simple_list_addpointer_gc(pVM->pRingState,pList,NULL);
			simple_list_addpointer_gc(pVM->pRingState,pList,NULL);
		}
		/* Clear aLoadAddressScope */
		simple_list_deleteallitems_gc(pVM->pRingState,pVM->aLoadAddressScope);
	}
	else if ( simple_list_getint(pList,SIMPLE_FUNCCL_TYPE) == SIMPLE_FUNCTYPE_C ) {
		/* Trace */
		simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_BEFORECFUNC);
		/*
		**  Save Active Memory 
		**  We save Active Memory to restore it , we don't depend on scopes list of lists 
		**  because we may call function from class init 
		**  and class init don't create new scope for executing init 
		*/
		pActiveMem = pVM->pActiveMem ;
		/* Create New Scope */
		simple_vm_newscope(pVM);
		/* Get Parameters */
		pVM->nCFuncParaCount = 0 ;
		nSP = simple_list_getint(pList,SIMPLE_FUNCCL_SP) ;
		/* Use Order (First In - First Out) As Queue , the first parameter comes first */
		if ( nSP < pVM->nSP ) {
			nMax1 = pVM->nSP ;
			for ( x = nSP+1 ; x <= nMax1 ; x++ ) {
				pVM->nSP = x ;
				if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
					simple_vm_addnewstringvar2(pVM,"",SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE);
				}
				else if ( SIMPLE_VM_STACK_ISNUMBER ) {
					simple_vm_addnewnumbervar(pVM,"",SIMPLE_VM_STACK_READN);
				}
				else if ( SIMPLE_VM_STACK_ISPOINTER ) {
					simple_vm_addnewpointervar(pVM,"",SIMPLE_VM_STACK_READP,SIMPLE_VM_STACK_OBJTYPE);
				}
				pVM->nCFuncParaCount++ ;
			}
			pVM->nSP = nSP ;
		}
		/* Prepare to check function termination by try/catch */
		pVM->nActiveCatch = 0 ;
		/* Enable C Pointer Type Check */
		pVM->nIgnoreCPointerTypeCheck = 0 ;
		/* Call Function */
		simple_list_callfuncpointer(pList,SIMPLE_FUNCCL_PC,pVM);
		/* Trace */
		simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_AFTERCFUNC);
		/* Restore nFuncEx state */
		pVM->nFuncExecute = nFuncEx ;
		/* Check for function termination by try/catch */
		if ( pVM->nActiveCatch == 1 ) {
			/*
			**  We don't remove the function from call list because simple_vm_catch() do when restore state 
			**  We don't delete the scope because simple_vm_catch() will do when restore state 
			**  Restore ActiveMem 
			*/
			pVM->pActiveMem = pActiveMem ;
			return ;
		}
		/* Function Output */
		if ( nSP == pVM->nSP ) {
			/* IgnoreNULL is Used by len(object) to get output from operator overloading method */
			if ( pVM->nIgnoreNULL  == 0 ) {
				SIMPLE_VM_STACK_PUSHCVALUE("");
			}
			else {
				pVM->nIgnoreNULL = 0 ;
			}
		}
		/* Move returned List to the previous scope */
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_movetoprevscope(pVM);
		}
		/* Return (Delete Scope, Restore ActiveMem) */
		simple_list_deleteitem_gc(pVM->pRingState,pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
		simple_vm_deletescope(pVM);
		/* Restore ActiveMem */
		pVM->pActiveMem = pActiveMem ;
		/* Restore nFuncSP value */
		if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
			pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
			pVM->nFuncSP = simple_list_getint(pList,SIMPLE_FUNCCL_SP) ;
		} else {
			pVM->nFuncSP = 0 ;
		}
		/* if eval() is called, start the main loop again */
		if ( pVM->nEvalCalledFromRingCode == 1 ) {
			pVM->nEvalCalledFromRingCode = 0 ;
			/*
			**  We use Stack POP to remove the empty string that we return after functions 
			**  This enable the code generated from eval() to be able to return any value 
			**  Using the return command 
			*/
			SIMPLE_VM_STACK_POP ;
			simple_vm_mainloop(pVM);
		}
	}
}

void simple_vm_return ( VM *pVM )
{
	List *pList  ;
	/* Check if the ringvm_evalinscope() function is active */
	if ( pVM->nEvalInScope >= 1 ) {
		/*
		**  Bad Command - But don't display the message 
		**  To avoid displaying the message in correct context 
		*/
		return ;
	}
	/* Support for nested "Load" instructions */
	if ( pVM->nBlockFlag >= 1 ) {
		simple_vm_removeblockflag(pVM);
		/* Be sure it's not a function call or method call */
		if ( pVM->nPC != 0 ) {
			return ;
		}
	}
	if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
		pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
		pVM->nPC = simple_list_getint(pList,SIMPLE_FUNCCL_CALLERPC) ;
		pVM->nFuncExecute = simple_list_getint(pList,SIMPLE_FUNCCL_FUNCEXE) ;
		/* Restore List Status */
		pVM->nListStart = simple_list_getint(pList,SIMPLE_FUNCCL_LISTSTART) ;
		if ( pVM->pNestedLists != simple_list_getpointer(pList,SIMPLE_FUNCCL_NESTEDLISTS) ) {
			pVM->pNestedLists = simple_list_delete_gc(pVM->pRingState,pVM->pNestedLists);
			pVM->pNestedLists = (List *) simple_list_getpointer(pList,SIMPLE_FUNCCL_NESTEDLISTS) ;
		}
		/* Restore File Name */
		pVM->cPrevFileName = pVM->cFileName ;
		pVM->cFileName = (char *) simple_list_getpointer(pList,SIMPLE_FUNCCL_FILENAME) ;
		/* Move returned List to the previous scope */
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			/*
			**  if the variable belong to the object state, don't move to prev. scope 
			**  We do this to enable returning a reference 
			**  So when we return an object we can access it directly using { } 
			*/
			if ( simple_vm_isstackpointertoobjstate(pVM) == 0 ) {
				simple_vm_movetoprevscope(pVM);
			}
		}
		simple_vm_deletescope(pVM);
		/* Restore State */
		simple_vm_restorestate2(pVM,pList,SIMPLE_FUNCCL_STATE);
		simple_list_deleteitem_gc(pVM->pRingState,pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
		/* Restore nFuncSP value */
		if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
			pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
			pVM->nFuncSP = simple_list_getint(pList,SIMPLE_FUNCCL_SP) ;
		} else {
			pVM->nFuncSP = 0 ;
		}
		/* Trace */
		simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_RETURN);
	} else {
		/* Call Main Function */
		if ( pVM->nCallMainFunction == 0 ) {
			pVM->nPC-- ;
			pVM->nSP = 0 ;
			if ( simple_vm_loadfunc2(pVM,"main",0) ) {
				simple_vm_call(pVM);
				pVM->nCallMainFunction = 1 ;
				return ;
			}
		}
		/* End the execution Loop (Close the program) */
		simple_vm_bye(pVM);
	}
}

void simple_vm_returnnull ( VM *pVM )
{
	SIMPLE_VM_STACK_PUSHCVALUE("");
	simple_vm_return(pVM);
}

void simple_vm_newfunc ( VM *pVM )
{
	int x,nSP  ;
	List *pList  ;
	assert(pVM != NULL);
	simple_vm_newscope(pVM);
	/* Set the SP then Check Parameters */
	pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
	assert(pList != NULL);
	nSP = simple_list_getint(pList,SIMPLE_FUNCCL_SP) ;
	pVM->nFuncSP = nSP ;
	if ( SIMPLE_VM_IR_PARACOUNT > 2 ) {
		for ( x = SIMPLE_VM_IR_PARACOUNT ; x >= 3 ; x-- ) {
			if ( nSP < pVM->nSP ) {
				if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
					simple_vm_addnewstringvar2(pVM,SIMPLE_VM_IR_READCVALUE(x-1),SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE);
					SIMPLE_VM_STACK_POP ;
				}
				else if ( SIMPLE_VM_STACK_ISNUMBER ) {
					simple_vm_addnewnumbervar(pVM,SIMPLE_VM_IR_READCVALUE(x-1),SIMPLE_VM_STACK_READN);
					SIMPLE_VM_STACK_POP ;
				}
				else if ( SIMPLE_VM_STACK_ISPOINTER ) {
					simple_vm_addnewpointervar(pVM,SIMPLE_VM_IR_READCVALUE(x-1),SIMPLE_VM_STACK_READP,SIMPLE_VM_STACK_OBJTYPE);
					SIMPLE_VM_STACK_POP ;
				}
			} else {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_LESSPARAMETERSCOUNT);
				break ;
			}
		}
	}
	if ( nSP < pVM->nSP ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_EXTRAPARAMETERSCOUNT);
	}
	/* Support this in the method */
	simple_vm_oop_setthethisvariable(pVM);
	/* Trace */
	simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_NEWFUNC);
}

void simple_vm_blockflag ( VM *pVM )
{
	simple_vm_blockflag2(pVM,SIMPLE_VM_IR_READI);
}

void simple_vm_blockflag2 ( VM *pVM,int x )
{
	List *pList  ;
	pVM->nBlockFlag++ ;
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->aPCBlockFlag);
	simple_list_addint_gc(pVM->pRingState,pList,x);
	/* Save State */
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pExitMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pLoopMark));
	simple_list_addint_gc(pVM->pRingState,pList,simple_list_getsize(pVM->pTry));
}

void simple_vm_removeblockflag ( VM *pVM )
{
	List *pList  ;
	pList = simple_list_getlist(pVM->aPCBlockFlag,simple_list_getsize(pVM->aPCBlockFlag));
	pVM->nPC = simple_list_getint(pList,1);
	pVM->nBlockFlag-- ;
	/* Restore State */
	simple_vm_backstate(pVM,simple_list_getint(pList,2),pVM->pExitMark);
	simple_vm_backstate(pVM,simple_list_getint(pList,3),pVM->pLoopMark);
	simple_vm_backstate(pVM,simple_list_getint(pList,4),pVM->pTry);
	simple_list_deleteitem_gc(pVM->pRingState,pVM->aPCBlockFlag,simple_list_getsize(pVM->aPCBlockFlag));
}

void simple_vm_movetoprevscope ( VM *pVM )
{
	Item *pItem  ;
	List *pList,*pList2,*pList3  ;
	/*
	**  When the function return a value of type List or nested List 
	**  We copy the list to the previous scope, change the pointer 
	*/
	if ( simple_list_getsize(pVM->pMem) < 2 ) {
		return ;
	}
	/* Get The Source List */
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		if ( simple_list_islist(pList,SIMPLE_VAR_VALUE) ) {
			pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
		} else {
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		pList = simple_item_getlist(pItem);
	} else {
		return ;
	}
	pList2 = simple_list_getlist(pVM->pMem,simple_list_getsize(pVM->pMem)-1);
	pList3 = simple_vm_newvar2(pVM,SIMPLE_TEMP_VARIABLE,pList2);
	simple_list_setint_gc(pVM->pRingState,pList3,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pList3,SIMPLE_VAR_VALUE);
	pList2 = simple_list_getlist(pList3,SIMPLE_VAR_VALUE);
	/* Copy the list */
	simple_list_copy_gc(pVM->pRingState,pList2,pList);
	/* Update self object pointer */
	if ( simple_vm_oop_isobject(pList2) ) {
		simple_vm_oop_updateselfpointer(pVM,pList2,SIMPLE_OBJTYPE_VARIABLE,pList3);
	}
	SIMPLE_VM_STACK_SETPVALUE(pList3);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
}

void simple_vm_createtemplist ( VM *pVM )
{
	List *pList  ;
	/*
	**  Create the list in the TempMem related to the function 
	**  The advantage of TempMem over Scope is that TempMem out of search domain (Var Name is not important) 
	**  Variable name in TemMem is not important, we use it for storage (no search) 
	*/
	pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
	pList = simple_list_getlist(pList,SIMPLE_FUNCCL_TEMPMEM);
	simple_vm_newtempvar(pVM,SIMPLE_TEMP_VARIABLE,pList);
}

void simple_vm_saveloadaddressscope ( VM *pVM )
{
	simple_list_addpointer_gc(pVM->pRingState,pVM->pLoadAddressScope,pVM->aLoadAddressScope);
	pVM->aLoadAddressScope = simple_list_new_gc(pVM->pRingState,0);
}

void simple_vm_restoreloadaddressscope ( VM *pVM )
{
	simple_list_delete_gc(pVM->pRingState,pVM->aLoadAddressScope);
	pVM->aLoadAddressScope = (List *) simple_list_getpointer(pVM->pLoadAddressScope,simple_list_getsize(pVM->pLoadAddressScope));
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pLoadAddressScope,simple_list_getsize(pVM->pLoadAddressScope));
}

void simple_vm_anonymous ( VM *pVM )
{
	const char *cStr  ;
	if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr = SIMPLE_VM_STACK_READC ;
		SIMPLE_VM_STACK_POP ;
		simple_vm_loadfunc2(pVM,cStr,0);
	}
	else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADCALLPARA);
	}
}

int simple_vm_isstackpointertoobjstate ( VM *pVM )
{
	int nScope  ;
	/* if the variable belong to the object state, return 1 */
	if ( simple_list_getsize(pVM->aLoadAddressScope)  >= 1 ) {
		nScope = simple_list_getint(pVM->aLoadAddressScope,1) ;
		if ( (nScope == SIMPLE_VARSCOPE_OBJSTATE) || (nScope ==SIMPLE_VARSCOPE_GLOBAL) ) {
			return 1 ;
		}
	}
	return 0 ;
}
