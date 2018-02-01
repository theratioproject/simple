/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/ring.h"
/* Functions */

void ring_vm_math_loadfunctions ( RingState *pRingState )
{
	ring_vm_funcregister("sin",ring_vm_math_sin);
	ring_vm_funcregister("cos",ring_vm_math_cos);
	ring_vm_funcregister("tan",ring_vm_math_tan);
	ring_vm_funcregister("asin",ring_vm_math_asin);
	ring_vm_funcregister("acos",ring_vm_math_acos);
	ring_vm_funcregister("atan",ring_vm_math_atan);
	ring_vm_funcregister("atan2",ring_vm_math_atan2);
	ring_vm_funcregister("sinh",ring_vm_math_sinh);
	ring_vm_funcregister("cosh",ring_vm_math_cosh);
	ring_vm_funcregister("tanh",ring_vm_math_tanh);
	ring_vm_funcregister("exp",ring_vm_math_exp);
	ring_vm_funcregister("log",ring_vm_math_log);
	ring_vm_funcregister("log10",ring_vm_math_log10);
	ring_vm_funcregister("ceil",ring_vm_math_ceil);
	ring_vm_funcregister("floor",ring_vm_math_floor);
	ring_vm_funcregister("fabs",ring_vm_math_fabs);
	ring_vm_funcregister("pow",ring_vm_math_pow);
	ring_vm_funcregister("sqrt",ring_vm_math_sqrt);
	ring_vm_funcregister("unsigned",ring_vm_math_unsigned);
	ring_vm_funcregister("decimals",ring_vm_math_decimals);
	ring_vm_funcregister("murmur3hash",ring_vm_math_murmur3hash);
}

void ring_vm_math_sin ( void *pPointer )
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

void ring_vm_math_cos ( void *pPointer )
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

void ring_vm_math_tan ( void *pPointer )
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

void ring_vm_math_asin ( void *pPointer )
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

void ring_vm_math_acos ( void *pPointer )
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

void ring_vm_math_atan ( void *pPointer )
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

void ring_vm_math_atan2 ( void *pPointer )
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

void ring_vm_math_sinh ( void *pPointer )
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

void ring_vm_math_cosh ( void *pPointer )
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

void ring_vm_math_tanh ( void *pPointer )
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

void ring_vm_math_exp ( void *pPointer )
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

void ring_vm_math_log ( void *pPointer )
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

void ring_vm_math_log10 ( void *pPointer )
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

void ring_vm_math_ceil ( void *pPointer )
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

void ring_vm_math_floor ( void *pPointer )
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

void ring_vm_math_fabs ( void *pPointer )
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

void ring_vm_math_pow ( void *pPointer )
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

void ring_vm_math_sqrt ( void *pPointer )
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

void ring_vm_math_unsigned ( void *pPointer )
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

void ring_vm_math_decimals ( void *pPointer )
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

void ring_vm_math_murmur3hash ( void *pPointer )
{
	unsigned int nResult  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISNUMBER(2) ) {
		nResult = ring_murmur3_32(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRINGSIZE(1),SIMPLE_API_GETNUMBER(2));
		SIMPLE_API_RETNUMBER(nResult);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
