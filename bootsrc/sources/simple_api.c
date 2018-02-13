
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
/* Support for C Functions */

SIMPLE_API void register_block_t ( SimpleState *sState,const char *cStr, void (*pFunc)(void *) )
{
	List *list  ;
	if ( sState->c_blocks == NULL ) {
		sState->c_blocks = simple_list_new_gc(sState,0);
	}
	list = simple_list_newlist_gc(sState,sState->c_blocks);
	simple_list_addstring_gc(sState,list,cStr);
	simple_list_addfuncpointer_gc(sState,list,pFunc);
}

SIMPLE_API void loadcfunctions ( SimpleState *sState )
{
	/* General */
	register_block("lengthOf",simple_vmlib_len);
	register_block("add",simple_vmlib_add);
	/*
	**  Simple See and Give 
	**  Also we add the display() and read() block to the api
	*/
	register_block("display",display_string);
	register_block("read",read_string);
}

int api_is_list ( void *pointer,int x )
{
	int nType  ;
	if ( SIMPLE_API_ISPOINTER(x) ) {
		nType = SIMPLE_API_GETPOINTERTYPE(x);
		if ( nType == SIMPLE_OBJTYPE_VARIABLE || nType == SIMPLE_OBJTYPE_LISTITEM ) {
			return 1 ;
		}
	}
	return 0 ;
}

SIMPLE_API List * api_get_list ( void *pointer,int x )
{
	int nType  ;
	Item *pItem  ;
	List *list  ;
	if ( SIMPLE_API_ISPOINTER(x) ) {
		nType = SIMPLE_API_GETPOINTERTYPE(x);
		if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
			list = (List *) SIMPLE_API_GETPOINTER(x) ;
			return simple_list_getlist(list,3) ;
		}
		else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_API_GETPOINTER(x) ;
			return simple_item_getlist(pItem) ;
		}
	}
	return NULL ;
}

SIMPLE_API void api_ret_list ( void *pointer,List *list )
{
	List *list2,*list3  ;
	VM *vm  ;
	vm = (VM *) pointer ;
	list2 = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1);
	list3 = simple_vm_newvar2(vm,SIMPLE_TEMP_VARIABLE,list2);
	simple_list_setint_gc(((VM *) pointer)->sState,list3,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(((VM *) pointer)->sState,list3,SIMPLE_VAR_VALUE);
	list2 = simple_list_getlist(list3,SIMPLE_VAR_VALUE);
	/* Copy the list */
	simple_list_copy(list2,list);
	SIMPLE_API_PUSHPVALUE(list3);
	SIMPLE_API_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
}

SIMPLE_API List * api_new_list ( VM *vm )
{
	List *list  ;
	list = simple_list_newlist_gc(vm->sState,vm->pActiveMem);
	return list ;
}

SIMPLE_API void api_ret_cpointer ( void *pointer,void *pGeneral,const char *cType )
{
	List *list  ;
	/* Create the list */
	list = SIMPLE_API_NEWLIST ;
	/* The variable value will be a list contains the pointer */
	simple_list_addpointer_gc(((VM *) pointer)->sState,list,pGeneral);
	/* Add the pointer type */
	simple_list_addstring_gc(((VM *) pointer)->sState,list,cType);
	/* Add the status number ( 0 = Not Copied ,1 = Copied  2 = Not Assigned yet) */
	simple_list_addint_gc(((VM *) pointer)->sState,list,2);
	SIMPLE_API_RETLIST(list);
}

SIMPLE_API void * api_get_cpointer ( void *pointer,int x,const char *cType )
{
	List *list, *list2  ;
	int y  ;
	if ( SIMPLE_API_ISLIST(x) ) {
		list = SIMPLE_API_GETLIST(x) ;
		if ( simple_list_ispointer(list,1) ) {
			if ( simple_list_getpointer(list,1) != NULL ) {
				if ( (strcmp(simple_list_getstring(list,2),cType) == 0) || (((VM *) pointer)->nIgnoreCPointerTypeCheck==1) ) {
					/*
					**  Check if the pointer is copied or not 
					**  We check for 2 (not assigned) also, happens when f1 ( x , f2() ) and f2 return C pointer 
					*/
					if ( (simple_list_getint(list,3) == 0) || (simple_list_getint(list,3) == 2) ) {
						return simple_list_getpointer(list,1) ;
					}
					list2 = ((VM *) pointer)->aCPointers ;
					if ( simple_list_getsize(list2) > 0 ) {
						for ( y = 1 ; y <= simple_list_getsize(list2) ; y++ ) {
							if ( simple_list_getpointer(list,1) == simple_list_getpointer(list2,y) ) {
								return simple_list_getpointer(list,1) ;
							}
						}
					}
					simple_list_setpointer_gc(((VM *) pointer)->sState,list,1,NULL);
					SIMPLE_API_ERROR(SIMPLE_API_NULLPOINTER);
					return NULL ;
				}
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				return NULL ;
			}
			else {
				if ( strcmp(simple_list_getstring(list,2),"NULLPOINTER") == 0 ) {
					return NULL ;
				}
			}
			SIMPLE_API_ERROR(SIMPLE_API_NULLPOINTER);
			return NULL ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_NOTPOINTER);
	return NULL ;
}

SIMPLE_API void api_set_cpointer_null ( void *pointer,int x )
{
	List *list, *list2  ;
	int y  ;
	list = (List *) SIMPLE_API_GETLIST(x) ;
	/* Check pointer status ( 0 = copied , 1 = Not copied ) */
	if ( simple_list_getint(list,3) == 0 ) {
		simple_list_setpointer_gc(((VM *) pointer)->sState,list,1,NULL);
		return ;
	}
	list2 = ((VM *) pointer)->aCPointers ;
	if ( simple_list_getsize(list2) > 0 ) {
		for ( y = simple_list_getsize(list2) ; y >= 1 ; y-- ) {
			if ( simple_list_getpointer(list,1) == simple_list_getpointer(list2,y) ) {
				simple_list_deleteitem_gc(((VM *) pointer)->sState,list2,y);
				simple_list_setpointer_gc(((VM *) pointer)->sState,list,1,NULL);
			}
		}
	}
}

SIMPLE_API void * api_var_ptr ( void *pointer,const char  *cStr,const char *cStr2 )
{
	VM *vm  ;
	List *list, *pActiveMem  ;
	Item *pItem  ;
	/*
	**  Usage 
	**  To get pointer to a ring variable value (pointer to double or int) i.e. int * or double * 
	**  We need this because some C Functions get int * or double * as parameter 
	*/
	vm = (VM *) pointer ;
	/* Set the Active Scope */
	pActiveMem = vm->pActiveMem ;
	vm->pActiveMem = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1);
	if ( simple_vm_findvar(vm, cStr ) == 0 ) {
		/* Restore the Active Scope */
		vm->pActiveMem = pActiveMem ;
		SIMPLE_API_ERROR(SIMPLE_VM_ERROR_NOTVARIABLE);
		return NULL ;
	}
	/* Restore the Active Scope */
	vm->pActiveMem = pActiveMem ;
	list = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	if ( simple_list_getint(list,SIMPLE_VAR_TYPE) == SIMPLE_VM_NUMBER ) {
		pItem = simple_list_getitem(list,SIMPLE_VAR_VALUE);
		if ( strcmp(cStr2,"double") == 0 ) {
			return &(pItem->data.dNumber) ;
		}
		else if ( strcmp(cStr2,"int") == 0 ) {
			return &(pItem->data.iNumber) ;
		}
	}
	else if ( simple_list_getint(list,SIMPLE_VAR_TYPE) == SIMPLE_VM_STRING ) {
		pItem = simple_list_getitem(list,SIMPLE_VAR_VALUE);
		return pItem->data.pString->cStr ;
	}
	return NULL ;
}

SIMPLE_API void api_int_value ( void *pointer,const char  *cStr )
{
	VM *vm  ;
	List *list  ;
	Item *pItem  ;
	/*
	**  Usage 
	**  Convert the variable value from int to double 
	**  When we pass int * for Simple Variable Value to a C Function 
	**  We need to convert again from int to double, because Simple uses double 
	*/
	vm = (VM *) pointer ;
	if ( simple_vm_findvar(vm, cStr ) == 0 ) {
		SIMPLE_API_ERROR(SIMPLE_VM_ERROR_NOTVARIABLE);
		return ;
	}
	list = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	if ( simple_list_getint(list,SIMPLE_VAR_TYPE) == SIMPLE_VM_NUMBER ) {
		pItem = simple_list_getitem(list,SIMPLE_VAR_VALUE);
		pItem->data.dNumber = (double) pItem->data.iNumber ;
	}
}

SIMPLE_API void list_add_cpointer ( List *list,void *pGeneral,const char *cType )
{
	List *list2  ;
	/* create sub list */
	list2 = simple_list_newlist(list);
	/* The variable value will be a list contains the pointer */
	simple_list_addpointer(list2,pGeneral);
	/* Add the pointer type */
	simple_list_addstring(list2,cType);
	/* Add the status number ( 0 = Not Copied ,1 = Copied  2 = Not Assigned yet) */
	simple_list_addint(list2,2);
}

SIMPLE_API int api_iscpointer_list ( List *list )
{
	if ( simple_list_getsize(list) != 3 ) {
		return 0 ;
	}
	if ( simple_list_ispointer(list,1) && simple_list_isstring(list,2) && simple_list_isnumber(list,3) ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int api_is_cpointer ( void *pointer,int x )
{
	if ( SIMPLE_API_ISLIST(x) ) {
		return api_iscpointer_list(SIMPLE_API_GETLIST(x)) ;
	}
	return 0 ;
}

SIMPLE_API int api_is_object ( void *pointer,int x )
{
	if ( SIMPLE_API_ISLIST(x) ) {
		return simple_vm_oop_isobject(SIMPLE_API_GETLIST(x)) ;
	}
	return 0 ;
}

SIMPLE_API int api_cpointer_cmp ( List *list,List *list2 )
{
	if ( simple_list_getpointer(list,SIMPLE_CPOINTER_POINTER) == simple_list_getpointer(list2,SIMPLE_CPOINTER_POINTER) ) {
		return 1 ;
	}
	else {
		return 0 ;
	}
}

SIMPLE_API int api_is_pointer ( void *pointer,int x )
{
	List *list, *list2  ;
	VM *vm  ;
	Item *pItem  ;
	vm = (VM *) pointer ;
	list = simple_list_getlist(SIMPLE_API_PARALIST,x) ;
	if ( simple_list_ispointer(list,SIMPLE_VAR_VALUE) ) {
		return 1 ;
	}
	else if ( simple_list_isstring(list,SIMPLE_VAR_VALUE) ) {
		/* Treat NULL Strings as NULL Pointers - so we can use NULL instead of NULLPOINTER() */
		if ( strcmp(simple_list_getstring(list,SIMPLE_VAR_VALUE),"") == 0 ) {
			/* Create the list for the NULL Pointer */
			simple_list_setint_gc(((VM *) pointer)->sState,list,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
			list2 = SIMPLE_API_NEWLIST ;
			pItem = simple_list_getitem(vm->pActiveMem,simple_list_getsize(vm->pActiveMem));
			/* Increase the References count for the item */
			simple_vm_gc_newitemreference(pItem);
			simple_list_setpointer_gc(((VM *) pointer)->sState,list,SIMPLE_VAR_VALUE,pItem);
			simple_list_setint_gc(((VM *) pointer)->sState,list,SIMPLE_VAR_PVALUETYPE,SIMPLE_OBJTYPE_LISTITEM);
			/* The variable value will be a list contains the pointer */
			simple_list_addpointer_gc(((VM *) pointer)->sState,list2,NULL);
			/* Add the pointer type */
			simple_list_addstring_gc(((VM *) pointer)->sState,list2,"NULLPOINTER");
			/* Add the status number ( 0 = Not Copied ,1 = Copied  2 = Not Assigned yet) */
			simple_list_addint_gc(((VM *) pointer)->sState,list2,2);
			return 1 ;
		}
	}
	return 0 ;
}

SIMPLE_API void * api_get_cpointer2pointer ( void *pointer,int x,const char *cType )
{
	List *list, *list2  ;
	int y  ;
	Item *pItem  ;
	if ( SIMPLE_API_ISLIST(x) ) {
		list = SIMPLE_API_GETLIST(x) ;
		if ( simple_list_ispointer(list,1) ) {
			if ( simple_list_getpointer(list,1) != NULL ) {
				if ( (strcmp(simple_list_getstring(list,2),cType) == 0) || (((VM *) pointer)->nIgnoreCPointerTypeCheck==1) ) {
					/*
					**  Check if the pointer is copied or not 
					**  We check for 2 (not assigned) also, happens when f1 ( x , f2() ) and f2 return C pointer 
					*/
					if ( (simple_list_getint(list,3) == 0) || (simple_list_getint(list,3) == 2) ) {
						pItem = simple_list_getitem(list,1);
						return & (pItem->data.pointer) ;
					}
					list2 = ((VM *) pointer)->aCPointers ;
					if ( simple_list_getsize(list2) > 0 ) {
						for ( y = 1 ; y <= simple_list_getsize(list2) ; y++ ) {
							if ( simple_list_getpointer(list,1) == simple_list_getpointer(list2,y) ) {
								pItem = simple_list_getitem(list,1);
								return & (pItem->data.pointer) ;
							}
						}
					}
					simple_list_setpointer_gc(((VM *) pointer)->sState,list,1,NULL);
					SIMPLE_API_ERROR(SIMPLE_API_NULLPOINTER);
					return NULL ;
				}
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				return NULL ;
			}
			else {
				if ( strcmp(simple_list_getstring(list,2),"NULLPOINTER") == 0 ) {
					return NULL ;
				}
			}
			SIMPLE_API_ERROR(SIMPLE_API_NULLPOINTER);
			return NULL ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_NOTPOINTER);
	return NULL ;
}

SIMPLE_API void list_add_cpointer_gc ( void *pState,List *list,void *pGeneral,const char *cType )
{
	List *list2  ;
	/* create sub list */
	list2 = simple_list_newlist_gc(pState,list);
	/* The variable value will be a list contains the pointer */
	simple_list_addpointer_gc(pState,list2,pGeneral);
	/* Add the pointer type */
	simple_list_addstring_gc(pState,list2,cType);
	/* Add the status number ( 0 = Not Copied ,1 = Copied  2 = Not Assigned yet) */
	simple_list_addint_gc(pState,list2,2);
}
/*
**  Library 
**  General 
*/

void simple_vmlib_len ( void *pointer )
{
	VM *vm  ;
	vm = (VM *) pointer ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETNUMBER(SIMPLE_API_GETSTRINGSIZE(1) - 1);
	}
	else if ( SIMPLE_API_ISLIST(1) ) {
		if ( simple_vm_oop_isobject(SIMPLE_API_GETLIST(1)) == 0 ) {
			SIMPLE_API_RETNUMBER(simple_list_getsize(SIMPLE_API_GETLIST(1)) - 1);
		}
		else {
			SIMPLE_VM_STACK_PUSHPVALUE(SIMPLE_API_GETPOINTER(1));
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_API_GETPOINTERTYPE(1) ;
			simple_vm_expr_npoo(vm,"lengthOf",0);
			vm->nIgnoreNULL = 1 ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_add ( void *pointer )
{
	List *list,*list2  ;
	VM *vm  ;
	vm = (VM *) pointer ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1) ;
		if ( SIMPLE_API_ISSTRING(2) ) {
			simple_list_addstring2_gc(vm->sState,list,SIMPLE_API_GETSTRING(2),SIMPLE_API_GETSTRINGSIZE(2));
			SIMPLE_API_RETSTRING2(SIMPLE_API_GETSTRING(2),SIMPLE_API_GETSTRINGSIZE(2));
		}
		else if ( SIMPLE_API_ISNUMBER(2) ) {
			simple_list_adddouble_gc(vm->sState,list,SIMPLE_API_GETNUMBER(2));
			SIMPLE_API_RETNUMBER(SIMPLE_API_GETNUMBER(2));
		}
		else if ( SIMPLE_API_ISLIST(2) ) {
			list2 = SIMPLE_API_GETLIST(2) ;
			simple_vm_addlisttolist(vm,list2,list);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/** Block declarations with Headers in simple_vm.c**/

/* String As Array As:In Strindex*/

void simple_vm_stsimple_pushv ( VM *vm )
{
	char *newstr  ;
	char cStr[2]  ;
	newstr = (char *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	cStr[0] = newstr[0] ;
	cStr[1] = '\0' ;
	SIMPLE_VM_STACK_PUSHCVALUE(cStr);
}

void simple_vm_stsimple_assignment ( VM *vm )
{
	String *cStr1  ;
	char *newstr  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		cStr1 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( simple_string_size(cStr1) == 1 ) {
			newstr = (char *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			newstr[0] = simple_string_get(cStr1)[0] ;
			simple_string_delete_gc(vm->sState,cStr1);
			return ;
		} else {
			simple_string_delete_gc(vm->sState,cStr1);
			simple_vm_error(vm,SIMPLE_VM_ERROR_VALUEMORETHANONECHAR);
			return ;
		}
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_VARISNOTSTRING);
		return ;
	}
}

void simple_vm_stsimple_index ( VM *vm, String *pString, double nNum1 )
{
	char *newstr  ; 
	/* We will push a pointer of the sub char to the stack */
	if ( nNum1 < list_index || nNum1 > simple_string_size(pString) ) {
            simple_vm_error(vm,SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
            return ;
	}
	newstr = pString->cStr ;
	newstr = newstr + ((int) (nNum1 - list_index) ) ;
	SIMPLE_VM_STACK_PUSHPVALUE(newstr);
	SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_SUBSTRING ;
}

/* Try Catch Done */

void simple_vm_try ( VM *vm )
{
	List *list  ;
	list = simple_list_newlist_gc(vm->sState,vm->pTry);
	simple_list_addint_gc(vm->sState,list,SIMPLE_VM_IR_READI);
	simple_vm_savestate(vm,list);
	vm->nActiveCatch = 0 ;
}

void simple_vm_catch ( VM *vm,const char *cError )
{
	List *list  ;
	list = simple_list_getlist(vm->pTry,simple_list_getsize(vm->pTry));
	vm->nPC = simple_list_getint(list,1) ;
	simple_vm_restorestate(vm,list,2,SIMPLE_STATE_TRYCATCH);
	/* Define variable __err__ to contain the error message */
	simple_list_setstsimple_gc(vm->sState,simple_list_getlist(simple_vm_getglobalscope(vm),6),3,cError);
	/* Tell C-API caller (CALL command) that catch happens! */
	vm->nActiveCatch = 1 ;
	/* Catch Statements must be executed without try effects */
	simple_vm_done(vm);
}

void simple_vm_done ( VM *vm )
{
	simple_list_deleteitem_gc(vm->sState,vm->pTry,simple_list_getsize(vm->pTry));
}
