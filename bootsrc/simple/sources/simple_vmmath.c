/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Functions */

void simple_vm_math_loadfunctions ( RingState *pRingState )
{
	simple_vm_funcregister("sin",simple_vm_math_sin);
	simple_vm_funcregister("cos",simple_vm_math_cos);
	simple_vm_funcregister("tan",simple_vm_math_tan);
	simple_vm_funcregister("asin",simple_vm_math_asin);
	simple_vm_funcregister("acos",simple_vm_math_acos);
	simple_vm_funcregister("atan",simple_vm_math_atan);
	simple_vm_funcregister("atan2",simple_vm_math_atan2);
	simple_vm_funcregister("sinh",simple_vm_math_sinh);
	simple_vm_funcregister("cosh",simple_vm_math_cosh);
	simple_vm_funcregister("tanh",simple_vm_math_tanh);
	simple_vm_funcregister("exp",simple_vm_math_exp);
	simple_vm_funcregister("log",simple_vm_math_log);
	simple_vm_funcregister("log10",simple_vm_math_log10);
	simple_vm_funcregister("ceil",simple_vm_math_ceil);
	simple_vm_funcregister("floor",simple_vm_math_floor);
	simple_vm_funcregister("fabs",simple_vm_math_fabs);
	simple_vm_funcregister("pow",simple_vm_math_pow);
	simple_vm_funcregister("sqrt",simple_vm_math_sqrt);
	simple_vm_funcregister("unsigned",simple_vm_math_unsigned);
	simple_vm_funcregister("decimals",simple_vm_math_decimals);
	simple_vm_funcregister("murmur3hash",simple_vm_math_murmur3hash);
}

void simple_vm_math_sin ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(sin(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_cos ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(cos(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_tan ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(tan(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_asin ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(asin(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_acos ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(acos(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_atan ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(atan(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_atan2 ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
		SIMPLE_API_RETNUMBER(atan2(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_sinh ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(sinh(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_cosh ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(cosh(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_tanh ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(tanh(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_exp ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(exp(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_log ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(log(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_log10 ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(log10(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_ceil ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(ceil(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_floor ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(floor(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_fabs ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(fabs(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_pow ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
		SIMPLE_API_RETNUMBER(pow(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_sqrt ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		SIMPLE_API_RETNUMBER(sqrt(SIMPLE_API_GETNUMBER(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_unsigned ( void *pPointer )
{
	unsigned int nNum1,nNum2  ;
	double nNum3  ;
	const char *cStr  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3) ) {
		nNum1 = (unsigned int) SIMPLE_API_GETNUMBER(1) ;
		nNum2 = (unsigned int ) SIMPLE_API_GETNUMBER(2) ;
		cStr = SIMPLE_API_GETSTRING(3) ;
		if ( strcmp(cStr,">>") == 0 ) {
			nNum3 = nNum1 >> nNum2 ;
		}
		else if ( strcmp(cStr,"<<") == 0 ) {
			nNum3 = nNum1 << nNum2 ;
		}
		else if ( strcmp(cStr,"+") == 0 ) {
			nNum3 = nNum1 + nNum2 ;
		}
		else if ( strcmp(cStr,"-") == 0 ) {
			nNum3 = nNum1 - nNum2 ;
		}
		else if ( strcmp(cStr,"*") == 0 ) {
			nNum3 = nNum1 * nNum2 ;
		}
		else if ( strcmp(cStr,"/") == 0 ) {
			if ( nNum2 != 0 ) {
				nNum3 = nNum1 / nNum2 ;
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_VM_ERROR_DIVIDEBYZERO);
				return ;
			}
		}
		else if ( strcmp(cStr,"^") == 0 ) {
			nNum3 = nNum1 ^ nNum2 ;
		}
		else if ( strcmp(cStr,"<") == 0 ) {
			nNum3 = nNum1 < nNum2 ;
		}
		else if ( strcmp(cStr,">") == 0 ) {
			nNum3 = nNum1 > nNum2 ;
		}
		else if ( strcmp(cStr,"<=") == 0 ) {
			nNum3 = nNum1 <= nNum2 ;
		}
		else if ( strcmp(cStr,">=") == 0 ) {
			nNum3 = nNum1 >= nNum2 ;
		}
		else if ( strcmp(cStr,"=") == 0 ) {
			nNum3 = nNum1 == nNum2 ;
		}
		else if ( strcmp(cStr,"!=") == 0 ) {
			nNum3 = nNum1 != nNum2 ;
		}
		else if ( strcmp(cStr,"&") == 0 ) {
			nNum3 = nNum1 & nNum2 ;
		}
		else if ( strcmp(cStr,"|") == 0 ) {
			nNum3 = nNum1 | nNum2 ;
		}
		else if ( strcmp(cStr,"~") == 0 ) {
			nNum3 = ~ nNum1 ;
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
			return ;
		}
		SIMPLE_API_RETNUMBER(nNum3);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void simple_vm_math_decimals ( void *pPointer )
{
	int nNum1  ;
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISNUMBER(1) ) {
			nNum1 = (int) SIMPLE_API_GETNUMBER(1) ;
			if ( (nNum1 >= 0) && (nNum1 <= 14) ) {
				((VM *) pPointer)->nDecimals = nNum1 ;
			}
			else {
				SIMPLE_API_ERROR(SIMPLE_VM_ERROR_BADDECIMALNUMBER);
			}
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
	}
}
/* Hash */

void simple_vm_math_murmur3hash ( void *pPointer )
{
	unsigned int nResult  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISNUMBER(2) ) {
		nResult = simple_murmur3_32(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRINGSIZE(1),SIMPLE_API_GETNUMBER(2));
		SIMPLE_API_RETNUMBER(nResult);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
