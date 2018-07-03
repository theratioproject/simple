
/* 
    Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   consoler.h
 * Author: thecarisma
 *
 * Created on February 11, 2018, 12:26 AM
 */

#include "../../../simple/includes/simple.h"
#include "console-colors.h"
#include "consoler.h"
#include "toot.h"

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
    #define SIMPLE_API
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
    register_block("__printwfb",print_with_foreground_background);
    register_block("__beep",console_beep);
    register_block("__exit",program_exit);
    register_block("__sleep",program_sleep);
    
}

void print_with_foreground_background ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISNUMBER(1) && ! SIMPLE_API_ISNUMBER(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	cc_fprintf(((int ) SIMPLE_API_GETNUMBER(1) << 0 ) | ((int ) SIMPLE_API_GETNUMBER(2) << CC_COLOR_BITS ), stdout, SIMPLE_API_GETSTRING(3));
}

void console_beep ( void *pointer )
{
	int lFd;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( ! SIMPLE_API_ISNUMBER(1) && ! SIMPLE_API_ISNUMBER(2) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    #ifdef _WIN32
	HANDLE lHStdOut;
        
        if ( !GetConsoleWindow() && AttachConsole(ATTACH_PARENT_PROCESS) )
        {
            lHStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            lFd = _open_osfhandle((intptr_t)lHStdOut, _O_TEXT);
            if (lFd > 0) *stdout = *_fdopen(lFd, "w");
            printf("\n");
        }
    #endif
    toot( SIMPLE_API_ISNUMBER(1) , SIMPLE_API_ISNUMBER(2) ) ; 
}

void program_exit ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISNUMBER(1) ) {
			exit(SIMPLE_API_GETNUMBER(1));
			return ;
		}
	}
	exit(0);
}

void program_sleep ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT == 1 ) {
        if ( SIMPLE_API_ISNUMBER(1) ) {
            _sleep(SIMPLE_API_GETNUMBER(1));
            return ;
        }
    }
    _sleep(0);
}