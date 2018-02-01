/*
**  Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> 
**  Remember, When we read from the stack LIFO 
**  If we have two parameters, we read the second parameter first 
*/
#include "../includes/simple.h"
/* Math */

void simple_vm_sum ( VM *pVM )
{
	String *cStr1,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	/*
	**  Description 
	**  We can sum string + number ---> string , number + string ---> number 
	**  string/number + nl ---> string 
	**  list + string/number ---> add item to the list 
	**  list1 + list2 ---> add list2 items to list 1 
	*/
	if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
			simple_stsimple_add2_gc(pVM->pRingState,cStr2,simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			SIMPLE_VM_STACK_SETCVALUE2(simple_stsimple_get(cStr2),simple_stsimple_size(cStr2));
			simple_stsimple_delete_gc(pVM->pRingState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			if ( strcmp(simple_stsimple_get(cStr1),"\n") == 0 ) {
				cStr2 = simple_stsimple_new_gc(pVM->pRingState,"") ;
				simple_stsimple_add_gc(pVM->pRingState,cStr2,simple_vm_numtostring(pVM,nNum2,cStr3));
				simple_stsimple_add_gc(pVM->pRingState,cStr2,simple_stsimple_get(cStr1));
				SIMPLE_VM_STACK_SETCVALUE(simple_stsimple_get(cStr2));
				simple_stsimple_delete_gc(pVM->pRingState,cStr2);
			} else {
				SIMPLE_VM_STACK_SETNVALUE(nNum2 + simple_vm_stringtonum(pVM,simple_stsimple_get(cStr1)));
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"+",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			SIMPLE_VM_STACK_SETNVALUE(nNum1+nNum2);
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC) ;
			simple_vm_numtostring(pVM,nNum1,cStr3);
			simple_stsimple_add_gc(pVM->pRingState,cStr2,cStr3);
			SIMPLE_VM_STACK_SETCVALUE(simple_stsimple_get(cStr2));
			simple_stsimple_delete_gc(pVM->pRingState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"+",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"+");
		return ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
}

void simple_vm_sub ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"-",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"-",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"-");
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum2-nNum1);
}

void simple_vm_mul ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"*",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"*",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"*");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(pVM,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(pVM,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum1*nNum2);
}

void simple_vm_div ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( nNum1 == 0 ) {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_DIVIDEBYZERO);
			return ;
		}
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"/",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"/",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"/");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(pVM,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(pVM,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(nNum2/nNum1);
}

void simple_vm_mod ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	char cStr2[100]  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( nNum1 == 0 ) {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_DIVIDEBYZERO);
			return ;
		}
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"%",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new2_gc(pVM->pRingState,SIMPLE_VM_STACK_READC,SIMPLE_VM_STACK_STSIMPLESIZE) ;
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"%",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"%");
		return ;
	}
	/* Check Overflow */
	if ( ( strlen(simple_vm_numtostring(pVM,nNum1,cStr2)) >= 15 ) || (strlen(simple_vm_numtostring(pVM,nNum2,cStr3)) >= 15 ) ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return ;
	}
	SIMPLE_VM_STACK_SETNVALUE(fmod(nNum2 , nNum1));
}

void simple_vm_neg ( VM *pVM )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE((SIMPLE_VM_STACK_READN)*(-1));
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_SETNVALUE((nNum1)*(-1));
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(pVM,"neg",0);
	}
}
/*
**  compare 
**  Here the conversion to string/number before comparing is not important 
**  Because the result is always logical (True/False) i.e. 1 or 0 
*/

void simple_vm_equal ( VM *pVM )
{
	String *cStr1,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
			if ( strcmp(simple_stsimple_get(cStr1),simple_stsimple_get(cStr2)) == 0 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
			simple_stsimple_delete_gc(pVM->pRingState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum1 = SIMPLE_VM_STACK_READN ;
			simple_vm_numtostring(pVM,nNum1,cStr3);
			if ( strcmp(simple_stsimple_get(cStr1),cStr3) == 0 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"=",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
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
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			if ( simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC) == nNum1 ) {
				SIMPLE_VM_STACK_TRUE ;
			} else {
				SIMPLE_VM_STACK_FALSE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"=");
	}
}

void simple_vm_lessequal ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"<=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"<=",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"<=");
		return ;
	}
	/* Compare */
	if ( nNum2 <= nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_less ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"<",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"<",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"<");
		return ;
	}
	/* Compare */
	if ( nNum2 < nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_greater ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,">",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,">",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,">");
		return ;
	}
	/* Compare */
	if ( nNum2 > nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_greaterequal ( VM *pVM )
{
	double nNum1=0,nNum2=0  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,">=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,">=",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,">=");
		return ;
	}
	/* Compare */
	if ( nNum2 >= nNum1 ) {
		SIMPLE_VM_STACK_TRUE ;
	} else {
		SIMPLE_VM_STACK_FALSE ;
	}
}

void simple_vm_notequal ( VM *pVM )
{
	String *cStr1,*cStr2  ;
	double nNum1,nNum2  ;
	char cStr3[100]  ;
	if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
			/* Compare */
			if ( strcmp(simple_stsimple_get(cStr1),simple_stsimple_get(cStr2)) == 0 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
			simple_stsimple_delete_gc(pVM->pRingState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISNUMBER ) {
			nNum2 = SIMPLE_VM_STACK_READN ;
			nNum1 = simple_vm_stringtonum(pVM,simple_stsimple_get(cStr1)) ;
			/* Compare */
			if ( nNum1 == nNum2 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"!=",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
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
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			cStr2 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
			simple_vm_numtostring(pVM,nNum1,cStr3);
			/* Compare */
			if ( strcmp(simple_stsimple_get(cStr2),cStr3) == 0 ) {
				SIMPLE_VM_STACK_FALSE ;
			} else {
				SIMPLE_VM_STACK_TRUE ;
			}
			simple_stsimple_delete_gc(pVM->pRingState,cStr2);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"!=",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"!=");
		return ;
	}
}
/* Logic */

void simple_vm_and ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"and",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 && nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"and",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"and");
	}
}

void simple_vm_or ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"or",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE((nNum1 || nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"or",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"or");
	}
}

void simple_vm_not ( VM *pVM )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		if ( SIMPLE_VM_STACK_READN != 0 ) {
			SIMPLE_VM_STACK_SETNVALUE(0.0);
		} else {
			SIMPLE_VM_STACK_SETNVALUE(1.0);
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		if ( nNum1 == 1.0 ) {
			SIMPLE_VM_STACK_SETNVALUE(0.0);
		} else {
			SIMPLE_VM_STACK_SETNVALUE(1.0);
		}
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(pVM,"not",0);
		return ;
	}
}
/* Bitwise */

void simple_vm_bitand ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE((int) nNum1 &  (int) (SIMPLE_VM_STACK_READN));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"&",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 & (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"&",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"&");
	}
}

void simple_vm_bitor ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"|",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 | (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"|",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"|");
	}
}

void simple_vm_bitshl ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) << (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 << (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"<<",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) << (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 << (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"<<",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"<<");
	}
}

void simple_vm_bitshr ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) >> (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 >> (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,">>",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(( (int) (SIMPLE_VM_STACK_READN) >> (int) nNum1 ));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum2 >> (int) nNum1));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,">>",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,">>");
	}
}

void simple_vm_bitxor ( VM *pVM )
{
	double nNum1,nNum2  ;
	String *cStr1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		nNum1 = SIMPLE_VM_STACK_READN ;
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_npoo(pVM,"^",nNum1);
			return ;
		}
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		cStr1 = simple_stsimple_new_gc(pVM->pRingState,SIMPLE_VM_STACK_READC);
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_POP ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) (SIMPLE_VM_STACK_READN)));
		}
		else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
			nNum2 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
			SIMPLE_VM_STACK_SETNVALUE(((int) nNum1 ^ (int) nNum2));
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_vm_expr_spoo(pVM,"^",simple_stsimple_get(cStr1),simple_stsimple_size(cStr1));
			simple_stsimple_delete_gc(pVM->pRingState,cStr1);
			return ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,cStr1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_ppoo(pVM,"^");
	}
}

void simple_vm_bitnot ( VM *pVM )
{
	double nNum1  ;
	if ( SIMPLE_VM_STACK_ISNUMBER ) {
		SIMPLE_VM_STACK_SETNVALUE(~ (int) SIMPLE_VM_STACK_READN);
	}
	else if ( SIMPLE_VM_STACK_ISSTSIMPLE ) {
		nNum1 = simple_vm_stringtonum(pVM,SIMPLE_VM_STACK_READC);
		SIMPLE_VM_STACK_SETNVALUE(~ (int) nNum1);
	}
	else if ( SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_expr_npoo(pVM,"~",0);
		return ;
	}
}
/* Conversion */

char * simple_vm_numtostring ( VM *pVM,double nNum1,char *cStr )
{
	char cOptions[10]  ;
	if ( nNum1 == (int) nNum1 ) {
		sprintf( cStr , "%.0f" , nNum1 ) ;
	}
	else {
		sprintf( cOptions , "%s%df" , "%.",pVM->nDecimals ) ;
		sprintf( cStr , cOptions , nNum1 ) ;
	}
	return cStr ;
}

double simple_vm_stringtonum ( VM *pVM,const char *cStr )
{
	double nResult  ;
	if ( strlen(cStr) <= 15 ) {
		nResult = atof(cStr);
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NUMERICOVERFLOW);
		return 0.0 ;
	}
	return nResult ;
}
/*
**  Operator Overloading 
**  Stack Pointer then Stack Pointer - Operator Overloading 
*/

void simple_vm_expr_ppoo ( VM *pVM,const char *cStr )
{
	List *pList,*pList2  ;
	Item *pItem  ;
	void *pPointer  ;
	int nType  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		pList = simple_item_getlist(pItem);
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	/* Get Pointer Data */
	pPointer = SIMPLE_VM_STACK_READP ;
	nType = SIMPLE_VM_STACK_OBJTYPE ;
	SIMPLE_VM_STACK_POP ;
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pList2 = (List *) SIMPLE_VM_STACK_READP ;
			pList2 = simple_list_getlist(pList2,SIMPLE_VAR_VALUE);
		}
		else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem = (Item *) SIMPLE_VM_STACK_READP ;
			pList2 = simple_item_getlist(pItem);
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
			return ;
		}
		if ( strcmp(cStr,"+") == 0 ) {
			if ( (simple_vm_oop_isobject(pList2) == 0) ) {
				simple_vm_addlisttolist(pVM,pList,pList2);
				return ;
			}
		}
		else if ( strcmp(cStr,"=") == 0 ) {
			if ( simple_vm_api_iscpointerlist(pList) && simple_vm_api_iscpointerlist(pList2) ) {
				SIMPLE_VM_STACK_POP ;
				if ( simple_vm_api_cpointercmp(pList,pList2) ) {
					SIMPLE_VM_STACK_PUSHNVALUE(1.0) ;
				}
				else {
					SIMPLE_VM_STACK_PUSHNVALUE(0) ;
				}
				return ;
			}
		}
		if ( simple_vm_oop_isobject(pList2) == 1 ) {
			/* Operator Overloading */
			simple_vm_oop_operatoroverloading(pVM,pList2,cStr,SIMPLE_OOPARA_POINTER,"",0,pPointer,nType);
			SIMPLE_VM_STACK_POP ;
		} else {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		}
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Stack Number then Stack Pointer - Operator Overloading */

void simple_vm_expr_npoo ( VM *pVM,const char *cStr,double nNum1 )
{
	List *pList  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		pList = simple_item_getlist(pItem);
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	if ( strcmp(cStr,"+") == 0 ) {
		if ( simple_vm_oop_isobject(pList) == 0 ) {
			simple_list_adddouble_gc(pVM->pRingState,pList,nNum1);
			return ;
		}
	}
	if ( simple_vm_oop_isobject(pList) == 1 ) {
		/* Operator Overloading */
		simple_vm_oop_operatoroverloading(pVM,pList,cStr,SIMPLE_OOPARA_NUMBER,"",nNum1,NULL,0);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Stack String then Stack Pointer - Operator Overloading */

void simple_vm_expr_spoo ( VM *pVM,const char *cStr,const char *cStr2,int nSize )
{
	List *pList  ;
	Item *pItem  ;
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		pList = simple_list_getlist(pList,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		pList = simple_item_getlist(pItem);
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
		return ;
	}
	if ( strcmp(cStr,"+") == 0 ) {
		if ( simple_vm_oop_isobject(pList) == 0 ) {
			simple_list_addstring2_gc(pVM->pRingState,pList,cStr2,nSize);
			return ;
		}
	}
	if ( simple_vm_oop_isobject(pList) == 1 ) {
		/* Operator Overloading */
		simple_vm_oop_operatoroverloading(pVM,pList,cStr,SIMPLE_OOPARA_STSIMPLE,cStr2,0,NULL,0);
		SIMPLE_VM_STACK_POP ;
	} else {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BADVALUES);
	}
}
/* Add List to List */

void simple_vm_addlisttolist ( VM *pVM,List *pList,List *pList2 )
{
	List *pList3, *pList4  ;
	/*
	**  Here we are going to copy the list pList to the list pList2 
	**  We will copy to a temp list first (pList4) 
	**  So we can add the Self object for example to an attribute in this object 
	*/
	pList4 = simple_list_new_gc(pVM->pRingState,0);
	simple_list_copy_gc(pVM->pRingState,pList4,pList);
	pList3 = simple_list_newlist_gc(pVM->pRingState,pList2);
	simple_list_copy_gc(pVM->pRingState,pList3,pList4);
	simple_list_delete_gc(pVM->pRingState,pList4);
	if ( (simple_vm_oop_isobject(pList3) == 1)  && (pVM->pBraceObject == pList) ) {
		pVM->pBraceObject = pList3 ;
		/*
		**  The copied object was created in Temp. memory that will be deleted 
		**  The object contains the self property that contains a pointer to the object in memory 
		**  We need to modify the pointer that point to the old location in Temp. Memory 
		**  The pointer will be changed to point to the new location in the array 
		**  The array maybe global or related to the object state and may stay longer than the Temp. Memory 
		**  Without this modification using self may lead to crash or using corrupted memory 
		*/
		simple_vm_oop_updateselfpointer(pVM,pList3,SIMPLE_OBJTYPE_LISTITEM,simple_list_getitem(pList2,simple_list_getsize(pList2)));
	}
	else if ( (simple_vm_oop_isobject(pList3) == 1)  && (pVM->pBraceObject != pList) ) {
		/*
		**  in ring code if we used mylist + new obj() the init method will be called 
		**  the pVM->pBraceObject will not == pList but we have to update the self pointer! 
		*/
		simple_vm_oop_updateselfpointer(pVM,pList3,SIMPLE_OBJTYPE_LISTITEM,simple_list_getitem(pList2,simple_list_getsize(pList2)));
	}
}
