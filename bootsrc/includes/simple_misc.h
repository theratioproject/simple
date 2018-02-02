
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_misc.h
 * Author: thecarisma
 *
 * Created on July 12, 2017, 3:31 PM
 */

#ifndef SIMPLE_MISC_H
#define SIMPLE_MISC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define SIMPLE_VERSION "0.3.2"
#define KB_BYTE_SIZE 1024
    
extern int NOT_CASE_SENSITIVE ;

void display_help();

int is_simple_file( const char *file_name );

int is_complex_file( const char *file_name );

const char *file_real_name(const char *absolute_name);


#ifdef __cplusplus
}
#endif

#endif /* SIMPLE_MISC_H */

