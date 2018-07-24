
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

void path_status_date(void *pointer);
void path_modify_date(void *pointer);
void path_access_date(void *pointer);
void path_gid(void *pointer);
void path_uid(void *pointer);
void path_link_count(void *pointer);
void path_node_number(void *pointer);
void path_type(void *pointer);
void path_size(void *pointer);
void check_path(void *pointer);
void read_file(void *pointer);
void write_file(void *pointer);
void file_exists(void *pointer);
void file_rename(void *pointer);
void file_delete(void *pointer);
void file_delete_folder(void *pointer);
void blow_directory(void *pointer);
void mk_directory(void *pointer);
void dir_exists(void *pointer) ;

/* Constants */
#define SIMPLE_VM_FILE_BUFFERSIZE "Buffer size must be >= 1"
#define SIMPLE_VM_POINTER_FILE "file"
#define SIMPLE_VM_POINTER_FILEPOS "filepos"
#define SIMPLE_API_BADDIRECTORY "Error, Couldn't open the directory"
#define FILE_SAVANT_FILE_ERROR "Error occur while stating the file, check the file existence and permissions"
    
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

/*
**	Do nothing if S_ISDIR is defined
**	Else define it Issue with Microsoft Visual Studio
*/
#ifdef S_ISDIR
#else
#if defined(_MSC_VER) && _MSC_VER < 1900
#define S_ISDIR(m) (((m) & 0170000) == (0040000))
#endif
#endif

#if !defined(S_IFLNK)
#define        S_IFLNK  0120000  /* symbolic link */
#endif

#if !defined(S_IFSOCK)
#define        S_IFSOCK  0140000  /* socket */
#endif

#if !defined(S_IFWHT)
#define        S_IFWHT  0160000  /* whiteout */
#endif

#ifdef __cplusplus
}
#endif

#endif /* FILE_SAVANT_H */

