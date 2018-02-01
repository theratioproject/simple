/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"

void simple_vm_extension ( RingState *pRingState )
{
	/* Reflection and Meta-programming */
	#if SIMPLE_VM_REFMETA
	simple_vm_refmeta_loadfunctions(pRingState);
	#endif
	/* List Functions */
	#if SIMPLE_VM_LISTFUNCS
	simple_vm_listfuncs_loadfunctions(pRingState);
	#endif
	/* Math */
	#if SIMPLE_VM_MATH
	simple_vm_math_loadfunctions(pRingState);
	#endif
	/* File */
	#if SIMPLE_VM_FILE
	simple_vm_file_loadfunctions(pRingState);
	#endif
	/* OS */
	#if SIMPLE_VM_OS
	simple_vm_os_loadfunctions(pRingState);
	#endif
	/* DLL */
	#if SIMPLE_VM_DLL
	simple_vm_dll_loadfunctions(pRingState);
	#endif
}
