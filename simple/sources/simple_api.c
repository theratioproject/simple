
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
/* Support for C Blocks */

//TODO : move to headers
SIMPLE_API void simple_vmlib_isblock( void *pointer );
SIMPLE_API void simple_vmlib_throw( void *pointer );

SIMPLE_API void register_block_t ( SimpleState *sState,const char *cStr, void (*pBlock)(void *) )
{
	List *list  ;
	if ( sState->c_blocks == NULL ) {
		sState->c_blocks = simple_list_new_gc(sState,0);
	}
	list = simple_list_newlist_gc(sState,sState->c_blocks);
	simple_list_addstring_gc(sState,list,cStr);
	simple_list_addblockpointer_gc(sState,list,pBlock);
}

SIMPLE_API void loadcblocks ( SimpleState *sState )
{
	/** General **/
	register_block("lengthOf",simple_vmlib_len);
	register_block("__add_to_list",simple_vmlib_add);
	register_block("ascii",simple_vmlib_char);
	register_block("simpleVersion",simple_vmlib_version);
        /* Check Data Type */
    register_block("isString",simple_vmlib_isstring);
	register_block("isNumber",simple_vmlib_isnumber);
	register_block("isList",simple_vmlib_islist);
	register_block("getType",simple_vmlib_type);
	register_block("isNull",simple_vmlib_isnull);
	register_block("isObject",simple_vmlib_isobject);
	register_block("isPointer",simple_vmlib_ispointer);
        /** Functional Execution **/
	register_block("executeCode",simple_vmlib_exec);
        /* Meta */
	register_block("hasBlock",simple_vmlib_isblock);
    register_block("__throw",simple_vmlib_throw);
	#ifdef __ANDROID__
    __init_full_tick(sState);
	#endif
	/*
	**  Simple Display and Read 
	**  Also we add the display() and read() block to the api
	*/
	register_block("display",display_string);
	register_block("read",read_string);
	
	/*
	* Dynamically call a wrapper shared library in simple-lang
	*/
	register_block("callDynamicModule",simple_vm_dll_calllib);
	register_block("closeDynamicModule",simple_vm_dll_closelib);
	sState->loaded_cblocks = 1 ;
}

#ifdef __ANDROID__
SIMPLE_API void __a_init_full_tick(SimpleState *sState) { printf("hella \n"); }
__android_init_full_tick __init_full_tick = __a_init_full_tick ;
#endif

SIMPLE_API int api_is_list ( void *pointer,int x )
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
	**  We need this because some C Blocks get int * or double * as parameter 
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
		return pItem->data.string->str ;
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
	**  When we pass int * for Simple Variable Value to a C Block 
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
		SIMPLE_API_RETNUMBER(SIMPLE_API_GETSTRINGSIZE(1));
	}
	else if ( SIMPLE_API_ISLIST(1) ) {
		if ( simple_vm_oop_isobject(SIMPLE_API_GETLIST(1)) == 0 ) {
			SIMPLE_API_RETNUMBER(simple_list_getsize(SIMPLE_API_GETLIST(1)));
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

void simple_vmlib_version ( void *pointer )
{
	SIMPLE_API_RETSTRING(SIMPLE_VERSION);
}

/* Check Data Type */

void simple_vmlib_isstring ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETNUMBER(1);
	} else {
		SIMPLE_API_RETNUMBER(0);
	}
}

void simple_vmlib_isnumber ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(1);
	} else {
		SIMPLE_API_RETNUMBER(0);
	}
}

void simple_vmlib_islist ( void *pointer )
{
	List *list;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		if ( simple_vm_oop_isobject(SIMPLE_API_GETLIST(1) ) == 0 ) {
			list = SIMPLE_API_GETLIST(1) ;
			if ( simple_list_ispointer(list,1) && simple_list_getpointer(list,1) == NULL ) {
				SIMPLE_API_RETNUMBER(0);
				return ;
			}
			SIMPLE_API_RETNUMBER(1);
			return ;
		}
	}
	SIMPLE_API_RETNUMBER(0);
}

void simple_vmlib_type ( void *pointer )
{
	List *list  ;
	VM *vm  ;
	vm = (VM *) pointer ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	/* The order of checking C Pointer and OBJECT before List is important because the list can be both of them */
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETSTRING("String");
	}
	else if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETSTRING("Number");
	}
	else if ( SIMPLE_API_ISCPOINTER(1) ) {
		list = SIMPLE_API_GETLIST(1) ;
		SIMPLE_API_RETSTRING(simple_list_getstring(list,SIMPLE_CPOINTER_TYPE));
	}
	else if ( SIMPLE_API_ISOBJECT(1) ) {
		SIMPLE_VM_STACK_PUSHPVALUE(SIMPLE_API_GETPOINTER(1));
		SIMPLE_VM_STACK_OBJTYPE = SIMPLE_API_GETPOINTERTYPE(1) ;
		simple_vm_expr_npoo(vm,"getType",0);
		vm->nIgnoreNULL = 1 ;
	}
	else if ( SIMPLE_API_ISLIST(1) ) {
		SIMPLE_API_RETSTRING("List");
	} else {
		SIMPLE_API_RETSTRING("(null)");
	}
}

SIMPLE_API void simple_vmlib_isnull ( void *pointer )
{
	List *list;
	Item *item;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	 if (SIMPLE_API_ISLIST(1)) {
		list = SIMPLE_API_GETLIST(1) ;
		if ( simple_list_ispointer(list,1) && simple_list_getpointer(list,1) == NULL ) {
			SIMPLE_API_RETNUMBER(1);
			return ;
		}
	} else if ( SIMPLE_API_ISPOINTER(1) ) {
		if ( SIMPLE_API_GETPOINTER(1) == NULL ) {
			SIMPLE_API_RETNUMBER(1);
			return ;
		}
	}
	SIMPLE_API_RETNUMBER(0);
}

void simple_vmlib_isobject ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		if ( simple_vm_oop_isobject(SIMPLE_API_GETLIST(1) ) == 1 ) {
			SIMPLE_API_RETNUMBER(1);
			return ;
		}
	}
	SIMPLE_API_RETNUMBER(0);
}

void simple_vmlib_ispointer ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		SIMPLE_API_RETNUMBER(1);
		return ;
	}
	SIMPLE_API_RETNUMBER(0);
}

/* Functional Execution */

SIMPLE_API void simple_vmlib_exec ( void *pointer )
{
	const char *cStr  ;
	VM *vm  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1); 
		vm = (VM *) pointer ;
		vm->nEvalCalledFromSimpleCode = 1 ;
		if ( simple_vm_exec(vm,cStr) == 0 ) {
			vm->nEvalCalledFromSimpleCode = 0 ;
		}
		/*
		**  The CALL instruction will check nEvalCalledFromSimpleCode to execute the main loop again 
		**  Before executing the main loop again, The CALL instruction will set nEvalCalledFromSimpleCode to 0 
		*/
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void simple_vmlib_isblock ( void *pointer )
{
	List *pList  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) == 0 ) {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			return ;
		}
		if ( SIMPLE_API_ISSTRING(2) ) {
			cStr = SIMPLE_API_GETSTRING(2) ;
			SIMPLE_API_RETNUMBER(simple_vm_oop_isblock((VM *) pointer,pList,cStr));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void simple_vmlib_throw(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if (((VM *) pointer)->sState->skip_error == 0) 
			((VM *) pointer)->sState->skip_error = 1;
		SIMPLE_API_ERROR(SIMPLE_API_GETSTRING(1));
		if (((VM *) pointer)->sState->skip_error == 1) 
			((VM *) pointer)->sState->skip_error = 0;
		return;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_char ( void *pointer )
{
	int x  ;
	char cStr[2]  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		x = SIMPLE_API_GETNUMBER(1) ;
		cStr[0] = (char) x ;
		cStr[1] = '\0' ;
		SIMPLE_API_RETSTRING2(cStr,1);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}


void simple_vm_dll_calllib ( void *pointer )
{
    LpHandleType handle  ;
	int x ;
    const char *cDLL  ;
    char library_path[200]  ; 
	char module_path[SIMPLE_PATHSIZE]  ;
	char simple_folder[100] ;
	char* simple_env_path;
    loadlibblockptr pBlock  ;
    VM *vm  ;
    SimpleState *sState  ;
    vm = (VM *) pointer ;
    sState = vm->sState ;
	strcpy(library_path,SIMPLE_API_GETSTRING(1));
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISSTRING(1) ) {
		if (!simple_fexists(library_path)) {
			for ( x = 1 ; x <= simple_list_getsize(sState->module_paths) ; x++ ) {
				snprintf(module_path, sizeof(module_path), "%s/dynamic_modules/%s", simple_list_getstring(sState->module_paths,x), library_path);
				if (simple_fexists(module_path)) {
					strcpy(library_path,module_path);
					break;
				}
			}
		}
        cDLL = library_path;
        handle = LoadDLL(cDLL);
		if ( handle == NULL ) {
                SIMPLE_API_ERROR2(SIMPLE_VM_ERROR_LIBLOADERROR,library_path);
                return ;
        } 
        pBlock = (loadlibblockptr) GetDLLBlock(handle, "init_simple_module") ;
        if ( pBlock == NULL ) {
                SIMPLE_API_ERROR2("The dynamic library doesn't contain the init_simple_module() block!",file_real_name(library_path));
                return ;
        } 
        simple_list_deletearray_gc(sState,sState->c_blocks);
        (*pBlock)(sState) ;
        simple_list_genarray_gc(sState,sState->c_blocks);
        simple_list_genhashtable2_gc(sState,sState->c_blocks);
        SIMPLE_API_RETCPOINTER(handle,"SIMPLE_DYNAMIC_LIBRARY_");
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void simple_vm_dll_closelib ( void *pointer )
{
	LpHandleType handle  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		handle = SIMPLE_API_GETCPOINTER(1,"SIMPLE_DYNAMIC_LIBRARY_") ;
		CloseDLL(handle);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/* User Interface - Commands Implementation (Faster) - Because we don't have blocks call */

SIMPLE_API void simple_vm_display ( VM *vm )
{
	Item *pItem  ;
	char cStr[100]  ;
	List *list  ;
	char *string  ;
	int x  ;
	if ( vm->nBlockExecute > 0 ) {
		vm->nBlockExecute-- ;
	}
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		string = SIMPLE_VM_STACK_READC ;
		if ( strlen(string) != (unsigned int) SIMPLE_VM_STACK_STRINGSIZE ) {
			for ( x = 0 ; x < SIMPLE_VM_STACK_STRINGSIZE ; x++ ) {
				printf( "%c",string[x] ) ;
			}
		} else {
			printf( "%s",string ) ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			list = simple_list_getlist((List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_VALUE);
			if ( simple_vm_oop_isobject(list) ) {
				simple_vm_oop_printobj(vm,list);
			} else {
				simple_list_print(list);
			}
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			list = simple_item_getlist(pItem) ;
			if ( simple_vm_oop_isobject(list) ) {
				simple_vm_oop_printobj(vm,list);
			} else {
				simple_list_print(list);
			}
		}
		else {
			printf("(null)");
		}
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		simple_vm_numtostring(vm,SIMPLE_VM_STACK_READN,cStr);
		printf( "%s",cStr ) ;
	}
	SIMPLE_VM_STACK_POP ;
	simple_vm_freestack(vm);
	fflush(stdout);
}

SIMPLE_API void simple_vm_read ( VM *vm )
{
	int x  ;
	char cLine[256]  ;
	List *var  ;
	Item *pItem  ;
	/* Get Input From the User and save it in the variable */
	fgets(cLine , 256 , stdin );
	/* Remove New Line */
	for ( x = 0 ; x <= 255 ; x++ ) {
		if ( cLine[x] == '\n' ) {
			cLine[x] = '\0' ;
			break ;
		}
	}
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			var = (List *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			simple_list_setint_gc(vm->sState,var, SIMPLE_VAR_TYPE ,SIMPLE_VM_STRING);
			simple_list_setstring_gc(vm->sState,var, SIMPLE_VAR_VALUE, cLine);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE ==SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			SIMPLE_VM_STACK_POP ;
			simple_item_settype_gc(vm->sState,pItem,ITEMTYPE_STRING);
			simple_string_set_gc(vm->sState,simple_item_getstring(pItem),cLine);
		}
	}
}

/* User Interface Blocks (Another implementation) - Flexibile (We can replace blocks in Simple Code) */

void display_string ( void *pointer )
{
	char *string  ;
	int x  ;
	char cStr[100]  ;
	List *list  ;
	VM *vm  ;
	vm = (VM *) pointer ;
	if ( SIMPLE_API_ISSTRING(1) ) {
		string = SIMPLE_API_GETSTRING(1) ;
		if ( strlen(string) != (unsigned int) SIMPLE_API_GETSTRINGSIZE(1) ) {
			for ( x = 0 ; x < SIMPLE_API_GETSTRINGSIZE(1) ; x++ ) {
				printf( "%c",string[x] ) ;
			}
		} else {
			printf( "%s",string ) ;
		}
	}
	else if ( SIMPLE_API_ISNUMBER(1) ) {
		simple_vm_numtostring(vm,SIMPLE_API_GETNUMBER(1),cStr);
		printf( "%s",cStr ) ;
	}
	else if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1);
		if ( simple_vm_oop_isobject(list) ) {
			simple_vm_oop_printobj(vm,list);
		} else {
			simple_list_print(list);
		}
	}
	fflush(stdout);
}

void read_string ( void *pointer )
{
	int x  ;
	char cLine[256]  ;
	/* Get Input From the User and save it in the variable */
	fgets(cLine , 256 , stdin );
	/* Remove New Line */
	for ( x = 0 ; x <= 255 ; x++ ) {
		if ( cLine[x] == '\n' ) {
			cLine[x] = '\0' ;
			break ;
		}
	}
	SIMPLE_API_RETSTRING(cLine);
}