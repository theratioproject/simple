/*
**  Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> 
**  Include Files 
*/
#ifdef _WIN32
#include "windows.h"
typedef int (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); ;
LPFN_ISWOW64PROCESS fnCheckWindows64  ;
#endif
#include "../includes/simple.h"
#include "simple_vmos.h"
/* Functions */

void simple_vm_os_loadfunctions ( RingState *pRingState )
{
	simple_vm_funcregister("ismsdos",simple_vm_os_ismsdos);
	simple_vm_funcregister("iswindows",simple_vm_os_iswindows);
	simple_vm_funcregister("iswindows64",simple_vm_os_iswindows64);
	simple_vm_funcregister("isunix",simple_vm_os_isunix);
	simple_vm_funcregister("ismacosx",simple_vm_os_ismacosx);
	simple_vm_funcregister("islinux",simple_vm_os_islinux);
	simple_vm_funcregister("isfreebsd",simple_vm_os_isfreebsd);
	simple_vm_funcregister("isandroid",simple_vm_os_isandroid);
	simple_vm_funcregister("windowsnl",simple_vm_os_windowsnl);
	simple_vm_funcregister("currentdir",simple_vm_os_currentdir);
	simple_vm_funcregister("exefilename",simple_vm_os_exefilename);
	simple_vm_funcregister("chdir",simple_vm_os_chdir);
	simple_vm_funcregister("exefolder",simple_vm_os_exefolder);
}

void simple_vm_os_ismsdos ( void *pPointer )
{
	#if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_iswindows ( void *pPointer )
{
	#ifdef _WIN32
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_iswindows64 ( void *pPointer )
{
	int lSystem64  ;
	lSystem64 = 0 ;
	#ifdef _WIN32
	fnCheckWindows64 = (LPFN_ISWOW64PROCESS) GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process") ;
	if ( fnCheckWindows64 != NULL ) {
		fnCheckWindows64(GetCurrentProcess(),&lSystem64);
	}
	#endif
	SIMPLE_API_RETNUMBER(lSystem64);
}

void simple_vm_os_isunix ( void *pPointer )
{
	#if defined(unix) || defined(__unix__) || defined(__unix)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_ismacosx ( void *pPointer )
{
	#if defined(__APPLE__)  || defined(__MACH__)
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_islinux ( void *pPointer )
{
	#ifdef __linux__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_isfreebsd ( void *pPointer )
{
	#ifdef __FreeBSD__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_isandroid ( void *pPointer )
{
	#ifdef __ANDROID__
	SIMPLE_API_RETNUMBER(1);
	#else
	SIMPLE_API_RETNUMBER(0);
	#endif
}

void simple_vm_os_windowsnl ( void *pPointer )
{
	SIMPLE_API_RETSTRING("\r\n");
}

void simple_vm_os_currentdir ( void *pPointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	simple_currentdir(cDirPath);
	SIMPLE_API_RETSTRING(cDirPath);
}

void simple_vm_os_exefilename ( void *pPointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	if ( simple_exefilename(cDirPath) ) {
		SIMPLE_API_RETSTRING(cDirPath);
	}
}

void simple_vm_os_chdir ( void *pPointer )
{
	SIMPLE_API_RETNUMBER(simple_chdir(SIMPLE_API_GETSTRING(1)));
}

void simple_vm_os_exefolder ( void *pPointer )
{
	char cDirPath[SIMPLE_PATHSIZE]  ;
	simple_exefolder(cDirPath);
	SIMPLE_API_RETSTRING(cDirPath);
}
