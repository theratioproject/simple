
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   mathic.h 
 * Author: thecarisma
 *
 * Created on Febuary 7, 2018, 3:23 AM
 */

#include "../../../simple/includes/simple.h"
#include "core_dynamic_module.h"

#ifdef _WIN32
	#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
	/* List */
	register_block("__del_from_List",list_delete_from_list);
	register_block("__find_in_list",list_find_in_list);
	register_block("__min_value",list_min_value);
	register_block("__max_value",list_max_value);
	register_block("__insert_into_list",list_insert_into_list);
	register_block("__sort_list",list_sort_list);
	register_block("__reverse_list",list_reverse_list);
<<<<<<< HEAD
	register_block("__binarysearch_in_list",list_binarysearch_in_list);
=======
	register_block("__reverse_list",list_reverse_list);
>>>>>>> 6076414576bd95ae9778d1496b59fcfeb35b8e50
	
	/* Runtime Dynamic Library Loading */
	register_block("__loadDynamicLibrary",simple_vm_dll_loadlib);
	register_block("__callDynamicFunction",simple_vm_dll_calllib_function);
	/* Date and Time */
	register_block("__clock",date_time_clock);
	register_block("__clock_per_second",date_time_clock_per_second);
	register_block("__time",date_time_time);
	register_block("__date",date_time_date);
	register_block("__date_time_list",date_time_list);
	register_block("__date_time_t_to_list",date_time_t_to_list);
	register_block("__date_time_add_days",date_time_add_days);
	
	/* Error and Warn */
    register_block("__throw",error_throw);
    register_block("__stack_trace",error_stack_trace);
    register_block("__warn",error_warn);
	
    /* Conversion */ 
    register_block("__string_to_chex",conversion_string_to_chex);
    register_block("__hex_to_string",conversion_hex_to_string);
    register_block("__string_to_list",conversion_string_to_list);
    register_block("__string_to_hex",conversion_string_to_hex);

    /* Characters Checking */ 
    register_block("__is_alpha_num",check_characters_is_alpha_num);
    register_block("__is_alpha",check_characters_is_alpha);
    register_block("__is_num",check_characters_is_num);
    register_block("__is_control_char",check_characters_is_cntrl);
    register_block("__is_digit",check_characters_is_num);
    register_block("__is_graph",check_characters_is_graph);
    register_block("__is_lower",check_characters_is_lower);
    register_block("__is_print",check_characters_is_print);
    register_block("__is_punct",check_characters_is_punct);
    register_block("__is_space",check_characters_is_space);
    register_block("__is_upper",check_characters_is_upper);
    register_block("__is_x_digit",check_characters_is_xdigit);
	
	/* Meta Blocks */ 
	register_block("__add_attribute",meta_blocks_add_addribute);
}

/* List */
void list_delete_from_list( void *pointer )
{
	List *list  ;
	double num  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1) ;
		if ( SIMPLE_API_ISNUMBER(2) ) {
			num = SIMPLE_API_GETNUMBER(2) ;
			if ( ( num < 1 ) || ( num > simple_list_getsize(list) ) ) {
				SIMPLE_API_ERROR("Error in second parameter, item number outside the list size range!");
				return ;
			}
			simple_list_deleteitem_gc(((VM *) pointer)->sState,list,num);
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires number!");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void list_find_in_list( void *pointer )
{
	int num,column  ;
	List *list  ;
	if ( ! ( (SIMPLE_API_PARACOUNT >= 2) && (SIMPLE_API_PARACOUNT <= 4) ) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		num = 0 ;
		list = SIMPLE_API_GETLIST(1) ;
		if ( simple_list_getsize(list) > 0 ) {
			column = 0 ;
			if ( SIMPLE_API_PARACOUNT >= 3 ) {
				if ( SIMPLE_API_ISNUMBER(3) ) {
					column = SIMPLE_API_GETNUMBER(3) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
			}
			if ( SIMPLE_API_PARACOUNT == 4 ) {
				if ( SIMPLE_API_ISSTRING(4) ) {
					if ( SIMPLE_API_ISSTRING(2) ) {
						num = simple_list_findinlistofobjs(list,SIMPLE_VM_LISTOFOBJS_FINDSTRING,0.0,SIMPLE_API_GETSTRING(2),column,SIMPLE_API_GETSTRING(4));
					}
					else if ( SIMPLE_API_ISNUMBER(2) ) {
						num = simple_list_findinlistofobjs(list,SIMPLE_VM_LISTOFOBJS_FINDNUMBER,SIMPLE_API_GETNUMBER(2),"",column,SIMPLE_API_GETSTRING(4));
					}
					else {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					}
					if ( num == -1 ) {
						SIMPLE_API_ERROR(SIMPLE_VM_ERROR_PROPERTYNOTFOUND);
					}
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
			}
			else {
				if ( SIMPLE_API_ISSTRING(2) ) {
					num = simple_list_findstring(list,SIMPLE_API_GETSTRING(2),column);
				}
				else if ( SIMPLE_API_ISNUMBER(2) ) {
					num = simple_list_finddouble(list,SIMPLE_API_GETNUMBER(2),column);
				}
				else if ( SIMPLE_API_ISCPOINTER(2) ) {
					num = simple_list_findcpointer(list,SIMPLE_API_GETLIST(2),column);
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
				}
				if ( num == -1 ) {
					SIMPLE_API_ERROR(SIMPLE_VM_ERROR_BADCOLUMNNUMBER);
				}
			}
		}
		SIMPLE_API_RETNUMBER(num);
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void list_min_value( void *pointer )
{
	double num  ;
	List *list  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISLIST(1) ) {
			list = SIMPLE_API_GETLIST(1) ;
			if ( simple_list_getsize(list) > 0 ) {
				if ( simple_list_isnumber(list,1) ) {
					num = simple_list_getdouble(list,1) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					return ;
				}
				if ( simple_list_getsize(list) > 1 ) {
					for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
						if ( simple_list_isnumber(list,x) ) {
							if ( simple_list_getdouble(list,x) < num ) {
								num = simple_list_getdouble(list,x) ;
							}
						}
						else {
							SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
							return ;
						}
					}
				}
				SIMPLE_API_RETNUMBER(num);
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

void list_max_value( void *pointer )
{
	double num  ;
	List *list  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISLIST(1) ) {
			list = SIMPLE_API_GETLIST(1) ;
			if ( simple_list_getsize(list) > 0 ) {
				if ( simple_list_isnumber(list,1) ) {
					num = simple_list_getdouble(list,1) ;
				}
				else {
					SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
					return ;
				}
				if ( simple_list_getsize(list) > 1 ) {
					for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
						if ( simple_list_isnumber(list,x) ) {
							if ( simple_list_getdouble(list,x) > num ) {
								num = simple_list_getdouble(list,x) ;
							}
						}
						else {
							SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
							return ;
						}
					}
				}
				SIMPLE_API_RETNUMBER(num);
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

void list_insert_into_list( void *pointer )
{
	List *list, *list2  ;
	int nPos  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) && SIMPLE_API_ISNUMBER(2) ) {
		list = SIMPLE_API_GETLIST(1) ;
		nPos = (int) SIMPLE_API_GETNUMBER(2) ;
		if ( (nPos < 0) || (nPos > simple_list_getsize(list) ) ) {
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_INDEXOUTOFRANGE);
			return ;
		}
		if ( SIMPLE_API_ISSTRING(3) ) {
			simple_list_insertstring2(list,nPos,SIMPLE_API_GETSTRING(3),SIMPLE_API_GETSTRINGSIZE(3));
		}
		else if ( SIMPLE_API_ISNUMBER(3) ) {
			simple_list_insertdouble(list,nPos,SIMPLE_API_GETNUMBER(3));
		}
		else if ( SIMPLE_API_ISLIST(3) ) {
			list2 = simple_list_insertlist(list,nPos);
			simple_vm_list_copy((VM *) pointer,list2,SIMPLE_API_GETLIST(3));
		}
		else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void list_sort_list( void *pointer )
{
	List *list, *list2, *list3  ;
	int x,nParaCount,column,nPos  ;
	char *cAttribute  ;
	nParaCount = SIMPLE_API_PARACOUNT ;
	if ( ! ( (nParaCount >= 1) && (nParaCount <= 3) ) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_NEWLIST ;
		list2 = SIMPLE_API_GETLIST(1);
		simple_vm_list_copy((VM *) pointer,list,list2);
		if ( simple_list_getsize(list) < 2 ) {
			SIMPLE_API_RETLIST(list2);
			return ;
		}
		if ( nParaCount == 1 ) {
			if ( simple_list_isnumber(list,1) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					if ( ! simple_list_isnumber(list,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortnum(list,1,simple_list_getsize(list),0,"");
			}
			else if ( simple_list_isstring(list,1) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					if ( ! simple_list_isstring(list,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortstr(list,1,simple_list_getsize(list),0,"");
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else if ( (nParaCount == 2) && SIMPLE_API_ISNUMBER(2) && simple_list_islist(list,1) ) {
			column = SIMPLE_API_GETNUMBER(2) ;
			list3 = simple_list_getlist(list,1);
			if ( simple_list_isnumber(list3,column) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					list3 = simple_list_getlist(list,x);
					if ( ! simple_list_isnumber(list3,column) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortnum(list,1,simple_list_getsize(list),column,"");
			}
			else if ( simple_list_isstring(list3,column) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					list3 = simple_list_getlist(list,x);
					if ( ! simple_list_isstring(list3,column) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				simple_list_sortstr(list,1,simple_list_getsize(list),column,"");
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else if ( (nParaCount == 3) && SIMPLE_API_ISNUMBER(2) && simple_list_islist(list,1) && SIMPLE_API_ISSTRING(3) ) {
			column = SIMPLE_API_GETNUMBER(2) ;
			cAttribute = SIMPLE_API_GETSTRING(3) ;
			simple_string_lower(cAttribute);
			list3 = simple_list_getlist(list,1);
			if ( column > 1 ) {
				list3 = simple_list_getlist(list3,column);
			}
			if ( simple_vm_oop_isobject(list3) ) {
				nPos = simple_list_findstring(simple_list_getlist(list3,SIMPLE_OBJECT_OBJECTDATA),cAttribute,SIMPLE_VAR_NAME);
				if ( nPos == 0 ) {
					SIMPLE_API_ERROR(SIMPLE_VM_ERROR_PROPERTYNOTFOUND);
					return ;
				}
				list3 = simple_list_getlist(list3,SIMPLE_OBJECT_OBJECTDATA) ;
				list3 = simple_list_getlist(list3,nPos) ;
				if ( simple_list_isstring(list3,SIMPLE_VAR_VALUE) ) {
					simple_list_sortstr(list,1,simple_list_getsize(list),column,cAttribute);
				}
				else if ( simple_list_isnumber(list3,SIMPLE_VAR_VALUE) ) {
					simple_list_sortnum(list,1,simple_list_getsize(list),column,cAttribute);
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
		SIMPLE_API_RETLIST(list);
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void list_reverse_list (void *pointer )
{
	List *list  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		list = simple_reverse_list(((VM *) pointer),SIMPLE_API_GETLIST(1));
		SIMPLE_API_RETLIST(list);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void list_binarysearch_in_list( void *pointer )
{
	List *list, *list2  ;
	int x,nParaCount,column  ;
	nParaCount = SIMPLE_API_PARACOUNT ;
	if ( (nParaCount != 2) && (nParaCount != 3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1);
		if ( list->pItemsArray == NULL ) {
			simple_list_genarray_gc(((VM *) pointer)->sState,list);
		}
		if ( nParaCount == 2 ) {
			if ( SIMPLE_API_ISSTRING(2) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					if ( ! simple_list_isstring(list,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchstr(list,SIMPLE_API_GETSTRING(2),0,""));
			}
			else if ( SIMPLE_API_ISNUMBER(2) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					if ( ! simple_list_isnumber(list,x) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchnum(list,SIMPLE_API_GETNUMBER(2),0,""));
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		}
		else {
			column = SIMPLE_API_GETNUMBER(3) ;
			if ( SIMPLE_API_ISSTRING(2) ) {
				/* Check that all items are strings */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					list2 = simple_list_getlist(list,x);
					if ( ! simple_list_isstring(list2,column) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchstr(list,SIMPLE_API_GETSTRING(2),column,""));
			}
			else if ( SIMPLE_API_ISNUMBER(2) ) {
				/* Check that all items are numbers */
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					list2 = simple_list_getlist(list,x);
					if ( ! simple_list_isnumber(list2,column) ) {
						SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
						return ;
					}
				}
				SIMPLE_API_RETNUMBER(simple_list_binarysearchnum(list,SIMPLE_API_GETNUMBER(2),column,""));
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


/* Date and Time */
SIMPLE_API void date_time_add_days(void *pointer)
{
	const char *cStr  ;
	char buffer[25]  ;
	int x,nDay,nMonth,nYear,nDaysInMonth  ;
	int aDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 } ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( ! (SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISNUMBER(2)) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	cStr = SIMPLE_API_GETSTRING(1);
	if ( (SIMPLE_API_GETSTRINGSIZE(1) == 10) ) {
		if ( isalnum(cStr[0]) && isalnum(cStr[1]) && isalnum(cStr[3]) && isalnum(cStr[4]) && isalnum(cStr[6]) && isalnum(cStr[7]) && isalnum(cStr[8]) && isalnum(cStr[9]) ) {
			sprintf( buffer , "%c%c" , cStr[0],cStr[1] ) ;
			nDay = atoi(buffer) + ((int) SIMPLE_API_GETNUMBER(2)) ;
			sprintf( buffer , "%c%c" , cStr[3],cStr[4] ) ;
			nMonth = atoi(buffer) ;
			sprintf( buffer , "%c%c%c%c" , cStr[6],cStr[7],cStr[8],cStr[9] ) ;
			nYear = atoi(buffer) ;
			/* Fix Day Number */
			nDaysInMonth = aDaysInMonth[nMonth-1] ;
			/* Fix Leap Year */
			if ( (nMonth == 2) && (simple_add_leap_year(nYear)) ) {
				nDaysInMonth = 29 ;
			}
			while ( nDay > nDaysInMonth ) {
				nDay = nDay - nDaysInMonth ;
				nMonth++ ;
				if ( nMonth == 13 ) {
					nMonth = 1 ;
					nYear++ ;
				}
				nDaysInMonth = aDaysInMonth[nMonth-1] ;
				/* Fix Leap Year */
				if ( (nMonth == 2) && (simple_add_leap_year(nYear)) ) {
					nDaysInMonth = 29 ;
				}
			}
			while ( nDay < 1 ) {
				nMonth-- ;
				if ( nMonth == 0 ) {
					nMonth = 12 ;
					nYear-- ;
				}
				nDaysInMonth = aDaysInMonth[nMonth-1] ;
				/* Fix Leap Year */
				if ( (nMonth == 2) && (simple_add_leap_year(nYear)) ) {
					nDaysInMonth = 29 ;
				}
				nDay = nDaysInMonth - abs(nDay) ;
			}
			sprintf(buffer,"%2d/%2d/%4d", nDay,nMonth,nYear);
			for ( x = 0 ; x <= 9 ; x++ ) {
				if ( buffer[x] == ' ' ) {
					buffer[x] = '0' ;
				}
			}
			SIMPLE_API_RETSTRING(buffer);
			return ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	return ;
}

int simple_add_leap_year(int year)
{
	if ( year%400 == 0 ) {
		return 1 ;
	}
	if ( year%100 == 0 ) {
		return 0 ;
	}
	return year % 4 == 0 ;
}

SIMPLE_API void date_time_t_to_list(void *pointer)
{
	time_t timer  ;
	char buffer[25]  ;
	struct tm*tm_info  ;
	List *list  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		list = SIMPLE_API_NEWLIST ;
		timer = SIMPLE_API_GETCPOINTER(1,"SIMPLE_LANG_TIME_");
		tm_info = localtime(&timer);
		/*
		**  Add List Items 
		**  abbreviated weekday name 
		*/
		strftime(buffer,25,"%a", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* full weekday name */
		strftime(buffer,25,"%A", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* abbreviated month name */
		strftime(buffer,25,"%b", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* full month name */
		strftime(buffer,25,"%B", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Date & Time */
		strftime(buffer,25,"%c", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Day of the month */
		strftime(buffer,25,"%d", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Hour (24) */
		strftime(buffer,25,"%H", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Hour (12) */
		strftime(buffer,25,"%I", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Day of the year */
		strftime(buffer,25,"%j", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Month of the year */
		strftime(buffer,25,"%m", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Minutes after hour */
		strftime(buffer,25,"%M", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* AM or PM */
		strftime(buffer,25,"%p", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Seconds after the hour */
		strftime(buffer,25,"%S", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* Week of the year (sun-sat) */
		strftime(buffer,25,"%U", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* day of the week */
		strftime(buffer,25,"%w", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* date */
		strftime(buffer,25,"%x", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* time */
		strftime(buffer,25,"%X", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* year of the century */
		strftime(buffer,25,"%y", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* year */
		strftime(buffer,25,"%Y", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* time zone */
		strftime(buffer,25,"%Z", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		/* percent sign */
		strftime(buffer,25,"%%", tm_info);
		simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
		SIMPLE_API_RETLIST(list);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void date_time_list(void *pointer)
{
	time_t timer  ;
	char buffer[25]  ;
	struct tm*tm_info  ;
	List *list  ;
	list = SIMPLE_API_NEWLIST ;
	time(&timer);
	tm_info = localtime(&timer);
	/*
	**  Add List Items 
	**  abbreviated weekday name 
	*/
	strftime(buffer,25,"%a", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* full weekday name */
	strftime(buffer,25,"%A", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* abbreviated month name */
	strftime(buffer,25,"%b", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* full month name */
	strftime(buffer,25,"%B", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Date & Time */
	strftime(buffer,25,"%c", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Day of the month */
	strftime(buffer,25,"%d", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Hour (24) */
	strftime(buffer,25,"%H", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Hour (12) */
	strftime(buffer,25,"%I", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Day of the year */
	strftime(buffer,25,"%j", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Month of the year */
	strftime(buffer,25,"%m", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Minutes after hour */
	strftime(buffer,25,"%M", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* AM or PM */
	strftime(buffer,25,"%p", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Seconds after the hour */
	strftime(buffer,25,"%S", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* Week of the year (sun-sat) */
	strftime(buffer,25,"%U", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* day of the week */
	strftime(buffer,25,"%w", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* date */
	strftime(buffer,25,"%x", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* time */
	strftime(buffer,25,"%X", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* year of the century */
	strftime(buffer,25,"%y", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* year */
	strftime(buffer,25,"%Y", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* time zone */
	strftime(buffer,25,"%Z", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	/* percent sign */
	strftime(buffer,25,"%%", tm_info);
	simple_list_addstring_gc(((VM *) pointer)->sState,list,buffer);
	SIMPLE_API_RETLIST(list);
}

SIMPLE_API void date_time_date(void *pointer)
{
	time_t timer  ;
	char buffer[25]  ;
	struct tm*tm_info  ;
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer,25,"%d/%m/%Y", tm_info);
	SIMPLE_API_RETSTRING(buffer);
}

SIMPLE_API void date_time_time(void *pointer)
{
	time_t timer  ;
	char buffer[25]  ;
	struct tm*tm_info  ;
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer,25,"%H:%M:%S", tm_info);
	SIMPLE_API_RETSTRING(buffer);
}

SIMPLE_API void date_time_clock_per_second(void *pointer)
{
	SIMPLE_API_RETNUMBER(CLOCKS_PER_SEC);
}

SIMPLE_API void date_time_clock(void *pointer)
{
	clock_t tick  ;
	tick = clock();
	SIMPLE_API_RETNUMBER((double) tick);
}

/* Meta Blocks */ 
SIMPLE_API void meta_blocks_add_addribute(void *pointer)
{
	List *list, *list2  ;
	char *str  ;
	int x  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	/*if ( SIMPLE_API_ISLIST(1) ) {
		list = SIMPLE_API_GETLIST(1) ;
		if ( simple_vm_oop_isobject(list) ) {
			list = simple_list_getlist(list,SIMPLE_OBJECT_OBJECTDATA);
			if ( SIMPLE_API_ISSTRING(2) ) {
				str = SIMPLE_API_GETSTRING(2) ;
				simple_string_lower(str);
				/* Create Variable List *
				simple_vm_newvar2((VM *) pointer,str,list);
			}
			else if ( SIMPLE_API_ISLIST(2) ) {
				list2 = SIMPLE_API_GETLIST(2) ;
				for ( x = 1 ; x <= simple_list_getsize(list2) ; x++ ) {
					if ( simple_list_isstring(list2,x) ) {
						str = simple_list_getstring(list2,x);
						simple_string_lower(str);
						/* Create Variable List *
						simple_vm_newvar2((VM *) pointer,str,list);
					}
				}
			} else {
				SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			}
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	} */
}

/* Characters Checking */ 
SIMPLE_API void check_characters__(void *pointer,int type)
{
	char *str  ;
	int size,x  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		str = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		switch (type) {
			case 0:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isalnum(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 1:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isalpha(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 2:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isdigit(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 3:
				for ( x = 0 ; x < size ; x++ ) {
					if (!iscntrl(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 4:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isgraph(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 5:
				for ( x = 0 ; x < size ; x++ ) {
					if (!islower(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 6:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isprint(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 7:
				for ( x = 0 ; x < size ; x++ ) {
					if (!ispunct(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 8:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isspace(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 9:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isupper(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
			case 10:
				for ( x = 0 ; x < size ; x++ ) {
					if (!isxdigit(str[x])) {
						SIMPLE_API_RETNUMBER(0);
						return ; 
					}
				}
				SIMPLE_API_RETNUMBER(1); return;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void check_characters_is_alpha_num(void *pointer)
{
	check_characters__(pointer,0);
}

SIMPLE_API void check_characters_is_alpha(void *pointer)
{
	check_characters__(pointer,1);
}

SIMPLE_API void check_characters_is_num(void *pointer)
{
	check_characters__(pointer,2);
}

SIMPLE_API void check_characters_is_cntrl(void *pointer)
{
	check_characters__(pointer,3);
}

SIMPLE_API void check_characters_is_graph(void *pointer)
{
	check_characters__(pointer,4);
}

SIMPLE_API void check_characters_is_lower(void *pointer)
{
	check_characters__(pointer,5);
}

SIMPLE_API void check_characters_is_print(void *pointer)
{
	check_characters__(pointer,6);
}

SIMPLE_API void check_characters_is_punct(void *pointer)
{
	check_characters__(pointer,7);
}

SIMPLE_API void check_characters_is_space(void *pointer)
{
	check_characters__(pointer,8);
}

SIMPLE_API void check_characters_is_upper(void *pointer)
{
	check_characters__(pointer,9);
}

SIMPLE_API void check_characters_is_xdigit(void *pointer)
{
	check_characters__(pointer,10);
}

SIMPLE_API void error_warn(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if (((VM *) pointer)->sState->nWarning) 
			printf("%s",SIMPLE_API_GETSTRING(1));
		return;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void error_stack_trace(void *pointer)
{
	String *string,*string2;
	List *list, *list2;
	int x,lBlockCall,is_last_block  ;
	const char *cFile  ;
	VM *vm;	
	list2 = SIMPLE_API_NEWLIST ;
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	} else {
		vm = ((VM *) pointer);
		/* Print the Error Message */
		string = simple_string_new_gc(((VM *) pointer)->sState,"at line ");
			string2 = simple_string_new_gc(((VM *) pointer)->sState,"");
			simple_string_setfromint_gc(((VM *) pointer)->sState,string2,vm->nLineNumber);
		simple_string_add_gc(((VM *) pointer)->sState,string,string2->str);
		/* Print Calling Information */
		lBlockCall = 0 ; is_last_block = 1 ;
		for ( x = simple_list_getsize(vm->pBlockCallList) ; x >= 1 ; x-- ) {
			list = simple_list_getlist(vm->pBlockCallList,x);
			/*
			**  If we have ICO_LoadBlock but not ICO_CALL then we need to pass 
			**  ICO_LOADBLOCK is executed, but still ICO_CALL is not executed! 
			*/
			if ( simple_list_getsize(list) < SIMPLE_BLOCKCL_CALLERPC ) {
				continue ;
			}
			if ( simple_list_getint(list,SIMPLE_BLOCKCL_TYPE) == SIMPLE_BLOCKTYPE_SCRIPT ) {
				/*
				**  Prepare Message 
				**  In 
				*/
				simple_string_add_gc(((VM *) pointer)->sState,string," at ");
				simple_string_add_gc(((VM *) pointer)->sState,string,simple_list_getstring(list,SIMPLE_BLOCKCL_NAME));
				/* Adding () */
				simple_string_add_gc(((VM *) pointer)->sState,string,"() in file ");
				/* File Name */
				if ( lBlockCall == 1 ) {
					cFile = (const char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_NEWFILENAME) ;
				}
				else {
					if ( vm->nInClassRegion ) {
						cFile = vm->cFileNameInClassRegion ;
					}
					else {
						cFile = vm->file_name ;
					}
				}
				simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(cFile));
				simple_list_addstring_gc(vm,list2,string->str);
				/* Called From */
				string = simple_string_new_gc(((VM *) pointer)->sState,"at line ");
					string2 = simple_string_new_gc(((VM *) pointer)->sState,"");
					simple_string_setfromint_gc(((VM *) pointer)->sState,string2,simple_list_getint(list,SIMPLE_BLOCKCL_LINENUMBER));
				simple_string_add_gc(((VM *) pointer)->sState,string,string2->str);
				is_last_block = 0; 
				lBlockCall = 1 ;
			}
			else {
				simple_string_add_gc(((VM *) pointer)->sState,string," in ");
				simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(simple_list_getstring(list,SIMPLE_BLOCKCL_NAME)));
			}
		}
		if ( lBlockCall ) {
			simple_string_add_gc(((VM *) pointer)->sState,string," in file ");
			simple_string_add_gc(((VM *) pointer)->sState,string,file_real_name(simple_list_getstring(vm->sState->files_list,1)));
		} else {
			if ( vm->nInClassRegion ) {
				cFile = vm->cFileNameInClassRegion ;
			}
			else {
				cFile = file_real_name(vm->file_name) ;
			}
			simple_string_add_gc(((VM *) pointer)->sState,string," in file ");
			simple_string_add_gc(((VM *) pointer)->sState,string,cFile);
		}
		simple_list_addstring_gc(vm,list2,string->str);
		simple_string_delete_gc(((VM *) pointer)->sState,string);
		simple_string_delete_gc(((VM *) pointer)->sState,string2);
		SIMPLE_API_RETLIST(list2);
		return;
	}
}

SIMPLE_API void error_throw(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if (((VM *) pointer)->sState->skip_error == 0) 
			((VM *) pointer)->sState->skip_error = 1;
		SIMPLE_API_ERROR(SIMPLE_API_GETSTRING(1));
		if (((VM *) pointer)->sState->skip_error == 1) 
			((VM *) pointer)->sState->skip_error = 0;
		return;
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/* Conversion */ 

SIMPLE_API void conversion_string_to_hex(void *pointer)
{
	char str[3]  ;
	unsigned char *string  ;
	int x,max  ;
	char *string2  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		string = (unsigned char *) SIMPLE_API_GETSTRING(1) ;
		max = SIMPLE_API_GETSTRINGSIZE(1) ;
		string2 = (char *) simple_state_malloc(((VM *) pointer)->sState,max*2);
		if ( string2 == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		for ( x = 1 ; x <= max ; x++ ) {
			sprintf( str , "%x" , (unsigned int) string[x-1] ) ;
			string2[(x-1)*2] = str[0] ;
			if ( str[1] != '\0' ) {
				string2[((x-1)*2)+1] = str[1] ;
			} else {
				string2[((x-1)*2)+1] = ' ' ;
			}
		}
		SIMPLE_API_RETSTRING2(string2,max*2);
		simple_state_free(((VM *) pointer)->sState,string2);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void conversion_hex_to_string(void *pointer)
{
	char str[3]  ;
	const char *string  ;
	char *string2  ;
	int x,i,max  ;
	unsigned int y  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		string = SIMPLE_API_GETSTRING(1) ;
		max = SIMPLE_API_GETSTRINGSIZE(1) ;
		string2 = (char *) simple_state_malloc(((VM *) pointer)->sState,(max/2)+1);
		if ( string2 == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		i = 0 ;
		for ( x = 0 ; x < max ; x+=2 ) {
			str[0] = string[x] ;
			if ( string[x+1]   != ' ' ) {
				str[1] = string[x+1] ;
				str[2] = '\0' ;
			} else {
				str[1] = '\0' ;
			}
			sscanf(str,"%x",&y);
			string2[i] = y ;
			i++ ;
		}
		SIMPLE_API_RETSTRING2(string2,max/2);
		simple_state_free(((VM *) pointer)->sState,string2);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}



SIMPLE_API void conversion_string_to_chex (void *pointer)
{
	char str[3]  ;
	unsigned char *string  ;
	int x,max  ;
	char *string2  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		string = (unsigned char *) SIMPLE_API_GETSTRING(1) ;
		max = SIMPLE_API_GETSTRINGSIZE(1) ;
		string2 = (char *) simple_state_malloc(((VM *) pointer)->sState,max*5);
		if ( string2 == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		for ( x = 1 ; x <= max ; x++ ) {
			sprintf( str , "%x" , (unsigned int) string[x-1] ) ;
			/* Separator */
			string2[(x-1)*5] = ',' ;
			string2[(x-1)*5+1] = '0' ;
			string2[(x-1)*5+2] = 'x' ;
			string2[(x-1)*5+3] = str[0] ;
			if ( str[1] != '\0' ) {
				string2[((x-1)*5)+4] = str[1] ;
			} else {
				string2[((x-1)*5)+4] = ' ' ;
			}
		}
		/* Pass the first letter to avoid the first comma */
		string2++ ;
		SIMPLE_API_RETSTRING2(string2,max*5-1);
		/* When we call free() we use the original pointer */
		string2-- ;
		simple_state_free(((VM *) pointer)->sState,string2);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void conversion_string_to_list ( void *pointer )
{
	char *str  ;
	int x,size,start  ;
	List *list  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		str = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		start = 0 ;
		list = SIMPLE_API_NEWLIST ;
		for ( x = 0 ; x < size ; x++ ) {
			if ( str[x] == '\n' ) {
				if ( x > start ) {
					if ( str[x-1] == '\r' ) {
						simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,x-start-1);
					}
					else {
						simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,x-start);
					}
				} else {
					simple_list_addstring_gc(((VM *) pointer)->sState,list,"");
				}
				start = x+1 ;
			}
		}
		if ( size > start ) {
			simple_list_addstring2_gc(((VM *) pointer)->sState,list,str+start,size-start);
		}
		SIMPLE_API_RETLIST(list);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_dll_loadlib ( void *pointer )
{
	LpHandleType handle  ;
	char library_path[200]  ; 
	if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISSTRING(1) ) {
		strcpy(library_path,SIMPLE_API_GETSTRING(1));
		handle = LoadDLL(library_path);
		if ( handle == NULL ) {
                printf( "\nCannot load dynamic library : %s",library_path) ;
                SIMPLE_API_ERROR(SIMPLE_VM_ERROR_LIBLOADERROR);
                return ;
        } else {
			SIMPLE_API_RETCPOINTER(handle,"SIMPLE_DYNAMIC_LIBRARY_");
		}		
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_dll_calllib_function ( void *pointer )
{
	LpHandleType handle  ;
	lp address ;
	char library_path[200]  ; 
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISNUMBER(3)&& SIMPLE_API_ISLIST(4) ) {
		strcpy(library_path,SIMPLE_API_GETSTRING(2));
		handle = SIMPLE_API_GETCPOINTER(1,"SIMPLE_DYNAMIC_LIBRARY_") ;
		address = (lp) GetDLLBlock(handle, library_path) ;
        if ( address == NULL ) {
			printf( "\nCannot call the function : %s", library_path ) ;
			SIMPLE_API_ERROR("Error occur while calling the function");
			return ;
		} else {
			int returnValue = call_func(address,SIMPLE_API_GETLIST(4));
			int returnType = (int) SIMPLE_API_GETNUMBER(3) ;
			switch (returnType) {
				case 1 : //pointer
					SIMPLE_API_RETCPOINTER(returnValue,"SIMPLE_DYNAMIC_LIBRARY_");
					break ;
				case 2 : //number
					SIMPLE_API_RETNUMBER(returnValue);
					break ;
				case 3 : //string
					SIMPLE_API_RETSTRING(returnValue);
					break ;
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

int get_parameter_value(Item * item) {
	List *list;
	switch (item->nType) {
		case ITEMTYPE_NUMBER:
			return simple_item_getnumber(item);
			break;
		case ITEMTYPE_STRING : 
			return simple_item_getstring(item)->str;
			break;
		case ITEMTYPE_LIST :
			//SIMPLE_API_RETCPOINTER return a list with the pointer at index 1
			//now we assume all list that finds it way here is actually a pointer 
			//returned from dynamically calling a foreign function
			//:( i hope this does not explode to my face
			list = simple_item_getlist(item);
			return simple_list_getpointer(list,1);
			break;
		case ITEMTYPE_POINTER : 
			return simple_item_getpointer(item);
			break;
	}
}

void* call_func(lp address, List* parameters) 
{
	int size, i ;
	int arg[100] ;
	void* returnValue ;
	size = simple_list_getsize(parameters);
	for (i = 0; i < size; i++) {
		arg[i] = get_parameter_value(simple_list_getitem(parameters,(i+1))); 
	}
	switch (size) {
		case 1 :
			returnValue = (*address)(BUILD(arg, 0));
			break ;
		case 2 : 
			returnValue = (*address)(BUILD(arg, 1));
			break ;
		case 3 : 
			returnValue = (*address)(BUILD(arg, 2));
			break ;
		case 4 :
			returnValue = (*address)(BUILD(arg, 3));
			break ;
		case 5 :
			returnValue = (*address)(BUILD(arg, 4));
			break ;
		case 6 :
			returnValue = (*address)(BUILD(arg, 5));
			break ;
		case 7 :
			returnValue = (*address)(BUILD(arg, 6));
			break ;
		case 8 :
			returnValue = (*address)(BUILD(arg, 7));
			break ;
		case 9 :
			returnValue = (*address)(BUILD(arg, 8));
			break ;
		case 10 :
			returnValue = (*address)(BUILD(arg, 9));
			break ;
		case 11 :
			returnValue = (*address)(BUILD(arg, 10));
			break ;
		case 12 :
			returnValue = (*address)(BUILD(arg, 11));
			break ;
		case 13 :
			returnValue = (*address)(BUILD(arg, 12));
			break ;
		case 14 :
			returnValue = (*address)(BUILD(arg, 13));
			break ;
		case 15 :
			returnValue = (*address)(BUILD(arg, 14));
			break ;
		default :
			returnValue = (*address)(NULL);
	}
	return returnValue ;
	
}
