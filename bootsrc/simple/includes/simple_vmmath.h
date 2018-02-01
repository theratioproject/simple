/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_vmmath_h
#define simple_vmmath_h
/* Functions */

void simple_vm_math_loadfunctions ( RingState *pRingState ) ;

void simple_vm_math_sin ( void *pPointer ) ;

void simple_vm_math_cos ( void *pPointer ) ;

void simple_vm_math_tan ( void *pPointer ) ;

void simple_vm_math_asin ( void *pPointer ) ;

void simple_vm_math_acos ( void *pPointer ) ;

void simple_vm_math_atan ( void *pPointer ) ;

void simple_vm_math_atan2 ( void *pPointer ) ;

void simple_vm_math_sinh ( void *pPointer ) ;

void simple_vm_math_cosh ( void *pPointer ) ;

void simple_vm_math_tanh ( void *pPointer ) ;

void simple_vm_math_exp ( void *pPointer ) ;

void simple_vm_math_log ( void *pPointer ) ;

void simple_vm_math_log10 ( void *pPointer ) ;

void simple_vm_math_ceil ( void *pPointer ) ;

void simple_vm_math_floor ( void *pPointer ) ;

void simple_vm_math_fabs ( void *pPointer ) ;

void simple_vm_math_pow ( void *pPointer ) ;

void simple_vm_math_sqrt ( void *pPointer ) ;

void simple_vm_math_unsigned ( void *pPointer ) ;

void simple_vm_math_decimals ( void *pPointer ) ;

void simple_vm_math_murmur3hash ( void *pPointer ) ;
#endif
