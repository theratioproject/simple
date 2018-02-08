
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: thecarisma
 *
 * Created on July 10, 2017, 1:10 PM
 */


#ifndef simple_state_h
#define simple_state_h
/* Data */
typedef struct SimpleState {
	/* First use by simple_scanner_readfile */
	List *pSimpleFilesList  ;
	List *pSimpleFilesStack  ;
	/* First use by simple_parser_new */
	List *pSimpleGenCode  ;
	List *pSimpleFunctionsMap  ;
	List *pSimpleClassesMap  ;
	List *pSimpleModulessMap  ;
	/* First use by simple_vm_new */
	List *pSimpleCFunctions  ;
	/* ISCGI is 1 if we are using the language as for CGI development */
	unsigned int nISCGI : 1  ;
	/* RUN is 0 if we need to compile only */
	unsigned int nRun : 1  ;
	/* PRINTIC is 1 if we need to print byte code before execution */
	unsigned int nPrintIC : 1  ;
	/* set to 1 if we need to print the fine byte code after execution */
	unsigned int nPrintICFinal : 1  ;
	/* set to 1 if we need to print the tokens */
	unsigned int nPrintTokens : 1  ;
	/* set to 1 if we need to print the grammar rules */
	unsigned int nPrintRules : 1  ;
	/* set to 1 if we need to print the  current instruction executed */
	unsigned int nPrintInstruction : 1  ;
	/* set to 1 if we need to generate the object file (ringo) */
	unsigned int nGenObj : 1  ;
	/* set to 1 if we need to display warnings */
	unsigned int nWarning : 1  ;
	/* Set to 1 to tell the scanner to don't delete the VM after execution */
	unsigned int nDontDeleteTheVM : 1  ;
	/* command line parameters */
	int argc  ;
	char  **argv  ;
	/* Virtual Machine */
	struct VM *vm  ;
	/* Startup File */
	char lStartup  ;
	/* Pool Manager */
	PoolManager vPoolManager  ;
	/* Avoid line number ( when we use executeCode() from VM ) */
	char lNoLineNumber  ;
	/* Custom Global Scope */
	int nCustomGlobalScopeCounter  ;
	List *aCustomGlobalScopeStack  ;
} SimpleState ;
/* Functions */

SIMPLE_API SimpleState * simple_state_new ( void ) ;

SIMPLE_API SimpleState * simple_state_delete ( SimpleState *sState ) ;

void simple_state_cgiheader ( SimpleState *sState ) ;

SIMPLE_API void print_line ( void ) ;

SIMPLE_API SimpleState * simple_state_init ( void ) ;

SIMPLE_API void simple_state_runcode ( SimpleState *sState,const char *cStr ) ;

SIMPLE_API List * simple_state_findvar ( SimpleState *sState,const char *cStr ) ;

SIMPLE_API List * simple_state_newvar ( SimpleState *sState,const char *cStr ) ;

SIMPLE_API void simple_state_main ( int argc, char *argv[] ) ;

SIMPLE_API void simple_state_runfile ( SimpleState *sState,char *cFileName ) ;

SIMPLE_API void simple_state_runobjectfile ( SimpleState *sState,char *cFileName ) ;

SIMPLE_API void simple_state_runobjectstring ( SimpleState *sState,char *cString,const char *cFileName ) ;
/* MACRO */
#define SIMPLE_STATE_CHECKPRINTRULES if ( parser->sState->nPrintRules )
/* General Functions */

int simple_fexists ( const char *cFileName ) ;

int simple_currentdir ( char *cDirPath ) ;

int simple_exefilename ( char *cDirPath ) ;

int simple_chdir ( const char *cDir ) ;

void simple_exefolder ( char *cDirPath ) ;

void simple_switchtofilefolder ( char *cFileName ) ;

int simple_justfilepath ( char *cFileName ) ;

void simple_justfilename ( char *cFileName ) ;
#endif
