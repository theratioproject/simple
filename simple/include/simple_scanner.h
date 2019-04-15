
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: Azeez Adewale
 *
 * Created on July 10, 2017, 1:10 PM
 */


#ifndef simple_scanner_h
#define simple_scanner_h

/* Compiler - Scanner - Reading Files Blocks */
#define SIMPLE_FILE FILE *
#define SIMPLE_OPENFILE(x,y) fopen(x,y)
#define SIMPLE_CLOSEFILE(x) fclose(x)
#define SIMPLE_READCHAR(x,y,z) y = getc(x)  /* z is unused here = number of characters - default = 1 */

/* Data */
typedef struct Scanner {
	char state  ;
	List *Keywords  ;
	List *Operators  ;
	List *Tokens  ;
	String *ActiveToken  ;
	int LinesCount  ;
	/* Float Identification (0 = Start 1 = Number  2 = Number Dot  3 = Number Dot Number ) */
	char FloatMark  ;
	/* Literal Type "  or ' */
	char cLiteral  ;
	/* Multiline comment end ( 0 = start  1 = * ) */
	char cMLComment  ;
	/* Simple State */
	SimpleState *sState  ;
	/* Index of Keyword/Operator */
	int nTokenIndex  ;
	/* Literal Line */
	int nLiteralLine  ;
} Scanner ;
/* Keywords */
typedef enum SCANNER_KEYWORD {
	KEYWORD_IF=1 ,
	KEYWORD_TO ,
	/* Logic */
	KEYWORD_OR ,
	KEYWORD_AND ,
	KEYWORD_NOT ,
	KEYWORD_FOR ,
	KEYWORD_NEW ,
	KEYWORD_BLOCK ,
	KEYWORD_INHERIT ,
	KEYWORD_LOOP ,
	KEYWORD_FROM ,
	KEYWORD_CALL,
	KEYWORD_ELSE ,
	KEYWORD_DISPLAY ,
	KEYWORD_WHILE ,
	KEYWORD_CLASS ,
	KEYWORD_RETURN ,
	KEYWORD_END ,
	KEYWORD_READ ,
	KEYWORD_EXIT ,
	KEYWORD_BREAK ,
	KEYWORD_TRY ,
	KEYWORD_CATCH ,
	/* Switch */
	KEYWORD_SWITCH ,
	KEYWORD_DEFAULT ,
	KEYWORD_IN ,
	KEYWORD_CONTINUE ,
	/* Packages */
	KEYWORD_MODULE ,
	KEYWORD_IMPORT ,
	KEYWORD_PRIVATE ,
	KEYWORD_FINAL ,
	KEYWORD_STEP ,
	KEYWORD_DO ,
	KEYWORD_EXEC ,
	KEYWORD_ELSEIF ,
	KEYWORD_CASE ,
	KEYWORD_CHANGESIMPLEKEYWORD ,
	KEYWORD_CHANGESIMPLEIOPERATOR ,
	KEYWORD_LOADSYNTAX 
} SCANNER_KEYWORD ;

/* Secondary (Not Enforced) Keywords */
typedef enum SCANNER_SECONDARY_KEYWORD {
	KEYWORD_VARIADIC = 1
} SCANNER_SECONDARY_KEYWORD ;

/* Operators */
typedef enum SCANNER_OPERATOR {
	OP_PLUS = 1 ,
	OP_MINUS ,
	OP_MUL ,
	OP_DIV ,
	OP_REM ,
	OP_DOT ,
	OP_FOPEN ,
	OP_FCLOSE ,
	OP_EQUAL ,
	OP_COMMA ,
	OP_NOT ,
	OP_GREATER ,
	OP_LESS ,
	OP_LOPEN ,
	OP_LCLOSE ,
	OP_RANGE ,
	OP_BRACEOPEN ,
	OP_BRACECLOSE ,
	OP_BITAND ,
	OP_BITOR ,
	OP_BITNOT ,
	OP_XOR 
} SCANNER_OPERATOR ;
/* Blocks */

Scanner * new_simple_scanner ( SimpleState *sState ) ;

Scanner * delete_simple_scanner ( Scanner *scanner ) ;

int simple_scanner_readfile ( SimpleState *sState,char *file_name ) ;

void simple_scanner_readchar ( Scanner *scanner,char c ) ;

void simple_scanner_keywords ( Scanner *scanner ) ;

void simple_scanner_addtoken ( Scanner *scanner,int type ) ;

void simple_scanner_checktoken ( Scanner *scanner ) ;

int simple_scanner_isnumber ( char *cStr ) ;

int simple_scanner_checklasttoken ( Scanner *scanner ) ;

int simple_scanner_isoperator ( Scanner *scanner,const char *cStr ) ;

void simple_scanner_operators ( Scanner *scanner ) ;

int simple_scanner_lasttokentype ( Scanner *scanner ) ;

char * simple_scanner_lasttokenvalue ( Scanner *scanner ) ;

void simple_scanner_floatmark ( Scanner *scanner,int type ) ;

void simple_scanner_endofline ( Scanner *scanner ) ;

void simple_scanner_addreturn ( SimpleState *sState ) ;

void simple_scanner_addreturn2 ( SimpleState *sState ) ;

void simple_scanner_addreturn3 ( SimpleState *sState,int aPara[3] ) ;

void display_tokens ( Scanner *scanner ) ;

SIMPLE_API void simple_execute ( char *file_name, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int generate_object,int nWarn,int argc,char *argv[],int skip_error) ;

void simple_scanner_runobject( SimpleState *sState,char *file_name );

void simple_scanner_runobjstring ( SimpleState *sState,char *string,const char *file_name );

const char * simple_scanner_getkeywordtext ( const char *cStr ) ;

const char * simple_secondary_keyword_value(SCANNER_SECONDARY_KEYWORD position);

void simple_scanner_runprogram ( SimpleState *sState ) ;

void simple_scanner_changekeyword ( Scanner *scanner ) ;

void simple_scanner_changeoperator ( Scanner *scanner ) ;

void simple_scanner_loadsyntax ( Scanner *scanner ) ;

/* MACRO */
#define SIMPLE_SCANNER_DELETELASTTOKEN simple_list_deleteitem(scanner->Tokens,simple_list_getsize(scanner->Tokens))
/*
**  Constants 
**  General 
*/
#define SIMPLE_SCANNER_TOKENTYPE 1
#define SIMPLE_SCANNER_TOKENVALUE 2
/* Scanner Tokens Types */
#define SCANNER_TOKEN_KEYWORD 0
#define SCANNER_TOKEN_OPERATOR 1
#define SCANNER_TOKEN_LITERAL 2
#define SCANNER_TOKEN_NUMBER 3
#define SCANNER_TOKEN_IDENTIFIER 4
#define SCANNER_TOKEN_ENDLINE 5
#define SCANNER_TOKEN_NOTOKEN 6
/* Scanner States */
#define SCANNER_STATE_GENERAL 0
#define SCANNER_STATE_LITERAL 1
#define SCANNER_STATE_COMMENT 2
#define SCANNER_STATE_MLCOMMENT 3
#define SCANNER_STATE_CHANGEKEYWORD 4
#define SCANNER_STATE_CHANGEOPERATOR 5
#define SCANNER_STATE_LOADSYNTAX 6
/* Change Simple Keyword/Operator */
#define SIMPLE_SCANNER_CHANGERINGKEYWORD 47
#define SIMPLE_SCANNER_CHANGERINGOPERATOR 48
#define SIMPLE_SCANNER_LOADSYNTAX 49
#endif
