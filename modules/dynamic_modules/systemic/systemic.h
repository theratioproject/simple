
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
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

SIMPLE_API void init_simple_module(SimpleState *sState) ;

void systemic_ismsdos(void *pointer) ;
void systemic_iswindows(void *pointer) ;
void systemic_iswindows64(void *pointer) ;
void systemic_isunix(void *pointer);
void systemic_ismacosx(void *pointer);
void systemic_islinux(void *pointer);
void systemic_isfreebsd(void *pointer);
void systemic_isandroid(void *pointer);
void systemic_istermux(void *pointer);
void systemic_windowsnl(void *pointer);
void systemic_currentdir(void *pointer);
void systemic_exefilename(void *pointer);
void systemic_chdir(void *pointer);
void systemic_exefolder(void *pointer);
void get_env (void *pointer);

void systemic_monitor_count(void *pointer);
void systemic_screen_sizes(void *pointer);

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

