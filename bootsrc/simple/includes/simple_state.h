/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_state_h
#define simple_state_h
/* Data */
typedef struct RingState {
	/* First use by simple_scanner_readfile */
	List *pRingFilesList  ;
	List *pRingFilesStack  ;
	/* First use by simple_parser_new */
	List *pRingGenCode  ;
	List *pRingFunctionsMap  ;
	List *pRingClassesMap  ;
	List *pRingPackagesMap  ;
	/* First use by simple_vm_new */
	List *pRingCFunctions  ;
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
	/* set to 1 if we need to generate the object file (simpleo) */
	unsigned int nGenObj : 1  ;
	/* set to 1 if we need to display warnings */
	unsigned int nWarning : 1  ;
	/* Set to 1 to tell the scanner to don't delete the VM after execution */
	unsigned int nDontDeleteTheVM : 1  ;
	/* command line parameters */
	int argc  ;
	char  **argv  ;
	/* Virtual Machine */
	struct VM *pVM  ;
	/* Startup File */
	char lStartup  ;
	/* Pool Manager */
	PoolManager vPoolManager  ;
	/* Avoid line number ( when we use eval() from VM ) */
	char lNoLineNumber  ;
	/* Custom Global Scope */
	int nCustomGlobalScopeCounter  ;
	List *aCustomGlobalScopeStack  ;
} RingState ;
/* Functions */

SIMPLE_API RingState * simple_state_new ( void ) ;

SIMPLE_API RingState * simple_state_delete ( RingState *pRingState ) ;

void simple_state_cgiheader ( RingState *pRingState ) ;

SIMPLE_API void simple_print_line ( void ) ;

SIMPLE_API RingState * simple_state_init ( void ) ;

SIMPLE_API void simple_state_runcode ( RingState *pRingState,const char *cStr ) ;

SIMPLE_API List * simple_state_findvar ( RingState *pRingState,const char *cStr ) ;

SIMPLE_API List * simple_state_newvar ( RingState *pRingState,const char *cStr ) ;

SIMPLE_API void simple_state_main ( int argc, char *argv[] ) ;

SIMPLE_API void simple_state_runfile ( RingState *pRingState,char *cFileName ) ;

SIMPLE_API void simple_state_runobjectfile ( RingState *pRingState,char *cFileName ) ;

SIMPLE_API void simple_state_runobjectstring ( RingState *pRingState,char *cStsimple,const char *cFileName ) ;
/* MACRO */
#define SIMPLE_STATE_CHECKPRINTRULES if ( pParser->pRingState->nPrintRules )
#define SIMPLE_VERSION "1.7"
/* General Functions */

int simple_fexists ( const char *cFileName ) ;

int simple_currentdir ( char *cDirPath ) ;

int simple_exefilename ( char *cDirPath ) ;

int simple_chdir ( const char *cDir ) ;

void simple_exefolder ( char *cDirPath ) ;

int simple_issourcefile ( const char *cStr ) ;

int simple_isobjectfile ( const char *cStr ) ;

void simple_switchtofilefolder ( char *cFileName ) ;

int simple_justfilepath ( char *cFileName ) ;

void simple_justfilename ( char *cFileName ) ;
#endif
