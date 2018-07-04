
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   systemic.c
 * Author: thecarisma
 *
 * Created on February 9, 2018, 10:05 PM
 */

#ifdef _WIN32
#include "windows.h"
typedef int (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); ;
LPFN_ISWOW64PROCESS isWindows64  ;
#endif

#include "../../../simple/includes/simple.h"
#include "systemic.h"

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
    register_block("isMsDos",os_ismsdos);
    register_block("isWindows",os_iswindows);
    register_block("isWindows64",os_iswindows64);
    register_block("isUnix",os_isunix);
    register_block("isMacosx",os_ismacosx);
    register_block("isLinux",os_islinux);
    register_block("isFreebsd",os_isfreebsd);
    register_block("isAndroid",os_isandroid);
    register_block("windowsnl",os_windowsnl);
    register_block("currentDirectory",os_currentdir);
    register_block("simplePath",os_exefilename);
    register_block("__exec",exe_system);
    register_block("__beep",system_beep);
    register_block("__sleep",system_sleep);
    register_block("changeDirectory",os_chdir);
    register_block("exeFolder",os_exefolder);
    register_block("getSystemEnvironment",get_env);
    register_block("__exit",system_exit);
    register_block("currentFilePath",current_filepath);
    register_block("currentFileName",current_filename);
    register_block("previousFileName",previous_filename);
    register_block("previousFilePath",previous_filepath);
}

void os_ismsdos ( void *pointer )
{
	#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_iswindows ( void *pointer )
{
	#ifdef _WIN32
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_iswindows64 ( void *pointer )
{
	int lSystem64  ;
	lSystem64 = 0 ;
	#ifdef _WIN32
	isWindows64 = (LPFN_ISWOW64PROCESS) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process") ;
	if ( isWindows64 != NULL ) {
		isWindows64(GetCurrentProcess(),&lSystem64);
	}
	#endif
	SIMPLE_API_RETNUMBER(lSystem64);
}

void os_isunix ( void *pointer )
{
	#if defined(unix) || defined(__unix__) || defined(__unix)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_ismacosx ( void *pointer )
{
	#if defined(__APPLE__)  || defined(__MACH__)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_islinux ( void *pointer )
{
	#ifdef __linux__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_isfreebsd ( void *pointer )
{
	#ifdef __FreeBSD__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_isandroid ( void *pointer )
{
	#ifdef __ANDROID__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void os_windowsnl ( void *pointer )
{
	SIMPLE_API_RETSTRING("\r\n");
}

void os_currentdir ( void *pointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	simple_currentdir(cDirPath);
	SIMPLE_API_RETSTRING(cDirPath);
}

void os_exefilename ( void *pointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	if ( simple_exefilename(cDirPath) ) {
		SIMPLE_API_RETSTRING(cDirPath);
	}
}

void os_chdir ( void *pointer )
{
	SIMPLE_API_RETNUMBER(simple_chdir(SIMPLE_API_GETSTRING(1)));
}

void os_exefolder ( void *pointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	simple_exefolder(cDirPath);
	SIMPLE_API_RETSTRING(cDirPath);
}

void get_env ( void *pointer )
{
	char *pData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		pData = getenv(SIMPLE_API_GETSTRING(1));
		if ( pData != NULL ) {
			SIMPLE_API_RETSTRING(pData);
		} else {
			SIMPLE_API_RETSTRING("(null)");
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void system_exit ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISNUMBER(1) ) {
			exit(SIMPLE_API_GETNUMBER(1));
			return ;
		}
	}
	exit(0);
}

void current_filepath ( void *pointer )
{
	VM *vm  ;
	int nPos  ;
	List *list  ;
	vm = (VM *) pointer ;
	if ( vm->nInClassRegion ) {
		SIMPLE_API_RETSTRING(vm->cFileNameInClassRegion);
		return ;
	}
	if ( (vm->nBlockExecute2 > 0) && (simple_list_getsize(vm->pBlockCallList)>0) ) {
		/*
		**  Here we have Load Function Instruction - But Still the function is not called 
		**  FunctionName (  ***Parameters**** We are here! ) 
		*/
		nPos = simple_list_getsize(vm->pBlockCallList)  -  (vm->nBlockExecute2 - 1) ;
		if ( (nPos > 0) && (nPos <= simple_list_getsize(vm->pBlockCallList)) ) {
			list = simple_list_getlist(vm->pBlockCallList,nPos);
			if ( simple_list_getsize(list) >= SIMPLE_BLOCKCL_FILENAME ) {
				SIMPLE_API_RETSTRING((char *) simple_list_getpointer(list,SIMPLE_BLOCKCL_FILENAME ));
			}
		}
		return ;
	}
        
	SIMPLE_API_RETSTRING(vm->file_name);
}

void current_filename ( void *pointer )
{
    VM *vm  ;
    int nPos  ;
    List *list  ;
    vm = (VM *) pointer ;
    if ( vm->nInClassRegion ) {
        SIMPLE_API_RETSTRING(file_real_name(vm->cFileNameInClassRegion));
        return ;
    }
    if ( (vm->nBlockExecute2 > 0) && (simple_list_getsize(vm->pBlockCallList)>0) ) {
        /*
        **  Here we have Load Function Instruction - But Still the function is not called 
        **  FunctionName (  ***Parameters**** We are here! ) 
        */
        nPos = simple_list_getsize(vm->pBlockCallList)  -  (vm->nBlockExecute2 - 1) ;
        if ( (nPos > 0) && (nPos <= simple_list_getsize(vm->pBlockCallList)) ) {
            list = simple_list_getlist(vm->nBlockExecute2,nPos);
            /*if ( simple_list_getsize(list) >= SIMPLE_BLOCKCL_FILENAME ) {
                    SIMPLE_API_RETSTRING((char *) file_real_name(simple_list_getpointer(list,SIMPLE_BLOCKCL_FILENAME )));
            } */
        }
        return ;
    }
    SIMPLE_API_RETSTRING(file_real_name(vm->file_name));
}

void previous_filename ( void *pointer )
{
    SIMPLE_API_RETSTRING(file_real_name(((VM *) pointer)->cPrevFileName));
}

void previous_filepath ( void *pointer )
{
    SIMPLE_API_RETSTRING(((VM *) pointer)->cPrevFileName);
}

void exe_system ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		system(SIMPLE_API_GETSTRING(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void system_beep ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) ) {
        #ifdef _WIN32
        Beep(SIMPLE_API_GETNUMBER(1), SIMPLE_API_GETNUMBER(2));
        #else
        _beep(SIMPLE_API_GETNUMBER(1), SIMPLE_API_GETNUMBER(2));
        #endif
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void system_sleep ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
            SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
            return ;
    }
    if ( SIMPLE_API_ISNUMBER(1) ) {
        #ifdef _WIN32
	Sleep(SIMPLE_API_GETNUMBER(1));
	#else
	//_sleep(SIMPLE_API_GETNUMBER(1));
		#if _POSIX_C_SOURCE >= 199309L
		    struct timespec ts;
		    ts.tv_sec = (int)SIMPLE_API_GETNUMBER(1) / 1000;
		    ts.tv_nsec = ((int)SIMPLE_API_GETNUMBER(1) % 1000) * 1000000;
		    nanosleep(&ts, NULL);
		#else
		    usleep((int)SIMPLE_API_GETNUMBER(1) * 1000);
		#endif
	#endif
    } else {
            SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}