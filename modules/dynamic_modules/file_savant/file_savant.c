
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
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
    register_block("__path_absolute_path",path_absolute_path);
    register_block("__path_block_size",path_block_size);
    register_block("__path_blocks",path_blocks);
    register_block("__path_access_date",path_access_date);
    register_block("__path_modify_date",path_modify_date);
    register_block("__path_status_date",path_status_date);
    register_block("__path_uid",path_uid);
    register_block("__path_gid",path_gid);
    register_block("__path_link_count",path_link_count);
    register_block("__path_node_number",path_node_number);
    register_block("__path_type",path_type);
    register_block("__path_size",path_size);
    register_block("__check_path",check_path);
    register_block("__rename",file_rename);
    register_block("__delete",file_delete);
    register_block("__delete_directory",file_delete_folder);
    register_block("blow_dir",blow_directory);
    register_block("__mkdir",mk_directory);
    register_block("__dir_exists",dir_exists);
}

void path_absolute_path(void *pointer)
{
	char resolved_path[SIMPLE_PATHSIZE];
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		#ifdef _WIN32
			_fullpath(resolved_path, SIMPLE_API_GETSTRING(1), SIMPLE_PATHSIZE);
		#else
			realpath(SIMPLE_API_GETSTRING(1), resolved_path);
		#endif
		SIMPLE_API_RETSTRING(resolved_path);
	}
}

void path_blocks(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				#ifdef info.st_blocks
					SIMPLE_API_RETNUMBER((long) info.st_blksize);
				#else
					SIMPLE_API_RETNUMBER(-1);
				#endif
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_block_size(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				#ifdef info.st_blksize
					SIMPLE_API_RETNUMBER((long) info.st_blksize);
				#else
					SIMPLE_API_RETNUMBER(512);
				#endif
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_status_date(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETCPOINTER(info.st_ctime,"SIMPLE_LANG_TIME_");
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_modify_date(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETCPOINTER(info.st_mtime,"SIMPLE_LANG_TIME_");
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_access_date(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETCPOINTER(info.st_atime,"SIMPLE_LANG_TIME_");
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_gid(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETNUMBER((long) info.st_gid);
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_uid(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETNUMBER((long) info.st_uid);
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_link_count(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETNUMBER((long) info.st_nlink);
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_node_number(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				SIMPLE_API_RETNUMBER((long) info.st_ino);
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_type(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1));
            int err = stat(string->str, &info);
			if (err == -1) {
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			} else {
				switch (info.st_mode & S_IFMT) {
					case S_IFWHT:  SIMPLE_API_RETNUMBER(160000);	break; 
					case S_IFBLK:  SIMPLE_API_RETNUMBER(60000);	break;
					case S_IFCHR:  SIMPLE_API_RETNUMBER(20000);	break;
					case S_IFDIR:  SIMPLE_API_RETNUMBER(40000);	break;
					case S_IFIFO:  SIMPLE_API_RETNUMBER(10000);	break;
					case S_IFLNK:  SIMPLE_API_RETNUMBER(120000);	break;
					case S_IFREG:  SIMPLE_API_RETNUMBER(100000);	break;
					case S_IFSOCK: SIMPLE_API_RETNUMBER(140000);	break;
					default:       SIMPLE_API_RETNUMBER(0000000);   break;
				}
			}
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void path_size(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1)); 
            int err = stat(string->str, &info);
			if (err == -1) 
				SIMPLE_API_ERROR(FILE_SAVANT_FILE_ERROR);
			else
				SIMPLE_API_RETNUMBER((long long) info.st_size);
			
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void check_path(void *pointer)
{
	struct stat info;
	String * string;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
            string = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(1)); 
            int err = stat(string->str, &info);
			SIMPLE_API_RETNUMBER(err);
			simple_string_delete_gc(((VM *) pointer)->sState,string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void read_file(void *pointer)
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
		if (rename(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2)) == 0) {
			SIMPLE_API_RETNUMBER(1);
		} else {
			SIMPLE_API_RETNUMBER(0);
		}
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
		#ifdef unlink
			SIMPLE_API_RETNUMBER(unlink(SIMPLE_API_GETSTRING(1)));
		#else
			SIMPLE_API_RETNUMBER(remove(SIMPLE_API_GETSTRING(1)));
		#endif
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void file_delete_folder ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		#ifdef _WIN32
			SIMPLE_API_RETNUMBER(RemoveDirectory(SIMPLE_API_GETSTRING(1)));
		#else
			#ifdef rmdir
				SIMPLE_API_RETNUMBER(rmdir(SIMPLE_API_GETSTRING(1)));
			#else
				SIMPLE_API_RETNUMBER(remove(SIMPLE_API_GETSTRING(1)));
			#endif
		#endif
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
	String *child_string;
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
				child_string = simple_string_new_gc(((VM *) pointer)->sState,cStr);
				simple_string_add_gc(((VM *) pointer)->sState,child_string,pDirent->d_name);
				if ( strcmp(pDirent->d_name, ".") != 0 && strcmp(pDirent->d_name, "..") != 0 ) {
					pList2 = simple_list_newlist_gc(((VM *) pointer)->sState,pList);
					simple_list_addstring_gc(((VM *) pointer)->sState,pList2,pDirent->d_name);
					int err = stat(child_string->str,&st);
					switch (st.st_mode & S_IFMT) {
						case S_IFWHT:  SIMPLE_API_RETNUMBER(160000);	break; 
						case S_IFBLK:  SIMPLE_API_RETNUMBER(60000);	break;
						case S_IFCHR:  SIMPLE_API_RETNUMBER(20000);	break;
						case S_IFDIR:  simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,1);	break;
						case S_IFIFO:  SIMPLE_API_RETNUMBER(10000);	break;
						case S_IFLNK:  SIMPLE_API_RETNUMBER(120000);	break;
						case S_IFREG:  simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,0);	break;
						case S_IFSOCK: SIMPLE_API_RETNUMBER(140000);	break;
						default:       SIMPLE_API_RETNUMBER(0000000);   break;
					}
				}
			}
			closedir(pDir);
			SIMPLE_API_RETLIST(pList);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADDIRECTORY);
		}
		simple_string_delete_gc(((VM *) pointer)->sState,child_string);
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
