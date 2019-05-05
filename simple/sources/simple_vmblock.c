
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: Azeez Adewale
 *
 * Created on July 10, 2017, 1:10 PM
 */

#include "../include/simple.h"
/* Blocks */

SIMPLE_API int simple_vm_loadblock ( VM *vm )
{
	return simple_vm_loadblock2(vm,SIMPLE_VM_IR_READC,1) ;
}

SIMPLE_API int simple_vm_loadblock2 ( VM *vm,const char *block_name,int nPerformance )
{
	List *list,*list2,*list3  ;
	int y  ; 
	/* nBlockExecute is used also by See command while nBlockExecute2 is not */
	vm->nBlockExecute++ ;
	vm->nBlockExecute2++ ;
	/* Search */
	for ( y = 2 ; y >= 1 ; y-- ) {
		/* For OOP Support - Search in the Class Methods */
		if ( y == 2 ) {
			/* Exit if we are  ( not inside class (no active object) ) or we call method after object name */
			if ( ( simple_list_getsize(vm->pObjState) == 0 ) || ( vm->nCallMethod == 1 ) ) {
				continue ;
			}
			list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState));
			/* Pass Braces for Class Init() method */
			if ( (simple_list_getsize(vm->pObjState) > 1) && (vm->nCallClassInit) ) {
				if ( strcmp(block_name,"Init") != 0 ) {
					list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)-1) ;
				}
			}
			list = (List *) simple_list_getpointer(list,SIMPLE_OBJSTATE_METHODS);
			if ( list == NULL ) {
				continue ;
			}
		}
		else {
			/* pBlocksMap is a list of lists (Blocks in the program) */
			list = vm->pBlocksMap ;
		}
		if ( simple_list_gethashtable(list) == NULL ) {
			simple_list_genhashtable2_gc(vm->sState,list);
		}
		list2 = (List *) simple_hashtable_findpointer(simple_list_gethashtable(list),block_name);
		if ( list2 != NULL ) {
			/* Error when the method is private */
			if ( simple_list_getint(list2,SIMPLE_BLOCKMAP_PRIVATEFLAG) == 1 ) {
				if ( simple_vm_oop_callmethodinsideclass(vm) == 0 ) {
					simple_vm_error2(vm,SIMPLE_VM_ERROR_CALLINGPRIVATEMETHOD,block_name);
					return 0 ;
				}
			}
			list3 = simple_list_newlist_gc(vm->sState,vm->pBlockCallList);
			simple_list_addint_gc(vm->sState,list3,SIMPLE_BLOCKTYPE_SCRIPT);
			/* Add the block name */
			simple_list_addstring_gc(vm->sState,list3,block_name);
			simple_list_addint_gc(vm->sState,list3,simple_list_getint(list2,SIMPLE_BLOCKMAP_PC));
			simple_list_addint_gc(vm->sState,list3,vm->nsp);
			/* Create Temp Memory */
			simple_list_newlist_gc(vm->sState,list3);
			/* File Name */
			simple_list_addpointer_gc(vm->sState,list3,vm->file_name);
			vm->cPrevFileName = vm->file_name ;
			vm->file_name = simple_list_getstring(list2,SIMPLE_BLOCKMAP_FILENAME) ;
			simple_list_addpointer_gc(vm->sState,list3,vm->file_name);
			/* Method or Block */
			if ( (y == 1) && (vm->nCallMethod != 1) ) {
				simple_list_addint_gc(vm->sState,list3,0);
			} else {
				simple_list_addint_gc(vm->sState,list3,1);
			}
			/* Line Number */
			simple_list_addint_gc(vm->sState,list3,vm->nLineNumber);
			if ( (strcmp(block_name,"main") != 0 ) && (vm->nCallMethod != 1) && (y != 2) && (nPerformance == 1) ) {
				/*
				**  We check that we will convert Blocks only, not methods 
				**  Replace Instruction with ICO_LOADBLOCKP for better performance 
				*/
				SIMPLE_VM_IR_OPCODE = ICO_LOADBLOCKP ; 
				/*
				**  Leave the first parameter (contains the block name as wanted) 
				**  Create the items 
				*/
				simple_vm_newbytecodeitem(vm,2);
				simple_vm_newbytecodeitem(vm,3);
				simple_vm_newbytecodeitem(vm,4);
				simple_vm_newbytecodeitem(vm,5);
				simple_vm_newbytecodeitem(vm,6);
				#if SIMPLE_SHOWICFINAL
				/* Update generated code list, so the new items could appear */
				SIMPLE_VM_IR_PARACOUNT = SIMPLE_VM_IR_PARACOUNT + 5 ;
				simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getint(list2,SIMPLE_BLOCKMAP_PC));
				simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,SIMPLE_BLOCKTYPE_SCRIPT);
				simple_list_addpointer_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getstring(list2,SIMPLE_BLOCKMAP_FILENAME));
				simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getint(list3,SIMPLE_BLOCKCL_METHODORBLOCK));
				simple_list_addint_gc(vm->sState,SIMPLE_VM_IR_LIST,simple_list_getint(list3,SIMPLE_BLOCKCL_LINENUMBER));
				#endif
				simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(2),simple_list_getint(list2,SIMPLE_BLOCKMAP_PC));
				simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(3),SIMPLE_BLOCKTYPE_SCRIPT);
				simple_item_setpointer_gc(vm->sState,SIMPLE_VM_IR_ITEM(4),simple_list_getstring(list2,SIMPLE_BLOCKMAP_FILENAME));
				simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(5),simple_list_getint(list3,SIMPLE_BLOCKCL_METHODORBLOCK));
				simple_item_setint_gc(vm->sState,SIMPLE_VM_IR_ITEM(6),simple_list_getint(list3,SIMPLE_BLOCKCL_LINENUMBER));
			}
			/* Add aLoadAddressScope pointer to pLoadAddressScope */
			simple_vm_saveloadaddressscope(vm);
			return 1 ;
		}
	}
	
	/* For OOP Support - Check Method not found! */
	if ( vm->nCallMethod == 1 ) {
		/* Pass The Call Instruction and the AfterCallMethod Instruction */
		vm->nPC += 2 ;
		/* Decrement BlockExecute Counter */
		vm->nBlockExecute-- ;
		vm->nBlockExecute2-- ;
		simple_vm_error2(vm,SIMPLE_VM_ERROR_METHODNOTFOUND,block_name);
		return 0 ;
	}
	/* Find Block in C Blocks List */
	list = (List *) simple_hashtable_findpointer(simple_list_gethashtable(vm->pCBlocksList),block_name);
	if ( list != NULL ) {
		list2 = simple_list_newlist_gc(vm->sState,vm->pBlockCallList);
		simple_list_addint_gc(vm->sState,list2,SIMPLE_BLOCKTYPE_C);
		simple_list_addstring_gc(vm->sState,list2,block_name);
		simple_list_addblockpointer_gc(vm->sState,list2,simple_list_getblockpointer(list,SIMPLE_BLOCKMAP_PC));
		simple_list_addint_gc(vm->sState,list2,vm->nsp);
		/* Create Temp Memory */
		simple_list_newlist_gc(vm->sState,list2);
		/*
		**  File Name 
		**  The old source file name 
		*/
		simple_list_addpointer_gc(vm->sState,list2,vm->file_name);
		/* The new source file name */
		simple_list_addpointer_gc(vm->sState,list2,vm->file_name);
		/* Method or Block */
		simple_list_addint_gc(vm->sState,list2,0);
		/* Line Number */
		simple_list_addint_gc(vm->sState,list2,vm->nLineNumber);
		/* Add aLoadAddressScope pointer to pLoadAddressScope */
		simple_vm_saveloadaddressscope(vm);
		return 1 ;
	}
	/* Avoid Error if it is automatic call to the main block */
	if ( vm->nCallMainBlock == 0 ) {
		if ( strcmp(block_name,"main") == 0 ) {
			return 0 ;
		}
	}
	/*
	**  Pass The Call Instruction 
	**  We need this when we execute done() 
	**  In this case, no parameters and the call instruction is directly after the load block instruction 
	**  So it's correct to use vm->nPC++ 
	*/
	vm->nPC++ ;
	/*
	**  Display Error Message 
	**  Decrement BlockExecute Counter 
	*/
	vm->nBlockExecute-- ;
	vm->nBlockExecute2-- ;
	simple_vm_error2(vm,SIMPLE_VM_ERROR_BLOCKNOTFOUND,block_name);
	return 0 ;
}

SIMPLE_API void simple_vm_call ( VM *vm )
{
	List *list  ;
	/* Check if we call method using ObjName.MethodName() */
	if ( SIMPLE_VM_IR_PARACOUNT == 3 ) {
		if ( SIMPLE_VM_IR_READIVALUE(2) ) {
			/*
			**  Now we make the object state visible by moving it from aBeforeObjState to pObjState 
			**  We do this here and not in LoadMethod to avoid accessing the object state when passing parameters 
			**  This fix a problem when we pass the self object to avoid passing ObjName that comes before the method 
			*/
			if ( simple_list_getsize(vm->aBeforeObjState) > 0 ) {
				list = simple_list_newlist_gc(vm->sState,vm->pObjState);
				simple_list_copy_gc(vm->sState,list,simple_list_getlist(vm->aBeforeObjState,simple_list_getsize(vm->aBeforeObjState)));
				simple_list_deleteitem_gc(vm->sState,vm->aBeforeObjState,simple_list_getsize(vm->aBeforeObjState));
			}
		}
	}
	simple_vm_call2(vm);
}

SIMPLE_API void simple_vm_call2 ( VM *vm )
{
	List *list, *pActiveMem  ;
	int x,nsp,nMax1,nBlockEx  ;
	/* Decrement BlockExecute Counter */
	if ( vm->nBlockExecute > 0 ) {
		vm->nBlockExecute-- ;
		vm->nBlockExecute2-- ;
	}
	/* Restore aLoadAddressScope from pLoadAddressScope */
	simple_vm_restoreloadaddressscope(vm);
	list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
	/* Calling Method from brace */
	if ( simple_list_getsize(list) >= SIMPLE_BLOCKCL_METHODORBLOCK ) {
		/* The first test to be sure it's not a C Block Call */
		if ( simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK) == 1 ) {
			simple_vm_oop_callmethodfrombrace(vm);
		}
	}
	/* Store the Caller Position */
	simple_list_addint_gc(vm->sState,list,vm->nPC);
	/* Store BlockExe Counter Value */
	simple_list_addint_gc(vm->sState,list,vm->nBlockExecute);
	nBlockEx = vm->nBlockExecute ;
	vm->nBlockExecute = 0 ;
	/* Call Block */ 
	if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_SCRIPT ) {
		/* Store List information to allow calling block from list item and creating lists from that block */
		simple_list_addint_gc(vm->sState,list,vm->nListStart);
		simple_list_addpointer_gc(vm->sState,list,vm->pNestedLists);
		vm->nListStart = 0 ;
		vm->pNestedLists = simple_list_new_gc(vm->sState,0);
		vm->nPC = simple_list_getint(list,SIMPLE_BLOCKCL_PC) ;
		/* Save State */
		simple_vm_savestate2(vm,list);
		/* Avoid accessing object data or methods */
		if ( simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK) == 0 ) {
			list = simple_list_newlist_gc(vm->sState,vm->pObjState);
			simple_list_addpointer_gc(vm->sState,list,NULL);
			simple_list_addpointer_gc(vm->sState,list,NULL);
			simple_list_addpointer_gc(vm->sState,list,NULL);
		}
		/* Clear aLoadAddressScope */
		simple_list_deleteallitems_gc(vm->sState,vm->aLoadAddressScope);
		
	} else if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_C ) {
		/* Trace */ 
		simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_BEFORECBLOCK);
		/*
		**  Save Active Memory 
		**  We save Active Memory to restore it , we don't depend on scopes list of lists 
		**  because we may call block from class constructor
		**  and class constructor don't create new scope for executing constructor
		*/
		pActiveMem = vm->pActiveMem ;
		/* Create New Scope */
		simple_vm_newscope(vm);
		/* Get Parameters */
		vm->nCBlockParaCount = 0 ;
		nsp = simple_list_getint(list,SIMPLE_BLOCKCL_SP) ;
		/* Use Order (First In - First Out) As Queue , the first parameter comes first */
		if ( nsp < vm->nsp ) {
			nMax1 = vm->nsp ;
			for ( x = nsp+1 ; x <= nMax1 ; x++ ) {
				vm->nsp = x ;
				if ( SIMPLE_VM_STACK_ISSTRING ) {
					simple_vm_addnewstringvar2(vm,"",SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE);
				}
				else if ( SIMPLE_VM_STACK_ISNUMBER ) {
					simple_vm_addnewnumbervar(vm,"",SIMPLE_VM_STACK_READN);
				}
				else if ( SIMPLE_VM_STACK_ISPOINTER ) {
					simple_vm_addnewpointervar(vm,"",SIMPLE_VM_STACK_READP,SIMPLE_VM_STACK_OBJTYPE);
				}
				vm->nCBlockParaCount++ ;
			}
			vm->nsp = nsp ;
		}
		/* Prepare to check block termination by try/catch */
		vm->nActiveCatch = 0 ;
		/* Enable C Pointer Type Check */
		vm->nIgnoreCPointerTypeCheck = 0 ;
		/* Call Block */
		simple_list_callblockpointer(list,SIMPLE_BLOCKCL_PC,vm);
		/* Trace */
		simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_AFTERCBLOCK);
		/* Restore nBlockEx state */
		vm->nBlockExecute = nBlockEx ;
		/* Check for block termination by try/catch */
		if ( vm->nActiveCatch == 1 ) {
			/*
			**  We don't remove the block from call list because simple_vm_catch() do when restore state 
			**  We don't delete the scope because simple_vm_catch() will do when restore state 
			**  Restore ActiveMem 
			*/
			vm->pActiveMem = pActiveMem ;
			return ;
		}
		/* Block Output */
		if ( nsp == vm->nsp ) {
			/* IgnoreNULL is Used by lengthOf(object) to get output from operator overloading method */
			if ( vm->nIgnoreNULL  == 0 ) {
				SIMPLE_VM_STACK_PUSHCVALUE("");
			}
			else {
				vm->nIgnoreNULL = 0 ;
			}
		}
		/* Move returned List to the previous scope */
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_movetoprevscope(vm);
		}
		/* Return (Delete Scope, Restore ActiveMem) */
		simple_list_deleteitem_gc(vm->sState,vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
		simple_vm_deletescope(vm);
		/* Restore ActiveMem */
		vm->pActiveMem = pActiveMem ;
		/* Restore nBlockSP value */
		if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
			list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
			vm->nBlockSP = simple_list_getint(list,SIMPLE_BLOCKCL_SP) ;
		} else {
			vm->nBlockSP = 0 ;
		}
		/* if executeCode() is called, start the main loop again */
		if ( vm->nEvalCalledFromSimpleCode == 1 ) {
			vm->nEvalCalledFromSimpleCode = 0 ;
			/*
			**  We use Stack POP to remove the empty string that we return after blocks 
			**  This enable the code generated from executeCode() to be able to return any value 
			**  Using the return command 
			*/
			SIMPLE_VM_STACK_POP ;
			simple_vm_mainloop(vm);
		}
	}
}

SIMPLE_API void simple_vm_return ( VM *vm )
{
	List *list  ;
	/* Check if the ringvm_evalinscope() block is active */
	if ( vm->nEvalInScope >= 1 ) {
		/*
		**  Bad Command - But don't display the message 
		**  To avoid displaying the message in correct context 
		*/
		return ;
	}
	/* Support for nested "Load" instructions */
	if ( vm->nBlockFlag >= 1 ) {
		simple_vm_removeblockflag(vm);
		/* Be sure it's not a block call or method call */
		if ( vm->nPC != 0 ) {
			return ;
		}
	}
	if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
		list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
		vm->nPC = simple_list_getint(list,SIMPLE_BLOCKCL_CALLERPC) ;
		vm->nBlockExecute = simple_list_getint(list,SIMPLE_BLOCKCL_BLOCKEXE) ;
		/* Restore List Status */
		vm->nListStart = simple_list_getint(list,SIMPLE_BLOCKCL_LISTSTART) ;
		if ( vm->pNestedLists != simple_list_getpointer(list,SIMPLE_BLOCKCL_NESTEDLISTS) ) {
			vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
			vm->pNestedLists = (List *) simple_list_getpointer(list,SIMPLE_BLOCKCL_NESTEDLISTS) ;
		}
		/* Restore File Name */
		vm->cPrevFileName = vm->file_name ;
		vm->file_name = (char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_FILENAME) ;
		/* Move returned List to the previous scope */
		if ( SIMPLE_VM_STACK_ISPOINTER ) {
			/*
			**  if the variable belong to the object state, don't move to prev. scope 
			**  We do this to enable returning a reference 
			**  So when we return an object we can access it directly using { } 
			*/
			if ( simple_vm_isstackpointertoobjstate(vm) == 0 ) {
				simple_vm_movetoprevscope(vm);
			}
		}
		simple_vm_deletescope(vm);
		/* Restore State */
		simple_vm_restorestate2(vm,list,SIMPLE_BLOCKCL_STATE);
		simple_list_deleteitem_gc(vm->sState,vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
		/* Restore nBlockSP value */
		if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
			list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
			vm->nBlockSP = simple_list_getint(list,SIMPLE_BLOCKCL_SP) ;
		} else {
			vm->nBlockSP = 0 ;
		}
		/* Trace */
		simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_RETURN);
	} else {
		/* Call Main block */
		if ( vm->nCallMainBlock == 0 ) {
			vm->nPC-- ;
			vm->nsp = 0 ;
			if ( simple_vm_loadblock2(vm,"main",0) ) {
				simple_vm_call(vm);
				vm->nCallMainBlock = 1 ;
				return ;
			}
		}
		/* End the execution Loop (Close the program) */
		exit_simple_vm(vm);
	}
}

SIMPLE_API void simple_vm_returnnull ( VM *vm )
{
	SIMPLE_VM_STACK_PUSHPVALUE(NULL);
	simple_vm_return(vm);
}

SIMPLE_API void simple_vm_newblock ( VM *vm )
{
	int w,x,y,z,nsp,insp,type, is_variadic  ; 
	List *list, *variadic_list  ;
	String *param, *v_param ;
	Item *item, *variadic_item ;
	const char *variadic_value ;
	
	/* Variables for Variadic parameter */
	List *void_value, *list3;
	Item *list_value, *pItem ;
	
	
	assert(vm != NULL);
	simple_vm_newscope(vm);
	/* Set the SP then Check Parameters */
	list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
	assert(list != NULL);
	nsp = simple_list_getint(list,SIMPLE_BLOCKCL_SP) ;
	vm->nBlockSP = nsp ; 
	insp = vm->nsp ;
	variadic_value = "" ;
	is_variadic = 0 ;
	variadic_list = simple_list_new_gc(vm->sState,0) ;
	if ( SIMPLE_VM_IR_PARACOUNT > 2 ) { 
		x = SIMPLE_VM_IR_PARACOUNT; 
		y = 0 ;
		z = 0 ;
		for (; x >= 3 && y <= SIMPLE_VM_IR_PARACOUNT ; x--, y++ ) { 
			param = simple_string_new(SIMPLE_VM_IR_READCVALUE(x-1));
			if (strcmp(param->str,simple_secondary_keyword_value(KEYWORD_VARIADIC)) == 0 ) {
				is_variadic = 1 ; continue ;
			}
			if (x == SIMPLE_VM_IR_PARACOUNT || is_variadic) {
				v_param = simple_string_new(SIMPLE_VM_IR_READCVALUE(x-1));
			} 
			if (is_variadic) { variadic_value = param->str; is_variadic = 0; }
			if ( nsp < vm->nsp || strcmp(v_param->str,variadic_value) == 0) { 
				if ( strcmp(param->str,variadic_value) == 0 ) { 
					variadic_item = simple_item_new_gc (vm->sState,ITEMTYPE_LIST);
					variadic_item->data.list = variadic_list ;
					SIMPLE_VM_STACK_PUSHPVALUE(variadic_item) ; 
					SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_LISTITEM ;					
					simple_vm_addnewpointervar(vm,param->str,SIMPLE_VM_STACK_READP,SIMPLE_VM_STACK_OBJTYPE);
					w = SIMPLE_VM_IR_PARACOUNT - 3  ; 
					SIMPLE_VM_STACK_POP_(w) ; 
				} 
				if ( SIMPLE_VM_STACK_ISSTRING ) {
					simple_vm_addnewstringvar(vm,param->str,SIMPLE_VM_STACK_READC);
					SIMPLE_VM_STACK_POP ; 
				}
				else if ( SIMPLE_VM_STACK_ISNUMBER ) {
					simple_vm_addnewnumbervar(vm,param->str,SIMPLE_VM_STACK_READN);
					SIMPLE_VM_STACK_POP ;
				}
				else if ( SIMPLE_VM_STACK_ISPOINTER ) {
					simple_vm_addnewpointervar(vm,param->str,SIMPLE_VM_STACK_READP,SIMPLE_VM_STACK_OBJTYPE);
					SIMPLE_VM_STACK_POP ;
				} 
				if (y == (SIMPLE_VM_IR_PARACOUNT - 3) && strcmp(v_param->str,variadic_value) == 0) {
					//printf("X%i Y%i P%i VN%i N%i INSP%i\n",x,y,SIMPLE_VM_IR_PARACOUNT,vm->nsp,nsp,insp);
					if (vm->nsp == 1 && y > 1) { 
						y++; 
						vm->nsp = insp - y + 2;
					} else {
						vm->nsp = insp - y + 1;
					}
					for (; z <= nsp; z++) {
						y++; 
					} 
					while (nsp < vm->nsp){ 
						if ( SIMPLE_VM_STACK_ISSTRING_AT(y) ) {
							simple_list_addstring(variadic_list,SIMPLE_VM_STACK_READC_AT(y));
							SIMPLE_VM_STACK_POP ; 
						}
						else if ( SIMPLE_VM_STACK_ISNUMBER_AT(y) ) {
							simple_list_adddouble(variadic_list,SIMPLE_VM_STACK_READN_AT(y));
							SIMPLE_VM_STACK_POP ;
						}
						else if ( SIMPLE_VM_STACK_ISPOINTER_AT(y) ) {
							if (SIMPLE_VM_STACK_OBJTYPE_AT(y) == SIMPLE_OBJTYPE_VARIABLE) {
								void_value = (List *) SIMPLE_VM_STACK_READP_AT(y);
								list3 = simple_list_newlist_gc(vm->sState,variadic_list);
								//simple_list_refcopy(list3,simple_list_getlist(void_value,SIMPLE_VAR_VALUE));
								simple_list_copy(list3,simple_list_getlist(void_value,SIMPLE_VAR_VALUE));
							}
							else if (SIMPLE_VM_STACK_OBJTYPE_AT(y) == SIMPLE_OBJTYPE_LISTITEM) {
								list_value = (Item *) SIMPLE_VM_STACK_READP_AT(y);
								void_value = simple_item_getlist(list_value);
								list3 = simple_list_newlist_gc(vm->sState,variadic_list);
								//simple_list_refcopy(list3,void_value);
								simple_list_copy(list3,void_value);
							}
							SIMPLE_VM_STACK_POP ;
						}
						y++;
					}
					break ;
				}
			} else {
				simple_vm_error(vm,SIMPLE_VM_ERROR_LESSPARAMETERSCOUNT);
				break ;
			}
		}
	}
	if ( nsp < vm->nsp ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_EXTRAPARAMETERSCOUNT);
	}
	/* Support this in the method */
	simple_vm_oop_setthethisvariable(vm);
	/* Trace */
	simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_NEWBLOCK);
}

SIMPLE_API void simple_vm_blockflag ( VM *vm )
{
	simple_vm_blockflag2(vm,SIMPLE_VM_IR_READI);
}

SIMPLE_API void simple_vm_blockflag2 ( VM *vm,int x )
{
	List *list  ;
	vm->nBlockFlag++ ;
	list = simple_list_newlist_gc(vm->sState,vm->aPCBlockFlag);
	simple_list_addint_gc(vm->sState,list,x);
	/* Save State */
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pExitMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pLoopMark));
	simple_list_addint_gc(vm->sState,list,simple_list_getsize(vm->pTry));
}

SIMPLE_API void simple_vm_removeblockflag ( VM *vm )
{
	List *list  ;
	list = simple_list_getlist(vm->aPCBlockFlag,simple_list_getsize(vm->aPCBlockFlag));
	vm->nPC = simple_list_getint(list,1);
	vm->nBlockFlag-- ;
	/* Restore State */
	simple_vm_backstate(vm,simple_list_getint(list,2),vm->pExitMark);
	simple_vm_backstate(vm,simple_list_getint(list,3),vm->pLoopMark);
	simple_vm_backstate(vm,simple_list_getint(list,4),vm->pTry);
	simple_list_deleteitem_gc(vm->sState,vm->aPCBlockFlag,simple_list_getsize(vm->aPCBlockFlag));
}

SIMPLE_API void simple_vm_movetoprevscope ( VM *vm )
{
	Item *pItem  ;
	List *list,*list2,*list3  ;
	/*
	**  When the block return a value of type List or nested List 
	**  We copy the list to the previous scope, change the pointer 
	*/
	if ( simple_list_getsize(vm->pMem) < 2 ) {
		return ;
	}
	/* Get The Source List */
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		if ( simple_list_islist(list,SIMPLE_VAR_VALUE) ) {
			list = simple_list_getlist(list,SIMPLE_VAR_VALUE);
		} else {
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		list = simple_item_getlist(pItem);
	} else {
		return ;
	}
	list2 = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1);
	list3 = simple_vm_newvar2(vm,SIMPLE_TEMP_VARIABLE,list2);
	simple_list_setint_gc(vm->sState,list3,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,list3,SIMPLE_VAR_VALUE);
	list2 = simple_list_getlist(list3,SIMPLE_VAR_VALUE);
	/* Copy the list */
	simple_list_copy_gc(vm->sState,list2,list);
	/* Update self object pointer */
	if ( simple_vm_oop_isobject(list2) ) {
		simple_vm_oop_updateselfpointer(vm,list2,SIMPLE_OBJTYPE_VARIABLE,list3);
	}
	SIMPLE_VM_STACK_SETPVALUE(list3);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
}

SIMPLE_API void simple_vm_createtemlist ( VM *vm )
{
	List *list  ;
	/*
	**  Create the list in the TempMem related to the block 
	**  The advantage of TempMem over Scope is that TempMem out of search domain (Var Name is not important) 
	**  Variable name in TemMem is not important, we use it for storage (no search) 
	*/
	list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
	list = simple_list_getlist(list,SIMPLE_BLOCKCL_TEMPMEM);
	simple_vm_newtempvar(vm,SIMPLE_TEMP_VARIABLE,list);
}

SIMPLE_API void simple_vm_saveloadaddressscope ( VM *vm )
{
	simple_list_addpointer_gc(vm->sState,vm->pLoadAddressScope,vm->aLoadAddressScope);
	vm->aLoadAddressScope = simple_list_new_gc(vm->sState,0);
}

SIMPLE_API void simple_vm_restoreloadaddressscope ( VM *vm )
{
	simple_list_delete_gc(vm->sState,vm->aLoadAddressScope);
	vm->aLoadAddressScope = (List *) simple_list_getpointer(vm->pLoadAddressScope,simple_list_getsize(vm->pLoadAddressScope));
	simple_list_deleteitem_gc(vm->sState,vm->pLoadAddressScope,simple_list_getsize(vm->pLoadAddressScope));
}

SIMPLE_API void simple_vm_anonymous ( VM *vm )
{
	const char *cStr  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		cStr = SIMPLE_VM_STACK_READC ;
		SIMPLE_VM_STACK_POP ;
		simple_vm_loadblock2(vm,cStr,0);
	}
	else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADCALLPARA);
	}
}

int simple_vm_isstackpointertoobjstate ( VM *vm )
{
	int nScope  ;
	/* if the variable belong to the object state, return 1 */
	if ( simple_list_getsize(vm->aLoadAddressScope)  >= 1 ) {
		nScope = simple_list_getint(vm->aLoadAddressScope,1) ;
		if ( (nScope == SIMPLE_VARSCOPE_OBJSTATE) || (nScope ==SIMPLE_VARSCOPE_GLOBAL) ) {
			return 1 ;
		}
	}
	return 0 ;
}
