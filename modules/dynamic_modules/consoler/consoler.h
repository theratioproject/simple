
/* 
    Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com> 
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

#define CC_COLOR_BITS 5

typedef enum {
    CC_FG_NONE         = 0  << 0,
    CC_FG_BLACK        = 1  << 0,
    CC_FG_DARK_RED     = 2  << 0,
    CC_FG_DARK_GREEN   = 3  << 0,
    CC_FG_DARK_YELLOW  = 4  << 0,
    CC_FG_DARK_BLUE    = 5  << 0,
    CC_FG_DARK_MAGENTA = 6  << 0,
    CC_FG_DARK_CYAN    = 7  << 0,
    CC_FG_GRAY         = 8  << 0,
    CC_FG_DARK_GRAY    = 9  << 0,
    CC_FG_RED          = 10 << 0,
    CC_FG_GREEN        = 11 << 0,
    CC_FG_YELLOW       = 12 << 0,
    CC_FG_BLUE         = 13 << 0,
    CC_FG_MAGENTA      = 14 << 0,
    CC_FG_CYAN         = 15 << 0,
    CC_FG_WHITE        = 16 << 0,

    CC_BG_NONE         = 0  << CC_COLOR_BITS,
    CC_BG_BLACK        = 1  << CC_COLOR_BITS,
    CC_BG_DARK_RED     = 2  << CC_COLOR_BITS,
    CC_BG_DARK_GREEN   = 3  << CC_COLOR_BITS,
    CC_BG_DARK_YELLOW  = 4  << CC_COLOR_BITS,
    CC_BG_DARK_BLUE    = 5  << CC_COLOR_BITS,
    CC_BG_DARK_MAGENTA = 6  << CC_COLOR_BITS,
    CC_BG_DARK_CYAN    = 7  << CC_COLOR_BITS,
    CC_BG_GRAY         = 8  << CC_COLOR_BITS,
    CC_BG_DARK_GRAY    = 9  << CC_COLOR_BITS,
    CC_BG_RED          = 10 << CC_COLOR_BITS,
    CC_BG_GREEN        = 11 << CC_COLOR_BITS,
    CC_BG_YELLOW       = 12 << CC_COLOR_BITS,
    CC_BG_BLUE         = 13 << CC_COLOR_BITS,
    CC_BG_MAGENTA      = 14 << CC_COLOR_BITS,
    CC_BG_CYAN         = 15 << CC_COLOR_BITS,
    CC_BG_WHITE        = 16 << CC_COLOR_BITS
} cc_color_t;

#ifndef COMMON_LVB_LEADING_BYTE
#define COMMON_LVB_LEADING_BYTE    0x0100
#endif

#ifndef COMMON_LVB_TRAILING_BYTE
#define COMMON_LVB_TRAILING_BYTE   0x0200
#endif

#ifndef COMMON_LVB_GRID_HORIZONTAL
#define COMMON_LVB_GRID_HORIZONTAL 0x0400
#endif

#ifndef COMMON_LVB_GRID_LVERTICAL
#define COMMON_LVB_GRID_LVERTICAL  0x0800
#endif

#ifndef COMMON_LVB_GRID_RVERTICAL
#define COMMON_LVB_GRID_RVERTICAL  0x1000
#endif

#ifndef COMMON_LVB_REVERSE_VIDEO
#define COMMON_LVB_REVERSE_VIDEO   0x4000
#endif

#ifndef COMMON_LVB_UNDERSCORE
#define COMMON_LVB_UNDERSCORE      0x8000
#endif

int cc_fprintf(cc_color_t color, FILE* stream, const char* format, ...);

void program_flush_console(void *pointer);

void print_with_foreground_background ( void *pointer ) ;

void program_exit ( void *pointer ) ;

void program_sleep ( void *pointer ) ;

#ifdef __cplusplus
}
#endif

#endif /* CONSOLER_H */

