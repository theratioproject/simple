
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

void display_help(){
    printf("Usage:  simple ([OPTIONS]) [PATH] [ARGS...]\n");
    printf("\t\t\t<to run a simple or complex file>\n");
    printf("\tsimple ([OPTIONS]) [SARFILE] [ARGS...]\n");
    printf("\t\t\t<to run a simple archive file>\n\n");
    printf("[PATH]     : The Simple/Complex source file to execute.\n");
    printf("[ARG...]   : The arguments to pass to your simple application.\n");
    printf("([OPTIONS]): The flags/options to pass to the Simple VM.\n\n");
    printf("The OPTIONS [SIMPLE FILE] include : \n");
    printf("\t-h -help                    Displays this help and exits.\n");
    printf("\t-s -show-tokens             Scans and outputs the tokens in the source file.\n");
    printf("\t-t -time                    Shows the execution time of the program at completion.\n");
    printf("\t-v -verbose                 Displays all the modules and libraries of SIMPLE and exits.\n");
    printf("\t-a -about                   Display the SIMPLE Property and exits.\n");
    printf("\t-z -licence                 Print the current SIMPLE LICENCE and exits.\n");
    printf("\t-p -property                Pop up a dialog that shows the current SRE/SDK and your Computer Property.\n");
    printf("\t-e -error                   Skip all error instance and print error report in console.\n");
    printf("\t-l[PATH] -log-error[PATH]   Skip all error instance and print error report in file.\n");
}
