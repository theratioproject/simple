/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simpleext_h
#define simpleext_h
/* Constants */
#define SIMPLE_VM_LISTFUNCS 1
#define SIMPLE_VM_REFMETA 1
#define SIMPLE_VM_MATH 1
#define SIMPLE_VM_FILE 1
#define SIMPLE_VM_OS 1
#define SIMPLE_VM_DLL 1
/* Compiler - Scanner - Reading Files Functions */
#define SIMPLE_FILE FILE *
#define SIMPLE_OPENFILE(x,y) fopen(x,y)
#define SIMPLE_CLOSEFILE(x) fclose(x)
#define SIMPLE_READCHAR(x,y,z) y = getc(x)  /* z is unused here = number of characters - default = 1 */
#endif
