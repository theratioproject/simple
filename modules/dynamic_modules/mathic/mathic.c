
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

#include "../../../simple/include/simple.h"
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

#ifdef log2
#else
#define log2(x) (log(x)*1.4426950408889634)
#endif

#ifdef scalbln
#else
#define scalbln(x,y) (log(x)*log(y))
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
	//Trigonometric blocks
    register_block("__sin",math_sin);
    register_block("__cos",math_cos);
    register_block("__tan",math_tan);
    register_block("__asin",math_asin);
    register_block("__acos",math_acos);
    register_block("__atan",math_atan);
    register_block("__atan2",math_atan2);
	
	//Hyperbolic blocks
    register_block("__sinh",math_sinh);
    register_block("__cosh",math_cosh);
    register_block("__tanh",math_tanh);
    register_block("__asinh",math_asinh);
    register_block("__acosh",math_acosh);
    register_block("__atanh",math_atanh);
	
	//Rounding and remainder blocks
    register_block("__rint",math_rint);
    register_block("__round",math_round);
    register_block("__floor",math_floor);
    register_block("__ceil",math_ceil);
    register_block("__fmod",math_fmod);
    register_block("__trunc",math_trunc);
    register_block("__remainder",math_remainder);
    register_block("__nearbyint",math_nearbyint);
	
	//Exponential and logarithmic blocks
    register_block("__exp",math_exp);
    register_block("__log",math_log);
    register_block("__log10",math_log10);
    register_block("__frexp",math_frexp);
    register_block("__ldexp",math_ldexp);
    register_block("__modf",math_modf);
    register_block("__exp2",math_exp2);
    register_block("__expm1",math_expm1);
    register_block("__ilogb",math_ilogb);
    register_block("__log1p",math_log1p);
    register_block("__log2",math_log2);
    register_block("__logb",math_logb);
    register_block("__scalbn",math_scalbn);
    register_block("__scalbln",math_scalbln);
	
	//Power blocks
    register_block("__pow",math_pow);
    register_block("__sqrt",math_sqrt);
    register_block("__cbrt",math_cbrt);
    register_block("__hypot",math_hypot);
	
	//others
    register_block("__rand",math_rand);
    register_block("__unsigned",math_unsigned);
    register_block("__decimals",math_decimals);
    register_block("__fabs",math_fabs);
}

//Trigonometric blocks

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

//Hyperbolic functions

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

void math_asinh ( void *pointer )
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

void math_acosh ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(acosh(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_atanh ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(atanh(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

//Exponential and logarithmic blocks

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

void math_frexp ( void *pointer )
{
	List *list ;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
			int n ;			
			list = SIMPLE_API_NEWLIST;
			simple_list_adddouble_gc(((VM *) pointer)->sState,list,frexp(SIMPLE_API_GETNUMBER(1),&n));
			simple_list_adddouble_gc(((VM *) pointer)->sState,list,n);
			SIMPLE_API_RETLIST(list);
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_ldexp ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(ldexp(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_modf ( void *pointer )
{
	List *list ;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1)) {
			double n ;			
			list = SIMPLE_API_NEWLIST;
			simple_list_adddouble_gc(((VM *) pointer)->sState,list,modf(SIMPLE_API_GETNUMBER(1),&n));
			simple_list_adddouble_gc(((VM *) pointer)->sState,list,n);
			SIMPLE_API_RETLIST(list);
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_exp2 ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(exp2(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_expm1 ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(expm1(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_ilogb ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(ilogb(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_log1p ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(log1p(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_log2 ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(log2(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_logb ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(logb(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_scalbn ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(scalbn(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_scalbln ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(scalbln(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

//Power blocks

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

void math_cbrt ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(cbrt(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_hypot ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(hypot(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

//Rounding and remainder functions

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

void math_rint ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(rint(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_round ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(round(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_nearbyint ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(nearbyint(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_remainder ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(remainder(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_fmod ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
            SIMPLE_API_RETNUMBER(fmod(SIMPLE_API_GETNUMBER(1),SIMPLE_API_GETNUMBER(2)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void math_trunc ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
            SIMPLE_API_RETNUMBER(trunc(SIMPLE_API_GETNUMBER(1)));
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

//Others 

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

void math_rand(void *pointer)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
            SIMPLE_API_ERROR("no parameter Expected ");
            return ;
    }
    SIMPLE_API_RETNUMBER(rand());
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

