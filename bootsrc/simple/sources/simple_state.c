/*
**  Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> 
**  Include Files 
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
static int nRingStateDEBUGSEGFAULT  ;
static int nRingStateCGI  ;
/* Define Functions */
#if SIMPLE_TESTUNITS

static void simple_testallunits ( void ) ;
#endif
#if SIMPLE_TESTPERFORMANCE

static void simple_showtime ( void ) ;
#endif

void segfaultaction ( int sig ) ;
/* API Functions */

SIMPLE_API RingState * simple_state_new ( void )
{
	RingState *pRingState  ;
	pRingState = (RingState *) simple_malloc(sizeof(RingState));
	if ( pRingState == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pRingState->pRingFilesList = NULL ;
	pRingState->pRingFilesStack = NULL ;
	pRingState->pRingGenCode = NULL ;
	pRingState->pRingFunctionsMap = NULL ;
	pRingState->pRingClassesMap = NULL ;
	pRingState->pRingPackagesMap = NULL ;
	pRingState->pRingCFunctions = NULL ;
	pRingState->nISCGI = 0 ;
	pRingState->nRun = 1 ;
	pRingState->nPrintIC = 0 ;
	pRingState->nPrintICFinal = 0 ;
	pRingState->nPrintTokens = 0 ;
	pRingState->nPrintRules = 0 ;
	pRingState->nPrintInstruction = 0 ;
	pRingState->nGenObj = 0 ;
	pRingState->nWarning = 0 ;
	pRingState->argc = 0 ;
	pRingState->argv = NULL ;
	pRingState->pVM = NULL ;
	pRingState->lStartup = 0 ;
	pRingState->vPoolManager.pCurrentItem = NULL ;
	pRingState->vPoolManager.pBlockStart = NULL ;
	pRingState->vPoolManager.pBlockEnd = NULL ;
	pRingState->nDontDeleteTheVM = 0 ;
	pRingState->lNoLineNumber = 0 ;
	pRingState->nCustomGlobalScopeCounter = 0 ;
	pRingState->aCustomGlobalScopeStack = simple_list_new(0) ;
	simple_list_addint(pRingState->aCustomGlobalScopeStack,pRingState->nCustomGlobalScopeCounter);
	return pRingState ;
}

SIMPLE_API RingState * simple_state_delete ( RingState *pRingState )
{
	if ( pRingState->pRingFilesList != NULL ) {
		pRingState->pRingFilesList = simple_list_delete_gc(pRingState,pRingState->pRingFilesList);
		pRingState->pRingFilesStack = simple_list_delete_gc(pRingState,pRingState->pRingFilesStack);
	}
	if ( pRingState->pRingGenCode   != NULL ) {
		pRingState->pRingGenCode = simple_list_delete_gc(pRingState,pRingState->pRingGenCode);
		pRingState->pRingFunctionsMap = simple_list_delete_gc(pRingState,pRingState->pRingFunctionsMap);
		pRingState->pRingClassesMap = simple_list_delete_gc(pRingState,pRingState->pRingClassesMap);
		pRingState->pRingPackagesMap = simple_list_delete_gc(pRingState,pRingState->pRingPackagesMap);
		if ( pRingState->pRingCFunctions != NULL ) {
			/* We check because the execution may end by the compiler error */
			pRingState->pRingCFunctions = simple_list_delete_gc(pRingState,pRingState->pRingCFunctions);
		}
	}
	if ( pRingState->pVM != NULL ) {
		simple_vm_delete(pRingState->pVM);
	}
	simple_poolmanager_delete(pRingState);
	pRingState->aCustomGlobalScopeStack = simple_list_delete(pRingState->aCustomGlobalScopeStack);
	simple_free(pRingState);
	return NULL ;
}

void simple_state_cgiheader ( RingState *pRingState )
{
	if ( pRingState->nISCGI == 1 ) {
		printf( "Content-Type: text/plain \n\n" ) ;
	}
}

SIMPLE_API void simple_print_line ( void )
{
	puts("==================================================================");
}

SIMPLE_API RingState * simple_state_init ( void )
{
	RingState *pRingState  ;
	pRingState = simple_state_new();
	simple_vm_init(pRingState);
	return pRingState ;
}

SIMPLE_API void simple_state_runcode ( RingState *pRingState,const char *cStr )
{
	simple_vm_runcode(pRingState->pVM,cStr);
}

SIMPLE_API List * simple_state_findvar ( RingState *pRingState,const char *cStr )
{
	VM *pVM  ;
	List *pList  ;
	pVM = pRingState->pVM ;
	pList = NULL ;
	if ( simple_vm_findvar(pVM,cStr) ) {
		pList = (List *) SIMPLE_VM_STACK_READP ;
		SIMPLE_VM_STACK_POP ;
	}
	return pList ;
}

SIMPLE_API List * simple_state_newvar ( RingState *pRingState,const char *cStr )
{
	VM *pVM  ;
	List *pList  ;
	pVM = pRingState->pVM ;
	if ( simple_vm_findvar(pVM,cStr) == 0 ) {
		simple_vm_newvar(pVM,cStr);
	}
	pList = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	return pList ;
}

SIMPLE_API void simple_state_main ( int argc, char *argv[] )
{
	int x,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nPerformance,nSRC,nGenObj,nWarn  ;
	char *cStr  ;
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
	nRingStateDEBUGSEGFAULT = 0 ;
	nRingStateCGI = 0 ;
	signal(SIGSEGV,segfaultaction);
	#if SIMPLE_TESTUNITS
	simple_testallunits();
	#endif
	if ( argc > 1 ) {
		for ( x = 1 ; x < argc ; x++ ) {
			if ( strcmp(argv[x],"-cgi") == 0 ) {
				nCGI = 1 ;
				nRingStateCGI = 1 ;
			}
			else if ( strcmp(argv[x],"-tokens") == 0 ) {
				nTokens = 1 ;
			}
			else if ( strcmp(argv[x],"-rules") == 0 ) {
				nRules = 1 ;
			}
			else if ( strcmp(argv[x],"-ic") == 0 ) {
				nPrintIC = 1 ;
			}
			else if ( strcmp(argv[x],"-norun") == 0 ) {
				nRun = 0 ;
			}
			else if ( strcmp(argv[x],"-icfinal") == 0 ) {
				nPrintICFinal = 1 ;
			}
			else if ( strcmp(argv[x],"-ins") == 0 ) {
				nIns = 1 ;
			}
			else if ( strcmp(argv[x],"-clock") == 0 ) {
				nPerformance = 1 ;
			}
			else if ( strcmp(argv[x],"-go") == 0 ) {
				nGenObj = 1 ;
			}
			else if ( strcmp(argv[x],"-w") == 0 ) {
				nWarn = 1 ;
				nRingStateDEBUGSEGFAULT = 1 ;
			}
			else if ( ( simple_issourcefile(argv[x]) || simple_isobjectfile(argv[x])) && nSRC == 0 ) {
				cStr = argv[x] ;
				nSRC = 1 ;
			}
		}
	}
	#if SIMPLE_TESTPERFORMANCE
	if ( nPerformance ) {
		simple_showtime();
	}
	#endif
	srand(time(NULL));
	/* Check Startup ring.ring */
	if ( simple_fexists("ring.ring") && argc == 1 ) {
		simple_execute("ring.ring",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
		exit(0);
	}
	if ( simple_fexists("ring.ringo") && argc == 1 ) {
		simple_execute("ring.ringo",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
		exit(0);
	}
	/* Print Version */
	if ( (argc == 1) || (cStr == NULL) ) {
		simple_print_line();
		printf( "Ring version %s \n2013-2018, Mahmoud Fayed <msfclipper@yahoo.com>\n",SIMPLE_VERSION ) ;
		puts("Usage : ring filename.ring [Options]");
		simple_print_line();
		/* Options */
		puts("-tokens   :  Print a list of tokens in the source code file");
		puts("-rules    :  Print grammar rules applied on the tokens");
		puts("-ic       :  Print the intermediate byte code (before execution)");
		puts("-icfinal  :  Print the final byte code (after execution)");
		puts("-cgi      :  Print http response header before error messages");
		puts("-norun    :  Don't run the program after compiling");
		puts("-ins      :  Print instruction operation code before execution");
		puts("-clock    :  Print clock before and after program execution");
		puts("-go       :  Generate object file");
		puts("-w        :  Display Warnings");
		simple_print_line();
		exit(0);
	}
	simple_execute(cStr,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,nGenObj,nWarn,argc,argv);
	#if SIMPLE_TESTPERFORMANCE
	if ( nPerformance ) {
		simple_showtime();
	}
	#endif
}

SIMPLE_API void simple_state_runfile ( RingState *pRingState,char *cFileName )
{
	simple_scanner_readfile(pRingState,cFileName);
}

SIMPLE_API void simple_state_runobjectfile ( RingState *pRingState,char *cFileName )
{
	simple_scanner_runobjfile(pRingState,cFileName);
}

SIMPLE_API void simple_state_runobjectstring ( RingState *pRingState,char *cString,const char *cFileName )
{
	simple_scanner_runobjstring(pRingState,cString,cFileName);
}
#if SIMPLE_TESTUNITS

static void simple_testallunits ( void )
{
	/* Test */
	simple_stsimple_test();
	simple_list_test();
	simple_hashtable_test();
	printf( "end of test \n  " ) ;
	getchar();
}
#endif
#if SIMPLE_TESTPERFORMANCE

static void simple_showtime ( void )
{
	time_t timer  ;
	char buffer[50]  ;
	struct tm*tm_info  ;
	clock_t myclock  ;
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer,50,"Date  : %Y/%m/%d Time : %H:%M:%S", tm_info);
	printf( "\n" ) ;
	simple_print_line();
	puts(buffer);
	myclock = clock();
	printf( "Clock : %ld \n", myclock ) ;
	simple_print_line();
}
#endif

void segfaultaction ( int sig )
{
	if ( nRingStateDEBUGSEGFAULT == 1 ) {
		if ( nRingStateCGI == 1 ) {
			printf( "Content-Type: text/plain\n\n" ) ;
		}
		printf( SIMPLE_SEGFAULT ) ;
		printf( " : %d ",sig ) ;
	}
	exit(0);
}

int simple_issourcefile ( const char *cStr )
{
	int x  ;
	x = strlen(cStr) - 1 ;
	if ( x >= 5 ) {
		if ( tolower(cStr[x]) == 'g' && tolower(cStr[x-1]) == 'n' && tolower(cStr[x-2]) == 'i' && tolower(cStr[x-3]) == 'r' && cStr[x-4] == '.' ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_isobjectfile ( const char *cStr )
{
	int x  ;
	x = strlen(cStr) - 1 ;
	if ( x > 6 ) {
		if ( tolower(cStr[x]) == 'o' && tolower(cStr[x-1]) == 'g' && tolower(cStr[x-2]) == 'n' && tolower(cStr[x-3]) == 'i' && tolower(cStr[x-4]) == 'r' && cStr[x-5] == '.' ) {
			return 1 ;
		}
	}
	return 0 ;
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
