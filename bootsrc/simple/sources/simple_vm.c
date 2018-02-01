/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/*
**  Functions 
**  Main 
*/

VM * simple_vm_new ( RingState *pRingState )
{
	VM *pVM  ;
	int x  ;
	pVM = (VM *) simple_state_malloc(pRingState,sizeof(VM));
	if ( pVM == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Ring State */
	pVM->pRingState = pRingState ;
	pRingState->pVM = pVM ;
	pVM->nPC = 1 ;
	pVM->pCode = NULL ;
	pVM->pFunctionsMap = NULL ;
	pVM->nOPCode = 0 ;
	pVM->nSP = 0 ;
	pVM->pMem = simple_list_new_gc(pVM->pRingState,0);
	pVM->pActiveMem = NULL ;
	pVM->pTempMem = simple_list_new_gc(pVM->pRingState,0);
	pVM->nLineNumber = 1 ;
	/* Information to test the lifetime of the local scope */
	pVM->nScopeID = 0 ;
	pVM->aScopeID = simple_list_new_gc(pVM->pRingState,0);
	simple_vm_newscope(pVM);
	for ( x = 0 ; x < SIMPLE_VM_STACK_SIZE ; x++ ) {
		pVM->aStack[x].nType = ITEMTYPE_NOTHING ;
		pVM->aStack[x].nObjectType = 0 ;
		pVM->aStack[x].NumberFlag = ITEM_NUMBERFLAG_NOTHING ;
	}
	/* Add Variables */
	simple_vm_addglobalvariables(pVM);
	/* Lists */
	pVM->nListStart = 0 ;
	pVM->pNestedLists = simple_list_new_gc(pVM->pRingState,0);
	/* Support for nested Load Instructions */
	pVM->nBlockFlag = 0 ;
	pVM->aPCBlockFlag = simple_list_new_gc(pVM->pRingState,0);
	/* Calling Functions */
	pVM->pFuncCallList = simple_list_new_gc(pVM->pRingState,0);
	pVM->nFuncSP = 0 ;
	pVM->nFuncExecute = 0 ;
	if ( pRingState->pRingCFunctions == NULL ) {
		pRingState->pRingCFunctions = simple_list_new_gc(pVM->pRingState,0);
	}
	pVM->pCFunctionsList = pRingState->pRingCFunctions ;
	pVM->nCallMainFunction = 0 ;
	/* Support for Exit/Loop Commands inside For/While loops. */
	pVM->pExitMark = simple_list_new_gc(pVM->pRingState,0);
	pVM->pLoopMark = simple_list_new_gc(pVM->pRingState,0);
	/* Try-Catch-Done */
	pVM->pTry = simple_list_new_gc(pVM->pRingState,0);
	/* Saving scope when creating new objects and calling class init method */
	pVM->aScopeNewObj = simple_list_new_gc(pVM->pRingState,0);
	/* Flag ( 0 = Call Function  1 = Call Method After writing object name using dot ) */
	pVM->nCallMethod = 0 ;
	/* List of Lists used like Stack, list structure [Pointer to State , Pointer to Methods] */
	pVM->pObjState = simple_list_new_gc(pVM->pRingState,0);
	/* Support for using Braces to access object state */
	pVM->pBraceObject = NULL ;
	pVM->aBraceObjects = simple_list_new_gc(pVM->pRingState,0);
	/* Used by BraceStart, BraceEnd & FreeStack */
	pVM->nInsideBraceFlag = 0 ;
	/* Variable scope, where is the varaible (when we use findvar) */
	pVM->nVarScope = SIMPLE_VARSCOPE_NOTHING ;
	/* Flag used by Try/Catch to tell C-API that catch happens! */
	pVM->nActiveCatch = 0 ;
	/*
	**  Flag ( 0 = check NULL variable in PUSHV  , greater than 0 = Ignore null variable ) 
	**  Class Region (After the Class Name) 
	*/
	pVM->nInClassRegion = 0 ;
	pVM->pPackagesMap = NULL ;
	/* Set the main File Name */
	pVM->cFileName = simple_list_getstring(pVM->pRingState->pRingFilesList,1) ;
	pVM->cPrevFileName = simple_list_getstring(pVM->pRingState->pRingFilesList,1) ;
	/* We keep information about active package to access its classes directly with new/from */
	pVM->aActivePackage = simple_list_new_gc(pVM->pRingState,0);
	/* Scope of class attribute ( 0 = public 1 = private ) */
	pVM->nPrivateFlag = 0 ;
	/* Set/Get Property */
	pVM->nGetSetProperty = 0 ;
	pVM->pGetSetObject = NULL ;
	pVM->nGetSetObjType = 0 ;
	pVM->aSetProperty = simple_list_new_gc(pVM->pRingState,0);
	/* Assignment Pointer */
	pVM->pAssignment = NULL ;
	/* C Pointers List (Copied Pointers Only that are active i.e. Not NULL) */
	pVM->aCPointers = simple_list_new_gc(pVM->pRingState,0) ;
	/* For Loop - Step List */
	pVM->aForStep = simple_list_new_gc(pVM->pRingState,0);
	/* Flag for LoadA , when = 1 , if it's a pointer we get First Var. not the Pointer */
	pVM->nFirstAddress = 0 ;
	/* Used to know operator before = like += -= *= /= */
	pVM->nBeforeEqual = 0 ;
	/*
	**  NOAssignment used to disable instruction AssignmentPointer 
	**  We uses this when we change assignment to set property 
	**  It's important for ListStart to create Temp List when we use setter 
	**  and try to set attribute value to a list and a function setproperty() will be called 
	**  With this list as parameter stored in temp memory 
	*/
	pVM->nNOAssignment = 0 ;
	/* List contains the scope of the result of Load Address */
	pVM->aLoadAddressScope = simple_list_new_gc(pVM->pRingState,0);
	/* List contains what to add  later to pObjState, prepare by loadmethod, add before call */
	pVM->aBeforeObjState = simple_list_new_gc(pVM->pRingState,0) ;
	/* Saving pointers to aLoadAddressScope before func. para. to restore after them */
	pVM->pLoadAddressScope = simple_list_new_gc(pVM->pRingState,0);
	/* Another flag like nFuncExec but not used by see command or return command */
	pVM->nFuncExecute2 = 0 ;
	/* Create List for Temp Items (added to ByteCode) inside TempMem */
	pVM->aNewByteCodeItems = simple_list_new_gc(pVM->pRingState,0);
	/* Eval can be called from C code (OOP Set/Get/Operator Overloading) or from ring code using eval() */
	pVM->nEvalCalledFromRingCode = 0 ;
	/* Number of decimals after the point */
	pVM->nDecimals = 2 ;
	/*
	**  Do we need to reallocation for eval() or not ! 
	**  Size of items that we can use without reallocation (double of the original size) 
	*/
	pVM->nEvalReallocationSize = 0 ;
	/* Flag ( 1 = we need space over allocated size so we have to do reallocation ) */
	pVM->nEvalReallocationFlag = 0 ;
	/* Parameters Count Passed to C Function */
	pVM->nCFuncParaCount = 0 ;
	/*
	**  Flag to Ignore NULL output after calling C Function 
	**  This flag is used by the len() function when we use len(object) 
	**  So operator overloading can return the result from the method 
	*/
	pVM->nIgnoreNULL = 0 ;
	/* If pVM->nPC <= nEvalReturnPC we end the main loop (used by evalreturn) */
	pVM->nEvalReturnPC = 0 ;
	/* Flag to return Item Reference (of object state) */
	pVM->nRetItemRef = 0 ;
	/* Mutex Functions Pointers - for threads/lock/unlock */
	pVM->pFuncMutexLock = NULL ;
	pVM->pFuncMutexUnlock = NULL ;
	pVM->pFuncMutexDestroy = NULL ;
	pVM->pMutex = NULL ;
	/* Ignore C Pointer Type Check in extension functions */
	pVM->nIgnoreCPointerTypeCheck = 0 ;
	/*
	**  Flag when we call class init using new obj() 
	**  Since we call init() using generated braces { } 
	**  setting this flag enable LoadAddress to pass these braces 
	**  To access the class attributes of the caller 
	**  because {} hides the class attributes and we need to avoid that! 
	*/
	pVM->nCallClassInit = 0 ;
	/*
	**  Flag to avoid deleteing Byte Code using Return From Eval() 
	**  When we use eval() then inside eval we uses eval for setter/getter/operator overloading 
	**  Then deleting byte code will cause a problem in setter/getter/operator overloading 
	**  In this case we set this flag to avoid the delete operation and solve the problem 
	*/
	pVM->nRetEvalDontDelete = 0 ;
	/* Counter to know if we are inside simple_vm_runcode() */
	pVM->nRunCode = 0 ;
	/* Flag that we have runtime error to avoid calling the error function again */
	pVM->nActiveError = 0 ;
	/* Dynamic List of Self Items and PC */
	pVM->aDynamicSelfItems = simple_list_new_gc(pVM->pRingState,0);
	/* The active package name (after using import command) */
	pVM->pPackageName = simple_stsimple_new_gc(pVM->pRingState,"");
	/*
	**  Trace Program (After Each Line) 
	**  lTrace = Logical Value (Trace is Active or Not) 
	**  pTrace = String contains the code to be executed (Trace Function) 
	**  lTraceActive = The Trace Function is Active - Don't Call Trace function from Trace Function 
	**  nTraceEvent = The Trace Event (1 = New Line , etc) 
	*/
	pVM->lTrace = 0 ;
	pVM->pTrace = simple_stsimple_new_gc(pVM->pRingState,"");
	pVM->lTraceActive = 0 ;
	pVM->nTraceEvent = 0 ;
	pVM->pTraceData = simple_list_new_gc(pVM->pRingState,0) ;
	/* Eval In Scope function is Active : ringvm_evalinscope() */
	pVM->nEvalInScope = 0 ;
	/* Pass error in simple_vm_error() from ringvm_passerror() */
	pVM->lPassError = 0 ;
	/* Hide Error message - don't display it in simple_vm_error() */
	pVM->lHideErrorMsg = 0 ;
	/* Custom Global Scopes (using load package) */
	pVM->aGlobalScopes = simple_list_new_gc(pVM->pRingState,0);
	pVM->aActiveGlobalScopes = simple_list_new_gc(pVM->pRingState,0);
	pVM->nCurrentGlobalScope = 0 ;
	/* File name in the class region */
	pVM->cFileNameInClassRegion = NULL ;
	return pVM ;
}

VM * simple_vm_delete ( VM *pVM )
{
	int x  ;
	List *pRecord  ;
	Item *pItem  ;
	assert(pVM);
	pVM->pMem = simple_list_delete_gc(pVM->pRingState,pVM->pMem);
	pVM->pNestedLists = simple_list_delete_gc(pVM->pRingState,pVM->pNestedLists);
	pVM->pFuncCallList = simple_list_delete_gc(pVM->pRingState,pVM->pFuncCallList);
	pVM->aPCBlockFlag = simple_list_delete_gc(pVM->pRingState,pVM->aPCBlockFlag);
	pVM->pTempMem = simple_list_delete_gc(pVM->pRingState,pVM->pTempMem);
	pVM->pExitMark = simple_list_delete_gc(pVM->pRingState,pVM->pExitMark);
	pVM->pLoopMark = simple_list_delete_gc(pVM->pRingState,pVM->pLoopMark);
	pVM->pTry = simple_list_delete_gc(pVM->pRingState,pVM->pTry);
	pVM->aScopeNewObj = simple_list_delete_gc(pVM->pRingState,pVM->aScopeNewObj);
	pVM->pObjState = simple_list_delete_gc(pVM->pRingState,pVM->pObjState);
	pVM->aBraceObjects = simple_list_delete_gc(pVM->pRingState,pVM->aBraceObjects);
	pVM->aScopeID = simple_list_delete_gc(pVM->pRingState,pVM->aScopeID);
	pVM->aActivePackage = simple_list_delete_gc(pVM->pRingState,pVM->aActivePackage);
	pVM->aSetProperty = simple_list_delete_gc(pVM->pRingState,pVM->aSetProperty);
	pVM->aCPointers = simple_list_delete_gc(pVM->pRingState,pVM->aCPointers);
	pVM->aForStep = simple_list_delete_gc(pVM->pRingState,pVM->aForStep);
	pVM->aLoadAddressScope = simple_list_delete_gc(pVM->pRingState,pVM->aLoadAddressScope);
	pVM->aBeforeObjState = simple_list_delete_gc(pVM->pRingState,pVM->aBeforeObjState);
	pVM->pLoadAddressScope = simple_list_delete_gc(pVM->pRingState,pVM->pLoadAddressScope);
	pVM->aNewByteCodeItems = simple_list_delete_gc(pVM->pRingState,pVM->aNewByteCodeItems);
	/* Free Stack */
	for ( x = 0 ; x < SIMPLE_VM_STACK_SIZE ; x++ ) {
		simple_item_content_delete(&(pVM->aStack[x]));
	}
	simple_state_free(pVM->pRingState,pVM->pByteCode);
	/* Delete Mutex */
	simple_vm_mutexdestroy(pVM);
	/*
	**  Remove Dynamic Self Items 
	**  Delete Items 
	*/
	for ( x = 1 ; x <= simple_list_getsize(pVM->aDynamicSelfItems) ; x++ ) {
		pRecord = simple_list_getlist(pVM->aDynamicSelfItems,x);
		pItem = (Item *) simple_list_getpointer(pRecord,2);
		simple_state_free(pVM->pRingState,pItem);
	}
	/* Delete List */
	pVM->aDynamicSelfItems = simple_list_delete_gc(pVM->pRingState,pVM->aDynamicSelfItems);
	pVM->pPackageName = simple_stsimple_delete_gc(pVM->pRingState,pVM->pPackageName);
	pVM->pTrace = simple_stsimple_delete_gc(pVM->pRingState,pVM->pTrace);
	pVM->pTraceData = simple_list_delete_gc(pVM->pRingState,pVM->pTraceData);
	/* Custom Global Scope (using Load Package) */
	pVM->aGlobalScopes = simple_list_delete_gc(pVM->pRingState,pVM->aGlobalScopes);
	pVM->aActiveGlobalScopes = simple_list_delete_gc(pVM->pRingState,pVM->aActiveGlobalScopes);
	pVM->pRingState->pVM = NULL ;
	simple_state_free(pVM->pRingState,pVM);
	pVM = NULL ;
	return pVM ;
}

SIMPLE_API void simple_vm_loadcode ( VM *pVM )
{
	int x,nSize  ;
	/*
	**  We may allocation double of the size that we need to avoid reallocation when we use eval() 
	**  eval() will check if there is a need to reallocation or not 
	**  This optimization increase the performance of applications that uses eval() 
	*/
	nSize = (simple_list_getsize(pVM->pCode))*SIMPLE_VM_EXTRASIZE ;
	pVM->pByteCode = (ByteCode *) simple_state_calloc(pVM->pRingState,nSize,sizeof(ByteCode));
	if ( pVM->pByteCode == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 1 ; x <= simple_list_getsize(pVM->pCode) ; x++ ) {
		simple_vm_tobytecode(pVM,x);
	}
	pVM->nEvalReallocationSize = nSize ;
}

void simple_vm_start ( RingState *pRingState,VM *pVM )
{
	pVM->pCode = pRingState->pRingGenCode ;
	pVM->pFunctionsMap = pRingState->pRingFunctionsMap ;
	pVM->pClassesMap = pRingState->pRingClassesMap ;
	pVM->pPackagesMap = pRingState->pRingPackagesMap ;
	simple_vm_loadcode(pVM);
	simple_vm_loadcfunctions(pRingState);
	/* Generate Items Array &  Hash Table */
	simple_list_genarray(pRingState->pRingCFunctions);
	simple_list_genhashtable2(pRingState->pRingCFunctions);
	if ( simple_list_getsize(pVM->pCode) > 0 ) {
		pVM->nPC = 1 ;
		simple_vm_mainloop(pVM);
	}
}

void simple_vm_mainloop ( VM *pVM )
{
	#if SIMPLE_VMSHOWOPCODE
	/* Preprocessor Allows showing the OPCODE */
	if ( pVM->pRingState->nPrintInstruction ) {
		do {
			simple_vm_fetch2(pVM);
			if ( pVM->nPC <= pVM->nEvalReturnPC ) {
				pVM->nEvalReturnPC = 0 ;
				break ;
			}
		} while (pVM->nPC <= simple_list_getsize(pVM->pCode))  ;
	}
	else {
		do {
			simple_vm_fetch(pVM);
			if ( pVM->nPC <= pVM->nEvalReturnPC ) {
				pVM->nEvalReturnPC = 0 ;
				break ;
			}
		} while (pVM->nPC <= simple_list_getsize(pVM->pCode))  ;
	}
	#else
	do {
		simple_vm_fetch(pVM);
		if ( pVM->nPC <= pVM->nEvalReturnPC ) {
			pVM->nEvalReturnPC = 0 ;
			break ;
		}
	} while (pVM->nPC <= simple_list_getsize(pVM->pCode))  ;
	#endif
}

void simple_vm_fetch ( VM *pVM )
{
	pVM->pByteCodeIR = pVM->pByteCode + pVM->nPC - 1 ;
	pVM->nOPCode = SIMPLE_VM_IR_OPCODE ;
	pVM->nPC++ ;
	simple_vm_execute(pVM);
	if ( pVM->nSP > SIMPLE_VM_STACK_CHECKOVERFLOW ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_STACKOVERFLOW);
	}
}

void simple_vm_fetch2 ( VM *pVM )
{
	pVM->pByteCodeIR = pVM->pByteCode + pVM->nPC - 1 ;
	pVM->nOPCode = SIMPLE_VM_IR_OPCODE ;
	#if SIMPLE_VMSHOWOPCODE
	if ( pVM->pRingState->nPrintInstruction ) {
		simple_print_line();
		printf( "\nVM Pointer  : %p  " , (void *) pVM ) ;
		printf( "\nOperation  : %s  " , SIMPLE_IC_OP[pVM->nOPCode] ) ;
		printf( "\nPC         : %d  " ,pVM->nPC ) ;
		printf( "\nLine Number    : %d  , File %s \n " ,pVM->nLineNumber,pVM->cFileName ) ;
		if ( (pVM->nOPCode == ICO_PUSHC) || (pVM->nOPCode == ICO_LOADADDRESS) || (pVM->nOPCode == ICO_LOADFUNC) ) {
			printf( "\nData       : %s \n",SIMPLE_VM_IR_READC ) ;
		}
	}
	#endif
	pVM->nPC++ ;
	simple_vm_execute(pVM);
	#if SIMPLE_VMSHOWOPCODE
	if ( pVM->pRingState->nPrintInstruction ) {
		printf( "\nSP (After) : %d  - FuncSP : %d \n LineNumber %d \n" , (int) pVM->nSP,pVM->nFuncSP,pVM->nLineNumber ) ;
		simple_print_line();
	}
	#endif
	if ( pVM->nSP > SIMPLE_VM_STACK_CHECKOVERFLOW ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_STACKOVERFLOW);
	}
}

void simple_vm_execute ( VM *pVM )
{
	switch ( pVM->nOPCode ) {
		/* Stack and Variables */
		case ICO_PUSHC :
			SIMPLE_VM_STACK_PUSHC ;
			break ;
		case ICO_PUSHN :
			SIMPLE_VM_STACK_PUSHN ;
			break ;
		case ICO_PUSHV :
			simple_vm_pushv(pVM);
			break ;
		case ICO_LOADADDRESS :
			simple_vm_loadaddress(pVM);
			break ;
		case ICO_ASSIGNMENT :
			simple_vm_assignment(pVM);
			break ;
		case ICO_INC :
			simple_vm_inc(pVM);
			break ;
		case ICO_LOADAPUSHV :
			simple_vm_loadapushv(pVM);
			break ;
		case ICO_NEWLINE :
			simple_vm_newline(pVM);
			break ;
		case ICO_FREESTACK :
			simple_vm_freestack(pVM);
			break ;
		case ICO_FILENAME :
			simple_vm_setfilename(pVM);
			break ;
		case ICO_FREELOADASCOPE :
			simple_vm_freeloadaddressscope(pVM);
			break ;
		/* Jump */
		case ICO_JUMP :
			simple_vm_jump(pVM);
			break ;
		case ICO_JUMPZERO :
			simple_vm_jumpzero(pVM);
			break ;
		case ICO_JUMPFOR :
			simple_vm_jumpfor(pVM);
			break ;
		case ICO_JUMPONE :
			simple_vm_jumpone(pVM);
			break ;
		case ICO_JUMPZERO2 :
			simple_vm_jumpzero2(pVM);
			break ;
		case ICO_JUMPONE2 :
			simple_vm_jumpone2(pVM);
			break ;
		/* Compare */
		case ICO_LESSEQUAL :
			simple_vm_lessequal(pVM);
			break ;
		case ICO_EQUAL :
			simple_vm_equal(pVM);
			break ;
		case ICO_LESS :
			simple_vm_less(pVM);
			break ;
		case ICO_GREATER :
			simple_vm_greater(pVM);
			break ;
		case ICO_GREATEREQUAL :
			simple_vm_greaterequal(pVM);
			break ;
		case ICO_NOTEQUAL :
			simple_vm_notequal(pVM);
			break ;
		/* Math */
		case ICO_SUM :
			simple_vm_sum(pVM);
			break ;
		case ICO_SUB :
			simple_vm_sub(pVM);
			break ;
		case ICO_MUL :
			simple_vm_mul(pVM);
			break ;
		case ICO_DIV :
			simple_vm_div(pVM);
			break ;
		case ICO_MOD :
			simple_vm_mod(pVM);
			break ;
		case ICO_NEG :
			simple_vm_neg(pVM);
			break ;
		case ICO_PLUSPLUS :
			simple_vm_plusplus(pVM);
			break ;
		case ICO_MINUSMINUS :
			simple_vm_minusminus(pVM);
			break ;
		/* Logic */
		case ICO_AND :
			simple_vm_and(pVM);
			break ;
		case ICO_OR :
			simple_vm_or(pVM);
			break ;
		case ICO_NOT :
			simple_vm_not(pVM);
			break ;
		/* Lists */
		case ICO_LISTSTART :
			simple_vm_liststart(pVM);
			break ;
		case ICO_LISTITEM :
			simple_vm_listitem(pVM);
			break ;
		case ICO_LISTEND :
			simple_vm_listend(pVM);
			break ;
		case ICO_LOADINDEXADDRESS :
			simple_vm_loadindexaddress(pVM);
			break ;
		/* Functions */
		case ICO_LOADFUNC :
			simple_vm_loadfunc(pVM);
			break ;
		case ICO_CALL :
			simple_vm_call(pVM);
			break ;
		case ICO_RETURN :
			simple_vm_return(pVM);
			break ;
		case ICO_RETNULL :
			simple_vm_returnnull(pVM);
			break ;
		case ICO_RETFROMEVAL :
			simple_vm_returneval(pVM);
			break ;
		case ICO_RETITEMREF :
			simple_vm_retitemref(pVM);
			break ;
		case ICO_NEWFUNC :
			simple_vm_newfunc(pVM);
			break ;
		case ICO_BLOCKFLAG :
			simple_vm_blockflag(pVM);
			break ;
		case ICO_FUNCEXE :
			pVM->nFuncExecute++ ;
			break ;
		case ICO_ENDFUNCEXE :
			simple_vm_endfuncexec(pVM);
			break ;
		case ICO_ANONYMOUS :
			simple_vm_anonymous(pVM);
			break ;
		/* User Interface */
		case ICO_PRINT :
			simple_vm_see(pVM);
			break ;
		case ICO_GIVE :
			simple_vm_give(pVM);
			break ;
		/* End Program - Exit from Loop - Loop (Continue) */
		case ICO_BYE :
			simple_vm_bye(pVM);
			break ;
		case ICO_EXITMARK :
			simple_vm_exitmark(pVM);
			break ;
		case ICO_POPEXITMARK :
			simple_vm_popexitmark(pVM);
			break ;
		case ICO_EXIT :
			simple_vm_exit(pVM,1);
			break ;
		case ICO_LOOP :
			simple_vm_exit(pVM,2);
			break ;
		/* For Better Performance */
		case ICO_PUSHP :
			simple_vm_pushp(pVM);
			break ;
		case ICO_INCP :
			simple_vm_incp(pVM);
			break ;
		case ICO_PUSHPV :
			simple_vm_pushpv(pVM);
			break ;
		case ICO_INCJUMP :
			simple_vm_incjump(pVM);
			break ;
		case ICO_INCPJUMP :
			simple_vm_incpjump(pVM);
			break ;
		case ICO_JUMPVARLENUM :
			simple_vm_jumpvarlenum(pVM);
			break ;
		case ICO_JUMPVARPLENUM :
			simple_vm_jumpvarplenum(pVM);
			break ;
		case ICO_LOADFUNCP :
			simple_vm_loadfuncp(pVM);
			break ;
		case ICO_PUSHPLOCAL :
			simple_vm_pushplocal(pVM);
			break ;
		case ICO_INCLPJUMP :
			simple_vm_inclpjump(pVM);
			break ;
		case ICO_JUMPVARLPLENUM :
			simple_vm_jumpvarlplenum(pVM);
			break ;
		case ICO_INCPJUMPSTEP1 :
			simple_vm_incpjumpstep1(pVM);
			break ;
		case ICO_JUMPVARPLENUMSTEP1 :
			simple_vm_jumpvarplenumstep1(pVM);
			break ;
		/* Try-Catch-Done */
		case ICO_TRY :
			simple_vm_try(pVM);
			break ;
		case ICO_DONE :
			simple_vm_done(pVM);
			break ;
		/* Duplicate and Range */
		case ICO_DUPLICATE :
			simple_vm_dup(pVM);
			break ;
		case ICO_RANGE :
			simple_vm_range(pVM);
			break ;
		/* OOP */
		case ICO_NEWOBJ :
			simple_vm_oop_newobj(pVM);
			break ;
		case ICO_SETSCOPE :
			simple_vm_oop_setscope(pVM);
			break ;
		case ICO_LOADSUBADDRESS :
			simple_vm_oop_property(pVM);
			break ;
		case ICO_LOADMETHOD :
			simple_vm_oop_loadmethod(pVM);
			break ;
		case ICO_AFTERCALLMETHOD :
			simple_vm_oop_aftercallmethod(pVM);
			break ;
		case ICO_AFTERCALLMETHOD2 :
			simple_vm_oop_aftercallmethod(pVM);
			break ;
		case ICO_NEWCLASS :
			simple_vm_oop_newclass(pVM);
			break ;
		case ICO_BRACESTART :
			simple_vm_oop_bracestart(pVM);
			break ;
		case ICO_BRACEEND :
			simple_vm_oop_braceend(pVM);
			break ;
		case ICO_IMPORT :
			simple_vm_oop_import(pVM);
			break ;
		case ICO_PRIVATE :
			pVM->nPrivateFlag = 1 ;
			break ;
		case ICO_SETPROPERTY :
			simple_vm_oop_setproperty(pVM);
			break ;
		case ICO_CALLCLASSINIT :
			simple_vm_callclassinit(pVM);
			break ;
		/* Other */
		case ICO_SETREFERENCE :
			simple_vm_setreference(pVM);
			break ;
		case ICO_KILLREFERENCE :
			simple_vm_gc_killreference(pVM);
			break ;
		case ICO_ASSIGNMENTPOINTER :
			simple_vm_assignmentpointer(pVM);
			break ;
		case ICO_BEFOREEQUAL :
			pVM->nBeforeEqual = SIMPLE_VM_IR_READI ;
			break ;
		/* Bitwise Operators */
		case ICO_BITAND :
			simple_vm_bitand(pVM);
			break ;
		case ICO_BITOR :
			simple_vm_bitor(pVM);
			break ;
		case ICO_BITXOR :
			simple_vm_bitxor(pVM);
			break ;
		case ICO_BITNOT :
			simple_vm_bitnot(pVM);
			break ;
		case ICO_BITSHL :
			simple_vm_bitshl(pVM);
			break ;
		case ICO_BITSHR :
			simple_vm_bitshr(pVM);
			break ;
		/* For Step */
		case ICO_STEPNUMBER :
			simple_vm_stepnumber(pVM);
			break ;
		case ICO_POPSTEP :
			simple_vm_popstep(pVM);
			break ;
		case ICO_LOADAFIRST :
			simple_vm_loadaddressfirst(pVM);
			break ;
		/* Custom Global Scope */
		case ICO_NEWGLOBALSCOPE :
			simple_vm_newglobalscope(pVM);
			break ;
		case ICO_ENDGLOBALSCOPE :
			simple_vm_endglobalscope(pVM);
			break ;
		case ICO_SETGLOBALSCOPE :
			simple_vm_setglobalscope(pVM);
			break ;
	}
}

SIMPLE_API void simple_vm_error ( VM *pVM,const char *cStr )
{
	List *pList  ;
	/* Check if we have active error */
	if ( pVM->nActiveError ) {
		return ;
	}
	pVM->nActiveError = 1 ;
	/* Check BraceError() */
	if ( (simple_list_getsize(pVM->pObjState) > 0) && (simple_vm_oop_callmethodinsideclass(pVM) == 0 ) && (pVM->nCallMethod == 0) ) {
		if ( simple_vm_findvar(pVM,"self") ) {
			pList = simple_vm_oop_getobj(pVM);
			SIMPLE_VM_STACK_POP ;
			if ( simple_vm_oop_isobject(pList) ) {
				if ( simple_vm_oop_ismethod(pVM, pList,"braceerror") ) {
					simple_list_setstsimple_gc(pVM->pRingState,simple_list_getlist(simple_vm_getglobalscope(pVM),6),3,cStr);
					simple_vm_runcode(pVM,"braceerror()");
					pVM->nActiveError = 0 ;
					return ;
				}
			}
		}
	}
	if ( simple_list_getsize(pVM->pTry) == 0 ) {
		if ( pVM->lHideErrorMsg == 0 ) {
			simple_vm_showerrormessage(pVM,cStr);
		}
		/* Trace */
		pVM->nActiveError = 0 ;
		simple_vm_traceevent(pVM,SIMPLE_VM_TRACEEVENT_ERROR);
		if ( pVM->lPassError  == 1 ) {
			pVM->lPassError = 0 ;
			return ;
		}
		pVM->nActiveError = 1 ;
		exit(0);
	}
	/*
	**  Check Eval In Scope 
	**  When we have ringvm_evalinscope() We don't support try/catch 
	**  We just display the error message and continue 
	*/
	if ( pVM->nEvalInScope ) {
		simple_vm_showerrormessage(pVM,cStr);
		pVM->nActiveError = 0 ;
		simple_vm_freestack(pVM);
		return ;
	}
	simple_vm_catch(pVM,cStr);
	pVM->nActiveError = 0 ;
}

int simple_vm_eval ( VM *pVM,const char *cStr )
{
	int nPC,nCont,nLastPC,nRunVM,x,nSize  ;
	Scanner *pScanner  ;
	int aPara[3]  ;
	ByteCode *pByteCode  ;
	nSize = strlen( cStr ) ;
	if ( nSize == 0 ) {
		return 0 ;
	}
	nPC = pVM->nPC ;
	/* Add virtual file name */
	simple_list_addstsimple_gc(pVM->pRingState,pVM->pRingState->pRingFilesList,"eval");
	simple_list_addstsimple_gc(pVM->pRingState,pVM->pRingState->pRingFilesStack,"eval");
	pScanner = simple_scanner_new(pVM->pRingState);
	for ( x = 0 ; x < nSize ; x++ ) {
		simple_scanner_readchar(pScanner,cStr[x]);
	}
	nCont = simple_scanner_checklasttoken(pScanner);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(pScanner);
	nLastPC = simple_list_getsize(pVM->pCode);
	/* Get Functions/Classes Size before change by parser */
	aPara[0] = nLastPC ;
	aPara[1] = simple_list_getsize(pVM->pFunctionsMap) ;
	aPara[2] = simple_list_getsize(pVM->pClassesMap) ;
	/* Call Parser */
	if ( nCont == 1 ) {
		pVM->pRingState->lNoLineNumber = 1 ;
		nRunVM = simple_parser_start(pScanner->Tokens,pVM->pRingState);
		pVM->pRingState->lNoLineNumber = 0 ;
	} else {
		simple_vm_error(pVM,"Error in eval!");
		simple_scanner_delete(pScanner);
		return 0 ;
	}
	if ( nRunVM == 1 ) {
		/*
		**  Generate Code 
		**  Generate  Hash Table 
		*/
		simple_list_genhashtable2(pVM->pFunctionsMap);
		if ( pVM->nEvalCalledFromRingCode ) {
			simple_scanner_addreturn3(pVM->pRingState,aPara);
		}
		else {
			simple_scanner_addreturn2(pVM->pRingState);
		}
		simple_vm_blockflag2(pVM,nPC);
		pVM->nPC = nLastPC+1 ;
		if ( simple_list_getsize(pVM->pCode)  > pVM->nEvalReallocationSize ) {
			pByteCode = (ByteCode *) simple_state_realloc(pVM->pRingState,pVM->pByteCode , sizeof(ByteCode) * simple_list_getsize(pVM->pCode));
			if ( pByteCode == NULL ) {
				printf( SIMPLE_OOM ) ;
				simple_scanner_delete(pScanner);
				exit(0);
			}
			pVM->pByteCode = pByteCode ;
			if ( pVM->nEvalCalledFromRingCode ) {
				/* Here eval() function is called from .ring files ( not by the VM for setter/getter/operator overloading) */
				pVM->nEvalReallocationFlag = 1 ;
			}
		}
		else {
			pVM->nEvalReallocationFlag = 0 ;
		}
		/* Load New Code */
		for ( x = pVM->nPC ; x <= simple_list_getsize(pVM->pCode) ; x++ ) {
			simple_vm_tobytecode(pVM,x);
		}
		/*
		**  The mainloop will be called again 
		**  We do this to execute eval instructions directly 
		**  This is necessary when we have GUI library that takes the event loop 
		**  Then an event uses the eval() function to execute instructions 
		**  We don't call the main loop here we call it from simple_vm_call() 
		**  We do this to execute the eval() instructions in the correct scope 
		**  Because when we call a C Function like eval() we have parameters scope 
		**  Before we call the main loop from simple_vm_call the parameters scope will be deleted 
		**  And the local scope will be restored so we can use it from eval() 
		**  Update ReallocationSize 
		*/
		pVM->nEvalReallocationSize = pVM->nEvalReallocationSize - (simple_list_getsize(pVM->pCode)-nLastPC) ;
	} else {
		simple_vm_error(pVM,"Error in eval!");
		simple_scanner_delete(pScanner);
		return 0 ;
	}
	simple_scanner_delete(pScanner);
	simple_list_deletelastitem_gc(pVM->pRingState,pVM->pRingState->pRingFilesList);
	simple_list_deletelastitem_gc(pVM->pRingState,pVM->pRingState->pRingFilesStack);
	return nRunVM ;
}

void simple_vm_tobytecode ( VM *pVM,int x )
{
	List *pIR  ;
	int x2  ;
	ByteCode *pByteCode  ;
	Item *pItem  ;
	pByteCode = pVM->pByteCode + x - 1 ;
	pIR = simple_list_getlist(pVM->pCode,x);
	pByteCode->nSize = simple_list_getsize(pIR) ;
	#if SIMPLE_SHOWICFINAL
	pByteCode->pList = pIR ;
	#endif
	/* Check Instruction Size */
	if ( simple_list_getsize(pIR) > SIMPLE_VM_BC_ITEMS_COUNT ) {
		printf( SIMPLE_LONGINSTRUCTION ) ;
		printf( "In File : %s  - Byte-Code PC : %d  ",pVM->cFileName,x ) ;
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

void simple_vm_returneval ( VM *pVM )
{
	int aPara[3]  ;
	ByteCode *pByteCode  ;
	simple_vm_return(pVM);
	aPara[0] = SIMPLE_VM_IR_READIVALUE(1) ;
	aPara[1] = SIMPLE_VM_IR_READIVALUE(2) ;
	aPara[2] = SIMPLE_VM_IR_READIVALUE(3) ;
	if ( ( pVM->nRetEvalDontDelete == 0 ) && (aPara[1] == simple_list_getsize(pVM->pFunctionsMap)) && (aPara[2] == simple_list_getsize(pVM->pClassesMap)) ) {
		/*
		**  The code interpreted by eval doesn't add new functions or new classes 
		**  This means that the code can be deleted without any problems 
		**  We do that to avoid memory leaks 
		*/
		while ( simple_list_getsize(pVM->pCode) != aPara[0] ) {
			simple_list_deletelastitem_gc(pVM->pRingState,pVM->pCode);
		}
		if ( pVM->nEvalReallocationFlag == 1 ) {
			pVM->nEvalReallocationFlag = 0 ;
			pByteCode = (ByteCode *) simple_state_realloc(pVM->pRingState,pVM->pByteCode , sizeof(ByteCode) * simple_list_getsize(pVM->pCode));
			if ( pByteCode == NULL ) {
				printf( SIMPLE_OOM ) ;
				exit(0);
			}
			pVM->pByteCode = pByteCode ;
		}
	}
	/*
	**  nEvalReturnPC is checked by the simple_vm_mainloop to end the loop 
	**  if the pVM->nPC becomes <= pVM->nEvalReturnPC the loop will be terminated 
	**  Remember that this is just a sub loop (another main loop) created after using eval() 
	**  If we don't terminate the sub main loop , this is just an extra overhead 
	**  Also terminating the sub main loop is a must when we do GUI programming 
	**  Because in GUI programming, the main loop calls the GUI Main Loop 
	**  During GUI main loop when event happens that calls a ring code 
	**  Eval will be used and a sub main loop will be executed 
	**  If we don't terminate the sub main loop, we can't return to the GUI Main Loop 
	**  It's necessary to return to the GUI main loop 
	**  When the GUI Main Loop Ends, we return to the Ring Main Loop 
	*/
	pVM->nEvalReturnPC = aPara[0] ;
}

void simple_vm_error2 ( VM *pVM,const char *cStr,const char *cStr2 )
{
	String *pError  ;
	pError = simple_stsimple_new_gc(pVM->pRingState,cStr);
	simple_stsimple_add_gc(pVM->pRingState,pError,": ");
	simple_stsimple_add_gc(pVM->pRingState,pError,cStr2);
	simple_vm_error(pVM,simple_stsimple_get(pError));
	simple_stsimple_delete_gc(pVM->pRingState,pError);
}

void simple_vm_newbytecodeitem ( VM *pVM,int x )
{
	Item *pItem  ;
	simple_list_addint_gc(pVM->pRingState,pVM->aNewByteCodeItems,0);
	pItem = simple_list_getitem(pVM->aNewByteCodeItems,simple_list_getsize(pVM->aNewByteCodeItems));
	SIMPLE_VM_IR_ITEM(x) = pItem ;
}

SIMPLE_API void simple_vm_runcode ( VM *pVM,const char *cStr )
{
	int nEvalReturnPC,nEvalReallocationFlag,nPC,nRunVM,nSP,nFuncSP,nLineNumber,nRetEvalDontDelete  ;
	List *pStackList  ;
	/* Save state to take in mind nested events execution */
	pVM->nRunCode++ ;
	nEvalReturnPC = pVM->nEvalReturnPC ;
	nEvalReallocationFlag = pVM->nEvalReallocationFlag ;
	nPC = pVM->nPC ;
	nSP = pVM->nSP ;
	nFuncSP = pVM->nFuncSP ;
	pStackList = simple_vm_savestack(pVM);
	nLineNumber = pVM->nLineNumber ;
	nRetEvalDontDelete = pVM->nRetEvalDontDelete ;
	simple_vm_mutexlock(pVM);
	pVM->nEvalCalledFromRingCode = 1 ;
	/* Check removing the new byte code */
	if ( pVM->nRunCode != 1 ) {
		/* We have nested events that call this function */
		pVM->nRetEvalDontDelete = 1 ;
	}
	nRunVM = simple_vm_eval(pVM,cStr);
	pVM->nEvalCalledFromRingCode = 0 ;
	simple_vm_mutexunlock(pVM);
	if ( nRunVM ) {
		pVM->nFuncExecute = 0 ;
		pVM->nFuncExecute2 = 0 ;
		simple_vm_mainloop(pVM);
	}
	/* Restore state to take in mind nested events execution */
	pVM->nRunCode-- ;
	pVM->nEvalReturnPC = nEvalReturnPC ;
	pVM->nEvalReallocationFlag = nEvalReallocationFlag ;
	pVM->nPC = nPC ;
	if ( pVM->nRunCode != 0 ) {
		/* It's a nested event (Here we don't care about the output and we can restore the stack) */
		simple_vm_restorestack(pVM,pStackList);
	}
	/* Here we free the list because, restorestack() don't free it */
	simple_list_delete_gc(pVM->pRingState,pStackList);
	/* Restore Stack to avoid Stack Overflow */
	pVM->nSP = nSP ;
	pVM->nFuncSP = nFuncSP ;
	pVM->nLineNumber = nLineNumber ;
	pVM->nRetEvalDontDelete = nRetEvalDontDelete ;
}

void simple_vm_init ( RingState *pRingState )
{
	Scanner *pScanner  ;
	VM *pVM  ;
	int nRunVM,nFreeFilesList = 0 ;
	/* Check file */
	if ( pRingState->pRingFilesList == NULL ) {
		pRingState->pRingFilesList = simple_list_new_gc(pRingState,0);
		pRingState->pRingFilesStack = simple_list_new_gc(pRingState,0);
		nFreeFilesList = 1 ;
	}
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesList,"Ring_EmbeddedCode");
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesStack,"Ring_EmbeddedCode");
	/* Read File */
	pScanner = simple_scanner_new(pRingState);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(pScanner);
	/* Call Parser */
	nRunVM = simple_parser_start(pScanner->Tokens,pRingState);
	simple_scanner_delete(pScanner);
	/* Files List */
	simple_list_deleteitem_gc(pRingState,pRingState->pRingFilesStack,simple_list_getsize(pRingState->pRingFilesStack));
	if ( nFreeFilesList ) {
		/* Run the Program */
		if ( nRunVM == 1 ) {
			/* Add return to the end of the program */
			simple_scanner_addreturn(pRingState);
			pVM = simple_vm_new(pRingState);
			simple_vm_start(pRingState,pVM);
			pRingState->pVM = pVM ;
		}
	}
	return ;
}

void simple_vm_retitemref ( VM *pVM )
{
	List *pList  ;
	pVM->nRetItemRef++ ;
	/* We free the stack to avoid effects on aLoadAddressScope which is used by isstackpointertoobjstate */
	simple_vm_freestack(pVM);
	/*
	**  Check if we are in the operator method to increment the counter again 
	**  We do this to avoid another PUSHV on the list item 
	**  The first one after return expression in the operator method 
	**  The second one before return from eval() that is used by operator overloading 
	**  This to avoid using & two times like  &  & 
	*/
	if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
		pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
		if ( strcmp(simple_list_getstring(pList,SIMPLE_FUNCCL_NAME),"operator") == 0 ) {
			pVM->nRetItemRef++ ;
		}
	}
}

void simple_vm_printstack ( VM *pVM )
{
	int x,nSP  ;
	printf( "\n*****************************************\n" ) ;
	printf( "Stack Size %d \n",pVM->nSP ) ;
	nSP = pVM->nSP ;
	if ( nSP > 0 ) {
		for ( x = 1 ; x <= nSP ; x++ ) {
			/* Print Values */
			if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
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

void simple_vm_callclassinit ( VM *pVM )
{
	if ( SIMPLE_VM_IR_READIVALUE(1) ) {
		pVM->nCallClassInit++ ;
	}
	else {
		pVM->nCallClassInit-- ;
	}
}

SIMPLE_API void simple_vm_showerrormessage ( VM *pVM,const char *cStr )
{
	int x,lFunctionCall  ;
	List *pList  ;
	const char *cFile  ;
	/* CGI Support */
	simple_state_cgiheader(pVM->pRingState);
	/* Print the Error Message */
	printf( "\nLine %d %s \n",pVM->nLineNumber,cStr ) ;
	/* Print Calling Information */
	lFunctionCall = 0 ;
	for ( x = simple_list_getsize(pVM->pFuncCallList) ; x >= 1 ; x-- ) {
		pList = simple_list_getlist(pVM->pFuncCallList,x);
		/*
		**  If we have ICO_LoadFunc but not ICO_CALL then we need to pass 
		**  ICO_LOADFUNC is executed, but still ICO_CALL is not executed! 
		*/
		if ( simple_list_getsize(pList) < SIMPLE_FUNCCL_CALLERPC ) {
			continue ;
		}
		if ( simple_list_getint(pList,SIMPLE_FUNCCL_TYPE) == SIMPLE_FUNCTYPE_SCRIPT ) {
			/*
			**  Prepare Message 
			**  In 
			*/
			printf( "In " ) ;
			/* Method or Function */
			if ( simple_list_getint(pList,SIMPLE_FUNCCL_METHODORFUNC) ) {
				printf( "method " ) ;
			}
			else {
				printf( "function " ) ;
			}
			/* Function Name */
			printf( "%s",simple_list_getstring(pList,SIMPLE_FUNCCL_NAME) ) ;
			/* Adding () */
			printf( "() in file " ) ;
			/* File Name */
			if ( lFunctionCall == 1 ) {
				cFile = (const char *) simple_list_getpointer(pList,SIMPLE_FUNCCL_NEWFILENAME) ;
			}
			else {
				if ( pVM->nInClassRegion ) {
					cFile = pVM->cFileNameInClassRegion ;
				}
				else {
					cFile = pVM->cFileName ;
				}
			}
			printf( "%s",cFile ) ;
			/* Called From */
			printf( "\ncalled from line %d  ",simple_list_getint(pList,SIMPLE_FUNCCL_LINENUMBER) ) ;
			lFunctionCall = 1 ;
		}
		else {
			printf( "In %s ",simple_list_getstring(pList,SIMPLE_FUNCCL_NAME) ) ;
		}
	}
	if ( lFunctionCall ) {
		printf( "in file %s ",simple_list_getstring(pVM->pRingState->pRingFilesList,1) ) ;
	}
	else {
		if ( pVM->nInClassRegion ) {
			cFile = pVM->cFileNameInClassRegion ;
		}
		else {
			cFile = pVM->cFileName ;
		}
		printf( "in file %s ",cFile ) ;
	}
}

void simple_vm_setfilename ( VM *pVM )
{
	if ( pVM->nInClassRegion ) {
		/*
		**  We are using special attribute for this region to avoid save/restore file name 
		**  If we used pVM->cFileName we could get problem in finding classes and packages 
		*/
		pVM->cFileNameInClassRegion = SIMPLE_VM_IR_READC ;
		return ;
	}
	pVM->cPrevFileName = pVM->cFileName ;
	pVM->cFileName = SIMPLE_VM_IR_READC ;
}

void simple_vm_loadaddressfirst ( VM *pVM )
{
	pVM->nFirstAddress = 1 ;
	simple_vm_loadaddress(pVM);
	pVM->nFirstAddress = 0 ;
}

void simple_vm_endfuncexec ( VM *pVM )
{
	if ( pVM->nFuncExecute > 0 ) {
		pVM->nFuncExecute-- ;
	}
}

void simple_vm_addglobalvariables ( VM *pVM )
{
	List *pList  ;
	int x  ;
	/*
	**  Add Variables 
	**  We write variable name in lower case because Identifiers is converted to lower by Compiler(Scanner) 
	*/
	simple_vm_addnewnumbervar(pVM,"true",1);
	simple_vm_addnewnumbervar(pVM,"false",0);
	simple_vm_addnewstringvar(pVM,"nl","\n");
	simple_vm_addnewstringvar(pVM,"null","");
	simple_vm_addnewpointervar(pVM,"simple_gettemp_var",NULL,0);
	simple_vm_addnewstringvar(pVM,"ccatcherror","NULL");
	simple_vm_addnewpointervar(pVM,"simple_settemp_var",NULL,0);
	simple_vm_addnewnumbervar(pVM,"simple_tempflag_var",0);
	simple_vm_addnewcpointervar(pVM,"stdin",stdin,"file");
	simple_vm_addnewcpointervar(pVM,"stdout",stdout,"file");
	simple_vm_addnewcpointervar(pVM,"stderr",stderr,"file");
	simple_vm_addnewpointervar(pVM,"this",NULL,0);
	simple_vm_addnewstringvar(pVM,"tab","\t");
	simple_vm_addnewstringvar(pVM,"cr","\r");
	/* Add Command Line Parameters */
	pList = simple_vm_newvar2(pVM,"sysargv",pVM->pActiveMem);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE);
	pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	for ( x = 0 ; x < pVM->pRingState->argc ; x++ ) {
		simple_list_addstsimple_gc(pVM->pRingState,pList,pVM->pRingState->argv[x]);
	}
}
/* Threads */

SIMPLE_API void simple_vm_mutexfunctions ( VM *pVM,void *(*pFunc)(void),void (*pFuncLock)(void *),void (*pFuncUnlock)(void *),void (*pFuncDestroy)(void *) )
{
	if ( pVM->pMutex == NULL ) {
		pVM->pMutex = pFunc() ;
		pVM->pFuncMutexLock = pFuncLock ;
		pVM->pFuncMutexUnlock = pFuncUnlock ;
		pVM->pFuncMutexDestroy = pFuncDestroy ;
	}
}

SIMPLE_API void simple_vm_mutexlock ( VM *pVM )
{
	if ( pVM->pMutex != NULL ) {
		pVM->pFuncMutexLock(pVM->pMutex);
	}
}

SIMPLE_API void simple_vm_mutexunlock ( VM *pVM )
{
	if ( pVM->pMutex != NULL ) {
		pVM->pFuncMutexUnlock(pVM->pMutex);
	}
}

SIMPLE_API void simple_vm_mutexdestroy ( VM *pVM )
{
	if ( pVM->pMutex != NULL ) {
		pVM->pFuncMutexDestroy(pVM->pMutex);
		pVM->pMutex = NULL ;
	}
}

SIMPLE_API void simple_vm_runcodefromthread ( VM *pVM,const char *cStr )
{
	RingState *pState  ;
	List *pList,*pList2,*pList3,*pList4,*pList5  ;
	Item *pItem  ;
	/* Create the RingState */
	pState = simple_state_init();
	pState->nPrintInstruction = pVM->pRingState->nPrintInstruction ;
	/* Share the same Mutex between VMs */
	simple_vm_mutexlock(pVM);
	pState->pVM->pMutex = pVM->pMutex ;
	pState->pVM->pFuncMutexDestroy = pVM->pFuncMutexDestroy ;
	pState->pVM->pFuncMutexLock = pVM->pFuncMutexLock ;
	pState->pVM->pFuncMutexUnlock = pVM->pFuncMutexUnlock ;
	/* Share the global scope between threads */
	pItem = pState->pVM->pMem->pFirst->pValue ;
	pState->pVM->pMem->pFirst->pValue = pVM->pMem->pFirst->pValue ;
	/* Save the state */
	pList = pState->pVM->pCode ;
	pList2 = pState->pVM->pFunctionsMap ;
	pList3 = pState->pVM->pClassesMap ;
	pList4 = pState->pVM->pPackagesMap ;
	pList5 = pState->pVM->pCFunctionsList ;
	/* Share the code between the VMs */
	pState->pVM->pFunctionsMap = pVM->pRingState->pRingFunctionsMap ;
	pState->pVM->pClassesMap = pVM->pRingState->pRingClassesMap ;
	pState->pVM->pPackagesMap = pVM->pRingState->pRingPackagesMap ;
	pState->pVM->pCFunctionsList = pVM->pCFunctionsList ;
	pState->pRingFunctionsMap = pVM->pRingState->pRingFunctionsMap ;
	pState->pRingClassesMap = pVM->pRingState->pRingClassesMap ;
	pState->pRingPackagesMap = pVM->pRingState->pRingPackagesMap ;
	pState->pRingCFunctions = pVM->pRingState->pRingCFunctions ;
	/* Get a copy from the byte code List */
	pState->pVM->nScopeID = pVM->nScopeID + 10000 ;
	pState->pVM->pCode = simple_list_new_gc(pVM->pRingState,0) ;
	simple_list_copy(pState->pVM->pCode,pVM->pRingState->pRingGenCode);
	pState->pRingGenCode = pState->pVM->pCode ;
	simple_vm_loadcode(pState->pVM);
	/* Avoid the call to the main function */
	pState->pVM->nCallMainFunction = 1 ;
	simple_vm_mutexunlock(pVM);
	/* Run the code */
	simple_state_runcode(pState,cStr);
	simple_list_delete_gc(pVM->pRingState,pState->pVM->pCode);
	/* Restore the first scope - global scope */
	pState->pVM->pMem->pFirst->pValue = pItem ;
	/* Avoid deleteing the shared code and the Mutex */
	pState->pVM->pCode = pList ;
	pState->pVM->pFunctionsMap = pList2 ;
	pState->pVM->pClassesMap = pList3 ;
	pState->pVM->pPackagesMap = pList4 ;
	pState->pVM->pCFunctionsList = pList5 ;
	pState->pRingGenCode = pList ;
	pState->pRingFunctionsMap = pList2 ;
	pState->pRingClassesMap = pList3 ;
	pState->pRingPackagesMap = pList4 ;
	pState->pRingCFunctions = pList5 ;
	pState->pVM->pMutex = NULL ;
	pState->pVM->pFuncMutexDestroy = NULL ;
	pState->pVM->pFuncMutexLock = NULL ;
	pState->pVM->pFuncMutexUnlock = NULL ;
	/* Delete the RingState */
	simple_state_delete(pState);
}
/* Fast Function Call for Extensions (Without Eval) */

SIMPLE_API void simple_vm_callfunction ( VM *pVM,char *cFuncName )
{
	/* Lower Case and pass () in the end */
	simple_stsimple_lower(cFuncName);
	/* Prepare (Remove effects of the currect function) */
	simple_list_deletelastitem_gc(pVM->pRingState,pVM->pFuncCallList);
	/* Load the function and call it */
	simple_vm_loadfunc2(pVM,cFuncName,0);
	simple_vm_call2(pVM);
	/* Execute the function */
	simple_vm_mainloop(pVM);
	/* Free Stack */
	simple_vm_freestack(pVM);
	/* Avoid normal steps after this function, because we deleted the scope in Prepare */
	pVM->nActiveCatch = 1 ;
}
/* Trace */

void simple_vm_traceevent ( VM *pVM,char nEvent )
{
	List *pList  ;
	if ( (pVM->lTrace == 1) && (pVM->lTraceActive == 0) ) {
		pVM->lTraceActive = 1 ;
		pVM->nTraceEvent = nEvent ;
		/* Prepare Trace Data */
		simple_list_deleteallitems_gc(pVM->pRingState,pVM->pTraceData);
		/* Add Line Number */
		simple_list_adddouble_gc(pVM->pRingState,pVM->pTraceData,pVM->nLineNumber);
		/* Add File Name */
		simple_list_addstsimple_gc(pVM->pRingState,pVM->pTraceData,pVM->cFileName);
		/* Add Function/Method Name */
		if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
			pList = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList)) ;
			simple_list_addstsimple_gc(pVM->pRingState,pVM->pTraceData,simple_list_getstring(pList,SIMPLE_FUNCCL_NAME));
			/* Method of Function */
			simple_list_adddouble_gc(pVM->pRingState,pVM->pTraceData,simple_list_getint(pList,SIMPLE_FUNCCL_METHODORFUNC));
		}
		else {
			simple_list_addstsimple_gc(pVM->pRingState,pVM->pTraceData,"");
			/* Method of Function */
			simple_list_adddouble_gc(pVM->pRingState,pVM->pTraceData,0);
		}
		/* Execute Trace Function */
		simple_vm_runcode(pVM,simple_stsimple_get(pVM->pTrace));
		pVM->lTraceActive = 0 ;
		pVM->nTraceEvent = 0 ;
	}
}
