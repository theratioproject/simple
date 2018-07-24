
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

/* Date and Time */
SIMPLE_API void date_time_clock(void *pointer);
SIMPLE_API void date_time_clock_per_second(void *pointer);
SIMPLE_API void date_time_date(void *pointer);
SIMPLE_API void date_time_time(void *pointer);
SIMPLE_API void date_time_list(void *pointer);

/* Error and Warn */
SIMPLE_API void error_warn(void *pointer);
SIMPLE_API void error_stack_trace(void *pointer);
SIMPLE_API void error_throw(void *pointer);

/* Conversion */
SIMPLE_API void conversion_string_to_hex(void *pointer);
SIMPLE_API void conversion_string_to_chex (void *pointer);
SIMPLE_API void conversion_hex_to_string(void *pointer);
SIMPLE_API void conversion_string_to_list (void *pointer);

/* Characters Checking */ 
SIMPLE_API void check_characters_is_block(void *pointer,int (*block)(int));
SIMPLE_API void check_characters_is_alpha_num(void *pointer);

/* Meta Blocks */ 
SIMPLE_API void meta_blocks_add_addribute(void *pointer);

#ifdef __cplusplus
}
#endif

#endif /* MATHIC_H */

