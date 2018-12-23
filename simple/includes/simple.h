
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: thecarisma
 *
 * Created on July 10, 2017, 1:10 PM
 */

#ifndef SIMPLE_H
#define SIMPLE_H
/*
**  DLL/So 
**  Check Operating System 
*/
#ifdef _WIN32
/*
**  Windows 
**  Support Windows XP 
**  To avoid error message : procedure entry point InitializeConditionVariable could not be located in Kernel32.dll 
*/
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x502
#define SIMPLE_USEDLL 1
#define SIMPLE_BUILDLIB 1
/* Linux */
#else
#define SIMPLE_USEDLL 0
#define SIMPLE_BUILDLIB 0
#endif
#if SIMPLE_USEDLL
#if SIMPLE_BUILDLIB
#define SIMPLE_API __declspec(dllexport)
#else
#define SIMPLE_API __declspec(dllimport)
#endif
#else
#define SIMPLE_API extern
#endif
/* Constants */
#define SIMPLE_DEBUG 0
#define SIMPLE_TESTUNITS 0
#define SIMPLE_TESTPERFORMANCE 1
#define SIMPLE_SCANNEROUTPUT 0
#define SIMPLE_PARSERSTART 1
#define SIMPLE_PARSERTRACE 1
#define SIMPLE_PARSERFINAL 0
#define SIMPLE_SHOWIC 0
#define SIMPLE_RUNVM 1
#define SIMPLE_VMSHOWOPCODE 1
#define SIMPLE_DEVELOPMENT 0
#ifndef NDEBUG
#define NDEBUG
#endif
/* Environment Errors */
#define SIMPLE_SEGFAULT "\nENVIRONMENT ERROR 1 : Caught SegFault!"
#define SIMPLE_OOM "\nENVIRONMENT ERROR 2 : Out of Memory!"
#define SIMPLE_NOSCOPE "\nENVIRONMENT ERROR 3 : Deleting scope while no scope! "
#define SIMPLE_LONGINSTRUCTION "\nENVIRONMENT ERROR 4 : Long VM Instruction! "
/* General */
#define SIMPLE_PATHSIZE 256
/* See and Give - use simplevm_display() and read_string() */
#define SIMPLE_USEDISPLAYBLOCKTION 1
#define SIMPLE_USEGIVEBLOCKTION 1
#define TRUE 1
/*
**  Include Files 
**  Include C Headers 
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "signal.h"
#ifdef _WIN32
#include "io.h"
#include "fcntl.h"
/* Required to get binary data from stdin (to be able to upload and read using cgi) */
#if __BORLANDC__
#define SIMPLE_SETBINARY setmode(fileno(stdin), O_BINARY)
#else
#define SIMPLE_SETBINARY _setmode(_fileno(stdin), _O_BINARY)
#endif
#else
#define SIMPLE_SETBINARY ((void)0)
#endif
#include <errno.h>

/* Include android Headers*/
#ifdef __TERMUX__
#undef __ANDROID__
#endif
#ifdef __ANDROID__
#include <android/native_activity.h>
#include <android/log.h>
#include <unistd.h>
#define SIMPLE_ANDROID_LOG "simple-lang:0.3.36"

/* Make fprintf function custom to allow output in android designated std(s)*/
/* ANDROID_LOG_DEBUG - stdout, ANDROID_LOG_ERROR - stderr */
#define fprintf(std,...) __android_log_print(std, SIMPLE_ANDROID_LOG, __VA_ARGS__)
/* Replace Printf to print to the actual android log */
#define printv(...) fprintf(ANDROID_LOG_VERBOSE,__VA_ARGS__)
#define printf(...) fprintf(ANDROID_LOG_DEBUG,__VA_ARGS__)
#define printi(...) fprintf(ANDROID_LOG_INFO,__VA_ARGS__)
#define printw(...) fprintf(ANDROID_LOG_WARN,__VA_ARGS__)
#define printe(...) fprintf(ANDROID_LOG_ERROR,__VA_ARGS__)
#define printa(...) fprintf(ANDROID_LOG_ASSERT,__VA_ARGS__)
#define stdout ANDROID_LOG_INFO
#define stderr ANDROID_LOG_ERROR

#else
#define printv(...) fprintf(stdout,__VA_ARGS__)
#define printi(...) fprintf(stdout,__VA_ARGS__)
#define printw(...) fprintf(stdout,__VA_ARGS__)
#define printe(...) fprintf(stderr,__VA_ARGS__)
#define printa(...) fprintf(stderr,__VA_ARGS__)
#endif

/* Include Project Headers */
#include "simple_misc.h"
#include "simple_string.h"
#include "simple_item.h"
#include "simple_list.h"
#include "simple_hashtable.h"
#include "simple_state.h"
#include "simple_scanner.h"
#include "simple_parser.h"
#include "simple_codegen.h"

#ifdef __ANDROID__
/* load the fulltick module here */
typedef void (*__android_init_full_tick)(SimpleState *sState);
extern __android_init_full_tick __init_full_tick ;
#endif

#include "simple_vm.h"
#include "simple_vmgc.h"
#include "simple_api.h"

/*
**	Do nothing if snprintf is defined
**	Else define it as _snprintf_s since we dont need return values
**	Issue with Microsoft Visual Studio
*/
#ifdef snprintf
#else
#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf(buf,len, format,...) _snprintf_s(buf, len,len, format, __VA_ARGS__)
#endif
#endif

#endif
