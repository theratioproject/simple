
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
**  Functions 
**  List 
*/

SIMPLE_API List * simple_list_new_gc ( void *pState,int nSize )
{
	List *pList  ;
	pList = (List *) simple_state_malloc(pState,sizeof(List));
	if ( pList == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	return simple_list_new2_gc(pState,pList,nSize) ;
}

SIMPLE_API List * simple_list_new2_gc ( void *pState,List *pList,int nSize )
{
	int x  ;
	Items *pItems,*pItemsLast  ;
	pList->nSize = nSize ;
	if ( nSize > 0 ) {
		pItems = simple_items_new_gc(pState);
		pList->pFirst = pItems ;
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
		pList->pLast = pItems ;
	} else {
		pList->pFirst = NULL ;
		pList->pLast = NULL ;
	}
	pList->nNextItemAfterLastAccess = 0 ;
	pList->pLastItemLastAccess = NULL ;
	pList->pItemsArray = NULL ;
	pList->pHashTable = NULL ;
	return pList ;
}

SIMPLE_API List * simple_list_delete_gc ( void *pState,List *pList )
{
	Items *pItems,*pItemsNext  ;
	pItems = pList->pFirst ;
	pItemsNext = pItems ;
	/* Delete Items */
	while ( pItemsNext != NULL ) {
		pItemsNext = pItems->pNext ;
		simple_items_delete_gc(pState,pItems);
		pItems = pItemsNext ;
	}
	/* Free Items Array */
	simple_list_deletearray_gc(pState,pList);
	/* Free HashTable */
	if ( pList->pHashTable != NULL ) {
		pList->pHashTable = simple_hashtable_delete_gc(pState,pList->pHashTable);
	}
	simple_state_free(pState,pList);
	pList = NULL ;
	return pList ;
}

SIMPLE_API void simple_list_copy_gc ( void *pState,List *pNewList, List *pList )
{
	int x  ;
	List *pNewList2  ;
	assert(pList != NULL);
	/*
	**  This function don't add a new list before copying items 
	**  if you want to add a list to another one, create new list in the target then copy to it 
	**  Copy Items 
	*/
	if ( simple_list_getsize(pList) == 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		if ( simple_list_isint(pList,x) ) {
			simple_list_addint_gc(pState,pNewList,simple_list_getint(pList,x));
		}
		else if ( simple_list_isdouble(pList,x) ) {
			simple_list_adddouble_gc(pState,pNewList,simple_list_getdouble(pList,x));
		}
		else if ( simple_list_isstring(pList,x) ) {
			simple_list_addstring2_gc(pState,pNewList,simple_list_getstring(pList,x),simple_list_getstringsize(pList,x));
		}
		else if ( simple_list_ispointer(pList,x) ) {
			simple_list_addpointer_gc(pState,pNewList,simple_list_getpointer(pList,x));
		}
		else if ( simple_list_islist(pList,x) ) {
			pNewList2 = simple_list_newlist_gc(pState,pNewList);
			simple_list_copy_gc(pState,pNewList2,simple_list_getlist(pList,x));
		}
	}
}

SIMPLE_API void simple_list_print ( List *pList )
{
	int x,t,nSize  ;
	double y  ;
	const char *cStr  ;
	List *pList2  ;
	assert(pList != NULL);
	/* Print Items */
	if ( simple_list_getsize(pList) < 0 ) {
		return ;
	}
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		if ( simple_list_isstring(pList,x) ) {
			cStr = simple_list_getstring(pList,x) ;
			nSize = simple_list_getstringsize(pList,x);
			for ( t = 0 ; t < nSize ; t++ ) {
				printf( "%c",cStr[t] ) ;
			}
			printf( "\n" ) ;
		}
		else if ( simple_list_isnumber(pList,x) ) {
			if ( simple_list_isdouble(pList,x) ) {
				y = simple_list_getdouble(pList,x) ;
				if ( y == (int) y ) {
					printf( "%.0f\n",y ) ;
				} else {
					printf( "%.2f\n",y ) ;
				}
			}
			else if ( simple_list_isint(pList,x) ) {
				printf( "%d\n",simple_list_getint(pList,x) ) ;
			}
		}
		else if ( simple_list_islist(pList,x) ) {
			pList2 = simple_list_getlist(pList,x) ;
			if ( simple_vm_oop_isobject(pList2) ) {
				simple_vm_oop_printobj(NULL,pList2);
			}
			else {
				simple_list_print(pList2);
			}
		}
		else if ( simple_list_ispointer(pList,x) ) {
			printf( "%p\n",simple_list_getpointer(pList,x) ) ;
		}
	}
}

SIMPLE_API void simple_list_deleteallitems_gc ( void *pState,List *pList )
{
	Items *pItems,*pItemsNext  ;
	pItems = pList->pFirst ;
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
	pList->pFirst = NULL ;
	pList->pLast = NULL ;
	pList->pLastItemLastAccess = NULL ;
	pList->nSize = 0 ;
	pList->nNextItemAfterLastAccess = 0 ;
	/* Free Items Array */
	simple_list_deletearray_gc(pState,pList);
	/* Free HashTable */
	if ( pList->pHashTable != NULL ) {
		pList->pHashTable = simple_hashtable_delete_gc(pState,pList->pHashTable);
	}
}
/* List Items */

SIMPLE_API void simple_list_newitem_gc ( void *pState,List *pList )
{
	Items *pItems  ;
	assert(pList != NULL);
	pItems = simple_items_new_gc(pState);
	if ( (pList->nSize) > 0 ) {
		pList->pLast->pNext = pItems ;
		pItems->pPrev = pList->pLast ;
		pList->pLast = pItems ;
	} else {
		pList->pFirst = pItems ;
		pList->pLast = pItems ;
	}
	pList->nSize = pList->nSize + 1 ;
	/* Refresh The Cache */
	pList->nNextItemAfterLastAccess = 0 ;
	pList->pLastItemLastAccess = NULL ;
}

SIMPLE_API Item * simple_list_getitem ( List *pList,int index )
{
	int x  ;
	Items *pItems  ;
	Item *pItem  ;
	pItem = NULL ;
	assert(pList != NULL);
	if ( index >= 0 && ( simple_list_getsize(pList) >= 0 ) && index <= simple_list_getsize(pList) ) {
		/* Quickly get item from ItemsArray */
		if ( pList->pItemsArray != NULL ) {
			return pList->pItemsArray[index-1] ;
		}
		/* Quickly Get The First or The Last Item */
		if ( index == 0 ) {
			pList->pLastItemLastAccess = pList->pFirst ;
			pList->nNextItemAfterLastAccess = index   ;
			return pList->pFirst->pValue ;
		}
		else if ( index == simple_list_getsize(pList) ) {
			pList->pLastItemLastAccess = pList->pLast ;
			pList->nNextItemAfterLastAccess = index  ;
			return pList->pLast->pValue ;
		}
		/* Quickly get the next item */
		else if ( ( index == pList->nNextItemAfterLastAccess ) && ( pList->pLastItemLastAccess != NULL ) ) {
			if ( pList->pLastItemLastAccess->pNext  != NULL ) {
				pList->pLastItemLastAccess = pList->pLastItemLastAccess->pNext ;
				pList->nNextItemAfterLastAccess++ ;
				return pList->pLastItemLastAccess->pValue ;
			}
		}
		/* Quickly get the current item */
		else if ( (index == pList->nNextItemAfterLastAccess - 1) && ( pList->pLastItemLastAccess != NULL ) ) {
			return pList->pLastItemLastAccess->pValue ;
		}
		/* Quickly get item after the current item */
		else if ( ( index > pList->nNextItemAfterLastAccess )  && ( pList->pLastItemLastAccess != NULL ) ) {
			pItems = pList->pLastItemLastAccess ;
			for ( x = pList->nNextItemAfterLastAccess - 1 ; x <= index ; x++ ) {
				if ( x == index ) {
					pList->nNextItemAfterLastAccess = index+1 ;
					pList->pLastItemLastAccess = pItems ;
				}
				pItem = pItems->pValue ;
				pItems = pItems->pNext ;
			}
			return pItem ;
		}
		/* Quickly get item before the current item */
		else if ( ( ( pList->nNextItemAfterLastAccess - index ) < index ) && ( pList->pLastItemLastAccess != NULL ) ) {
			pItems = pList->pLastItemLastAccess ;
			for ( x = pList->nNextItemAfterLastAccess - 1 ; x >= index ; x-- ) {
				if ( x == index ) {
					pList->nNextItemAfterLastAccess = index+1 ;
					pList->pLastItemLastAccess = pItems ;
				}
				pItem = pItems->pValue ;
				pItems = pItems->pPrev ;
			}
			return pItem ;
		}
		/* Linear Search  From Start */
		pItems = pList->pFirst ;
		for ( x = 1 ; x <= index ; x++ ) {
			if ( x == index ) {
				pList->nNextItemAfterLastAccess = index+1 ;
				pList->pLastItemLastAccess = pItems ;
			}
			pItem = pItems->pValue ;
			pItems = pItems->pNext ;
		}
	}
	return pItem ;
}

SIMPLE_API void simple_list_setactiveitem ( List *pList, Items *pItems, int index )
{
	assert(pList != NULL);
	pList->pLastItemLastAccess = pItems ;
	pList->nNextItemAfterLastAccess = index + 1 ;
}

SIMPLE_API void simple_list_deleteitem_gc ( void *pState,List *pList,int index )
{
	int x  ;
	Items *pItems,*pItemsPrev  ;
	assert(pList != NULL);
	/* Goto the Item */
	if ( index > 0 && ( simple_list_getsize(pList) > 0 ) && index <= simple_list_getsize(pList) ) {
		/* Quickly Get the Last Item */
		if ( index == simple_list_getsize(pList) ) {
			pItems = pList->pLast ;
			pItemsPrev = pItems->pPrev ;
		}
		/* Linear Search */
		else {
			pItems = pList->pFirst ;
			pItemsPrev = NULL ;
			for ( x = 1 ; x < index ; x++ ) {
				pItemsPrev = pItems ;
				pItems = pItems->pNext ;
			}
		}
		/* Delete The Item */
		if ( index == 1 ) {
			pList->pFirst = pItems->pNext ;
		}
		if ( index == simple_list_getsize(pList) ) {
			pList->pLast = pItemsPrev ;
		}
		if ( pItemsPrev != NULL ) {
			pItemsPrev->pNext = pItems->pNext ;
		}
		if ( pItems->pNext != NULL ) {
			pItems->pNext->pPrev = pItemsPrev ;
		}
		simple_items_delete_gc(pState,pItems);
		pList->nSize = pList->nSize - 1 ;
	}
	/* Refresh The Cache */
	pList->nNextItemAfterLastAccess = 0 ;
	pList->pLastItemLastAccess = NULL ;
}

SIMPLE_API int simple_list_gettype ( List *pList, int index )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	if ( pItem != NULL ) {
		return simple_item_gettype(pItem) ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_isstring ( List *pList, int index )
{
	if ( simple_list_gettype(pList,index) == ITEMTYPE_STRING ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_isnumber ( List *pList, int index )
{
	if ( simple_list_gettype(pList,index) == ITEMTYPE_NUMBER ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_islist ( List *pList, int index )
{
	if ( simple_list_gettype(pList,index) == ITEMTYPE_LIST ) {
		return 1 ;
	}
	return 0 ;
}

SIMPLE_API int simple_list_ispointer ( List *pList, int index )
{
	if ( simple_list_gettype(pList,index) == ITEMTYPE_POINTER ) {
		return 1 ;
	}
	return 0 ;
}
/* int */

SIMPLE_API void simple_list_setint_gc ( void *pState,List *pList, int index ,int number )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.iNumber = number ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_INT ;
}

SIMPLE_API void simple_list_addint_gc ( void *pState,List *pList,int x )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setint_gc(pState,pList,simple_list_getsize(pList),x);
}
/* Pointers */

SIMPLE_API void simple_list_setpointer_gc ( void *pState,List *pList, int index ,void *pValue )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_POINTER);
	pItem->data.pPointer = pValue ;
}

SIMPLE_API void simple_list_addpointer_gc ( void *pState,List *pList,void *pValue )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setpointer_gc(pState,pList,simple_list_getsize(pList),pValue);
}
/* double */

SIMPLE_API void simple_list_setdouble_gc ( void *pState,List *pList, int index ,double number )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_NUMBER);
	pItem->data.dNumber = number ;
	pItem->NumberFlag = ITEM_NUMBERFLAG_DOUBLE ;
}

SIMPLE_API void simple_list_adddouble_gc ( void *pState,List *pList,double x )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setdouble_gc(pState,pList,simple_list_getsize(pList),x);
}
/* String */

SIMPLE_API void simple_list_setstsimple_gc ( void *pState,List *pList, int index ,const char *str )
{
	Item *pItem  ;
	String *pString  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	simple_string_set_gc(pState,pString,str);
}

SIMPLE_API void simple_list_setstring2_gc ( void *pState,List *pList, int index ,const char *str,int nStrSize )
{
	Item *pItem  ;
	String *pString  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	simple_string_set2_gc(pState,pString,str,nStrSize);
}

SIMPLE_API void simple_list_addstring_gc ( void *pState,List *pList,const char *str )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setstsimple_gc(pState,pList,simple_list_getsize(pList),str);
}

SIMPLE_API void simple_list_addstring2_gc ( void *pState,List *pList,const char *str,int nStrSize )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setstring2_gc(pState,pList,simple_list_getsize(pList),str,nStrSize);
}
/* List */

SIMPLE_API List * simple_list_newlist_gc ( void *pState,List *pList )
{
	Item *pItem  ;
	List *pList2  ;
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	pItem = simple_list_getitem(pList,simple_list_getsize(pList));
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
	pList2 = simple_item_getlist(pItem);
	return pList2 ;
}

SIMPLE_API void simple_list_setlist_gc ( void *pState,List *pList, int index )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
}

SIMPLE_API List * simple_list_getlist ( List *pList, int index )
{
	Item *pItem  ;
	List *pList2  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	pList2 = simple_item_getlist(pItem);
	return pList2 ;
}
/* Function Pointers */

SIMPLE_API void simple_list_setfuncpointer_gc ( void *pState,List *pList, int index ,void (*pFunc)(void *) )
{
	Item *pItem  ;
	assert(pList != NULL);
	pItem = simple_list_getitem(pList,index);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_BLOCKPOINTER);
	pItem->data.pFunc = pFunc ;
}

SIMPLE_API void simple_list_addfuncpointer_gc ( void *pState,List *pList,void (*pFunc)(void *) )
{
	assert(pList != NULL);
	simple_list_newitem_gc(pState,pList);
	simple_list_setfuncpointer_gc(pState,pList,simple_list_getsize(pList),pFunc);
}

SIMPLE_API int simple_list_isfuncpointer ( List *pList, int index )
{
	if ( simple_list_gettype(pList,index) == ITEMTYPE_BLOCKPOINTER ) {
		return 1 ;
	}
	return 0 ;
}

void simple_list_testfuncpointer ( void *pPointer )
{
	List *pList  ;
	pList = (List *) pPointer ;
	puts(" Message from a function called by function pointer  ");
	printf( "List Size %d  \n",pList->nSize ) ;
}
/*
**  Insert Items 
**  When you insert item, it will be inserted after nPos 
*/

SIMPLE_API void simple_list_insertitem_gc ( void *pState,List *pList,int x )
{
	Items *pItems  ;
	assert(pList != NULL);
	if ( ( x < 0 ) || ( x > simple_list_getsize(pList) ) ) {
		return ;
	}
	else if ( x == simple_list_getsize(pList) ) {
		simple_list_newitem_gc(pState,pList);
		return ;
	}
	pItems = simple_items_new_gc(pState);
	/* Insert Item at the first of the list */
	if ( x==0 ) {
		pItems->pNext = pList->pFirst ;
		pItems->pPrev = NULL ;
		pList->pFirst->pPrev = pItems ;
		pList->pFirst = pItems ;
		pList->nSize = pList->nSize + 1 ;
		return ;
	}
	simple_list_getitem(pList,x);
	/* When we get an item, pLastItemLastAccess will be changed to Items * of that item */
	pItems->pNext = pList->pLastItemLastAccess->pNext ;
	pItems->pNext->pPrev = pItems ;
	pItems->pPrev = pList->pLastItemLastAccess ;
	pList->pLastItemLastAccess->pNext = pItems ;
	pList->nSize = pList->nSize + 1 ;
}

SIMPLE_API void simple_list_insertint_gc ( void *pState,List *pList,int nPos,int x )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setint_gc(pState,pList,nPos+1,x);
}

SIMPLE_API void simple_list_insertdouble_gc ( void *pState,List *pList,int nPos,double x )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setdouble_gc(pState,pList,nPos+1,x);
}

SIMPLE_API void simple_list_insertpointer_gc ( void *pState,List *pList,int nPos,void *pValue )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setpointer_gc(pState,pList,nPos+1,pValue);
}

SIMPLE_API void simple_list_insertstsimple_gc ( void *pState,List *pList,int nPos,const char *str )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setstsimple_gc(pState,pList,nPos+1,str);
}

SIMPLE_API void simple_list_insertstring2_gc ( void *pState,List *pList,int nPos,const char *str,int nStrSize )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setstring2_gc(pState,pList,nPos+1,str,nStrSize);
}

SIMPLE_API void simple_list_insertfuncpointer_gc ( void *pState,List *pList,int nPos,void (*pFunc)(void *) )
{
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	simple_list_setfuncpointer_gc(pState,pList,nPos+1,pFunc);
}

SIMPLE_API List * simple_list_insertlist_gc ( void *pState,List *pList,int nPos )
{
	Item *pItem  ;
	List *pList2  ;
	assert(pList != NULL);
	simple_list_insertitem_gc(pState,pList,nPos);
	pItem = simple_list_getitem(pList,nPos+1);
	simple_item_settype_gc(pState,pItem,ITEMTYPE_LIST);
	pList2 = simple_item_getlist(pItem);
	return pList2 ;
}
/* Is item inside list, support nested Lists */

SIMPLE_API int simple_list_isiteminsidelist ( List *pList,Item *pItem )
{
	int x  ;
	Item *pItem2  ;
	List *pList2  ;
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pItem2 = simple_list_getitem(pList,x);
		if ( pItem == pItem2 ) {
			return 1 ;
		}
		if ( simple_list_islist(pList,x) ) {
			pList2 = simple_item_getlist(pItem2);
			if ( simple_list_isiteminsidelist(pList2,pItem) ) {
				return 1 ;
			}
		}
	}
	return 0 ;
}
/* Delete item from list using the item pointer */

SIMPLE_API int simple_list_deliteminsidelist ( List *pList,Item *pItem )
{
	int x  ;
	Item *pItem2  ;
	List *pList2  ;
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pItem2 = simple_list_getitem(pList,x);
		if ( pItem == pItem2 ) {
			simple_list_deleteitem(pList,x);
			return 1 ;
		}
		if ( simple_list_islist(pList,x) ) {
			pList2 = simple_item_getlist(pItem2);
			if ( simple_list_isiteminsidelist(pList2,pItem) ) {
				return 1 ;
			}
		}
	}
	return 0 ;
}
/* Linear Search */

SIMPLE_API int simple_list_findstring ( List *pList,const char *str,int nColumn )
{
	int x,nCount  ;
	List *pList2  ;
	assert(pList != NULL);
	nCount = simple_list_getsize(pList);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_isstring(pList,x) ) {
					if ( strcmp(str,simple_list_getstring(pList,x)) == 0 ) {
						return x ;
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(pList,x) == 0 ) {
					continue ;
				}
				pList2 = simple_list_getlist(pList,x);
				if ( simple_list_getsize(pList2)< nColumn ) {
					return -1 ;
				}
				if ( simple_list_isstring(pList2,nColumn) ) {
					if ( strcmp(str,simple_list_getstring(pList2,nColumn)) == 0 ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_finddouble ( List *pList,double nNum1,int nColumn )
{
	int x,nCount  ;
	List *pList2  ;
	assert(pList != NULL);
	nCount = simple_list_getsize(pList);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_isdouble(pList,x) ) {
					if ( simple_list_getdouble(pList,x) == nNum1 ) {
						return x ;
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(pList,x) == 0 ) {
					continue ;
				}
				pList2 = simple_list_getlist(pList,x);
				if ( simple_list_getsize(pList2)< nColumn ) {
					return -1 ;
				}
				if ( simple_list_isdouble(pList2,nColumn) ) {
					if ( simple_list_getdouble(pList2,nColumn) == nNum1 ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findpointer ( List *pList,void *pPointer )
{
	int x  ;
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		if ( simple_list_ispointer(pList,x) ) {
			if ( simple_list_getpointer(pList,x) == pPointer ) {
				return x ;
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findinlistofobjs ( List *pList,int nType,double nNum1,const char *str,int nColumn,char *cAttribute )
{
	int x,nCount,nPos  ;
	List *pList2  ;
	assert(pList != NULL);
	nCount = simple_list_getsize(pList);
	simple_string_lower(cAttribute);
	/* Find Item */
	if ( (nCount > 0) && (nColumn > 0) ) {
		for ( x = 1 ; x <= nCount ; x++ ) {
			if ( simple_list_islist(pList,x) == 0 ) {
				continue ;
			}
			pList2 = simple_list_getlist(pList,x);
			if ( nColumn > 1 ) {
				if ( simple_list_islist(pList2,nColumn) ) {
					pList2 = simple_list_getlist(pList2,nColumn);
				}
				else {
					continue ;
				}
			}
			if ( simple_vm_oop_isobject(pList2) == 0 ) {
				continue ;
			}
			nPos = simple_list_findstring(simple_list_getlist(pList2,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
			if ( nPos == 0 ) {
				return -1 ;
			}
			pList2 = simple_list_getlist(pList2,SIMPLE_OBJECT_OBJECTDATA) ;
			pList2 = simple_list_getlist(pList2,nPos) ;
			if ( nType  == SIMPLE_VM_LISTOFOBJS_FINDSTRING ) {
				if ( strcmp(str,simple_list_getstring(pList2,SIMPLE_VAR_VALUE)) == 0 ) {
					return x ;
				}
			}
			else {
				if ( simple_list_getdouble(pList2,SIMPLE_VAR_VALUE) == nNum1 ) {
					return x ;
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_findcpointer ( List *pList,List *pValue,int nColumn )
{
	int x,nCount  ;
	List *pList2, *pList3  ;
	assert(pList != NULL);
	nCount = simple_list_getsize(pList);
	/* Find Item */
	if ( nCount > 0 ) {
		if ( nColumn == 0 ) {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(pList,x) ) {
					pList2 = simple_list_getlist(pList,x);
					if ( simple_vm_api_iscpointerlist(pList2) ) {
						if ( simple_vm_api_cpointercmp(pList2,pValue) ) {
							return x ;
						}
					}
				}
			}
		}
		else {
			for ( x = 1 ; x <= nCount ; x++ ) {
				if ( simple_list_islist(pList,x) == 0 ) {
					continue ;
				}
				pList2 = simple_list_getlist(pList,x);
				if ( simple_list_islist(pList2,nColumn) ) {
					pList3 = simple_list_getlist(pList2,nColumn);
					if ( simple_vm_api_cpointercmp(pList3,pValue) ) {
						return x ;
					}
				}
			}
		}
	}
	return 0 ;
}
/* Sort (QuickSort) and Binary Search */

SIMPLE_API void simple_list_sortnum ( List *pList,int left,int right,int nColumn,const char *cAttribute )
{
	int x,y,mid  ;
	double midvalue  ;
	x = left ;
	y = right ;
	mid = (x+y)/2 ;
	midvalue = simple_list_getdoublecolumn(pList,mid,nColumn,cAttribute);
	while ( x <= y ) {
		while ( simple_list_getdoublecolumn(pList,x,nColumn,cAttribute) < midvalue ) {
			x++ ;
		}
		while ( simple_list_getdoublecolumn(pList,y,nColumn,cAttribute) > midvalue ) {
			y-- ;
		}
		if ( x <= y ) {
			simple_list_swap(pList,x,y);
			x++ ;
			y-- ;
		}
	}
	if ( left < y ) {
		simple_list_sortnum(pList, left, y,nColumn,cAttribute);
	}
	if ( y < right ) {
		simple_list_sortnum(pList, x, right,nColumn,cAttribute);
	}
}

SIMPLE_API void simple_list_sortstr_gc ( void *pState,List *pList,int left,int right,int nColumn,const char *cAttribute )
{
	int x,y,mid  ;
	String *midvalue  ;
	x = left ;
	y = right ;
	mid = (x+y)/2 ;
	midvalue = simple_string_new_gc(pState,simple_list_getstringcolumn(pList,mid,nColumn,cAttribute));
	while ( x <= y ) {
		while ( strcmp(simple_list_getstringcolumn(pList,x,nColumn,cAttribute),simple_string_get(midvalue)) < 0 ) {
			x++ ;
		}
		while ( strcmp(simple_list_getstringcolumn(pList,y,nColumn,cAttribute),simple_string_get(midvalue)) > 0 ) {
			y-- ;
		}
		if ( x <= y ) {
			simple_list_swap(pList,x,y);
			x++ ;
			y-- ;
		}
	}
	simple_string_delete_gc(pState,midvalue);
	if ( left < y ) {
		simple_list_sortstr_gc(pState,pList, left, y,nColumn,cAttribute);
	}
	if ( y < right ) {
		simple_list_sortstr_gc(pState,pList, x, right, nColumn,cAttribute);
	}
}

SIMPLE_API int simple_list_binarysearchnum ( List *pList,double nNum1,int nColumn,const char *cAttribute )
{
	int nFirst,nMiddle,nLast  ;
	nFirst = 1 ;
	nLast = simple_list_getsize(pList) ;
	while ( nFirst <= nLast ) {
		nMiddle = (nFirst+nLast)/2 ;
		if ( simple_list_getdoublecolumn(pList,nMiddle,nColumn,cAttribute) == nNum1 ) {
			return nMiddle ;
		}
		else if ( simple_list_getdoublecolumn(pList,nMiddle,nColumn,cAttribute) < nNum1 ) {
			nFirst = nMiddle + 1 ;
		}
		else {
			nLast = nMiddle - 1 ;
		}
	}
	return 0 ;
}

SIMPLE_API int simple_list_binarysearchstr ( List *pList,const char *cFind,int nColumn,const char *cAttribute )
{
	int nFirst,nMiddle,nLast,nRes  ;
	nFirst = 1 ;
	nLast = simple_list_getsize(pList) ;
	while ( nFirst <= nLast ) {
		nMiddle = (nFirst+nLast)/2 ;
		nRes = strcmp(simple_list_getstringcolumn(pList,nMiddle,nColumn,cAttribute) ,cFind) ;
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

SIMPLE_API void simple_list_swap ( List *pList,int x,int y )
{
	Item *pItem  ;
	Items *pItems  ;
	pItem = simple_list_getitem(pList,x);
	pItems = pList->pLastItemLastAccess ;
	simple_list_getitem(pList,y);
	pItems->pValue = pList->pLastItemLastAccess->pValue ;
	pList->pLastItemLastAccess->pValue = pItem ;
}

SIMPLE_API double simple_list_getdoublecolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute )
{
	int nPos  ;
	if ( nColumn == 0 ) {
		return simple_list_getdouble(pList,nIndex) ;
	}
	else {
		if ( strcmp(cAttribute,"") == 0 ) {
			return simple_list_getdouble(simple_list_getlist(pList,nIndex),nColumn) ;
		}
		else {
			pList = simple_list_getlist(pList,nIndex);
			if ( nColumn > 1 ) {
				pList = simple_list_getlist(pList,nColumn);
			}
			if ( simple_vm_oop_isobject(pList) ) {
				nPos = simple_list_findstring(simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA) ;
				pList = simple_list_getlist(pList,nPos) ;
				if ( simple_list_isdouble(pList,SIMPLE_VAR_VALUE) ) {
					return simple_list_getdouble(pList,SIMPLE_VAR_VALUE) ;
				}
			}
		}
	}
	return 0.0 ;
}

SIMPLE_API char * simple_list_getstringcolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute )
{
	int nPos  ;
	static char nullstring[] = "" ;
	if ( nColumn == 0 ) {
		return simple_list_getstring(pList,nIndex) ;
	}
	else {
		if ( strcmp(cAttribute,"") == 0 ) {
			return simple_list_getstring(simple_list_getlist(pList,nIndex),nColumn) ;
		}
		else {
			pList = simple_list_getlist(pList,nIndex);
			if ( nColumn > 1 ) {
				pList = simple_list_getlist(pList,nColumn);
			}
			if ( simple_vm_oop_isobject(pList) ) {
				nPos = simple_list_findstring(simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				pList = simple_list_getlist(pList,SIMPLE_OBJECT_OBJECTDATA) ;
				pList = simple_list_getlist(pList,nPos) ;
				if ( simple_list_isstring(pList,SIMPLE_VAR_VALUE) ) {
					return simple_list_getstring(pList,SIMPLE_VAR_VALUE) ;
				}
			}
		}
	}
	return nullstring ;
}
/* List Items to Array */

SIMPLE_API void simple_list_genarray_gc ( void *pState,List *pList )
{
	int x  ;
	Item **pArray  ;
	if ( simple_list_getsize(pList) == 0 ) {
		return ;
	}
	if ( pList->pItemsArray != NULL ) {
		simple_state_free(pState,pList->pItemsArray);
	}
	/*
	**  Here we save the pointer in pArray and not in pList->pItemsArray 
	**  Because we will fill the array with items pointers using simple_list_getitem() 
	**  And simple_list_getitem() check for using pList->pItemsArray 
	*/
	pArray = (Item **) simple_state_malloc(pState,simple_list_getsize(pList) * sizeof(Item *));
	if ( pArray == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pArray[x-1] = simple_list_getitem(pList,x);
	}
	pList->pItemsArray = pArray ;
}

SIMPLE_API void simple_list_deletearray_gc ( void *pState,List *pList )
{
	if ( pList->pItemsArray != NULL ) {
		simple_state_free(pState,pList->pItemsArray);
		pList->pItemsArray = NULL ;
	}
}
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable_gc ( void *pState,List *pList )
{
	int x  ;
	if ( pList->pHashTable != NULL ) {
		pList->pHashTable = simple_hashtable_delete_gc(pState,pList->pHashTable);
	}
	pList->pHashTable = simple_hashtable_new_gc(pState);
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		simple_hashtable_newnumber_gc(pState,pList->pHashTable,simple_list_getstring(pList,x),x);
	}
}

SIMPLE_API void simple_list_genhashtable2_gc ( void *pState,List *pList )
{
	int x  ;
	List *pList2  ;
	/* This Func. Take list of lists , the first item of the sub list is a string (key) */
	if ( pList->pHashTable != NULL ) {
		pList->pHashTable = simple_hashtable_delete_gc(pState,pList->pHashTable);
	}
	pList->pHashTable = simple_hashtable_new_gc(pState);
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList2 = simple_list_getlist(pList,x);
		simple_hashtable_newpointer_gc(pState,pList->pHashTable,simple_list_getstring(pList2,1),pList2);
	}
}
/* Copy list by reference */

SIMPLE_API void simple_list_refcopy ( List *pNewList, List *pList )
{
	pNewList->pFirst = pList->pFirst ;
	pNewList->pLast = pList->pLast ;
	pNewList->nSize = pList->nSize ;
	pNewList->nNextItemAfterLastAccess = pList->nNextItemAfterLastAccess ;
	pNewList->pLastItemLastAccess = pList->pLastItemLastAccess ;
	pNewList->pItemsArray = pList->pItemsArray ;
	pNewList->pHashTable = pList->pHashTable ;
}

SIMPLE_API void simple_list_clear ( List *pList )
{
	pList->pFirst = NULL ;
	pList->pLast = NULL ;
	pList->nSize = 0 ;
	pList->nNextItemAfterLastAccess = 0 ;
	pList->pLastItemLastAccess = NULL ;
	pList->pItemsArray = NULL ;
	pList->pHashTable = NULL ;
}
/* Define functions without State Pointer */

SIMPLE_API List * simple_list_new ( int nSize )
{
	return simple_list_new_gc(NULL,nSize) ;
}

SIMPLE_API void simple_list_genarray ( List *pList )
{
	simple_list_genarray_gc(NULL,pList);
}

SIMPLE_API List * simple_list_delete ( List *pList )
{
	return simple_list_delete_gc(NULL,pList) ;
}

SIMPLE_API void simple_list_deletearray ( List *pList )
{
	simple_list_deletearray_gc(NULL,pList);
}

SIMPLE_API void simple_list_newitem ( List *pList )
{
	simple_list_newitem_gc(NULL,pList);
}

SIMPLE_API void simple_list_deleteitem ( List *pList,int index )
{
	simple_list_deleteitem_gc(NULL,pList,index);
}
/* int */

SIMPLE_API void simple_list_setint ( List *pList, int index ,int number )
{
	simple_list_setint_gc(NULL,pList,index,number);
}

SIMPLE_API void simple_list_addint ( List *pList,int x )
{
	simple_list_addint_gc(NULL,pList,x);
}
/* Pointers */

SIMPLE_API void simple_list_setpointer ( List *pList, int index ,void *pValue )
{
	simple_list_setpointer_gc(NULL,pList,index,pValue);
}

SIMPLE_API void simple_list_addpointer ( List *pList,void *pValue )
{
	simple_list_addpointer_gc(NULL,pList,pValue);
}
/* Function Pointers */

SIMPLE_API void simple_list_setfuncpointer ( List *pList, int index ,void (*pFunc)(void *) )
{
	simple_list_setfuncpointer_gc(NULL,pList,index,pFunc);
}

SIMPLE_API void simple_list_addfuncpointer ( List *pList,void (*pFunc)(void *) )
{
	simple_list_addfuncpointer_gc(NULL,pList,pFunc);
}
/* double */

SIMPLE_API void simple_list_setdouble ( List *pList, int index ,double number )
{
	simple_list_setdouble_gc(NULL,pList,index,number);
}

SIMPLE_API void simple_list_adddouble ( List *pList,double x )
{
	simple_list_adddouble_gc(NULL,pList,x);
}
/* String */

SIMPLE_API void simple_list_setstring ( List *pList, int index ,const char *str )
{
	simple_list_setstsimple_gc(NULL,pList,index,str);
}

SIMPLE_API void simple_list_setstring2 ( List *pList, int index ,const char *str,int nStrSize )
{
	simple_list_setstring2_gc(NULL,pList,index,str,nStrSize);
}

SIMPLE_API void simple_list_addstring ( List *pList,const char *str )
{
	simple_list_addstring_gc(NULL,pList,str);
}

SIMPLE_API void simple_list_addstring2 ( List *pList,const char *str,int nStrSize )
{
	simple_list_addstring2_gc(NULL,pList,str,nStrSize);
}
/* List */

SIMPLE_API List * simple_list_newlist ( List *pList )
{
	return simple_list_newlist_gc(NULL,pList) ;
}

SIMPLE_API void simple_list_setlist ( List *pList, int index )
{
	simple_list_setlist_gc(NULL,pList,index);
}

SIMPLE_API void simple_list_copy ( List *pNewList, List *pList )
{
	simple_list_copy_gc(NULL,pNewList,pList);
}

SIMPLE_API void simple_list_deleteallitems ( List *pList )
{
	simple_list_deleteallitems_gc(NULL,pList);
}
/* Insert Items */

SIMPLE_API void simple_list_insertitem ( List *pList,int x )
{
	simple_list_insertitem_gc(NULL,pList,x);
}

SIMPLE_API void simple_list_insertint ( List *pList,int nPos,int x )
{
	simple_list_insertint_gc(NULL,pList,nPos,x);
}

SIMPLE_API void simple_list_insertdouble ( List *pList,int nPos,double x )
{
	simple_list_insertdouble_gc(NULL,pList,nPos,x);
}

SIMPLE_API void simple_list_insertpointer ( List *pList,int nPos,void *pValue )
{
	simple_list_insertpointer_gc(NULL,pList,nPos,pValue);
}

SIMPLE_API void simple_list_insertstring ( List *pList,int nPos,const char *str )
{
	simple_list_insertstsimple_gc(NULL,pList,nPos,str);
}

SIMPLE_API void simple_list_insertstring2 ( List *pList,int nPos,const char *str,int nStrSize )
{
	simple_list_insertstring2_gc(NULL,pList,nPos,str,nStrSize);
}

SIMPLE_API void simple_list_insertfuncpointer ( List *pList,int nPos,void (*pFunc)(void *) )
{
	simple_list_insertfuncpointer_gc(NULL,pList,nPos,pFunc);
}

SIMPLE_API List * simple_list_insertlist ( List *pList,int nPos )
{
	return simple_list_insertlist_gc(NULL,pList,nPos) ;
}

SIMPLE_API void simple_list_sortstr ( List *pList,int left,int right,int nColumn,const char *cAttribute )
{
	simple_list_sortstr_gc(NULL,pList,left,right,nColumn,cAttribute);
}
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable ( List *pList )
{
	simple_list_genhashtable_gc(NULL,pList);
}

SIMPLE_API void simple_list_genhashtable2 ( List *pList )
{
	simple_list_genhashtable2_gc(NULL,pList);
}
/* Test */

void simple_list_test ( void )
{
	List *pList,*pList2  ;
	int x  ;
	Item *pItem  ;
	String *pString  ;
	char mystr[20]  ;
	printf( "Create new list, size = 10 \n" ) ;
	pList = simple_list_new(10);
	printf( "List(1) size %d    \n", simple_list_getsize(pList) ) ;
	printf( "Create empty list \n" ) ;
	pList2 = simple_list_new(0);
	printf( "adding 15 items to the list \n" ) ;
	for ( x = 1 ; x <= 15 ; x++ ) {
		printf( "x : %d  \n" , x ) ;
		simple_list_newitem(pList2);
	}
	printf( "List(2) size %d    \n", simple_list_getsize(pList2) ) ;
	for ( x = 1 ; x <= 10 ; x++ ) {
		/* Work on items */
		pItem = simple_list_getitem(pList2,x);
		simple_item_settype(pItem,ITEMTYPE_STRING);
		pString = simple_item_getstring(pItem);
		sprintf( mystr , "The Item Number %d" , x ) ;
		simple_string_set(pString,mystr);
		simple_string_print(pString);
	}
	for ( x = 11 ; x <= 15 ; x++ ) {
		/* Work on items */
		pItem = simple_list_getitem(pList2,x);
		simple_item_settype(pItem,ITEMTYPE_NUMBER);
	}
	/* Delete Items */
	printf( "Delete item number 5 \n" ) ;
	simple_list_deleteitem(pList2,5);
	pItem = simple_list_getitem(pList2,5);
	pString = simple_item_getstring(pItem);
	simple_string_print(pString);
	printf( "Delete item number 1 \n" ) ;
	/* Print Item */
	simple_list_deleteitem(pList2,1);
	pItem = simple_list_getitem(pList2,1);
	pString = simple_item_getstring(pItem);
	simple_string_print(pString);
	printf( "Delete item number %d \n",simple_list_getsize(pList2) ) ;
	/* Print Item */
	simple_list_deleteitem(pList2,simple_list_getsize(pList2));
	printf( "get item number %d \n",simple_list_getsize(pList2) ) ;
	/* Delete Lists */
	printf( "Deleting List 1 \n" ) ;
	simple_list_delete(pList);
	printf( "Deleting List 2 \n" ) ;
	simple_list_delete(pList2);
	getchar();
	/* Create/Delete Large List */
	printf( "Create List of 1000000 Items  \n" ) ;
	pList = simple_list_new(1000000);
	printf( "Before Loop  \n" ) ;
	for ( x = 1 ; x <= 1000000 ; x++ ) {
		simple_list_setstring(pList,x,"empty item");
	}
	printf( "Done  \n" ) ;
	getchar();
	printf( "Deleting List 1 \n" ) ;
	simple_list_delete(pList);
	getchar();
	/* Create Nested Lists */
	printf( "List = {'first item',{'item (2) item(1)','item(2) item(2)'},'lastitem' , 50 , Pointer to int } \n  " ) ;
	pList = simple_list_new(5);
	/* Set Item 1 */
	pItem = simple_list_getitem(pList,1);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	simple_string_set(pString,mystr);
	simple_string_print(pString);
	/* Set Item 2 */
	pItem = simple_list_getitem(pList,2);
	simple_item_settype(pItem,ITEMTYPE_LIST);
	pList2 = simple_item_getlist(pItem);
	simple_list_newitem(pList2);
	simple_list_newitem(pList2);
	/* Work on items */
	pItem = simple_list_getitem(pList2,1);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	sprintf( mystr , "Item (2) Item (1) "  ) ;
	simple_string_set(pString,mystr);
	simple_string_print(pString);
	/* Work on items */
	pItem = simple_list_getitem(pList2,2);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	sprintf( mystr , "Item (2) Item (2) "  ) ;
	simple_string_set(pString,mystr);
	simple_string_print(pString);
	/* Set Item 3 */
	pItem = simple_list_getitem(pList,3);
	simple_item_settype(pItem,ITEMTYPE_STRING);
	pString = simple_item_getstring(pItem);
	sprintf( mystr , "last item"  ) ;
	simple_string_set(pString,mystr);
	simple_string_print(pString);
	/* set item 4 */
	pItem = simple_list_getitem(pList,4);
	simple_item_settype(pItem,ITEMTYPE_NUMBER);
	/* set item 5 */
	pItem = simple_list_getitem(pList,5);
	simple_item_settype(pItem,ITEMTYPE_POINTER);
	printf( "Printing list \n  " ) ;
	simple_list_print(pList);
	/* Copy List */
	printf( "\n Copy List1 to List 2 \n  " ) ;
	pList2 = simple_list_new(0);
	simple_list_copy(pList2,pList);
	printf( "\n Printing List 2 \n  " ) ;
	simple_list_print(pList2);
	simple_list_delete(pList2);
	simple_list_delete(pList);
	/* Use list_setstring & list_getstring */
	printf( "\n use simple_list_setstring and simple_list_getstring  \n" ) ;
	pList = simple_list_new(3);
	simple_list_setstring(pList,1,"one");
	simple_list_setstring(pList,2,"two");
	simple_list_setstring(pList,3,"three");
	for ( x = 1 ; x <= 3 ; x++ ) {
		printf( "Item Number %d = %s  \n",x,simple_list_getstring(pList,x) ) ;
	}
	simple_list_delete(pList);
	/* using list_addstring */
	printf( "using simple_list_addstring  \n" ) ;
	pList = simple_list_new(0);
	simple_list_addstring(pList,"item 1");
	simple_list_addstring(pList,"item 2");
	simple_list_addstring(pList,"item 3");
	simple_list_addstring(pList,"item 4");
	simple_list_addstring(pList,"item 5");
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		printf( "Item Number %d = %s  \n",x,simple_list_getstring(pList,x) ) ;
	}
	/* Test Get item */
	printf( "Item Number 1 = %s  \n",simple_list_getstring(pList,1) ) ;
	printf( "Item Number 5 = %s  \n",simple_list_getstring(pList,5) ) ;
	printf( "Item Number 4 = %s  \n",simple_list_getstring(pList,4) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(pList,3) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(pList,3) ) ;
	printf( "Item Number 2 = %s  \n",simple_list_getstring(pList,2) ) ;
	printf( "Item Number 3 = %s  \n",simple_list_getstring(pList,3) ) ;
	simple_list_delete(pList);
	/* Function Pointers */
	pList = simple_list_new(0);
	simple_list_addfuncpointer(pList,simple_list_testfuncpointer);
	puts(" *** Test Function Pointer *** ");
	simple_list_callfuncpointer(pList,1,pList);
	simple_list_delete(pList);
	getchar();
}
