
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


#include "../includes/simple.h"
/*
**  Blocks 
**  List 
*/

SIMPLE_API List * simple_list_new_gc ( void *pState,int nSize )
{
	List *list  ;
	list = (List *) simple_state_malloc(pState,sizeof(List));
	if ( list == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	return simple_list_new2_gc(pState,list,nSize) ;
}

SIMPLE_API List * simple_list_new2_gc ( void *pState,List *list,int nSize )
{
	int x  ;
	Items *pItems,*pItemsLast  ;
	list->size = nSize ;
	if ( nSize > 0 ) {
		pItems = simple_items_new_gc(pState);
		list->pFirst = pItems ;
		pItemsLast = pItems ;
		for ( x = 2 ; x <= nSize ; x++ ) {
			pItems = simple_items_new_gc(pState);
			if ( pItems == NULL ) {
				printf( "OUT OF MEMEORY \n  " ) ;
				exit(0);
			}
			pItemsLast->pNext = pItems ;
			pItems->pPrev = pItemsLast ;
			pItemsLast = pItems ;
		}
		list->pLast = pItems ;
	} else {
		list->pFirst = NULL ;
		list->pLast = NULL ;
	}
	list->nNextItemAfterLastAccess = 0 ;
	list->pLastItemLastAccess = NULL ;
	list->pItemsArray = NULL ;
	list->pHashTable = NULL ;
	return list ;
}

SIMPLE_API List * simple_list_delete_gc ( void *pState,List *list )
{
	Items *pItems,*pItemsNext  ;
	pItems = list->pFirst ;
	pItemsNext = pItems ;
	/* Delete Items */
	while ( pItemsNext != NULL ) {
		pItemsNext = pItems->pNext ;
		simple_items_delete_gc(pState,pItems);
		pItems = pItemsNext ;
	}
	/* Free Items Array */
	simple_list_deletearray_gc(pState,list);
	/* Free HashTable */
	if ( list->pHashTable != NULL ) {
		list->pHashTable = simple_hashtable_delete_gc(pState,list->pHashTable);
	}
	simple_state_free(pState,list);
	list = NULL ;
	return list ;
}

SIMPLE_API void simple_list_copy_gc ( void *pState,List *pNewList, List *list )
{
	int x  ;
	List *pNewList2  ;
	assert(list != NULL);
	/*
	**  This block don't add a new list before copying items 
	**  if you want to add a list to another one, create new list in the target then copy to it 
	**  Copy Items 
	*/
	if ( simple_list_getsize(list) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		if ( simple_list_isint(list,x) ) {
			simple_list_addint_gc(pState,pNewList,simple_list_getint(list,x));
		}
		else if ( simple_list_isdouble(list,x) ) {
			simple_list_adddouble_gc(pState,pNewList,simple_list_getdouble(list,x));
		}
		else if ( simple_list_isstring(list,x) ) {
			simple_list_addstring2_gc(pState,pNewList,simple_list_getstring(list,x),simple_list_getstringsize(list,x));
		}
		else if ( simple_list_ispointer(list,x) ) {
			simple_list_addpointer_gc(pState,pNewList,simple_list_getpointer(list,x));
		}
		else if ( simple_list_islist(list,x) ) {
			pNewList2 = simple_list_newlist_gc(pState,pNewList);
			simple_list_copy_gc(pState,pNewList2,simple_list_getlist(list,x));
		}
	}
}

SIMPLE_API void simple_list_print ( List *list )
{
	int x,t,nSize  ;
	double y  ;
	const char *cStr  ;
	List *list2  ;
	assert(list != NULL);
	/* Print Items */
	if ( simple_list_getsize(list) < 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) { 
		if ( simple_list_isstring(list,x) ) {
			cStr = simple_list_getstring(list,x) ;
			nSize = simple_list_getstringsize(list,x);
			for ( t = 0 ; t < nSize ; t++ ) {
				printf( "%c",cStr[t] ) ;
			}
			printf( "\n" ) ;
		}
		else if ( simple_list_isnumber(list,x) ) {
			if ( simple_list_isdouble(list,x) ) {
				y = simple_list_getdouble(list,x) ;
				if ( y == (int) y ) {
					printf( "%.0f\n",y ) ;
				} else {
					printf( "%.2f\n",y ) ;
				}
			}
			else if ( simple_list_isint(list,x) ) {
				printf( "%d\n",simple_list_getint(list,x) ) ;
			}
		}
		else if ( simple_list_islist(list,x) ) {
			list2 = simple_list_getlist(list,x) ;
			if ( simple_vm_oop_isobject(list2) ) {
				simple_vm_oop_printobj(NULL,list2);
			}
			else {
				simple_list_print(list2);
			}
		}
		else if ( simple_list_ispointer(list,x) ) {
			printf( "%p\n",simple_list_getpointer(list,x) ) ;
		}
	}
}

SIMPLE_API void simple_list_deleteallitems_gc ( void *pState,List *list )
{
	Items *pItems,*pItemsNext  ;
	pItems = list->pFirst ;
	if ( pItems == NULL ) {
		return ;
	}
	pItemsNext = pItems ;
	/* Delete Items */
	while ( pItemsNext != NULL ) {
		pItemsNext = pItems->pNext ;
		simple_items_delete_gc(pState,pItems);
		pItems = pItemsNext ;
	}
	list->pFirst = NULL ;
	list->pLast = NULL ;
	list->pLastItemLastAccess = NULL ;
	list->size = 0 ;
	list->nNextItemAfterLastAccess = 0 ;
	/* Free Items Array */
	simple_list_deletearray_gc(pState,list);
	/* Free HashTable */
	if ( list->pHashTable != NULL ) {
		list->pHashTable = simple_hashtable_delete_gc(pState,list->pHashTable);
	}
}
/* List Items */

SIMPLE_API void simple_list_newitem_gc ( void *pState,List *list )
{
	Items *pItems  ;
	assert(list != NULL);
	pItems = simple_items_new_gc(pState);
	if ( (list->size) > 0 ) {
		list->pLast->pNext = pItems ;
		pItems->pPrev = list->pLast ;
		list->pLast = pItems ;
	} else {
		list->pFirst = pItems ;
		list->pLast = pItems ;
	}
	list->size = list->size + 1 ;
	/* Refresh The Cache */
	list->nNextItemAfterLastAccess = 0 ;
	list->pLastItemLastAccess = NULL ;
}

SIMPLE_API Item * simple_list_getitem ( List *list,int index )
{
	int x  ;
	Items *pItems  ;
	Item *pItem  ;
	pItem = NULL ; 
	assert(list != NULL);
	if ( index > 0 && ( simple_list_getsize(list) > 0 ) && index <= simple_list_getsize(list) ) {
		/* Quickly get item from ItemsArray */
		if ( list->pItemsArray != NULL ) {
			return list->pItemsArray[index-1] ; 
		}
		/* Quickly Get The First or The Last Item */
		if ( index == 0 ) {
			list->pLastItemLastAccess = list->pFirst ;
			list->nNextItemAfterLastAccess = index + 1 ;
			return list->pFirst->pValue ;
		}
		else if ( index == simple_list_getsize(list) ) {
			list->pLastItemLastAccess = list->pLast ;
			list->nNextItemAfterLastAccess = index + 1 ;
			return list->pLast->pValue ;
		}
		/* Quickly get the next item */
		else if ( ( index == list->nNextItemAfterLastAccess ) && ( list->pLastItemLastAccess != NULL ) ) {
			if ( list->pLastItemLastAccess->pNext  != NULL ) {
				list->pLastItemLastAccess = list->pLastItemLastAccess->pNext ;
				list->nNextItemAfterLastAccess++ ;
				return list->pLastItemLastAccess->pValue ;
			}
		}
		/* Quickly get the current item */
		else if ( (index == list->nNextItemAfterLastAccess - 1) && ( list->pLastItemLastAccess != NULL ) ) {
			return list->pLastItemLastAccess->pValue ;
		}
		/* Quickly get item after the current item */
		else if ( ( index > list->nNextItemAfterLastAccess )  && ( list->pLastItemLastAccess != NULL ) ) {
			pItems = list->pLastItemLastAccess ;
			for ( x = list->nNextItemAfterLastAccess - 1 ; x <= index ; x++ ) {
				if ( x == index ) {
					list->nNextItemAfterLastAccess = index+1 ;
					list->pLastItemLastAccess = pItems ;
				}
				pItem = pItems->pValue ;
				pItems = pItems->pNext ;
			}
			return pItem ;
		}
		/* Quickly get item before the current item */
		else if ( ( ( list->nNextItemAfterLastAccess - index ) < index ) && ( list->pLastItemLastAccess != NULL ) ) {
			pItems = list->pLastItemLastAccess ;
			for ( x = list->nNextItemAfterLastAccess - 1 ; x >= index ; x-- ) {
				if ( x == index ) {
					list->nNextItemAfterLastAccess = index+1 ;
					list->pLastItemLastAccess = pItems ;
				}
				pItem = pItems->pValue ;
				pItems = pItems->pPrev ;
			}
			return pItem ;
		}
		/* Linear Search  From Start */
		pItems = list->pFirst ;
		for ( x = 1 ; x <= index ; x++ ) {
			if ( x == index ) {
				list->nNextItemAfterLastAccess = index+1 ;
				list->pLastItemLastAccess = pItems ;
			}
			pItem = pItems->pValue ;
			pItems = pItems->pNext ;
		}
	}
	return pItem ;
}

SIMPLE_API void simple_list_setactiveitem ( List *list, Items *pItems, int index )
{
	assert(list != NULL);
	list->pLastItemLastAccess = pItems ;
	list->nNextItemAfterLastAccess = index + 1 ;
}

SIMPLE_API void simple_list_deleteitem_gc ( void *pState,List *list,int index )
{
	int x  ;
	Items *pItems,*pItemsPrev  ;
	assert(list != NULL);
	/* Goto the Item */
	if ( index > 0 && ( simple_list_getsize(list) > 0 ) && index <= simple_list_getsize(list) ) {
		/* Quickly Get the Last Item */
		if ( index == simple_list_getsize(list) ) {
			pItems = list->pLast ;
			pItemsPrev = pItems->pPrev ;
		}
		/* Linear Search */
		else {
			pItems = list->pFirst ;
			pItemsPrev = NULL ;
			for ( x = 1 ; x < index ; x++ ) {
				pItemsPrev = pItems ;
				pItems = pItems->pNext ;
			}
		}
		/* Delete The Item */
		if ( index == 1 ) {
			list->pFirst = pItems->pNext ;
		}
		if ( index == simple_list_getsize(list) ) {
			list->pLast = pItemsPrev ;
		}
		if ( pItemsPrev != NULL ) {
			pItemsPrev->pNext = pItems->pNext ;
		}
		if ( pItems->pNext != NULL ) {
			pItems->pNext->pPrev = pItemsPrev ;
		}
		simple_items_delete_gc(pState,pItems);
		list->size = list->size - 1 ;
	}
	/* Refresh The Cache */
	list->nNextItemAfterLastAccess = 0 ;
	list->pLastItemLastAccess = NULL ;
}

SIMPLE_API int simple_list_gettype ( List *list, int index )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	if ( pItem != NULL ) {
		return simple_item_gettype(pItem) ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_isstring ( List *list, int index )
{
	if ( simple_list_gettype(list,index) == ITEMTYPE_STRING ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_isnumber ( List *list, int index )
{
	if ( simple_list_gettype(list,index) == ITEMTYPE_NUMBER ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_islist ( List *list, int index )
{
	if ( simple_list_gettype(list,index) == ITEMTYPE_LIST ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_ispointer ( List *list, int index )
{
	if ( simple_list_gettype(list,index) == ITEMTYPE_POINTER ) {
		return 1 ;
	}
	return 0 ;
}
/* int */

SIMPLE_API void simple_list_setint_gc ( void *pState,List *list, int index ,int number )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.iNumber = number ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_INT ;
}

SIMPLE_API void simple_list_addint_gc ( void *pState,List *list,int x )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setint_gc(pState,list,simple_list_getsize(list),x);
}
/* Pointers */

SIMPLE_API void simple_list_setpointer_gc ( void *pState,List *list, int index ,void *pValue )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_POINTER);
	pItem->data.pointer = pValue ;
}

SIMPLE_API void simple_list_addpointer_gc ( void *pState,List *list,void *pValue )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setpointer_gc(pState,list,simple_list_getsize(list),pValue);
}
/* double */

SIMPLE_API void simple_list_setdouble_gc ( void *pState,List *list, int index ,double number )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.dNumber = number ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_DOUBLE ;
}

SIMPLE_API void simple_list_adddouble_gc ( void *pState,List *list,double x )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setdouble_gc(pState,list,simple_list_getsize(list),x);
}
/* String */

SIMPLE_API void simple_list_setstsimple_gc ( void *pState,List *list, int index ,const char *str )
{
	Item *pItem  ;
	String *string  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	simple_string_set_gc(pState,string,str);
}

SIMPLE_API void simple_list_setstring2_gc ( void *pState,List *list, int index ,const char *str,int str_size )
{
	Item *pItem  ;
	String *string  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	simple_string_set2_gc(pState,string,str,str_size);
}

SIMPLE_API void simple_list_addstring_gc ( void *pState,List *list,const char *str )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setstsimple_gc(pState,list,simple_list_getsize(list),str);
}

SIMPLE_API void simple_list_addstring2_gc ( void *pState,List *list,const char *str,int str_size )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setstring2_gc(pState,list,simple_list_getsize(list),str,str_size);
}
/* List */

SIMPLE_API List * simple_list_newlist_gc ( void *pState,List *list )
{
	Item *pItem  ;
	List *list2  ;
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	pItem = simple_list_getitem(list,simple_list_getsize(list));
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
	list2 = simple_item_getlist(pItem);
	return list2 ;
}

SIMPLE_API void simple_list_setlist_gc ( void *pState,List *list, int index )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
}

SIMPLE_API List * simple_list_getlist ( List *list, int index )
{
	Item *pItem  ;
	List *list2  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	list2 = simple_item_getlist(pItem);
	return list2 ;
}
/* Block Pointers */

SIMPLE_API void simple_list_setblockpointer_gc ( void *pState,List *list, int index ,void (*pBlock)(void *) )
{
	Item *pItem  ;
	assert(list != NULL);
	pItem = simple_list_getitem(list,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_BLOCKPOINTER);
	pItem->data.pBlock = pBlock ;
}

SIMPLE_API void simple_list_addblockpointer_gc ( void *pState,List *list,void (*pBlock)(void *) )
{
	assert(list != NULL);
	simple_list_newitem_gc(pState,list);
	simple_list_setblockpointer_gc(pState,list,simple_list_getsize(list),pBlock);
}

SIMPLE_API int simple_list_isblockpointer ( List *list, int index )
{
	if ( simple_list_gettype(list,index) == ITEMTYPE_BLOCKPOINTER ) {
		return 1 ;
	}
	return 0 ;
}

void simple_list_testblockpointer ( void *pointer )
{
	List *list  ;
	list = (List *) pointer ;
	puts(" Message from a block called by block pointer  ");
	printf( "List Size %d  \n",list->size ) ;
}
/*
**  Insert Items 
**  When you insert item, it will be inserted after nPos 
*/

SIMPLE_API void simple_list_insertitem_gc ( void *pState,List *list,int x )
{
	Items *pItems  ;
	assert(list != NULL);
	if ( ( x < 0 ) || ( x > simple_list_getsize(list) ) ) {
		return ;
	}
	else if ( x == simple_list_getsize(list) ) {
		simple_list_newitem_gc(pState,list);
		return ;
	}
	pItems = simple_items_new_gc(pState);
	/* Insert Item at the first of the list */
	if ( x==0 ) {
		pItems->pNext = list->pFirst ;
		pItems->pPrev = NULL ;
		list->pFirst->pPrev = pItems ;
		list->pFirst = pItems ;
		list->size = list->size + 1 ;
		return ;
	}
	simple_list_getitem(list,x);
	/* When we get an item, pLastItemLastAccess will be changed to Items * of that item */
	pItems->pNext = list->pLastItemLastAccess->pNext ;
	pItems->pNext->pPrev = pItems ;
	pItems->pPrev = list->pLastItemLastAccess ;
	list->pLastItemLastAccess->pNext = pItems ;
	list->size = list->size + 1 ;
}

SIMPLE_API void simple_list_insertint_gc ( void *pState,List *list,int nPos,int x )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setint_gc(pState,list,nPos+1,x);
}

SIMPLE_API void simple_list_insertdouble_gc ( void *pState,List *list,int nPos,double x )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setdouble_gc(pState,list,nPos+1,x);
}

SIMPLE_API void simple_list_insertpointer_gc ( void *pState,List *list,int nPos,void *pValue )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setpointer_gc(pState,list,nPos+1,pValue);
}

SIMPLE_API void simple_list_insertstsimple_gc ( void *pState,List *list,int nPos,const char *str )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setstsimple_gc(pState,list,nPos+1,str);
}

SIMPLE_API void simple_list_insertstring2_gc ( void *pState,List *list,int nPos,const char *str,int str_size )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setstring2_gc(pState,list,nPos+1,str,str_size);
}

SIMPLE_API void simple_list_insertblockpointer_gc ( void *pState,List *list,int nPos,void (*pBlock)(void *) )
{
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	simple_list_setblockpointer_gc(pState,list,nPos+1,pBlock);
}

SIMPLE_API List * simple_list_insertlist_gc ( void *pState,List *list,int nPos )
{
	Item *pItem  ;
	List *list2  ;
	assert(list != NULL);
	simple_list_insertitem_gc(pState,list,nPos);
	pItem = simple_list_getitem(list,nPos+1);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
	list2 = simple_item_getlist(pItem);
	return list2 ;
}
/* Is item inside list, support nested Lists */

SIMPLE_API int simple_list_isiteminsidelist ( List *list,Item *pItem )
{
	int x  ;
	Item *pItem2  ;
	List *list2  ;
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		pItem2 = simple_list_getitem(list,x);
		if ( pItem == pItem2 ) {
			return 1 ;
		}
		if ( simple_list_islist(list,x) ) {
			list2 = simple_item_getlist(pItem2);
			if ( simple_list_isiteminsidelist(list2,pItem) ) {
				return 1 ;
			}
		}
	}
	return 0 ;
}
/* Delete item from list using the item pointer */

SIMPLE_API int simple_list_deliteminsidelist ( List *list,Item *pItem )
{
	int x  ;
	Item *pItem2  ;
	List *list2  ;
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		pItem2 = simple_list_getitem(list,x);
		if ( pItem == pItem2 ) {
			simple_list_deleteitem(list,x);
			return 1 ;
		}
		if ( simple_list_islist(list,x) ) {
			list2 = simple_item_getlist(pItem2);
			if ( simple_list_isiteminsidelist(list2,pItem) ) {
				return 1 ;
			}
		}
	}
	return 0 ;
}
/* Linear Search */

SIMPLE_API int simple_list_findstring ( List *list,const char *str,int nColumn )
{
	int x,nCount  ;
	List *list2  ;
	assert(list != NULL);
	nCount = simple_list_getsize(list);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_isstring(list,x) ) {
					if ( strcmp(str,simple_list_getstring(list,x)) == 0 ) {
						return x ;
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(list,x) == 0 ) {
					continue ;
				}
				list2 = simple_list_getlist(list,x);
				if ( simple_list_getsize(list2)< nColumn ) {
					return -1 ;
				}
				if ( simple_list_isstring(list2,nColumn) ) {
					if ( strcmp(str,simple_list_getstring(list2,nColumn)) == 0 ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_finddouble ( List *list,double nNum1,int nColumn )
{
	int x,nCount  ;
	List *list2  ;
	assert(list != NULL);
	nCount = simple_list_getsize(list);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_isdouble(list,x) ) {
					if ( simple_list_getdouble(list,x) == nNum1 ) {
						return x ;
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(list,x) == 0 ) {
					continue ;
				}
				list2 = simple_list_getlist(list,x);
				if ( simple_list_getsize(list2)< nColumn ) {
					return -1 ;
				}
				if ( simple_list_isdouble(list2,nColumn) ) {
					if ( simple_list_getdouble(list2,nColumn) == nNum1 ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findpointer ( List *list,void *pointer )
{
	int x  ;
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		if ( simple_list_ispointer(list,x) ) {
			if ( simple_list_getpointer(list,x) == pointer ) {
				return x ;
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findinlistofobjs ( List *list,int nType,double nNum1,const char *str,int nColumn,char *cAttribute )
{
	int x,nCount,nPos  ;
	List *list2  ;
	assert(list != NULL);
	nCount = simple_list_getsize(list);
	simple_string_lower(cAttribute);
	/* Find Item */
	if ( (nCount > 0) && (nColumn > 0) ) {
		for ( x = 1 ; x <= nCount ; x++ ) {
			if ( simple_list_islist(list,x) == 0 ) {
				continue ;
			}
			list2 = simple_list_getlist(list,x);
			if ( nColumn > 1 ) {
				if ( simple_list_islist(list2,nColumn) ) {
					list2 = simple_list_getlist(list2,nColumn);
				}
				else {
					continue ;
				}
			}
			if ( simple_vm_oop_isobject(list2) == 0 ) {
				continue ;
			}
			nPos = simple_list_findstring(simple_list_getlist(list2,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
			if ( nPos == 0 ) {
				return -1 ;
			}
			list2 = simple_list_getlist(list2,SIMPLE_OBJECT_OBJECTDATA) ;
			list2 = simple_list_getlist(list2,nPos) ;
			if ( nType  == SIMPLE_VM_LISTOFOBJS_FINDSTRING ) {
				if ( strcmp(str,simple_list_getstring(list2,SIMPLE_VAR_VALUE)) == 0 ) {
					return x ;
				}
			}
			else {
				if ( simple_list_getdouble(list2,SIMPLE_VAR_VALUE) == nNum1 ) {
					return x ;
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findcpointer ( List *list,List *pValue,int nColumn )
{
	int x,nCount  ;
	List *list2, *list3  ;
	assert(list != NULL);
	nCount = simple_list_getsize(list);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(list,x) ) {
					list2 = simple_list_getlist(list,x);
					if ( api_iscpointer_list(list2) ) {
						if ( api_cpointer_cmp(list2,pValue) ) {
							return x ;
						}
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(list,x) == 0 ) {
					continue ;
				}
				list2 = simple_list_getlist(list,x);
				if ( simple_list_islist(list2,nColumn) ) {
					list3 = simple_list_getlist(list2,nColumn);
					if ( api_cpointer_cmp(list3,pValue) ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}
/* Sort (QuickSort) and Binary Search */

SIMPLE_API void simple_list_sortnum ( List *list,int left,int right,int nColumn,const char *cAttribute )
{
	int x,y,mid  ;
	double midvalue  ;
	x = left ;
	y = right ;
	mid = (x+y)/2 ;
	midvalue = simple_list_getdoublecolumn(list,mid,nColumn,cAttribute);
	while ( x <= y ) {
		while ( simple_list_getdoublecolumn(list,x,nColumn,cAttribute) < midvalue ) {
			x++ ;
		}
		while ( simple_list_getdoublecolumn(list,y,nColumn,cAttribute) > midvalue ) {
			y-- ;
		}
		if ( x <= y ) {
			simple_list_swap(list,x,y);
			x++ ;
			y-- ;
		}
	}
	if ( left < y ) {
		simple_list_sortnum(list, left, y,nColumn,cAttribute);
	}
	if ( y < right ) {
		simple_list_sortnum(list, x, right,nColumn,cAttribute);
	}
}

SIMPLE_API void simple_list_sortstr_gc ( void *pState,List *list,int left,int right,int nColumn,const char *cAttribute )
{
	int x,y,mid  ;
	String *midvalue  ;
	x = left ;
	y = right ;
	mid = (x+y)/2 ;
	midvalue = simple_string_new_gc(pState,simple_list_getstringcolumn(list,mid,nColumn,cAttribute));
	while ( x <= y ) {
		while ( strcmp(simple_list_getstringcolumn(list,x,nColumn,cAttribute),simple_string_get(midvalue)) < 0 ) {
			x++ ;
		}
		while ( strcmp(simple_list_getstringcolumn(list,y,nColumn,cAttribute),simple_string_get(midvalue)) > 0 ) {
			y-- ;
		}
		if ( x <= y ) {
			simple_list_swap(list,x,y);
			x++ ;
			y-- ;
		}
	}
	simple_string_delete_gc(pState,midvalue);
	if ( left < y ) {
		simple_list_sortstr_gc(pState,list, left, y,nColumn,cAttribute);
	}
	if ( y < right ) {
		simple_list_sortstr_gc(pState,list, x, right, nColumn,cAttribute);
	}
}

SIMPLE_API int simple_list_binarysearchnum ( List *list,double nNum1,int nColumn,const char *cAttribute )
{
	int nFirst,nMiddle,nLast  ;
	nFirst = 1 ;
	nLast = simple_list_getsize(list) ;
	while ( nFirst <= nLast ) {
		nMiddle = (nFirst+nLast)/2 ;
		if ( simple_list_getdoublecolumn(list,nMiddle,nColumn,cAttribute) == nNum1 ) {
			return nMiddle ;
		}
		else if ( simple_list_getdoublecolumn(list,nMiddle,nColumn,cAttribute) < nNum1 ) {
			nFirst = nMiddle + 1 ;
		}
		else {
			nLast = nMiddle - 1 ;
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_binarysearchstr ( List *list,const char *cFind,int nColumn,const char *cAttribute )
{
	int nFirst,nMiddle,nLast,nRes  ;
	nFirst = 1 ;
	nLast = simple_list_getsize(list) ;
	while ( nFirst <= nLast ) {
		nMiddle = (nFirst+nLast)/2 ;
		nRes = strcmp(simple_list_getstringcolumn(list,nMiddle,nColumn,cAttribute) ,cFind) ;
		if ( nRes == 0 ) {
			return nMiddle ;
		}
		else if ( nRes < 0 ) {
			nFirst = nMiddle + 1 ;
		}
		else {
			nLast = nMiddle - 1 ;
		}
	}
	return 0 ;
}

SIMPLE_API void simple_list_swap ( List *list,int x,int y )
{
	Item *pItem  ;
	Items *pItems  ;
	pItem = simple_list_getitem(list,x);
	pItems = list->pLastItemLastAccess ;
	simple_list_getitem(list,y);
	pItems->pValue = list->pLastItemLastAccess->pValue ;
	list->pLastItemLastAccess->pValue = pItem ;
}

SIMPLE_API double simple_list_getdoublecolumn ( List *list,int nIndex,int nColumn,const char *cAttribute )
{
	int nPos  ;
	if ( nColumn == 0 ) {
		return simple_list_getdouble(list,nIndex) ;
	}
	else {
		if ( strcmp(cAttribute,"") == 0 ) {
			return simple_list_getdouble(simple_list_getlist(list,nIndex),nColumn) ;
		}
		else {
			list = simple_list_getlist(list,nIndex);
			if ( nColumn > 1 ) {
				list = simple_list_getlist(list,nColumn);
			}
			if ( simple_vm_oop_isobject(list) ) {
				nPos = simple_list_findstring(simple_list_getlist(list,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				list = simple_list_getlist(list,SIMPLE_OBJECT_OBJECTDATA) ;
				list = simple_list_getlist(list,nPos) ;
				if ( simple_list_isdouble(list,SIMPLE_VAR_VALUE) ) {
					return simple_list_getdouble(list,SIMPLE_VAR_VALUE) ;
				}
			}
		}
	}
	return 0.0 ;
}

SIMPLE_API char * simple_list_getstringcolumn ( List *list,int nIndex,int nColumn,const char *cAttribute )
{
	int nPos  ;
	static char nullstring[] = "" ;
	if ( nColumn == 0 ) {
		return simple_list_getstring(list,nIndex) ;
	}
	else {
		if ( strcmp(cAttribute,"") == 0 ) {
			return simple_list_getstring(simple_list_getlist(list,nIndex),nColumn) ;
		}
		else {
			list = simple_list_getlist(list,nIndex);
			if ( nColumn > 1 ) {
				list = simple_list_getlist(list,nColumn);
			}
			if ( simple_vm_oop_isobject(list) ) {
				nPos = simple_list_findstring(simple_list_getlist(list,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				list = simple_list_getlist(list,SIMPLE_OBJECT_OBJECTDATA) ;
				list = simple_list_getlist(list,nPos) ;
				if ( simple_list_isstring(list,SIMPLE_VAR_VALUE) ) {
					return simple_list_getstring(list,SIMPLE_VAR_VALUE) ;
				}
			}
		}
	}
	return nullstring ;
}
/* List Items to Array */

SIMPLE_API void simple_list_genarray_gc ( void *pState,List *list )
{
	int x  ;
	Item **pArray  ;
	if ( simple_list_getsize(list) == 0 ) {
		return ;
	}
	if ( list->pItemsArray != NULL ) {
		simple_state_free(pState,list->pItemsArray);
	}
	/*
	**  Here we save the pointer in pArray and not in list->pItemsArray 
	**  Because we will fill the array with items pointers using simple_list_getitem() 
	**  And simple_list_getitem() check for using list->pItemsArray 
	*/
	pArray = (Item **) simple_state_malloc(pState,simple_list_getsize(list) * sizeof(Item *));
	if ( pArray == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		pArray[x-1] = simple_list_getitem(list,x);
	}
	list->pItemsArray = pArray ;
}

SIMPLE_API void simple_list_deletearray_gc ( void *pState,List *list )
{
	if ( list->pItemsArray != NULL ) {
		simple_state_free(pState,list->pItemsArray);
		list->pItemsArray = NULL ;
	}
}
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable_gc ( void *pState,List *list )
{
	int x  ;
	if ( list->pHashTable != NULL ) {
		list->pHashTable = simple_hashtable_delete_gc(pState,list->pHashTable);
	}
	list->pHashTable = simple_hashtable_new_gc(pState);
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		simple_hashtable_newnumber_gc(pState,list->pHashTable,simple_list_getstring(list,x),x);
	}
}

SIMPLE_API void simple_list_genhashtable2_gc ( void *pState,List *list )
{
	int x  ;
	List *list2  ;
	/* This Block. Take list of lists , the first item of the sub list is a string (key) */
	if ( list->pHashTable != NULL ) {
		list->pHashTable = simple_hashtable_delete_gc(pState,list->pHashTable);
	}
	list->pHashTable = simple_hashtable_new_gc(pState);
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		list2 = simple_list_getlist(list,x);
		simple_hashtable_newpointer_gc(pState,list->pHashTable,simple_list_getstring(list2,1),list2);
	}
}
/* Copy list by reference */

SIMPLE_API void simple_list_refcopy ( List *pNewList, List *list )
{
	pNewList->pFirst = list->pFirst ;
	pNewList->pLast = list->pLast ;
	pNewList->size = list->size ;
	pNewList->nNextItemAfterLastAccess = list->nNextItemAfterLastAccess ;
	pNewList->pLastItemLastAccess = list->pLastItemLastAccess ;
	pNewList->pItemsArray = list->pItemsArray ;
	pNewList->pHashTable = list->pHashTable ;
}

SIMPLE_API void simple_list_clear ( List *list )
{
	list->pFirst = NULL ;
	list->pLast = NULL ;
	list->size = 0 ;
	list->nNextItemAfterLastAccess = 0 ;
	list->pLastItemLastAccess = NULL ;
	list->pItemsArray = NULL ;
	list->pHashTable = NULL ;
}
/* Define blocks without State Pointer */

SIMPLE_API List * simple_list_new ( int nSize )
{
	return simple_list_new_gc(NULL,nSize) ;
}

SIMPLE_API void simple_list_genarray ( List *list )
{
	simple_list_genarray_gc(NULL,list);
}

SIMPLE_API List * simple_list_delete ( List *list )
{
	return simple_list_delete_gc(NULL,list) ;
}

SIMPLE_API void simple_list_deletearray ( List *list )
{
	simple_list_deletearray_gc(NULL,list);
}

SIMPLE_API void simple_list_newitem ( List *list )
{
	simple_list_newitem_gc(NULL,list);
}

SIMPLE_API void simple_list_deleteitem ( List *list,int index )
{
	simple_list_deleteitem_gc(NULL,list,index);
}
/* int */

SIMPLE_API void simple_list_setint ( List *list, int index ,int number )
{
	simple_list_setint_gc(NULL,list,index,number);
}

SIMPLE_API void simple_list_addint ( List *list,int x )
{
	simple_list_addint_gc(NULL,list,x);
}
/* Pointers */

SIMPLE_API void simple_list_setpointer ( List *list, int index ,void *pValue )
{
	simple_list_setpointer_gc(NULL,list,index,pValue);
}

SIMPLE_API void simple_list_addpointer ( List *list,void *pValue )
{
	simple_list_addpointer_gc(NULL,list,pValue);
}
/* Block Pointers */

SIMPLE_API void simple_list_setblockpointer ( List *list, int index ,void (*pBlock)(void *) )
{
	simple_list_setblockpointer_gc(NULL,list,index,pBlock);
}

SIMPLE_API void simple_list_addblockpointer ( List *list,void (*pBlock)(void *) )
{
	simple_list_addblockpointer_gc(NULL,list,pBlock);
}
/* double */

SIMPLE_API void simple_list_setdouble ( List *list, int index ,double number )
{
	simple_list_setdouble_gc(NULL,list,index,number);
}

SIMPLE_API void simple_list_adddouble ( List *list,double x )
{
	simple_list_adddouble_gc(NULL,list,x);
}
/* String */

SIMPLE_API void simple_list_setstring ( List *list, int index ,const char *str )
{
	simple_list_setstsimple_gc(NULL,list,index,str);
}

SIMPLE_API void simple_list_setstring2 ( List *list, int index ,const char *str,int str_size )
{
	simple_list_setstring2_gc(NULL,list,index,str,str_size);
}

SIMPLE_API void simple_list_addstring ( List *list,const char *str )
{
	simple_list_addstring_gc(NULL,list,str);
}

SIMPLE_API void simple_list_addstring2 ( List *list,const char *str,int str_size )
{
	simple_list_addstring2_gc(NULL,list,str,str_size);
}
/* List */

SIMPLE_API List * simple_list_newlist ( List *list )
{
	return simple_list_newlist_gc(NULL,list) ;
}

SIMPLE_API void simple_list_setlist ( List *list, int index )
{
	simple_list_setlist_gc(NULL,list,index);
}

SIMPLE_API void simple_list_copy ( List *pNewList, List *list )
{
	simple_list_copy_gc(NULL,pNewList,list);
}

SIMPLE_API void simple_list_deleteallitems ( List *list )
{
	simple_list_deleteallitems_gc(NULL,list);
}
/* Insert Items */

SIMPLE_API void simple_list_insertitem ( List *list,int x )
{
	simple_list_insertitem_gc(NULL,list,x);
}

SIMPLE_API void simple_list_insertint ( List *list,int nPos,int x )
{
	simple_list_insertint_gc(NULL,list,nPos,x);
}

SIMPLE_API void simple_list_insertdouble ( List *list,int nPos,double x )
{
	simple_list_insertdouble_gc(NULL,list,nPos,x);
}

SIMPLE_API void simple_list_insertpointer ( List *list,int nPos,void *pValue )
{
	simple_list_insertpointer_gc(NULL,list,nPos,pValue);
}

SIMPLE_API void simple_list_insertstring ( List *list,int nPos,const char *str )
{
	simple_list_insertstsimple_gc(NULL,list,nPos,str);
}

SIMPLE_API void simple_list_insertstring2 ( List *list,int nPos,const char *str,int str_size )
{
	simple_list_insertstring2_gc(NULL,list,nPos,str,str_size);
}

SIMPLE_API void simple_list_insertblockpointer ( List *list,int nPos,void (*pBlock)(void *) )
{
	simple_list_insertblockpointer_gc(NULL,list,nPos,pBlock);
}

SIMPLE_API List * simple_list_insertlist ( List *list,int nPos )
{
	return simple_list_insertlist_gc(NULL,list,nPos) ;
}

SIMPLE_API void simple_list_sortstr ( List *list,int left,int right,int nColumn,const char *cAttribute )
{
	simple_list_sortstr_gc(NULL,list,left,right,nColumn,cAttribute);
}
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable ( List *list )
{
	simple_list_genhashtable_gc(NULL,list);
}

SIMPLE_API void simple_list_genhashtable2 ( List *list )
{
	simple_list_genhashtable2_gc(NULL,list);
}
/* Test */

void simple_list_test ( void )
{
	List *list,*list2  ;
	int x  ;
	Item *pItem  ;
	String *string  ;
	char mystr[20]  ;
	printf( "Create new list, size = 10 \n" ) ;
	list = simple_list_new(10);
	printf( "List(1) size %d    \n", simple_list_getsize(list) ) ;
	printf( "Create empty list \n" ) ;
	list2 = simple_list_new(0);
	printf( "adding 15 items to the list \n" ) ;
	for ( x = 1 ; x <= 15 ; x++ ) {
		printf( "x : %d  \n" , x ) ;
		simple_list_newitem(list2);
	}
	printf( "List(2) size %d    \n", simple_list_getsize(list2) ) ;
	for ( x = 1 ; x <= 10 ; x++ ) {
		/* Work on items */
		pItem = simple_list_getitem(list2,x);
		simple_item_settype(pItem,ITEMTYPE_STRING);
		string = simple_item_getstring(pItem);
		sprintf( mystr , "The Item Number %d" , x ) ;
		simple_string_set(string,mystr);
		simple_string_print(string);
	}
	for ( x = 11 ; x <= 15 ; x++ ) {
		/* Work on items */
		pItem = simple_list_getitem(list2,x);
		simple_item_settype(pItem,ITEMTYPE_NUMBER);
	}
	/* Delete Items */
	printf( "Delete item number 5 \n" ) ;
	simple_list_deleteitem(list2,5);
	pItem = simple_list_getitem(list2,5);
	string = simple_item_getstring(pItem);
	simple_string_print(string);
	printf( "Delete item number 1 \n" ) ;
	/* Print Item */
	simple_list_deleteitem(list2,1);
	pItem = simple_list_getitem(list2,1);
	string = simple_item_getstring(pItem);
	simple_string_print(string);
	printf( "Delete item number %d \n",simple_list_getsize(list2) ) ;
	/* Print Item */
	simple_list_deleteitem(list2,simple_list_getsize(list2));
	printf( "get item number %d \n",simple_list_getsize(list2) ) ;
	/* Delete Lists */
	printf( "Deleting List 1 \n" ) ;
	simple_list_delete(list);
	printf( "Deleting List 2 \n" ) ;
	simple_list_delete(list2);
	getchar();
	/* Create/Delete Large List */
	printf( "Create List of 1000000 Items  \n" ) ;
	list = simple_list_new(1000000);
	printf( "Before Loop  \n" ) ;
	for ( x = 1 ; x <= 1000000 ; x++ ) {
		simple_list_setstring(list,x,"empty item");
	}
	printf( "Done  \n" ) ;
	getchar();
	printf( "Deleting List 1 \n" ) ;
	simple_list_delete(list);
	getchar();
	/* Create Nested Lists */
	printf( "List = {'first item',{'item (2) item(1)','item(2) item(2)'},'lastitem' , 50 , Pointer to int } \n  " ) ;
	list = simple_list_new(5);
	/* Set Item 1 */
	pItem = simple_list_getitem(list,1);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	simple_string_set(string,mystr);
	simple_string_print(string);
	/* Set Item 2 */
	pItem = simple_list_getitem(list,2);
	simple_item_settype(pItem,ITEMTYPE_LIST);
	list2 = simple_item_getlist(pItem);
	simple_list_newitem(list2);
	simple_list_newitem(list2);
	/* Work on items */
	pItem = simple_list_getitem(list2,1);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	sprintf( mystr , "Item (2) Item (1) "  ) ;
	simple_string_set(string,mystr);
	simple_string_print(string);
	/* Work on items */
	pItem = simple_list_getitem(list2,2);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	sprintf( mystr , "Item (2) Item (2) "  ) ;
	simple_string_set(string,mystr);
	simple_string_print(string);
	/* Set Item 3 */
	pItem = simple_list_getitem(list,3);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	string = simple_item_getstring(pItem);
	sprintf( mystr , "last item"  ) ;
	simple_string_set(string,mystr);
	simple_string_print(string);
	/* set item 4 */
	pItem = simple_list_getitem(list,4);
	simple_item_settype(pItem,ITEMTYPE_NUMBER);
	/* set item 5 */
	pItem = simple_list_getitem(list,5);
	simple_item_settype(pItem,ITEMTYPE_POINTER);
	printf( "Printing list \n  " ) ;
	simple_list_print(list);
	/* Copy List */
	printf( "\n Copy List1 to List 2 \n  " ) ;
	list2 = simple_list_new(0);
	simple_list_copy(list2,list);
	printf( "\n Printing List 2 \n  " ) ;
	simple_list_print(list2);
	simple_list_delete(list2);
	simple_list_delete(list);
	/* Use list_setstring & list_getstring */
	printf( "\n use simple_list_setstring and simple_list_getstring  \n" ) ;
	list = simple_list_new(3);
	simple_list_setstring(list,1,"one");
	simple_list_setstring(list,2,"two");
	simple_list_setstring(list,3,"three");
	for ( x = 1 ; x <= 3 ; x++ ) {
		printf( "Item Number %d = %s  \n",x,simple_list_getstring(list,x) ) ;
	}
	simple_list_delete(list);
	/* using list_addstring */
	printf( "using simple_list_addstring  \n" ) ;
	list = simple_list_new(0);
	simple_list_addstring(list,"item 1");
	simple_list_addstring(list,"item 2");
	simple_list_addstring(list,"item 3");
	simple_list_addstring(list,"item 4");
	simple_list_addstring(list,"item 5");
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		printf( "Item Number %d = %s  \n",x,simple_list_getstring(list,x) ) ;
	}
	/* Test Get item */
	printf( "Item Number 1 = %s  \n",simple_list_getstring(list,1) ) ;
	printf( "Item Number 5 = %s  \n",simple_list_getstring(list,5) ) ;
	printf( "Item Number 4 = %s  \n",simple_list_getstring(list,4) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(list,3) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(list,3) ) ;
	printf( "Item Number 2 = %s  \n",simple_list_getstring(list,2) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(list,3) ) ;
	simple_list_delete(list);
	/* Block Pointers */
	list = simple_list_new(0);
	simple_list_addblockpointer(list,simple_list_testblockpointer);
	puts(" *** Test Block Pointer *** ");
	simple_list_callblockpointer(list,1,list);
	simple_list_delete(list);
	getchar();
}
