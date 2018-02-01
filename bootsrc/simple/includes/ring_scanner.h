/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef ring_scanner_h
#define ring_scanner_h
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
	/* Ring State */
	RingState *pRingState  ;
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
	KEYWORD_FUNC ,
	KEYWORD_FROM ,
	KEYWORD_NEXT ,
	KEYWORD_LOAD ,
	KEYWORD_ELSE ,
	KEYWORD_SEE ,
	KEYWORD_WHILE ,
	KEYWORD_OK ,
	KEYWORD_CLASS ,
	KEYWORD_RETURN ,
	KEYWORD_BUT ,
	KEYWORD_END ,
	KEYWORD_GIVE ,
	KEYWORD_BYE ,
	KEYWORD_EXIT ,
	KEYWORD_TRY ,
	KEYWORD_CATCH ,
	KEYWORD_DONE ,
	/* Switch */
	KEYWORD_SWITCH ,
	KEYWORD_ON ,
	KEYWORD_OTHER ,
	KEYWORD_OFF ,
	KEYWORD_IN ,
	KEYWORD_LOOP ,
	/* Packages */
	KEYWORD_PACKAGE ,
	KEYWORD_IMPORT ,
	KEYWORD_PRIVATE ,
	KEYWORD_STEP ,
	KEYWORD_DO ,
	KEYWORD_AGAIN ,
	KEYWORD_CALL ,
	KEYWORD_ELSEIF ,
	KEYWORD_GET ,
	KEYWORD_CASE ,
	KEYWORD_DEF ,
	KEYWORD_ENDFUNC ,
	KEYWORD_ENDCLASS ,
	KEYWORD_ENDPACKAGE ,
	KEYWORD_CHANGERINGKEYWORD ,
	KEYWORD_CHANGERINGIOPERATOR ,
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

Scanner * ring_scanner_new ( RingState *pRingState ) ;

Scanner * ring_scanner_delete ( Scanner *pScanner ) ;

int ring_scanner_readfile ( RingState *pRingState,char *cFileName ) ;

void ring_scanner_readchar ( Scanner *pScanner,char c ) ;

void ring_scanner_keywords ( Scanner *pScanner ) ;

void ring_scanner_addtoken ( Scanner *pScanner,int type ) ;

void ring_scanner_checktoken ( Scanner *pScanner ) ;

int ring_scanner_isnumber ( char *cStr ) ;

int ring_scanner_checklasttoken ( Scanner *pScanner ) ;

int ring_scanner_isoperator ( Scanner *pScanner,const char *cStr ) ;

void ring_scanner_operators ( Scanner *pScanner ) ;

int ring_scanner_lasttokentype ( Scanner *pScanner ) ;

char * ring_scanner_lasttokenvalue ( Scanner *pScanner ) ;

void ring_scanner_floatmark ( Scanner *pScanner,int type ) ;

void ring_scanner_endofline ( Scanner *pScanner ) ;

void ring_scanner_addreturn ( RingState *pRingState ) ;

void ring_scanner_addreturn2 ( RingState *pRingState ) ;

void ring_scanner_addreturn3 ( RingState *pRingState,int aPara[3] ) ;

void display_tokens ( Scanner *pScanner ) ;

SIMPLE_API void ring_execute ( char *cFileName, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int nGenObj,int nWarn,int argc,char *argv[] ) ;

const char * ring_scanner_getkeywordtext ( const char *cStr ) ;

void ring_scanner_runobjfile ( RingState *pRingState,char *cFileName ) ;

void ring_scanner_runprogram ( RingState *pRingState ) ;

void ring_scanner_changekeyword ( Scanner *pScanner ) ;

void ring_scanner_changeoperator ( Scanner *pScanner ) ;

void ring_scanner_loadsyntax ( Scanner *pScanner ) ;

void ring_scanner_runobjstring ( RingState *pRingState,char *cString,const char *cFileName ) ;
/* MACRO */
#define SIMPLE_SCANNER_DELETELASTTOKEN ring_list_deleteitem(pScanner->Tokens,ring_list_getsize(pScanner->Tokens))
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
/* Change Ring Keyword/Operator */
#define SIMPLE_SCANNER_CHANGERINGKEYWORD 47
#define SIMPLE_SCANNER_CHANGERINGOPERATOR 48
#define SIMPLE_SCANNER_LOADSYNTAX 49
#endif
