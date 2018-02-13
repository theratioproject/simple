
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
#include "../includes/simple_vmdll.h"
/* Blocks */

void simple_vm_dll_loadblocks ( SimpleState *sState )
{
	register_block("callDynamicModule",simple_vm_dll_loadlib);
	register_block("closeDynamicModule",simple_vm_dll_closelib);
}

void simple_vm_dll_loadlib ( void *pointer )
{
    LpHandleType handle  ;
    const char *cDLL  ;
    loadlibblockptr pBlock  ;
    VM *vm  ;
    SimpleState *sState  ;
    vm = (VM *) pointer ;
    sState = vm->sState ;
    char library_path[200]  ;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISSTRING(1) ) {
        if (simple_fexists(SIMPLE_API_GETSTRING(1))) {
            strcpy(library_path,SIMPLE_API_GETSTRING(1));
        } else {
            char* SIMPLEPATH = getenv("SIMPLE_PATH"); 
            if (SIMPLEPATH != NULL) {
                snprintf(library_path, sizeof(library_path), "%s/simple%s/modules/dynamic_modules/%s", SIMPLEPATH, SIMPLE_VERSION, SIMPLE_API_GETSTRING(1));
            }
            if (!simple_fexists(library_path)) {
                char* SIMPLEMODULEPATH = getenv("SIMPLE_MODULE_PATH"); 
                if (SIMPLEMODULEPATH != NULL) {
                    snprintf(library_path, sizeof(library_path), "%s/%s", SIMPLEMODULEPATH, SIMPLE_API_GETSTRING(1));
                }
                if (!simple_fexists(library_path)) {
                    snprintf(library_path, sizeof(library_path), "%s%s", DEFAULT_FILE_PATH, SIMPLE_API_GETSTRING(1));
                    if (!simple_fexists(library_path)) {
                        snprintf(library_path, sizeof(library_path), "%s/modules/%s", DEFAULT_FILE_PATH, SIMPLE_API_GETSTRING(1));
                        if (!simple_fexists(library_path)) {
                            snprintf(library_path, sizeof(library_path), "%s/library/%s", DEFAULT_FILE_PATH, SIMPLE_API_GETSTRING(1));
                            if (!simple_fexists(library_path)) {
                                //already checked all assumed folders
                            }
                        }

                    }
                }
            } 
        }
        cDLL = library_path;
        handle = LoadDLL(cDLL);
        if ( handle == NULL ) {
                printf( "\nLibrary File : %s",SIMPLE_API_GETSTRING(1) ) ;
                SIMPLE_API_ERROR(SIMPLE_VM_ERROR_LIBLOADERROR);
                return ;
        }
        pBlock = (loadlibblockptr) GetDLLBlock(handle, "init_simple_module") ;
        if ( pBlock == NULL ) {
                printf( "\nLibrary File : %s", file_real_name(SIMPLE_API_GETSTRING(1)) ) ;
                SIMPLE_API_ERROR("The dynamic library doesn't contain the init_simple_module() block!");
                return ;
        }
        simple_list_deletearray_gc(sState,sState->c_blocks);
        (*pBlock)(sState) ;
        simple_list_genarray_gc(sState,sState->c_blocks);
        simple_list_genhashtable2_gc(sState,sState->c_blocks);
        SIMPLE_API_RETCPOINTER(handle,"DLL");
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
		handle = SIMPLE_API_GETCPOINTER(1,"DLL") ;
		CloseDLL(handle);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/* User Interface - Commands Implementation (Faster) - Because we don't have blocks call */

void simple_vm_display ( VM *vm )
{
	Item *pItem  ;
	char cStr[100]  ;
	List *list  ;
	char *cString  ;
	int x  ;
	if ( vm->nBlockExecute > 0 ) {
		vm->nBlockExecute-- ;
	}
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		cString = SIMPLE_VM_STACK_READC ;
		if ( strlen(cString) != (unsigned int) SIMPLE_VM_STACK_STRINGSIZE ) {
			for ( x = 0 ; x < SIMPLE_VM_STACK_STRINGSIZE ; x++ ) {
				printf( "%c",cString[x] ) ;
			}
		} else {
			printf( "%s",cString ) ;
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
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		simple_vm_numtostring(vm,SIMPLE_VM_STACK_READN,cStr);
		printf( "%s",cStr ) ;
	}
	SIMPLE_VM_STACK_POP ;
	simple_vm_freestack(vm);
	fflush(stdout);
}

void simple_vm_read ( VM *vm )
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
			simple_list_setstsimple_gc(vm->sState,var, SIMPLE_VAR_VALUE, cLine);
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
	char *cString  ;
	int x  ;
	char cStr[100]  ;
	List *list  ;
	VM *vm  ;
	vm = (VM *) pointer ;
	if ( SIMPLE_API_ISSTRING(1) ) {
		cString = SIMPLE_API_GETSTRING(1) ;
		if ( strlen(cString) != (unsigned int) SIMPLE_API_GETSTRINGSIZE(1) ) {
			for ( x = 0 ; x < SIMPLE_API_GETSTRINGSIZE(1) ; x++ ) {
				printf( "%c",cString[x] ) ;
			}
		} else {
			printf( "%s",cString ) ;
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


