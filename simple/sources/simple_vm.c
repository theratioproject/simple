
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
/*
**  Blocks 
**  Main 
*/

VM * simple_vm_new ( SimpleState *sState )
{
	VM *vm  ;
	int x  ;
	vm = (VM *) simple_state_malloc(sState,sizeof(VM));
	if ( vm == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Simple State */
	vm->sState = sState ;
	sState->vm = vm ;
	vm->nPC = 1 ;
	vm->pCode = NULL ;
	vm->pBlocksMap = NULL ;
	vm->nOPCode = 0 ;
	vm->nsp = 0 ;
	vm->pMem = simple_list_new_gc(vm->sState,0);
	vm->pActiveMem = NULL ;
	vm->pTempMem = simple_list_new_gc(vm->sState,0);
	vm->nLineNumber = 1 ;
	/* Information to test the lifetime of the local scope */
	vm->nScopeID = 0 ;
	vm->aScopeID = simple_list_new_gc(vm->sState,0);
	simple_vm_newscope(vm);
	for ( x = 0 ; x < SIMPLE_VM_STACK_SIZE ; x++ ) {
		vm->aStack[x].nType = ITEMTYPE_NOTHING ;
		vm->aStack[x].nObjectType = 0 ;
		vm->aStack[x].NumberFlag = ITEM_NUMBERFLAG_NOTHING ;
	}
	/* Add Variables */
	simple_vm_addglobalvariables(vm);
	/* Lists */
	vm->nListStart = 0 ;
	vm->pNestedLists = simple_list_new_gc(vm->sState,0);
	/* Support for nested Load Instructions */
	vm->nBlockFlag = 0 ;
	vm->aPCBlockFlag = simple_list_new_gc(vm->sState,0);
	/* Calling Blocks */
	vm->pBlockCallList = simple_list_new_gc(vm->sState,0);
	vm->nBlockSP = 0 ;
	vm->nBlockExecute = 0 ;
	if ( sState->c_blocks == NULL ) {
		sState->c_blocks = simple_list_new_gc(vm->sState,0);
	}
	vm->pCBlocksList = sState->c_blocks ;
	vm->nCallMainBlock = 0 ;
	/* Support for Exit/Loop Commands inside For/While loops. */
	vm->pExitMark = simple_list_new_gc(vm->sState,0);
	vm->pLoopMark = simple_list_new_gc(vm->sState,0);
	/* Try-Catch-Done */
	vm->pTry = simple_list_new_gc(vm->sState,0);
	/* Saving scope when creating new objects and calling class init method */
	vm->aScopeNewObj = simple_list_new_gc(vm->sState,0);
	/* Flag ( 0 = Call Block  1 = Call Method After writing object name using dot ) */
	vm->nCallMethod = 0 ;
	/* List of Lists used like Stack, list structure [Pointer to State , Pointer to Methods] */
	vm->pObjState = simple_list_new_gc(vm->sState,0);
	/* Support for using Braces to access object state */
	vm->pBraceObject = NULL ;
	vm->aBraceObjects = simple_list_new_gc(vm->sState,0);
	/* Used by BraceStart, BraceEnd & FreeStack */
	vm->nInsideBraceFlag = 0 ;
	/* Variable scope, where is the varaible (when we use findvar) */
	vm->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	/* Flag used by Try/Catch to tell C-API that catch happens! */
	vm->nActiveCatch = 0 ;
	/*
	**  Flag ( 0 = check NULL variable in PUSHV  , greater than 0 = Ignore null variable ) 
	**  Class Region (After the Class Name) 
	*/
	vm->within_class = 0 ;
	vm->pModulessMap = NULL ;
	/* Set the main File Name */
	vm->file_name = simple_list_getstring(vm->sState->files_list,1) ;
	vm->cPrevFileName = simple_list_getstring(vm->sState->files_list,1) ;
	/* We keep information about active modules to access its classes directly with new/from */
	vm->aActiveModules = simple_list_new_gc(vm->sState,0);
	/* Scope of class attribute ( 0 = public 1 = private ) */
	vm->nPrivateFlag = 0 ;
	/* Final Scope of class attribute ( 0 = not final 1 = final ) */
	vm->finalFlag = 0 ;
	/* Set/Get Property */
	vm->nGetSetProperty = 0 ;
	vm->pGetSetObject = NULL ;
	vm->nGetSetObjType = 0 ;
	vm->aSetProperty = simple_list_new_gc(vm->sState,0);
	/* Assignment Pointer */
	vm->pAssignment = NULL ;
	/* C Pointers List (Copied Pointers Only that are active i.e. Not NULL) */
	vm->aCPointers = simple_list_new_gc(vm->sState,0) ;
	/* For Loop - Step List */
	vm->aForStep = simple_list_new_gc(vm->sState,0);
	/* Flag for LoadA , when = 1 , if it's a pointer we get First Var. not the Pointer */
	vm->nFirstAddress = 0 ;
	/* Used to know operator before = like += -= *= /= */
	vm->nBeforeEqual = 0 ;
	/*
	**  NOAssignment used to disable instruction AssignmentPointer 
	**  We uses this when we change assignment to set property 
	**  It's important for ListStart to create Temp List when we use setter 
	**  and try to set attribute value to a list and a block setproperty() will be called 
	**  With this list as parameter stored in temp memory 
	*/
	vm->nNOAssignment = 0 ;
	/* List contains the scope of the result of Load Address */
	vm->aLoadAddressScope = simple_list_new_gc(vm->sState,0);
	/* List contains what to add  later to pObjState, prepare by loadmethod, add before call */
	vm->aBeforeObjState = simple_list_new_gc(vm->sState,0) ;
	/* Saving pointers to aLoadAddressScope before block. para. to restore after them */
	vm->pLoadAddressScope = simple_list_new_gc(vm->sState,0);
	/* Another flag like nBlockExec but not used by see command or return command */
	vm->nBlockExecute2 = 0 ;
	/* Create List for Temp Items (added to ByteCode) inside TempMem */
	vm->aNewByteCodeItems = simple_list_new_gc(vm->sState,0);
	/* Eval can be called from C code (OOP Set/Get/Operator Overloading) or from ring code using executeCode() */
	vm->nEvalCalledFromSimpleCode = 0 ;
	/* Number of decimals after the point */
	vm->nDecimals = 2 ;
	/*
	**  Do we need to reallocation for executeCode() or not ! 
	**  Size of items that we can use without reallocation (double of the original size) 
	*/
	vm->nEvalReallocationSize = 0 ;
	/* Flag ( 1 = we need space over allocated size so we have to do reallocation ) */
	vm->nEvalReallocationFlag = 0 ;
	/* Parameters Count Passed to C Block */
	vm->nCBlockParaCount = 0 ;
	/*
	**  Flag to Ignore NULL output after calling C Block 
	**  This flag is used by the len() block when we use len(object) 
	**  So operator overloading can return the result from the method 
	*/
	vm->nIgnoreNULL = 0 ;
	/* If vm->nPC <= nEvalReturnPC we end the main loop (used by evalreturn) */
	vm->nEvalReturnPC = 0 ;
	/* Flag to return Item Reference (of object state) */
	vm->nRetItemRef = 0 ;
	/* Mutex Blocks Pointers - for threads/lock/unlock */
	vm->pBlockMutexLock = NULL ;
	vm->pBlockMutexUnlock = NULL ;
	vm->pBlockMutexDestroy = NULL ;
	vm->pMutex = NULL ;
	/* Ignore C Pointer Type Check in extension blocks */
	vm->nIgnoreCPointerTypeCheck = 0 ;
	/*
	**  Flag when we call class init using new obj() 
	**  Since we call init() using generated braces { } 
	**  setting this flag enable LoadAddress to pass these braces 
	**  To access the class attributes of the caller 
	**  because {} hides the class attributes and we need to avoid that! 
	*/
	vm->nCallClassInit = 0 ;
	/*
	**  Flag to avoid deleteing Byte Code using Return From Eval() 
	**  When we use executeCode() then inside executeCode we uses executeCode for setter/getter/operator overloading 
	**  Then deleting byte code will cause a problem in setter/getter/operator overloading 
	**  In this case we set this flag to avoid the delete operation and solve the problem 
	*/
	vm->nRetEvalDontDelete = 0 ;
	/* Counter to know if we are inside simple_vm_runcode() */
	vm->nRunCode = 0 ;
	/* Flag that we have runtime error to avoid calling the error block again */
	vm->nActiveError = 0 ;
	/* Dynamic List of Self Items and PC */
	vm->aDynamicSelfItems = simple_list_new_gc(vm->sState,0);
	/* The active modules name (after using import command) */
	vm->pModulesName = simple_string_new_gc(vm->sState,"");
	/*
	**  Trace Program (After Each Line) 
	**  lTrace = Logical Value (Trace is Active or Not) 
	**  pTrace = String contains the code to be executed (Trace Block) 
	**  lTraceActive = The Trace Block is Active - Don't Call Trace block from Trace Block 
	**  nTraceEvent = The Trace Event (1 = New Line , etc) 
	*/
	vm->lTrace = 0 ;
	vm->pTrace = simple_string_new_gc(vm->sState,"");
	vm->lTraceActive = 0 ;
	vm->nTraceEvent = 0 ;
	vm->pTraceData = simple_list_new_gc(vm->sState,0) ;
	/* Eval In Scope block is Active : ringvm_evalinscope() */
	vm->nEvalInScope = 0 ;
	/* Pass error in simple_vm_error() from ringvm_passerror() */
	vm->lPassError = 0 ;
	/* Hide Error message - don't display it in simple_vm_error() */
	vm->lHideErrorMsg = 0 ;
	/* Custom Global Scopes (using load modules) */
	vm->aGlobalScopes = simple_list_new_gc(vm->sState,0);
	vm->aActiveGlobalScopes = simple_list_new_gc(vm->sState,0);
	vm->nCurrentGlobalScope = 0 ;
	/* File name in the class region */
	vm->file_name_within_class = NULL ;
	return vm ;
}

VM * simple_vm_delete ( VM *vm )
{
	int x  ;
	List *pRecord  ;
	Item *pItem  ;
	assert(vm);
	vm->pMem = simple_list_delete_gc(vm->sState,vm->pMem);
	vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
	vm->pBlockCallList = simple_list_delete_gc(vm->sState,vm->pBlockCallList);
	vm->aPCBlockFlag = simple_list_delete_gc(vm->sState,vm->aPCBlockFlag);
	vm->pTempMem = simple_list_delete_gc(vm->sState,vm->pTempMem);
	vm->pExitMark = simple_list_delete_gc(vm->sState,vm->pExitMark);
	vm->pLoopMark = simple_list_delete_gc(vm->sState,vm->pLoopMark);
	vm->pTry = simple_list_delete_gc(vm->sState,vm->pTry);
	vm->aScopeNewObj = simple_list_delete_gc(vm->sState,vm->aScopeNewObj);
	vm->pObjState = simple_list_delete_gc(vm->sState,vm->pObjState);
	vm->aBraceObjects = simple_list_delete_gc(vm->sState,vm->aBraceObjects);
	vm->aScopeID = simple_list_delete_gc(vm->sState,vm->aScopeID);
	vm->aActiveModules = simple_list_delete_gc(vm->sState,vm->aActiveModules);
	vm->aSetProperty = simple_list_delete_gc(vm->sState,vm->aSetProperty);
	vm->aCPointers = simple_list_delete_gc(vm->sState,vm->aCPointers);
	vm->aForStep = simple_list_delete_gc(vm->sState,vm->aForStep);
	vm->aLoadAddressScope = simple_list_delete_gc(vm->sState,vm->aLoadAddressScope);
	vm->aBeforeObjState = simple_list_delete_gc(vm->sState,vm->aBeforeObjState);
	vm->pLoadAddressScope = simple_list_delete_gc(vm->sState,vm->pLoadAddressScope);
	vm->aNewByteCodeItems = simple_list_delete_gc(vm->sState,vm->aNewByteCodeItems);
	/* Free Stack */
	for ( x = 0 ; x < SIMPLE_VM_STACK_SIZE ; x++ ) {
		simple_item_content_delete(&(vm->aStack[x]));
	}
	simple_state_free(vm->sState,vm->pByteCode);
	/* Delete Mutex */
	simple_vm_mutexdestroy(vm);
	/*
	**  Remove Dynamic Self Items 
	**  Delete Items 
	*/
	for ( x = 1 ; x <= simple_list_getsize(vm->aDynamicSelfItems) ; x++ ) {
		pRecord = simple_list_getlist(vm->aDynamicSelfItems,x);
		pItem = (Item *) simple_list_getpointer(pRecord,2);
		simple_state_free(vm->sState,pItem);
	}
	/* Delete List */
	vm->aDynamicSelfItems = simple_list_delete_gc(vm->sState,vm->aDynamicSelfItems);
	vm->pModulesName = simple_string_delete_gc(vm->sState,vm->pModulesName);
	vm->pTrace = simple_string_delete_gc(vm->sState,vm->pTrace);
	vm->pTraceData = simple_list_delete_gc(vm->sState,vm->pTraceData);
	/* Custom Global Scope (using Load Modules) */
	vm->aGlobalScopes = simple_list_delete_gc(vm->sState,vm->aGlobalScopes);
	vm->aActiveGlobalScopes = simple_list_delete_gc(vm->sState,vm->aActiveGlobalScopes);
	vm->sState->vm = NULL ;
	simple_state_free(vm->sState,vm);
	vm = NULL ;
	return vm ;
}

SIMPLE_API void simple_vm_loadcode ( VM *vm )
{
	int x,nSize  ;
	/*
	**  We may allocation double of the size that we need to avoid reallocation when we use executeCode() 
	**  executeCode() will check if there is a need to reallocation or not 
	**  This optimization increase the performance of applications that uses executeCode() 
	*/
	nSize = (simple_list_getsize(vm->pCode))*SIMPLE_VM_EXTRASIZE ;
	vm->pByteCode = (ByteCode *) simple_state_calloc(vm->sState,nSize,sizeof(ByteCode));
	if ( vm->pByteCode == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 1 ; x <= simple_list_getsize(vm->pCode) ; x++ ) {
		simple_vm_tobytecode(vm,x);
	}
	vm->nEvalReallocationSize = nSize ;
}

//re visit
SIMPLE_API void simple_vm_start ( SimpleState *sState,VM *vm )
{
	vm->pCode = sState->generated_code ;
	vm->pBlocksMap = sState->blocks_map ;
	vm->pClassesMap = sState->classes_map ;
	vm->pModulessMap = sState->modules_map ;
	simple_vm_loadcode(vm); 
	if (sState->loaded_cblocks == 0) {
		loadcblocks(sState); 
		/* Generate Items Array &  Hash Table */
		simple_list_genarray(sState->c_blocks);
		simple_list_genhashtable2(sState->c_blocks);
	}
	if ( simple_list_getsize(vm->pCode) > 0 ) {
		vm->nPC = 1 ;
		simple_vm_mainloop(vm);
	}
}

SIMPLE_API void simple_vm_mainloop ( VM *vm )
{
	#if SIMPLE_VMSHOWOPCODE
	/* Preprocessor Allows showing the OPCODE */
	if ( vm->sState->nPrintInstruction ) {
		do {
			simple_vm_fetch2(vm);
			if ( vm->nPC <= vm->nEvalReturnPC ) {
				vm->nEvalReturnPC = 0 ;
				break ;
			}
		} while (vm->nPC <= simple_list_getsize(vm->pCode))  ;
	}
	else {
		do {
			simple_vm_fetch(vm);
			if ( vm->nPC <= vm->nEvalReturnPC ) {
				vm->nEvalReturnPC = 0 ;
				break ;
			}
		} while (vm->nPC <= simple_list_getsize(vm->pCode))  ;
	}
	#else
	do {
		simple_vm_fetch(vm);
		if ( vm->nPC <= vm->nEvalReturnPC ) {
			vm->nEvalReturnPC = 0 ;
			break ;
		}
	} while (vm->nPC <= simple_list_getsize(vm->pCode))  ;
	#endif
}

SIMPLE_API void simple_vm_fetch ( VM *vm )
{
	vm->pByteCodeIR = vm->pByteCode + vm->nPC - 1 ;
	vm->nOPCode = SIMPLE_VM_IR_OPCODE ;
	vm->nPC++ ;
	simple_vm_execute(vm);
	if ( vm->nsp > SIMPLE_VM_STACK_CHECKOVERFLOW ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_STACKOVERFLOW);
	}
}

SIMPLE_API void simple_vm_fetch2 ( VM *vm )
{
	vm->pByteCodeIR = vm->pByteCode + vm->nPC - 1 ;
	vm->nOPCode = SIMPLE_VM_IR_OPCODE ;
	#if SIMPLE_VMSHOWOPCODE
	if ( vm->sState->nPrintInstruction ) {
		print_line();
		printf( "\nVM Pointer  : %p  " , (void *) vm ) ;
		printf( "\nOperation  : %s  " , SIMPLE_IC_OP[vm->nOPCode] ) ;
		printf( "\nPC         : %d  " ,vm->nPC ) ;
		printf( "\nLine Number    : %d  , File %s \n " ,vm->nLineNumber,vm->file_name ) ;
		if ( (vm->nOPCode == ICO_PUSHC) || (vm->nOPCode == ICO_LOADADDRESS) || (vm->nOPCode == ICO_LOADBLOCK) ) {
			printf( "\nData       : %s \n",SIMPLE_VM_IR_READC ) ;
		}
	}
	#endif
	vm->nPC++ ;
	simple_vm_execute(vm);
	#if SIMPLE_VMSHOWOPCODE
	if ( vm->sState->nPrintInstruction ) {
		printf( "\nsp (After) : %d  - BlockSP : %d \n LineNumber %d \n" , (int) vm->nsp,vm->nBlockSP,vm->nLineNumber ) ;
		print_line();
	}
	#endif
	if ( vm->nsp > SIMPLE_VM_STACK_CHECKOVERFLOW ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_STACKOVERFLOW);
	}
}

SIMPLE_API void simple_vm_execute ( VM *vm )
{
	switch ( vm->nOPCode ) {
		/* Stack and Variables */
		case ICO_PUSHC :
			SIMPLE_VM_STACK_PUSHC ; 
			break ;
		case ICO_PUSHN :
			SIMPLE_VM_STACK_PUSHN ;
			break ;
		case ICO_PUSHV :
			simple_vm_pushv(vm);
			break ;
		case ICO_LOADADDRESS :
			simple_vm_loadaddress(vm);
			break ;
		case ICO_ASSIGNMENT :
			simple_vm_assignment(vm);
			break ;
		case ICO_FINAL :
			vm->finalFlag = 1 ; 
			break ;
		case ICO_INC :
			simple_vm_inc(vm);
			break ;
		case ICO_LOADAPUSHV :
			simple_vm_loadapushv(vm);
			break ;
		case ICO_NEWLINE :
			simple_vm_newline(vm);
			break ;
		case ICO_FREESTACK :
			simple_vm_freestack(vm);
			break ;
		case ICO_FILENAME :
			simple_vm_setfilename(vm);
			break ;
		case ICO_FREELOADASCOPE :
			simple_vm_freeloadaddressscope(vm);
			break ;
		/* Jump */
		case ICO_JUMP :
			simple_vm_jump(vm);
			break ;
		case ICO_JUMPZERO :
			simple_vm_jumpzero(vm);
			break ;
		case ICO_JUMPFOR :
			simple_vm_jumpfor(vm);
			break ;
		case ICO_JUMPONE :
			simple_vm_jumpone(vm);
			break ;
		case ICO_JUMPZERO2 :
			simple_vm_jumpzero2(vm);
			break ;
		case ICO_JUMPONE2 :
			simple_vm_jumpone2(vm);
			break ;
		/* Compare */
		case ICO_LESSEQUAL :
			simple_vm_lessequal(vm);
			break ;
		case ICO_EQUAL :
			simple_vm_equal(vm);
			break ;
		case ICO_LESS :
			simple_vm_less(vm);
			break ;
		case ICO_GREATER :
			simple_vm_greater(vm);
			break ;
		case ICO_GREATEREQUAL :
			simple_vm_greaterequal(vm);
			break ;
		case ICO_NOTEQUAL :
			simple_vm_notequal(vm);
			break ;
		/* Math */
		case ICO_SUM :
			simple_vm_sum(vm);
			break ;
		case ICO_SUB :
			simple_vm_sub(vm);
			break ;
		case ICO_MUL :
			simple_vm_mul(vm);
			break ;
		case ICO_DIV :
			simple_vm_div(vm);
			break ;
		case ICO_MOD :
			simple_vm_mod(vm);
			break ;
		case ICO_NEG :
			simple_vm_neg(vm);
			break ;
		case ICO_PLUSPLUS :
			simple_vm_plusplus(vm);
			break ;
		case ICO_MINUSMINUS :
			simple_vm_minusminus(vm);
			break ;
		/* Logic */
		case ICO_AND :
			simple_vm_and(vm);
			break ;
		case ICO_OR :
			simple_vm_or(vm);
			break ;
		case ICO_NOT :
			simple_vm_not(vm);
			break ;
		/* Lists */
		case ICO_LISTSTART :
			simple_vm_liststart(vm);
			break ;
		case ICO_LISTITEM :
			simple_vm_listitem(vm);
			break ;
		case ICO_LISTEND :
			simple_vm_listend(vm);
			break ;
		case ICO_LOADINDEXADDRESS :
			simple_vm_loadindexaddress(vm);
			break ;
		/* Blocks */
		case ICO_LOADBLOCK :
			simple_vm_loadblock(vm);
			break ;
		case ICO_CALL :
			simple_vm_call(vm);
			break ;
		case ICO_RETURN :
			simple_vm_return(vm);
			break ;
		case ICO_RETNULL :
			simple_vm_returnnull(vm);
			break ;
		case ICO_RETFROMEVAL :
			simple_vm_returneval(vm);
			break ;
		case ICO_RETITEMREF :
			simple_vm_retitemref(vm);
			break ;
		case ICO_NEWBLOCK :
			simple_vm_newblock(vm);
			break ;
		case ICO_BLOCKFLAG :
			simple_vm_blockflag(vm);
			break ;
		case ICO_BLOCKEXE :
			vm->nBlockExecute++ ;
			break ;
		case ICO_ENDBLOCKEXE :
			simple_vm_endblockexec(vm);
			break ;
		case ICO_ANONYMOUS :
			simple_vm_anonymous(vm);
			break ;
		/* User Interface */
		case ICO_DISPLAY :
			simple_vm_display(vm);
			break ;
		case ICO_GIVE :
			simple_vm_read(vm);
			break ;
		/* End Program - Exit from Loop - Loop (Continue) */
		case ICO_EXITPROGRAM :
			exit_simple_vm(vm);
			break ;
		case ICO_EXITMARK :
			simple_vm_exitmark(vm);
			break ;
		case ICO_POPEXITMARK :
			simple_vm_popexitmark(vm);
			break ;
		case ICO_EXIT :
			simple_vm_exit(vm,1);
			break ;
		case ICO_LOOP :
			simple_vm_exit(vm,2);
			break ;
		/* For Better Performance */
		case ICO_PUSHP :
			simple_vm_pushp(vm);
			break ;
		case ICO_INCP :
			simple_vm_incp(vm);
			break ;
		case ICO_PUSHPV :
			simple_vm_pushpv(vm);
			break ;
		case ICO_INCJUMP :
			simple_vm_incjump(vm);
			break ;
		case ICO_INCPJUMP :
			simple_vm_incpjump(vm);
			break ;
		case ICO_JUMPVARLENUM :
			simple_vm_jumpvarlenum(vm);
			break ;
		case ICO_JUMPVARPLENUM :
			simple_vm_jumpvarplenum(vm);
			break ;
		case ICO_LOADBLOCKP :
			simple_vm_loadblockp(vm);
			break ;
		case ICO_PUSHPLOCAL :
			simple_vm_pushplocal(vm);
			break ;
		case ICO_INCLPJUMP :
			simple_vm_inclpjump(vm);
			break ;
		case ICO_JUMPVARLPLENUM :
			simple_vm_jumpvarlplenum(vm);
			break ;
		case ICO_INCPJUMPSTEP1 :
			simple_vm_incpjumpstep1(vm);
			break ;
		case ICO_JUMPVARPLENUMSTEP1 :
			simple_vm_jumpvarplenumstep1(vm);
			break ;
		/* Try-Catch-Done */
		case ICO_TRY :
			simple_vm_try(vm);
			break ;
		case ICO_FREE_TRY :
			simple_vm_free_try(vm);
			break ;
		/* Duplicate and Range */
		case ICO_DUPLICATE :
			simple_vm_dup(vm);
			break ;
		case ICO_RANGE :
			simple_vm_range(vm);
			break ;
		/* OOP */
		case ICO_NEWOBJ :
			simple_vm_oop_newobj(vm);
			break ;
		case ICO_SETSCOPE :
			simple_vm_oop_setscope(vm);
			break ;
		case ICO_LOADSUBADDRESS :
			simple_vm_oop_property(vm);
			break ;
		case ICO_LOADMETHOD :
			simple_vm_oop_loadmethod(vm);
			break ;
		case ICO_AFTERCALLMETHOD :
			simple_vm_oop_aftercallmethod(vm);
			break ;
		case ICO_AFTERCALLMETHOD2 :
			simple_vm_oop_aftercallmethod(vm);
			break ;
		case ICO_NEWCLASS :
			simple_vm_oop_newclass(vm);
			break ;
		case ICO_BRACESTART :
			simple_vm_oop_bracestart(vm);
			break ;
		case ICO_BRACEEND :
			simple_vm_oop_braceend(vm);
			break ;
		case ICO_IMPORT :
			simple_vm_oop_import(vm);
			break ;
		case ICO_PRIVATE :
			vm->nPrivateFlag = 1 ;
			break ;
		case ICO_SETPROPERTY :
			simple_vm_oop_setproperty(vm);
			break ;
		case ICO_CALLCLASSINIT :
			simple_vm_callclassinit(vm);
			break ;
		/* Other */
		case ICO_SETREFERENCE :
			simple_vm_setreference(vm);
			break ;
		case ICO_KILLREFERENCE :
			simple_vm_gc_killreference(vm);
			break ;
		case ICO_ASSIGNMENTPOINTER :
			simple_vm_assignmentpointer(vm);
			break ;
		case ICO_BEFOREEQUAL :
			vm->nBeforeEqual = SIMPLE_VM_IR_READI ;
			break ;
		/* Bitwise Operators */
		case ICO_BITAND :
			simple_vm_bitand(vm);
			break ;
		case ICO_BITOR :
			simple_vm_bitor(vm);
			break ;
		case ICO_BITXOR :
			simple_vm_bitxor(vm);
			break ;
		case ICO_BITNOT :
			simple_vm_bitnot(vm);
			break ;
		case ICO_BITSHL :
			simple_vm_bitshl(vm);
			break ;
		case ICO_BITSHR :
			simple_vm_bitshr(vm);
			break ;
		/* For Step */
		case ICO_STEPNUMBER :
			simple_vm_stepnumber(vm);
			break ;
		case ICO_POPSTEP :
			simple_vm_popstep(vm);
			break ;
		case ICO_LOADAFIRST :
			simple_vm_loadaddressfirst(vm);
			break ;
		/* Custom Global Scope */
		case ICO_NEWGLOBALSCOPE :
			simple_vm_newglobalscope(vm);
			break ;
		case ICO_ENDGLOBALSCOPE :
			simple_vm_endglobalscope(vm);
			break ;
		case ICO_SETGLOBALSCOPE :
			simple_vm_setglobalscope(vm);
			break ;
	}
}

//TODO : replace exit() with delete scanner and halt state instead of program
SIMPLE_API void simple_vm_error ( VM *vm,const char *cStr )
{
	List *list  ;
	/* Check if we have active error */
	if ( vm->nActiveError ) {
		return ;
	}
	vm->nActiveError = 1 ;
	/* Check Error() */
	if ( (simple_list_getsize(vm->pObjState) > 0) && (simple_vm_oop_callmethodinsideclass(vm) == 0 ) && (vm->nCallMethod == 0) ) {
		if ( simple_vm_findvar(vm,"self") ) {
			list = simple_vm_oop_getobj(vm);
			SIMPLE_VM_STACK_POP ;
			if ( simple_vm_oop_isobject(list) ) {
				if ( simple_vm_oop_isblock(vm, list,"Error") ) {
					simple_list_setstring_gc(vm->sState,simple_list_getlist(simple_vm_getglobalscope(vm),6),3,cStr);
					simple_vm_runcode(vm,"Error()");
					vm->nActiveError = 0 ;
					return ;
				}
			}
		}
	}
	if ( simple_list_getsize(vm->pTry) == 0 ) {
		if ( vm->lHideErrorMsg == 0 ) {
			if (vm->sState->nISCGI == 1 ) 
				simple_vm_cgi_showerrormessage(vm,cStr);
			else 
				simple_vm_showerrormessage(vm,cStr);
		}
		/* Trace */
		vm->nActiveError = 0 ;
		simple_vm_traceevent(vm,SIMPLE_VM_TRACEEVENT_ERROR);
		if ( vm->lPassError  == 1 ) {
			vm->lPassError = 0 ;
			return ;
		}
		if (vm->sState->skip_error == 0) { vm->nActiveError = 1 ; exit(0); } else { return; }
	}
	/*
	**  Check Eval In Scope 
	**  When we have simplevm_evalinscope() We don't support try/catch 
	**  We just display the error message and continue 
	*/
	if ( vm->nEvalInScope ) {
		if (vm->sState->nISCGI == 1 ) 
			simple_vm_cgi_showerrormessage(vm,cStr);
		else 
			simple_vm_showerrormessage(vm,cStr);
		vm->nActiveError = 0 ;
		simple_vm_freestack(vm);
		return ;
	}
	simple_vm_catch(vm,cStr);
	vm->nActiveError = 0 ;
}

SIMPLE_API int simple_vm_exec ( VM *vm,const char *cStr )
{
	int nPC,nCont,nLastPC,nRunVM,x,nSize  ;
	Scanner *scanner  ;
	int aPara[3]  ;
	ByteCode *pByteCode  ;
	nSize = strlen( cStr ) ;
	if ( nSize == 0 ) {
		return 0 ;
	}
	nPC = vm->nPC ;
	/* Add virtual file name */
	simple_list_addstring_gc(vm->sState,vm->sState->files_list,"simple_embedded_code");
	simple_list_addstring_gc(vm->sState,vm->sState->files_stack,"simple_embedded_code");
	scanner = new_simple_scanner(vm->sState);
	for ( x = 0 ; x < nSize ; x++ ) {
		simple_scanner_readchar(scanner,cStr[x]);
	}
	nCont = simple_scanner_checklasttoken(scanner);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(scanner);
	nLastPC = simple_list_getsize(vm->pCode);
	/* Get Blocks/Classes Size before change by parser */
	aPara[0] = nLastPC ;
	aPara[1] = simple_list_getsize(vm->pBlocksMap) ;
	aPara[2] = simple_list_getsize(vm->pClassesMap) ;
	/* Call Parser */
	if ( nCont == 1 ) {
		vm->sState->lNoLineNumber = 1 ;
		nRunVM = simple_parser_start(scanner->Tokens,vm->sState);
		vm->sState->lNoLineNumber = 0 ;
	} else {
		simple_vm_error(vm,"Error in executeCode!");
		delete_simple_scanner(scanner);
		return 0 ;
	}
	if ( nRunVM == 1 ) {
		/*
		**  Generate Code 
		**  Generate  Hash Table 
		*/
		simple_list_genhashtable2(vm->pBlocksMap);
		if ( vm->nEvalCalledFromSimpleCode ) {
			simple_scanner_addreturn3(vm->sState,aPara);
		}
		else {
			simple_scanner_addreturn2(vm->sState);
		}
		simple_vm_blockflag2(vm,nPC);
		vm->nPC = nLastPC+1 ;
		if ( simple_list_getsize(vm->pCode)  > vm->nEvalReallocationSize ) {
			pByteCode = (ByteCode *) simple_state_realloc(vm->sState,vm->pByteCode , sizeof(ByteCode) * simple_list_getsize(vm->pCode));
			if ( pByteCode == NULL ) {
				printf( SIMPLE_OOM ) ;
				delete_simple_scanner(scanner);
				exit(0);
			}
			vm->pByteCode = pByteCode ;
			if ( vm->nEvalCalledFromSimpleCode ) {
				/* Here executeCode() block is called from .sim files ( not by the VM for setter/getter/operator overloading) */
				vm->nEvalReallocationFlag = 1 ;
			}
		}
		else {
			vm->nEvalReallocationFlag = 0 ;
		}
		/* Load New Code */
		for ( x = vm->nPC ; x <= simple_list_getsize(vm->pCode) ; x++ ) {
			simple_vm_tobytecode(vm,x);
		}
		/*
		**  The mainloop will be called again 
		**  We do this to execute executeCode instructions directly 
		**  This is necessary when we have GUI library that takes the event loop 
		**  Then an event uses the executeCode() block to execute instructions 
		**  We don't call the main loop here we call it from simple_vm_call() 
		**  We do this to execute the executeCode() instructions in the correct scope 
		**  Because when we call a C Block like executeCode() we have parameters scope 
		**  Before we call the main loop from simple_vm_call the parameters scope will be deleted 
		**  And the local scope will be restored so we can use it from executeCode() 
		**  Update ReallocationSize 
		*/
		vm->nEvalReallocationSize = vm->nEvalReallocationSize - (simple_list_getsize(vm->pCode)-nLastPC) ;
	} else {
		simple_vm_error(vm,"Error in executeCode!");
		delete_simple_scanner(scanner);
		return 0 ;
	}
	delete_simple_scanner(scanner);
	simple_list_deletelastitem_gc(vm->sState,vm->sState->files_list);
	simple_list_deletelastitem_gc(vm->sState,vm->sState->files_stack);
	return nRunVM ;
}

SIMPLE_API void simple_vm_tobytecode ( VM *vm,int x )
{
	List *pIR  ;
	int x2  ;
	ByteCode *pByteCode  ;
	Item *pItem  ;
	pByteCode = vm->pByteCode + x - 1 ;
	pIR = simple_list_getlist(vm->pCode,x);
	pByteCode->size = simple_list_getsize(pIR) ;
	#if SIMPLE_SHOWICFINAL
	pByteCode->list = pIR ;
	#endif
	/* Check Instruction Size */
	if ( simple_list_getsize(pIR) > SIMPLE_VM_BC_ITEMS_COUNT ) {
		printf( SIMPLE_LONGINSTRUCTION ) ;
		printf( "In File : %s  - Byte-Code PC : %d  ",vm->file_name,x ) ;
		exit(0);
	}
	for ( x2 = 1 ; x2 <= simple_list_getsize(pIR) ; x2++ ) {
		pItem = simple_list_getitem(pIR,x2) ;
		pByteCode->aData[x2-1] = pItem ;
		/* Avoid Performance Instuctions (Happens when called from New Thread) */
		if ( x2 == 1 ) {
			switch ( pItem->data.iNumber ) {
				case ICO_PUSHPLOCAL :
					pItem->data.iNumber = ICO_LOADADDRESS ;
					break ;
				case ICO_JUMPVARLPLENUM :
					pItem->data.iNumber = ICO_JUMPVARLENUM ;
					break ;
				case ICO_INCLPJUMP :
					pItem->data.iNumber = ICO_INCJUMP ;
					break ;
			}
		}
	}
	/* Clear Other Items */
	for ( x2 = simple_list_getsize(pIR)+1 ; x2 <= SIMPLE_VM_BC_ITEMS_COUNT ; x2++ ) {
		pByteCode->aData[x2-1] = NULL ;
	}
}

SIMPLE_API void simple_vm_returneval ( VM *vm )
{
	int aPara[3]  ;
	ByteCode *pByteCode  ;
	simple_vm_return(vm);
	aPara[0] = SIMPLE_VM_IR_READIVALUE(1) ;
	aPara[1] = SIMPLE_VM_IR_READIVALUE(2) ;
	aPara[2] = SIMPLE_VM_IR_READIVALUE(3) ;
	if ( ( vm->nRetEvalDontDelete == 0 ) && (aPara[1] == simple_list_getsize(vm->pBlocksMap)) && (aPara[2] == simple_list_getsize(vm->pClassesMap)) ) {
		/*
		**  The code interpreted by eval doesn't add new blocks or new classes 
		**  This means that the code can be deleted without any problems 
		**  We do that to avoid memory leaks 
		*/
		while ( simple_list_getsize(vm->pCode) != aPara[0] ) {
			simple_list_deletelastitem_gc(vm->sState,vm->pCode);
		}
		if ( vm->nEvalReallocationFlag == 1 ) {
			vm->nEvalReallocationFlag = 0 ;
			pByteCode = (ByteCode *) simple_state_realloc(vm->sState,vm->pByteCode , sizeof(ByteCode) * simple_list_getsize(vm->pCode));
			if ( pByteCode == NULL ) {
				printf( SIMPLE_OOM ) ;
				exit(0);
			}
			vm->pByteCode = pByteCode ;
		}
	}
	/*
	**  nEvalReturnPC is checked by the simple_vm_mainloop to end the loop 
	**  if the vm->nPC becomes <= vm->nEvalReturnPC the loop will be terminated 
	**  Remember that this is just a sub loop (another main loop) created after using executeCode() 
	**  If we don't terminate the sub main loop , this is just an extra overhead 
	**  Also terminating the sub main loop is a must when we do GUI programming 
	**  Because in GUI programming, the main loop calls the GUI Main Loop 
	**  During GUI main loop when event happens that calls a simple code 
	**  Eval will be used and a sub main loop will be executed 
	**  If we don't terminate the sub main loop, we can't return to the GUI Main Loop 
	**  It's necessary to return to the GUI main loop 
	**  When the GUI Main Loop Ends, we return to the Simple Main Loop 
	*/
	vm->nEvalReturnPC = aPara[0] ;
}

SIMPLE_API void simple_vm_error2 ( VM *vm,const char *cStr,const char *cStr2 )
{
	String *pError  ;
	pError = simple_string_new_gc(vm->sState,cStr);
	simple_string_add_gc(vm->sState,pError,": ");
	simple_string_add_gc(vm->sState,pError,cStr2);
	simple_vm_error(vm,simple_string_get(pError));
	simple_string_delete_gc(vm->sState,pError);
}

SIMPLE_API void simple_vm_newbytecodeitem ( VM *vm,int x )
{
	Item *pItem  ;
	simple_list_addint_gc(vm->sState,vm->aNewByteCodeItems,0);
	pItem = simple_list_getitem(vm->aNewByteCodeItems,simple_list_getsize(vm->aNewByteCodeItems));
	SIMPLE_VM_IR_ITEM(x) = pItem ;
}

SIMPLE_API void simple_vm_runcode ( VM *vm,const char *cStr )
{
	int nEvalReturnPC,nEvalReallocationFlag,nPC,nRunVM,nsp,nBlockSP,nLineNumber,nRetEvalDontDelete,finalFlag  ;
	List *pStackList  ;
	/* Save state to take in mind nested events execution */
	vm->nRunCode++ ;
	nEvalReturnPC = vm->nEvalReturnPC ;
	nEvalReallocationFlag = vm->nEvalReallocationFlag ;
	nPC = vm->nPC ;
	nsp = vm->nsp ;
	finalFlag = vm->finalFlag ;
	nBlockSP = vm->nBlockSP ;
	pStackList = simple_vm_savestack(vm);
	nLineNumber = vm->nLineNumber ;
	nRetEvalDontDelete = vm->nRetEvalDontDelete ;
	simple_vm_mutexlock(vm);
	vm->nEvalCalledFromSimpleCode = 1 ;
	/* Check removing the new byte code */
	if ( vm->nRunCode != 1 ) {
		/* We have nested events that call this block */
		vm->nRetEvalDontDelete = 1 ;
	}
	nRunVM = simple_vm_exec(vm,cStr);
	vm->nEvalCalledFromSimpleCode = 0 ;
	simple_vm_mutexunlock(vm);
	if ( nRunVM ) {
		vm->nBlockExecute = 0 ;
		vm->nBlockExecute2 = 0 ;
		simple_vm_mainloop(vm);
	}
	/* Restore state to take in mind nested events execution */
	vm->nRunCode-- ;
	vm->nEvalReturnPC = nEvalReturnPC ;
	vm->nEvalReallocationFlag = nEvalReallocationFlag ;
	vm->nPC = nPC ;
	if ( vm->nRunCode != 0 ) {
		/* It's a nested event (Here we don't care about the output and we can restore the stack) */
		simple_vm_restorestack(vm,pStackList);
	}
	/* Here we free the list because, restorestack() don't free it */
	simple_list_delete_gc(vm->sState,pStackList);
	/* Restore Stack to avoid Stack Overflow */
	vm->nsp = nsp ;
	vm->nBlockSP = nBlockSP ;
	vm->nLineNumber = nLineNumber ;
	vm->finalFlag = finalFlag ;
	vm->nRetEvalDontDelete = nRetEvalDontDelete ;
}

SIMPLE_API void simple_vm_init ( SimpleState *sState )
{
	Scanner *scanner  ;
	VM *vm  ;
	int nRunVM,nFreeFilesList = 0 ;
	/* Check file */
	if ( sState->files_list == NULL ) {
		sState->files_list = simple_list_new_gc(sState,0);
		sState->files_stack = simple_list_new_gc(sState,0);
		nFreeFilesList = 1 ;
	}
	simple_list_addstring_gc(sState,sState->files_list,"Simple_EmbeddedCode");
	simple_list_addstring_gc(sState,sState->files_stack,"Simple_EmbeddedCode");
	/* Read File */
	scanner = new_simple_scanner(sState);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(scanner);
	/* Call Parser */
	nRunVM = simple_parser_start(scanner->Tokens,sState);
	delete_simple_scanner(scanner);
	/* Files List */
	simple_list_deleteitem_gc(sState,sState->files_stack,simple_list_getsize(sState->files_stack));
	if ( nFreeFilesList ) {
		/* Run the Program */
		if ( nRunVM == 1 ) {
			/* Add return to the end of the program */
			simple_scanner_addreturn(sState);
			vm = simple_vm_new(sState);
			simple_vm_start(sState,vm);
			sState->vm = vm ;
		}
	}
	return ;
}

SIMPLE_API void simple_vm_retitemref ( VM *vm )
{
	List *list  ;
	vm->nRetItemRef++ ;
	/* We free the stack to avoid effects on aLoadAddressScope which is used by isstackpointertoobjstate */
	simple_vm_freestack(vm);
	/*
	**  Check if we are in the operator method to increment the counter again 
	**  We do this to avoid another PUSHV on the list item 
	**  The first one after return expression in the operator method 
	**  The second one before return from executeCode() that is used by operator overloading 
	**  This to avoid using & two times like  &  & 
	*/
	if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
		list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
		if ( strcmp(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME),"operator") == 0 ) {
			vm->nRetItemRef++ ;
		}
	}
}

SIMPLE_API void simple_vm_printstack ( VM *vm )
{
	int x,nsp  ;
	printf( "\n*****************************************\n" ) ;
	printf( "Stack Size %d \n",vm->nsp ) ;
	nsp = vm->nsp ;
	if ( nsp > 0 ) {
		for ( x = 1 ; x <= nsp ; x++ ) {
			/* Print Values */
			if ( SIMPLE_VM_STACK_ISSTRING ) {
				printf( "(String) : %s  \n",SIMPLE_VM_STACK_READC ) ;
			}
			else if ( SIMPLE_VM_STACK_ISNUMBER ) {
				printf( "(Number) : %f  \n",SIMPLE_VM_STACK_READN ) ;
			}
			else if ( SIMPLE_VM_STACK_ISPOINTER ) {
				printf( "(Pointer) : %p  \n",SIMPLE_VM_STACK_READP ) ;
				if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
					printf( "(Pointer Type) : Variable \n" ) ;
					simple_list_print((List *) SIMPLE_VM_STACK_READP);
				}
				else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
					printf( "(Pointer Type) : ListItem \n" ) ;
					simple_item_print((Item *) SIMPLE_VM_STACK_READP);
				}
			}
			SIMPLE_VM_STACK_POP ;
			printf( "\n*****************************************\n" ) ;
		}
	}
}

SIMPLE_API void simple_vm_callclassinit ( VM *vm )
{
	if ( SIMPLE_VM_IR_READIVALUE(1) ) {
		vm->nCallClassInit++ ;
	}
	else {
		vm->nCallClassInit-- ;
	}
}

SIMPLE_API void simple_vm_showerrormessage ( VM *vm,const char *cStr )
{
	String *string, *string2;
	int x,lBlockCall,is_last_block  ;
	List *list  ;
	const char *cFile  ;
	/* Print the Error Message */ 
	printe( "\n%s",cStr ) ;
	string = simple_string_new_gc(vm->sState,"at line ");
	string2 = simple_string_new_gc(vm->sState,"");
	simple_string_setfromint_gc(vm->sState,string2,vm->nLineNumber);
	simple_string_add_gc(vm->sState,string,string2->str);
	/* Print Calling Information */ 
	lBlockCall = 0 ; is_last_block = 1 ;
	for ( x = simple_list_getsize(vm->pBlockCallList) ; x >= 1 ; x-- ) {
		list = simple_list_getlist(vm->pBlockCallList,x); 
		/*
		**  If we have ICO_LoadBlock but not ICO_CALL then we need to pass 
		**  ICO_LOADBLOCK is executed, but still ICO_CALL is not executed! 
		*/
		if ( simple_list_getsize(list) < SIMPLE_BLOCKCL_CALLERPC ) {
			continue ;
		}
		if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_SCRIPT ) {
			/*
			**  Prepare Message 
			**  In 
			*/
			simple_string_add_gc(vm->sState,string," at ");
			simple_string_add_gc(vm->sState,string,simple_list_getstring(list,SIMPLE_BLOCKCL_NAME));
			/* Adding () */
			simple_string_add_gc(vm->sState,string,"() in file ");
			/* File Name */
			if ( lBlockCall == 1 ) {
				cFile = (const char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_NEWFILENAME) ;
			}
			else {
				if ( vm->within_class ) {
					cFile = vm->file_name_within_class ; 
				}
				else {
					cFile = vm->file_name ;
				}
			}
			simple_string_add_gc(vm->sState,string,file_real_name(cFile));
			printe("\n\t%s", string->str);
			/* Called From */
			string = simple_string_new_gc(vm->sState,"at line ");
			string2 = simple_string_new_gc(vm->sState,"");
			simple_string_setfromint_gc(vm->sState,string2,simple_list_getint(list,SIMPLE_BLOCKCL_LINENUMBER));
			simple_string_add_gc(vm->sState,string,string2->str);
			is_last_block = 0; 
			lBlockCall = 1 ;
		}
		else {
			simple_string_add_gc(vm->sState,string," in ");
			simple_string_add_gc(vm->sState,string,file_real_name(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME)));
		}
	}
	if ( lBlockCall ) {
		simple_string_add_gc(vm->sState,string," in file ");
		simple_string_add_gc(vm->sState,string,file_real_name(simple_list_getstring(vm->sState->files_list,1)));
	} else {
		if ( vm->within_class ) {
			cFile = vm->file_name_within_class ;
		}
		else {
			cFile = file_real_name(vm->file_name) ;
		}
		simple_string_add_gc(vm->sState,string," in file ");
		simple_string_add_gc(vm->sState,string,cFile);
	}
	printe("\n\t%s\n", string->str);
	simple_string_delete_gc(vm->sState,string);
	simple_string_delete_gc(vm->sState,string2);
}

SIMPLE_API void simple_vm_cgi_showerrormessage ( VM *vm,const char *cStr )
{
	int x,lBlockCall,is_last_block,current_file  ;
	List *list  ;
	const char *cFile  ;
	current_file = simple_list_findstring(vm->sState->files_list,vm->file_name,1);
	printf("<br />current file : %i </br>",current_file);
	if (simple_list_findstring(vm->sState->files_list,vm->file_name,1)==0 || simple_list_findstring(vm->sState->files_list,vm->file_name,1)==1) 
		current_file += 1 ;
	printf("<br />current file : %i </br>",current_file);
	/* Print the Error Message */
	printf("<table border='1' cellspacing='0' cellpadding='2'>\n");
	printf("<tr><th align='left' style='background:rgb(190,25,49);' colspan='5'><span style='color:white;'> Line %d : %s in %s</br></span></th></tr>\n",vm->nLineNumber,cStr,simple_list_getstring(vm->sState->files_list,current_file));
	printf("<tr><th align='center' bgcolor='#eeeeec'>#</th><th align='left' bgcolor='#eeeeec'>Block</th><th align='left' bgcolor='#eeeeec'>File</th><th align='left' bgcolor='#eeeeec'>Location</th><th align='left' bgcolor='#eeeeec'>File Path</th></tr>\n");
	/* Print Calling Information */
	lBlockCall = 0 ; is_last_block = 1 ;
	for ( x = simple_list_getsize(vm->pBlockCallList) ; x >= 1 ; x-- ) {
		printf("<tr>");
		printf("<td bgcolor='#eeeeec' align='center'>%i</td>",x ) ;
		list = simple_list_getlist(vm->pBlockCallList,x);
		/*
		**  If we have ICO_LoadBlock but not ICO_CALL then we need to pass 
		**  ICO_LOADBLOCK is executed, but still ICO_CALL is not executed! 
		*/
		if ( simple_list_getsize(list) < SIMPLE_BLOCKCL_CALLERPC ) {
			continue ;
		}
		if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_SCRIPT ) {
			/*
			**  Prepare Message 
			**  In 
			*/
			/* Method or Block */
			/*if ( simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK) ) {
				printf( "method " ) ;
			}
			else {
				printf( "block " ) ;
			}*/
			/* Block Name */
			printf("<td bgcolor='#eeeeec' align='center'>%s()</td>",simple_list_getstring(list,SIMPLE_BLOCKCL_NAME) ) ;
			/* Adding () */
			/* File Name */
			if ( lBlockCall == 1 ) {
				cFile = (const char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_NEWFILENAME) ;
			}
			else {
				if ( vm->within_class ) {
					cFile = vm->file_name_within_class ;
				}
				else {
					cFile = vm->file_name ;
				}
			}
			printf("<td bgcolor='#eeeeec' align='center'>%s</td>",file_real_name(cFile) ) ;
			/* Called From */
			printf("<td bgcolor='#eeeeec' align='center'>Line %d</td>",simple_list_getint(list,SIMPLE_BLOCKCL_LINENUMBER) ) ;
			printf("<td title='%s' bgcolor='#eeeeec' ><a href='%s' target='__blank' >%s</a></td>",simple_list_getstring(vm->sState->files_list,1),simple_list_getstring(vm->sState->files_list,1),file_real_name(cFile) ) ;
			lBlockCall = 1 ;
		}
		else {
			printf( "In %s ",file_real_name(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME)) ) ;
		}
		printf("</tr>\n");
	}
	if ( lBlockCall ) {
		printf("<tr><th bgcolor='#eeeeec' align='right' colspan='5'> from file %s</th></tr>",simple_list_getstring(vm->sState->files_list,1)) ;
	}
	else {
		if ( vm->within_class ) {
			cFile = vm->file_name_within_class ;
		}
		else {
			cFile = file_real_name(vm->file_name) ;
		}
		printf("<tr><th bgcolor='#eeeeec' align='right' colspan='5'> from file %s</th></tr>",cFile) ;
	}
	printf("\n</table>");
}

SIMPLE_API void simple_vm_setfilename ( VM *vm )
{
	if ( vm->within_class ) {
		/*
		**  We are using special attribute for this region to avoid save/restore file name 
		**  If we used vm->file_name we could get problem in finding classes and moduless 
		*/
		vm->file_name_within_class = SIMPLE_VM_IR_READC ;
		return ;
	}
	vm->cPrevFileName = vm->file_name ;
	vm->file_name = SIMPLE_VM_IR_READC ;
}

SIMPLE_API void simple_vm_loadaddressfirst ( VM *vm )
{
	vm->nFirstAddress = 1 ;
	simple_vm_loadaddress(vm);
	vm->nFirstAddress = 0 ;
}

SIMPLE_API void simple_vm_endblockexec ( VM *vm )
{
	if ( vm->nBlockExecute > 0 ) {
		vm->nBlockExecute-- ;
	}
}

SIMPLE_API void simple_vm_addglobalvariables ( VM *vm )
{
	List *list, *list2  ;
	int x  ;
	/*
	**  Add Variables 
	**  We write variable name in lower case because Identifiers is converted to lower by Compiler(Scanner) 
	*/
	simple_vm_addnewnumbervar(vm,"true",1);
	simple_vm_addnewnumbervar(vm,"false",0);
	simple_vm_addnewstringvar(vm,"crlf","\r\n");
	/* Add null pointer */
	list = simple_vm_newvar2(vm,"null",vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,list,SIMPLE_VAR_VALUE);
	list2 = simple_list_new_gc(vm->sState,0);
	simple_list_addpointer_gc(vm->sState,list2,NULL);
	simple_list_addstring_gc(vm->sState,list2,"(null)");
	simple_list_addint_gc(vm->sState,list2,2);
	simple_list_copy(simple_list_getlist(list,SIMPLE_VAR_VALUE),list2);
	/* End Add null pointer */
	simple_vm_addnewpointervar(vm,"simple_gettemp_var",NULL,0);
	simple_vm_addnewstringvar(vm,"__err__","");
	simple_vm_addnewpointervar(vm,"simple_settemp_var",NULL,0);
	simple_vm_addnewnumbervar(vm,"simple_tempflag_var",0);
	simple_vm_addnewstringvar(vm,"tab","\t");
	simple_vm_addnewstringvar(vm,"cr","\r");
	simple_vm_addnewstringvar(vm,"nl","\n");
	simple_vm_addnewpointervar(vm,"this",NULL,0);
	/* Add Command Line Parameters */
	list = simple_vm_newvar2(vm,"cmdparams",vm->pActiveMem);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,list,SIMPLE_VAR_VALUE);
	list = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	for ( x = 1 ; x < vm->sState->argc ; x++ ) {
		simple_list_addstring_gc(vm->sState,list,vm->sState->argv[x]);
	}
}
/* Threads */

SIMPLE_API void simple_vm_mutexblocks ( VM *vm,void *(*pBlock)(void),void (*pBlockLock)(void *),void (*pBlockUnlock)(void *),void (*pBlockDestroy)(void *) )
{
	if ( vm->pMutex == NULL ) {
		vm->pMutex = pBlock() ;
		vm->pBlockMutexLock = pBlockLock ;
		vm->pBlockMutexUnlock = pBlockUnlock ;
		vm->pBlockMutexDestroy = pBlockDestroy ;
	}
}

SIMPLE_API void simple_vm_mutexlock ( VM *vm )
{
	if ( vm->pMutex != NULL ) {
		vm->pBlockMutexLock(vm->pMutex);
	}
}

SIMPLE_API void simple_vm_mutexunlock ( VM *vm )
{
	if ( vm->pMutex != NULL ) {
		vm->pBlockMutexUnlock(vm->pMutex);
	}
}

SIMPLE_API void simple_vm_mutexdestroy ( VM *vm )
{
	if ( vm->pMutex != NULL ) {
		vm->pBlockMutexDestroy(vm->pMutex);
		vm->pMutex = NULL ;
	}
}

SIMPLE_API void simple_vm_runcodefromthread ( VM *vm,const char *cStr )
{
	SimpleState *pState  ;
	List *list,*list2,*list3,*list4,*list5  ;
	Item *pItem  ;
	/* Create the SimpleState */
	pState = init_simple_state();
	pState->nPrintInstruction = vm->sState->nPrintInstruction ;
	/* Share the same Mutex between VMs */
	simple_vm_mutexlock(vm);
	pState->vm->pMutex = vm->pMutex ;
	pState->vm->pBlockMutexDestroy = vm->pBlockMutexDestroy ;
	pState->vm->pBlockMutexLock = vm->pBlockMutexLock ;
	pState->vm->pBlockMutexUnlock = vm->pBlockMutexUnlock ;
	/* Share the global scope between threads */
	pItem = pState->vm->pMem->pFirst->pValue ;
	pState->vm->pMem->pFirst->pValue = vm->pMem->pFirst->pValue ;
	/* Save the state */
	list = pState->vm->pCode ;
	list2 = pState->vm->pBlocksMap ;
	list3 = pState->vm->pClassesMap ;
	list4 = pState->vm->pModulessMap ;
	list5 = pState->vm->pCBlocksList ;
	/* Share the code between the VMs */
	pState->vm->pBlocksMap = vm->sState->blocks_map ;
	pState->vm->pClassesMap = vm->sState->classes_map ;
	pState->vm->pModulessMap = vm->sState->modules_map ;
	pState->vm->pCBlocksList = vm->pCBlocksList ;
	pState->blocks_map = vm->sState->blocks_map ;
	pState->classes_map = vm->sState->classes_map ;
	pState->modules_map = vm->sState->modules_map ;
	pState->c_blocks = vm->sState->c_blocks ;
	/* Get a copy from the byte code List */
	pState->vm->nScopeID = vm->nScopeID + 10000 ;
	pState->vm->pCode = simple_list_new_gc(vm->sState,0) ;
	simple_list_copy(pState->vm->pCode,vm->sState->generated_code);
	pState->generated_code = pState->vm->pCode ;
	simple_vm_loadcode(pState->vm);
	/* Avoid the call to the main block */
	pState->vm->nCallMainBlock = 1 ;
	simple_vm_mutexunlock(vm);
	/* Run the code */
	execute_simple_code(pState,cStr);
	simple_list_delete_gc(vm->sState,pState->vm->pCode);
	/* Restore the first scope - global scope */
	pState->vm->pMem->pFirst->pValue = pItem ;
	/* Avoid deleteing the shared code and the Mutex */
	pState->vm->pCode = list ;
	pState->vm->pBlocksMap = list2 ;
	pState->vm->pClassesMap = list3 ;
	pState->vm->pModulessMap = list4 ;
	pState->vm->pCBlocksList = list5 ;
	pState->generated_code = list ;
	pState->blocks_map = list2 ;
	pState->classes_map = list3 ;
	pState->modules_map = list4 ;
	pState->c_blocks = list5 ;
	pState->vm->pMutex = NULL ;
	pState->vm->pBlockMutexDestroy = NULL ;
	pState->vm->pBlockMutexLock = NULL ;
	pState->vm->pBlockMutexUnlock = NULL ;
	/* Delete the SimpleState */
	finalize_simple_state(pState);
}

/* Fast Block Call for Extensions (Without Eval) */

SIMPLE_API void simple_vm_callblock ( VM *vm,char *cBlockName )
{
	/* Prepare (Remove effects of the currect block) */
	simple_list_deletelastitem_gc(vm->sState,vm->pBlockCallList);
	/* Load the block and call it */
	simple_vm_loadblock2(vm,cBlockName,0);
	simple_vm_call2(vm);
	/* Execute the block */
	simple_vm_mainloop(vm);
	/* Free Stack */
	simple_vm_freestack(vm);
	/* Avoid normal steps after this block, because we deleted the scope in Prepare */
	vm->nActiveCatch = 1 ;
}
/* Trace */

SIMPLE_API void simple_vm_traceevent ( VM *vm,char nEvent )
{
	List *list  ;
	if ( (vm->lTrace == 1) && (vm->lTraceActive == 0) ) {
		vm->lTraceActive = 1 ;
		vm->nTraceEvent = nEvent ;
		/* Prepare Trace Data */
		simple_list_deleteallitems_gc(vm->sState,vm->pTraceData);
		/* Add Line Number */
		simple_list_adddouble_gc(vm->sState,vm->pTraceData,vm->nLineNumber);
		/* Add File Name */
		simple_list_addstring_gc(vm->sState,vm->pTraceData,vm->file_name);
		/* Add Block/Method Name */
		if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
			list = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList)) ;
			simple_list_addstring_gc(vm->sState,vm->pTraceData,simple_list_getstring(list,SIMPLE_BLOCKCL_NAME));
			/* Method of Block */
			simple_list_adddouble_gc(vm->sState,vm->pTraceData,simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK));
		}
		else {
			simple_list_addstring_gc(vm->sState,vm->pTraceData,"");
			/* Method of Block */
			simple_list_adddouble_gc(vm->sState,vm->pTraceData,0);
		}
		/* Execute Trace Block */
		simple_vm_runcode(vm,simple_string_get(vm->pTrace));
		vm->lTraceActive = 0 ;
		vm->nTraceEvent = 0 ;
	}
}
