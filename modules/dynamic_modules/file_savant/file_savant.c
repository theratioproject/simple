
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   file_savant.c
 * Author: thecarisma
 *
 * Created on February 9, 2018, 9:01 PM
 */

#include "../../../simple/includes/simple.h"
#include "../../../simple/includes/simple_state.h"
#include "file_savant.h"
#ifdef _WIN32
#else
#include <sys/stat.h>
#include <dirent.h>
#endif

#ifdef _WIN32
	#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
    register_block("readfile",read_file);
    register_block("writefile",write_file);
    register_block("__exists",file_exists);
    register_block("__rename",file_rename);
    register_block("__delete",file_delete);
    register_block("blow_dir",blow_directory);
    register_block("__mkdir",mk_directory);
    register_block("__dir_exists",dir_exists);
}

void read_file ( void *pointer )
{
	FILE *fp  ;
	long int nSize  ;
	char *cBuffer  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		fp = fopen(SIMPLE_API_GETSTRING(1) , "rb" );
		if ( fp == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_CANTOPENFILE);
			return ;
		}
		fseek( fp , 0 , SEEK_END );
		nSize = ftell(fp);
		fseek( fp , 0 , SEEK_SET );
		cBuffer = (char *) simple_state_malloc(((VM *) pointer)->sState,nSize);
		if ( cBuffer == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		fread( cBuffer , 1 , nSize , fp );
		fclose( fp ) ;
		SIMPLE_API_RETSTRING2(cBuffer,nSize);
		simple_state_free(((VM *) pointer)->sState,cBuffer);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void write_file ( void *pointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_ISSTRING(2) ) {
			fp = fopen(SIMPLE_API_GETSTRING(1) , "w+b" );
			if ( fp == NULL ) {
				SIMPLE_API_ERROR(SIMPLE_VM_ERROR_CANTOPENFILE);
				return ;
			}
			fwrite( SIMPLE_API_GETSTRING(2) , SIMPLE_API_GETSTRINGSIZE(2) , 1 , fp );
			fclose( fp ) ;
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires string !");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void file_exists ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            FILE *fp  ;
            fp = fopen(SIMPLE_API_GETSTRING(1) , "r" );
            if ( fp ) {
                fclose( fp ) ;
                SIMPLE_API_RETNUMBER(1);
            } else {
                fclose( fp ) ;
                SIMPLE_API_RETNUMBER(0);
            }
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void file_rename ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
		rename(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void file_delete ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		remove(SIMPLE_API_GETSTRING(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void blow_directory ( void *pointer )
{
	const char *cStr  ;
	List *pList, *pList2  ;
	#ifdef _WIN32
	/* Windows Only */
	WIN32_FIND_DATA fdFile  ;
	HANDLE hFind  ;
	String *pString  ;
	#else
	DIR *pDir  ;
	struct dirent *pDirent  ;
	struct stat st  ;
	#endif
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1);
		pList = SIMPLE_API_NEWLIST ;
		#ifdef _WIN32
		/* Windows Only */
		pString = simple_string_new_gc(((VM *) pointer)->sState,cStr);
		simple_string_add_gc(((VM *) pointer)->sState,pString,"\\*.*");
		cStr = simple_string_get(pString);
		if ( ! ((hFind = FindFirstFile(cStr, &fdFile)) == INVALID_HANDLE_VALUE) ) {
			do {
				if ( strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0 ) {
					pList2 = simple_list_newlist_gc(((VM *) pointer)->sState,pList);
					simple_list_addstring_gc(((VM *) pointer)->sState,pList2,fdFile.cFileName);
					if ( fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
						simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,1);
					} else {
						simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,0);
					}
				}
			} while (FindNextFile(hFind, &fdFile))  ;
			SIMPLE_API_RETLIST(pList);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADDIRECTORY);
		}
		simple_string_delete_gc(((VM *) pointer)->sState,pString);
		#else
		pDir = opendir(cStr);
		if ( pDir != NULL ) {
			while ( (pDirent = readdir(pDir)) ) {
				pList2 = simple_list_newlist_gc(((VM *) pointer)->sState,pList);
				simple_list_addstring_gc(((VM *) pointer)->sState,pList2,pDirent->d_name);
				stat(pDirent->d_name,&st);
				if ( S_ISDIR(st.st_mode) ) {
					simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,1);
				} else {
					simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,0);
				}
			}
			closedir(pDir);
			SIMPLE_API_RETLIST(pList);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADDIRECTORY);
		}
		#endif
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void mk_directory ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            #ifdef _WIN32
                SIMPLE_API_RETNUMBER(_mkdir(SIMPLE_API_GETSTRING(1)));
            #else
                SIMPLE_API_RETNUMBER(mkdir(SIMPLE_API_GETSTRING(1), 0755)); 
            #endif
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void dir_exists ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            struct stat info;
            int err = stat(SIMPLE_API_GETSTRING(1), &info);
            if (err == -1 ) {
                if (ENOENT == errno) {
                    SIMPLE_API_RETNUMBER(-1); //does not exist
                } else {
                    SIMPLE_API_RETNUMBER(-2); //unknown error 
                }
            } else {
                if (S_ISDIR(info.st_mode)) {
                    SIMPLE_API_RETNUMBER(1); //it is a directory
                } else {
                    SIMPLE_API_RETNUMBER(0); //it not a directory
                }
            }
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
