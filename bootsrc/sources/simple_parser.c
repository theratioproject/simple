
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
/* Functions */

int simple_parser_start ( List *pTokens,RingState *pRingState )
{
	Parser *pParser  ;
	int nResult,RingActiveFile  ;
	pParser = simple_parser_new(pTokens,pRingState);
	#if SIMPLE_PARSERSTART
	/* Parse Tokens */
	simple_parser_nexttoken(pParser);
	do {
		nResult = simple_parser_class(pParser);
		if ( nResult == 0 ) {
			simple_parser_error(pParser,"");
			/* Important check to avoid missing the line number counter */
			if ( simple_parser_isendline(pParser) == 0 ) {
				/* Move next trying to avoid the error */
				simple_parser_nexttoken(pParser);
			}
		}
	} while (pParser->ActiveToken !=pParser->TokensCount)  ;
	/* Display Errors Count */
	RingActiveFile = simple_list_getsize(pParser->pRingState->pRingFilesStack);
	if ( pParser->nErrorsCount == 0 ) {
		#if SIMPLE_PARSERFINAL
		printf( "\n%s compiling done, no errors.\n",simple_list_getstring(pParser->pRingState->pRingFilesStack,RingActiveFile) ) ;
		#endif
		simple_parser_delete(pParser);
		return 1 ;
	} else {
		printf( "\n%s errors count : %d \n",simple_list_getstring(pParser->pRingState->pRingFilesStack,RingActiveFile),pParser->nErrorsCount ) ;
	}
	#endif
	simple_parser_delete(pParser);
	return 0 ;
}

Parser * simple_parser_new ( List *pTokens,RingState *pRingState )
{
	Parser *pParser  ;
	pParser = (Parser *) simple_state_malloc(pRingState,sizeof(Parser));
	if ( pParser == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Ring State */
	pParser->pRingState = pRingState ;
	pParser->Tokens = pTokens ;
	pParser->ActiveToken = 0 ;
	pParser->TokensCount = simple_list_getsize(pParser->Tokens) ;
	pParser->nTokenIndex = 0 ;
	pParser->nLineNumber = 1 ;
	pParser->nErrorLine = 0 ;
	pParser->nErrorsCount = 0 ;
	if ( pRingState->pRingGenCode == NULL ) {
		pRingState->pRingGenCode = simple_list_new(0);
		pRingState->pRingFunctionsMap = simple_list_new(0);
		pRingState->pRingClassesMap = simple_list_new(0);
		pRingState->pRingPackagesMap = simple_list_new(0);
	}
	pParser->GenCode = pRingState->pRingGenCode ;
	pParser->FunctionsMap = pRingState->pRingFunctionsMap ;
	pParser->ActiveGenCodeList = NULL ;
	pParser->nAssignmentFlag = 1 ;
	pParser->nClassStart = 0 ;
	pParser->ClassesMap = pRingState->pRingClassesMap ;
	pParser->PackagesMap = pRingState->pRingPackagesMap ;
	pParser->nClassMark = 0 ;
	pParser->nPrivateFlag = 0 ;
	pParser->nBraceFlag = 0 ;
	pParser->nInsertFlag = 0 ;
	pParser->nInsertCounter = 0 ;
	pParser->nNoAssignment = 0 ;
	pParser->nFuncCallOnly = 0 ;
	pParser->nControlStructureExpr = 0 ;
	pParser->nControlStructureBrace = 0 ;
	return pParser ;
}

Parser * simple_parser_delete ( Parser *pParser )
{
	assert(pParser != NULL);
	simple_state_free(pParser->pRingState,pParser);
	return NULL ;
}
/* Check Token */

void simple_parser_loadtoken ( Parser *pParser )
{
	List *pList  ;
	assert(pParser != NULL);
	pList = simple_list_getlist(pParser->Tokens,pParser->ActiveToken);
	pParser->TokenType = simple_list_getint(pList,1) ;
	pParser->TokenText = simple_list_getstring(pList,2) ;
	pParser->nTokenIndex = simple_list_getint(pList,3) ;
}

int simple_parser_nexttoken ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->ActiveToken < pParser->TokensCount ) {
		pParser->ActiveToken++ ;
		simple_parser_loadtoken(pParser);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_iskeyword ( Parser *pParser,SCANNER_KEYWORD x )
{
	assert(pParser != NULL);
	if ( pParser->TokenType == SCANNER_TOKEN_KEYWORD ) {
		if ( ((unsigned int) atoi(pParser->TokenText)) == ((unsigned int) x) ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_isoperator ( Parser *pParser,const char *cStr )
{
	assert(pParser != NULL);
	if ( pParser->TokenType == SCANNER_TOKEN_OPERATOR ) {
		if ( strcmp( pParser->TokenText,cStr) == 0 ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_isliteral ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->TokenType ==SCANNER_TOKEN_LITERAL ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isnumber ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->TokenType ==SCANNER_TOKEN_NUMBER ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isidentifier ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->TokenType ==SCANNER_TOKEN_IDENTIFIER ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isendline ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->TokenType ==SCANNER_TOKEN_ENDLINE ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_settoken ( Parser *pParser,int x )
{
	assert(pParser != NULL);
	if ( (x >= 1) && (x <= pParser->TokensCount) ) {
		pParser->ActiveToken = x ;
		simple_parser_loadtoken(pParser);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isanykeyword ( Parser *pParser )
{
	assert(pParser != NULL);
	if ( pParser->TokenType == SCANNER_TOKEN_KEYWORD ) {
		return 1 ;
	}
	return 0 ;
}

int simple_parser_isoperator2 ( Parser *pParser,SCANNER_OPERATOR nType )
{
	assert(pParser != NULL);
	if ( (pParser->TokenType == SCANNER_TOKEN_OPERATOR) && ( pParser->nTokenIndex == (int) nType ) ) {
		return 1 ;
	}
	return 0 ;
}
/* Display Errors */

void simple_parser_error ( Parser *pParser,const char *cStr )
{
	int RingActiveFile  ;
	simple_state_cgiheader(pParser->pRingState);
	RingActiveFile = simple_list_getsize(pParser->pRingState->pRingFilesStack);
	if ( pParser->nErrorLine != pParser->nLineNumber ) {
		pParser->nErrorLine = pParser->nLineNumber ;
		printf( "\n%s Line (%d) ",simple_list_getstring(pParser->pRingState->pRingFilesStack,RingActiveFile),pParser->nLineNumber ) ;
		pParser->nErrorsCount++ ;
		if ( strcmp(cStr,"") != 0 ) {
			printf( "%s",cStr ) ;
		} else {
			printf( "Syntax error" ) ;
		}
		return ;
	} else if ( strcmp(cStr,"") != 0 ) {
		pParser->nErrorsCount++ ;
	}
	if ( strcmp(cStr,"") != 0 ) {
		printf( "\n%s Line (%d) ",simple_list_getstring(pParser->pRingState->pRingFilesStack,RingActiveFile),pParser->nLineNumber ) ;
		printf( "%s",cStr ) ;
	}
}
