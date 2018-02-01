/*
**  Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> 
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
	pItem->data.pPointer = NULL ;
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
		case ITEMTYPE_STSIMPLE :
			/* Work */
			simple_stsimple_print(pItem->data.pString);
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
			printf( "%p",pItem->data.pPointer ) ;
			break ;
		case ITEMTYPE_LIST :
			/* Work */
			simple_list_print(pItem->data.pList);
			break ;
	}
}

SIMPLE_API void simple_item_content_delete_gc ( void *pState,Item *pItem )
{
	assert(pItem != NULL);
	switch ( pItem->nType ) {
		case ITEMTYPE_STSIMPLE :
			/* Work */
			pItem->data.pString = simple_stsimple_delete_gc(pState,pItem->data.pString);
			break ;
		case ITEMTYPE_LIST :
			/* Work */
			pItem->data.pList = simple_list_delete_gc(pState,pItem->data.pList);
			break ;
	}
	/* Set Type */
	pItem->nType = ITEMTYPE_NOTHING ;
	/* Delete pointer information */
	pItem->data.pPointer = NULL ;
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
		case ITEMTYPE_STSIMPLE :
			pItem->nType = ITEMTYPE_STSIMPLE ;
			pItem->data.pString = simple_stsimple_new_gc(pState,"");
			break ;
		case ITEMTYPE_NUMBER :
			pItem->nType = ITEMTYPE_NUMBER ;
			pItem->data.dNumber = 0 ;
			pItem->data.iNumber = 0 ;
			break ;
		case ITEMTYPE_POINTER :
			pItem->nType = ITEMTYPE_POINTER ;
			pItem->data.pPointer = NULL ;
			pItem->nObjectType = 0 ;
			break ;
		case ITEMTYPE_LIST :
			pItem->nType = ITEMTYPE_LIST ;
			pItem->data.pList = simple_list_new_gc(pState,0);
			break ;
		case ITEMTYPE_FUNCPOINTER :
			pItem->nType = ITEMTYPE_FUNCPOINTER ;
			pItem->data.pFunc = NULL ;
			break ;
	}
}
/*
**  Functions to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint_gc ( void *pState,Item pList[], int index ,int number )
{
	simple_item_settype_gc(pState,&pList[index],ITEMTYPE_NUMBER);
	pList[index].data.iNumber = number ;
	pList[index].NumberFlag = ITEM_NUMBERFLAG_INT ;
}
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer_gc ( void *pState,Item pList[], int index ,void *pValue )
{
	simple_item_settype_gc(pState,&pList[index],ITEMTYPE_POINTER);
	pList[index].data.pPointer = pValue ;
	pList[index].nObjectType = 0 ;
}
/* double */

SIMPLE_API void simple_itemarray_setdouble_gc ( void *pState,Item pList[], int index ,double number )
{
	simple_item_settype_gc(pState,&pList[index],ITEMTYPE_NUMBER);
	pList[index].data.dNumber = number ;
	pList[index].NumberFlag = ITEM_NUMBERFLAG_DOUBLE ;
}
#define simple_list_getint(pList,index) ( simple_list_getitem(pList,index)->data.iNumber )
#define simple_list_getpointer(pList,index) ( simple_list_getitem(pList,index)->data.pPointer )
#define simple_list_getfuncpointer(pList,index) ( simple_list_getitem(pList,index)->data.pFunc )
#define simple_list_callfuncpointer(pList,index,x) ( simple_list_getitem(pList,index)->data.pFunc(x) )
#define simple_list_getdouble(pList,index) simple_list_getitem(pList,index)->data.dNumber
#define simple_list_getstring(pList,index) ( simple_stsimple_get(simple_item_getstring(simple_list_getitem(pList,index))) )
#define simple_list_getstringobject(pList,index) ( simple_item_getstring(simple_list_getitem(pList,index)) )
#define simple_list_getstringsize(pList,index) ( simple_stsimple_size(simple_item_getstring(simple_list_getitem(pList,index))) )
/* String */

SIMPLE_API void simple_itemarray_setstsimple_gc ( void *pState,Item pList[], int index ,const char *str )
{
	simple_item_settype_gc(pState,&pList[index],ITEMTYPE_STSIMPLE);
	simple_stsimple_set_gc(pState,pList[index].data.pString ,str);
}

SIMPLE_API void simple_itemarray_setstring2_gc ( void *pState,Item pList[], int index ,const char *str,int nStrSize )
{
	simple_item_settype_gc(pState,&pList[index],ITEMTYPE_STSIMPLE);
	simple_stsimple_set2_gc(pState,pList[index].data.pString ,str,nStrSize);
}
/* Functions to deal with one item */

SIMPLE_API void simple_item_setstsimple_gc ( void *pState,Item *pItem,const char *cStr )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STSIMPLE);
	simple_stsimple_set_gc(pState,simple_item_getstring(pItem),cStr);
}

SIMPLE_API void simple_item_setstring2_gc ( void *pState,Item *pItem,const char *cStr,int nStrSize )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STSIMPLE);
	simple_stsimple_set2_gc(pState,simple_item_getstring(pItem),cStr,nStrSize);
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
	pItem->data.pPointer = pValue ;
	pItem->nObjectType = 0 ;
}

SIMPLE_API void simple_item_setint_gc ( void *pState,Item *pItem,int x )
{
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.iNumber = x ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_INT ;
}
/* Functions without state pointer */

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
**  Functions to deal with array of items 
**  int 
*/

SIMPLE_API void simple_itemarray_setint ( Item pList[], int index ,int number )
{
	simple_itemarray_setint_gc(NULL,pList,index,number);
}
/* Pointers */

SIMPLE_API void simple_itemarray_setpointer ( Item pList[], int index ,void *pValue )
{
	simple_itemarray_setpointer_gc(NULL,pList,index,pValue);
}
/* double */

SIMPLE_API void simple_itemarray_setdouble ( Item pList[], int index ,double number )
{
	simple_itemarray_setdouble_gc(NULL,pList,index,number);
}
/* String */

SIMPLE_API void simple_itemarray_setstring ( Item pList[], int index ,const char *str )
{
	simple_itemarray_setstsimple_gc(NULL,pList,index,str);
}

SIMPLE_API void simple_itemarray_setstring2 ( Item pList[], int index ,const char *str,int nStrSize )
{
	simple_itemarray_setstring2_gc(NULL,pList,index,str,nStrSize);
}
/* Functions to deal with one item */

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
