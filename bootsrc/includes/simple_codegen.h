
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


#ifndef simple_codegen_h
#define simple_codegen_h
/*
**  Data 
**  Intermediate Code 
*/
typedef enum IC_OPERATIONS {
	/* General */
	ICO_NEWLINE=0 ,
	ICO_FILENAME ,
	ICO_DISPLAY ,
	ICO_NEWCLASS ,
	ICO_NEWBLOCK ,
	ICO_DUPLICATE ,
	ICO_NEWOBJ ,
	ICO_GIVE ,
	ICO_PRIVATE ,
	ICO_NEWLABEL ,
	/* Control Structure */
	ICO_JUMP ,
	ICO_JUMPZERO ,
	ICO_JUMPONE ,
	ICO_JUMPFOR ,
	ICO_JUMPZERO2 ,
	ICO_JUMPONE2 ,
	/* Variables */
	ICO_LOADADDRESS ,
	ICO_ASSIGNMENT ,
	ICO_LOADSUBADDRESS ,
	ICO_LOADINDEXADDRESS ,
	ICO_LOADAPUSHV ,
	/* Comparsion operators */
	ICO_EQUAL ,
	ICO_LESS ,
	ICO_GREATER ,
	ICO_NOTEQUAL ,
	ICO_LESSEQUAL ,
	ICO_GREATEREQUAL ,
	/* Data */
	ICO_PUSHC ,
	ICO_PUSHN ,
	ICO_PUSHV ,
	ICO_PUSHP ,
	ICO_PUSHPV ,
	ICO_PUSHPLOCAL ,
	/* Arithmetic */
	ICO_SUM ,
	ICO_SUB ,
	ICO_MUL ,
	ICO_DIV ,
	ICO_MOD ,
	ICO_NEG ,
	ICO_INC ,
	ICO_INCP ,
	/* Functions/Methods */
	ICO_LOADBLOCK ,
	ICO_CALL ,
	ICO_RETURN ,
	ICO_RETNULL ,
	ICO_RETFROMEVAL ,
	ICO_RETITEMREF ,
	/* Lists */
	ICO_LISTSTART ,
	ICO_LISTITEM ,
	ICO_LISTEND ,
	/* Logic */
	ICO_AND ,
	ICO_OR ,
	ICO_NOT ,
	/* More */
	ICO_FREESTACK ,
	ICO_BLOCKFLAG ,
	ICO_BLOCKEXE ,
	ICO_ENDBLOCKEXE ,
	ICO_BYE ,
	ICO_EXITMARK ,
	ICO_POPEXITMARK ,
	ICO_EXIT ,
	ICO_INCJUMP ,
	ICO_INCPJUMP ,
	ICO_JUMPVARLENUM ,
	ICO_JUMPVARPLENUM ,
	ICO_TRY ,
	ICO_DONE ,
	ICO_RANGE ,
	ICO_LOADMETHOD ,
	ICO_SETSCOPE ,
	ICO_AFTERCALLMETHOD ,
	ICO_BRACESTART ,
	ICO_BRACEEND ,
	ICO_LOADBLOCKP ,
	ICO_FREELOADASCOPE ,
	/* Loop */
	ICO_LOOP ,
	/* Loop optimization in blocks (local scope) */
	ICO_INCLPJUMP ,
	ICO_JUMPVARLPLENUM ,
	/* Moduless */
	ICO_MODULE ,
	ICO_IMPORT ,
	/* Property */
	ICO_SETPROPERTY ,
	ICO_NOOP ,
	ICO_AFTERCALLMETHOD2 ,
	/* Other */
	ICO_SETREFERENCE ,
	ICO_KILLREFERENCE ,
	ICO_ASSIGNMENTPOINTER ,
	ICO_BEFOREEQUAL ,
	ICO_PLUSPLUS ,
	ICO_MINUSMINUS ,
	/* Bitwise Operators */
	ICO_BITAND ,
	ICO_BITOR ,
	ICO_BITNOT ,
	ICO_BITXOR ,
	ICO_BITSHL ,
	ICO_BITSHR ,
	/* For Loop Step */
	ICO_STEPNUMBER ,
	ICO_POPSTEP ,
	ICO_LOADAFIRST ,
	ICO_INCPJUMPSTEP1 ,
	ICO_JUMPVARPLENUMSTEP1 ,
	/* Anonymous Functions */
	ICO_ANONYMOUS ,
	/* Class Init */
	ICO_CALLCLASSINIT ,
	/* Custom Global Scope */
	ICO_NEWGLOBALSCOPE ,
	ICO_ENDGLOBALSCOPE ,
	ICO_SETGLOBALSCOPE 
} IC_OPERATIONS ;
/*
**  Functions 
**  Generate Intermediate Code 
*/

void simple_parser_icg_newoperation ( Parser *parser , IC_OPERATIONS opcode ) ;

void simple_parser_icg_newoperand ( Parser *parser , const char *cStr ) ;

void simple_parser_icg_newoperandint ( Parser *parser , int nValue ) ;

void simple_parser_icg_newoperanddouble ( Parser *parser , double nValue ) ;

void simple_parser_icg_newoperandpointer ( Parser *parser , void *pValue ) ;

List * simple_parser_icg_getactiveoperation ( Parser *parser ) ;

void simple_parser_icg_addoperand ( Parser *parser ,List *pList , const char *cStr ) ;

void simple_parser_icg_addoperandint ( Parser *parser ,List *pList , int nValue ) ;

void simple_parser_icg_addoperandpointer ( Parser *parser ,List *pList , void *pValue ) ;

void simple_parser_icg_showoutput ( List *pListGenCode,int nStatus ) ;

Items * simple_parser_icg_getoperationpos ( Parser *parser ) ;

void simple_parser_icg_deletelastoperation ( Parser *parser ) ;

void simple_parser_icg_duplicate ( Parser *parser,int nStart,int nEnd ) ;

int simple_parser_icg_newlabel2 ( Parser *parser ) ;

void simple_parser_icg_insertoperation ( Parser *parser , int nPos , IC_OPERATIONS opcode ) ;
/* Macro */
#define simple_parser_icg_newlabel(x) ( simple_list_getsize(x->GenCode) + 1 )
#define simple_parser_icg_getlastoperation(parser) simple_list_getint(parser->ActiveGenCodeList,1)
#define simple_parser_icg_setlastoperation(parser,x) simple_list_setint_gc(parser->pSimpleState,parser->ActiveGenCodeList,1,x)
#define simple_parser_icg_instructionscount(parser) simple_list_getsize(parser->GenCode)
#define simple_parser_icg_getoperationlist(parser,x) simple_list_getlist(parser->GenCode,x)
#define SIMPLE_PARSER_ICG_GOTOLASTOP parser->ActiveGenCodeList = simple_list_getlist(parser->GenCode,simple_list_getsize(parser->GenCode))
extern const char *SIMPLE_IC_OP[] ;
#endif
