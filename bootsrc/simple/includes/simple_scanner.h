/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_scanner_h
#define simple_scanner_h
/* Data */
typedef struct Scanner {
	char state  ;
	List *Keywords  ;
	List *Operators  ;
	List *Tokens  ;
	Stsimple *ActiveToken  ;
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
	K_IF=1 ,
	K_TO ,
	/* Logic */
	K_OR ,
	K_AND ,
	K_NOT ,
	K_FOR ,
	K_NEW ,
	K_FUNC ,
	K_FROM ,
	K_NEXT ,
	K_LOAD ,
	K_ELSE ,
	K_SEE ,
	K_WHILE ,
	K_OK ,
	K_CLASS ,
	K_RETURN ,
	K_BUT ,
	K_END ,
	K_GIVE ,
	K_BYE ,
	K_EXIT ,
	K_TRY ,
	K_CATCH ,
	K_DONE ,
	/* Switch */
	K_SWITCH ,
	K_ON ,
	K_OTHER ,
	K_OFF ,
	K_IN ,
	K_LOOP ,
	/* Packages */
	K_PACKAGE ,
	K_IMPORT ,
	K_PRIVATE ,
	K_STEP ,
	K_DO ,
	K_AGAIN ,
	K_CALL ,
	K_ELSEIF ,
	K_PUT ,
	K_GET ,
	K_CASE ,
	K_DEF ,
	K_ENDFUNC ,
	K_ENDCLASS ,
	K_ENDPACKAGE ,
	K_CHANGERINGKEYWORD ,
	K_CHANGERINGIOPERATOR ,
	K_LOADSYNTAX 
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

Scanner * simple_scanner_new ( RingState *pRingState ) ;

Scanner * simple_scanner_delete ( Scanner *pScanner ) ;

int simple_scanner_readfile ( RingState *pRingState,char *cFileName ) ;

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

void simple_scanner_addreturn ( RingState *pRingState ) ;

void simple_scanner_addreturn2 ( RingState *pRingState ) ;

void simple_scanner_addreturn3 ( RingState *pRingState,int aPara[3] ) ;

void simple_scanner_printtokens ( Scanner *pScanner ) ;

RING_API void simple_execute ( char *cFileName, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int nGenObj,int nWarn,int argc,char *argv[] ) ;

const char * simple_scanner_getkeywordtext ( const char *cStr ) ;

void simple_scanner_runobjfile ( RingState *pRingState,char *cFileName ) ;

void simple_scanner_runprogram ( RingState *pRingState ) ;

void simple_scanner_changekeyword ( Scanner *pScanner ) ;

void simple_scanner_changeoperator ( Scanner *pScanner ) ;

void simple_scanner_loadsyntax ( Scanner *pScanner ) ;

void simple_scanner_runobjstsimple ( RingState *pRingState,char *cStsimple,const char *cFileName ) ;
/* MACRO */
#define RING_SCANNER_DELETELASTTOKEN simple_list_deleteitem(pScanner->Tokens,simple_list_getsize(pScanner->Tokens))
/*
**  Constants 
**  General 
*/
#define RING_SCANNER_TOKENTYPE 1
#define RING_SCANNER_TOKENVALUE 2
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
#define RING_SCANNER_CHANGERINGKEYWORD 47
#define RING_SCANNER_CHANGERINGOPERATOR 48
#define RING_SCANNER_LOADSYNTAX 49
#endif
