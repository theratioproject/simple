
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_misc.c
 * Author: thecarisma
 *
 * Created on July 12, 2017, 3:34 PM
 */

#include "../includes/simple.h"

int NOT_CASE_SENSITIVE = 0 ;
int SKIP_ERROR = 0 ;

SIMPLE_API void print_line ( void )
{
    puts("============================================================================================="); 
}

void display_help(){
    printf("Usage:  simple ([OPTIONS]) [PATH] [ARGS...]\n");
    printf("\t\t\t<to run a simple or complex file>\n\n");
    printf("[PATH]     : The Simple/Complex source file to execute.\n");
    printf("[ARG...]   : The arguments to pass to your simple application.\n");
    printf("([OPTIONS]): The flags/options to pass to the Simple VM/Simplify.\n\n");
    printf("The OPTIONS include : \n");
    printf("  -h -help                    Displays this help and exits.\n");
    printf("  -k -show-tokens             Scans and outputs the tokens in the source file.\n");
    printf("  -s -simplify                Compile simple file to one complex file.\n");
    printf("  -t -time                    Shows time before and after program execution.\n");
    printf("  -c -case-insensitive        Make simple case insensitive 'a=A'.\n");
    printf("  -v -verbose                 Displays all the modules and libraries of SIMPLE and exits.\n");
    printf("  -a -about                   Display the SIMPLE Property and exits.\n");
    printf("  -l -license                 Print the current SIMPLE LICENCE and exits.\n");
    printf("  -n -no-run                  Compile the program but don't run it.\n");
    printf("  -b -byte-code               Print the program Byte Code after compilation.\n");
    printf("  -e -error                   Skip all error instance and print error report in console.\n");
    //printf("  -l [PATH] -log-error [PATH] Skip all error instance and print error report in file.\n");
    //print_line(); printf("MORE OPTION BELOW"); print_line(); 
    //printf("\t-k [PATH] -show-tokens [PATH]             Save the token into a file for debugging.\n");
    exit(0);
}

void display_licence(){
    print_line();
    printf("\t\tSimple Intelligent and Modular Programming Language \n"
            "\t\tSIMPLE v%s | %s | %d - %d\n"
            , SIMPLE_VERSION, PRIMARY_AUTHOR, START_YEAR, CURRENT_YEAR);
    print_line();
    printf("\n\t\t\t\t\tMIT License\n\n");
    printf("\t\t\t\tCopyright (c) %d - %d simple\n\n",START_YEAR, CURRENT_YEAR);
    printf("\tPermission is hereby granted, free of charge, to any person obtaining a copy\n"
            "\tof this software and associated documentation files (the \"Software\"), to deal\n"
            "\tin the Software without restriction, including without limitation the rights\n"
            "\tto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
            "\tcopies of the Software, and to permit persons to whom the Software is\n"
            "\tfurnished to do so, subject to the following conditions:\n\n"
            "\tThe above copyright notice and this permission notice shall be included in all\n"
            "\tcopies or substantial portions of the Software.\n\n"
            "\tTHE SOFTWARE IS PROVIDED\"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
            "\tIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
            "\tFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
            "\tAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
            "\tLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
            "\tOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
            "\tSOFTWARE.\n"); 
    print_line(); exit(0);
}

void display_about(){
    print_line();
    printf("\t\tSimple Intelligent and Modular Programming Language - SIMPLE\n"
            "\tVERSION  : v%s\n"
            "\tAUTHOR   : %s\n"
            "\tLICENCE  : %s\n"
            "\tDATE     : %d - %d\n"
            , SIMPLE_VERSION, PRIMARY_AUTHOR, SIMPLE_LICENCE, START_YEAR, CURRENT_YEAR);
    print_line();
    exit(0);
}

int is_simple_file( const char *file_name )
{
    int x  ; 
    x = strlen(file_name) - 1 ;
    if ( x >= 5 ) {
        if ( tolower(file_name[x]) == 'm' && tolower(file_name[x-1]) == 'i' && tolower(file_name[x-2]) == 's' && tolower(file_name[x-3]) == '.'  ) {
            return 1 ;
        }
    }
    return 0 ;
}

int is_complex_file( const char *file_name )
{
    int x ;
    x = strlen(file_name) - 1 ;
    if ( x > 6 ) {
        if ( tolower(file_name[x]) == 'x' && tolower(file_name[x-1]) == 'e' && tolower(file_name[x-2]) == 'l' && tolower(file_name[x-3]) == 'm' && tolower(file_name[x-4]) == 'o' && file_name[x-5] == 'c' && file_name[x-5] == '.' ) {
            return 1 ;
        }
    } 
    return 0 ;
}

const char *file_real_name(const char *absolute_name){
    char *filename = (char*)calloc(1, sizeof(KB_BYTE_SIZE));
    if (strstr(absolute_name, "\\") != NULL ) {
        filename = (strrchr(absolute_name, '\\'))+1;
    } else {
        filename = (strrchr(absolute_name, '/'))+1;
    }

    return filename;
}

#if SIMPLE_TESTPERFORMANCE

static void simple_showtime ( time_t before_execution, time_t after_execution )
{
    time(&after_execution);
    double seconds = difftime(before_execution, after_execution);
    time_t timer  ;
	char buffer[50]  ;
	struct tm*tm_info  ;
	clock_t myclock  ;
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer,50,"Date  : %Y/%m/%d Time : %H:%M:%S", tm_info);
	printf( "\n" ) ;
	print_line();
	puts(buffer);
	myclock = clock();
	printf( "Clock : %ld \n", myclock ) ;
	print_line();
}
#endif