/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"

void simple_vm_gc_checkreferences ( VM *vm )
{
	int x  ;
	List *list, *list2  ;
	Item *pItem  ;
	/* Check References (Called when we delete a scope) */
	list = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem));
	for ( x = simple_list_getsize(list) ; x >= 1 ; x-- ) {
		list2 = simple_list_getlist(list,x);
		if ( simple_list_getsize(list2) == SIMPLE_VAR_LISTSIZE ) {
			if ( simple_list_getint(list2,SIMPLE_VAR_TYPE) == SIMPLE_VM_POINTER ) {
				if ( simple_list_getint(list2,SIMPLE_VAR_PVALUETYPE) == SIMPLE_OBJTYPE_LISTITEM ) {
					pItem = (Item *) simple_list_getpointer(list2,SIMPLE_VAR_VALUE) ;
					#if GCLog
					printf( "GC CheckReferences - Free Memory %p \n",pItem ) ;
					#endif
					simple_item_delete(pItem);
				}
			}
		}
	}
}

void simple_vm_gc_checknewreference ( void *pointer,int nType )
{
	Item *pItem  ;
	/*
	**  Called when we create new pointer (new reference) 
	**  The reference may be to a list or a sublist (list item) 
	**  We care only about list items (sublists) 
	*/
	if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) pointer ;
		pItem->gc.nReferenceCount++ ;
		#if GCLog
		printf( "\nGC CheckNewReference - To Pointer %p \n",pItem ) ;
		#endif
	}
}

void simple_vm_gc_checkupdatereference ( List *list )
{
	Item *pItem  ;
	/* Reference Counting to Destination before copy from Source */
	if ( simple_list_getint(list,SIMPLE_VAR_TYPE) == SIMPLE_VM_POINTER ) {
		if ( simple_list_getint(list,SIMPLE_VAR_PVALUETYPE) == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) simple_list_getpointer(list,SIMPLE_VAR_VALUE) ;
			simple_item_delete(pItem);
		}
	}
}

void simple_vm_gc_deleteitem_gc ( void *pState,Item *pItem )
{
	if ( pItem->gc.nReferenceCount == 0 ) {
		#if GCLog
		printf( "GC Delete Item - Free Memory %p \n",pItem ) ;
		#endif
		simple_item_content_delete(pItem);
		simple_state_free(pState,pItem);
	}
	else {
		pItem->gc.nReferenceCount-- ;
	}
}

void simple_vm_gc_killreference ( VM *vm )
{
	List *list  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		simple_vm_gc_checkupdatereference(list);
	}
}

void simple_vm_gc_deletetemlists ( VM *vm )
{
	int x  ;
	List *pScope,*list  ;
	/* If we are in the class region (After class name) then return */
	if ( vm->nInClassRegion ) {
		return ;
	}
	/*
	**  This block is called from Simple code by callgc() 
	**  Block Goal 
	**  When we return Lists/Pointers from blocks we create variable called simple_sys_temp 
	**  This variable is created in the previous scope instead of the active block scope 
	**  This is necessary because the block scope will be deleted and we need the varaible 
	**  This is important because we may assign the variable to variable name 
	**  The problem happens when we have a loop that uses f1(f2()) 
	**  and f2() return a lists/pointer 
	**  The temp list/C Pointer will not be deleted until the end of the block 
	**  But we have a loop and this will lead to a memory leak during loop execution 
	**  When testing al_map_rgb() in Allegro Library this problem becomes critical 
	**  This block solves this problem, by deleting temp lists/C Pointers in the current scope 
	**  We use -1 to skip the currect scope of the Simple block (callgc()) 
	*/
	pScope = simple_list_getlist(vm->pMem,simple_list_getsize(vm->pMem)-1) ;
	/* The block works only when we expect to have temp variables */
	if ( simple_list_getsize(pScope) >= 1 ) {
		for ( x = simple_list_getsize(pScope) ; x >= 1 ; x-- ) {
			list = simple_list_getlist(pScope,x);
			if ( simple_list_getsize(list) != SIMPLE_VAR_LISTSIZE ) {
				continue ;
			}
			if ( strcmp(simple_list_getstring(list,SIMPLE_VAR_NAME),SIMPLE_TEMP_VARIABLE) == 0 ) {
				simple_list_deleteitem(pScope,x);
			}
			else if ( strcmp(simple_list_getstring(list,SIMPLE_VAR_NAME),SIMPLE_TEMP_OBJECT) == 0 ) {
				simple_list_deleteitem(pScope,x);
			}
		}
	}
	/* Delete The HashTable */
	pScope->pHashTable = simple_hashtable_delete(pScope->pHashTable) ;
	simple_list_genhashtable2(pScope);
}

void simple_vm_gc_newitemreference ( Item *pItem )
{
	pItem->gc.nReferenceCount++ ;
}
/* Memory Blocks (General) */

SIMPLE_API void * simple_malloc ( size_t size )
{
	return malloc(size) ;
}

SIMPLE_API void simple_free ( void *ptr )
{
	free( ptr ) ;
}

SIMPLE_API void * simple_calloc ( size_t nitems, size_t size )
{
	return calloc(nitems,size) ;
}

SIMPLE_API void * simple_realloc ( void *ptr, size_t size )
{
	return realloc(ptr,size) ;
}
/* Memory Blocks (SimpleState Aware) */

SIMPLE_API void * simple_state_malloc ( void *pState,size_t size )
{
	#if SIMPLE_USEPOOLMANAGER
	if ( pState != NULL ) {
		if ( ((SimpleState *) pState )->vm  != NULL ) {
			if ( size <= SIMPLE_POOLMANAGER_ITEMSIZE ) {
				return simple_poolmanager_allocate( (SimpleState *) pState,size) ;
			}
		}
	}
	#endif
	return simple_malloc(size) ;
}

SIMPLE_API void simple_state_free ( void *pState,void *pMemory )
{
	#if SIMPLE_USEPOOLMANAGER
	/* Use Pool Manager */
	simple_poolmanager_free((SimpleState *) pState,pMemory);
	#else
	simple_free(pMemory);
	#endif
}

SIMPLE_API void * simple_state_calloc ( void *pState,size_t nitems, size_t size )
{
	return simple_calloc(nitems,size) ;
}

SIMPLE_API void * simple_state_realloc ( void *pState,void *ptr, size_t size )
{
	return simple_realloc(ptr,size) ;
}

void simple_vm_gc_deleteitem ( Item *pItem )
{
	simple_vm_gc_deleteitem_gc(NULL,pItem);
}
/* Pool Manager Blocks */

void simple_poolmanager_newblock ( SimpleState *sState )
{
	PoolData *pMemory  ;
	int x  ;
	/* Get Block Memory */
	pMemory = (PoolData *) simple_malloc(sizeof(PoolData)*SIMPLE_POOLMANAGER_ITEMSINBLOCK);
	/* Check Memory */
	if ( pMemory == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Set Linked Lists (pNext values) */
	for ( x = 0 ; x < SIMPLE_POOLMANAGER_ITEMSINBLOCK - 2 ; x++ ) {
		pMemory[x].pNext = pMemory+x+1 ;
	}
	pMemory[SIMPLE_POOLMANAGER_ITEMSINBLOCK-1].pNext = NULL ;
	/*
	**  Set Values in Simple State 
	**  Set First Item in Simple State 
	*/
	sState->vPoolManager.pCurrentItem = pMemory+1 ;
	/* Set Block Start and End */
	sState->vPoolManager.pBlockStart = (void *) pMemory ;
	sState->vPoolManager.pBlockEnd = (void *) (pMemory + SIMPLE_POOLMANAGER_ITEMSINBLOCK - 1) ;
}

void * simple_poolmanager_allocate ( SimpleState *sState,size_t size )
{
	void *pMemory  ;
	pMemory = NULL ;
	/* If No memory - Create new block */
	if ( (sState->vPoolManager.pCurrentItem == NULL) && (sState->vPoolManager.pBlockStart == NULL) ) {
		simple_poolmanager_newblock(sState);
	}
	/* Get Item from the Pool Manager */
	if ( sState->vPoolManager.pCurrentItem != NULL ) {
		pMemory = sState->vPoolManager.pCurrentItem ;
		sState->vPoolManager.pCurrentItem = sState->vPoolManager.pCurrentItem->pNext ;
	}
	/* If no free items, Allocate new item */
	else {
		pMemory = simple_malloc(size);
		/* Check Memory */
		if ( pMemory == NULL ) {
			printf( SIMPLE_OOM ) ;
			exit(0);
		}
	}
	return pMemory ;
}

void simple_poolmanager_free ( SimpleState *sState,void *pMemory )
{
	PoolData *pPoolData  ;
	if ( sState != NULL ) {
		if ( sState->vPoolManager.pBlockStart != NULL ) {
			if ( (pMemory > sState->vPoolManager.pBlockStart) && (pMemory <= sState->vPoolManager.pBlockEnd ) ) {
				pPoolData = (PoolData *) pMemory ;
				pPoolData->pNext = sState->vPoolManager.pCurrentItem ;
				sState->vPoolManager.pCurrentItem = pPoolData ;
				return ;
			}
		}
	}
	simple_free(pMemory);
}

void simple_poolmanager_delete ( SimpleState *sState )
{
	if ( sState != NULL ) {
		if ( sState->vPoolManager.pBlockStart != NULL ) {
			free( sState->vPoolManager.pBlockStart ) ;
		}
	}
}
