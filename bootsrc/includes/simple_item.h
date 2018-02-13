
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


#ifndef simple_item_h
#define simple_item_h
/* Data */
typedef struct Item {
	/* Item Type */
	unsigned int nType:3  ;
	/* The number type, 0 = Nothing , 1 = int , 2 = double */
	unsigned int NumberFlag:2  ;
	/*
	**  what is the type of the object that the pointer refer to 
	**  Used when putting the item in the stack to refer to list or listitem 
	*/
	unsigned int nObjectType:2  ;
	/* Data */
	union {
		struct String *pString  ;
		double dNumber  ;
		int iNumber  ;
		void *pointer  ;
		struct List *list  ;
		void (*pFunc)(void *) ;
	} data ;
	/* Garbage Collector Data (Reference Counting) */
	GCData gc  ;
} Item ;
/* Constants */
#define ITEMTYPE_NOTHING 0
#define ITEMTYPE_STRING 1
#define ITEMTYPE_NUMBER 2
#define ITEMTYPE_POINTER 3
#define ITEMTYPE_LIST 4
#define ITEMTYPE_BLOCKPOINTER 5
#define ITEM_NUMBERFLAG_NOTHING 0
#define ITEM_NUMBERFLAG_INT 1
#define ITEM_NUMBERFLAG_DOUBLE 2
/* Functions */

SIMPLE_API Item * simple_item_new_gc ( void *pState,int ItemType ) ;

SIMPLE_API Item * simple_item_delete_gc ( void *pState,Item *pItem ) ;

SIMPLE_API void simple_item_settype_gc ( void *pState,Item *pItem,int ItemType ) ;

SIMPLE_API void simple_item_print ( Item *pItem ) ;

SIMPLE_API void simple_item_content_delete_gc ( void *pState,Item *pItem ) ;
/*
**  Functions to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint_gc ( void *pState,Item list[], int index ,int number ) ;
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer_gc ( void *pState,Item list[], int index ,void *pValue ) ;
/* double */

SIMPLE_API void simple_itemarray_setdouble_gc ( void *pState,Item list[], int index ,double number ) ;
/* String */

SIMPLE_API void simple_itemarray_setstsimple_gc ( void *pState,Item list[], int index ,const char *str ) ;

SIMPLE_API void simple_itemarray_setstring2_gc ( void *pState,Item list[], int index ,const char *str,int nStrSize ) ;
/* Functions to deal with one item */

SIMPLE_API void simple_item_setstsimple_gc ( void *pState,Item *pItem,const char *cStr ) ;

SIMPLE_API void simple_item_setdouble_gc ( void *pState,Item *pItem,double x ) ;

SIMPLE_API void simple_item_setpointer_gc ( void *pState,Item *pItem,void *pValue ) ;

SIMPLE_API void simple_item_setint_gc ( void *pState,Item *pItem,int x ) ;

SIMPLE_API void simple_item_setstring2_gc ( void *pState,Item *pItem,const char *cStr,int nStrSize ) ;
/* Macro */
#define simple_item_getstring(x) x->data.pString
#define simple_item_getnumber(x) x->data.dNumber
#define simple_item_getdouble(x) x->data.dNumber
#define simple_item_getint(x) x->data.iNumber
#define simple_item_getlist(x) x->data.list
#define simple_item_getpointer(x) x->data.pointer
#define simple_item_gettype(x) x->nType
#define simple_itemarray_getint(list,index) ( list[index].data.iNumber )
#define simple_itemarray_getpointer(list,index) ( list[index].data.pointer )
#define simple_itemarray_getdouble(list,index) list[index].data.dNumber
#define simple_itemarray_getstring(list,index) simple_string_get(list[index].data.pString )
#define simple_itemarray_getstringsize(list,index) simple_string_size(list[index].data.pString )
/* Check */
#define simple_itemarray_isstring(list,index) (list[index].nType == ITEMTYPE_STRING)
#define simple_itemarray_isnumber(list,index) (list[index].nType == ITEMTYPE_NUMBER)
#define simple_itemarray_ispointer(list,index) (list[index].nType == ITEMTYPE_POINTER)
#define simple_item_isstring(x) (x->nType == ITEMTYPE_STRING)
#define simple_item_islist(x) (x->nType == ITEMTYPE_LIST)
#define simple_item_isdouble(x) ( (x->nType == ITEMTYPE_NUMBER) && ( x->NumberFlag == ITEM_NUMBERFLAG_DOUBLE ) )
/* Functions without state pointer */

SIMPLE_API Item * simple_item_new ( int ItemType ) ;

SIMPLE_API Item * simple_item_delete ( Item *pItem ) ;

SIMPLE_API void simple_item_settype ( Item *pItem,int ItemType ) ;

SIMPLE_API void simple_item_content_delete ( Item *pItem ) ;
/*
**  Functions to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint ( Item list[], int index ,int number ) ;
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer ( Item list[], int index ,void *pValue ) ;
/* double */

SIMPLE_API void simple_itemarray_setdouble ( Item list[], int index ,double number ) ;
/* String */

SIMPLE_API void simple_itemarray_setstring ( Item list[], int index ,const char *str ) ;

SIMPLE_API void simple_itemarray_setstring2 ( Item list[], int index ,const char *str,int nStrSize ) ;
/* Functions to deal with one item */

SIMPLE_API void simple_item_setstring ( Item *pItem,const char *cStr ) ;

SIMPLE_API void simple_item_setdouble ( Item *pItem,double x ) ;

SIMPLE_API void simple_item_setpointer ( Item *pItem,void *pValue ) ;

SIMPLE_API void simple_item_setint ( Item *pItem,int x ) ;

SIMPLE_API void simple_item_setstring2 ( Item *pItem,const char *cStr,int nStrSize ) ;

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
