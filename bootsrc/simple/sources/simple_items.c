/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"

Items * simple_items_new_gc ( void *pState )
{
	Items *pItems  ;
	pItems = (Items *) simple_state_malloc(pState,sizeof(Items));
	if ( pItems == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pItems->pValue = simple_item_new_gc(pState,ITEMTYPE_NOTHING) ;
	pItems->pNext = NULL ;
	pItems->pPrev = NULL ;
	return pItems ;
}

Items * simple_items_delete_gc ( void *pState,Items *pItems )
{
	assert(pItems != NULL);
	pItems->pValue = simple_item_delete_gc(pState,pItems->pValue);
	simple_state_free(pState,pItems);
	pItems = NULL ;
	return pItems ;
}

void simple_items_print ( Items *pItems )
{
	assert(pItems != NULL);
	simple_item_print(pItems->pValue);
}
/* Functions without State pointer */

Items * simple_items_new ( void )
{
	return simple_items_new_gc(NULL) ;
}

Items * simple_items_delete ( Items *pItems )
{
	return simple_items_delete_gc(NULL,pItems) ;
}
