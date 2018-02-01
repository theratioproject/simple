/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_vmrefmeta_h
#define simple_vmrefmeta_h
/* Functions */

void simple_vm_refmeta_loadfunctions ( RingState *pRingState ) ;
/* Functions */

void simple_vm_refmeta_locals ( void *pPointer ) ;

void simple_vm_refmeta_globals ( void *pPointer ) ;

void simple_vm_refmeta_functions ( void *pPointer ) ;

void simple_vm_refmeta_cfunctions ( void *pPointer ) ;

void simple_vm_refmeta_islocal ( void *pPointer ) ;

void simple_vm_refmeta_isglobal ( void *pPointer ) ;

void simple_vm_refmeta_isfunction ( void *pPointer ) ;

void simple_vm_refmeta_iscfunction ( void *pPointer ) ;
/* OOP */

void simple_vm_refmeta_packages ( void *pPointer ) ;

void simple_vm_refmeta_ispackage ( void *pPointer ) ;

void simple_vm_refmeta_classes ( void *pPointer ) ;

void simple_vm_refmeta_isclass ( void *pPointer ) ;

void simple_vm_refmeta_packageclasses ( void *pPointer ) ;

void simple_vm_refmeta_ispackageclass ( void *pPointer ) ;

void simple_vm_refmeta_classname ( void *pPointer ) ;

void simple_vm_refmeta_objectid ( void *pPointer ) ;

void simple_vm_refmeta_attributes ( void *pPointer ) ;

void simple_vm_refmeta_methods ( void *pPointer ) ;

void simple_vm_refmeta_isattribute ( void *pPointer ) ;

void simple_vm_refmeta_ismethod ( void *pPointer ) ;

void simple_vm_refmeta_isprivateattribute ( void *pPointer ) ;

void simple_vm_refmeta_isprivatemethod ( void *pPointer ) ;

void simple_vm_refmeta_addattribute ( void *pPointer ) ;

void simple_vm_refmeta_addmethod ( void *pPointer ) ;

void simple_vm_refmeta_getattribute ( void *pPointer ) ;

void simple_vm_refmeta_setattribute ( void *pPointer ) ;

void simple_vm_refmeta_mergemethods ( void *pPointer ) ;

void simple_vm_refmeta_packagename ( void *pPointer ) ;
/* VM */

void simple_vm_refmeta_simplevmfileslist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmcalllist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmmemorylist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmfunctionslist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmclasseslist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmpackageslist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmcfunctionslist ( void *pPointer ) ;

void simple_vm_refmeta_simplevmsettrace ( void *pPointer ) ;

void simple_vm_refmeta_simplevmtracedata ( void *pPointer ) ;

void simple_vm_refmeta_simplevmtraceevent ( void *pPointer ) ;

void simple_vm_refmeta_simplevmtracefunc ( void *pPointer ) ;

void simple_vm_refmeta_simplevmscopescount ( void *pPointer ) ;

void simple_vm_refmeta_simplevmevalinscope ( void *pPointer ) ;

void simple_vm_refmeta_simplevmpasserror ( void *pPointer ) ;

void simple_vm_refmeta_simplevmhideerrormsg ( void *pPointer ) ;

void simple_vm_refmeta_simplevmcallfunc ( void *pPointer ) ;
#endif
