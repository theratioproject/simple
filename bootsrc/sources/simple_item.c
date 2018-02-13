
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

/*
**  Header Files 
*/
#include "../includes/simple.h"

SIMPLE_API Item * simple_item_new_gc ( void *pState,int ItemType )
{
	Item *pItem  ;
	pItem = (Item *) simple_state_malloc(pState,sizeof(Item));
	if ( pItem == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Set Type */
	pItem->nType = ITEMTYPE_NOTHING ;
	/* Delete pointer information */
	pItem->data.pointer = NULL ;
	pItem->nObjectType = 0 ;
	/* Delete number information */
	pItem->data.dNumber = 0 ;
	pItem->data.iNumber = 0 ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_NOTHING ;
	/* Reference Count */
	simple_vm_gc_cleardata(pItem);
	simple_item_settype_gc(pState,pItem,ItemType);
	return pItem ;
}

SIMPLE_API Item * simple_item_delete_gc ( void *pState,Item *pItem )
{
	assert(pItem != NULL);
	simple_vm_gc_deleteitem_gc(pState,pItem);
	return NULL ;
}

SIMPLE_API void simple_item_print ( Item *pItem )
{
	int ItemType  ;
	assert(pItem != NULL);
	ItemType = pItem->nType ;
	switch ( ItemType ) {
		case ITEMTYPE_NOTHING :
			/* Work */
			break ;
		case ITEMTYPE_STRING :
			/* Work */
			simple_string_print(pItem->data.pString);
			break ;
		case ITEMTYPE_NUMBER :
			/* Work */
			if ( pItem->NumberFlag == ITEM_NUMBERFLAG_INT ) {
				printf( "%d\n ",pItem->data.iNumber ) ;
			} else {
				printf( "%f \n",pItem->data.dNumber ) ;
			}
			break ;
		case ITEMTYPE_POINTER :
			/* Work */
			printf( "%p",pItem->data.pointer ) ;
			break ;
		case ITEMTYPE_LIST :
			/* Work */
			simple_list_print(pItem->data.list);
			break ;
	}
}

SIMPLE_API void simple_item_content_delete_gc ( void *pState,Item *pItem )
{
	assert(pItem != NULL);
	switch ( pItem->nType ) {
		case ITEMTYPE_STRING :
			/* Work */
			pItem->data.pString = simple_string_delete_gc(pState,pItem->data.pString);
			break ;
		case ITEMTYPE_LIST :
			/* Work */
			pItem->data.list = simple_list_delete_gc(pState,pItem->data.list);
			break ;
	}
	/* Set Type */
	pItem->nType = ITEMTYPE_NOTHING ;
	/* Delete pointer information */
	pItem->data.pointer = NULL ;
	pItem->nObjectType = 0 ;
	/* Delete number information */
	pItem->data.dNumber = 0 ;
	pItem->data.iNumber = 0 ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_NOTHING ;
}

SIMPLE_API void simple_item_settype_gc ( void *pState,Item *pItem,int ItemType )
{
	assert(pItem != NULL);
	/* When we set the type we remove the current content at first */
	simple_item_content_delete_gc(pState,pItem);
	switch ( ItemType ) {
		case ITEMTYPE_NOTHING :
			pItem->nType = ITEMTYPE_NOTHING ;
			break ;
		case ITEMTYPE_STRING :
			pItem->nType = ITEMTYPE_STRING ;
			pItem->data.pString = simple_string_new_gc(pState,"");
			break ;
		case ITEMTYPE_NUMBER :
			pItem->nType = ITEMTYPE_NUMBER ;
			pItem->data.dNumber = 0 ;
			pItem->data.iNumber = 0 ;
			break ;
		case ITEMTYPE_POINTER :
			pItem->nType = ITEMTYPE_POINTER ;
			pItem->data.pointer = NULL ;
			pItem->nObjectType = 0 ;
			break ;
		case ITEMTYPE_LIST :
			pItem->nType = ITEMTYPE_LIST ;
			pItem->data.list = simple_list_new_gc(pState,0);
			break ;
		case ITEMTYPE_BLOCKPOINTER :
			pItem->nType = ITEMTYPE_BLOCKPOINTER ;
			pItem->data.pBlock = NULL ;
			break ;
	}
}
/*
**  Blocks to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint_gc ( void *pState,Item list[], int index ,int number )
{
	simple_item_settype_gc(pState,&list[index],ITEMTYPE_NUMBER);
	list[index].data.iNumber = number ;
	list[index].NumberFlag = ITEM_NUMBERFLAG_INT ;
}
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer_gc ( void *pState,Item list[], int index ,void *pValue )
{
	simple_item_settype_gc(pState,&list[index],ITEMTYPE_POINTER);
	list[index].data.pointer = pValue ;
	list[index].nObjectType = 0 ;
}
/* double */

SIMPLE_API void simple_itemarray_setdouble_gc ( void *pState,Item list[], int index ,double number )
{
	simple_item_settype_gc(pState,&list[index],ITEMTYPE_NUMBER);
	list[index].data.dNumber = number ;
	list[index].NumberFlag = ITEM_NUMBERFLAG_DOUBLE ;
}
#define simple_list_getint(list,index) ( simple_list_getitem(list,index)->data.iNumber )
#define simple_list_getpointer(list,index) ( simple_list_getitem(list,index)->data.pointer )
#define simple_list_getblockpointer(list,index) ( simple_list_getitem(list,index)->data.pBlock )
#define simple_list_callblockpointer(list,index,x) ( simple_list_getitem(list,index)->data.pBlock(x) )
#define simple_list_getdouble(list,index) simple_list_getitem(list,index)->data.dNumber
#define simple_list_getstring(list,index) ( simple_string_get(simple_item_getstring(simple_list_getitem(list,index))) )
#define simple_list_getstringobject(list,index) ( simple_item_getstring(simple_list_getitem(list,index)) )
#define simple_list_getstringsize(list,index) ( simple_string_size(simple_item_getstring(simple_list_getitem(list,index))) )
/* String */

SIMPLE_API void simple_itemarray_setstsimple_gc ( void *pState,Item list[], int index ,const char *str )
{
	simple_item_settype_gc(pState,&list[index],ITEMTYPE_STRING);
	simple_string_set_gc(pState,list[index].data.pString ,str);
}

SIMPLE_API void simple_itemarray_setstring2_gc ( void *pState,Item list[], int index ,const char *str,int nStrSize )
{
	simple_item_settype_gc(pState,&list[index],ITEMTYPE_STRING);
	simple_string_set2_gc(pState,list[index].data.pString ,str,nStrSize);
}
/* Blocks to deal with one item */

SIMPLE_API void simple_item_setstsimple_gc ( void *pState,Item *pItem,const char *cStr )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	simple_string_set_gc(pState,simple_item_getstring(pItem),cStr);
}

SIMPLE_API void simple_item_setstring2_gc ( void *pState,Item *pItem,const char *cStr,int nStrSize )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	simple_string_set2_gc(pState,simple_item_getstring(pItem),cStr,nStrSize);
}

SIMPLE_API void simple_item_setdouble_gc ( void *pState,Item *pItem,double x )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.dNumber = x ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_DOUBLE ;
}

SIMPLE_API void simple_item_setpointer_gc ( void *pState,Item *pItem,void *pValue )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_POINTER);
	pItem->data.pointer = pValue ;
	pItem->nObjectType = 0 ;
}

SIMPLE_API void simple_item_setint_gc ( void *pState,Item *pItem,int x )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.iNumber = x ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_INT ;
}
/* Blocks without state pointer */

SIMPLE_API Item * simple_item_new ( int ItemType )
{
	return simple_item_new_gc(NULL,ItemType) ;
}

SIMPLE_API Item * simple_item_delete ( Item *pItem )
{
	return simple_item_delete_gc(NULL,pItem) ;
}

SIMPLE_API void simple_item_settype ( Item *pItem,int ItemType )
{
	simple_item_settype_gc(NULL,pItem,ItemType);
}

SIMPLE_API void simple_item_content_delete ( Item *pItem )
{
	simple_item_content_delete_gc(NULL,pItem);
}
/*
**  Blocks to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint ( Item list[], int index ,int number )
{
	simple_itemarray_setint_gc(NULL,list,index,number);
}
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer ( Item list[], int index ,void *pValue )
{
	simple_itemarray_setpointer_gc(NULL,list,index,pValue);
}
/* double */

SIMPLE_API void simple_itemarray_setdouble ( Item list[], int index ,double number )
{
	simple_itemarray_setdouble_gc(NULL,list,index,number);
}
/* String */

SIMPLE_API void simple_itemarray_setstring ( Item list[], int index ,const char *str )
{
	simple_itemarray_setstsimple_gc(NULL,list,index,str);
}

SIMPLE_API void simple_itemarray_setstring2 ( Item list[], int index ,const char *str,int nStrSize )
{
	simple_itemarray_setstring2_gc(NULL,list,index,str,nStrSize);
}
/* Blocks to deal with one item */

SIMPLE_API void simple_item_setstring ( Item *pItem,const char *cStr )
{
	simple_item_setstsimple_gc(NULL,pItem,cStr);
}

SIMPLE_API void simple_item_setdouble ( Item *pItem,double x )
{
	simple_item_setdouble_gc(NULL,pItem,x);
}

SIMPLE_API void simple_item_setpointer ( Item *pItem,void *pValue )
{
	simple_item_setpointer_gc(NULL,pItem,pValue);
}

SIMPLE_API void simple_item_setint ( Item *pItem,int x )
{
	simple_item_setint_gc(NULL,pItem,x);
}

SIMPLE_API void simple_item_setstring2 ( Item *pItem,const char *cStr,int nStrSize )
{
	simple_item_setstring2_gc(NULL,pItem,cStr,nStrSize);
}

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
/* Blocks without State pointer */

Items * simple_items_new ( void )
{
	return simple_items_new_gc(NULL) ;
}

Items * simple_items_delete ( Items *pItems )
{
	return simple_items_delete_gc(NULL,pItems) ;
}

