
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

/* Error and Warn */

SIMPLE_API void error_warn(void *pointer);

SIMPLE_API void error_stack_trace(void *pointer);

SIMPLE_API void error_throw(void *pointer);

/* Conversion */
SIMPLE_API void conversion_string_to_chex (void *pointer) ;

SIMPLE_API void conversion_string_to_list (void *pointer) ;

#ifdef __cplusplus
}
#endif

#endif /* MATHIC_H */

