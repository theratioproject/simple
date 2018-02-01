
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

#include "../includes/ring.h"

SIMPLE_API void print_line ( void )
{
	puts("==================================================================");
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
    printf("  -v -verbose                 Displays all the modules and libraries of SIMPLE and exits.\n");
    printf("  -a -about                   Display the SIMPLE Property and exits.\n");
    printf("  -z -licence                 Print the current SIMPLE LICENCE and exits.\n");
    //printf("\t-p -property                Pop up a dialog that shows the current SIMPLE and your Computer Property.\n");
    printf("  -e -error                   Skip all error instance and print error report in console.\n");
    printf("  -l [PATH] -log-error [PATH] Skip all error instance and print error report in file.\n");
    //print_line(); printf("MORE OPTION BELOW"); print_line(); 
    //printf("\t-k [PATH] -show-tokens [PATH]             Save the token into a file for debugging.\n");
}
