
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2018 simple 

*/

#ifndef simple_h
#define simple_h
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
#define RING_USEDLL 1
#define RING_BUILDLIB 1
/* Linux */
#else
#define RING_USEDLL 0
#define RING_BUILDLIB 0
#endif
#if RING_USEDLL
#if RING_BUILDLIB
#define RING_API __declspec(dllexport)
#else
#define RING_API __declspec(dllimport)
#endif
#else
#define RING_API extern
#endif
/* Constants */
#define RING_DEBUG 0
#define RING_TESTUNITS 0
#define RING_TESTPERFORMANCE 1
#define RING_SCANNEROUTPUT 0
#define RING_PARSERSTART 1
#define RING_PARSERTRACE 1
#define RING_PARSERFINAL 0
#define RING_SHOWIC 0
#define RING_RUNVM 1
#define RING_VMSHOWOPCODE 1
#ifndef NDEBUG
#define NDEBUG
#endif
/* Environment Errors */
#define RING_SEGFAULT "\nError (E1) : Caught SegFault!\n"
#define RING_OOM "\nError (E2) : Out of Memory!\n"
#define RING_NOSCOPE "\nError (E3) : Deleting scope while no scope! \n"
#define RING_LONGINSTRUCTION "\nError (E4) : Long VM Instruction! \n"
/* General */
#define RING_PATHSIZE 256
/* See and Give - use simplevm_see() and simplevm_give() */
#define RING_USESEEFUNCTION 1
#define RING_USEGIVEFUNCTION 1
/*
**  Include Files 
**  Include C Headers 
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stsimple.h>
#include <ctype.h>
#include <math.h>
#include "signal.h"
#ifdef _WIN32
#include "io.h"
#include "fcntl.h"
/* Required to get binary data from stdin (to be able to upload and read using cgi) */
#if __BORLANDC__
#define RING_SETBINARY setmode(fileno(stdin), O_BINARY)
#else
#define RING_SETBINARY _setmode(_fileno(stdin), _O_BINARY)
#endif
#else
#define RING_SETBINARY ((void)0)
#endif
#include <errno.h>
/* Include Project Headers */
#include "simple_ext.h"
#include "simple_stsimple.h"
#include "simple_vmgcdata.h"
#include "simple_item.h"
#include "simple_items.h"
#include "simple_list.h"
#include "simple_hashlib.h"
#include "simple_hashtable.h"
#include "simple_pooldata.h"
#include "simple_state.h"
#include "simple_scanner.h"
#include "simple_parser.h"
#include "simple_codegen.h"
#include "simple_vm.h"
#include "simple_vmgc.h"
#include "simple_api.h"
#include "simple_objfile.h"
/* Extensions Headers */
#ifdef RING_VM_MATH
#include "simple_vmmath.h"
#endif
#ifdef RING_VM_FILE
#include "simple_vmfile.h"
#endif
#ifdef RING_VM_OS
#include "simple_vmos.h"
#endif
#ifdef RING_VM_LISTFUNCS
#include "simple_vmlistfuncs.h"
#endif
#ifdef RING_VM_REFMETA
#include "simple_vmrefmeta.h"
#endif
#ifdef RING_VM_DLL
#include "simple_vmdll.h"
#endif
#endif
