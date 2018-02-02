
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
	/* List of Lists, Packages in the program */
	List *PackagesMap  ;
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
	/* Object Init() Uses mixer for one purpose only( function call)  - don't continue to get braces { } */
	char nFuncCallOnly  ;
	/* Flag to tell { } that we are inside control structure (if/for/while/...) expression */
	int nControlStructureExpr  ;
	/* Flag - We started using braces {} in control structure - we have { */
	int nControlStructureBrace  ;
	/* Ring State */
	RingState *pRingState  ;
} Parser ;
/* Error Messages */
#define SIMPLE_PARSER_ERROR_PARALIST "Error (C1) : Error in parameters list, expected identifier"
#define SIMPLE_PARSER_ERROR_CLASSNAME "Error (C2) : Error in class name"
#define SIMPLE_PARSER_ERROR_OK "Error (C3) : Unclosed control strucutre, 'ok' is missing"
#define SIMPLE_PARSER_ERROR_END "Error (C4) : Unclosed control strucutre, 'end' is missing"
#define SIMPLE_PARSER_ERROR_NEXT "Error (C5) : Unclosed control strucutre, next is missing"
#define SIMPLE_PARSER_ERROR_FUNCNAME "Error (C6) : Error in function name"
#define SIMPLE_PARSER_ERROR_LISTITEM "Error (C7) : Error in list items"
#define SIMPLE_PARSER_ERROR_MISSPARENTHESES "Error (C8) : Parentheses ')' is missing "
#define SIMPLE_PARSER_ERROR_MISSBRACKETS "Error (C9) : Brackets ']' is missing "
#define SIMPLE_PARSER_ERROR_PRENTCLASSNAME "Error (C10) : Error in parent class name"
#define SIMPLE_PARSER_ERROR_EXPROPERATOR "Error (C11) : Error in expression operator"
#define SIMPLE_PARSER_ERROR_NOCLASSDEFINED "Error (C12) :No class definition"
#define SIMPLE_PARSER_ERROR_VARNAME "Error (C13) : Error in variable name"
#define SIMPLE_PARSER_ERROR_NOCATCH "Error (C14) : Try/Catch miss the Catch keyword!"
#define SIMPLE_PARSER_ERROR_NODONE "Error (C15) : Try/Catch miss the Done keyword!"
#define SIMPLE_PARSER_ERROR_SWITCHEXPR "Error (C16) : Error in Switch statement expression!"
#define SIMPLE_PARSER_ERROR_SWITCHOFF "Error (C17) : Switch statement without OFF"
#define SIMPLE_PARSER_ERROR_BRACESNOTCLOSED "Error (C18) : Missing closing brace for the block opened!"
#define SIMPLE_PARSER_ERROR_NUMERICOVERFLOW "Error (C19) : Numeric Overflow!"
#define SIMPLE_PARSER_ERROR_PACKAGENAME "Error (C20) : Error in package name"
#define SIMPLE_PARSER_ERROR_AGAIN "Error (C21) : Unclosed control strucutre, 'again' is missing"
#define SIMPLE_PARSER_ERROR_FUNCREDEFINE "Error (C22) : Function redefinition, function is already defined!"
#define SIMPLE_PARSER_ERROR_USINGBRACTAFTERNUM "Error (C23) : Using '(' after number!"
#define SIMPLE_PARSER_ERROR_PARENTLIKESUBCLASS "Error (C24) : The parent class name is identical to the subclass name"
#define SIMPLE_PARSER_ERROR_ACCESSSELFREF "Error (C25) : Trying to access the self reference after the object name"
#define SIMPLE_PARSER_ERROR_CLASSREDEFINE "Error (C26) : Class redefinition, class is already defined!"
/* Functions */

int simple_parser_start ( List *pTokens,RingState *pRingState ) ;

Parser * simple_parser_new ( List *pTokens,RingState *pRingState ) ;

Parser * simple_parser_delete ( Parser *pParser ) ;

void simple_parser_printtokens ( Parser *pParser ) ;
/* Grammar */

int simple_parser_class ( Parser *pParser ) ;

int simple_parser_stmt ( Parser *pParser ) ;

int simple_parser_step ( Parser *pParser,int *nMark1 ) ;

int simple_parser_paralist ( Parser *pParser ) ;

int simple_parser_expr ( Parser *pParser ) ;

int simple_parser_logicnot ( Parser *pParser ) ;

int simple_parser_equalornot ( Parser *pParser ) ;

int simple_parser_compare ( Parser *pParser ) ;

int simple_parser_bitorxor ( Parser *pParser ) ;

int simple_parser_bitand ( Parser *pParser ) ;

int simple_parser_bitshift ( Parser *pParser ) ;

int simple_parser_arithmetic ( Parser *pParser ) ;

int simple_parser_term ( Parser *pParser ) ;

int simple_parser_range ( Parser *pParser ) ;

int simple_parser_factor ( Parser *pParser,int *nFlag ) ;

int simple_parser_mixer ( Parser *pParser ) ;

int simple_parser_list ( Parser *pParser ) ;

int simple_parser_epslion ( Parser *pParser ) ;

int simple_parser_passepslion ( Parser *pParser ) ;

int simple_parser_namedotname ( Parser *pParser ) ;

int simple_parser_ppmm ( Parser *pParser ) ;

int simple_parser_csexpr ( Parser *pParser ) ;

int simple_parser_csbraceend ( Parser *pParser ) ;

int simple_parser_objattributes ( Parser *pParser ) ;

int simple_parser_bracesandend ( Parser *pParser,int lClass,SCANNER_KEYWORD nKeyword ) ;
/* Check Token */

void simple_parser_loadtoken ( Parser *pParser ) ;

int simple_parser_nexttoken ( Parser *pParser ) ;

int simple_parser_iskeyword ( Parser *pParser,SCANNER_KEYWORD x ) ;

int simple_parser_isoperator ( Parser *pParser,const char *cStr ) ;

int simple_parser_isliteral ( Parser *pParser ) ;

int simple_parser_isidentifier ( Parser *pParser ) ;

int simple_parser_isnumber ( Parser *pParser ) ;

int simple_parser_isendline ( Parser *pParser ) ;

int simple_parser_settoken ( Parser *pParser,int x ) ;

int simple_parser_isanykeyword ( Parser *pParser ) ;

int simple_parser_isoperator2 ( Parser *pParser,SCANNER_OPERATOR nType ) ;
/* Display Errors */

void simple_parser_error ( Parser *pParser,const char *cStr ) ;
/* Generate Code */

void simple_parser_gencall ( Parser *pParser,int nCallMethod ) ;

void simple_parser_gencallbracemethod ( Parser *pParser,const char *cMethod ) ;
/* MACRO */
#define SIMPLE_PARSER_IGNORENEWLINE while(simple_parser_epslion(pParser));
#define SIMPLE_PARSER_PASSNEWLINE while(simple_parser_passepslion(pParser));
#define SIMPLE_PARSER_CURRENTTOKEN pParser->ActiveToken
#define SIMPLE_PARSER_OPERATIONID simple_list_getsize(pParser->GenCode)
#endif
