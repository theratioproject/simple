
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: thecarisma
 *
 * Created on July 10, 2017, 1:10 PM
 */

#ifndef ring_h
#define ring_h
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
#ifndef NDEBUG
#define NDEBUG
#endif
/* Environment Errors */
#define SIMPLE_SEGFAULT "\nError (E1) : Caught SegFault!\n"
#define SIMPLE_OOM "\nError (E2) : Out of Memory!\n"
#define SIMPLE_NOSCOPE "\nError (E3) : Deleting scope while no scope! \n"
#define SIMPLE_LONGINSTRUCTION "\nError (E4) : Long VM Instruction! \n"
/* General */
#define SIMPLE_PATHSIZE 256
/* See and Give - use ringvm_display() and ringvm_give() */
#define SIMPLE_USEDISPLAYFUNCTION 1
#define SIMPLE_USEGIVEFUNCTION 1
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
/* Include Project Headers */
#include "simple_misc.h"
#include "ring_ext.h"
#include "ring_string.h"
#include "ring_vmgcdata.h"
#include "ring_item.h"
#include "ring_items.h"
#include "ring_list.h"
#include "ring_hashlib.h"
#include "ring_hashtable.h"
#include "ring_pooldata.h"
#include "ring_state.h"
#include "ring_scanner.h"
#include "ring_parser.h"
#include "ring_codegen.h"
#include "ring_vm.h"
#include "ring_vmgc.h"
#include "ring_api.h"
#include "ring_objfile.h"
/* Extensions Headers */
#ifdef SIMPLE_VM_MATH
#include "ring_vmmath.h"
#endif
#ifdef SIMPLE_VM_FILE
#include "ring_vmfile.h"
#endif
#ifdef SIMPLE_VM_OS
#include "ring_vmos.h"
#endif
#ifdef SIMPLE_VM_LISTFUNCS
#include "ring_vmlistfuncs.h"
#endif
#ifdef SIMPLE_VM_REFMETA
#include "ring_vmrefmeta.h"
#endif
#ifdef SIMPLE_VM_DLL
#include "ring_vmdll.h"
#endif
#endif
