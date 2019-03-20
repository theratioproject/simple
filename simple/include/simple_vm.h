
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


#ifndef simple_vm_h
#define simple_vm_h
/*
**  Data 
**  Stack Size 
*/
#define SIMPLE_VM_STACK_SIZE 256
#define SIMPLE_VM_STACK_CHECKOVERFLOW 253
#define SIMPLE_VM_FREE_STACK_IN_CLASS_REGION_AFTER 100
#define SIMPLE_VM_BC_ITEMS_COUNT 24
typedef struct ByteCode {
	Item *aData[SIMPLE_VM_BC_ITEMS_COUNT]  ;
	char size  ;
	List *list  ;
} ByteCode ;
typedef struct VM {
	int nPC  ;
	List *pCode  ;
	List *pBlocksMap  ;
	List *pClassesMap  ;
	List *pModulessMap  ;
	int nOPCode  ;
	Item aStack[SIMPLE_VM_STACK_SIZE]  ;
	unsigned char nsp  ;
	List *pMem  ;
	List *pActiveMem  ;
	List *pTempMem  ;
	ByteCode *pByteCode  ;
	ByteCode *pByteCodeIR  ;
	char *file_name  ;
	int nLineNumber  ;
	int nListStart  ;
	List *pNestedLists  ;
	int nBlockFlag  ;
	List *aPCBlockFlag  ;
	List *pBlockCallList  ;
	int nBlockSP  ;
	int nBlockExecute  ;
	List *pCBlocksList  ;
	List *pExitMark  ;
	List *pLoopMark  ;
	int nCallMainBlock  ;
	List *pTry  ;
	List *aScopeNewObj  ;
	char nCallMethod  ;
	List *pObjState  ;
	List *pBraceObject  ;
	List *aBraceObjects  ;
	int nVarScope  ;
	int nScopeID  ;
	List *aScopeID  ;
	int nActiveScopeID  ;
	int nActiveCatch  ;
	char nInsideBraceFlag  ;
	char within_class  ;
	List *aActiveModules  ;
	char nPrivateFlag  ;
	char finalFlag ;
	char nGetSetProperty  ;
	void *pGetSetObject  ;
	char nGetSetObjType  ;
	List *aSetProperty  ;
	void *pAssignment  ;
	List *aCPointers  ;
	List *aForStep  ;
	char nFirstAddress  ;
	char nBeforeEqual  ;
	char nNOAssignment  ;
	SimpleState *sState  ;
	List *aLoadAddressScope  ;
	List *aBeforeObjState  ;
	List *pLoadAddressScope  ;
	int nBlockExecute2  ;
	List *aNewByteCodeItems  ;
	char nEvalCalledFromSimpleCode  ;
	char nDecimals  ;
	char nEvalReallocationFlag  ;
	int nEvalReallocationSize  ;
	int nCBlockParaCount  ;
	char nIgnoreNULL  ;
	int nEvalReturnPC  ;
	char nRetItemRef  ;
	void (*pBlockMutexDestroy)(void *) ;
	void (*pBlockMutexLock)(void *) ;
	void (*pBlockMutexUnlock)(void *) ;
	void *pMutex  ;
	char nIgnoreCPointerTypeCheck  ;
	char nCallClassInit  ;
	char nRetEvalDontDelete  ;
	char *cPrevFileName  ;
	char nRunCode  ;
	char nActiveError  ;
	List *aDynamicSelfItems  ;
	String *pModulesName  ;
	char lTrace  ;
	String *pTrace  ;
	char lTraceActive  ;
	char nTraceEvent  ;
	List *pTraceData  ;
	char nEvalInScope  ;
	char lPassError  ;
	char lHideErrorMsg  ;
	List *aGlobalScopes  ;
	List *aActiveGlobalScopes  ;
	int nCurrentGlobalScope  ;
	char *file_name_within_class  ;
} VM ;
/*
**  Blocks 
**  Main 
*/

VM * simple_vm_new ( SimpleState *sState ) ;

VM * simple_vm_delete ( VM *vm ) ;

SIMPLE_API void simple_vm_loadcode ( VM *vm ) ;

SIMPLE_API void simple_vm_start ( SimpleState *sState,VM *vm ) ;

SIMPLE_API void simple_vm_fetch ( VM *vm ) ;

SIMPLE_API void simple_vm_fetch2 ( VM *vm ) ;

SIMPLE_API void simple_vm_execute ( VM *vm ) ;

SIMPLE_API void simple_vm_error ( VM *vm,const char *cStr ) ;

SIMPLE_API int simple_vm_exec ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_tobytecode ( VM *vm,int x ) ;

SIMPLE_API void simple_vm_error2 ( VM *vm,const char *cStr,const char *cStr2 ) ;

SIMPLE_API void simple_vm_newbytecodeitem ( VM *vm,int x ) ;

SIMPLE_API void simple_vm_mainloop ( VM *vm ) ;

SIMPLE_API void simple_vm_runcode ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_init ( SimpleState *sState ) ;

SIMPLE_API void simple_vm_printstack ( VM *vm ) ;

SIMPLE_API void simple_vm_showerrormessage ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_cgi_showerrormessage ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_addglobalvariables ( VM *vm ) ;
/* Stack and Variables */

SIMPLE_API void simple_vm_pushv ( VM *vm ) ;

SIMPLE_API void simple_vm_loadaddress ( VM *vm ) ;

SIMPLE_API void simple_vm_assignment ( VM *vm ) ;

SIMPLE_API void simple_vm_inc ( VM *vm ) ;

SIMPLE_API void simple_vm_loadapushv ( VM *vm ) ;

SIMPLE_API void simple_vm_newline ( VM *vm ) ;

SIMPLE_API void simple_vm_freestack ( VM *vm ) ;

SIMPLE_API void simple_vm_setreference ( VM *vm ) ;

SIMPLE_API void simple_vm_list_copy ( VM *vm,List *pNewList, List *list ) ;

SIMPLE_API List * simple_reverse_list(VM *vm, List *list) ;

SIMPLE_API void simple_reverse_list_ref(VM *vm, List *list) ;

SIMPLE_API void simple_vm_list_simpointercopy ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_beforeequallist ( VM *vm,List *var,double nNum1 ) ;

SIMPLE_API void simple_vm_beforeequalitem ( VM *vm,Item *pItem,double nNum1 ) ;

SIMPLE_API void simple_vm_assignmentpointer ( VM *vm ) ;

SIMPLE_API void simple_vm_freeloadaddressscope ( VM *vm ) ;

SIMPLE_API void simple_vm_setfilename ( VM *vm ) ;

SIMPLE_API void simple_vm_loadaddressfirst ( VM *vm ) ;

SIMPLE_API void simple_vm_endblockexec ( VM *vm ) ;
/* Compare */

SIMPLE_API void simple_vm_equal ( VM *vm ) ;

SIMPLE_API void simple_vm_lessequal ( VM *vm ) ;

SIMPLE_API void simple_vm_less ( VM *vm ) ;

SIMPLE_API void simple_vm_greater ( VM *vm ) ;

SIMPLE_API void simple_vm_greaterequal ( VM *vm ) ;

SIMPLE_API void simple_vm_notequal ( VM *vm ) ;
/* Math */

SIMPLE_API void simple_vm_sum ( VM *vm ) ;

SIMPLE_API void simple_vm_sub ( VM *vm ) ;

SIMPLE_API void simple_vm_mul ( VM *vm ) ;

SIMPLE_API void simple_vm_div ( VM *vm ) ;

SIMPLE_API void simple_vm_mod ( VM *vm ) ;

SIMPLE_API void simple_vm_neg ( VM *vm ) ;

char * simple_vm_numtostring ( VM *vm,double nNum1,char *cStr ) ;

double simple_vm_stringtonum ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_expr_ppoo ( VM *vm,const char *cStr ) ;

SIMPLE_API void simple_vm_expr_npoo ( VM *vm,const char *cStr,double nNum1 ) ;

SIMPLE_API void simple_vm_expr_spoo ( VM *vm,const char *cStr,const char *cStr2,int nSize ) ;

SIMPLE_API void simple_vm_plusplus ( VM *vm ) ;

SIMPLE_API void simple_vm_minusminus ( VM *vm ) ;

SIMPLE_API void simple_vm_addlisttolist ( VM *vm,List *list,List *list2 ) ;
/* Logic */

SIMPLE_API void simple_vm_and ( VM *vm ) ;

SIMPLE_API void simple_vm_or ( VM *vm ) ;

SIMPLE_API void simple_vm_not ( VM *vm ) ;
/* Variables */

SIMPLE_API void simple_vm_newscope ( VM *vm ) ;

SIMPLE_API int simple_vm_findvar ( VM *vm,const char *cStr ) ;

SIMPLE_API int simple_vm_findvar2 ( VM *vm,int x,List *list2,const char *cStr ) ;

SIMPLE_API void simple_vm_newvar ( VM *vm,const char *cStr ) ;

SIMPLE_API List * simple_vm_newvar2 ( VM *vm,const char *cStr,List *pParent ) ;

SIMPLE_API void simple_vm_addnewnumbervar ( VM *vm,const char *cStr,double x ) ;

SIMPLE_API void simple_vm_addnewstringvar ( VM *vm,const char *cStr,const char *cStr2 ) ;

SIMPLE_API void simple_vm_deletescope ( VM *vm ) ;

SIMPLE_API void simple_vm_addnewpointervar ( VM *vm,const char *cStr,void *x,int y ) ;

SIMPLE_API void simple_vm_newtempvar ( VM *vm,const char *cStr, List *Temlist ) ;

SIMPLE_API void simple_vm_addnewstringvar2 ( VM *vm,const char *cStr,const char *cStr2,int str_size ) ;

List * simple_vm_newtempvar2 ( VM *vm,const char *cStr,List *list3 ) ;

SIMPLE_API void simple_vm_addnewcpointervar ( VM *vm,const char *cStr,void *pointer,const char *cStr2 ) ;
/* Jump */

SIMPLE_API void simple_vm_jump ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpzero ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpfor ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpone ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpzero2 ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpone2 ( VM *vm ) ;
/* Lists */

SIMPLE_API void simple_vm_liststart ( VM *vm ) ;

SIMPLE_API void simple_vm_listitem ( VM *vm ) ;

SIMPLE_API void simple_vm_listend ( VM *vm ) ;

SIMPLE_API void simple_vm_loadindexaddress ( VM *vm ) ;

SIMPLE_API void simple_vm_listpushv ( VM *vm ) ;

SIMPLE_API void simple_vm_listassignment ( VM *vm ) ;

SIMPLE_API void simple_vm_listgetvalue ( VM *vm,List *var,const char *cStr ) ;

SIMPLE_API int simple_vm_strcmpnotcasesensitive ( const char *string_one,const char *cStr2 ) ;
/* Blocks */

SIMPLE_API int simple_vm_loadblock ( VM *vm ) ;

SIMPLE_API int simple_vm_loadblock2 ( VM *vm,const char *cStr,int nPerformance ) ;

SIMPLE_API void simple_vm_call ( VM *vm ) ;

SIMPLE_API void simple_vm_call2 ( VM *vm ) ;

SIMPLE_API void simple_vm_return ( VM *vm ) ;

SIMPLE_API void simple_vm_returnnull ( VM *vm ) ;

SIMPLE_API void simple_vm_returneval ( VM *vm ) ;

SIMPLE_API void simple_vm_newblock ( VM *vm ) ;

SIMPLE_API void simple_vm_blockflag ( VM *vm ) ;

SIMPLE_API void simple_vm_blockflag2 ( VM *vm,int x ) ;

SIMPLE_API void simple_vm_removeblockflag ( VM *vm ) ;

SIMPLE_API void simple_vm_movetoprevscope ( VM *vm ) ;

SIMPLE_API void simple_vm_createtemlist ( VM *vm ) ;

SIMPLE_API void simple_vm_saveloadaddressscope ( VM *vm ) ;

SIMPLE_API void simple_vm_restoreloadaddressscope ( VM *vm ) ;

SIMPLE_API void simple_vm_anonymous ( VM *vm ) ;

int simple_vm_isstackpointertoobjstate ( VM *vm ) ;

SIMPLE_API void simple_vm_retitemref ( VM *vm ) ;

SIMPLE_API void simple_vm_callclassinit ( VM *vm ) ;
/* User Interface */

SIMPLE_API void simple_vm_display ( VM *vm ) ;

SIMPLE_API void simple_vm_read ( VM *vm ) ;
/* String As Array */

SIMPLE_API void simple_vm_string_pushv ( VM *vm ) ;

SIMPLE_API void simple_vm_string_assignment ( VM *vm ) ;

SIMPLE_API void simple_vm_string_index ( VM *vm , String *string , double x ) ;
/* Try Catch Done */

SIMPLE_API void simple_vm_try ( VM *vm ) ;

SIMPLE_API void simple_vm_catch ( VM *vm,const char *cError ) ;

SIMPLE_API void simple_vm_free_try ( VM *vm ) ;
/* Duplicate and Range */

SIMPLE_API void simple_vm_dup ( VM *vm ) ;

SIMPLE_API void simple_vm_range ( VM *vm ) ;

List * simple_vm_range_newlist ( VM *vm ) ;
/* OOP */

SIMPLE_API void simple_vm_oop_newobj ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_property ( VM *vm ) ;

SIMPLE_API int simple_vm_oop_isobject ( List *list ) ;

List * simple_vm_oop_getobj ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_loadmethod ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_aftercallmethod ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_setscope ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_printobj ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_parentinit ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_parentmethods ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_newclass ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_setbraceobj ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_bracestart ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_braceend ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_bracestack ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_newsuperobj ( VM *vm,List *pState,List *pClass ) ;

List * simple_vm_oop_getsuperobj ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_loadsuperobjmethod ( VM *vm,List *pSuper ) ;

SIMPLE_API void simple_vm_oop_import ( VM *vm ) ;

SIMPLE_API List * simple_vm_oop_checkpointertoclassinmodules ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_import2 ( VM *vm,const char *cModules ) ;

SIMPLE_API void simple_vm_oop_import3 ( VM *vm,List *list ) ;

SIMPLE_API int simple_vm_oop_visibleclassescount ( VM *vm ) ;

List * simple_vm_oop_visibleclassitem ( VM *vm,int x ) ;

SIMPLE_API void simple_vm_oop_pushclassmodules ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_oop_popclassmodules ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_deletemodulessafter ( VM *vm,int x ) ;

SIMPLE_API int simple_vm_oop_callmethodinsideclass ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_setget ( VM *vm,List *var ) ;

SIMPLE_API void simple_vm_oop_setproperty ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_operatoroverloading ( VM *vm,List *pObj,const char *string_one,int nType,const char *cStr2,double nNum1,void *pointer,int nPointerType ) ;

SIMPLE_API List * simple_vm_oop_objvarfromobjlist ( List *list ) ;

SIMPLE_API int simple_vm_oop_objtypefromobjlist ( List *list ) ;

SIMPLE_API Item * simple_vm_oop_objitemfromobjlist ( List *list ) ;

SIMPLE_API void simple_vm_oop_callmethodfrombrace ( VM *vm ) ;

SIMPLE_API int simple_vm_oop_isblock ( VM *vm,List *list,const char *cStr ) ;

SIMPLE_API void simple_vm_oop_updateselfpointer ( VM *vm,List *pObj,int nType,void *pContainer ) ;

SIMPLE_API void simple_vm_oop_movetobeforeobjstate ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_setthethisvariable ( VM *vm ) ;

SIMPLE_API void simple_vm_oop_updateselfpointer2 ( VM *vm,List *pObj ) ;
/* For Better Performance */

SIMPLE_API void simple_vm_pushp ( VM *vm ) ;

SIMPLE_API void simple_vm_incp ( VM *vm ) ;

SIMPLE_API void simple_vm_pushpv ( VM *vm ) ;

SIMPLE_API void simple_vm_incjump ( VM *vm ) ;

SIMPLE_API void simple_vm_incpjump ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpvarlenum ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpvarplenum ( VM *vm ) ;

SIMPLE_API void simple_vm_loadblockp ( VM *vm ) ;

SIMPLE_API void simple_vm_pushplocal ( VM *vm ) ;

SIMPLE_API void simple_vm_inclpjump ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpvarlplenum ( VM *vm ) ;

SIMPLE_API void simple_vm_incpjumpstep1 ( VM *vm ) ;

SIMPLE_API void simple_vm_jumpvarplenumstep1 ( VM *vm ) ;
/* End Program / Exit from Loop / Loop (Continue) */

void exit_simple_vm ( VM *vm ) ;

SIMPLE_API void simple_vm_exitmark ( VM *vm ) ;

SIMPLE_API void simple_vm_popexitmark ( VM *vm ) ;

SIMPLE_API void simple_vm_exit ( VM *vm,int nType ) ;
/* State */

SIMPLE_API void simple_vm_savestate ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_restorestate ( VM *vm,List *list,int nPos,int nFlag ) ;

SIMPLE_API void simple_vm_backstate ( VM *vm,int x,List *list ) ;

SIMPLE_API void simple_vm_savestate2 ( VM *vm,List *list ) ;

SIMPLE_API void simple_vm_restorestate2 ( VM *vm,List *list,int x ) ;

List * simple_vm_savestack ( VM *vm ) ;

SIMPLE_API void simple_vm_restorestack ( VM *vm,List *list ) ;
/* Bitwise */

SIMPLE_API void simple_vm_bitand ( VM *vm ) ;

SIMPLE_API void simple_vm_bitor ( VM *vm ) ;

SIMPLE_API void simple_vm_bitxor ( VM *vm ) ;

SIMPLE_API void simple_vm_bitnot ( VM *vm ) ;

SIMPLE_API void simple_vm_bitshl ( VM *vm ) ;

SIMPLE_API void simple_vm_bitshr ( VM *vm ) ;
/* Step Number */

SIMPLE_API void simple_vm_stepnumber ( VM *vm ) ;

SIMPLE_API void simple_vm_popstep ( VM *vm ) ;
/* Threads */

SIMPLE_API void simple_vm_mutexblocks ( VM *vm,void *(*pBlock)(void),void (*pBlockLock)(void *),void (*pBlockUnlock)(void *),void (*pBlockDestroy)(void *) ) ;

SIMPLE_API void simple_vm_mutexlock ( VM *vm ) ;

SIMPLE_API void simple_vm_mutexunlock ( VM *vm ) ;

SIMPLE_API void simple_vm_mutexdestroy ( VM *vm ) ;

SIMPLE_API void simple_vm_runcodefromthread ( VM *vm,const char *cStr ) ;
/* Trace */

SIMPLE_API void simple_vm_traceevent ( VM *vm,char nEvent ) ;
/* Fast Block Call for Extensions (Without Eval) */

SIMPLE_API void simple_vm_callblock ( VM *vm,char *cBlockName ) ;
/* Custom Global Scope */

SIMPLE_API void simple_vm_newglobalscope ( VM *vm ) ;

SIMPLE_API void simple_vm_endglobalscope ( VM *vm ) ;

SIMPLE_API void simple_vm_setglobalscope ( VM *vm ) ;

SIMPLE_API List * simple_vm_getglobalscope ( VM *vm ) ;

SIMPLE_API void simple_vm_setthenullvariable ( VM *vm ) ;
/*
**  Macro 
**  Stack 
**  Add 
*/
#define SIMPLE_VM_STACK_PUSHC vm->nsp++ ; simple_itemarray_setstring2(vm->aStack, vm->nsp, simple_string_get(vm->pByteCodeIR->aData[1]->data.string), simple_string_size(vm->pByteCodeIR->aData[1]->data.string))
#define SIMPLE_VM_STACK_PUSHN vm->nsp++ ; simple_itemarray_setdouble(vm->aStack, vm->nsp , vm->pByteCodeIR->aData[1]->data.dNumber)
#define SIMPLE_VM_STACK_PUSHP vm->nsp++ ; simple_itemarray_setpointer(vm->aStack, vm->nsp , vm->pByteCodeIR->aData[1]->data.pointer )
/* Note, use SIMPLE_VM_STACK_OBJTYPE to read/write the pointer type */
#define SIMPLE_VM_STACK_TRUE simple_itemarray_setdouble(vm->aStack,vm->nsp, 1)
#define SIMPLE_VM_STACK_FALSE simple_itemarray_setdouble(vm->aStack,vm->nsp, 0)
#define SIMPLE_VM_STACK_PUSHCVAR simple_itemarray_setstring2(vm->aStack,vm->nsp,simple_list_getstring(var,3),simple_list_getstringsize(var,3))
#define SIMPLE_VM_STACK_PUSHNVAR simple_itemarray_setdouble(vm->aStack,vm->nsp,simple_list_getdouble(var,3))
#define SIMPLE_VM_STACK_PUSHPVALUE(x) vm->nsp++ ; simple_itemarray_setpointer(vm->aStack, vm->nsp , x )
#define SIMPLE_VM_STACK_PUSHCVALUE(x) vm->nsp++ ; simple_itemarray_setstring(vm->aStack, vm->nsp, x)
#define SIMPLE_VM_STACK_PUSHNVALUE(x) vm->nsp++ ; simple_itemarray_setdouble(vm->aStack, vm->nsp , x)
#define SIMPLE_VM_STACK_SETCVALUE(x) simple_itemarray_setstring(vm->aStack, vm->nsp, x)
#define SIMPLE_VM_STACK_SETNVALUE(x) simple_itemarray_setdouble(vm->aStack, vm->nsp , x)
#define SIMPLE_VM_STACK_SETPVALUE(x) simple_itemarray_setpointer(vm->aStack, vm->nsp , x )
#define SIMPLE_VM_STACK_SETCVALUE2(x,y) simple_itemarray_setstring2(vm->aStack, vm->nsp, x,y)
/* Check */
#define SIMPLE_VM_STACK_ISSTRING simple_itemarray_isstring(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_ISNUMBER simple_itemarray_isnumber(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_ISPOINTER simple_itemarray_ispointer(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_ISLIST simple_itemarray_islist(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_ISNOTHING simple_itemarray_isnothing(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_ISPOINTERVALUE(x) simple_itemarray_ispointer(vm->aStack,x)
/* Check At Index*/
#define SIMPLE_VM_STACK_ISSTRING_AT(x) simple_itemarray_isstring(vm->aStack,x)
#define SIMPLE_VM_STACK_ISNUMBER_AT(x) simple_itemarray_isnumber(vm->aStack,x)
#define SIMPLE_VM_STACK_ISPOINTER_AT(x) simple_itemarray_ispointer(vm->aStack,x)
#define SIMPLE_VM_STACK_ISLIST_AT(x) simple_itemarray_islist(vm->aStack,x)
/* Read */
#define SIMPLE_VM_STACK_READC simple_itemarray_getstring(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_STRINGSIZE simple_itemarray_getstringsize(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_READN simple_itemarray_getdouble(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_READP simple_itemarray_getpointer(vm->aStack,vm->nsp)
#define SIMPLE_VM_STACK_OBJTYPE vm->aStack[vm->nsp].nObjectType
#define SIMPLE_VM_STACK_PREVOBJTYPE vm->aStack[vm->nsp-1].nObjectType
/*Read At Index */
#define SIMPLE_VM_STACK_READC_AT(x) simple_itemarray_getstring(vm->aStack,x)
#define SIMPLE_VM_STACK_STRINGSIZE_AT(x) simple_itemarray_getstringsize(vm->aStack,x)
#define SIMPLE_VM_STACK_READN_AT(x) simple_itemarray_getdouble(vm->aStack,x)
#define SIMPLE_VM_STACK_READP_AT(x) simple_itemarray_getpointer(vm->aStack,x)
#define SIMPLE_VM_STACK_OBJTYPE_AT(x) vm->aStack[x].nObjectType
#define SIMPLE_VM_STACK_PREVOBJTYPE_AT(x) vm->aStack[x-1].nObjectType
/* Delete */
#define SIMPLE_VM_STACK_POP vm->nsp--
#define SIMPLE_VM_STACK_POP_(x) if (nsp) { for (z = vm->nsp-nsp; z > x ; z--) vm->nsp--;} else { for (z = vm->nsp; z > x ; z--) vm->nsp--;} 
#define SIMPLE_VM_STACK_PUSH vm->nsp++
/* Objects/Pointer  - Type */
#define SIMPLE_OBJTYPE_VARIABLE 1
#define SIMPLE_OBJTYPE_LISTITEM 2
#define SIMPLE_OBJTYPE_SUBSTRING 3
/* Variable Structure */
#define SIMPLE_VAR_NAME 1
#define SIMPLE_VAR_TYPE 2
#define SIMPLE_VAR_VALUE 3
#define SIMPLE_VAR_PVALUETYPE 4
#define SIMPLE_VAR_PRIVATEFLAG 5
/* Number of global variables defined by the VM like True, False, __err__ */
#define SIMPLE_VM_INTERNALGLOBALSCOUNT 14
#define SIMPLE_VAR_LISTSIZE 5
/* Variable Type */
#define SIMPLE_VM_NULL 0
#define SIMPLE_VM_STRING 1
#define SIMPLE_VM_NUMBER 2
#define SIMPLE_VM_LIST 3
#define SIMPLE_VM_POINTER 4
/* IR (Instruction Register) */
#define SIMPLE_VM_JUMP vm->nPC = vm->pByteCodeIR->aData[1]->data.iNumber
#define SIMPLE_VM_IR_READC simple_string_get(vm->pByteCodeIR->aData[1]->data.string)
#define SIMPLE_VM_IR_READCVALUE(x) simple_string_get(vm->pByteCodeIR->aData[x]->data.string)
#define SIMPLE_VM_IR_READP vm->pByteCodeIR->aData[1]->data.pointer
#define SIMPLE_VM_IR_READPVALUE(x) vm->pByteCodeIR->aData[x]->data.pointer
#define SIMPLE_VM_IR_READI vm->pByteCodeIR->aData[1]->data.iNumber
#define SIMPLE_VM_IR_READIVALUE(x) vm->pByteCodeIR->aData[x]->data.iNumber
#define SIMPLE_VM_IR_READD vm->pByteCodeIR->aData[1]->data.dNumber
#define SIMPLE_VM_IR_READDVALUE(x) vm->pByteCodeIR->aData[x]->data.dNumber
#define SIMPLE_VM_IR_PARACOUNT vm->pByteCodeIR->size
#define SIMPLE_VM_IR_OPCODE vm->pByteCodeIR->aData[0]->data.iNumber
#define SIMPLE_VM_IR_SETCVALUE(x,y) simple_string_set_gc(vm->sState,vm->pByteCodeIR->aData[x]->data.string,y)
#define SIMPLE_VM_IR_ITEM(x) vm->pByteCodeIR->aData[x]
#define SIMPLE_VM_IR_LIST vm->pByteCodeIR->list
#define SIMPLE_VM_IR_LOAD vm->pByteCodeIR = vm->pByteCode + vm->nPC - 1
#define SIMPLE_VM_IR_UNLOAD vm->pByteCodeIR = vm->pByteCode + vm->nPC - 2
/*
**  Calling Blocks 
**  Note : When you insert items check performance blocks for update too! 
**  pBlockCallList ( Type, Block Name , Position(PC) , Stack Pointer , TempMem, ... 
**  Types 
*/
#define SIMPLE_BLOCKTYPE_SCRIPT 1
#define SIMPLE_BLOCKTYPE_C 2
#define SIMPLE_BLOCKCL_TYPE 1
#define SIMPLE_BLOCKCL_NAME 2
#define SIMPLE_BLOCKCL_PC 3
#define SIMPLE_BLOCKCL_SP 4
#define SIMPLE_BLOCKCL_TEMPMEM 5
#define SIMPLE_BLOCKCL_FILENAME 6
#define SIMPLE_BLOCKCL_NEWFILENAME 6
#define SIMPLE_BLOCKCL_METHODORBLOCK 8
#define SIMPLE_BLOCKCL_LINENUMBER 9
#define SIMPLE_BLOCKCL_CALLERPC 10
#define SIMPLE_BLOCKCL_BLOCKEXE 11
#define SIMPLE_BLOCKCL_LISTSTART 12
#define SIMPLE_BLOCKCL_NESTEDLISTS 13
#define SIMPLE_BLOCKCL_STATE 14
/* pBlocksMap ( Block Name , Position , File Name, Private Flag) */
#define SIMPLE_BLOCKMAP_NAME 1
#define SIMPLE_BLOCKMAP_PC 2
#define SIMPLE_BLOCKMAP_FILENAME 3
#define SIMPLE_BLOCKMAP_PRIVATEFLAG 4 //multiblocklead
/* BlockMap List Size */
#define SIMPLE_BLOCKMAP_NORMALSIZE 4
/* Variable Scope */
#define SIMPLE_VARSCOPE_NOTHING 0
#define SIMPLE_VARSCOPE_LOCAL 1
#define SIMPLE_VARSCOPE_OBJSTATE 2
#define SIMPLE_VARSCOPE_GLOBAL 3
#define SIMPLE_VARSCOPE_NEWOBJSTATE 4
#define SIMPLE_VARSCOPE_FINAL 5
/*
**  OOP 
**  pClassesMap 
*/
#define SIMPLE_CLASSMAP_CLASSNAME 1
#define SIMPLE_CLASSMAP_PC 2
#define SIMPLE_CLASSMAP_PARENTCLASS 3
#define SIMPLE_CLASSMAP_METHODSLIST 4
#define SIMPLE_CLASSMAP_FLAGISPARENTCLASSINFCOLLECTED 5
#define SIMPLE_CLASSMAP_POINTERTOMODULE 6
#define SIMPLE_CLASSMAP_POINTERTOLISTOFCLASSINSIDEMODULE 2
#define SIMPLE_CLASSMAP_POINTERTOFILENAME 3
#define SIMPLE_CLASSMAP_IMPORTEDCLASSSIZE 3
/* Moduless */
#define SIMPLE_MODULENAME 1
#define SIMPLE_CLASSESLIST 2
/* Object */
#define SIMPLE_OBJECT_CLASSPOINTER 1
#define SIMPLE_OBJECT_OBJECTDATA 2
/* pObjState */
#define SIMPLE_OBJSTATE_SCOPE 1
#define SIMPLE_OBJSTATE_METHODS 2
#define SIMPLE_OBJSTATE_CLASS 3
/* Operator Overloading */
#define SIMPLE_OOPARA_STRING 1
#define SIMPLE_OOPARA_NUMBER 2
#define SIMPLE_OOPARA_POINTER 3
/* aBraceObjects */
#define SIMPLE_ABRACEOBJECTS_BRACEOBJECT 1
/* aScopeNewObj */
#define SIMPLE_ASCOPENEWOBJ_PREVSCOPE 1
#define SIMPLE_ASCOPENEWOBJ_LISTSTART 2
#define SIMPLE_ASCOPENEWOBJ_NESTEDLISTS 3
#define SIMPLE_ASCOPENEWOBJ_SP 4
#define SIMPLE_ASCOPENEWOBJ_BLOCKSP 10
/* State */
#define SIMPLE_STATE_TRYCATCH 1
#define SIMPLE_STATE_EXIT 2
#define SIMPLE_STATE_RETURN 3
/* Memory */
#define SIMPLE_MEMORY_GLOBALSCOPE 1
/* List as Hash */
#define SIMPLE_LISTHASH_KEY 1
#define SIMPLE_LISTHASH_SIZE 2
#define SIMPLE_LISTHASH_VALUE 2
/* C Pointer List (inside Variable Value) */
#define SIMPLE_CPOINTER_POINTER 1
#define SIMPLE_CPOINTER_TYPE 2
#define SIMPLE_CPOINTER_STATUS 3
#define SIMPLE_CPOINTER_LISTSIZE 3
/* C Pointer Status */
#define SIMPLE_CPOINTERSTATUS_NOTCOPIED 0
#define SIMPLE_CPOINTERSTATUS_COPIED 1
#define SIMPLE_CPOINTERSTATUS_NOTASSIGNED 2
/* Temp Object */
#define SIMPLE_TEMP_OBJECT "simple_temp_object"
#define SIMPLE_TEMP_VARIABLE "simple_sys_temp"
/* Trace */
#define SIMPLE_VM_TRACEEVENT_NEWLINE 1
#define SIMPLE_VM_TRACEEVENT_NEWBLOCK 2
#define SIMPLE_VM_TRACEEVENT_RETURN 3
#define SIMPLE_VM_TRACEEVENT_ERROR 4
#define SIMPLE_VM_TRACEEVENT_BEFORECBLOCK 5
#define SIMPLE_VM_TRACEEVENT_AFTERCBLOCK 6
/* Runtime Error Messages */
#define SIMPLE_VM_ERROR_DIVIDEBYZERO "RUNTIME ERROR 1 : Can't divide by zero "
#define SIMPLE_VM_ERROR_INDEXOUTOFRANGE "RUNTIME ERROR 2 : Array Access (Index out of range) "
#define SIMPLE_VM_ERROR_BLOCKNOTFOUND "RUNTIME ERROR 2 : Calling Block without definition "
#define SIMPLE_VM_ERROR_STACKOVERFLOW "RUNTIME ERROR 3 : Stack Overflow "
#define SIMPLE_VM_ERROR_OBJECTISNOTLIST "RUNTIME ERROR 4 : Can't access the list item, Object is not list !"
#define SIMPLE_VM_ERROR_NOTVARIABLE "RUNTIME ERROR 5 : A variable is required"
#define SIMPLE_VM_ERROR_VALUEMORETHANONECHAR "RUNTIME ERROR 6 : String letter assignment is to one character only"
#define SIMPLE_VM_ERROR_VARISNOTSTRING "RUNTIME ERROR 7 : The variable is not a string "
#define SIMPLE_VM_ERROR_EXITWITHOUTLOOP "RUNTIME ERROR 24 : Using exit command outside loop "
#define SIMPLE_VM_ERROR_EXITNUMBEROUTSIDERANGE "RUNTIME ERROR 24 : Using exit command with number outside the range "
#define SIMPLE_VM_ERROR_CLASSNOTFOUND "RUNTIME ERROR 24 : Invalid class name, Class not found "
#define SIMPLE_VM_ERROR_PROPERTYNOTFOUND "RUNTIME ERROR 24 : Invalid property name, property not found"
#define SIMPLE_VM_ERROR_NOTOBJECT "RUNTIME ERROR 24 : Object is required"
#define SIMPLE_VM_ERROR_METHODNOTFOUND "RUNTIME ERROR 24 : Calling Method without definition "
#define SIMPLE_VM_ERROR_PARENTCLASSNOTFOUND "RUNTIME ERROR 24 : Invalid parent class name, class not found"
#define SIMPLE_VM_ERROR_BRACEWITHOUTOBJECT "RUNTIME ERROR 24 : Using braces to access unknown object "
#define SIMPLE_VM_ERROR_SUPERCLASSNOTFOUND "RUNTIME ERROR 24 : error, using 'Super' without parent class "
#define SIMPLE_VM_ERROR_NUMERICOVERFLOW "RUNTIME ERROR 24 : Numeric Overflow! "
#define SIMPLE_VM_ERROR_LESSPARAMETERSCOUNT "RUNTIME ERROR 24 : Calling block with less parameters!"
#define SIMPLE_VM_ERROR_EXTRAPARAMETERSCOUNT "RUNTIME ERROR 24 : Calling block with extra parameters!"
#define SIMPLE_VM_ERROR_BADVALUES "RUNTIME ERROR 24 : Using operator with values of incorrect type"
#define SIMPLE_VM_ERROR_LOOPWITHOUTLOOP "RUNTIME ERROR 24 : Using loop command outside loops "
#define SIMPLE_VM_ERROR_LOOPNUMBEROUTSIDERANGE "RUNTIME ERROR 24 : Using loop command with number outside the range "
#define SIMPLE_VM_ERROR_USINGNULLVARIABLE "RUNTIME ERROR 24 : The varible is not initialized"
#define SIMPLE_VM_ERROR_MODULENOTFOUND "RUNTIME ERROR 24 : Invalid modules name, Modules not found! "
#define SIMPLE_VM_ERROR_CALLINGPRIVATEMETHOD "RUNTIME ERROR 24 : Private blocks is inaccesible from outside class "
#define SIMPLE_VM_ERROR_USINGPRIVATEATTRIBUTE "RUNTIME ERROR 24 : Using private attribute from outside the class "
#define SIMPLE_VM_ERROR_FORSTEPDATATYPE "RUNTIME ERROR 24 : The step value is not valid"
#define SIMPLE_VM_ERROR_FORLOOPDATATYPE "RUNTIME ERROR 24 : Using bad data type in for loop"
#define SIMPLE_VM_ERROR_PARENTCLASSLIKESUBCLASS "RUNTIME ERROR 24 : The parent and child class cannot have the same name "
#define SIMPLE_VM_ERROR_TRYINGTOMODIFYTHESELFPOINTER "RUNTIME ERROR 24 : Trying to destory the object using the this reference "
#define SIMPLE_VM_ERROR_BADCALLPARA "RUNTIME ERROR 24 : The INVOKE command expect a variable, contains string"
#define SIMPLE_VM_ERROR_BADDECIMALNUMBER "RUNTIME ERROR 24 : The decimals number is out of range (correct range >= 0 and <=14) !"
#define SIMPLE_VM_ERROR_ASSIGNNOTVARIABLE "RUNTIME ERROR 24 : Variable is required for the assignment operation"
#define SIMPLE_VM_ERROR_CANTOPENFILE "RUNTIME ERROR 24 : Can't create/open the file!"
#define SIMPLE_VM_ERROR_BADCOLUMNNUMBER "RUNTIME ERROR 24 : The column number is not correct! It's greater than the number of columns in the list"
#define SIMPLE_VM_ERROR_BADCOMMAND "RUNTIME ERROR 24 : Sorry, The command is not supported in this context"
#define SIMPLE_VM_ERROR_LIBLOADERROR "RUNTIME ERROR 24 : Runtime Error Occur while loading the dynamic library!"
#define SIMPLE_VM_ERROR_TEMPFILENAME "RUNTIME ERROR 24 : Error occurred while creating unique filename."
#define SIMPLE_VM_ERROR_CANNOT_ASSIGN_FINAL "RUNTIME ERROR 24 : Cannot assign a value to the final variable "
/* Extra Size (for codeExecution) */
#define SIMPLE_VM_EXTRASIZE 2
/* Variables Location */
#define SIMPLE_VM_STATICVAR_THIS 12
#define SIMPLE_VM_STATICVAR_NULL 4
#endif
