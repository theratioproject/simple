
/*
    Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com>
    MIT License Copyright (c) 2018 simple

*/

/*
 * File:   consoler.h
 * Author: thecarisma
 *
 * Created on February 11, 2018, 12:26 AM
 */

#include "../../../simple/includes/simple.h"
#include "consoler.h"

#if defined(__GNUC__)
#include <stdarg.h>
#endif

#ifdef _WIN32
	#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft
    #define SIMPLE_API __declspec(dllexport)
    #define SIMPLE_API __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
    #define SIMPLE_API
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{
    register_block("__flush_console",program_flush_console);
    register_block("__printwfb",print_with_foreground_background);
    register_block("__exit",program_exit);
}

void program_flush_console(void *pointer)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	} else {
		fflush(stdout);
		return;
	}
}

void print_with_foreground_background ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISNUMBER(1) && ! SIMPLE_API_ISNUMBER(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	cc_fprintf(((int ) SIMPLE_API_GETNUMBER(1) << 0 ) | ((int ) SIMPLE_API_GETNUMBER(2) << CC_COLOR_BITS ), stdout, SIMPLE_API_GETSTRING(3));
}

void program_exit ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT == 1 ) {
		if ( SIMPLE_API_ISNUMBER(1) ) {
			exit(SIMPLE_API_GETNUMBER(1));
			return ;
		}
	}
	exit(0);
}

static int Write(FILE *stream, const char *format, va_list ap) {
#if defined(_WIN32) && !defined(__MINGW32__)
    return vfprintf_s(stream, format, ap);
#else
    return vfprintf(stream, format, ap);
#endif
}

#ifdef _WIN32
static const WORD FG[] = {
/* NONE         */  0,
/* BLACK        */  0,
/* DARK_RED     */  FOREGROUND_RED,
/* DARK_GREEN   */  FOREGROUND_GREEN,
/* DARK_YELLOW  */  FOREGROUND_RED | FOREGROUND_GREEN,
/* DARK_BLUE    */  FOREGROUND_BLUE,
/* DARK_MAGENTA */  FOREGROUND_RED | FOREGROUND_BLUE,
/* DARK_CYAN    */  FOREGROUND_GREEN | FOREGROUND_BLUE,
/* GRAY         */  FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED,
/* DARK_GRAY    */  FOREGROUND_INTENSITY,
/* RED          */  FOREGROUND_INTENSITY | FOREGROUND_RED,
/* GREEN        */  FOREGROUND_INTENSITY | FOREGROUND_GREEN,
/* YELLOW       */  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
/* BLUE         */  FOREGROUND_INTENSITY | FOREGROUND_BLUE,
/* MAGENTA      */  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
/* CYAN         */  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
/* WHITE        */  FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED,
};

static const WORD BG[] = {
/* NONE         */  0,
/* BLACK        */  0,
/* DARK_RED     */  BACKGROUND_RED,
/* DARK_GREEN   */  BACKGROUND_GREEN,
/* DARK_YELLOW  */  BACKGROUND_RED | BACKGROUND_GREEN,
/* DARK_BLUE    */  BACKGROUND_BLUE,
/* DARK_MAGENTA */  BACKGROUND_RED | BACKGROUND_BLUE,
/* DARK_CYAN    */  BACKGROUND_GREEN | BACKGROUND_BLUE,
/* GRAY         */  BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED,
/* DARK_GRAY    */  BACKGROUND_INTENSITY,
/* RED          */  BACKGROUND_INTENSITY | BACKGROUND_RED,
/* GREEN        */  BACKGROUND_INTENSITY | BACKGROUND_GREEN,
/* YELLOW       */  BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
/* BLUE         */  BACKGROUND_INTENSITY | BACKGROUND_BLUE,
/* MAGENTA      */  BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
/* CYAN         */  BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
/* WHITE        */  BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED,
};

static WORD ExtractForeground(WORD attributes) {
    const WORD mask =
        FOREGROUND_INTENSITY |
        FOREGROUND_GREEN |
        FOREGROUND_BLUE |
        FOREGROUND_RED;
    return attributes & mask;
}

static WORD ExtractBackground(WORD attributes) {
    const WORD mask =
        BACKGROUND_INTENSITY |
        BACKGROUND_GREEN |
        BACKGROUND_BLUE |
        BACKGROUND_RED;
    return attributes & mask;
}

static WORD ExtractOthers(WORD attributes) {
    const WORD mask =
        COMMON_LVB_LEADING_BYTE |
        COMMON_LVB_TRAILING_BYTE |
        COMMON_LVB_GRID_HORIZONTAL |
        COMMON_LVB_GRID_LVERTICAL |
        COMMON_LVB_GRID_RVERTICAL |
        COMMON_LVB_REVERSE_VIDEO |
        COMMON_LVB_UNDERSCORE;
    return attributes & mask;
}

static WORD Generate(unsigned int fg, unsigned int bg, WORD attributes) {
    WORD result = ExtractOthers(attributes);
    result |= ((fg == 0) ? ExtractForeground(attributes) : FG[fg]);
    result |= ((bg == 0) ? ExtractBackground(attributes) : BG[bg]);
    return result;
}

#else

static inline unsigned int Shift(
        unsigned int val, unsigned int normal, unsigned int bright) {
    if (val == 0) {
        return 9 + normal;
    }
    val -= 1;
    /* background */
    if (val >= 8) {
        return (val - 8) + bright;
    }
    return val + normal;
}

static void UnixTerminalColorize(
        FILE* stream, unsigned int fg, unsigned int bg) {
    fprintf(stream, "\x1B[39;49;%u;%um", Shift(fg, 30, 90), Shift(bg, 40, 100));
}

static void UnixTerminalRestore(FILE* stream) {
    fputs("\x1B[39;49m\x1B[K", stream);
}
#endif  /* _WIN32 */

int cc_fprintf(cc_color_t color, FILE* stream, const char* format, ...) {
    unsigned int fg;
    unsigned int bg;
    int result = -EINVAL;
    va_list ap;
#ifdef _WIN32
    HANDLE console;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
#endif  /* _WIN32 */

    va_start(ap, format);

    if (!isatty(fileno(stream)) || (stream != stdout && stream != stderr)) {
        result = Write(stream, format, ap);
        goto finish;
    }

    fg = color & ((1 << CC_COLOR_BITS) - 1);
    bg = (color >> CC_COLOR_BITS) & ((1 << CC_COLOR_BITS) - 1);

#ifdef _WIN32
    console = GetStdHandle(
            stream == stdout ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
    if (console == INVALID_HANDLE_VALUE) {
        result = Write(stream, format, ap);
        goto finish;
    }
    if (!GetConsoleScreenBufferInfo(console, &csbi)) {
        result = Write(stream, format, ap);
        goto finish;
    }
    SetConsoleTextAttribute(console, Generate(fg, bg, csbi.wAttributes));
    result = Write(stream, format, ap);
    SetConsoleTextAttribute(console, csbi.wAttributes);
#else
    UnixTerminalColorize(stream, fg, bg);
    Write(stream, format, ap);
    UnixTerminalRestore(stream);
#endif  /* _WIN32 */

finish:
    va_end(ap);
    return result;
}
