
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   systemic.h
 * Author: thecarisma
 *
 * Created on February 9, 2018, 10:04 PM
 */

#ifndef SYSTEMIC_H
#define SYSTEMIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define _sleep(x) sleep((x))

void init_simple_module ( SimpleState *pSimpleState ) ;

void os_ismsdos ( void *pointer ) ;

void os_iswindows ( void *pointer ) ;

void os_iswindows64 ( void *pointer ) ;

void os_isunix ( void *pointer ) ;

void os_ismacosx ( void *pointer ) ;

void os_islinux ( void *pointer ) ;

void os_isfreebsd ( void *pointer ) ;

void os_isandroid ( void *pointer ) ;

void os_windowsnl ( void *pointer ) ;

void os_currentdir ( void *pointer ) ;

void os_exefilename ( void *pointer ) ;

void os_chdir ( void *pointer ) ;

void os_exefolder ( void *pointer ) ;

void get_env ( void *pointer ) ;

void system_exit ( void *pointer ) ;

void current_filepath ( void *pointer ) ;

void current_filename ( void *pointer ) ;

void previous_filename ( void *pointer ) ;

void previous_filepath ( void *pointer ) ;

void exe_system ( void *pointer ) ;

void system_beep ( void *pointer ) ;

void system_sleep ( void *pointer ) ;

/* Constants */
#define SIMPLE_VM_POINTER_LIBNAME "system"

#ifdef __cplusplus
}
#endif

#endif /* SYSTEMIC_H */

