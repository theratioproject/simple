
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_misc.h
 * Author: Azeez Adewale
 *
 * Created on July 12, 2017, 3:31 PM
 */

#ifndef SIMPLE_MISC_H
#define SIMPLE_MISC_H

#ifdef __cplusplus
extern "C" {
#endif

/*
	Support for GCC Compiler with no TRUE and FALSE predefine
	Starting with Haiku OS
*/
#ifdef TRUE 
#else
#define TRUE 1
#endif
#ifdef FALSE
#else
#define FALSE 0
#endif
    
typedef struct GCData {
	int nReferenceCount  ;
} GCData ;

#define SIMPLE_NAME "simple"
#define SIMPLE_VERSION "0.4.0"
#define PRIMARY_AUTHOR "Azeez Adewale"
#define START_YEAR 2018
#define CURRENT_YEAR 2019
#define AUTHOR "The Simple Team"
#define SIMPLE_LICENCE "MIT Licence"
#define KB_BYTE_SIZE 1024
    
/*Fields*/
extern char simple_file_initial_dir[SIMPLE_PATHSIZE];

extern char* time_frame ;

/*Blocks*/

void display_help();

void display_version();

SIMPLE_API int is_simple_file( const char *file_name );

SIMPLE_API int is_complex_file( const char *file_name );

SIMPLE_API const char *file_real_name(const char *absolute_name);

SIMPLE_API void remove_file_ext(char file_name[], const char *absolute_name);

SIMPLE_API void last_text_after_char(char new_text[], char *old_text, char c);

SIMPLE_API void get_file_folder ( char *absolute_path ) ;

#if SIMPLE_TESTPERFORMANCE

void simple_showtime ( clock_t before_execution ) ;
float get_time_different(float diff) ;

unsigned simple_hash(unsigned pid);
unsigned simple_add_hash(unsigned char *key, int len);
unsigned simple_xor_hash(unsigned char *key, int len);
unsigned simple_rot_hash(unsigned char *key, int len);
unsigned simple_djb_hash(unsigned char *key, int len);
unsigned simple_sax_hash(unsigned char *key, int len);
unsigned simple_fnv_hash(unsigned char *key, int len);
unsigned simple_oat_hash(unsigned char *key, int len);
unsigned simple_elf_hash(unsigned char *key, int len);
unsigned simple_jen_hash(unsigned char *k, unsigned length, unsigned initval);
unsigned int simple_murmur3_32(const char *key, unsigned int len, unsigned int seed) ;

#endif

#ifdef __cplusplus
}
#endif

#endif /* SIMPLE_MISC_H */

