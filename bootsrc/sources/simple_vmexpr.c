
/* 
	Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   simple_vmexpr.c
 * Author: thecarisma
 *
 * Created on July 10, 2017, 2:10 PM
 */

#include "../includes/simple.h"

void simple_vm_sum ( VM *vm )
{
	String *string_one,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	/*
	**  Description 
	**  We can sum string + number ---> string , number + string ---> number 
	**  string/number + crlf ---> string 
	**  list + string/number ---> add item to the list 
	**  list1 + list2 ---> add list2 items to list 1 
	*/
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			cStr2 = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
			simple_string_add2_gc(vm->sState,cStr2,simple_string_get(string_one),simple_string_size(string_one));
			SIMPLE_VM_STACK_SETCVALUE2(simple_string_get(cStr2),simple_string_size(cStr2));
			simple_string_delete_gc(vm->sState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			if ( strcmp(simple_string_get(string_one),"\n") == 0 ) {
				cStr2 = simple_string_new_gc(vm->sState,"") ;
				simple_string_add_gc(vm->sState,cStr2,simple_vm_numtostring(vm,nNum2,cStr3));
				simple_string_add_gc(vm->sState,cStr2,simple_string_get(string_one));
				SIMPLE_VM_STACK_SETCVALUE(simple_string_get(cStr2));
				simple_string_delete_gc(vm->sState,cStr2);
			} else {
				SIMPLE_VM_STACK_SETNVALUE(nNum2 + simple_vm_stringtonum(vm,simple_string_get(string_one)));
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"+",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_SETNVALUE(nNum1+nNum2);
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			cStr2 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC) ;
			simple_vm_numtostring(vm,nNum1,cStr3);
			simple_string_add_gc(vm->sState,cStr2,cStr3);
			SIMPLE_VM_STACK_SETCVALUE(simple_string_get(cStr2));
			simple_string_delete_gc(vm->sState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"+",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"+");
		return ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_sub ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"-",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"-",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"-");
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum2-nNum1);
}

void simple_vm_mul ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"*",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"*",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"*");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(vm,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(vm,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum1*nNum2);
}

void simple_vm_div ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( nNum1 == 0 ) {
			simple_vm_error(vm,SIMPLE_VM_ERROR_DIVIDEBYZERO);
			return ;
		}
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"/",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"/",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"/");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(vm,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(vm,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum2/nNum1);
}

void simple_vm_mod ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( nNum1 == 0 ) {
			simple_vm_error(vm,SIMPLE_VM_ERROR_DIVIDEBYZERO);
			return ;
		}
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"%",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new2_gc(vm->sState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STRINGSIZE) ;
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"%",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"%");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(vm,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(vm,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(fmod(nNum2 , nNum1));
}

void simple_vm_neg ( VM *vm )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE((SIMPLE_VM_STACK_READN)*(-1));
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_SETNVALUE((nNum1)*(-1));
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(vm,"neg",0);
	}
}
/*
**  compare 
**  Here the conversion to string/number before comparing is not important 
**  Because the result is always logical (True/False) i.e. 1 or 0 
*/

void simple_vm_equal ( VM *vm )
{
	String *string_one,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			cStr2 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
			if ( strcmp(simple_string_get(string_one),simple_string_get(cStr2)) == 0 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
			simple_string_delete_gc(vm->sState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum1 = SIMPLE_VM_STACK_READN ;
			simple_vm_numtostring(vm,nNum1,cStr3);
			if ( strcmp(simple_string_get(string_one),cStr3) == 0 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"=",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			if ( nNum1 == nNum2 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			if ( simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC) == nNum1 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"=");
	}
}

void simple_vm_lessequal ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"<=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"<=",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"<=");
		return ;
	}
	/* Compare */
	if ( nNum2 <= nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_less ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"<",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"<",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"<");
		return ;
	}
	/* Compare */
	if ( nNum2 < nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_greater ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,">",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,">",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,">");
		return ;
	}
	/* Compare */
	if ( nNum2 > nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_greaterequal ( VM *vm )
{
	double nNum1=0,nNum2=0  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,">=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,">=",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,">=");
		return ;
	}
	/* Compare */
	if ( nNum2 >= nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_notequal ( VM *vm )
{
	String *string_one,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTRING ) {
			cStr2 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
			/* Compare */
			if ( strcmp(simple_string_get(string_one),simple_string_get(cStr2)) == 0 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
			simple_string_delete_gc(vm->sState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			nNum1 = simple_vm_stringtonum(vm,simple_string_get(string_one)) ;
			/* Compare */
			if ( nNum1 == nNum2 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"!=",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			/* Compare */
			if ( nNum1 == nNum2 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			cStr2 = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
			simple_vm_numtostring(vm,nNum1,cStr3);
			/* Compare */
			if ( strcmp(simple_string_get(cStr2),cStr3) == 0 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
			simple_string_delete_gc(vm->sState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"!=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"!=");
		return ;
	}
}
/* Logic */

void simple_vm_and ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"and",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"and",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"and");
	}
}

void simple_vm_or ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"or",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"or",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"or");
	}
}

void simple_vm_not ( VM *vm )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN != 0 ) {
			SIMPLE_VM_STACK_SETNVALUE(0.0);
		} else {
			SIMPLE_VM_STACK_SETNVALUE(1.0);
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_STACK_SETNVALUE(0.0);
		} else {
			SIMPLE_VM_STACK_SETNVALUE(1.0);
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(vm,"not",0);
		return ;
	}
}
/* Bitwise */

void simple_vm_bitand ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((int) nNum1 &  (int) (SIMPLE_VM_STACK_READN));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"&",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"&",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"&");
	}
}

void simple_vm_bitor ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"|",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"|",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"|");
	}
}

void simple_vm_bitshl ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) << (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 << (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"<<",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) << (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 << (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"<<",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"<<");
	}
}

void simple_vm_bitshr ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) >> (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 >> (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,">>",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) >> (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 >> (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,">>",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,">>");
	}
}

void simple_vm_bitxor ( VM *vm )
{
	double nNum1,nNum2  ;
	String *string_one  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(vm,"^",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		string_one = simple_string_new_gc(vm->sState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			nNum2 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(vm,"^",simple_string_get(string_one),simple_string_size(string_one));
			simple_string_delete_gc(vm->sState,string_one);
			return ;
		}
		simple_string_delete_gc(vm->sState,string_one);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(vm,"^");
	}
}

void simple_vm_bitnot ( VM *vm )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(~ (int) SIMPLE_VM_STACK_READN);
	}
	else if ( SIMPLE_VM_STACK_ISSTRING ) {
		nNum1 = simple_vm_stringtonum(vm,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_SETNVALUE(~ (int) nNum1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(vm,"~",0);
		return ;
	}
}
/* Conversion */

char * simple_vm_numtostring ( VM *vm,double nNum1,char *str )
{
	char cOptions[10]  ;
	if ( nNum1 == (int) nNum1 ) {
		sprintf( str , "%.0f" , nNum1 ) ;
	}
	else {
		sprintf( cOptions , "%s%df" , "%.",vm->nDecimals ) ;
		sprintf( str , cOptions , nNum1 ) ;
	}
	return str ;
}

double simple_vm_stringtonum ( VM *vm,const char *str )
{
	double nResult  ;
	if ( strlen(str) <= 15 ) {
		nResult = atof(str);
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return 0.0 ;
	}
	return nResult ;
}
/*
**  Operator Overloading 
**  Stack Pointer then Stack Pointer - Operator Overloading 
*/

void simple_vm_expr_ppoo ( VM *vm,const char *str )
{
	List *list,*list2  ;
	Item *pItem  ;
	void *pointer  ;
	int nType  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		list = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		list = simple_item_getlist(pItem);
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	/* Get Pointer Data */
	pointer = SIMPLE_VM_STACK_READP ;
	nType = SIMPLE_VM_STACK_OBJTYPE ;
	SIMPLE_VM_STACK_POP ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			list2 = (List *) SIMPLE_VM_STACK_READP ;
			list2 = simple_list_getlist(list2,SIMPLE_VAR_VALUE);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			list2 = simple_item_getlist(pItem);
		} else {
			simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
			return ;
		}
		if ( strcmp(str,"+") == 0 ) {
			if ( (simple_vm_oop_isobject(list2) == 0) ) {
				simple_vm_addlisttolist(vm,list,list2);
				return ;
			}
		}
		else if ( strcmp(str,"=") == 0 ) {
			if ( api_iscpointer_list(list) && api_iscpointer_list(list2) ) {
				SIMPLE_VM_STACK_POP ;
				if ( api_cpointer_cmp(list,list2) ) {
					SIMPLE_VM_STACK_PUSHNVALUE(1.0) ;
				}
				else {
					SIMPLE_VM_STACK_PUSHNVALUE(0) ;
				}
				return ;
			}
		}
		if ( simple_vm_oop_isobject(list2) == 1 ) {
			/* Operator Overloading */
			simple_vm_oop_operatoroverloading(vm,list2,str,SIMPLE_OOPARA_POINTER,"",0,pointer,nType);
			SIMPLE_VM_STACK_POP ;
		} else {
			simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		}
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Stack Number then Stack Pointer - Operator Overloading */

void simple_vm_expr_npoo ( VM *vm,const char *str,double nNum1 )
{
	List *list  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		list = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		list = simple_item_getlist(pItem);
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	if ( strcmp(str,"+") == 0 ) {
		if ( simple_vm_oop_isobject(list) == 0 ) {
			simple_list_adddouble_gc(vm->sState,list,nNum1);
			return ;
		}
	}
	if ( simple_vm_oop_isobject(list) == 1 ) {
		/* Operator Overloading */
		simple_vm_oop_operatoroverloading(vm,list,str,SIMPLE_OOPARA_NUMBER,"",nNum1,NULL,0);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Stack String then Stack Pointer - Operator Overloading */

void simple_vm_expr_spoo ( VM *vm,const char *str,const char *cStr2,int size )
{
	List *list  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		list = simple_list_getlist(list,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		list = simple_item_getlist(pItem);
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	if ( strcmp(str,"+") == 0 ) {
		if ( simple_vm_oop_isobject(list) == 0 ) {
			simple_list_addstring2_gc(vm->sState,list,cStr2,size);
			return ;
		}
	}
	if ( simple_vm_oop_isobject(list) == 1 ) {
		/* Operator Overloading */
		simple_vm_oop_operatoroverloading(vm,list,str,SIMPLE_OOPARA_STRING,cStr2,0,NULL,0);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Add List to List */

void simple_vm_addlisttolist ( VM *vm,List *list,List *list2 )
{
	List *list3, *list4  ;
	/*
	**  Here we are going to copy the list list to the list list2 
	**  We will copy to a temp list first (list4) 
	**  So we can add the Self object for example to an attribute in this object 
	*/
	list4 = simple_list_new_gc(vm->sState,0);
	simple_list_copy_gc(vm->sState,list4,list);
	list3 = simple_list_newlist_gc(vm->sState,list2);
	simple_list_copy_gc(vm->sState,list3,list4);
	simple_list_delete_gc(vm->sState,list4);
	if ( (simple_vm_oop_isobject(list3) == 1)  && (vm->pBraceObject == list) ) {
		vm->pBraceObject = list3 ;
		/*
		**  The copied object was created in Temp. memory that will be deleted 
		**  The object contains the self property that contains a pointer to the object in memory 
		**  We need to modify the pointer that point to the old location in Temp. Memory 
		**  The pointer will be changed to point to the new location in the array 
		**  The array maybe global or related to the object state and may stay longer than the Temp. Memory 
		**  Without this modification using self may lead to crash or using corrupted memory 
		*/
		simple_vm_oop_updateselfpointer(vm,list3,SIMPLE_OBJTYPE_LISTITEM,simple_list_getitem(list2,simple_list_getsize(list2)));
	}
	else if ( (simple_vm_oop_isobject(list3) == 1)  && (vm->pBraceObject != list) ) {
		/*
		**  in ring code if we used mylist + new obj() the init method will be called 
		**  the vm->pBraceObject will not == list but we have to update the self pointer! 
		*/
		simple_vm_oop_updateselfpointer(vm,list3,SIMPLE_OBJTYPE_LISTITEM,simple_list_getitem(list2,simple_list_getsize(list2)));
	}
}
