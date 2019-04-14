
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


#ifndef SIMPLE_API_H
#define SIMPLE_API_H
/*
**  Functions 
**  Support for C Functions 
*/

SIMPLE_API void register_block_t ( SimpleState *sState,const char *cStr, void (*block)(void *) ) ;

SIMPLE_API void loadcblocks ( SimpleState *sState ) ;

SIMPLE_API List * api_get_list ( void *pointer,int x ) ;

SIMPLE_API int api_is_list ( void *pointer,int x ) ;

SIMPLE_API void api_ret_list ( void *pointer,List *list ) ;

SIMPLE_API List * api_new_list ( VM *vm ) ;

SIMPLE_API void api_ret_cpointer ( void *pointer,void *pGeneral,const char *cType ) ;

SIMPLE_API void * api_get_cpointer ( void *pointer,int x,const char *cType ) ;

SIMPLE_API void api_set_cpointer_null ( void *pointer,int x ) ;

SIMPLE_API void * api_var_ptr ( void *pointer,const char  *cStr,const char *cStr2 ) ;

SIMPLE_API void api_int_value ( void *pointer,const char  *cStr ) ;

SIMPLE_API void list_add_cpointer ( List *list,void *pGeneral,const char *cType ) ;

SIMPLE_API int api_iscpointer_list ( List *list ) ;

SIMPLE_API int api_is_cpointer ( void *pointer,int x ) ;

SIMPLE_API int api_is_object ( void *pointer,int x ) ;

SIMPLE_API int api_cpointer_cmp ( List *list,List *list2 ) ;

SIMPLE_API int api_is_pointer ( void *pointer,int x ) ;

SIMPLE_API void * api_get_cpointer2pointer ( void *pointer,int x,const char *cType ) ;

SIMPLE_API void list_add_cpointer_gc ( void *pState,List *list,void *pGeneral,const char *cType ) ;
/*
**  Library 
**  General 
*/

void simple_vmlib_len ( void *pointer ) ;

void simple_vmlib_add ( void *pointer ) ;

void simple_vmlib_version ( void *pointer ) ;

/* Check Data Type */

void simple_vmlib_isstring ( void *pointer ) ;

void simple_vmlib_isnumber ( void *pointer ) ;

void simple_vmlib_islist ( void *pointer ) ;

void simple_vmlib_type ( void *pointer ) ;

void simple_vmlib_isnull ( void *pointer ) ;

void simple_vmlib_isobject ( void *pointer ) ;

void simple_vmlib_ispointer ( void *pointer );

SIMPLE_API void simple_vmlib_exec ( void *pointer ) ;

void simple_vmlib_char ( void *pointer ) ;

#ifndef simple_vmdll_h
#define simple_vmdll_h
#ifdef _WIN32
#include <windows.h>
#define LoadDLL(x) LoadLibrary(x)
#define GetDLLBlock GetProcAddress
#define CloseDLL FreeLibrary
typedef HINSTANCE LpHandleType ;
#else
#include <dlfcn.h>
#define LoadDLL(x) dlopen(x, RTLD_LAZY)
#define GetDLLBlock dlsym
#define CloseDLL dlclose
typedef void * LpHandleType ;
#endif
typedef void (*loadlibblockptr)(SimpleState *) ;

void simple_vm_dll_loadblocks ( SimpleState *sState ) ;

void simple_vm_dll_calllib ( void *pointer ) ;

void simple_vm_dll_closelib ( void *pointer ) ;
#endif


/* Simple Display and Read */

void display_string ( void *pointer ) ;

void read_string ( void *pointer ) ;

/* API For C Functions */
#define SIMPLE_API_PARALIST (((VM *) pointer)->pActiveMem)
#define SIMPLE_API_PARACOUNT (((VM *) pointer)->nCBlockParaCount)
#define SIMPLE_API_GETSTRING(x) (simple_list_getstring(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_GETNUMBER(x) (simple_list_getdouble(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_GETPOINTER(x) (simple_list_getpointer(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISSTRING(x) (simple_list_isstring(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISNUMBER(x) (simple_list_isnumber(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISPOINTER(x) (api_is_pointer((VM *) pointer,x))
#define SIMPLE_API_GETPOINTERTYPE(x) (simple_list_getint(simple_list_getlist(SIMPLE_API_PARALIST,x),4))
#define SIMPLE_API_ERROR(x) (simple_vm_error((VM *) pointer,x))
#define SIMPLE_API_ERROR2(x,y) (simple_vm_error2((VM *) pointer,x,y))
#define SIMPLE_API_ISLIST(x) (api_is_list((VM *) pointer,x))
#define SIMPLE_API_GETLIST(x) (api_get_list((VM *) pointer,x))
#define SIMPLE_API_RETNUMBER(x) ((VM *) pointer)->nsp++ ; simple_itemarray_setdouble(((VM *) pointer)->aStack, ((VM *) pointer)->nsp , x)
#define SIMPLE_API_RETSTRING(x) ((VM *) pointer)->nsp++ ; simple_itemarray_setstring(((VM *) pointer)->aStack, ((VM *) pointer)->nsp, x)
#define SIMPLE_API_RETSTRING2(x,y) ((VM *) pointer)->nsp++ ; simple_itemarray_setstring2(((VM *) pointer)->aStack, ((VM *) pointer)->nsp, x,y)
#define SIMPLE_API_RETLIST(x) api_ret_list((VM *) pointer,x)
#define SIMPLE_API_NEWLIST api_new_list((VM *) pointer)
#define SIMPLE_API_RETCPOINTER(x,y) (api_ret_cpointer((VM *) pointer,(void *) x,y))
#define SIMPLE_API_GETCPOINTER(x,y) (api_get_cpointer((VM *) pointer,x,y))
#define SIMPLE_API_PUSHPVALUE(x) ((VM *) pointer)->nsp++ ; simple_itemarray_setpointer(((VM *) pointer)->aStack, ((VM *) pointer)->nsp , x )
#define SIMPLE_API_OBJTYPE ((VM *) pointer)->aStack[((VM *) pointer)->nsp].nObjectType
#define SIMPLE_BLOCK(x) void x(void *pointer)
#define SIMPLE_API_GETSTRINGSIZE(x) (simple_list_getstringsize(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_SETNULLPOINTER(x) (api_set_cpointer_null((VM *) pointer,x))
#define SIMPLE_API_GETCPOINTERSTATUS(x) simple_list_getint(SIMPLE_API_GETLIST(x),SIMPLE_CPOINTER_STATUS)
#define SIMPLE_API_ISCPOINTERNOTASSIGNED(x) (SIMPLE_API_GETCPOINTERSTATUS(x) == SIMPLE_CPOINTERSTATUS_NOTASSIGNED)
#define SIMPLE_API_VARPOINTER(x,y) (api_var_ptr(pointer,x,y))
#define SIMPLE_API_INTVALUE(x) (api_int_value(pointer,x))
#define SIMPLE_API_GETINTPOINTER(x) (int *) SIMPLE_API_VARPOINTER(SIMPLE_API_GETSTRING(x),"int")
#define SIMPLE_API_ACCEPTINTVALUE(x) SIMPLE_API_INTVALUE(SIMPLE_API_GETSTRING(x))
#define SIMPLE_API_GETDOUBLEPOINTER(x) SIMPLE_API_VARPOINTER(SIMPLE_API_GETSTRING(x),"double")
#define SIMPLE_API_IGNORECPOINTERTYPE ((VM *) pointer)->nIgnoreCPointerTypeCheck = 1
#define SIMPLE_API_ISCPOINTER(x) api_is_cpointer(pointer,x)
#define SIMPLE_API_ISOBJECT(x) api_is_object(pointer,x)
#define SIMPLE_API_GETCPOINTER2POINTER(x,y) (api_get_cpointer2pointer((VM *) pointer,x,y))

/* Constants/MACRO */
#define SIMPLE_API_MISS0PARA "Bad parameters count, the block expect no parameter"
#define SIMPLE_API_MISS1PARA "Bad parameters count, the block expect one parameter"
#define SIMPLE_API_MISS2PARA "Bad parameters count, the block expect two parameters"
#define SIMPLE_API_MISS3PARA "Bad parameters count, the block expect three parameters"
#define SIMPLE_API_MISS4PARA "Bad parameters count, the block expect four parameters"
#define SIMPLE_API_MISS5PARA "Bad parameters count, the block expect five parameters"
#define SIMPLE_API_MISS6PARA "Bad parameters count, the block expect six parameters"
#define SIMPLE_API_MISS7PARA "Bad parameters count, the block expect seven parameters"
#define SIMPLE_API_MISS8PARA "Bad parameters count, the block expect eight parameters"
#define SIMPLE_API_MISS9PARA "Bad parameters count, the block expect nine parameters"
#define SIMPLE_API_MISS10PARA "Bad parameters count, the block expect ten parameters"
#define SIMPLE_API_BADPARATYPE "Bad parameter type!"
#define SIMPLE_API_BADPARACOUNT "Invalid length of parameters!"
#define SIMPLE_API_BADPARARANGE "Bad parameters value, error in range!"
#define SIMPLE_API_NOTPOINTER "Error in parameter, not pointer!"
#define SIMPLE_API_NULLPOINTER "Error in parameter, NULL pointer!"
#define SIMPLE_API_EMPTYLIST "Bad parameter, empty list!"
#define register_block(x,y) register_block_t(sState,x,y)
/*
**  Note : The C Function Get Lists as pointers because of (List Pass by Reference) 
**  The List Maybe a Variable/ListItem or may represent Object or C Pointer inside a List 
**  C Pointer List , [ Pointer Value , Type String , Status Number 0=Not Copied 1=Copied 2= Not Assigned Yet] 
*/
#endif
