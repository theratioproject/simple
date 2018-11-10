
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

/* List */
void list_delete_from_list( void *pointer );
void list_find_in_list( void *pointer );
void list_min_value( void *pointer );
void list_max_value( void *pointer );
void list_insert_into_list( void *pointer );
void list_sort_list( void *pointer );
void list_reverse_list( void *pointer );
void list_binarysearch_in_list( void *pointer );

/* Runtime Dynamic Library Loading */
#define BUILD0(x) x[0]
#define BUILD1(x) BUILD0(x), x[1]
#define BUILD2(x) BUILD1(x), x[2]
#define BUILD3(x) BUILD2(x), x[3]
#define BUILD4(x) BUILD3(x), x[4]
#define BUILD5(x) BUILD4(x), x[5]
#define BUILD6(x) BUILD5(x), x[6]
#define BUILD7(x) BUILD6(x), x[7]
#define BUILD8(x) BUILD7(x), x[8]
#define BUILD9(x) BUILD8(x), x[9]
#define BUILD10(x) BUILD9(x), x[10]
#define BUILD11(x) BUILD10(x), x[11]
#define BUILD12(x) BUILD11(x), x[12]
#define BUILD13(x) BUILD12(x), x[13]
#define BUILD14(x) BUILD13(x), x[14]
#define BUILD15(x) BUILD14(x), x[15]
#define BUILD16(x) BUILD15(x), x[16]
#define BUILD17(x) BUILD16(x), x[17]
#define BUILD18(x) BUILD17(x), x[18]
#define BUILD19(x) BUILD18(x), x[19]
#define BUILD20(x) BUILD19(x), x[20]
#define BUILD21(x) BUILD20(x), x[21]
#define BUILD22(x) BUILD21(x), x[22]
#define BUILD(x, i) BUILD##i(x)

typedef void* (*lp)(int,...);
void* call_func(lp address, List* parameters);
int get_parameter_value(Item * item);
void simple_vm_dll_loadlib (void *pointer) ;
void simple_vm_dll_calllib_function (void *pointer) ;

/* Date and Time */
SIMPLE_API void date_time_clock(void *pointer);
SIMPLE_API void date_time_clock_per_second(void *pointer);
SIMPLE_API void date_time_date(void *pointer);
SIMPLE_API void date_time_time(void *pointer);
SIMPLE_API void date_time_list(void *pointer);
SIMPLE_API void date_time_t_to_list(void *pointer);
SIMPLE_API void date_time_add_days(void *pointer);
int simple_add_leap_year(int nYear);

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
SIMPLE_API void check_characters__(void *pointer,int type);
SIMPLE_API void check_characters_is_alpha_num(void *pointer);
SIMPLE_API void check_characters_is_alpha(void *pointer);
SIMPLE_API void check_characters_is_num(void *pointer);
SIMPLE_API void check_characters_is_cntrl(void *pointer);
SIMPLE_API void check_characters_is_graph(void *pointer);
SIMPLE_API void check_characters_is_lower(void *pointer);
SIMPLE_API void check_characters_is_print(void *pointer);
SIMPLE_API void check_characters_is_punct(void *pointer);
SIMPLE_API void check_characters_is_space(void *pointer);
SIMPLE_API void check_characters_is_upper(void *pointer);
SIMPLE_API void check_characters_is_xdigit(void *pointer);

/* Meta Blocks */ 
SIMPLE_API void meta_blocks_add_addribute(void *pointer);

#ifdef __cplusplus
}
#endif

#endif /* MATHIC_H */

