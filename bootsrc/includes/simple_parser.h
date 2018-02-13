
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


#ifndef simple_parser_h
#define simple_parser_h
/* Data */
typedef struct Parser {
	List *Tokens  ;
	int ActiveToken  ;
	int TokensCount  ;
	char TokenType  ;
	const char *TokenText  ;
	int nTokenIndex  ;
	int nLineNumber  ;
	int nErrorLine  ;
	int nErrorsCount  ;
	List *GenCode  ;
	List *ActiveGenCodeList  ;
	/* Variable to select between = and == while using = only in the code */
	char nAssignmentFlag  ;
	/* Variable to determine the start of the class definition */
	char nClassStart  ;
	/* Lists of Lists, Functions in Program or in Class */
	List *FunctionsMap  ;
	/* Lists of Lists, Classes in Program or in Class */
	List *ClassesMap  ;
	/* List of Lists, Moduless in the program */
	List *ModulessMap  ;
	/* Mark to class label to be used by Private */
	int nClassMark  ;
	/* Private Flag */
	char nPrivateFlag  ;
	/* Counter to know if we are inside { } or not */
	int nBraceFlag  ;
	/* required for For-Step , insert instructions */
	char nInsertFlag  ;
	int nInsertCounter  ;
	/* required for using { } after using new object to avoid assignment */
	char nNoAssignment  ;
	/* Object ClassName() Uses mixer for one purpose only( function call)  - don't continue to get braces { } */
	char nFuncCallOnly  ;
	/* Flag to tell { } that we are inside control structure (if/for/while/...) expression */
	int nControlStructureExpr  ;
	/* Flag - We started using braces {} in control structure - we have { */
	int nControlStructureBrace  ;
	/* Simple State */
	SimpleState *sState  ;
} Parser ;
/* Error Messages */
#define PARSER_ERROR_PARALIST "COMPILER ERROR 0 : Check your parameters, Identifier expected"
#define PARSER_ERROR_CLASSNAME "COMPILER ERROR 1 : Invalid class name"
#define PARSER_ERROR_END "COMPILER ERROR 2 : The structure is not closed missing end | {}"
#define PARSER_ERROR_BLOCKNAME "COMPILER ERROR 3 : Invalid block name"
#define PARSER_ERROR_LISTITEM "COMPILER ERROR 4 : Error in list items"
#define PARSER_ERROR_MISSPARENTHESES "COMPILER ERROR 5 : Parentheses ')' is required "
#define PARSER_ERROR_MISSBRACKETS "COMPILER ERROR 6 : Brackets ']' is required "
#define PARSER_ERROR_PRENTCLASSNAME "COMPILER ERROR 7 : You need to provide a valid parent class name"
#define PARSER_ERROR_EXPROPERATOR "COMPILER ERROR 8 : Unknown expression operator"
#define PARSER_ERROR_NOCLASSDEFINED "COMPILER ERROR 9 : Specified class is not defined"
#define PARSER_ERROR_VARNAME "COMPILER ERROR 10 : Invalid variable name"
#define PARSER_ERROR_NOCATCH "COMPILER ERROR 11 : 'catch' keyword is missing in try | catch"
#define PARSER_ERROR_SWITCHEXPR "COMPILER ERROR 12 : Error in Switch statement expression"
#define PARSER_ERROR_BRACESNOTCLOSED "COMPILER ERROR 13 : Missing closing brace for the opened block"
#define PARSER_ERROR_NUMERICOVERFLOW "COMPILER ERROR 14 : Numeric Overflow!"
#define PARSER_ERROR_MODULENAME "COMPILER ERROR 15 : Error in module name"
#define PARSER_ERROR_BLOCKREDEFINE "COMPILER ERROR 16 : The block is already defined "
#define PARSER_ERROR_USINGBRACTAFTERNUM "COMPILER ERROR 17 : Using '(' after number"
#define PARSER_ERROR_PARENTLIKESUBCLASS "COMPILER ERROR 18 : The parent class name is identical to class name"
#define PARSER_ERROR_ACCESSSELFREF "COMPILER ERROR 19 : Object reference is out of context"
#define PARSER_ERROR_CLASSREDEFINE "COMPILER ERROR 20 : Class is already defined"
/* Functions */

int accept_token_token( Parser *parser, SCANNER_OPERATOR nType );

int simple_parser_start ( List *pTokens,SimpleState *sState ) ;

Parser * simple_parser_new ( List *pTokens,SimpleState *sState ) ;

Parser * simple_parser_delete ( Parser *parser ) ;

void simple_parser_printtokens ( Parser *parser ) ;
/* Grammar */

int simple_parser_class ( Parser *parser ) ;

int simple_parser_stmt ( Parser *parser ) ;

int simple_parser_step ( Parser *parser,int *nMark1 ) ;

int load_module( Parser *parser );

int simple_parser_paralist ( Parser *parser ) ;

int simple_parser_expr ( Parser *parser ) ;

int simple_parser_logicnot ( Parser *parser ) ;

int simple_parser_equalornot ( Parser *parser ) ;

int simple_parser_compare ( Parser *parser ) ;

int simple_parser_bitorxor ( Parser *parser ) ;

int simple_parser_bitand ( Parser *parser ) ;

int simple_parser_bitshift ( Parser *parser ) ;

int simple_parser_arithmetic ( Parser *parser ) ;

int simple_parser_term ( Parser *parser ) ;

int simple_parser_range ( Parser *parser ) ;

int simple_parser_factor ( Parser *parser,int *nFlag ) ;

int simple_parser_mixer ( Parser *parser ) ;

int simple_parser_list ( Parser *parser ) ;

int simple_parser_epslion ( Parser *parser ) ;

int simple_parser_passepslion ( Parser *parser ) ;

int simple_parser_namedotname ( Parser *parser ) ;

int simple_parser_ppmm ( Parser *parser ) ;

int simple_parser_csexpr ( Parser *parser ) ;

int simple_parser_csbraceend ( Parser *parser ) ;

int simple_parser_objattributes ( Parser *parser ) ;

int simple_parser_bracesandend ( Parser *parser,int lClass,SCANNER_KEYWORD nKeyword ) ;
/* Check Token */

void simple_parser_loadtoken ( Parser *parser ) ;

int simple_parser_nexttoken ( Parser *parser ) ;

int simple_parser_iskeyword ( Parser *parser,SCANNER_KEYWORD x ) ;

int simple_parser_isoperator ( Parser *parser,const char *cStr ) ;

int simple_parser_isliteral ( Parser *parser ) ;

int simple_parser_isidentifier ( Parser *parser ) ;

int simple_parser_isnumber ( Parser *parser ) ;

int simple_parser_isendline ( Parser *parser ) ;

int simple_parser_settoken ( Parser *parser,int x ) ;

int simple_parser_isanykeyword ( Parser *parser ) ;

int simple_parser_isoperator2 ( Parser *parser,SCANNER_OPERATOR nType ) ;
/* Display Errors */

void parser_error ( Parser *parser,const char *cStr ) ;
/* Generate Code */

void simple_parser_gencall ( Parser *parser,int nCallMethod ) ;

void simple_parser_gencallbracemethod ( Parser *parser,const char *cMethod ) ;
/* MACRO */
#define SIMPLE_PARSER_IGNORENEWLINE while(simple_parser_epslion(parser));
#define SIMPLE_PARSER_PASSNEWLINE while(simple_parser_passepslion(parser));
#define SIMPLE_PARSER_CURRENTTOKEN parser->ActiveToken
#define SIMPLE_PARSER_OPERATIONID simple_list_getsize(parser->GenCode)
#endif
