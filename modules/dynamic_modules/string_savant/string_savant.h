/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   string_savant.h
 * Author: thecarisma
 *
 * Created on February 9, 2018, 12:48 AM
 */

#ifndef STRING_SAVANT_H
#define STRING_SAVANT_H

#ifdef __cplusplus
extern "C" {
#endif

void simple_vmlib_lower ( void *pointer ) ;

void simple_vmlib_upper ( void *pointer ) ;

void simple_vmlib_left ( void *pointer ) ;

void simple_vmlib_right ( void *pointer ) ;

void simple_vmlib_trim ( void *pointer ) ;

void simple_vmlib_copy ( void *pointer ) ;

void simple_vmlib_substr ( void *pointer ) ;

void simple_vmlib_lines ( void *pointer ) ;

void simple_vmlib_strcmp ( void *pointer ) ;

void string_replace ( void *pointer ) ;

void string_last_char ( void *pointer ) ;

void split_string ( void *pointer ) ;


#ifdef __cplusplus
}
#endif

#endif /* STRING_SAVANT_H */

