
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


#ifndef simple_scanner_h
#define simple_scanner_h

/* Compiler - Scanner - Reading Files Functions */
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
	KEYWORD_CALL ,
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
	KEYWORD_FINALLY ,
	/* Switch */
	KEYWORD_SWITCH ,
	KEYWORD_DEFAULT ,
	KEYWORD_IN ,
	KEYWORD_CONTINUE ,
	/* Packages */
	KEYWORD_MODULE ,
	KEYWORD_PRIVATE ,
	KEYWORD_STEP ,
	KEYWORD_DO ,
	KEYWORD_EXEC ,
	KEYWORD_ELSEIF ,
	KEYWORD_GET ,
	KEYWORD_CASE ,
	KEYWORD_CHANGESIMPLEKEYWORD ,
	KEYWORD_CHANGESIMPLEIOPERATOR ,
	KEYWORD_LOADSYNTAX 
} SCANNER_KEYWORD ;
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
/* Functions */

Scanner * simple_scanner_new ( SimpleState *sState ) ;

Scanner * simple_scanner_delete ( Scanner *pScanner ) ;

int simple_scanner_readfile ( SimpleState *sState,char *file_name ) ;

void simple_scanner_readchar ( Scanner *pScanner,char c ) ;

void simple_scanner_keywords ( Scanner *pScanner ) ;

void simple_scanner_addtoken ( Scanner *pScanner,int type ) ;

void simple_scanner_checktoken ( Scanner *pScanner ) ;

int simple_scanner_isnumber ( char *cStr ) ;

int simple_scanner_checklasttoken ( Scanner *pScanner ) ;

int simple_scanner_isoperator ( Scanner *pScanner,const char *cStr ) ;

void simple_scanner_operators ( Scanner *pScanner ) ;

int simple_scanner_lasttokentype ( Scanner *pScanner ) ;

char * simple_scanner_lasttokenvalue ( Scanner *pScanner ) ;

void simple_scanner_floatmark ( Scanner *pScanner,int type ) ;

void simple_scanner_endofline ( Scanner *pScanner ) ;

void simple_scanner_addreturn ( SimpleState *sState ) ;

void simple_scanner_addreturn2 ( SimpleState *sState ) ;

void simple_scanner_addreturn3 ( SimpleState *sState,int aPara[3] ) ;

void display_tokens ( Scanner *pScanner ) ;

SIMPLE_API void simple_execute ( char *file_name, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int nGenObj,int nWarn,int argc,char *argv[] ) ;

const char * simple_scanner_getkeywordtext ( const char *cStr ) ;

void simple_scanner_runprogram ( SimpleState *sState ) ;

void simple_scanner_changekeyword ( Scanner *pScanner ) ;

void simple_scanner_changeoperator ( Scanner *pScanner ) ;

void simple_scanner_loadsyntax ( Scanner *pScanner ) ;

/* MACRO */
#define SIMPLE_SCANNER_DELETELASTTOKEN simple_list_deleteitem(pScanner->Tokens,simple_list_getsize(pScanner->Tokens))
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
