
/* 
	Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   string_savant.h 
 * Author: thecarisma
 *
 * Created on Febuary 7, 2018, 5:23 PM
 */

#include "../../../simple/includes/simple.h"
#include "string_savant.h"

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
    register_block("__left",simple_vmlib_left);
    register_block("__right",simple_vmlib_right);
    register_block("__trim",simple_vmlib_trim);
    register_block("__copy",simple_vmlib_copy);
    register_block("substr",simple_vmlib_substr);
    register_block("lines",simple_vmlib_lines);
    register_block("strcmp",simple_vmlib_strcmp);
    register_block("__lower",simple_vmlib_lower);
    register_block("__upper",simple_vmlib_upper);
    register_block("stringReplace",string_replace);
    register_block("__$__lastAfterChar",string_last_char);
    register_block("__split_string",split_string);
}

void simple_vmlib_left ( void *pointer )
{
	double nNum1  ;
	const char *cStr  ;
	int x  ;
	char *pString  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_ISNUMBER(2) ) {
			cStr = SIMPLE_API_GETSTRING(1) ;
			nNum1 = SIMPLE_API_GETNUMBER(2) + 1;
			if ( (nNum1 > 0 ) && (nNum1 <= SIMPLE_API_GETSTRINGSIZE(1) ) ) {
				pString = (char *) simple_state_malloc(((VM *) pointer)->sState,nNum1+1);
				if ( pString == NULL ) {
					SIMPLE_API_ERROR(SIMPLE_OOM);
					return ;
				}
				for ( x = 0 ; x < nNum1 ; x++ ) {
					pString[x] = cStr[x] ;
				}
				pString[(int) nNum1] = '\0' ;
				SIMPLE_API_RETSTRING2(pString,nNum1);
				simple_state_free(((VM *) pointer)->sState,pString);
			}
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires number !");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_right ( void *pointer )
{
	double nNum1  ;
	const char *cStr  ;
	int x,nSize  ;
	char *pString  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_ISNUMBER(2) ) {
			cStr = SIMPLE_API_GETSTRING(1) ;
			nNum1 = SIMPLE_API_GETNUMBER(2);
			nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
			if ( (nNum1 > 0 ) && (nNum1 <= nSize ) ) {
				pString = (char *) simple_state_malloc(((VM *) pointer)->sState,nNum1+1);
				if ( pString == NULL ) {
					SIMPLE_API_ERROR(SIMPLE_OOM);
					return ;
				}
				/* We start from 0 to copy the NULL character '\0' from the end */
				for ( x = 0 ; x <= nNum1 ; x++ ) {
					pString[((int)nNum1)-x] = cStr[nSize-x] ;
				}
				SIMPLE_API_RETSTRING2(pString,nNum1);
				simple_state_free(((VM *) pointer)->sState,pString);
			}
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires number !");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_trim ( void *pointer )
{
	const char *cStr  ;
	int x,nSize,nPos1,nPos2  ;
	char *cNewStr  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1) ;
		nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
		if ( nSize == 0 ) {
			SIMPLE_API_RETSTRING("");
			return ;
		}
		/* Get Limits */
		nPos1 = 0 ;
		nPos2 = nSize-1 ;
		for ( x = 0 ; x < nSize ; x++ ) {
			if ( cStr[x] != ' ' ) {
				nPos1 = x ;
				break ;
			}
		}
		for ( x = nSize-1 ; x  >= 0 ; x-- ) {
			if ( cStr[x] != ' ' ) {
				nPos2 = x ;
				break ;
			}
		}
		if ( (nPos1 == 0) && (nPos2 == nSize-1) && (cStr[0] == ' ') ) {
			SIMPLE_API_RETSTRING("");
			return ;
		}
		/* Create New String */
		cNewStr = (char *) simple_state_malloc(((VM *) pointer)->sState,nPos2-nPos1+1);
		for ( x = nPos1 ; x <= nPos2 ; x++ ) {
			cNewStr[x-nPos1] = cStr[x] ;
		}
		SIMPLE_API_RETSTRING2(cNewStr,nPos2-nPos1+1);
		simple_state_free(((VM *) pointer)->sState,cNewStr);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_copy ( void *pointer )
{
	const char *cStr  ;
	String *pString  ;
	int x,nSize  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_ISNUMBER(2) ) {
			cStr = SIMPLE_API_GETSTRING(1) ;
			pString = simple_string_new_gc(((VM *) pointer)->sState,"");
			nSize = SIMPLE_API_GETNUMBER(2) + 1;
			for ( x = 1 ; x <= nSize ; x++ ) {
				simple_string_add2_gc(((VM *) pointer)->sState,pString,cStr,SIMPLE_API_GETSTRINGSIZE(1));
			}
			SIMPLE_API_RETSTRING2(simple_string_get(pString),simple_string_size(pString));
			simple_string_delete_gc(((VM *) pointer)->sState,pString);
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires number !");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_substr ( void *pointer )
{
	char *cStr,*cStr2,*cStr3,*cString  ;
	double nNum1,nNum2  ;
	unsigned int x,nPos,nMark,nSize,nTransform,nSize2  ;
	String *pString  ;
	/*
	**  Usage 
	**  Substr(str,10) get substring from 10 to end 
	**  Substr(str,"nice") get position of "nice" inside str 
	**  Substr(str,10,15) get substring from 10 , get 15 characters 
	**  Substr(str,"nice","good") replace "nice" with "good" 
	**  Substr(str,"nice","good",true) replace "nice" with "good" - not case sensitive 
	**  Get String  (First Parameter) 
	*/
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1) ;
		nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
	} else {
		SIMPLE_API_ERROR("Error in first parameter, Function requires string !");
		return ;
	}
	/* Process */
	nTransform = 0 ;
	if ( SIMPLE_API_PARACOUNT == 2 ) {
		if ( SIMPLE_API_ISNUMBER(2) ) {
			nNum1 = SIMPLE_API_GETNUMBER(2) + 1 ;
			if ( nNum1 > 0 && nNum1 <= nSize ) {
				cStr2 = cStr + ( (int) nNum1 ) - 1 ;
				SIMPLE_API_RETSTRING2(cStr2,nSize-nNum1+1);
				return ;
			}
		}
		else if ( SIMPLE_API_ISSTRING(2) ) {
			cStr2 = SIMPLE_API_GETSTRING(2) ;
			nSize2 = SIMPLE_API_GETSTRINGSIZE(2) ;
			cStr3 = simple_string_find2(cStr,nSize,cStr2,nSize2);
			if ( cStr3 != NULL ) {
				nNum1 = ((long int) cStr3) - ((long int) cStr) + 1 ;
			} else {
				nNum1 = 0.0 ;
			}
			SIMPLE_API_RETNUMBER(nNum1 - 1);
		} else {
			SIMPLE_API_ERROR("Error in second parameter type!");
			return ;
		}
	}
	else if ( SIMPLE_API_PARACOUNT == 3 ) {
		if ( SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
			nNum1 = SIMPLE_API_GETNUMBER(2) + 1 ;
			nNum2 = SIMPLE_API_GETNUMBER(3) + 1;
			if ( (nNum1 > 0) && ( (nNum1+nNum2-1) <= nSize ) ) {
				cString = (char *) simple_state_malloc(((VM *) pointer)->sState,nNum2);
				if ( cString == NULL ) {
					SIMPLE_API_ERROR(SIMPLE_OOM);
					return ;
				}
				for ( x = 0 ; x < nNum2 ; x++ ) {
					cString[x] = cStr[((int) nNum1) + x - 1 ] ;
				}
				SIMPLE_API_RETSTRING2(cString,nNum2);
				simple_state_free(((VM *) pointer)->sState,cString);
			}
		}
		else if ( SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) ) {
			nTransform = 1 ;
		} else {
			SIMPLE_API_ERROR("Error in parameters type!");
			return ;
		}
	}
	else if ( SIMPLE_API_PARACOUNT == 4 ) {
		if ( SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) && SIMPLE_API_ISNUMBER(4) ) {
			if ( (SIMPLE_API_GETNUMBER(4) )== 1.0 ) {
				nTransform = 2 ;
			}
		} else {
			SIMPLE_API_ERROR("Error in parameters type!");
			return ;
		}
	} else {
		SIMPLE_API_ERROR("Error in parameters count!");
	}
	/* Transform/Replace */
	if ( nTransform > 0 ) {
		cStr2 = SIMPLE_API_GETSTRING(2) ;
		nSize2 = SIMPLE_API_GETSTRINGSIZE(2) ;
		/* Search */
		if ( nTransform == 1 ) {
			cString = simple_string_find2(cStr,nSize,cStr2,nSize2) ;
		} else {
			cString = simple_string_find3(cStr,nSize,cStr2,nSize2) ;
		}
		if ( cString == NULL ) {
			SIMPLE_API_RETSTRING(cStr);
			return ;
		}
		cStr3 = SIMPLE_API_GETSTRING(3) ;
		nMark = 0 ;
		pString = simple_string_new_gc(((VM *) pointer)->sState,"");
		while ( cString != NULL ) {
			nPos = ((long int) cString) - ((long int) cStr) + 1 ;
			/* Add SubString to pString */
			simple_string_add2_gc(((VM *) pointer)->sState,pString,cStr+nMark,nPos-1-nMark);
			simple_string_add2_gc(((VM *) pointer)->sState,pString,cStr3,SIMPLE_API_GETSTRINGSIZE(3));
			nMark = nPos + nSize2 -1 ;
			/* Search */
			if ( nTransform == 1 ) {
				cString = simple_string_find2(cStr+((int) nMark),nSize-nMark,cStr2,nSize2) ;
			} else {
				cString = simple_string_find3(cStr+((int) nMark),nSize-nMark,cStr2,nSize2) ;
			}
			if ( cString == NULL ) {
				/* Add SubString to pString */
				simple_string_add2_gc(((VM *) pointer)->sState,pString,cStr+nMark,nSize-nMark);
			}
		}
		SIMPLE_API_RETSTRING2(simple_string_get(pString),simple_string_size(pString));
		simple_string_delete_gc(((VM *) pointer)->sState,pString);
	}
}

void simple_vmlib_lower ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETSTRING2(simple_string_lower2(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRINGSIZE(1)),SIMPLE_API_GETSTRINGSIZE(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_upper ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETSTRING2(simple_string_upper2(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRINGSIZE(1)),SIMPLE_API_GETSTRINGSIZE(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_lines ( void *pointer )
{
	const char *cStr  ;
	int x,nSize,nCount  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1) ;
		nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
		nCount = 0 ;
		for ( x = 0 ; x < nSize ; x++ ) {
			if ( cStr[x] == '\n' ) {
				nCount++ ;
			}
		}
		SIMPLE_API_RETNUMBER(nCount);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vmlib_strcmp ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_RETNUMBER(strcmp(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void string_replace ( void *pointer )
{
	char *filename;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	} 
	filename = (char*)calloc(1, sizeof(SIMPLE_API_ISSTRING(1)));
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) ) {
            if (strstr(SIMPLE_API_GETSTRING(1), SIMPLE_API_GETSTRING(2)) != NULL ) { 
                filename = strrchr(SIMPLE_API_GETSTRING(1), SIMPLE_API_GETSTRING(2));
            } else {
                filename = strrchr(SIMPLE_API_GETSTRING(1), SIMPLE_API_GETSTRING(3));
            }
            SIMPLE_API_RETSTRING(filename);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void string_last_char ( void *pointer )
{
	char *filename;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	} 
	filename = (char*)calloc(1, sizeof(SIMPLE_API_ISSTRING(1)));
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
            filename = strrchr(SIMPLE_API_GETSTRING(1), atoi(SIMPLE_API_GETSTRING(2))) + 1;
            SIMPLE_API_RETSTRING(filename);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void split_string ( void *pointer ) {
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	} 
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
        
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/*
	to-do
	Conform with new inner string index from 0
*/