
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   file_savant.h
 * Author: thecarisma
 *
 * Created on February 9, 2018, 9:02 PM
 */

#ifndef FILE_SAVANT_H
#define FILE_SAVANT_H

#ifdef __cplusplus
extern "C" {
#endif
    
void read_file ( void *pointer ) ;

void write_file ( void *pointer ) ;

void file_exists ( void *pointer ) ;

void file_rename ( void *pointer ) ;

void file_delete ( void *pointer ) ;

void blow_directory ( void *pointer ) ;

void mk_directory ( void *pointer ) ;

void dir_exists ( void *pointer ) ;

/* Constants */
#define SIMPLE_VM_FILE_BUFFERSIZE "Buffer size must be >= 1"
#define SIMPLE_VM_POINTER_FILE "file"
#define SIMPLE_VM_POINTER_FILEPOS "filepos"
#define SIMPLE_API_BADDIRECTORY "Error, Couldn't open the directory"
    
/* Data */
typedef union Simple_uData {
	int iNumber  ;
	float fNumber  ;
	double dNumber  ;
	char cBytes[4]  ;
	char cBytesDouble[8]  ;
} Simple_uData ;

#include <sys/types.h>
#include <sys/stat.h>

#define S_ISDIR(m) (((m) & 0170000) == (0040000))

#ifdef __cplusplus
}
#endif

#endif /* FILE_SAVANT_H */

