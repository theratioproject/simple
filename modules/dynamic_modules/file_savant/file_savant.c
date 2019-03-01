
#include "../../../simple/include/simple.h"
#include "../../../simple/include/simple_state.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>



/*
  Copyright (C) 2014 Yusuke Suzuki <utatane.tea@gmail.com>

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* 
    Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   consoler.h
 * Author: thecarisma
 *
 * Created on February 11, 2018, 12:28 AM
 */
 
#ifndef _WIN32
#include <dirent.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(lstat) 
#define lstat(path, statstruct) stat(path, statstruct)
#endif

#define CC_COLOR_BITS 5

typedef enum {
    CC_FG_NONE         = 0  << 0,
    CC_FG_BLACK        = 1  << 0,
    CC_FG_DARK_RED     = 2  << 0,
    CC_FG_DARK_GREEN   = 3  << 0,
    CC_FG_DARK_YELLOW  = 4  << 0,
    CC_FG_DARK_BLUE    = 5  << 0,
    CC_FG_DARK_MAGENTA = 6  << 0,
    CC_FG_DARK_CYAN    = 7  << 0,
    CC_FG_GRAY         = 8  << 0,
    CC_FG_DARK_GRAY    = 9  << 0,
    CC_FG_RED          = 10 << 0,
    CC_FG_GREEN        = 11 << 0,
    CC_FG_YELLOW       = 12 << 0,
    CC_FG_BLUE         = 13 << 0,
    CC_FG_MAGENTA      = 14 << 0,
    CC_FG_CYAN         = 15 << 0,
    CC_FG_WHITE        = 16 << 0,

    CC_BG_NONE         = 0  << CC_COLOR_BITS,
    CC_BG_BLACK        = 1  << CC_COLOR_BITS,
    CC_BG_DARK_RED     = 2  << CC_COLOR_BITS,
    CC_BG_DARK_GREEN   = 3  << CC_COLOR_BITS,
    CC_BG_DARK_YELLOW  = 4  << CC_COLOR_BITS,
    CC_BG_DARK_BLUE    = 5  << CC_COLOR_BITS,
    CC_BG_DARK_MAGENTA = 6  << CC_COLOR_BITS,
    CC_BG_DARK_CYAN    = 7  << CC_COLOR_BITS,
    CC_BG_GRAY         = 8  << CC_COLOR_BITS,
    CC_BG_DARK_GRAY    = 9  << CC_COLOR_BITS,
    CC_BG_RED          = 10 << CC_COLOR_BITS,
    CC_BG_GREEN        = 11 << CC_COLOR_BITS,
    CC_BG_YELLOW       = 12 << CC_COLOR_BITS,
    CC_BG_BLUE         = 13 << CC_COLOR_BITS,
    CC_BG_MAGENTA      = 14 << CC_COLOR_BITS,
    CC_BG_CYAN         = 15 << CC_COLOR_BITS,
    CC_BG_WHITE        = 16 << CC_COLOR_BITS
} cc_color_t;

#ifndef COMMON_LVB_LEADING_BYTE
#define COMMON_LVB_LEADING_BYTE    0x0100
#endif

#ifndef COMMON_LVB_TRAILING_BYTE
#define COMMON_LVB_TRAILING_BYTE   0x0200
#endif

#ifndef COMMON_LVB_GRID_HORIZONTAL
#define COMMON_LVB_GRID_HORIZONTAL 0x0400
#endif

#ifndef COMMON_LVB_GRID_LVERTICAL
#define COMMON_LVB_GRID_LVERTICAL  0x0800
#endif

#ifndef COMMON_LVB_GRID_RVERTICAL
#define COMMON_LVB_GRID_RVERTICAL  0x1000
#endif

#ifndef COMMON_LVB_REVERSE_VIDEO
#define COMMON_LVB_REVERSE_VIDEO   0x4000
#endif

#ifndef COMMON_LVB_UNDERSCORE
#define COMMON_LVB_UNDERSCORE      0x8000
#endif

#ifdef __cplusplus
}
#endif


#ifdef _WIN32
    #define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
    #define SIMPLE_API __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

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

/*
**    Do nothing if S_ISDIR is defined
**    Else define it Issue with Microsoft Visual Studio
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

#ifndef _POSIX_SOURCE 
#define	S_IREAD		S_IRUSR 
#define	S_IWRITE	S_IWUSR 
#define	S_IEXEC		S_IXUSR 
#endif

#if !defined(S_ISUID)
static const mode_t S_ISUID      = 0x08000000;           ///< does nothing
#endif
#if !defined(S_ISGID)
static const mode_t S_ISGID      = 0x04000000;           ///< does nothing
#endif
#if !defined(S_ISVTX)
static const mode_t S_ISVTX      = 0x02000000;           ///< does nothing
#endif

static const mode_t MS_MODE_MASK = 0x0000ffff;           ///< low word

#if !defined(chmod) && defined(_WIN32)
#define chmod(path, mode) _chmod(path, (mode & MS_MODE_MASK))
#endif
#if !defined(mkdir) && defined(_WIN32)
#define mkdir(path, permission) _mkdir(path)
#endif

int file_savant_cc_fprintf(cc_color_t color, FILE* stream, const char* format, ...);

void file_savant_std_print(void *pointer)
{
    FILE* std_output ;
    char *str  ;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
    } else {
        std_output = (FILE*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
        str = SIMPLE_API_GETSTRING(2);
        fprintf( std_output, "%s", str );
    }
}

void file_savant_printwfb( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( ! SIMPLE_API_ISPOINTER(1) && ! SIMPLE_API_ISNUMBER(2) && ! SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISSTRING(4)) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    FILE* std_output = (FILE*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
    file_savant_cc_fprintf(((int ) SIMPLE_API_GETNUMBER(2) << 0 ) | ((int ) SIMPLE_API_GETNUMBER(3) << CC_COLOR_BITS ), std_output, SIMPLE_API_GETSTRING(4));
}

void file_savant_path_absolute_path(void *pointer)
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

void file_savant_path_blocks(void *pointer)
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

void file_savant_path_block_size(void *pointer)
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

void file_savant_path_status_date(void *pointer)
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

void file_savant_path_modify_date(void *pointer)
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

void file_savant_path_access_date(void *pointer)
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

void file_savant_path_gid(void *pointer)
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

void file_savant_path_uid(void *pointer)
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

void file_savant_path_link_count(void *pointer)
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

void file_savant_path_node_number(void *pointer)
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

void file_savant_path_type(void *pointer)
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
                    case S_IFWHT:  SIMPLE_API_RETNUMBER(160000);    break; 
                    case S_IFBLK:  SIMPLE_API_RETNUMBER(60000);    break;
                    case S_IFCHR:  SIMPLE_API_RETNUMBER(20000);    break;
                    case S_IFDIR:  SIMPLE_API_RETNUMBER(40000);    break;
                    case S_IFIFO:  SIMPLE_API_RETNUMBER(10000);    break;
                    case S_IFLNK:  SIMPLE_API_RETNUMBER(120000);    break;
                    case S_IFREG:  SIMPLE_API_RETNUMBER(100000);    break;
                    case S_IFSOCK: SIMPLE_API_RETNUMBER(140000);    break;
                    default:       SIMPLE_API_RETNUMBER(0000000);   break;
                }
            }
            simple_string_delete_gc(((VM *) pointer)->sState,string);
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void file_savant_path_size(void *pointer)
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

void file_savant_check_path(void *pointer)
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

void file_savant_ffread ( void *pointer )
{
	char *str  ;
	int size  ;
	int nResult  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT") ;
		if ( fp != NULL ) {
			size = SIMPLE_API_GETNUMBER(3) ;
			if ( size < 1 ) {
				SIMPLE_API_ERROR(SIMPLE_VM_FILE_BUFFERSIZE);
				return ;
			}
			str = (char *) simple_state_malloc(((VM *) pointer)->sState,size);
			if ( str == NULL ) {
				SIMPLE_API_ERROR(SIMPLE_OOM);
				return ;
			}
			nResult = fread(str,SIMPLE_API_GETNUMBER(2),size,fp);
			if ( nResult == 0 ) {
				SIMPLE_API_RETNUMBER(nResult);
			} else {
				SIMPLE_API_RETSTRING2(str,nResult);
			}
			simple_state_free(((VM *) pointer)->sState,str);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void file_savant_read_file(void *pointer)
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

void file_savant_write_file ( void *pointer )
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

void file_savant_file_exists ( void *pointer )
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
                SIMPLE_API_RETNUMBER(0);
            }
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void file_savant_file_rename ( void *pointer )
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

void file_savant_file_delete ( void *pointer )
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

void file_savant_file_delete_folder ( void *pointer )
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

void file_savant_blow_directory ( void *pointer )
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
                        case S_IFWHT:  SIMPLE_API_RETNUMBER(160000);    break; 
                        case S_IFBLK:  SIMPLE_API_RETNUMBER(60000);    break;
                        case S_IFCHR:  SIMPLE_API_RETNUMBER(20000);    break;
                        case S_IFDIR:  simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,1);    break;
                        case S_IFIFO:  SIMPLE_API_RETNUMBER(10000);    break;
                        case S_IFLNK:  SIMPLE_API_RETNUMBER(120000);    break;
                        case S_IFREG:  simple_list_adddouble_gc(((VM *) pointer)->sState,pList2,0);    break;
                        case S_IFSOCK: SIMPLE_API_RETNUMBER(140000);    break;
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

void file_savant_mk_directory ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISNUMBER(2)) {
            #ifdef _WIN32
                SIMPLE_API_RETNUMBER(_mkdir(SIMPLE_API_GETSTRING(1)) == 0);
            #else
                SIMPLE_API_RETNUMBER(mkdir(SIMPLE_API_GETSTRING(1), SIMPLE_API_GETNUMBER(2)) == 0); 
            #endif
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void file_savant_dir_exists ( void *pointer )
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

//todo so badly
void file_savant_GetFileAttributes ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    if ( SIMPLE_API_ISSTRING(1) ) {
        #if defined(_WIN32)
            SIMPLE_API_RETNUMBER(GetFileAttributes(SIMPLE_API_GETSTRING(1)));
        #else
            //check all the atributes to immitate the windows api GetFileAttributes
            SIMPLE_API_RETNUMBER(-1);
        #endif
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void file_savant_is_path_executable(void *pointer)
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
                SIMPLE_API_RETNUMBER(info.st_mode & S_IXUSR == 1);
            }
            simple_string_delete_gc(((VM *) pointer)->sState,string);
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}


SIMPLE_BLOCK(init_FILE) 
{
	FILE* FILE18037;	
	SIMPLE_API_RETCPOINTER(FILE18037,"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_chmod) 
{
	const char * str1;
	mode_t num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	num2 = (mode_t) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(chmod(str1,num2));
}

SIMPLE_BLOCK(file_savant_fclose) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fclose(point1));
}

SIMPLE_BLOCK(file_savant_clearerr) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	clearerr(point1);
}

SIMPLE_BLOCK(file_savant_feof) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(feof(point1));
}

SIMPLE_BLOCK(file_savant_ferror) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(ferror(point1));
}

SIMPLE_BLOCK(file_savant_fflush) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fflush(point1));
}

SIMPLE_BLOCK(file_savant_fgetpos) 
{
	FILE * point1;
	fpos_t * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	point2 = (fpos_t *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fgetpos(point1,point2));
}

SIMPLE_BLOCK(file_savant_fopen) 
{
	const char * str1;
	const char * str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	SIMPLE_API_RETCPOINTER(fopen(str1,str2),"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_fread) 
{
	char * str1;
	size_t num2;
	size_t num3;
	FILE * point4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	num2 = (size_t) (size_t) SIMPLE_API_GETNUMBER(2);
	num3 = (size_t) (size_t) SIMPLE_API_GETNUMBER(3);
	point4 = (FILE *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fread(str1,num2,num3,point4));
}

SIMPLE_BLOCK(file_savant_fread_1) 
{
	void * point1;
	size_t num2;
	size_t num3;
	FILE * point4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	point1 = (void *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	num2 = (size_t) (size_t) SIMPLE_API_GETNUMBER(2);
	num3 = (size_t) (size_t) SIMPLE_API_GETNUMBER(3);
	point4 = (FILE *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fread(point1,num2,num3,point4));
}

SIMPLE_BLOCK(file_savant_freopen) 
{
	const char * str1;
	const char * str2;
	FILE * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	point3 = (FILE *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETCPOINTER(freopen(str1,str2,point3),"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_fseek) 
{
	FILE * point1;
	long int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	num2 = (long int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETNUMBER(fseek(point1,num2,num3));
}

SIMPLE_BLOCK(file_savant_fsetpos) 
{
	FILE * point1;
	const fpos_t * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	point2 = (const fpos_t *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fsetpos(point1,point2));
}

SIMPLE_BLOCK(file_savant_ftell) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(ftell(point1));
}

SIMPLE_BLOCK(file_savant_fwrite) 
{
	const char * str1;
	size_t num2;
	size_t num3;
	FILE * point4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	num2 = (size_t) (size_t) SIMPLE_API_GETNUMBER(2);
	num3 = (size_t) (size_t) SIMPLE_API_GETNUMBER(3);
	point4 = (FILE *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fwrite(str1,num2,num3,point4));
}

SIMPLE_BLOCK(file_savant_fwrite_1) 
{
	const void * point1;
	size_t num2;
	size_t num3;
	FILE * point4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	point1 = (const void *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	num2 = (size_t) (size_t) SIMPLE_API_GETNUMBER(2);
	num3 = (size_t) (size_t) SIMPLE_API_GETNUMBER(3);
	point4 = (FILE *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fwrite(point1,num2,num3,point4));
}

SIMPLE_BLOCK(file_savant_remove) 
{
	const char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETNUMBER(remove(str1));
}

SIMPLE_BLOCK(file_savant_rename) 
{
	const char * str1;
	const char * str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	SIMPLE_API_RETNUMBER(rename(str1,str2));
}

SIMPLE_BLOCK(file_savant_rewind) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	rewind(point1);
}

SIMPLE_BLOCK(file_savant_setbuf) 
{
	FILE * point1;
	char * str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	str2 = (char *)  SIMPLE_API_GETSTRING(2);
	setbuf(point1,str2);
}

SIMPLE_BLOCK(file_savant_setvbuf) 
{
	FILE * point1;
	char * str2;
	int num3;
	size_t num4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	str2 = (char *)  SIMPLE_API_GETSTRING(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (size_t) (size_t) SIMPLE_API_GETNUMBER(4);
	SIMPLE_API_RETNUMBER(setvbuf(point1,str2,num3,num4));
}

SIMPLE_BLOCK(file_savant_tmpfile) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(tmpfile(),"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_tmpnam) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETSTRING(tmpnam(str1));
}

SIMPLE_BLOCK(file_savant_fprintf) 
{
	FILE * point1;
	const char * str2;
	void * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fprintf(point1,str2,point3));
}

SIMPLE_BLOCK(file_savant_printf) 
{
	const char * str1;
	void * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	point2 = (void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(printf(str1,point2));
}

SIMPLE_BLOCK(file_savant_sprintf) 
{
	char * str1;
	const char * str2;
	void * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(sprintf(str1,str2,point3));
}

SIMPLE_BLOCK(file_savant_fscanf) 
{
	FILE * point1;
	const char * str2;
	void * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fscanf(point1,str2,point3));
}

SIMPLE_BLOCK(file_savant_scanf) 
{
	const char * str1;
	void * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	point2 = (void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(scanf(str1,point2));
}

SIMPLE_BLOCK(file_savant_sscanf) 
{
	const char * str1;
	const char * str2;
	void * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(sscanf(str1,str2,point3));
}

SIMPLE_BLOCK(file_savant_fgetc) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fgetc(point1));
}

SIMPLE_BLOCK(file_savant_fgets) 
{
	char * str1;
	int num2;
	FILE * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (FILE *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETSTRING(fgets(str1,num2,point3));
}

SIMPLE_BLOCK(file_savant_fputc) 
{
	int num1;
	FILE * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	point2 = (FILE *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fputc(num1,point2));
}

SIMPLE_BLOCK(file_savant_fputs) 
{
	const char * str1;
	FILE * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	point2 = (FILE *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(fputs(str1,point2));
}

SIMPLE_BLOCK(file_savant_getc) 
{
	FILE * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (FILE *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(getc(point1));
}

SIMPLE_BLOCK(file_savant_getchar) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(getchar());
}

SIMPLE_BLOCK(file_savant_gets) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETSTRING(gets(str1));
}

SIMPLE_BLOCK(file_savant_putc) 
{
	int num1;
	FILE * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	point2 = (FILE *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(putc(num1,point2));
}

SIMPLE_BLOCK(file_savant_putchar) 
{
	int num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	SIMPLE_API_RETNUMBER(putchar(num1));
}

SIMPLE_BLOCK(file_savant_puts) 
{
	const char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETNUMBER(puts(str1));
}

SIMPLE_BLOCK(file_savant_ungetc) 
{
	int num1;
	FILE * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	point2 = (FILE *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FILE_SAVANT");
	SIMPLE_API_RETNUMBER(ungetc(num1,point2));
}

SIMPLE_BLOCK(file_savant_perror) 
{
	const char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	perror(str1);
}

SIMPLE_BLOCK(file_savant_printv) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	printv(str1);
}

SIMPLE_BLOCK(file_savant_printi) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	printi(str1);
}

SIMPLE_BLOCK(file_savant_printw) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	printw(str1);
}

SIMPLE_BLOCK(file_savant_printe) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	printe(str1);
}

SIMPLE_BLOCK(file_savant_printa) 
{
	char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (char *)  SIMPLE_API_GETSTRING(1);
	printa(str1);
}

SIMPLE_BLOCK(file_savant_mkdir) 
{
	const char * str1;
	mode_t num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	num2 = (mode_t) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(mkdir(str1,num2));
}

SIMPLE_BLOCK(file_savant_stderr) 
{
	SIMPLE_API_RETCPOINTER(stderr,"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_stdin) 
{
	SIMPLE_API_RETCPOINTER(stdin,"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_stdout) 
{
	SIMPLE_API_RETCPOINTER(stdout,"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_NULL) 
{
	SIMPLE_API_RETCPOINTER(NULL,"SMOOTHC_FILE_SAVANT");
}

SIMPLE_BLOCK(file_savant_errno) 
{
	SIMPLE_API_RETNUMBER(errno);
}

SIMPLE_BLOCK(file_savant_BUFSIZ) 
{
	SIMPLE_API_RETNUMBER(BUFSIZ);
}

SIMPLE_BLOCK(file_savant_EOF) 
{
	SIMPLE_API_RETNUMBER(EOF);
}

SIMPLE_BLOCK(file_savant_FOPEN_MAX) 
{
	SIMPLE_API_RETNUMBER(FOPEN_MAX);
}

SIMPLE_BLOCK(file_savant_FILENAME_MAX) 
{
	SIMPLE_API_RETNUMBER(FILENAME_MAX);
}

SIMPLE_BLOCK(file_savant_L_tmpnam) 
{
	SIMPLE_API_RETNUMBER(L_tmpnam);
}

SIMPLE_BLOCK(file_savant_SEEK_CUR) 
{
	SIMPLE_API_RETNUMBER(SEEK_CUR);
}

SIMPLE_BLOCK(file_savant_SEEK_END) 
{
	SIMPLE_API_RETNUMBER(SEEK_END);
}

SIMPLE_BLOCK(file_savant_SEEK_SET) 
{
	SIMPLE_API_RETNUMBER(SEEK_SET);
}

SIMPLE_BLOCK(file_savant_TMP_MAX) 
{
	SIMPLE_API_RETNUMBER(TMP_MAX);
}

SIMPLE_BLOCK(file_savant_CC_FG_NONE) 
{
	SIMPLE_API_RETNUMBER(CC_FG_NONE);
}

SIMPLE_BLOCK(file_savant_CC_FG_BLACK) 
{
	SIMPLE_API_RETNUMBER(CC_FG_BLACK);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_RED) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_RED);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_GREEN) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_GREEN);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_YELLOW) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_YELLOW);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_BLUE) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_BLUE);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_MAGENTA) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_MAGENTA);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_CYAN) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_CYAN);
}

SIMPLE_BLOCK(file_savant_CC_FG_GRAY) 
{
	SIMPLE_API_RETNUMBER(CC_FG_GRAY);
}

SIMPLE_BLOCK(file_savant_CC_FG_DARK_GRAY) 
{
	SIMPLE_API_RETNUMBER(CC_FG_DARK_GRAY);
}

SIMPLE_BLOCK(file_savant_CC_FG_RED) 
{
	SIMPLE_API_RETNUMBER(CC_FG_RED);
}

SIMPLE_BLOCK(file_savant_CC_FG_GREEN) 
{
	SIMPLE_API_RETNUMBER(CC_FG_GREEN);
}

SIMPLE_BLOCK(file_savant_CC_FG_YELLOW) 
{
	SIMPLE_API_RETNUMBER(CC_FG_YELLOW);
}

SIMPLE_BLOCK(file_savant_CC_FG_BLUE) 
{
	SIMPLE_API_RETNUMBER(CC_FG_BLUE);
}

SIMPLE_BLOCK(file_savant_CC_FG_MAGENTA) 
{
	SIMPLE_API_RETNUMBER(CC_FG_MAGENTA);
}

SIMPLE_BLOCK(file_savant_CC_FG_CYAN) 
{
	SIMPLE_API_RETNUMBER(CC_FG_CYAN);
}

SIMPLE_BLOCK(file_savant_CC_FG_WHITE) 
{
	SIMPLE_API_RETNUMBER(CC_FG_WHITE);
}

SIMPLE_BLOCK(file_savant_CC_BG_NONE) 
{
	SIMPLE_API_RETNUMBER(CC_BG_NONE);
}

SIMPLE_BLOCK(file_savant_CC_BG_BLACK) 
{
	SIMPLE_API_RETNUMBER(CC_BG_BLACK);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_RED) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_RED);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_GREEN) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_GREEN);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_YELLOW) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_YELLOW);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_BLUE) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_BLUE);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_MAGENTA) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_MAGENTA);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_CYAN) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_CYAN);
}

SIMPLE_BLOCK(file_savant_CC_BG_GRAY) 
{
	SIMPLE_API_RETNUMBER(CC_BG_GRAY);
}

SIMPLE_BLOCK(file_savant_CC_BG_DARK_GRAY) 
{
	SIMPLE_API_RETNUMBER(CC_BG_DARK_GRAY);
}

SIMPLE_BLOCK(file_savant_CC_BG_RED) 
{
	SIMPLE_API_RETNUMBER(CC_BG_RED);
}

SIMPLE_BLOCK(file_savant_CC_BG_GREEN) 
{
	SIMPLE_API_RETNUMBER(CC_BG_GREEN);
}

SIMPLE_BLOCK(file_savant_CC_BG_YELLOW) 
{
	SIMPLE_API_RETNUMBER(CC_BG_YELLOW);
}

SIMPLE_BLOCK(file_savant_CC_BG_BLUE) 
{
	SIMPLE_API_RETNUMBER(CC_BG_BLUE);
}

SIMPLE_BLOCK(file_savant_CC_BG_MAGENTA) 
{
	SIMPLE_API_RETNUMBER(CC_BG_MAGENTA);
}

SIMPLE_BLOCK(file_savant_CC_BG_CYAN) 
{
	SIMPLE_API_RETNUMBER(CC_BG_CYAN);
}

SIMPLE_BLOCK(file_savant_CC_BG_WHITE) 
{
	SIMPLE_API_RETNUMBER(CC_BG_WHITE);
}

SIMPLE_BLOCK(file_savant_S_ISUID) 
{
	SIMPLE_API_RETNUMBER(S_ISUID);
}

SIMPLE_BLOCK(file_savant_S_ISGID) 
{
	SIMPLE_API_RETNUMBER(S_ISGID);
}

SIMPLE_BLOCK(file_savant_S_ISVTX) 
{
	SIMPLE_API_RETNUMBER(S_ISVTX);
}

SIMPLE_BLOCK(file_savant_S_IRUSR) 
{
	SIMPLE_API_RETNUMBER(S_IRUSR);
}

SIMPLE_BLOCK(file_savant_S_IWUSR) 
{
	SIMPLE_API_RETNUMBER(S_IWUSR);
}

SIMPLE_BLOCK(file_savant_S_IXUSR) 
{
	SIMPLE_API_RETNUMBER(S_IXUSR);
}

SIMPLE_BLOCK(file_savant_S_IRGRP) 
{
	SIMPLE_API_RETNUMBER(S_IRGRP);
}

SIMPLE_BLOCK(file_savant_S_IWGRP) 
{
	SIMPLE_API_RETNUMBER(S_IWGRP);
}

SIMPLE_BLOCK(file_savant_S_IXGRP) 
{
	SIMPLE_API_RETNUMBER(S_IXGRP);
}

SIMPLE_BLOCK(file_savant_S_IROTH) 
{
	SIMPLE_API_RETNUMBER(S_IROTH);
}

SIMPLE_BLOCK(file_savant_S_IWOTH) 
{
	SIMPLE_API_RETNUMBER(S_IWOTH);
}

SIMPLE_BLOCK(file_savant_S_IXOTH) 
{
	SIMPLE_API_RETNUMBER(S_IXOTH);
}

SIMPLE_BLOCK(file_savant_MS_MODE_MASK) 
{
	SIMPLE_API_RETNUMBER(MS_MODE_MASK);
}

SIMPLE_BLOCK(file_savant_S_IWRITE) 
{
	SIMPLE_API_RETNUMBER(S_IWRITE);
}

SIMPLE_API void init_simple_module(SimpleState *sState)
{
	register_block("__init_FILE",init_FILE);
	register_block("__chmod",file_savant_chmod);
	register_block("__fclose",file_savant_fclose);
	register_block("__clearerr",file_savant_clearerr);
	register_block("__feof",file_savant_feof);
	register_block("__ferror",file_savant_ferror);
	register_block("__fflush",file_savant_fflush);
	register_block("__fgetpos",file_savant_fgetpos);
	register_block("__fopen",file_savant_fopen);
	register_block("__fread",file_savant_fread);
	register_block("__fread_1",file_savant_fread_1);
	register_block("__freopen",file_savant_freopen);
	register_block("__fseek",file_savant_fseek);
	register_block("__fsetpos",file_savant_fsetpos);
	register_block("__ftell",file_savant_ftell);
	register_block("__fwrite",file_savant_fwrite);
	register_block("__fwrite_1",file_savant_fwrite_1);
	register_block("__remove",file_savant_remove);
	register_block("__rename",file_savant_rename);
	register_block("__rewind",file_savant_rewind);
	register_block("__setbuf",file_savant_setbuf);
	register_block("__setvbuf",file_savant_setvbuf);
	register_block("__tmpfile",file_savant_tmpfile);
	register_block("__tmpnam",file_savant_tmpnam);
	register_block("__fprintf",file_savant_fprintf);
	register_block("__printf",file_savant_printf);
	register_block("__sprintf",file_savant_sprintf);
	register_block("__fscanf",file_savant_fscanf);
	register_block("__scanf",file_savant_scanf);
	register_block("__sscanf",file_savant_sscanf);
	register_block("__fgetc",file_savant_fgetc);
	register_block("__fgets",file_savant_fgets);
	register_block("__fputc",file_savant_fputc);
	register_block("__fputs",file_savant_fputs);
	register_block("__getc",file_savant_getc);
	register_block("__getchar",file_savant_getchar);
	register_block("__gets",file_savant_gets);
	register_block("__putc",file_savant_putc);
	register_block("__putchar",file_savant_putchar);
	register_block("__puts",file_savant_puts);
	register_block("__ungetc",file_savant_ungetc);
	register_block("__perror",file_savant_perror);
	register_block("__printv",file_savant_printv);
	register_block("__printi",file_savant_printi);
	register_block("__printw",file_savant_printw);
	register_block("__printe",file_savant_printe);
	register_block("__printa",file_savant_printa);
	register_block("__mkdir",file_savant_mkdir);
	register_block("__stderr",file_savant_stderr);
	register_block("__stdin",file_savant_stdin);
	register_block("__stdout",file_savant_stdout);
	register_block("__NULL",file_savant_NULL);
	register_block("__errno",file_savant_errno);
	register_block("__BUFSIZ",file_savant_BUFSIZ);
	register_block("__EOF",file_savant_EOF);
	register_block("__FOPEN_MAX",file_savant_FOPEN_MAX);
	register_block("__FILENAME_MAX",file_savant_FILENAME_MAX);
	register_block("__L_tmpnam",file_savant_L_tmpnam);
	register_block("__SEEK_CUR",file_savant_SEEK_CUR);
	register_block("__SEEK_END",file_savant_SEEK_END);
	register_block("__SEEK_SET",file_savant_SEEK_SET);
	register_block("__TMP_MAX",file_savant_TMP_MAX);
	register_block("__CC_FG_NONE",file_savant_CC_FG_NONE);
	register_block("__CC_FG_BLACK",file_savant_CC_FG_BLACK);
	register_block("__CC_FG_DARK_RED",file_savant_CC_FG_DARK_RED);
	register_block("__CC_FG_DARK_GREEN",file_savant_CC_FG_DARK_GREEN);
	register_block("__CC_FG_DARK_YELLOW",file_savant_CC_FG_DARK_YELLOW);
	register_block("__CC_FG_DARK_BLUE",file_savant_CC_FG_DARK_BLUE);
	register_block("__CC_FG_DARK_MAGENTA",file_savant_CC_FG_DARK_MAGENTA);
	register_block("__CC_FG_DARK_CYAN",file_savant_CC_FG_DARK_CYAN);
	register_block("__CC_FG_GRAY",file_savant_CC_FG_GRAY);
	register_block("__CC_FG_DARK_GRAY",file_savant_CC_FG_DARK_GRAY);
	register_block("__CC_FG_RED",file_savant_CC_FG_RED);
	register_block("__CC_FG_GREEN",file_savant_CC_FG_GREEN);
	register_block("__CC_FG_YELLOW",file_savant_CC_FG_YELLOW);
	register_block("__CC_FG_BLUE",file_savant_CC_FG_BLUE);
	register_block("__CC_FG_MAGENTA",file_savant_CC_FG_MAGENTA);
	register_block("__CC_FG_CYAN",file_savant_CC_FG_CYAN);
	register_block("__CC_FG_WHITE",file_savant_CC_FG_WHITE);
	register_block("__CC_BG_NONE",file_savant_CC_BG_NONE);
	register_block("__CC_BG_BLACK",file_savant_CC_BG_BLACK);
	register_block("__CC_BG_DARK_RED",file_savant_CC_BG_DARK_RED);
	register_block("__CC_BG_DARK_GREEN",file_savant_CC_BG_DARK_GREEN);
	register_block("__CC_BG_DARK_YELLOW",file_savant_CC_BG_DARK_YELLOW);
	register_block("__CC_BG_DARK_BLUE",file_savant_CC_BG_DARK_BLUE);
	register_block("__CC_BG_DARK_MAGENTA",file_savant_CC_BG_DARK_MAGENTA);
	register_block("__CC_BG_DARK_CYAN",file_savant_CC_BG_DARK_CYAN);
	register_block("__CC_BG_GRAY",file_savant_CC_BG_GRAY);
	register_block("__CC_BG_DARK_GRAY",file_savant_CC_BG_DARK_GRAY);
	register_block("__CC_BG_RED",file_savant_CC_BG_RED);
	register_block("__CC_BG_GREEN",file_savant_CC_BG_GREEN);
	register_block("__CC_BG_YELLOW",file_savant_CC_BG_YELLOW);
	register_block("__CC_BG_BLUE",file_savant_CC_BG_BLUE);
	register_block("__CC_BG_MAGENTA",file_savant_CC_BG_MAGENTA);
	register_block("__CC_BG_CYAN",file_savant_CC_BG_CYAN);
	register_block("__CC_BG_WHITE",file_savant_CC_BG_WHITE);
	register_block("__S_ISUID",file_savant_S_ISUID);
	register_block("__S_ISGID",file_savant_S_ISGID);
	register_block("__S_ISVTX",file_savant_S_ISVTX);
	register_block("__S_IRUSR",file_savant_S_IRUSR);
	register_block("__S_IWUSR",file_savant_S_IWUSR);
	register_block("__S_IXUSR",file_savant_S_IXUSR);
	register_block("__S_IRGRP",file_savant_S_IRGRP);
	register_block("__S_IWGRP",file_savant_S_IWGRP);
	register_block("__S_IXGRP",file_savant_S_IXGRP);
	register_block("__S_IROTH",file_savant_S_IROTH);
	register_block("__S_IWOTH",file_savant_S_IWOTH);
	register_block("__S_IXOTH",file_savant_S_IXOTH);
	register_block("__MS_MODE_MASK",file_savant_MS_MODE_MASK);
	register_block("__S_IWRITE",file_savant_S_IWRITE);
	register_block("__std_print",file_savant_std_print);
	register_block("__printwfb",file_savant_printwfb);
	register_block("__cc_fprintf",file_savant_cc_fprintf);
	register_block("__ffread",file_savant_ffread);
	register_block("__read_file",file_savant_read_file);
	register_block("__write_file",file_savant_write_file);
	register_block("__file_exists",file_savant_file_exists);
	register_block("__path_absolute_path",file_savant_path_absolute_path);
	register_block("__path_block_size",file_savant_path_block_size);
	register_block("__path_blocks",file_savant_path_blocks);
	register_block("__path_access_date",file_savant_path_access_date);
	register_block("__path_modify_date",file_savant_path_modify_date);
	register_block("__path_status_date",file_savant_path_status_date);
	register_block("__path_uid",file_savant_path_uid);
	register_block("__path_gid",file_savant_path_gid);
	register_block("__path_link_count",file_savant_path_link_count);
	register_block("__path_node_number",file_savant_path_node_number);
	register_block("__path_type",file_savant_path_type);
	register_block("__path_size",file_savant_path_size);
	register_block("__check_path",file_savant_check_path);
	register_block("__file_rename",file_savant_file_rename);
	register_block("__file_delete",file_savant_file_delete);
	register_block("__file_delete_folder",file_savant_file_delete_folder);
	register_block("__blow_directory",file_savant_blow_directory);
	register_block("__mk_directory",file_savant_mk_directory);
	register_block("__dir_exists",file_savant_dir_exists);
	register_block("__GetFileAttributes",file_savant_GetFileAttributes);
	register_block("__is_path_executable",file_savant_is_path_executable);
}

static int Write(FILE *stream, const char *format, va_list ap) {
#if defined(_WIN32) && !defined(__MINGW32__)
    return vfprintf_s(stream, format, ap);
#else
    return vfprintf(stream, format, ap);
#endif
}

#ifdef _WIN32
static const WORD FG[] = {
/* NONE         */  0,
/* BLACK        */  0,
/* DARK_RED     */  FOREGROUND_RED,
/* DARK_GREEN   */  FOREGROUND_GREEN,
/* DARK_YELLOW  */  FOREGROUND_RED | FOREGROUND_GREEN,
/* DARK_BLUE    */  FOREGROUND_BLUE,
/* DARK_MAGENTA */  FOREGROUND_RED | FOREGROUND_BLUE,
/* DARK_CYAN    */  FOREGROUND_GREEN | FOREGROUND_BLUE,
/* GRAY         */  FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED,
/* DARK_GRAY    */  FOREGROUND_INTENSITY,
/* RED          */  FOREGROUND_INTENSITY | FOREGROUND_RED,
/* GREEN        */  FOREGROUND_INTENSITY | FOREGROUND_GREEN,
/* YELLOW       */  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
/* BLUE         */  FOREGROUND_INTENSITY | FOREGROUND_BLUE,
/* MAGENTA      */  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
/* CYAN         */  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
/* WHITE        */  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED,
};

static const WORD BG[] = {
/* NONE         */  0,
/* BLACK        */  0,
/* DARK_RED     */  BACKGROUND_RED,
/* DARK_GREEN   */  BACKGROUND_GREEN,
/* DARK_YELLOW  */  BACKGROUND_RED | BACKGROUND_GREEN,
/* DARK_BLUE    */  BACKGROUND_BLUE,
/* DARK_MAGENTA */  BACKGROUND_RED | BACKGROUND_BLUE,
/* DARK_CYAN    */  BACKGROUND_GREEN | BACKGROUND_BLUE,
/* GRAY         */  BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED,
/* DARK_GRAY    */  BACKGROUND_INTENSITY,
/* RED          */  BACKGROUND_INTENSITY | BACKGROUND_RED,
/* GREEN        */  BACKGROUND_INTENSITY | BACKGROUND_GREEN,
/* YELLOW       */  BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
/* BLUE         */  BACKGROUND_INTENSITY | BACKGROUND_BLUE,
/* MAGENTA      */  BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
/* CYAN         */  BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
/* WHITE        */  BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED,
};

static WORD ExtractForeground(WORD attributes) {
    const WORD mask =
        FOREGROUND_INTENSITY |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE |
        FOREGROUND_RED;
    return attributes & mask;
}

static WORD ExtractBackground(WORD attributes) {
    const WORD mask =
        BACKGROUND_INTENSITY |
        BACKGROUND_GREEN |
        BACKGROUND_BLUE |
        BACKGROUND_RED;
    return attributes & mask;
}

static WORD ExtractOthers(WORD attributes) {
    const WORD mask =
        COMMON_LVB_LEADING_BYTE |
        COMMON_LVB_TRAILING_BYTE |
        COMMON_LVB_GRID_HORIZONTAL |
        COMMON_LVB_GRID_LVERTICAL |
        COMMON_LVB_GRID_RVERTICAL |
        COMMON_LVB_REVERSE_VIDEO |
        COMMON_LVB_UNDERSCORE;
    return attributes & mask;
}

static WORD Generate(unsigned int fg, unsigned int bg, WORD attributes) {
    WORD result = ExtractOthers(attributes);
    result |= ((fg == 0) ? ExtractForeground(attributes) : FG[fg]);
    result |= ((bg == 0) ? ExtractBackground(attributes) : BG[bg]);
    return result;
}

#else

static inline unsigned int Shift(
        unsigned int val, unsigned int normal, unsigned int bright) {
    if (val == 0) {
        return 9 + normal;
    }
    val -= 1;
    /* background */
    if (val >= 8) {
        return (val - 8) + bright;
    }
    return val + normal;
}

static void UnixTerminalColorize(
        FILE* stream, unsigned int fg, unsigned int bg) {
        fprintf(stream, "\x1B[39;49;%u;%um", Shift(fg, 30, 90), Shift(bg, 40, 100));
}

static void UnixTerminalRestore(FILE* stream) {
    fputs("\x1B[39;49m\x1B[K", stream);
}
#endif  /* _WIN32 */

int file_savant_cc_fprintf(cc_color_t color, FILE* stream, const char* format, ...) {
    unsigned int fg;
    unsigned int bg;
    int result = -EINVAL;
    va_list ap;
#ifdef _WIN32
    HANDLE console;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif  /* _WIN32 */

    va_start(ap, format);

    if (!isatty(fileno(stream)) || (stream != stdout && stream != stderr)) {
        result = Write(stream, format, ap);
        goto finish;
    }

    fg = color & ((1 << CC_COLOR_BITS) - 1);
    bg = (color >> CC_COLOR_BITS) & ((1 << CC_COLOR_BITS) - 1);

#ifdef _WIN32
    console = GetStdHandle(
            stream == stdout ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
    if (console == INVALID_HANDLE_VALUE) {
        result = Write(stream, format, ap);
        goto finish;
    }
    if (!GetConsoleScreenBufferInfo(console, &csbi)) {
        result = Write(stream, format, ap);
        goto finish;
    }
    SetConsoleTextAttribute(console, Generate(fg, bg, csbi.wAttributes));
    result = Write(stream, format, ap);
    SetConsoleTextAttribute(console, csbi.wAttributes);
#else
    UnixTerminalColorize(stream, fg, bg);
    Write(stream, format, ap);
    UnixTerminalRestore(stream);
#endif  /* _WIN32 */

finish:
    va_end(ap);
    return result;
}

