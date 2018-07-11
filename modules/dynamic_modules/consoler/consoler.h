
/* 
    Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   consoler.h
 * Author: thecarisma
 *
 * Created on February 11, 2018, 12:28 AM
 */

#ifndef CONSOLER_H
#define CONSOLER_H

#ifdef __cplusplus
extern "C" {
#endif

void program_flush_console(void *pointer);

void print_with_foreground_background ( void *pointer ) ;

void console_beep ( void *pointer ) ;

void program_exit ( void *pointer ) ;

void program_sleep ( void *pointer ) ;

#ifdef __cplusplus
}
#endif

#endif /* CONSOLER_H */

