
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_state.c
 * Author: Azeez Adewale
 *
 * Created on July 10, 2017, 1:10 PM
 */


#include "../include/simple.h"
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
/* Define Blocks */
#if SIMPLE_TESTUNITS

static void simple_testallunits ( void ) ;
#endif

void segfaultaction ( int sig ) ;
/* API Blocks */

SIMPLE_API SimpleState * simple_state_new ( void )
{
	char module_path[SIMPLE_PATHSIZE] ;
	SimpleState *sState  ;
	sState = (SimpleState *) simple_malloc(sizeof(SimpleState));
	if ( sState == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	sState->main_file_path = "" ;
	sState->files_list = NULL ;
	sState->files_stack = NULL ;
	sState->generated_code = NULL ;
	sState->blocks_map = NULL ;
	sState->classes_map = NULL ;
	sState->modules_map = NULL ;
	sState->module_paths = simple_list_new_gc(sState,0);
	sState->c_blocks = NULL ;
	sState->nISCGI = 0 ;
	sState->nRun = 1 ;
	sState->nPrintIC = 0 ;
	sState->nPrintICFinal = 0 ;
	sState->nPrintTokens = 0 ;
	sState->nPrintRules = 0 ;
	sState->nPrintInstruction = 0 ;
	sState->nWarning = 0 ;
	sState->argc = 0 ;
	sState->argv = NULL ;
	sState->vm = NULL ;
	sState->lStartup = 0 ;
	sState->vPoolManager.pCurrentItem = NULL ;
	sState->vPoolManager.pBlockStart = NULL ;
	sState->vPoolManager.pBlockEnd = NULL ;
	sState->nDontDeleteTheVM = 0 ;
	sState->lNoLineNumber = 0 ;
	sState->nCustomGlobalScopeCounter = 0 ;
	sState->aCustomGlobalScopeStack = simple_list_new(0) ;
	sState->loaded_cblocks = 0 ;
	simple_list_addint(sState->aCustomGlobalScopeStack,sState->nCustomGlobalScopeCounter);
	if (sState->module_paths != NULL) {
		simple_list_addstring_gc(sState,sState->module_paths,"./modules/");
		/* */
		snprintf(module_path, sizeof(module_path), "%s/../modules/", simple_file_initial_dir);
		simple_list_addstring_gc(sState,sState->module_paths,module_path);
		/* */
		simple_distro_folder(module_path);
		snprintf(module_path, sizeof(module_path), "%s/modules/", module_path);
		simple_list_addstring_gc(sState,sState->module_paths,module_path);
		/* */
		snprintf(module_path, sizeof(module_path), "%s/modules/", getenv("SIMPLE_PATH"));
		simple_list_addstring_gc(sState,sState->module_paths,module_path);
		/* */
		snprintf(module_path, sizeof(module_path), "%s/s%s/modules/", getenv("SIMPLE_PATH"), SIMPLE_VERSION);
		simple_list_addstring_gc(sState,sState->module_paths,module_path);
		/* add the github folder in modules ;) */
		snprintf(module_path, sizeof(module_path), "%s/s%s/modules/github.com/", getenv("SIMPLE_PATH"), SIMPLE_VERSION);
		simple_list_addstring_gc(sState,sState->module_paths,module_path);
		/* Now we assume it is executed in a folder bin and the modules is in parent folder 
			like
			simple/bin/
			simple/modules/
			simple/include/
		so we go parent directory *simple* and check for modules. Think execute simple from zip extract
		*/
		simple_list_addstring_gc(sState,sState->module_paths,"../modules/");
		#if defined(_WIN32)
			snprintf(module_path, sizeof(module_path), "C:/Simple/s%s/modules/", SIMPLE_VERSION);
			simple_list_addstring_gc(sState,sState->module_paths,module_path);
		#elif defined(__ANDROID__)
			/* since we wait upon the android specific variable to be set, load android paths after
				this initalization. call simple_add_android_paths(SimpleState *sState) in android.
			*/
		#else
			snprintf(module_path, sizeof(module_path), "/var/lib/simple/s%s/modules/", SIMPLE_VERSION);
			simple_list_addstring_gc(sState,sState->module_paths,module_path);
			snprintf(module_path, sizeof(module_path), "%s/var/lib/simple/s%s/modules/", getenv("PREFIX"), SIMPLE_VERSION);
			simple_list_addstring_gc(sState,sState->module_paths,module_path);
		#endif
	}
	return sState ;
}

#if defined(__ANDROID__)
SIMPLE_API SimpleState * simple_add_android_paths(SimpleState *sState) 
{
	char module_path[SIMPLE_PATHSIZE] ;
	/* add sdcard (External Storage) first. user might want to update module without having to reinstall the app or wait for an update from developer (BAD IDEA) */
	snprintf(module_path, sizeof(module_path), "%s/simple/s%s/modules/", getenv("EXTERNAL_STORAGE"), SIMPLE_VERSION);
	/* now add the android app folder (Android/data/pakage.name/)*/
	snprintf(module_path, sizeof(module_path), "%s/modules/", sState->simple_ANativeActivity->externalDataPath);
	simple_list_addstring_gc(sState,sState->module_paths,module_path);
}
#endif

SIMPLE_API SimpleState * finalize_simple_state ( SimpleState *sState )
{
	if ( sState->files_list != NULL ) {
		sState->files_list = simple_list_delete_gc(sState,sState->files_list);
		sState->files_stack = simple_list_delete_gc(sState,sState->files_stack);
	}
	if ( sState->generated_code   != NULL ) {
		sState->generated_code = simple_list_delete_gc(sState,sState->generated_code);
		sState->blocks_map = simple_list_delete_gc(sState,sState->blocks_map);
		sState->classes_map = simple_list_delete_gc(sState,sState->classes_map);
		sState->modules_map = simple_list_delete_gc(sState,sState->modules_map);
		sState->module_paths = simple_list_delete_gc(sState,sState->module_paths);
		if ( sState->c_blocks != NULL ) {
			/* We check because the execution may end by the compiler error */
			sState->c_blocks = simple_list_delete_gc(sState,sState->c_blocks);
		}
	}
	if ( sState->vm != NULL ) {
		simple_vm_delete(sState->vm);
	}
	simple_poolmanager_delete(sState);
	sState->aCustomGlobalScopeStack = simple_list_delete(sState->aCustomGlobalScopeStack);
	simple_free(sState);
	return NULL ;
}

void simple_state_cgiheader ( SimpleState *sState )
{
	if ( sState->nISCGI == 1 ) {
		printf( "Content-Type: text/html \n\n" ) ;
	}
}

SIMPLE_API SimpleState * init_simple_state ( void )
{
	SimpleState *sState  ;
	sState = simple_state_new();
	simple_vm_init(sState);
	return sState ;
}

SIMPLE_API void execute_simple_code ( SimpleState *sState,const char *cStr )
{
        simple_vm_runcode(sState->vm,cStr);
}

SIMPLE_API List * simple_state_findvar ( SimpleState *sState,const char *cStr )
{
	VM *vm  ;
	List *list  ;
	vm = sState->vm ;
	list = NULL ;
	if ( simple_vm_findvar(vm,cStr) ) {
		list = (List *) SIMPLE_VM_STACK_READP ;
		SIMPLE_VM_STACK_POP ;
	}
	return list ;
}

SIMPLE_API List * simple_state_newvar ( SimpleState *sState,const char *cStr )
{
	VM *vm  ;
	List *list  ;
	vm = sState->vm ;
	if ( simple_vm_findvar(vm,cStr) == 0 ) {
		simple_vm_newvar(vm,cStr);
	}
	list = (List *) SIMPLE_VM_STACK_READP ;
	SIMPLE_VM_STACK_POP ;
	return list ;
}

SIMPLE_API void simple_state_main ( int argc, char *argv[] )
{
	int x,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,show_time,nSRC,generate_object,nWarn,skip_error  ;
	char *cStr  ; clock_t before_execution ; 
	/* Init Values */
	nCGI = 0 ;
	nRun = 1 ;
	nPrintIC = 0 ;
	nPrintICFinal = 0 ;
	nTokens = 0 ;
	nRules = 0 ;
	nIns = 0 ;
	show_time = 0 ;
	cStr = NULL ;
	nSRC = 0 ;
	generate_object = 0 ;
	nWarn = 0 ;
	skip_error=0;
	nSimpleStateDEBUGSEGFAULT = 0 ;
	nSimpleStateCGI = 0 ;
	signal(SIGSEGV,segfaultaction);
        before_execution = clock(); 
	#if SIMPLE_TESTUNITS
	simple_testallunits();
	#endif
	if ( argc > 1 ) {
		for ( x = 1 ; x < argc ; x++ ) {
			if ( strcmp(argv[x],"--show-tokens") == 0 || strcmp(argv[x],"-k") == 0 ) {
				nTokens = 1;
			} else if ( strcmp(argv[x],"--error") == 0 || strcmp(argv[x],"-e") == 0 ) {
				skip_error = 1;
			} else if ( strcmp(argv[x],"--version") == 0 || strcmp(argv[x],"-v") == 0 ) {
				display_version();
			} else if ( strcmp(argv[x],"--help") == 0 || strcmp(argv[x],"-h") == 0 ) {
				display_help();
			} else if ( strcmp(argv[x],"-s") == 0 || strcmp(argv[x],"--simplify") == 0 ) {
				generate_object = 1 ; nRun = 0 ;
			} else if ( strcmp(argv[x],"-n") == 0 || strcmp(argv[x],"--no-run") == 0 ) {
				nRun = 0 ;
			} else if ( strcmp(argv[x],"-b") == 0 || strcmp(argv[x],"--byte-code") == 0 ) {
				nPrintIC = 1 ;  nRun = 0 ;
			} else if ( strcmp(argv[x],"-b-f") == 0 || strcmp(argv[x],"--byte-code-final") == 0 ) {
				nPrintICFinal = 1 ;  nRun = 0 ;
			} else if ( strcmp(argv[x],"-t") == 0 || strcmp(argv[x],"--time") == 0 ) {
				show_time = 1 ;
			} else if ( strcmp(argv[x],"-i") == 0 || strcmp(argv[x],"-cgi") == 0 || strcmp(argv[x],"--web") == 0 ) {
				nCGI = 1 ; nSimpleStateCGI = 1 ;
			}
			else if ( strcmp(argv[x],"-rulesgfgdf") == 0 ) {
				nRules = 1 ;
			}
			else if ( strcmp(argv[x],"-instteret") == 0 ) {
				nIns = 1 ;
			}
			else if ( strcmp(argv[x],"-w") == 0 || strcmp(argv[x],"--warn") == 0 ) {
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
	/* Check Startup simple.sim */
	if ( simple_fexists("simple.sim") && argc == 1 ) {
		simple_execute("simple.sim",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,generate_object,nWarn,argc,argv,skip_error);
		exit(0);
	}
	if ( simple_fexists("simple.complex") && argc == 1 ) {
		simple_execute("simple.complex",nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,generate_object,nWarn,argc,argv,skip_error);
		exit(0);
	}
	/* Print Help */
	if ( (argc == 1) || (cStr == NULL) ) {
		display_help();
	}
	/*Assign default file dir */
	getcwd(simple_file_initial_dir, sizeof(simple_file_initial_dir));
	simple_execute(cStr,nCGI,nRun,nPrintIC,nPrintICFinal,nTokens,nRules,nIns,generate_object,nWarn,argc,argv,skip_error);
	#if SIMPLE_TESTPERFORMANCE
	if ( show_time ) {
		simple_showtime( before_execution);
	}
	#endif
}

SIMPLE_API void execute_simple_file ( SimpleState *sState,char *file_name )
{
	simple_scanner_readfile(sState,file_name);
}

SIMPLE_API void simple_state_runobjectfile ( SimpleState *sState,char *file_name )
{
	simple_scanner_runobject(sState,file_name);
}

SIMPLE_API void simple_execute_object( SimpleState *sState,char *string,const char *file_name )
{
	simple_scanner_runobjstring(sState,string,file_name);
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

/* General Blocks */

int simple_fexists ( const char *file_name )
{
	FILE *fp  ;
	fp = fopen(file_name , "r" );
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

void simple_distro_folder(char *dirPath) 
{
        char cDir[SIMPLE_PATHSIZE]  ;
	char cDir2[SIMPLE_PATHSIZE]  ;
	int x,x2,nSize  ;
	simple_exefilename(cDir);
	nSize = strlen( cDir ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (cDir[x] == 'b') ) {
			for ( x2 = x ; x2 >= 0 ; x2-- ) {
				cDir2[x2] = cDir[x2] ;
			}
                        cDir2[x-1] = '\0' ; cDir2[x] = '\0' ; cDir2[x+1] = '\0' ;
			break ;
		}
	}
	strcpy(dirPath,cDir2);
}

void simple_switchtofilefolder ( char *file_name )
{
	char file_name_two[SIMPLE_PATHSIZE]  ;
	strcpy(file_name_two,file_name);
	if ( simple_justfilepath(file_name_two) ) {
		simple_chdir(file_name_two);
		/* Remove The Path from the file Name - Keep the File Name Only */
		simple_justfilename(file_name);
		return ;
	}
}

int simple_justfilepath ( char *file_name )
{
	int x,nSize  ;
	nSize = strlen( file_name ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (file_name[x] == '\\') || (file_name[x] == '/') ) {
			file_name[x+1] = '\0' ;
			return 1 ;
		}
	}
	return 0 ;
}

void simple_justfilename ( char *file_name )
{
	int x,nSize,r  ;
	nSize = strlen( file_name ) ;
	for ( x = nSize-1 ; x >= 0 ; x-- ) {
		if ( (file_name[x] == '\\') || (file_name[x] == '/') ) {
			r = 0 ;
			for ( x = x+1 ; x <= nSize+1 ; x++ ) {
				file_name[r] = file_name[x] ;
				r++ ;
			}
			break ;
		}
	}
}
