/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
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
**  Functions 
**  Main List Functions 
*/

SIMPLE_API List * simple_list_new_gc ( void *pState,int nSize ) ;

SIMPLE_API List * simple_list_new2_gc ( void *pState,List *pList,int nSize ) ;

SIMPLE_API void simple_list_newitem_gc ( void *pState,List *pList ) ;

void simple_list_test ( void ) ;

SIMPLE_API Item * simple_list_getitem ( List *pList,int index ) ;

SIMPLE_API List * simple_list_delete_gc ( void *pState,List *pList ) ;

SIMPLE_API void simple_list_deleteitem_gc ( void *pState,List *pList,int index ) ;

SIMPLE_API void simple_list_print ( List *pList ) ;

SIMPLE_API int simple_list_gettype ( List *pList, int index ) ;
/* int */

SIMPLE_API void simple_list_setint_gc ( void *pState,List *pList, int index ,int number ) ;

SIMPLE_API void simple_list_addint_gc ( void *pState,List *pList,int x ) ;
/* Pointers */

SIMPLE_API void simple_list_setpointer_gc ( void *pState,List *pList, int index ,void *pValue ) ;

SIMPLE_API void simple_list_addpointer_gc ( void *pState,List *pList,void *pValue ) ;
/* Function Pointers */

SIMPLE_API void simple_list_setfuncpointer_gc ( void *pState,List *pList, int index ,void (*pFunc)(void *) ) ;

SIMPLE_API void simple_list_addfuncpointer_gc ( void *pState,List *pList,void (*pFunc)(void *) ) ;

SIMPLE_API int simple_list_isfuncpointer ( List *pList, int index ) ;

void simple_list_testfuncpointer ( void *pPointer ) ;
/* double */

SIMPLE_API void simple_list_setdouble_gc ( void *pState,List *pList, int index ,double number ) ;

SIMPLE_API void simple_list_adddouble_gc ( void *pState,List *pList,double x ) ;
/* String */

SIMPLE_API void simple_list_setstsimple_gc ( void *pState,List *pList, int index ,const char *str ) ;

SIMPLE_API void simple_list_setstring2_gc ( void *pState,List *pList, int index ,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_addstsimple_gc ( void *pState,List *pList,const char *str ) ;

SIMPLE_API void simple_list_addstring2_gc ( void *pState,List *pList,const char *str,int nStrSize ) ;
/* List */

SIMPLE_API List * simple_list_newlist_gc ( void *pState,List *pList ) ;

SIMPLE_API void simple_list_setlist_gc ( void *pState,List *pList, int index ) ;

SIMPLE_API List * simple_list_getlist ( List *pList, int index ) ;

SIMPLE_API void simple_list_setactiveitem ( List *pList, Items *pItems, int index ) ;

SIMPLE_API void simple_list_copy_gc ( void *pState,List *pNewList, List *pList ) ;

SIMPLE_API int simple_list_isnumber ( List *pList, int index ) ;

SIMPLE_API int simple_list_isstring ( List *pList, int index ) ;

SIMPLE_API int simple_list_islist ( List *pList, int index ) ;

SIMPLE_API int simple_list_ispointer ( List *pList, int index ) ;

SIMPLE_API void simple_list_deleteallitems_gc ( void *pState,List *pList ) ;
/* Insert Items */

SIMPLE_API void simple_list_insertitem_gc ( void *pState,List *pList,int x ) ;

SIMPLE_API void simple_list_insertint_gc ( void *pState,List *pList,int nPos,int x ) ;

SIMPLE_API void simple_list_insertdouble_gc ( void *pState,List *pList,int nPos,double x ) ;

SIMPLE_API void simple_list_insertpointer_gc ( void *pState,List *pList,int nPos,void *pValue ) ;

SIMPLE_API void simple_list_insertstsimple_gc ( void *pState,List *pList,int nPos,const char *str ) ;

SIMPLE_API void simple_list_insertstring2_gc ( void *pState,List *pList,int nPos,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_insertfuncpointer_gc ( void *pState,List *pList,int nPos,void (*pFunc)(void *) ) ;

SIMPLE_API List * simple_list_insertlist_gc ( void *pState,List *pList,int nPos ) ;
/* Is item inside list, support nested Lists */

SIMPLE_API int simple_list_isiteminsidelist ( List *pList,Item *pItem ) ;
/* Linear Search */

SIMPLE_API int simple_list_findstring ( List *pList,const char *str,int nColumn ) ;

SIMPLE_API int simple_list_finddouble ( List *pList,double nNum1,int nColumn ) ;

SIMPLE_API int simple_list_findpointer ( List *pList,void *pPointer ) ;

SIMPLE_API int simple_list_findinlistofobjs ( List *pList,int nType,double nNum1,const char *str,int nColumn,char *cAttribute ) ;

SIMPLE_API int simple_list_findcpointer ( List *pList,List *pValue,int nColumn ) ;
/* Sort and Binary Search */

SIMPLE_API void simple_list_sortnum ( List *pList,int left,int right,int nColumn,const char *cAttribute ) ;

SIMPLE_API void simple_list_sortstr_gc ( void *pState,List *pList,int left,int right,int nColumn,const char *cAttribute ) ;

SIMPLE_API int simple_list_binarysearchnum ( List *pList,double nNum1,int nColumn,const char *cAttribute ) ;

SIMPLE_API int simple_list_binarysearchstr ( List *pList,const char *cFind,int nColumn,const char *cAttribute ) ;

SIMPLE_API void simple_list_swap ( List *pList,int x,int y ) ;

SIMPLE_API double simple_list_getdoublecolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute ) ;

SIMPLE_API char * simple_list_getstringcolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute ) ;
/* List Items to Array */

SIMPLE_API void simple_list_genarray_gc ( void *pState,List *pList ) ;

SIMPLE_API void simple_list_deletearray_gc ( void *pState,List *pList ) ;
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable_gc ( void *pState,List *pList ) ;

SIMPLE_API void simple_list_genhashtable2_gc ( void *pState,List *pList ) ;

SIMPLE_API void simple_list_refcopy ( List *pNewList, List *pList ) ;

SIMPLE_API void simple_list_clear ( List *pList ) ;
/* Delete item from list using the item pointer */

SIMPLE_API int simple_list_deliteminsidelist ( List *pList,Item *pItem ) ;
/* Macro */
#define simple_list_isdouble(pList,index) ( simple_list_getitem(pList,index)->NumberFlag == ITEM_NUMBERFLAG_DOUBLE)
#define simple_list_isint(pList,index) ( simple_list_getitem(pList,index)->NumberFlag == ITEM_NUMBERFLAG_INT )
#define simple_list_deletelastitem(x) simple_list_deleteitem(x,simple_list_getsize(x))
#define simple_list_gethashtable(x) (x->pHashTable)
#define simple_list_getint(pList,index) ( simple_list_getitem(pList,index)->data.iNumber )
#define simple_list_getpointer(pList,index) ( simple_list_getitem(pList,index)->data.pPointer )
#define simple_list_getfuncpointer(pList,index) ( simple_list_getitem(pList,index)->data.pFunc )
#define simple_list_callfuncpointer(pList,index,x) ( simple_list_getitem(pList,index)->data.pFunc(x) )
#define simple_list_getdouble(pList,index) simple_list_getitem(pList,index)->data.dNumber
#define simple_list_getstring(pList,index) ( simple_stsimple_get(simple_item_getstring(simple_list_getitem(pList,index))) )
#define simple_list_getstringobject(pList,index) ( simple_item_getstring(simple_list_getitem(pList,index)) )
#define simple_list_getstringsize(pList,index) ( simple_stsimple_size(simple_item_getstring(simple_list_getitem(pList,index))) )
#define simple_list_getsize(x) (x->nSize)
#define SIMPLE_VM_LISTOFOBJS_FINDSTRING 1
#define SIMPLE_VM_LISTOFOBJS_FINDNUMBER 0
#define simple_list_deletelastitem_gc(s,x) simple_list_deleteitem_gc(s,x,simple_list_getsize(x))
/* Define functions without RingState * */

SIMPLE_API List * simple_list_new ( int nSize ) ;

SIMPLE_API void simple_list_genarray ( List *pList ) ;

SIMPLE_API List * simple_list_delete ( List *pList ) ;

SIMPLE_API void simple_list_deletearray ( List *pList ) ;

SIMPLE_API void simple_list_newitem ( List *pList ) ;

SIMPLE_API void simple_list_deleteitem ( List *pList,int index ) ;
/* int */

SIMPLE_API void simple_list_setint ( List *pList, int index ,int number ) ;

SIMPLE_API void simple_list_addint ( List *pList,int x ) ;
/* Pointers */

SIMPLE_API void simple_list_setpointer ( List *pList, int index ,void *pValue ) ;

SIMPLE_API void simple_list_addpointer ( List *pList,void *pValue ) ;
/* Function Pointers */

SIMPLE_API void simple_list_setfuncpointer ( List *pList, int index ,void (*pFunc)(void *) ) ;

SIMPLE_API void simple_list_addfuncpointer ( List *pList,void (*pFunc)(void *) ) ;
/* double */

SIMPLE_API void simple_list_setdouble ( List *pList, int index ,double number ) ;

SIMPLE_API void simple_list_adddouble ( List *pList,double x ) ;
/* String */

SIMPLE_API void simple_list_setstring ( List *pList, int index ,const char *str ) ;

SIMPLE_API void simple_list_setstring2 ( List *pList, int index ,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_addstring ( List *pList,const char *str ) ;

SIMPLE_API void simple_list_addstring2 ( List *pList,const char *str,int nStrSize ) ;
/* List */

SIMPLE_API List * simple_list_newlist ( List *pList ) ;

SIMPLE_API void simple_list_setlist ( List *pList, int index ) ;

SIMPLE_API void simple_list_copy ( List *pNewList, List *pList ) ;

SIMPLE_API void simple_list_deleteallitems ( List *pList ) ;
/* Insert Items */

SIMPLE_API void simple_list_insertitem ( List *pList,int x ) ;

SIMPLE_API void simple_list_insertint ( List *pList,int nPos,int x ) ;

SIMPLE_API void simple_list_insertdouble ( List *pList,int nPos,double x ) ;

SIMPLE_API void simple_list_insertpointer ( List *pList,int nPos,void *pValue ) ;

SIMPLE_API void simple_list_insertstring ( List *pList,int nPos,const char *str ) ;

SIMPLE_API void simple_list_insertstring2 ( List *pList,int nPos,const char *str,int nStrSize ) ;

SIMPLE_API void simple_list_insertfuncpointer ( List *pList,int nPos,void (*pFunc)(void *) ) ;

SIMPLE_API List * simple_list_insertlist ( List *pList,int nPos ) ;

SIMPLE_API void simple_list_sortstr ( List *pList,int left,int right,int nColumn,const char *cAttribute ) ;
/* List Items to HashTable */

SIMPLE_API void simple_list_genhashtable ( List *pList ) ;

SIMPLE_API void simple_list_genhashtable2 ( List *pList ) ;
#endif
