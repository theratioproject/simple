
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   mathic.h 
 * Author: thecarisma
 *
 * Created on Febuary 7, 2018, 3:23 AM
 */

#include "../../../simple/includes/simple.h"
#include "mathic.h"

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
    register_block("sin",math_sin);
    register_block("cos",math_cos);
    register_block("tan",math_tan);
    register_block("asin",math_asin);
    register_block("acos",math_acos);
    register_block("atan",math_atan);
    register_block("atan2",math_atan2);
    register_block("sinh",math_sinh);
    register_block("cosh",math_cosh);
    register_block("tanh",math_tanh);
    register_block("exp",math_exp);
    register_block("log",math_log);
    register_block("log10",math_log10);
    register_block("ceil",math_ceil);
    register_block("floor",math_floor);
    register_block("fabs",math_fabs);
    register_block("pow",math_pow);
    register_block("sqrt",math_sqrt);
    register_block("unsigned",math_unsigned);
    register_block("decimals",math_decimals);
}

void math_sin ( void *pointer )
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

void math_cos ( void *pointer )
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

void math_tan ( void *pointer )
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

void math_asin ( void *pointer )
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

void math_acos ( void *pointer )
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

void math_atan ( void *pointer )
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

void math_atan2 ( void *pointer )
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

void math_sinh ( void *pointer )
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

void math_cosh ( void *pointer )
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

void math_tanh ( void *pointer )
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

void math_exp ( void *pointer )
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

void math_log ( void *pointer )
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

void math_log10 ( void *pointer )
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

void math_ceil ( void *pointer )
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

void math_floor ( void *pointer )
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

void math_fabs ( void *pointer )
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

void math_pow ( void *pointer )
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

void math_sqrt ( void *pointer )
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

void math_unsigned ( void *pointer )
{
    unsigned int num1,num2  ;
    double num3  ;
    const char *str  ;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3) ) {
            num1 = (unsigned int) SIMPLE_API_GETNUMBER(1) ;
            num2 = (unsigned int ) SIMPLE_API_GETNUMBER(2) ;
            str = SIMPLE_API_GETSTRING(3) ;
            if ( strcmp(str,">>") == 0 ) {
                    num3 = num1 >> num2 ;
            }
            else if ( strcmp(str,"<<") == 0 ) {
                    num3 = num1 << num2 ;
            }
            else if ( strcmp(str,"+") == 0 ) {
                    num3 = num1 + num2 ;
            }
            else if ( strcmp(str,"-") == 0 ) {
                    num3 = num1 - num2 ;
            }
            else if ( strcmp(str,"*") == 0 ) {
                    num3 = num1 * num2 ;
            }
            else if ( strcmp(str,"/") == 0 ) {
                    if ( num2 != 0 ) {
                            num3 = num1 / num2 ;
                    }
                    else {
                            SIMPLE_API_ERROR(SIMPLE_VM_ERROR_DIVIDEBYZERO);
                            return ;
                    }
            }
            else if ( strcmp(str,"^") == 0 ) {
                    num3 = num1 ^ num2 ;
            }
            else if ( strcmp(str,"<") == 0 ) {
                    num3 = num1 < num2 ;
            }
            else if ( strcmp(str,">") == 0 ) {
                    num3 = num1 > num2 ;
            }
            else if ( strcmp(str,"<=") == 0 ) {
                    num3 = num1 <= num2 ;
            }
            else if ( strcmp(str,">=") == 0 ) {
                    num3 = num1 >= num2 ;
            }
            else if ( strcmp(str,"=") == 0 ) {
                    num3 = num1 == num2 ;
            }
            else if ( strcmp(str,"!=") == 0 ) {
                    num3 = num1 != num2 ;
            }
            else if ( strcmp(str,"&") == 0 ) {
                    num3 = num1 & num2 ;
            }
            else if ( strcmp(str,"|") == 0 ) {
                    num3 = num1 | num2 ;
            }
            else if ( strcmp(str,"~") == 0 ) {
                    num3 = ~ num1 ;
            } else {
                    SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
                    return ;
            }
            SIMPLE_API_RETNUMBER(num3);
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_decimals ( void *pointer )
{
    int num1  ;
    if ( SIMPLE_API_PARACOUNT == 1 ) {
            if ( SIMPLE_API_ISNUMBER(1) ) {
                    num1 = (int) SIMPLE_API_GETNUMBER(1) ;
                    if ( (num1 >= 0) && (num1 <= 14) ) {
                            ((VM *) pointer)->nDecimals = num1 ;
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


