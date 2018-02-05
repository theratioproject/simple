
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
#define PRIMARY_AUTHOR "Azeez Adewale"
#define START_YEAR 2016
#define CURRENT_YEAR 2018
#define AUTHOR "The Simpletons"
#define SIMPLE_LICENCE "MIT Licence"
#define KB_BYTE_SIZE 1024
    
/*Fields*/
    
extern int NOT_CASE_SENSITIVE ;

extern int SKIP_ERROR ;

extern char *DEFAULT_FILE_NAME ;

extern char *DEFAULT_FILE_PATH ;

/*Functions*/

void display_help();

void display_licence();

void display_about();

int is_simple_file( const char *file_name );

int is_complex_file( const char *file_name );

const char *file_real_name(const char *absolute_name);

const char *change_file_ext(const char *absolute_name, const char *extension);

void get_file_folder ( char *absolute_path ) ;

#if SIMPLE_TESTPERFORMANCE

void simple_showtime ( time_t before_execution, time_t after_execution ) ;

char* get_time_different(double diff) ;

#endif

#ifdef __cplusplus
}
#endif

#endif /* SIMPLE_MISC_H */

