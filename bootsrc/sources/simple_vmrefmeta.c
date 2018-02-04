
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
#include "../includes/simple_vmrefmeta.h"
/* Functions */

void simple_vm_refmeta_loadfunctions ( SimpleState *pSimpleState )
{
	/* Functions */
	simple_vm_funcregister("locals",simple_vm_refmeta_locals);
	simple_vm_funcregister("globals",simple_vm_refmeta_globals);
	simple_vm_funcregister("functions",simple_vm_refmeta_functions);
	simple_vm_funcregister("cfunctions",simple_vm_refmeta_cfunctions);
	simple_vm_funcregister("islocal",simple_vm_refmeta_islocal);
	simple_vm_funcregister("isglobal",simple_vm_refmeta_isglobal);
	simple_vm_funcregister("isfunction",simple_vm_refmeta_isfunction);
	simple_vm_funcregister("iscfunction",simple_vm_refmeta_iscfunction);
	/* OOP */
	simple_vm_funcregister("moduless",simple_vm_refmeta_moduless);
	simple_vm_funcregister("ismodules",simple_vm_refmeta_ismodules);
	simple_vm_funcregister("classes",simple_vm_refmeta_classes);
	simple_vm_funcregister("isclass",simple_vm_refmeta_isclass);
	simple_vm_funcregister("modulesclasses",simple_vm_refmeta_modulesclasses);
	simple_vm_funcregister("ismodulesclass",simple_vm_refmeta_ismodulesclass);
	simple_vm_funcregister("classname",simple_vm_refmeta_classname);
	simple_vm_funcregister("objectid",simple_vm_refmeta_objectid);
	simple_vm_funcregister("attributes",simple_vm_refmeta_attributes);
	simple_vm_funcregister("methods",simple_vm_refmeta_methods);
	simple_vm_funcregister("isattribute",simple_vm_refmeta_isattribute);
	simple_vm_funcregister("ismethod",simple_vm_refmeta_ismethod);
	simple_vm_funcregister("isprivateattribute",simple_vm_refmeta_isprivateattribute);
	simple_vm_funcregister("isprivatemethod",simple_vm_refmeta_isprivatemethod);
	simple_vm_funcregister("addattribute",simple_vm_refmeta_addattribute);
	simple_vm_funcregister("addmethod",simple_vm_refmeta_addmethod);
	simple_vm_funcregister("getattribute",simple_vm_refmeta_getattribute);
	simple_vm_funcregister("setattribute",simple_vm_refmeta_setattribute);
	simple_vm_funcregister("mergemethods",simple_vm_refmeta_mergemethods);
	simple_vm_funcregister("modulesname",simple_vm_refmeta_modulesname);
	/* VM */
	simple_vm_funcregister("ringvm_fileslist",simple_vm_refmeta_ringvmfileslist);
	simple_vm_funcregister("ringvm_calllist",simple_vm_refmeta_ringvmcalllist);
	simple_vm_funcregister("ringvm_memorylist",simple_vm_refmeta_ringvmmemorylist);
	simple_vm_funcregister("ringvm_functionslist",simple_vm_refmeta_ringvmfunctionslist);
	simple_vm_funcregister("ringvm_classeslist",simple_vm_refmeta_ringvmclasseslist);
	simple_vm_funcregister("ringvm_modulesslist",simple_vm_refmeta_ringvmmodulesslist);
	simple_vm_funcregister("ringvm_cfunctionslist",simple_vm_refmeta_ringvmcfunctionslist);
	simple_vm_funcregister("ringvm_settrace",simple_vm_refmeta_ringvmsettrace);
	simple_vm_funcregister("ringvm_tracedata",simple_vm_refmeta_ringvmtracedata);
	simple_vm_funcregister("ringvm_traceevent",simple_vm_refmeta_ringvmtraceevent);
	simple_vm_funcregister("ringvm_tracefunc",simple_vm_refmeta_ringvmtracefunc);
	simple_vm_funcregister("ringvm_scopescount",simple_vm_refmeta_ringvmscopescount);
	simple_vm_funcregister("ringvm_evalinscope",simple_vm_refmeta_ringvmevalinscope);
	simple_vm_funcregister("ringvm_passerror",simple_vm_refmeta_ringvmpasserror);
	simple_vm_funcregister("ringvm_hideerrormsg",simple_vm_refmeta_ringvmhideerrormsg);
	simple_vm_funcregister("ringvm_callfunc",simple_vm_refmeta_ringvmcallfunc);
}
/* Functions */

void simple_vm_refmeta_locals ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2, *pList3  ;
	vm = (VM *) pPointer ;
	/* We use -1 to skip the current scope of the locals() function */
	pList = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1) ;
	pList2 = SIMPLE_API_NEWLIST ;
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList3 = simple_list_getlist(pList,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList2,simple_list_getstring(pList3,SIMPLE_VAR_NAME));
	}
	SIMPLE_API_RETLIST(pList2);
}

void simple_vm_refmeta_globals ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2, *pList3  ;
	vm = (VM *) pPointer ;
	pList = simple_vm_getglobalscope(vm) ;
	pList2 = SIMPLE_API_NEWLIST ;
	/* We avoid internal global variables like true, false */
	for ( x = SIMPLE_VM_INTERNALGLOBALSCOUNT + 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList3 = simple_list_getlist(pList,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList2,simple_list_getstring(pList3,SIMPLE_VAR_NAME));
	}
	SIMPLE_API_RETLIST(pList2);
}

void simple_vm_refmeta_functions ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	vm = (VM *) pPointer ;
	pList = SIMPLE_API_NEWLIST ;
	for ( x = 1 ; x <= simple_list_getsize(vm->pFunctionsMap) ; x++ ) {
		pList2 = simple_list_getlist(vm->pFunctionsMap,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList,simple_list_getstring(pList2,SIMPLE_BLOCKMAP_NAME));
	}
	SIMPLE_API_RETLIST(pList);
}

void simple_vm_refmeta_cfunctions ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	vm = (VM *) pPointer ;
	pList = SIMPLE_API_NEWLIST ;
	for ( x = 1 ; x <= simple_list_getsize(vm->pCFunctionsList) ; x++ ) {
		pList2 = simple_list_getlist(vm->pCFunctionsList,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList,simple_list_getstring(pList2,SIMPLE_BLOCKMAP_NAME));
	}
	SIMPLE_API_RETLIST(pList);
}

void simple_vm_refmeta_islocal ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	const char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		/* We use -1 to skip the current scope of the locals() function */
		pList = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1) ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_VAR_NAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_isglobal ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	const char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		pList = simple_vm_getglobalscope(vm) ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_VAR_NAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_isfunction ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	const char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		pList = vm->pFunctionsMap ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_BLOCKMAP_NAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_iscfunction ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	const char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		pList = vm->pCFunctionsList ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_BLOCKMAP_NAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
/* OOP */

void simple_vm_refmeta_moduless ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	vm = (VM *) pPointer ;
	pList = SIMPLE_API_NEWLIST ;
	for ( x = 1 ; x <= simple_list_getsize(vm->pModulessMap) ; x++ ) {
		pList2 = simple_list_getlist(vm->pModulessMap,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList,simple_list_getstring(pList2,SIMPLE_MODULENAME));
	}
	SIMPLE_API_RETLIST(pList);
}

void simple_vm_refmeta_ismodules ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		simple_string_lower(cStr);
		pList = vm->pModulessMap ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_MODULENAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_classes ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	vm = (VM *) pPointer ;
	pList = SIMPLE_API_NEWLIST ;
	for ( x = 1 ; x <= simple_list_getsize(vm->pClassesMap) ; x++ ) {
		pList2 = simple_list_getlist(vm->pClassesMap,x);
		simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList,simple_list_getstring(pList2,SIMPLE_CLASSMAP_CLASSNAME));
	}
	SIMPLE_API_RETLIST(pList);
}

void simple_vm_refmeta_isclass ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		simple_string_lower(cStr);
		pList = vm->pClassesMap ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_CLASSMAP_CLASSNAME),cStr) == 0 ) {
				SIMPLE_API_RETNUMBER(1);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_modulesclasses ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2, *pList3  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		simple_string_lower(cStr);
		pList = vm->pModulessMap ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_MODULENAME),cStr) == 0 ) {
				pList3 = SIMPLE_API_NEWLIST ;
				pList2 = simple_list_getlist(pList2,SIMPLE_CLASSESLIST) ;
				/* We can use the variable x for the loop again because we have return */
				for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
					simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList3,simple_list_getstring(simple_list_getlist(pList2,x),SIMPLE_CLASSMAP_CLASSNAME));
				}
				SIMPLE_API_RETLIST(pList3);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_ismodulesclass ( void *pPointer )
{
	VM *vm  ;
	int x  ;
	List *pList, *pList2  ;
	char *cStr, *cStr2  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_GETSTRING(1) &&  SIMPLE_API_GETSTRING(2) ) {
		vm = (VM *) pPointer ;
		cStr = SIMPLE_API_GETSTRING(1) ;
		simple_string_lower(cStr);
		cStr2 = SIMPLE_API_GETSTRING(2) ;
		simple_string_lower(cStr2);
		pList = vm->pModulessMap ;
		for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
			pList2 = simple_list_getlist(pList,x);
			if ( strcmp(simple_list_getstring(pList2,SIMPLE_MODULENAME),cStr) == 0 ) {
				pList2 = simple_list_getlist(pList2,SIMPLE_CLASSESLIST) ;
				/* We can use the variable x for the loop again because we have return */
				for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(pList2,x),SIMPLE_CLASSMAP_CLASSNAME),cStr2)==0 ) {
						SIMPLE_API_RETNUMBER(1);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(0);
				return ;
			}
		}
		SIMPLE_API_RETNUMBER(0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_classname ( void *pPointer )
{
	List *pList  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			cStr = simple_list_getstring((List *) simple_list_getpointer(pList,SIMPLE_OBJECT_CLASSPOINTER),SIMPLE_CLASSMAP_CLASSNAME);
			SIMPLE_API_RETSTRING(cStr);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_objectid ( void *pPointer )
{
	List *pList  ;
	char cStr[100]  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			sprintf( cStr , "%p" , (void *) pList ) ;
			SIMPLE_API_RETSTRING(cStr);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_attributes ( void *pPointer )
{
	List *pList, *pList2  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			pList2 = SIMPLE_API_NEWLIST ;
			for ( x = 3 ; x <= simple_list_getsize(pList) ; x++ ) {
				simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList2,simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_VAR_NAME));
			}
			SIMPLE_API_RETLIST(pList2);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_methods ( void *pPointer )
{
	List *pList, *pList2  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = (List *) simple_list_getpointer(pList,SIMPLE_OBJECT_CLASSPOINTER);
			pList = simple_list_getlist(pList,SIMPLE_CLASSMAP_METHODSLIST);
			pList2 = SIMPLE_API_NEWLIST ;
			for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
				simple_list_addstring_gc(((VM *) pPointer)->pSimpleState,pList2,simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_BLOCKMAP_NAME));
			}
			SIMPLE_API_RETLIST(pList2);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_isattribute ( void *pPointer )
{
	List *pList  ;
	int x  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISSTRING(2) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			cStr = SIMPLE_API_GETSTRING(2) ;
			simple_string_lower(cStr);
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			for ( x = 3 ; x <= simple_list_getsize(pList) ; x++ ) {
				if ( strcmp(cStr,simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_VAR_NAME))==0 ) {
					SIMPLE_API_RETNUMBER(1);
					return ;
				}
			}
			SIMPLE_API_RETNUMBER(0);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_ismethod ( void *pPointer )
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
			simple_string_lower(cStr);
			SIMPLE_API_RETNUMBER(simple_vm_oop_ismethod((VM *) pPointer,pList,cStr));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_isprivateattribute ( void *pPointer )
{
	List *pList  ;
	int x  ;
	char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISSTRING(2) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			cStr = SIMPLE_API_GETSTRING(2) ;
			simple_string_lower(cStr);
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			for ( x = 3 ; x <= simple_list_getsize(pList) ; x++ ) {
				if ( strcmp(cStr,simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_VAR_NAME))==0 ) {
					if ( simple_list_getint(simple_list_getlist(pList,x),SIMPLE_VAR_PRIVATEFLAG) == 1 ) {
						SIMPLE_API_RETNUMBER(1);
					}
					else {
						SIMPLE_API_RETNUMBER(0);
					}
					return ;
				}
			}
			SIMPLE_API_RETNUMBER(0);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_isprivatemethod ( void *pPointer )
{
	List *pList  ;
	int x  ;
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
			simple_string_lower(cStr);
			x = simple_vm_oop_ismethod((VM *) pPointer,pList,cStr) ;
			if ( x==2 ) {
				SIMPLE_API_RETNUMBER(1);
			}
			else {
				SIMPLE_API_RETNUMBER(0);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_addattribute ( void *pPointer )
{
	List *pList, *pList2  ;
	char *cStr  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			if ( SIMPLE_API_ISSTRING(2) ) {
				cStr = SIMPLE_API_GETSTRING(2) ;
				simple_string_lower(cStr);
				/* Create Variable List */
				simple_vm_newvar2((VM *)pPointer,cStr,pList);
			}
			else if ( SIMPLE_API_ISLIST(2) ) {
				pList2 = SIMPLE_API_GETLIST(2) ;
				for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
					if ( simple_list_isstring(pList2,x) ) {
						cStr = simple_list_getstring(pList2,x);
						simple_string_lower(cStr);
						/* Create Variable List */
						simple_vm_newvar2((VM *)pPointer,cStr,pList);
					}
				}
			} else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_addmethod ( void *pPointer )
{
	List *pList, *pList2, *pList3  ;
	char *cStr  ;
	int x  ;
	VM *vm  ;
	/* Parameters : Object, MethodName, Anonymous Function */
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = (List *) simple_list_getlist(pList,SIMPLE_OBJECT_CLASSPOINTER);
			pList = (List *) simple_list_getlist(pList,SIMPLE_CLASSMAP_METHODSLIST);
			cStr = SIMPLE_API_GETSTRING(3);
			simple_string_lower(cStr);
			for ( x = 1 ; x <= simple_list_getsize(vm->pFunctionsMap) ; x++ ) {
				pList2 = simple_list_getlist(vm->pFunctionsMap,x);
				if ( strcmp(simple_list_getstring(pList2,SIMPLE_BLOCKMAP_NAME),cStr) == 0 ) {
					/* Add new list to the class methods list */
					pList3 = simple_list_newlist_gc(((VM *) pPointer)->pSimpleState,pList);
					/* Copy function to class methods */
					simple_list_copy(pList3,pList2);
					/* Set the Function Name */
					simple_list_setstsimple_gc(((VM *) pPointer)->pSimpleState,pList3,SIMPLE_BLOCKMAP_NAME,simple_string_lower(SIMPLE_API_GETSTRING(2)));
					/* Refresh the HashTable */
					simple_list_genhashtable2(pList);
					SIMPLE_API_RETNUMBER(1);
					return ;
				}
			}
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
	SIMPLE_API_RETNUMBER(0);
}

void simple_vm_refmeta_getattribute ( void *pPointer )
{
	List *pList  ;
	char *cStr  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISSTRING(2) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			cStr = SIMPLE_API_GETSTRING(2) ;
			simple_string_lower(cStr);
			for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
				if ( strcmp(simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_VAR_NAME),cStr) == 0 ) {
					pList = simple_list_getlist(pList,x) ;
					if ( simple_list_isnumber(pList,SIMPLE_VAR_VALUE) ) {
						SIMPLE_API_RETNUMBER(simple_list_getdouble(pList,SIMPLE_VAR_VALUE));
					}
					else if ( simple_list_isstring(pList,SIMPLE_VAR_VALUE) ) {
						SIMPLE_API_RETSTRING2(simple_list_getstring(pList,SIMPLE_VAR_VALUE),simple_list_getstringsize(pList,SIMPLE_VAR_VALUE));
					}
					else if ( simple_list_islist(pList,SIMPLE_VAR_VALUE) ) {
						SIMPLE_API_RETLIST(simple_list_getlist(pList,SIMPLE_VAR_VALUE));
					}
					return ;
				}
			}
			SIMPLE_API_ERROR("Error : Property is not found!");
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_setattribute ( void *pPointer )
{
	List *pList  ;
	char *cStr  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISSTRING(2) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(pList) ) {
			pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA);
			cStr = SIMPLE_API_GETSTRING(2) ;
			simple_string_lower(cStr);
			for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
				if ( strcmp(simple_list_getstring(simple_list_getlist(pList,x),SIMPLE_VAR_NAME),cStr) == 0 ) {
					pList = simple_list_getlist(pList,x) ;
					if ( SIMPLE_API_ISNUMBER(3) ) {
						simple_list_setdouble_gc(((VM *) pPointer)->pSimpleState,pList,SIMPLE_VAR_VALUE,SIMPLE_API_GETNUMBER(3));
					}
					else if ( SIMPLE_API_ISSTRING(3) ) {
						simple_list_setstring2_gc(((VM *) pPointer)->pSimpleState,pList,SIMPLE_VAR_VALUE,SIMPLE_API_GETSTRING(3),SIMPLE_API_GETSTRINGSIZE(3));
					}
					else if ( SIMPLE_API_ISLIST(3) ) {
						simple_list_setlist_gc(((VM *) pPointer)->pSimpleState,pList,SIMPLE_VAR_VALUE);
						pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
						simple_list_deleteallitems_gc(((VM *) pPointer)->pSimpleState,pList);
						simple_list_copy(pList,SIMPLE_API_GETLIST(3));
					}
					return ;
				}
			}
			SIMPLE_API_ERROR("Error : Property is not found!");
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_mergemethods ( void *pPointer )
{
	int x  ;
	List *pList, *pList2, *pList3  ;
	VM *vm  ;
	char *cStr, *cStr2  ;
	/*
	**  We copy class methods from class to another class 
	**  First Parameter = Dest Class Name, Second Para = Source Class Name 
	**  The Source Class is expected to be without Parent Class and Without Attributes 
	*/
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
		cStr = SIMPLE_API_GETSTRING(1) ;
		cStr2 = SIMPLE_API_GETSTRING(2) ;
		simple_string_lower(cStr);
		simple_string_lower(cStr2);
		vm = (VM *) pPointer ;
		/* Get the Dest Class Methods List */
		pList2 = NULL ;
		for ( x = 1 ; x <= simple_list_getsize(vm->pClassesMap) ; x++ ) {
			pList = simple_list_getlist(vm->pClassesMap,x) ;
			if ( strcmp(simple_list_getstring(pList,SIMPLE_CLASSMAP_CLASSNAME),cStr) == 0 ) {
				/* Check if the class is imported from a Modules */
				if ( simple_list_getsize(pList) == SIMPLE_CLASSMAP_IMPORTEDCLASSSIZE ) {
					pList = simple_list_getlist(pList,SIMPLE_CLASSMAP_POINTERTOLISTOFCLASSINSIDEMODULE);
				}
				pList2 = simple_list_getlist(pList,SIMPLE_CLASSMAP_METHODSLIST) ;
				break ;
			}
		}
		if ( pList2 == NULL ) {
			SIMPLE_API_ERROR("Error, Can't find the dest class!");
			return ;
		}
		/* Get the Source Class Methods List */
		pList3 = NULL ;
		for ( x = 1 ; x <= simple_list_getsize(vm->pClassesMap) ; x++ ) {
			pList = simple_list_getlist(vm->pClassesMap,x) ;
			if ( strcmp(simple_list_getstring(pList,SIMPLE_CLASSMAP_CLASSNAME),cStr2) == 0 ) {
				/* Check if the class is imported from a Modules */
				if ( simple_list_getsize(pList) == SIMPLE_CLASSMAP_IMPORTEDCLASSSIZE ) {
					pList = simple_list_getlist(pList,SIMPLE_CLASSMAP_POINTERTOLISTOFCLASSINSIDEMODULE);
				}
				pList3 = simple_list_getlist(pList,SIMPLE_CLASSMAP_METHODSLIST) ;
				break ;
			}
		}
		if ( pList3 == NULL ) {
			SIMPLE_API_ERROR("Error, Can't find the source class!");
			return ;
		}
		/* Copy Methods from Source to Dest */
		simple_list_copy(pList2,pList3);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_modulesname ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	SIMPLE_API_RETSTRING(simple_string_get(vm->pModulesName));
}
/* VM */

void simple_vm_refmeta_ringvmfileslist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pSimpleState->pSimpleFilesList);
}

void simple_vm_refmeta_ringvmcalllist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pFuncCallList);
}

void simple_vm_refmeta_ringvmmemorylist ( void *pPointer )
{
	VM *vm  ;
	List *pList, *pList2  ;
	vm = (VM *) pPointer ;
	pList = simple_list_new_gc(((VM *) pPointer)->pSimpleState,0) ;
	simple_list_copy(pList,vm->pMem);
	pList2 = SIMPLE_API_NEWLIST ;
	simple_list_copy(pList2,pList);
	simple_list_delete_gc(((VM *) pPointer)->pSimpleState,pList);
	SIMPLE_API_RETLIST(pList2);
}

void simple_vm_refmeta_ringvmfunctionslist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pFunctionsMap);
}

void simple_vm_refmeta_ringvmclasseslist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pClassesMap);
}

void simple_vm_refmeta_ringvmmodulesslist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pModulessMap);
}

void simple_vm_refmeta_ringvmcfunctionslist ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pCFunctionsList);
}

void simple_vm_refmeta_ringvmsettrace ( void *pPointer )
{
	VM *vm  ;
	char *cStr  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1) ;
		if ( strcmp(cStr,"") == 0 ) {
			vm->lTrace = 0 ;
			simple_string_set_gc(((VM *) pPointer)->pSimpleState,vm->pTrace,"");
		}
		else {
			vm->lTrace = 1 ;
			simple_string_set_gc(((VM *) pPointer)->pSimpleState,vm->pTrace,cStr);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_ringvmtracedata ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETLIST(vm->pTraceData);
}

void simple_vm_refmeta_ringvmtraceevent ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETNUMBER(vm->nTraceEvent);
}

void simple_vm_refmeta_ringvmtracefunc ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	SIMPLE_API_RETSTRING(simple_string_get(vm->pTrace));
}

void simple_vm_refmeta_ringvmscopescount ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	/* We uses -1 to avoid adding the current scope of this function */
	SIMPLE_API_RETNUMBER(simple_list_getsize(vm->pMem) - 1);
}

void simple_vm_refmeta_ringvmevalinscope ( void *pPointer )
{
	VM *vm  ;
	List *pActiveMem,*pState  ;
	const char *cStr  ;
	int nScope,nSize  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISSTRING(2) ) {
		/* We must get cStr before we change the vm->pActiveMem */
		cStr = SIMPLE_API_GETSTRING(2) ;
		nScope = (int) SIMPLE_API_GETNUMBER(1) ;
		pActiveMem = vm->pActiveMem ;
		vm->pActiveMem = simple_list_getlist(vm->pMem,nScope) ;
		vm->nActiveScopeID++ ;
		nSize = vm->pMem->nSize ;
		vm->pMem->nSize = nScope ;
		vm->nEvalInScope++ ;
		/* Save State */
		pState = simple_list_new_gc(((VM *) pPointer)->pSimpleState,0);
		simple_vm_savestate2(vm,pState);
		simple_vm_runcode(vm,cStr);
		/* Restore State */
		simple_vm_restorestate2(vm,pState,1);
		simple_list_delete_gc(((VM *) pPointer)->pSimpleState,pState);
		vm->nEvalInScope-- ;
		vm->pMem->nSize = nSize ;
		vm->pActiveMem = pActiveMem ;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_ringvmpasserror ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	vm->lPassError = 1 ;
}

void simple_vm_refmeta_ringvmhideerrormsg ( void *pPointer )
{
	VM *vm  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		vm->lHideErrorMsg = (int) SIMPLE_API_GETNUMBER(1) ;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_refmeta_ringvmcallfunc ( void *pPointer )
{
	VM *vm  ;
	String *pString  ;
	vm = (VM *) pPointer ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		/* We create a string, because the current scope will be deleted by simple_vm_callfunc() */
		pString = simple_string_new_gc(((VM *) pPointer)->pSimpleState,SIMPLE_API_GETSTRING(1));
		simple_vm_callfunction(vm,simple_string_get(pString));
		simple_string_delete_gc(((VM *) pPointer)->pSimpleState,pString);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
