
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   mathic.h
 * Author: thecarisma
 *
 * Created on February 7, 2018, 3:50 AM
 */

#ifndef MATHIC_H
#define MATHIC_H

#ifdef __cplusplus
extern "C" {
#endif
    
SIMPLE_API void init_simple_module(SimpleState *sState) ;

void math_sin ( void *pointer ) ;

void math_cos ( void *pointer ) ;

void math_tan ( void *pointer ) ;

void math_asin ( void *pointer ) ;

void math_acos ( void *pointer ) ;

void math_atan ( void *pointer ) ;

void math_atan2 ( void *pointer ) ;

//Hyperbolic functions

void math_sinh ( void *pointer ) ;

void math_cosh ( void *pointer ) ;

void math_tanh ( void *pointer ) ;

void math_asinh ( void *pointer ) ;

void math_acosh ( void *pointer ) ;

void math_atanh ( void *pointer ) ;

//Exponential and logarithmic blocks

void math_exp ( void *pointer ) ;

void math_log ( void *pointer ) ;

void math_log10 ( void *pointer ) ;

void math_frexp ( void *pointer ) ;

void math_ldexp ( void *pointer ) ;

void math_modf ( void *pointer ) ;

void math_exp2 ( void *pointer ) ;

void math_expm1 ( void *pointer ) ;

void math_ilogb ( void *pointer ) ;

void math_log1p ( void *pointer ) ;

void math_log2 ( void *pointer ) ;

void math_logb ( void *pointer ) ;

void math_scalbn ( void *pointer ) ;

void math_scalbln ( void *pointer ) ;

//Power blocks

void math_pow ( void *pointer ) ;

void math_sqrt ( void *pointer ) ;

void math_cbrt ( void *pointer ) ;

void math_hypot ( void *pointer ) ;

//Rounding and remainder functions

void math_ceil ( void *pointer ) ;

void math_floor ( void *pointer ) ;

void math_rint ( void *pointer ) ;

void math_round ( void *pointer ) ;

void math_nearbyint ( void *pointer ) ;

void math_remainder ( void *pointer ) ;

void math_fmod ( void *pointer ) ;

void math_trunc ( void *pointer ) ;

//Others 

void math_unsigned ( void *pointer ) ;

void math_rand(void *pointer);

void math_fabs ( void *pointer ) ;

void math_decimals ( void *pointer ) ;

#ifdef __cplusplus
}
#endif

#endif /* MATHIC_H */

