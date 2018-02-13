
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


#ifndef simple_api_h
#define simple_api_h
/*
**  Functions 
**  Support for C Functions 
*/

SIMPLE_API void register_block_t ( SimpleState *sState,const char *cStr, void (*pFunc)(void *) ) ;

SIMPLE_API void loadcfunctions ( SimpleState *sState ) ;

SIMPLE_API List * api_get_list ( void *pointer,int x ) ;

int api_is_list ( void *pointer,int x ) ;

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

void simple_vmlib_del ( void *pointer ) ;

void simple_vmlib_clock ( void *pointer ) ;

void simple_vmlib_input ( void *pointer ) ;

void simple_vmlib_ascii ( void *pointer ) ;

void simple_vmlib_char ( void *pointer ) ;

void simple_vmlib_date ( void *pointer ) ;

void simple_vmlib_time ( void *pointer ) ;

void simple_vmlib_getchar ( void *pointer ) ;

void simple_vmlib_random ( void *pointer ) ;

void simple_vmlib_timelist ( void *pointer ) ;

void simple_vmlib_adddays ( void *pointer ) ;

void simple_vmlib_diffdays ( void *pointer ) ;

void simple_vmlib_version ( void *pointer ) ;

void simple_vmlib_clockspersecond ( void *pointer ) ;

int simple_vmlib_adddays_isleapyear ( int nYear ) ;

void simple_vmlib_swap ( void *pointer ) ;

/* Check Data Type */

void simple_vmlib_isstring ( void *pointer ) ;

void simple_vmlib_isnumber ( void *pointer ) ;

void simple_vmlib_islist ( void *pointer ) ;

void simple_vmlib_type ( void *pointer ) ;

void simple_vmlib_isnull ( void *pointer ) ;

void simple_vmlib_isobject ( void *pointer ) ;
/* Conversion */

void simple_vmlib_hex ( void *pointer ) ;

void simple_vmlib_dec ( void *pointer ) ;

void simple_vmlib_number ( void *pointer ) ;

void simple_vmlib_string ( void *pointer ) ;

void simple_vmlib_str2hex ( void *pointer ) ;

void simple_vmlib_hex2str ( void *pointer ) ;

void simple_vmlib_str2list ( void *pointer ) ;

void simple_vmlib_list2str ( void *pointer ) ;

void simple_vmlib_str2hexcstyle ( void *pointer ) ;

/* Functional */

void simple_vmlib_eval ( void *pointer ) ;
/* Error Handling */

void simple_vmlib_raise ( void *pointer ) ;

void simple_vmlib_assert ( void *pointer ) ;
/* Check Characters */

void simple_vmlib_isfunc ( void *pointer,int (*pFunc)(int) ) ;

void simple_vmlib_isalnum ( void *pointer ) ;

void simple_vmlib_isalpha ( void *pointer ) ;

void simple_vmlib_iscntrl ( void *pointer ) ;

void simple_vmlib_isdigit ( void *pointer ) ;

void simple_vmlib_isgraph ( void *pointer ) ;

void simple_vmlib_islower ( void *pointer ) ;

void simple_vmlib_isprint ( void *pointer ) ;

void simple_vmlib_ispunct ( void *pointer ) ;

void simple_vmlib_isspace ( void *pointer ) ;

void simple_vmlib_isupper ( void *pointer ) ;

void simple_vmlib_isxdigit ( void *pointer ) ;
/* Garbage Collector & Variable Pointer */

void simple_vmlib_callgc ( void *pointer ) ;

void simple_vmlib_varptr ( void *pointer ) ;

void simple_vmlib_intvalue ( void *pointer ) ;

void simple_vmlib_object2pointer ( void *pointer ) ;

void simple_vmlib_pointer2object ( void *pointer ) ;

void simple_vmlib_nullpointer ( void *pointer ) ;

void simple_vmlib_space ( void *pointer ) ;

void simple_vmlib_ptrcmp ( void *pointer ) ;
/* Simple State */

void init_simple_state_block ( void *pointer ) ;

void execute_simple_code_block ( void *pointer ) ;

void free_simple_state_block ( void *pointer ) ;

void execute_simple_file_block ( void *pointer ) ;

void find_simple_variable_block ( void *pointer ) ;

void simple_vmlib_state_newvar ( void *pointer ) ;

void simple_vmlib_state_runobjectfile ( void *pointer ) ;

void main_simple_state_block ( void *pointer ) ;

void simple_vmlib_state_setvar ( void *pointer ) ;

void simple_vmlib_state_new ( void *pointer ) ;

void simple_vmlib_state_mainfile ( void *pointer ) ;
/* Simple See and Give */

void display_string ( void *pointer ) ;

void read_string ( void *pointer ) ;
/* API For C Functions */
#define SIMPLE_API_PARALIST (((VM *) pointer)->pActiveMem)
#define SIMPLE_API_PARACOUNT (((VM *) pointer)->nCFuncParaCount)
#define SIMPLE_API_GETSTRING(x) (simple_list_getstring(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_GETNUMBER(x) (simple_list_getdouble(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_GETPOINTER(x) (simple_list_getpointer(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISSTRING(x) (simple_list_isstring(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISNUMBER(x) (simple_list_isnumber(simple_list_getlist(SIMPLE_API_PARALIST,x),3))
#define SIMPLE_API_ISPOINTER(x) (api_is_pointer((VM *) pointer,x))
#define SIMPLE_API_GETPOINTERTYPE(x) (simple_list_getint(simple_list_getlist(SIMPLE_API_PARALIST,x),4))
#define SIMPLE_API_ERROR(x) (simple_vm_error((VM *) pointer,x))
#define SIMPLE_API_ISLIST(x) (api_is_list((VM *) pointer,x))
#define SIMPLE_API_GETLIST(x) (api_get_list((VM *) pointer,x))
#define SIMPLE_API_RETNUMBER(x) ((VM *) pointer)->nSP++ ; simple_itemarray_setdouble(((VM *) pointer)->aStack, ((VM *) pointer)->nSP , x)
#define SIMPLE_API_RETSTRING(x) ((VM *) pointer)->nSP++ ; simple_itemarray_setstring(((VM *) pointer)->aStack, ((VM *) pointer)->nSP, x)
#define SIMPLE_API_RETSTRING2(x,y) ((VM *) pointer)->nSP++ ; simple_itemarray_setstring2(((VM *) pointer)->aStack, ((VM *) pointer)->nSP, x,y)
#define SIMPLE_API_RETLIST(x) api_ret_list((VM *) pointer,x)
#define SIMPLE_API_NEWLIST api_new_list((VM *) pointer)
#define SIMPLE_API_RETCPOINTER(x,y) (api_ret_cpointer((VM *) pointer,(void *) x,y))
#define SIMPLE_API_GETCPOINTER(x,y) (api_get_cpointer((VM *) pointer,x,y))
#define SIMPLE_API_PUSHPVALUE(x) ((VM *) pointer)->nSP++ ; simple_itemarray_setpointer(((VM *) pointer)->aStack, ((VM *) pointer)->nSP , x )
#define SIMPLE_API_OBJTYPE ((VM *) pointer)->aStack[((VM *) pointer)->nSP].nObjectType
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
#define SIMPLE_API_MISS1PARA "Bad parameters count, the function expect one parameter"
#define SIMPLE_API_MISS2PARA "Bad parameters count, the function expect two parameters"
#define SIMPLE_API_MISS3PARA "Bad parameters count, the function expect three parameters"
#define SIMPLE_API_MISS4PARA "Bad parameters count, the function expect four parameters"
#define SIMPLE_API_BADPARATYPE "Bad parameter type!"
#define SIMPLE_API_BADPARACOUNT "Bad parameters count!"
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
