
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
/* Blocks */

int accept_token_token( Parser *parser, SCANNER_OPERATOR nType ) {
	assert(parser != NULL);
	if ( simple_parser_isoperator2(parser, nType) ) {
            simple_parser_nexttoken(parser);
            parser->nControlStructureBrace++ ;
            return TRUE ;
	}
	return FALSE;
}

int simple_parser_start ( List *pTokens,SimpleState *sState )
{
	Parser *parser  ;
	int nResult,SimpleActiveFile  ;
	parser = simple_parser_new(pTokens,sState);
	#if SIMPLE_PARSERSTART
	/* Parse Tokens */
	simple_parser_nexttoken(parser);
	do {
		nResult = simple_parser_class(parser);
		if ( nResult == 0 ) {
			parser_error(parser,"");
			/* Important check to avoid missing the line number counter */
			if ( simple_parser_isendline(parser) == 0 ) {
				/* Move next trying to avoid the error */
				simple_parser_nexttoken(parser);
			}
		}
	} while (parser->ActiveToken !=parser->TokensCount)  ;
	/* Display Errors Count */
	SimpleActiveFile = simple_list_getsize(parser->sState->files_stack);
	if ( parser->nErrorsCount == 0 ) {
		#if SIMPLE_PARSERFINAL
		printf( "\n%s compiling done, no errors.\n",simple_list_getstring(parser->sState->files_stack,SimpleActiveFile) ) ;
		#endif
		simple_parser_delete(parser);
		return 1 ;
	} else {
		printf( "\nTotal errors count : %d \n",parser->nErrorsCount ) ;
	}
	#endif
	simple_parser_delete(parser);
	return 0 ;
}

Parser * simple_parser_new ( List *pTokens,SimpleState *sState )
{
	Parser *parser  ;
	parser = (Parser *) simple_state_malloc(sState,sizeof(Parser));
	if ( parser == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Simple State */
	parser->sState = sState ;
	parser->Tokens = pTokens ;
	parser->ActiveToken = 0 ;
	parser->TokensCount = simple_list_getsize(parser->Tokens) ;
	parser->nTokenIndex = 0 ;
	parser->nLineNumber = 1 ;
	parser->nErrorLine = 0 ;
	parser->nErrorsCount = 0 ;
	if ( sState->pSimpleGenCode == NULL ) {
		sState->pSimpleGenCode = simple_list_new(0);
		sState->blocks_map = simple_list_new(0);
		sState->classes_map = simple_list_new(0);
		sState->modules_map = simple_list_new(0);
	}
	parser->GenCode = sState->pSimpleGenCode ;
	parser->BlocksMap = sState->blocks_map ;
	parser->ActiveGenCodeList = NULL ;
	parser->nAssignmentFlag = 1 ;
	parser->nClassStart = 0 ;
	parser->ClassesMap = sState->classes_map ;
	parser->ModulessMap = sState->modules_map ;
	parser->nClassMark = 0 ;
	parser->nPrivateFlag = 0 ;
	parser->nBraceFlag = 0 ;
	parser->nInsertFlag = 0 ;
	parser->nInsertCounter = 0 ;
	parser->nNoAssignment = 0 ;
	parser->nBlockCallOnly = 0 ;
	parser->nControlStructureExpr = 0 ;
	parser->nControlStructureBrace = 0 ;
	return parser ;
}

Parser * simple_parser_delete ( Parser *parser )
{
	assert(parser != NULL);
	simple_state_free(parser->sState,parser);
	return NULL ;
}
/* Check Token */

void simple_parser_loadtoken ( Parser *parser )
{
	List *list  ;
	assert(parser != NULL);
	list = simple_list_getlist(parser->Tokens,parser->ActiveToken);
	parser->TokenType = simple_list_getint(list,1) ;
	parser->TokenText = simple_list_getstring(list,2) ;
	parser->nTokenIndex = simple_list_getint(list,3) ;
}

int simple_parser_nexttoken ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->ActiveToken < parser->TokensCount ) {
		parser->ActiveToken++ ;
		simple_parser_loadtoken(parser);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_iskeyword ( Parser *parser,SCANNER_KEYWORD x )
{
	assert(parser != NULL);
	if ( parser->TokenType == SCANNER_TOKEN_KEYWORD ) {
		if ( ((unsigned int) atoi(parser->TokenText)) == ((unsigned int) x) ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_isoperator ( Parser *parser,const char *cStr )
{
	assert(parser != NULL);
	if ( parser->TokenType == SCANNER_TOKEN_OPERATOR ) {
		if ( strcmp( parser->TokenText,cStr) == 0 ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_isliteral ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->TokenType ==SCANNER_TOKEN_LITERAL ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isnumber ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->TokenType ==SCANNER_TOKEN_NUMBER ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isidentifier ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->TokenType ==SCANNER_TOKEN_IDENTIFIER ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isendline ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->TokenType ==SCANNER_TOKEN_ENDLINE ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_settoken ( Parser *parser,int x )
{
	assert(parser != NULL);
	if ( (x >= 1) && (x <= parser->TokensCount) ) {
		parser->ActiveToken = x ;
		simple_parser_loadtoken(parser);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isanykeyword ( Parser *parser )
{
	assert(parser != NULL);
	if ( parser->TokenType == SCANNER_TOKEN_KEYWORD ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isoperator2 ( Parser *parser,SCANNER_OPERATOR nType )
{
	assert(parser != NULL);
	if ( (parser->TokenType == SCANNER_TOKEN_OPERATOR) && ( parser->nTokenIndex == (int) nType ) ) {
		return 1 ;
	}
	return 0 ;
}
/* Display Errors */

void parser_error ( Parser *parser,const char *cStr )
{
	int SimpleActiveFile  ;
	SimpleActiveFile = simple_list_getsize(parser->sState->files_stack);
	if ( parser->nErrorLine != parser->nLineNumber ) {
		parser->nErrorLine = parser->nLineNumber ;
        if ( strcmp(cStr,"") != 0 ) {
			printf("\nLine %d -> %s\n", parser->nLineNumber,cStr);
		} else {
			printf( "\nLine %d -> Syntax error : Unexpected '%s' \n",parser->nLineNumber, parser->TokenText) ;
		}
		printf( "\tin file %s ",file_real_name(simple_list_getstring(parser->sState->files_stack,SimpleActiveFile)) ) ;
		parser->nErrorsCount++ ;
		return ;
	} else if ( strcmp(cStr,"") != 0 ) {
		parser->nErrorsCount++ ;
	}
	if ( strcmp(cStr,"") != 0 ) {
		printf( "\nLine %d -> %s\n",parser->nLineNumber,cStr ) ;
		printf( "\tin file %s",file_real_name(simple_list_getstring(parser->sState->files_stack,SimpleActiveFile)) ) ;
	}
        if (SKIP_ERROR == 0) { exit(1); }
}
