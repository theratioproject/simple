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

RING_API List * simple_list_new_gc ( void *pState,int nSize ) ;

RING_API List * simple_list_new2_gc ( void *pState,List *pList,int nSize ) ;

RING_API void simple_list_newitem_gc ( void *pState,List *pList ) ;

void simple_list_test ( void ) ;

RING_API Item * simple_list_getitem ( List *pList,int index ) ;

RING_API List * simple_list_delete_gc ( void *pState,List *pList ) ;

RING_API void simple_list_deleteitem_gc ( void *pState,List *pList,int index ) ;

RING_API void simple_list_print ( List *pList ) ;

RING_API int simple_list_gettype ( List *pList, int index ) ;
/* int */

RING_API void simple_list_setint_gc ( void *pState,List *pList, int index ,int number ) ;

RING_API void simple_list_addint_gc ( void *pState,List *pList,int x ) ;
/* Pointers */

RING_API void simple_list_setpointer_gc ( void *pState,List *pList, int index ,void *pValue ) ;

RING_API void simple_list_addpointer_gc ( void *pState,List *pList,void *pValue ) ;
/* Function Pointers */

RING_API void simple_list_setfuncpointer_gc ( void *pState,List *pList, int index ,void (*pFunc)(void *) ) ;

RING_API void simple_list_addfuncpointer_gc ( void *pState,List *pList,void (*pFunc)(void *) ) ;

RING_API int simple_list_isfuncpointer ( List *pList, int index ) ;

void simple_list_testfuncpointer ( void *pPointer ) ;
/* double */

RING_API void simple_list_setdouble_gc ( void *pState,List *pList, int index ,double number ) ;

RING_API void simple_list_adddouble_gc ( void *pState,List *pList,double x ) ;
/* Stsimple */

RING_API void simple_list_setstsimple_gc ( void *pState,List *pList, int index ,const char *str ) ;

RING_API void simple_list_setstsimple2_gc ( void *pState,List *pList, int index ,const char *str,int nStrSize ) ;

RING_API void simple_list_addstsimple_gc ( void *pState,List *pList,const char *str ) ;

RING_API void simple_list_addstsimple2_gc ( void *pState,List *pList,const char *str,int nStrSize ) ;
/* List */

RING_API List * simple_list_newlist_gc ( void *pState,List *pList ) ;

RING_API void simple_list_setlist_gc ( void *pState,List *pList, int index ) ;

RING_API List * simple_list_getlist ( List *pList, int index ) ;

RING_API void simple_list_setactiveitem ( List *pList, Items *pItems, int index ) ;

RING_API void simple_list_copy_gc ( void *pState,List *pNewList, List *pList ) ;

RING_API int simple_list_isnumber ( List *pList, int index ) ;

RING_API int simple_list_isstsimple ( List *pList, int index ) ;

RING_API int simple_list_islist ( List *pList, int index ) ;

RING_API int simple_list_ispointer ( List *pList, int index ) ;

RING_API void simple_list_deleteallitems_gc ( void *pState,List *pList ) ;
/* Insert Items */

RING_API void simple_list_insertitem_gc ( void *pState,List *pList,int x ) ;

RING_API void simple_list_insertint_gc ( void *pState,List *pList,int nPos,int x ) ;

RING_API void simple_list_insertdouble_gc ( void *pState,List *pList,int nPos,double x ) ;

RING_API void simple_list_insertpointer_gc ( void *pState,List *pList,int nPos,void *pValue ) ;

RING_API void simple_list_insertstsimple_gc ( void *pState,List *pList,int nPos,const char *str ) ;

RING_API void simple_list_insertstsimple2_gc ( void *pState,List *pList,int nPos,const char *str,int nStrSize ) ;

RING_API void simple_list_insertfuncpointer_gc ( void *pState,List *pList,int nPos,void (*pFunc)(void *) ) ;

RING_API List * simple_list_insertlist_gc ( void *pState,List *pList,int nPos ) ;
/* Is item inside list, support nested Lists */

RING_API int simple_list_isiteminsidelist ( List *pList,Item *pItem ) ;
/* Linear Search */

RING_API int simple_list_findstsimple ( List *pList,const char *str,int nColumn ) ;

RING_API int simple_list_finddouble ( List *pList,double nNum1,int nColumn ) ;

RING_API int simple_list_findpointer ( List *pList,void *pPointer ) ;

RING_API int simple_list_findinlistofobjs ( List *pList,int nType,double nNum1,const char *str,int nColumn,char *cAttribute ) ;

RING_API int simple_list_findcpointer ( List *pList,List *pValue,int nColumn ) ;
/* Sort and Binary Search */

RING_API void simple_list_sortnum ( List *pList,int left,int right,int nColumn,const char *cAttribute ) ;

RING_API void simple_list_sortstr_gc ( void *pState,List *pList,int left,int right,int nColumn,const char *cAttribute ) ;

RING_API int simple_list_binarysearchnum ( List *pList,double nNum1,int nColumn,const char *cAttribute ) ;

RING_API int simple_list_binarysearchstr ( List *pList,const char *cFind,int nColumn,const char *cAttribute ) ;

RING_API void simple_list_swap ( List *pList,int x,int y ) ;

RING_API double simple_list_getdoublecolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute ) ;

RING_API char * simple_list_getstsimplecolumn ( List *pList,int nIndex,int nColumn,const char *cAttribute ) ;
/* List Items to Array */

RING_API void simple_list_genarray_gc ( void *pState,List *pList ) ;

RING_API void simple_list_deletearray_gc ( void *pState,List *pList ) ;
/* List Items to HashTable */

RING_API void simple_list_genhashtable_gc ( void *pState,List *pList ) ;

RING_API void simple_list_genhashtable2_gc ( void *pState,List *pList ) ;

RING_API void simple_list_refcopy ( List *pNewList, List *pList ) ;

RING_API void simple_list_clear ( List *pList ) ;
/* Delete item from list using the item pointer */

RING_API int simple_list_deliteminsidelist ( List *pList,Item *pItem ) ;
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
#define simple_list_getstsimple(pList,index) ( simple_stsimple_get(simple_item_getstsimple(simple_list_getitem(pList,index))) )
#define simple_list_getstsimpleobject(pList,index) ( simple_item_getstsimple(simple_list_getitem(pList,index)) )
#define simple_list_getstsimplesize(pList,index) ( simple_stsimple_size(simple_item_getstsimple(simple_list_getitem(pList,index))) )
#define simple_list_getsize(x) (x->nSize)
#define RING_VM_LISTOFOBJS_FINDSTRING 1
#define RING_VM_LISTOFOBJS_FINDNUMBER 0
#define simple_list_deletelastitem_gc(s,x) simple_list_deleteitem_gc(s,x,simple_list_getsize(x))
/* Define functions without RingState * */

RING_API List * simple_list_new ( int nSize ) ;

RING_API void simple_list_genarray ( List *pList ) ;

RING_API List * simple_list_delete ( List *pList ) ;

RING_API void simple_list_deletearray ( List *pList ) ;

RING_API void simple_list_newitem ( List *pList ) ;

RING_API void simple_list_deleteitem ( List *pList,int index ) ;
/* int */

RING_API void simple_list_setint ( List *pList, int index ,int number ) ;

RING_API void simple_list_addint ( List *pList,int x ) ;
/* Pointers */

RING_API void simple_list_setpointer ( List *pList, int index ,void *pValue ) ;

RING_API void simple_list_addpointer ( List *pList,void *pValue ) ;
/* Function Pointers */

RING_API void simple_list_setfuncpointer ( List *pList, int index ,void (*pFunc)(void *) ) ;

RING_API void simple_list_addfuncpointer ( List *pList,void (*pFunc)(void *) ) ;
/* double */

RING_API void simple_list_setdouble ( List *pList, int index ,double number ) ;

RING_API void simple_list_adddouble ( List *pList,double x ) ;
/* Stsimple */

RING_API void simple_list_setstsimple ( List *pList, int index ,const char *str ) ;

RING_API void simple_list_setstsimple2 ( List *pList, int index ,const char *str,int nStrSize ) ;

RING_API void simple_list_addstsimple ( List *pList,const char *str ) ;

RING_API void simple_list_addstsimple2 ( List *pList,const char *str,int nStrSize ) ;
/* List */

RING_API List * simple_list_newlist ( List *pList ) ;

RING_API void simple_list_setlist ( List *pList, int index ) ;

RING_API void simple_list_copy ( List *pNewList, List *pList ) ;

RING_API void simple_list_deleteallitems ( List *pList ) ;
/* Insert Items */

RING_API void simple_list_insertitem ( List *pList,int x ) ;

RING_API void simple_list_insertint ( List *pList,int nPos,int x ) ;

RING_API void simple_list_insertdouble ( List *pList,int nPos,double x ) ;

RING_API void simple_list_insertpointer ( List *pList,int nPos,void *pValue ) ;

RING_API void simple_list_insertstsimple ( List *pList,int nPos,const char *str ) ;

RING_API void simple_list_insertstsimple2 ( List *pList,int nPos,const char *str,int nStrSize ) ;

RING_API void simple_list_insertfuncpointer ( List *pList,int nPos,void (*pFunc)(void *) ) ;

RING_API List * simple_list_insertlist ( List *pList,int nPos ) ;

RING_API void simple_list_sortstr ( List *pList,int left,int right,int nColumn,const char *cAttribute ) ;
/* List Items to HashTable */

RING_API void simple_list_genhashtable ( List *pList ) ;

RING_API void simple_list_genhashtable2 ( List *pList ) ;
#endif
