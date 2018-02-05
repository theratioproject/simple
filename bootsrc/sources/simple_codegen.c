
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
/* Operations Text (Array) */
const char * SIMPLE_IC_OP[] = {"NewLine","FileName","Print","Class","Func","Dup","New","Give","Private","NewLabel", 

"Jump","JumpZ","Jump1","JumpFOR","JZ2","J12","LoadA","Assignment","LoadSA","LoadIA","LoadAPushV","==","<",">","!=","<=",">=", 

"PushC","PushN","PushV","PushP","PushPV","PushPLocal", "SUM","SUB","MUL","DIV","MOD","Negative","Inc","IncP", 

"LoadFunc","Call", "Return","ReturnNull","RetFromEval","RetItemRef","ListStart","ListItem","ListEnd","And","Or","Not","FreeStack", 

"BlockFlag","FuncExE","EndFuncExe","Bye","ExitMark","POPExitMark","Exit","IncJump","IncPJump", 

"JumpVarLENum","JumpVarPLENum","Try","Done","Range","LoadMethod","SetScope","AfterCallMethod", 

"BraceStart","BraceEnd","LoadFuncP","FreeLoadAScope","Loop","IncLPJump","JumpVarLPLENum","Modules","Import", 

"SetProperty","NoOperation","AfterCallMethod2","SetReference","KillReference","AssignmentPointer","BeforeEqual","++","--", 

"BITAND","BITOR","BITNOT","BITXOR","BITSHL","BITSHR","StepNumber","POPStep","LoadAFirst", 

"INCPJUMPSTEP1","JUMPVARPLENUMSTEP1","ANONYMOUS","CallClassInit","NewGlobalScope","EndGlobalScope","SetGlobalScope"} ;
/*
**  Functions 
**  Generate Intermediate Code 
*/

void simple_parser_icg_newoperation ( Parser *parser , IC_OPERATIONS opcode )
{
	assert(parser != NULL);
	if ( parser->nInsertFlag == 1 ) {
		simple_parser_icg_insertoperation(parser,parser->nInsertCounter,opcode);
		parser->nInsertCounter++ ;
		return ;
	}
	parser->ActiveGenCodeList = simple_list_newlist_gc(parser->pSimpleState,parser->GenCode);
	simple_list_addint_gc(parser->pSimpleState,parser->ActiveGenCodeList,opcode);
	#if SIMPLE_SHOWIC
	printf( "\n %6d [ %s ] ",simple_list_getsize(parser->GenCode) , SIMPLE_IC_OP[opcode] ) ;
	#endif
}

void simple_parser_icg_insertoperation ( Parser *parser , int nPos , IC_OPERATIONS opcode )
{
	assert(parser != NULL);
	parser->ActiveGenCodeList = simple_list_insertlist(parser->GenCode,nPos);
	simple_list_addint_gc(parser->pSimpleState,parser->ActiveGenCodeList,opcode);
	#if SIMPLE_SHOWIC
	printf( "\n %6d [ %s ] ",nPos, SIMPLE_IC_OP[opcode] ) ;
	#endif
}

void simple_parser_icg_newoperand ( Parser *parser , const char *cStr )
{
	assert(parser != NULL);
	assert(parser->ActiveGenCodeList);
	simple_list_addstsimple_gc(parser->pSimpleState,parser->ActiveGenCodeList,cStr);
	#if SIMPLE_SHOWIC
	printf( " Operand : %s ",cStr ) ;
	#endif
}

void simple_parser_icg_newoperandint ( Parser *parser , int nValue )
{
	assert(parser != NULL);
	assert(parser->ActiveGenCodeList);
	simple_list_addint_gc(parser->pSimpleState,parser->ActiveGenCodeList,nValue);
	#if SIMPLE_SHOWIC
	printf( " Operand : %d ",nValue ) ;
	#endif
}

void simple_parser_icg_newoperanddouble ( Parser *parser , double nValue )
{
	assert(parser != NULL);
	assert(parser->ActiveGenCodeList);
	simple_list_adddouble_gc(parser->pSimpleState,parser->ActiveGenCodeList,nValue);
	#if SIMPLE_SHOWIC
	printf( " Operand : %.5f ",nValue ) ;
	#endif
}

void simple_parser_icg_newoperandpointer ( Parser *parser , void *pValue )
{
	assert(parser != NULL);
	assert(parser->ActiveGenCodeList);
	simple_list_addpointer_gc(parser->pSimpleState,parser->ActiveGenCodeList,pValue);
	#if SIMPLE_SHOWIC
	printf( " Operand : %p ",pValue ) ;
	#endif
}

List * simple_parser_icg_getactiveoperation ( Parser *parser )
{
	assert(parser != NULL);
	assert(parser->ActiveGenCodeList);
	return parser->ActiveGenCodeList ;
}

Items * simple_parser_icg_getoperationpos ( Parser *parser )
{
	assert(parser != NULL);
	assert(parser->GenCode);
	return parser->GenCode->pLast ;
}

void simple_parser_icg_addoperand ( Parser *parser ,List *pList , const char *cStr )
{
	assert(pList != NULL);
	simple_list_addstsimple_gc(parser->pSimpleState,pList,cStr);
}

void simple_parser_icg_addoperandint ( Parser *parser ,List *pList , int nValue )
{
	assert(pList != NULL);
	simple_list_addint_gc(parser->pSimpleState,pList,nValue);
}

void simple_parser_icg_addoperandpointer ( Parser *parser ,List *pList , void *pValue )
{
	assert(pList != NULL);
	simple_list_addpointer_gc(parser->pSimpleState,pList,pValue);
}

void simple_parser_icg_showoutput ( List *pListGenCode,int nStatus )
{
	int x,y,nCount,nCount2  ;
	List *pList  ;
	assert(pListGenCode != NULL);
	/* Header */
	printf( "\n\n" ) ;
	print_line();
	if ( nStatus == 1 ) {
		puts("Byte Code - Before Execution by the VM");
	}
	else {
		puts("Byte Code - After Execution by the VM");
	}
	print_line();
	nCount = simple_list_getsize(pListGenCode);
	if ( nCount > 0 ) {
		printf( "\n %6s  %10s  %10s\n", "PC","OPCode","Data" ) ;
		for ( x = 1 ; x <= nCount ; x++ ) {
			pList = simple_list_getlist(pListGenCode,x);
			nCount2 = simple_list_getsize(pList);
			printf( "\n %6d  %10s  ", x , SIMPLE_IC_OP[simple_list_getint(pList,1)] ) ;
			if ( nCount2 > 1 ) {
				for ( y = 2 ; y <= nCount2 ; y++ ) {
					if ( simple_list_isstring(pList,y) ) {
						printf( " %5s ",simple_list_getstring(pList,y) ) ;
					}
					else if ( simple_list_isnumber(pList,y) ) {
						if ( simple_list_isdouble(pList,y) ) {
							printf( " %f",simple_list_getdouble(pList,y) ) ;
						} else {
							printf( " %5d ",simple_list_getint(pList,y) ) ;
						}
					} else {
						printf( " %5p ",simple_list_getpointer(pList,y) ) ;
					}
				}
			}
		}
		printf( "\n" ) ;
	}
	/* End */
	puts("");
	print_line();
	puts("");
}

void simple_parser_icg_deletelastoperation ( Parser *parser )
{
	if ( simple_list_getsize(parser->GenCode) > 0 ) {
		simple_list_deleteitem(parser->GenCode,simple_list_getsize(parser->GenCode));
		parser->ActiveGenCodeList = simple_list_getlist(parser->GenCode,simple_list_getsize(parser->GenCode));
	}
}

void simple_parser_icg_duplicate ( Parser *parser,int nStart,int nEnd )
{
	List *pList,*pList2  ;
	int x  ;
	#if SIMPLE_SHOWIC
	int y,nCount2  ;
	#endif
	assert(parser != NULL);
	if ( (nStart <= nEnd) && ( nEnd <= simple_parser_icg_instructionscount(parser) ) ) {
		for ( x = nStart ; x <= nEnd ; x++ ) {
			pList = simple_list_newlist_gc(parser->pSimpleState,parser->GenCode);
			pList2 = simple_list_getlist(parser->GenCode,x);
			simple_list_copy(pList,pList2);
			#if SIMPLE_SHOWIC
			nCount2 = simple_list_getsize(pList);
			printf( "\n %6d [ %s ] ", simple_list_getsize(parser->GenCode) , SIMPLE_IC_OP[simple_list_getint(pList,1)] ) ;
			if ( nCount2 > 1 ) {
				for ( y = 2 ; y <= nCount2 ; y++ ) {
					if ( simple_list_isstring(pList,y) ) {
						printf( " Operand : %s ",simple_list_getstring(pList,y) ) ;
					}
					else if ( simple_list_isnumber(pList,y) ) {
						if ( simple_list_isdouble(pList,y) ) {
							printf( " Operand : %f ",simple_list_getdouble(pList,y) ) ;
						} else {
							printf( " Operand : %5d ",simple_list_getint(pList,y) ) ;
						}
					} else {
						printf( " Operand : %5p ",simple_list_getpointer(pList,y) ) ;
					}
				}
			}
			#endif
		}
	}
}

int simple_parser_icg_newlabel2 ( Parser *parser )
{
	assert(parser != NULL);
	simple_parser_icg_newoperation(parser,ICO_NEWLABEL);
	return simple_list_getsize(parser->GenCode) ;
}
