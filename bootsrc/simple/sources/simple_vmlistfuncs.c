/*
**  Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> 
**  Include Files 
*/
#include "../includes/simple.h"
/* Load Functions */

void simple_vm_listfuncs_loadfunctions ( RingState *pRingState )
{
	/* Lists */
	simple_vm_funcregister("list",simple_vmlib_list);
	simple_vm_funcregister("find",simple_vmlib_find);
	simple_vm_funcregister("min",simple_vmlib_min);
	simple_vm_funcregister("max",simple_vmlib_max);
	simple_vm_funcregister("insert",simple_vmlib_insert);
	simple_vm_funcregister("sort",simple_vmlib_sort);
	simple_vm_funcregister("reverse",simple_vmlib_reverse);
	simple_vm_funcregister("binarysearch",simple_vmlib_binarysearch);
}
/* Functions */

void simple_vmlib_list ( void *pPointer )
{
	List *pList  ;
	int x,nSize  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		nSize = SIMPLE_API_GETNUMBER(1) ;
		if ( nSize > 0 ) {
			pList = SIMPLE_API_NEWLIST ;
			for ( x = 1 ; x <=nSize ; x++ ) {
				simple_list_adddouble(pList,0.0);
			}
			SIMPLE_API_RETLIST(pList);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
/*
**  Find() Usage Syntax 
**  Find(List,ItemValue) ----> Item Index 
**  Find(List,ItemValue,nColumn) ---> Item Index 
**  Find(List,ItemValue,nColumn,cProperty) ---> Item Index 
*/

void simple_vmlib_find ( void *pPointer )
{
	int nNum1,nColumn  ;
	List *pList  ;
	if ( ! ( (SIMPLE_API_PARACOUNT >= 2) && (SIMPLE_API_PARACOUNT <= 4) ) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		nNum1 = 0 ;
		pList = SIMPLE_API_GETLIST(1) ;
		if ( simple_list_getsize(pList) > 0 ) {
			nColumn = 0 ;
			if ( SIMPLE_API_PARACOUNT >= 3 ) {
				if ( SIMPLE_API_ISNUMBER(3) ) {
					nColumn = SIMPLE_API_GETNUMBER(3) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
			}
			if ( SIMPLE_API_PARACOUNT == 4 ) {
				if ( SIMPLE_API_ISSTRING(4) ) {
					if ( SIMPLE_API_ISSTRING(2) ) {
						nNum1 = simple_list_findinlistofobjs(pList,SIMPLE_VM_LISTOFOBJS_FINDSTRING,0.0,SIMPLE_API_GETSTRING(2),nColumn,SIMPLE_API_GETSTRING(4));
					}
					else if ( SIMPLE_API_ISNUMBER(2) ) {
						nNum1 = simple_list_findinlistofobjs(pList,SIMPLE_VM_LISTOFOBJS_FINDNUMBER,SIMPLE_API_GETNUMBER(2),"",nColumn,SIMPLE_API_GETSTRING(4));
					}
					else {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					}
					if ( nNum1 == -1 ) {
						SIMPLE_API_ERROR(SIMPLE_VM_ERROR_PROPERTYNOTFOUND);
					}
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
			}
			else {
				if ( SIMPLE_API_ISSTRING(2) ) {
					nNum1 = simple_list_findstring(pList,SIMPLE_API_GETSTRING(2),nColumn);
				}
				else if ( SIMPLE_API_ISNUMBER(2) ) {
					nNum1 = simple_list_finddouble(pList,SIMPLE_API_GETNUMBER(2),nColumn);
				}
				else if ( SIMPLE_API_ISCPOINTER(2) ) {
					nNum1 = simple_list_findcpointer(pList,SIMPLE_API_GETLIST(2),nColumn);
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
				if ( nNum1 == -1 ) {
					SIMPLE_API_ERROR(SIMPLE_VM_ERROR_BADCOLUMNNUMBER);
				}
			}
		}
		SIMPLE_API_RETNUMBER(nNum1);
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_min ( void *pPointer )
{
	double nNum1  ;
	List *pList  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISLIST(1) ) {
			pList = SIMPLE_API_GETLIST(1) ;
			if ( simple_list_getsize(pList) > 0 ) {
				if ( simple_list_isnumber(pList,1) ) {
					nNum1 = simple_list_getdouble(pList,1) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					return ;
				}
				if ( simple_list_getsize(pList) > 1 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
						if ( simple_list_isnumber(pList,x) ) {
							if ( simple_list_getdouble(pList,x) < nNum1 ) {
								nNum1 = simple_list_getdouble(pList,x) ;
							}
						}
						else {
							SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
							return ;
						}
					}
				}
				SIMPLE_API_RETNUMBER(nNum1);
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_EMPTYLIST);
				return ;
			}
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else if ( SIMPLE_API_PARACOUNT == 2 ) {
		if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
			if ( SIMPLE_API_GETNUMBER(1) < SIMPLE_API_GETNUMBER(2) ) {
				SIMPLE_API_RETNUMBER(SIMPLE_API_GETNUMBER(1));
			}
			else {
				SIMPLE_API_RETNUMBER(SIMPLE_API_GETNUMBER(2));
			}
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
	}
}

void simple_vmlib_max ( void *pPointer )
{
	double nNum1  ;
	List *pList  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISLIST(1) ) {
			pList = SIMPLE_API_GETLIST(1) ;
			if ( simple_list_getsize(pList) > 0 ) {
				if ( simple_list_isnumber(pList,1) ) {
					nNum1 = simple_list_getdouble(pList,1) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					return ;
				}
				if ( simple_list_getsize(pList) > 1 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
						if ( simple_list_isnumber(pList,x) ) {
							if ( simple_list_getdouble(pList,x) > nNum1 ) {
								nNum1 = simple_list_getdouble(pList,x) ;
							}
						}
						else {
							SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
							return ;
						}
					}
				}
				SIMPLE_API_RETNUMBER(nNum1);
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_EMPTYLIST);
				return ;
			}
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else if ( SIMPLE_API_PARACOUNT == 2 ) {
		if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
			if ( SIMPLE_API_GETNUMBER(1) > SIMPLE_API_GETNUMBER(2) ) {
				SIMPLE_API_RETNUMBER(SIMPLE_API_GETNUMBER(1));
			}
			else {
				SIMPLE_API_RETNUMBER(SIMPLE_API_GETNUMBER(2));
			}
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
	}
}

void simple_vmlib_insert ( void *pPointer )
{
	List *pList, *pList2  ;
	int nPos  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISNUMBER(2) ) {
		pList = SIMPLE_API_GETLIST(1) ;
		nPos = (int) SIMPLE_API_GETNUMBER(2) ;
		if ( (nPos < 0) || (nPos > simple_list_getsize(pList) ) ) {
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
			return ;
		}
		if ( SIMPLE_API_ISSTRING(3) ) {
			simple_list_insertstring2(pList,nPos,SIMPLE_API_GETSTRING(3),SIMPLE_API_GETSTRINGSIZE(3));
		}
		else if ( SIMPLE_API_ISNUMBER(3) ) {
			simple_list_insertdouble(pList,nPos,SIMPLE_API_GETNUMBER(3));
		}
		else if ( SIMPLE_API_ISLIST(3) ) {
			pList2 = simple_list_insertlist(pList,nPos);
			simple_list_copy(pList2,SIMPLE_API_GETLIST(3));
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
/* Quicksort Algorithm */

void simple_vmlib_sort ( void *pPointer )
{
	List *pList, *pList2, *pList3  ;
	int x,nParaCount,nColumn,nPos  ;
	char *cAttribute  ;
	nParaCount = SIMPLE_API_PARACOUNT ;
	if ( ! ( (nParaCount >= 1) && (nParaCount <= 3) ) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_NEWLIST ;
		pList2 = SIMPLE_API_GETLIST(1);
		simple_list_copy(pList,pList2);
		if ( simple_list_getsize(pList) < 2 ) {
			SIMPLE_API_RETLIST(pList2);
			return ;
		}
		if ( nParaCount == 1 ) {
			if ( simple_list_isnumber(pList,1) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( ! simple_list_isnumber(pList,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortnum(pList,1,simple_list_getsize(pList),0,"");
			}
			else if ( simple_list_isstring(pList,1) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( ! simple_list_isstring(pList,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortstr(pList,1,simple_list_getsize(pList),0,"");
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else if ( (nParaCount == 2) && SIMPLE_API_ISNUMBER(2) && simple_list_islist(pList,1) ) {
			nColumn = SIMPLE_API_GETNUMBER(2) ;
			pList3 = simple_list_getlist(pList,1);
			if ( simple_list_isnumber(pList3,nColumn) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					pList3 = simple_list_getlist(pList,x);
					if ( ! simple_list_isnumber(pList3,nColumn) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortnum(pList,1,simple_list_getsize(pList),nColumn,"");
			}
			else if ( simple_list_isstring(pList3,nColumn) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					pList3 = simple_list_getlist(pList,x);
					if ( ! simple_list_isstring(pList3,nColumn) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortstr(pList,1,simple_list_getsize(pList),nColumn,"");
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else if ( (nParaCount == 3) && SIMPLE_API_ISNUMBER(2) && simple_list_islist(pList,1) && SIMPLE_API_ISSTRING(3) ) {
			nColumn = SIMPLE_API_GETNUMBER(2) ;
			cAttribute = SIMPLE_API_GETSTRING(3) ;
			simple_stsimple_lower(cAttribute);
			pList3 = simple_list_getlist(pList,1);
			if ( nColumn > 1 ) {
				pList3 = simple_list_getlist(pList3,nColumn);
			}
			if ( simple_vm_oop_isobject(pList3) ) {
				nPos = simple_list_findstring(simple_list_getlist(pList3,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				if ( nPos == 0 ) {
					SIMPLE_API_ERROR(SIMPLE_VM_ERROR_PROPERTYNOTFOUND);
					return ;
				}
				pList3 = simple_list_getlist(pList3,SIMPLE_OBJECT_OBJECTDATA) ;
				pList3 = simple_list_getlist(pList3,nPos) ;
				if ( simple_list_isstring(pList3,SIMPLE_VAR_VALUE) ) {
					simple_list_sortstr(pList,1,simple_list_getsize(pList),nColumn,cAttribute);
				}
				else if ( simple_list_isnumber(pList3,SIMPLE_VAR_VALUE) ) {
					simple_list_sortnum(pList,1,simple_list_getsize(pList),nColumn,cAttribute);
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
		SIMPLE_API_RETLIST(pList);
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
/* Binary Search */

void simple_vmlib_binarysearch ( void *pPointer )
{
	List *pList, *pList2  ;
	int x,nParaCount,nColumn  ;
	nParaCount = SIMPLE_API_PARACOUNT ;
	if ( (nParaCount != 2) && (nParaCount != 3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_GETLIST(1);
		if ( pList->pItemsArray == NULL ) {
			simple_list_genarray(pList);
		}
		if ( nParaCount == 2 ) {
			if ( SIMPLE_API_ISSTRING(2) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( ! simple_list_isstring(pList,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchstr(pList,SIMPLE_API_GETSTRING(2),0,""));
			}
			else if ( SIMPLE_API_ISNUMBER(2) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( ! simple_list_isnumber(pList,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchnum(pList,SIMPLE_API_GETNUMBER(2),0,""));
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else {
			nColumn = SIMPLE_API_GETNUMBER(3) ;
			if ( SIMPLE_API_ISSTRING(2) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					pList2 = simple_list_getlist(pList,x);
					if ( ! simple_list_isstring(pList2,nColumn) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchstr(pList,SIMPLE_API_GETSTRING(2),nColumn,""));
			}
			else if ( SIMPLE_API_ISNUMBER(2) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					pList2 = simple_list_getlist(pList,x);
					if ( ! simple_list_isnumber(pList2,nColumn) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchnum(pList,SIMPLE_API_GETNUMBER(2),nColumn,""));
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_reverse ( void *pPointer )
{
	List *pList,*pList2,*pList3  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		pList = SIMPLE_API_NEWLIST ;
		pList2 = SIMPLE_API_GETLIST(1) ;
		for ( x = simple_list_getsize(pList2) ; x >= 1 ; x-- ) {
			if ( simple_list_isstring(pList2,x) ) {
				simple_list_addstring(pList,simple_list_getstring(pList2,x));
			}
			else if ( simple_list_isnumber(pList2,x) ) {
				simple_list_adddouble(pList,simple_list_getdouble(pList2,x));
			}
			else if ( simple_list_islist(pList2,x) ) {
				pList3 = simple_list_newlist_gc(((VM *) pPointer)->pRingState,pList);
				simple_list_copy(pList3,simple_list_getlist(pList2,x));
			}
		}
		SIMPLE_API_RETLIST(pList);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
