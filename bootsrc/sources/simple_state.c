
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


#include "../includes/simple.h"
#ifdef _WIN32
/* Windows only */
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#if __MACH__
/* Mac OS X */
#include <mach-o/dyld.h>
#endif
#endif
/* General Options (Only for simple_state_main()) */
static int nSimpleStateDEBUGSEGFAULT  ;
static int nSimpleStateCGI  ;
/* Define Functions */
#if SIMPLE_TESTUNITS

static void simple_testallunits ( void ) ;
#endif

void segfaultaction ( int sig ) ;
/* API Functions */

SIMPLE_API SimpleState * simple_state_new ( void )
{
	SimpleState *pSimpleState  ;
	pSimpleState = (SimpleState *) simple_malloc(sizeof(SimpleState));
	if ( pSimpleState == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pSimpleState->pSimpleFilesList = NULL ;
	pSimpleState->pSimpleFilesStack = NULL ;
	pSimpleState->pSimpleGenCode = NULL ;
	pSimpleState->pSimpleFunctionsMap = NULL ;
	pSimpleState->pSimpleClassesMap = NULL ;
	pSimpleState->pSimpleModulessMap = NULL ;
	pSimpleState->pSimpleCFunctions = NULL ;
	pSimpleState->nISCGI = 0 ;
	pSimpleState->nRun = 1 ;
	pSimpleState->nPrintIC = 0 ;
	pSimpleState->nPrintICFinal = 0 ;
	pSimpleState->nPrintTokens = 0 ;
	pSimpleState->nPrintRules = 0 ;
	pSimpleState->nPrintInstruction = 0 ;
	pSimpleState->nGenObj = 0 ;
	pSimpleState->nWarning = 0 ;
	pSimpleState->argc = 0 ;
	pSimpleState->argv = NULL ;
	pSimpleState->vm = NULL ;
	pSimpleState->lStartup = 0 ;
	pSimpleState->vPoolManager.pCurrentItem = NULL ;
	pSimpleState->vPoolManager.pBlockStart = NULL ;
	pSimpleState->vPoolManager.pBlockEnd = NULL ;
	pSimpleState->nDontDeleteTheVM = 0 ;
	pSimpleState->lNoLineNumber = 0 ;
	pSimpleState->nCustomGlobalScopeCounter = 0 ;
	pSimpleState->aCustomGlobalScopeStack = simple_list_new(0) ;
	simple_list_addint(pSimpleState->aCustomGlobalScopeStack,pSimpleState->nCustomGlobalScopeCounter);
	return pSimpleState ;
}

SIMPLE_API SimpleState * simple_state_delete ( SimpleState *pSimpleState )
{
	if ( pSimpleState->pSimpleFilesList != NULL ) {
		pSimpleState->pSimpleFilesList = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleFilesList);
		pSimpleState->pSimpleFilesStack = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleFilesStack);
	}
	if ( pSimpleState->pSimpleGenCode   != NULL ) {
		pSimpleState->pSimpleGenCode = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleGenCode);
		pSimpleState->pSimpleFunctionsMap = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleFunctionsMap);
		pSimpleState->pSimpleClassesMap = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleClassesMap);
		pSimpleState->pSimpleModulessMap = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleModulessMap);
		if ( pSimpleState->pSimpleCFunctions != NULL ) {
			/* We check because the execution may end by the compiler error */
			pSimpleState->pSimpleCFunctions = simple_list_delete_gc(pSimpleState,pSimpleState->pSimpleCFunctions);
		}
	}
	if ( pSimpleState->vm != NULL ) {
		simple_vm_delete(pSimpleState->vm);
	}
	simple_poolmanager_delete(pSimpleState);
	pSimpleState->aCustomGlobalScopeStack = simple_list_delete(pSimpleState->aCustomGlobalScopeStack);
	simple_free(pSimpleState);
	return NULL ;
}

void simple_state_cgiheader ( SimpleState *pSimpleState )
{
	if ( pSimpleState->nISCGI == 1 ) {
		printf( "Content-Type: text/plain \n\n" ) ;
	}
}

SIMPLE_API SimpleState * simple_state_init ( void )
{
	SimpleState *pSimpleState  ;
	pSimpleState = simple_state_new();
	simple_vm_init(pSimpleState);
	return pSimpleState ;
}

SIMPLE_API void simple_state_runcode ( SimpleState *pSimpleState,const char *cStr )
{
	simple_vm_runcode(pSimpleState->vm,cStr);
}

SIMPLE_API List * simple_state_findvar ( SimpleState *pSimpleState,const char *cStr )
{
	VM *vm  ;
	List *pList  ;
	vm = pSimpleState->vm ;
	pList = NULL ;
	if ( simple_vm_findvar(vm,cStr) ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		SIMPLE_VM_STACK_POP ;
	}
	return pList ;
}

SIMPLE_API List * simple_state_newvar ( SimpleState *pSimpleState,const char *cStr )
{
	VM *vm  ;
	List *pList  ;
	vm = pSimpleState->vm ;
	if ( simple_vm_findvar(vm,cStr) == 0 ) {
		simple_vm_newvar(vm,cStr);
	}
	pList = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	return pList ;
}

SIMPLE_API void simple_state_main ( int argc, char *argv[] )
{
	int x,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nPerformance,nSRC,nGenObj,nWarn  ;
	char *cStr  ; time_t before_execution, after_execution; 
	/* Init Values */
	nCGI = 0 ;
	nRun = 1 ;
	nPrintIC = 0 ;
	nPrintICFinal = 0 ;
	nTokens = 0 ;
	nRules = 0 ;
	nIns = 0 ;
	nPerformance = 0 ;
	cStr = NULL ;
	nSRC = 0 ;
	nGenObj = 0 ;
	nWarn = 0 ;
	nSimpleStateDEBUGSEGFAULT = 0 ;
	nSimpleStateCGI = 0 ;
	signal(SIGSEGV,segfaultaction);
        time(&before_execution); 
	#if SIMPLE_TESTUNITS
	simple_testallunits();
	#endif
	if ( argc > 1 ) {
		for ( x = 1 ; x < argc ; x++ ) {
			if ( strcmp(argv[x],"-cgi") == 0 ) {
				nCGI = 1 ;
				nSimpleStateCGI = 1 ;
			}
			else if ( strcmp(argv[x],"-show-tokens") == 0 || strcmp(argv[x],"-k") == 0 ) {
				nTokens = 1;
			} else if ( strcmp(argv[x],"-case-insensitive") == 0 || strcmp(argv[x],"-c") == 0 ) {
				NOT_CASE_SENSITIVE = 1;
			} else if ( strcmp(argv[x],"-error") == 0 || strcmp(argv[x],"-e") == 0 ) {
				SKIP_ERROR = 1;
			} else if ( strcmp(argv[x],"-license") == 0 || strcmp(argv[x],"-l") == 0 ) {
				display_licence();
			} else if ( strcmp(argv[x],"-help") == 0 || strcmp(argv[x],"-h") == 0 ) {
				display_help();
			} else if ( strcmp(argv[x],"-about") == 0 || strcmp(argv[x],"-a") == 0 ) {
				display_about();
			} else if ( strcmp(argv[x],"-s") == 0 || strcmp(argv[x],"-simplify") == 0 ) {
				nGenObj = 1 ; nRun = 0 ;
			} else if ( strcmp(argv[x],"-n") == 0 || strcmp(argv[x],"-no-run") == 0 ) {
				nRun = 0 ;
			} else if ( strcmp(argv[x],"-b") == 0 || strcmp(argv[x],"-byte-code") == 0 ) {
				nPrintIC = 1 ;  nRun = 0 ;
			} else if ( strcmp(argv[x],"-bf") == 0 || strcmp(argv[x],"-byte-code-final") == 0 ) {
				nPrintICFinal = 1 ;  nRun = 0 ;
			} else if ( strcmp(argv[x],"-t") == 0 || strcmp(argv[x],"-time") == 0 ) {
				nPerformance = 1 ;
			}
			else if ( strcmp(argv[x],"-rulesgfgdf") == 0 ) {
				nRules = 1 ;
			}
			else if ( strcmp(argv[x],"-instteret") == 0 ) {
				nIns = 1 ;
			}
			else if ( strcmp(argv[x],"-w") == 0 ) {
				nWarn = 1 ;
				nSimpleStateDEBUGSEGFAULT = 1 ;
			}
			else if ( ( is_simple_file(argv[x]) || is_complex_file(argv[x])) && nSRC == 0 ) {
				cStr = argv[x] ;
				nSRC = 1 ;
			}
		}
	}
	srand(time(NULL));
	/* Check Startup ring.sim */
	if ( simple_fexists("ring.sim") && argc == 1 ) {
		simple_execute("ring.sim",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
		exit(0);
	}
	if ( simple_fexists("ring.complex") && argc == 1 ) {
		simple_execute("ring.complex",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
		exit(0);
	}
	/* Print Version */
	if ( (argc == 1) || (cStr == NULL) ) {
		display_help();
	}
	simple_execute(cStr,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
	#if SIMPLE_TESTPERFORMANCE
	if ( nPerformance ) {
		simple_showtime( before_execution, after_execution );
	}
	#endif
}

SIMPLE_API void simple_state_runfile ( SimpleState *pSimpleState,char *cFileName )
{
	simple_scanner_readfile(pSimpleState,cFileName);
}

SIMPLE_API void simple_state_runobjectfile ( SimpleState *pSimpleState,char *cFileName )
{
	simple_scanner_runobjfile(pSimpleState,cFileName);
}

SIMPLE_API void simple_state_runobjectstring ( SimpleState *pSimpleState,char *cString,const char *cFileName )
{
	simple_scanner_runobjstring(pSimpleState,cString,cFileName);
}
#if SIMPLE_TESTUNITS

static void simple_testallunits ( void )
{
	/* Test */
	simple_string_test();
	simple_list_test();
	simple_hashtable_test();
	printf( "end of test \n  " ) ;
	getchar();
}
#endif

void segfaultaction ( int sig )
{
	if ( nSimpleStateDEBUGSEGFAULT == 1 ) {
		if ( nSimpleStateCGI == 1 ) {
			printf( "Content-Type: text/plain\n\n" ) ;
		}
		printf( SIMPLE_SEGFAULT ) ;
		printf( " : %d ",sig ) ;
	}
	exit(0);
}

/* General Functions */

int simple_fexists ( const char *cFileName )
{
	FILE *fp  ;
	fp = fopen(cFileName , "r" );
	if ( fp ) {
		fclose( fp ) ;
		return 1 ;
	}
	return 0 ;
}

int simple_currentdir ( char *cDirPath )
{
	int nSize  ;
	nSize = SIMPLE_PATHSIZE ;
	if ( !GetCurrentDir(cDirPath, nSize) ) {
		return errno ;
	}
	cDirPath[nSize-1] = '\0' ;
	return 0 ;
}

int simple_exefilename ( char *cDirPath )
{
	unsigned int nSize  ;
	nSize = SIMPLE_PATHSIZE ;
	#ifdef _WIN32
	/* Windows only */
	GetModuleFileName(NULL,cDirPath,nSize);
	#elif __MACH__
	/* Mac OS X */
	_NSGetExecutablePath(cDirPath,&nSize);
	#elif __linux__
	/* readlink() doesn't null terminate */
	memset(cDirPath,0,nSize);
	if ( ! readlink("/proc/self/exe",cDirPath,nSize) ) {
		return 0 ;
	}
	#endif
	return 1 ;
}

int simple_chdir ( const char *cDir )
{
	return chdir(cDir) ;
}

void simple_exefolder ( char *cDirPath )
{
	char cDir[SIMPLE_PATHSIZE]  ;
	char cDir2[SIMPLE_PATHSIZE]  ;
	int x,x2,nSize  ;
	simple_exefilename(cDir);
	nSize = strlen( cDir ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (cDir[x] == '\\') || (cDir[x] == '/') ) {
			for ( x2 = x ; x2 >= 0 ; x2-- ) {
				cDir2[x2] = cDir[x2] ;
			}
			cDir2[x+1] = '\0' ;
			break ;
		}
	}
	strcpy(cDirPath,cDir2);
}

void simple_switchtofilefolder ( char *cFileName )
{
	char cFileName2[SIMPLE_PATHSIZE]  ;
	strcpy(cFileName2,cFileName);
	if ( simple_justfilepath(cFileName2) ) {
		simple_chdir(cFileName2);
		/* Remove The Path from the file Name - Keep the File Name Only */
		simple_justfilename(cFileName);
		return ;
	}
}

int simple_justfilepath ( char *cFileName )
{
	int x,nSize  ;
	nSize = strlen( cFileName ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (cFileName[x] == '\\') || (cFileName[x] == '/') ) {
			cFileName[x+1] = '\0' ;
			return 1 ;
		}
	}
	return 0 ;
}

void simple_justfilename ( char *cFileName )
{
	int x,nSize,r  ;
	nSize = strlen( cFileName ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (cFileName[x] == '\\') || (cFileName[x] == '/') ) {
			r = 0 ;
			for ( x = x+1 ; x <= nSize+1 ; x++ ) {
				cFileName[r] = cFileName[x] ;
				r++ ;
			}
			break ;
		}
	}
}
