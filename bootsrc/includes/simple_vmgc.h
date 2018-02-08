
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


#ifndef simple_gc_h
#define simple_gc_h
/* Functions */

void simple_vm_gc_checkreferences ( VM *vm ) ;

void simple_vm_gc_checknewreference ( void *pPointer,int nType ) ;

void simple_vm_gc_checkupdatereference ( List *pList ) ;

void simple_vm_gc_deleteitem ( Item *pItem ) ;

void simple_vm_gc_killreference ( VM *vm ) ;

void simple_vm_gc_deletetemplists ( VM *vm ) ;

void simple_vm_gc_newitemreference ( Item *pItem ) ;
/* Memory Functions (General) */

SIMPLE_API void * simple_malloc ( size_t size ) ;

SIMPLE_API void simple_free ( void *ptr ) ;

SIMPLE_API void * simple_calloc ( size_t nitems, size_t size ) ;

SIMPLE_API void * simple_realloc ( void *ptr, size_t size ) ;
/* Memory Functions (Simple StateAware) */

SIMPLE_API void * simple_state_malloc ( void *pState,size_t size ) ;

SIMPLE_API void simple_state_free ( void *pState,void *pMemory ) ;

SIMPLE_API void * simple_state_calloc ( void *pState,size_t nitems, size_t size ) ;

SIMPLE_API void * simple_state_realloc ( void *pState,void *ptr, size_t size ) ;

void simple_vm_gc_deleteitem_gc ( void *pState,Item *pItem ) ;
/* Macro */
#define simple_vm_gc_cleardata(pItem) (pItem->gc.nReferenceCount = 0)
#define GCLog 0
/* Pool Manager Functions */

void simple_poolmanager_newblock ( SimpleState *sState ) ;

void * simple_poolmanager_allocate ( SimpleState *sState,size_t size ) ;

void simple_poolmanager_free ( SimpleState *sState,void *pMemory ) ;

void simple_poolmanager_delete ( SimpleState *sState ) ;
#endif
