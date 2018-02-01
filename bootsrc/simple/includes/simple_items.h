/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_items_h
#define simple_items_h
/* Data */
typedef struct Items {
	struct Item *pValue  ;
	struct Items *pNext  ;
	struct Items *pPrev  ;
} Items ;
/* Functions */

Items * simple_items_new_gc ( void *pState ) ;

Items * simple_items_delete_gc ( void *pState,Items *pItems ) ;

void simple_items_print ( Items *pItems ) ;
/* Functions without State pointer */

Items * simple_items_new ( void ) ;

Items * simple_items_delete ( Items *pItems ) ;
#endif
