
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


#ifndef simple_list_h
#define simple_list_h
/* Data */
typedef struct List {
	struct Items *pFirst  ;
	struct Items *pLast  ;
	int nSize  ;
	int nNextItemAfterLastAccess  ;
	struct Items *pLastItemLastAccess  ;
	struct Item **pItemsArray  ;
	struct HashTable *pHashTable  ;
} List ;
/*
**  Blocks 
**  Main List Blocks 
*/

SIMPLE_API List * simple_list_new_gc ( void *pState,int nSize ) ;

SIMPLE_API List * simple_list_new2_gc ( void *pState,List *list,int nSize ) ;

SIMPLE_API void simple_list_newitem_gc ( void *pState,List *list ) ;

void simple_list_test ( void ) ;

SIMPLE_API Item * simple_list_getitem ( List *list,int index ) ;

SIMPLE_API List * simple_list_delete_gc ( void *pState,List *list ) ;

SIMPLE_API void simple_list_deleteitem_gc ( void *pState,List *list,int index ) ;

SIMPLE_API void simple_list_print ( List *list ) ;

SIMPLE_API int simple_list_gettype ( List *list, int index ) ;
/* int */

SIMPLE_API void simple_list_setint_gc ( void *pState,List *list, int index ,int number ) ;

SIMPLE_API void simple_list_addint_gc ( void *pState,List *list,int x ) ;
/* Pointers */

SIMPLE_API void simple_list_setpointer_gc ( void *pState,List *list, int index ,void *pValue ) ;

SIMPLE_API void simple_list_addpointer_gc ( void *pState,List *list,void *pValue ) ;
/* Block Pointers */

SIMPLE_API void simple_list_setfuncpointer_gc ( void *pState,List *list, int index ,void (*pFunc)(void *) ) ;

SIMPLE_API void simple_list_addfuncpointer_gc ( void *pState,List *list,void (*pFunc)(void *) ) ;

SIMPLE_API int simple_list_isfuncpointer ( List *list, int index ) ;

void simple_list_testfuncpointer ( void *pointer ) ;
/* double */

SIMPLE_API void simple_list_setdouble_gc ( void *pState,List *list, int index ,double number ) ;

SIMPLE_API void simple_list_adddouble_gc ( void *pState,List *list,double x ) ;
/* String */

SIMPLE_API void simple_list_setstsimple_gc ( void *pState,List *list, int index ,const char *str ) ;

SIMPLE_API void simple_list_setstring2_gc ( void *pState,List *list, int index ,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_addstring_gc ( void *pState,List *list,const char *str ) ;

SIMPLE_API void simple_list_addstring2_gc ( void *pState,List *list,const char *str,int nStrSize ) ;
/* List */

SIMPLE_API List * simple_list_newlist_gc ( void *pState,List *list ) ;

SIMPLE_API void simple_list_setlist_gc ( void *pState,List *list, int index ) ;

SIMPLE_API List * simple_list_getlist ( List *list, int index ) ;

SIMPLE_API void simple_list_setactiveitem ( List *list, Items *pItems, int index ) ;

SIMPLE_API void simple_list_copy_gc ( void *pState,List *pNewList, List *list ) ;

SIMPLE_API int simple_list_isnumber ( List *list, int index ) ;

SIMPLE_API int simple_list_isstring ( List *list, int index ) ;

SIMPLE_API int simple_list_islist ( List *list, int index ) ;

SIMPLE_API int simple_list_ispointer ( List *list, int index ) ;

SIMPLE_API void simple_list_deleteallitems_gc ( void *pState,List *list ) ;
/* Insert Items */

SIMPLE_API void simple_list_insertitem_gc ( void *pState,List *list,int x ) ;

SIMPLE_API void simple_list_insertint_gc ( void *pState,List *list,int nPos,int x ) ;

SIMPLE_API void simple_list_insertdouble_gc ( void *pState,List *list,int nPos,double x ) ;

SIMPLE_API void simple_list_insertpointer_gc ( void *pState,List *list,int nPos,void *pValue ) ;

SIMPLE_API void simple_list_insertstsimple_gc ( void *pState,List *list,int nPos,const char *str ) ;

SIMPLE_API void simple_list_insertstring2_gc ( void *pState,List *list,int nPos,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_insertfuncpointer_gc ( void *pState,List *list,int nPos,void (*pFunc)(void *) ) ;

SIMPLE_API List * simple_list_insertlist_gc ( void *pState,List *list,int nPos ) ;
/* Is item inside list, support nested Lists */

SIMPLE_API int simple_list_isiteminsidelist ( List *list,Item *pItem ) ;
/* Linear Search */

SIMPLE_API int simple_list_findstring ( List *list,const char *str,int nColumn ) ;

SIMPLE_API int simple_list_finddouble ( List *list,double nNum1,int nColumn ) ;

SIMPLE_API int simple_list_findpointer ( List *list,void *pointer ) ;

SIMPLE_API int simple_list_findinlistofobjs ( List *list,int nType,double nNum1,const char *str,int nColumn,char *cAttribute ) ;

SIMPLE_API int simple_list_findcpointer ( List *list,List *pValue,int nColumn ) ;
/* Sort and Binary Search */

SIMPLE_API void simple_list_sortnum ( List *list,int left,int right,int nColumn,const char *cAttribute ) ;

SIMPLE_API void simple_list_sortstr_gc ( void *pState,List *list,int left,int right,int nColumn,const char *cAttribute ) ;

SIMPLE_API int simple_list_binarysearchnum ( List *list,double nNum1,int nColumn,const char *cAttribute ) ;

SIMPLE_API int simple_list_binarysearchstr ( List *list,const char *cFind,int nColumn,const char *cAttribute ) ;

SIMPLE_API void simple_list_swap ( List *list,int x,int y ) ;

SIMPLE_API double simple_list_getdoublecolumn ( List *list,int nIndex,int nColumn,const char *cAttribute ) ;

SIMPLE_API char * simple_list_getstringcolumn ( List *list,int nIndex,int nColumn,const char *cAttribute ) ;
/* List Items to Array */

SIMPLE_API void simple_list_genarray_gc ( void *pState,List *list ) ;

SIMPLE_API void simple_list_deletearray_gc ( void *pState,List *list ) ;
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable_gc ( void *pState,List *list ) ;

SIMPLE_API void simple_list_genhashtable2_gc ( void *pState,List *list ) ;

SIMPLE_API void simple_list_refcopy ( List *pNewList, List *list ) ;

SIMPLE_API void simple_list_clear ( List *list ) ;
/* Delete item from list using the item pointer */

SIMPLE_API int simple_list_deliteminsidelist ( List *list,Item *pItem ) ;
/* Macro */
#define simple_list_isdouble(list,index) ( simple_list_getitem(list,index)->NumberFlag == ITEM_NUMBERFLAG_DOUBLE)
#define simple_list_isint(list,index) ( simple_list_getitem(list,index)->NumberFlag == ITEM_NUMBERFLAG_INT )
#define simple_list_deletelastitem(x) simple_list_deleteitem(x,simple_list_getsize(x))
#define simple_list_gethashtable(x) (x->pHashTable)
#define simple_list_getint(list,index) ( simple_list_getitem(list,index)->data.iNumber )
#define simple_list_getpointer(list,index) ( simple_list_getitem(list,index)->data.pointer )
#define simple_list_getfuncpointer(list,index) ( simple_list_getitem(list,index)->data.pFunc )
#define simple_list_callfuncpointer(list,index,x) ( simple_list_getitem(list,index)->data.pFunc(x) )
#define simple_list_getdouble(list,index) simple_list_getitem(list,index)->data.dNumber
#define simple_list_getstring(list,index) ( simple_string_get(simple_item_getstring(simple_list_getitem(list,index))) )
#define simple_list_getstringobject(list,index) ( simple_item_getstring(simple_list_getitem(list,index)) )
#define simple_list_getstringsize(list,index) ( simple_string_size(simple_item_getstring(simple_list_getitem(list,index))) )
#define simple_list_getsize(x) (x->nSize)
#define SIMPLE_VM_LISTOFOBJS_FINDSTRING 1
#define SIMPLE_VM_LISTOFOBJS_FINDNUMBER 0
#define simple_list_deletelastitem_gc(s,x) simple_list_deleteitem_gc(s,x,simple_list_getsize(x))
/* Define blocks without SimpleState * */

SIMPLE_API List * simple_list_new ( int nSize ) ;

SIMPLE_API void simple_list_genarray ( List *list ) ;

SIMPLE_API List * simple_list_delete ( List *list ) ;

SIMPLE_API void simple_list_deletearray ( List *list ) ;

SIMPLE_API void simple_list_newitem ( List *list ) ;

SIMPLE_API void simple_list_deleteitem ( List *list,int index ) ;
/* int */

SIMPLE_API void simple_list_setint ( List *list, int index ,int number ) ;

SIMPLE_API void simple_list_addint ( List *list,int x ) ;
/* Pointers */

SIMPLE_API void simple_list_setpointer ( List *list, int index ,void *pValue ) ;

SIMPLE_API void simple_list_addpointer ( List *list,void *pValue ) ;
/* Block Pointers */

SIMPLE_API void simple_list_setfuncpointer ( List *list, int index ,void (*pFunc)(void *) ) ;

SIMPLE_API void simple_list_addfuncpointer ( List *list,void (*pFunc)(void *) ) ;
/* double */

SIMPLE_API void simple_list_setdouble ( List *list, int index ,double number ) ;

SIMPLE_API void simple_list_adddouble ( List *list,double x ) ;
/* String */

SIMPLE_API void simple_list_setstring ( List *list, int index ,const char *str ) ;

SIMPLE_API void simple_list_setstring2 ( List *list, int index ,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_addstring ( List *list,const char *str ) ;

SIMPLE_API void simple_list_addstring2 ( List *list,const char *str,int nStrSize ) ;
/* List */

SIMPLE_API List * simple_list_newlist ( List *list ) ;

SIMPLE_API void simple_list_setlist ( List *list, int index ) ;

SIMPLE_API void simple_list_copy ( List *pNewList, List *list ) ;

SIMPLE_API void simple_list_deleteallitems ( List *list ) ;
/* Insert Items */

SIMPLE_API void simple_list_insertitem ( List *list,int x ) ;

SIMPLE_API void simple_list_insertint ( List *list,int nPos,int x ) ;

SIMPLE_API void simple_list_insertdouble ( List *list,int nPos,double x ) ;

SIMPLE_API void simple_list_insertpointer ( List *list,int nPos,void *pValue ) ;

SIMPLE_API void simple_list_insertstring ( List *list,int nPos,const char *str ) ;

SIMPLE_API void simple_list_insertstring2 ( List *list,int nPos,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_insertfuncpointer ( List *list,int nPos,void (*pFunc)(void *) ) ;

SIMPLE_API List * simple_list_insertlist ( List *list,int nPos ) ;

SIMPLE_API void simple_list_sortstr ( List *list,int left,int right,int nColumn,const char *cAttribute ) ;
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable ( List *list ) ;

SIMPLE_API void simple_list_genhashtable2 ( List *list ) ;
#endif
