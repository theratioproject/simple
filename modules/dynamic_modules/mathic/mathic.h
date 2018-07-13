
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
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

void math_sinh ( void *pointer ) ;

void math_cosh ( void *pointer ) ;

void math_tanh ( void *pointer ) ;

void math_exp ( void *pointer ) ;

void math_log ( void *pointer ) ;

void math_log10 ( void *pointer ) ;

void math_ceil ( void *pointer ) ;

void math_floor ( void *pointer ) ;

void math_fabs ( void *pointer ) ;

void math_pow ( void *pointer ) ;

void math_sqrt ( void *pointer ) ;

void math_unsigned ( void *pointer ) ;

void math_decimals ( void *pointer ) ;

#ifdef __cplusplus
}
#endif

#endif /* MATHIC_H */

