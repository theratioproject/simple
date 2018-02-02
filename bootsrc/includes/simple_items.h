
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
