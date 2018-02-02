
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
/* Keywords */
const char * SIMPLE_KEYWORDS[] = {"IF","TO","OR","AND","NOT","FOR","NEW","FUNC", 

"FROM","NEXT","LOAD","ELSE","display","WHILE","OK","CLASS","RETURN","BUT", 

"END","read","BYE","EXIT","TRY","CATCH","DONE","SWITCH","ON","OTHER","OFF", 

"IN","LOOP","PACKAGE","IMPORT","PRIVATE","STEP","DO","AGAIN","CALL","ELSEIF", 

"CASE","DEF","ENDFUNC","ENDCLASS","ENDPACKAGE", 

"CHANGERINGKEYWORD","CHANGERINGOPERATOR","LOADSYNTAX"} ;
/* Functions */

Scanner * simple_scanner_new ( RingState *pRingState )
{
	Scanner *pScanner  ;
	pScanner = (Scanner *) simple_state_malloc(pRingState,sizeof(Scanner));
	if ( pScanner == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pScanner->pRingState = pRingState ;
	pScanner->state = SCANNER_STATE_GENERAL ;
	pScanner->ActiveToken = simple_stsimple_new_gc(pRingState,"");
	pScanner->Tokens = simple_list_new_gc(pRingState,0);
	simple_scanner_keywords(pScanner);
	simple_scanner_operators(pScanner);
	pScanner->LinesCount = 1 ;
	pScanner->FloatMark = 0 ;
	pScanner->cMLComment = 0 ;
	pScanner->nTokenIndex = 0 ;
	return pScanner ;
}

Scanner * simple_scanner_delete ( Scanner *pScanner )
{
	assert(pScanner != NULL);
	pScanner->Keywords = simple_list_delete_gc(pScanner->pRingState,pScanner->Keywords);
	pScanner->Operators = simple_list_delete_gc(pScanner->pRingState,pScanner->Operators);
	pScanner->Tokens = simple_list_delete_gc(pScanner->pRingState,pScanner->Tokens);
	pScanner->ActiveToken = simple_stsimple_delete_gc(pScanner->pRingState,pScanner->ActiveToken);
	simple_state_free(pScanner->pRingState,pScanner);
	return NULL ;
}

int simple_scanner_readfile ( RingState *pRingState,char *cFileName )
{
	SIMPLE_FILE fp  ;
	/* Must be signed char to work fine on Android, because it uses -1 as NULL instead of Zero */
	signed char c  ;
	Scanner *pScanner  ;
	VM *pVM  ;
	int nCont,nRunVM,nFreeFilesList = 0 ;
	char cStartup[30]  ;
	int x,nSize  ;
	char cFileName2[200]  ;
	/* Check file */
	if ( pRingState->pRingFilesList == NULL ) {
		pRingState->pRingFilesList = simple_list_new_gc(pRingState,0);
		pRingState->pRingFilesStack = simple_list_new_gc(pRingState,0);
		simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesList,cFileName);
		simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesStack,cFileName);
		nFreeFilesList = 1 ;
	} else {
		if ( simple_list_findstring(pRingState->pRingFilesList,cFileName,0) == 0 ) {
			simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesList,cFileName);
			simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesStack,cFileName);
		} else {
			if ( pRingState->nWarning ) {
				printf( "\nWarning, Duplication in FileName, %s \n",cFileName ) ;
			}
			return 1 ;
		}
	}
	/* Switch To File Folder */
	strcpy(cFileName2,cFileName);
	fp = SIMPLE_OPENFILE(cFileName , "r");
	/* Avoid switching if it's the first file */
	if ( nFreeFilesList == 0 ) {
		simple_switchtofilefolder(cFileName2);
	}
	/* Read File */
	if ( fp==NULL ) {
		printf( "\nCan't open file %s \n",cFileName ) ;
		return 0 ;
	}
	SIMPLE_READCHAR(fp,c,nSize);
	pScanner = simple_scanner_new(pRingState);
	/* Check Startup file */
	if ( simple_fexists("startup.sim") && pScanner->pRingState->lStartup == 0 ) {
		pScanner->pRingState->lStartup = 1 ;
		strcpy(cStartup,"Load 'startup.sim'");
		/* Load "startup.sim" */
		for ( x = 0 ; x < 19 ; x++ ) {
			simple_scanner_readchar(pScanner,cStartup[x]);
		}
		/*
		**  Add new line 
		**  We add this here instead of using \n in load 'startup.sim' 
		**  To avoid increasing the line number of the code 
		**  so the first line in the source code file still the first line (not second line) 
		*/
		simple_stsimple_setfromint_gc(pRingState,pScanner->ActiveToken,0);
		simple_scanner_addtoken(pScanner,SCANNER_TOKEN_ENDLINE);
	}
	nSize = 1 ;
	while ( (c != EOF) && (nSize != 0) ) {
		simple_scanner_readchar(pScanner,c);
		SIMPLE_READCHAR(fp,c,nSize);
	}
	nCont = simple_scanner_checklasttoken(pScanner);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(pScanner);
	SIMPLE_CLOSEFILE(fp);
	/* Print Tokens */
	if ( pRingState->nPrintTokens ) {
		display_tokens(pScanner);
	}
	/* Call Parser */
	if ( nCont == 1 ) {
		#if SIMPLE_PARSERTRACE
		if ( pScanner->pRingState->nPrintRules ) {
			printf( "\n" ) ;
			print_line();
			puts("Grammar Rules Used by The Parser ");
			print_line();
			printf( "\nRule : Program --> {Statement}\n\nLine 1\n" ) ;
		}
		#endif
		nRunVM = simple_parser_start(pScanner->Tokens,pRingState);
		#if SIMPLE_PARSERTRACE
		if ( pScanner->pRingState->nPrintRules ) {
			printf( "\n" ) ;
			print_line();
			printf( "\n" ) ;
		}
		#endif
	} else {
		simple_list_deleteitem_gc(pRingState,pRingState->pRingFilesStack,simple_list_getsize(pRingState->pRingFilesStack));
		simple_scanner_delete(pScanner);
		return 0 ;
	}
	simple_scanner_delete(pScanner);
	/* Files List */
	simple_list_deleteitem_gc(pRingState,pRingState->pRingFilesStack,simple_list_getsize(pRingState->pRingFilesStack));
	if ( nFreeFilesList ) {
		/* Generate the Object File */
		if ( pRingState->nGenObj ) {
			simple_objfile_writefile(pRingState);
		}
		/* Run the Program */
		#if SIMPLE_RUNVM
		if ( nRunVM == 1 ) {
			/* Add return to the end of the program */
			simple_scanner_addreturn(pRingState);
			if ( pRingState->nPrintIC ) {
				simple_parser_icg_showoutput(pRingState->pRingGenCode,1);
			}
			if ( ! pRingState->nRun ) {
				return 1 ;
			}
			pVM = simple_vm_new(pRingState);
			simple_vm_start(pRingState,pVM);
			if ( ! pRingState->nDontDeleteTheVM ) {
				simple_vm_delete(pVM);
			}
		}
		#endif
		/* Display Generated Code */
		if ( pRingState->nPrintICFinal ) {
			simple_parser_icg_showoutput(pRingState->pRingGenCode,2);
		}
	}
	return nRunVM ;
}

void simple_scanner_readchar ( Scanner *pScanner,char c )
{
	char cStr[2]  ;
	List *pList  ;
	String *pString  ;
	int nTokenIndex  ;
	assert(pScanner != NULL);
	cStr[0] = c ;
	cStr[1] = '\0' ;
	#if SIMPLE_DEBUG
	printf("%c",c);
	printf( "\n State : %d \n  \n",pScanner->state ) ;
	#endif
	switch ( pScanner->state ) {
		case SCANNER_STATE_GENERAL :
			/* Check Unicode File */
			if ( simple_list_getsize(pScanner->Tokens) == 0 ) {
				/* UTF8 */
				if ( strcmp(simple_stsimple_get(pScanner->ActiveToken),"\xEF\xBB\xBF") == 0 ) {
					simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
					/* Don't use reading so the new character can be scanned */
				}
			}
			/* Check Space/Tab/New Line */
			if ( c != ' ' && c != '\n' && c != '\t' && c != '\"' && c != '\'' && c != '\r' && c != '`' ) {
				if ( simple_scanner_isoperator(pScanner,cStr) ) {
					nTokenIndex = pScanner->nTokenIndex ;
					simple_scanner_checktoken(pScanner);
					simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
					#if SIMPLE_SCANNEROUTPUT
					printf( "\nTOKEN (Operator) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
					#endif
					/* Check Multiline Comment */
					if ( (strcmp(cStr,"*") == 0) && (simple_scanner_lasttokentype(pScanner) ==SCANNER_TOKEN_OPERATOR) ) {
						pList = simple_list_getlist(pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
						if ( strcmp(simple_list_getstring(pList,2),"/") == 0 ) {
							simple_list_deleteitem_gc(pScanner->pRingState,pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
							pScanner->state = SCANNER_STATE_MLCOMMENT ;
							#if SIMPLE_SCANNEROUTPUT
							printf( "\nMultiline comments start, ignore /* \n" ) ;
							#endif
							return ;
						}
					}
					/* Check comment using // */
					if ( strcmp(cStr,"/") == 0 ) {
						if ( simple_scanner_lasttokentype(pScanner) ==SCANNER_TOKEN_OPERATOR ) {
							if ( strcmp("/",simple_scanner_lasttokenvalue(pScanner)) ==  0 ) {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								pScanner->state = SCANNER_STATE_COMMENT ;
								return ;
							}
						}
					}
					/* Check << | >> operators */
					if ( ( strcmp(cStr,"<") == 0 ) | ( strcmp(cStr,">") == 0 ) ) {
						if ( strcmp(cStr,simple_scanner_lasttokenvalue(pScanner)) ==  0 ) {
							if ( strcmp(cStr,"<") == 0 ) {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"<<");
							} else {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,">>");
							}
							#if SIMPLE_SCANNEROUTPUT
							printf( "\nTOKEN (Operator) = %s , merge previous two operators in one \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
							#endif
							nTokenIndex += 100 ;
						}
					}
					/* Check += -= *= /= %= &= |= ^= <<= >>= */
					else if ( strcmp(cStr,"=") == 0 ) {
						nTokenIndex += 100 ;
						if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"+") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"+=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"-") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"-=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"*") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"*=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"/") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"/=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"%") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"%=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"&") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"&=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"|") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"|=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"^") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set(pScanner->ActiveToken,"^=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"<<") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"<<=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(pScanner),">>") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,">>=");
						}
						else {
							nTokenIndex -= 100 ;
						}
					}
					/* Check ++ and -- */
					else if ( strcmp(cStr,"+") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"+") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"++");
							nTokenIndex += 100 ;
						}
					}
					else if ( strcmp(cStr,"-") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"-") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"--");
							nTokenIndex += 100 ;
						}
					}
					/* Check && and || */
					else if ( strcmp(cStr,"&") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"&") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"&&");
							nTokenIndex += 100 ;
						}
					}
					else if ( strcmp(cStr,"|") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(pScanner),"|") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"||");
							nTokenIndex += 100 ;
						}
					}
					pScanner->nTokenIndex = nTokenIndex ;
					simple_scanner_addtoken(pScanner,SCANNER_TOKEN_OPERATOR);
				} else {
					simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
					#if SIMPLE_DEBUG
					printf( "\nActive Token = %s",simple_stsimple_get(pScanner->ActiveToken) ) ;
					#endif
				}
			} else {
				if ( simple_scanner_isoperator(pScanner,simple_stsimple_get(pScanner->ActiveToken)) ) {
					simple_scanner_addtoken(pScanner,SCANNER_TOKEN_OPERATOR);
				}
				else {
					simple_scanner_checktoken(pScanner);
				}
			}
			/* Switch State */
			if ( c == '"' ) {
				pScanner->state = SCANNER_STATE_LITERAL ;
				pScanner->cLiteral = '"' ;
				pScanner->nLiteralLine = pScanner->LinesCount ;
			}
			else if ( c == '\'' ) {
				pScanner->state = SCANNER_STATE_LITERAL ;
				pScanner->cLiteral = '\'' ;
				pScanner->nLiteralLine = pScanner->LinesCount ;
			}
			else if ( c == '`' ) {
				pScanner->state = SCANNER_STATE_LITERAL ;
				pScanner->cLiteral = '`' ;
				pScanner->nLiteralLine = pScanner->LinesCount ;
			}
			else if ( c == '#' ) {
				pScanner->state = SCANNER_STATE_COMMENT ;
			}
			break ;
		case SCANNER_STATE_LITERAL :
			/* Switch State */
			if ( c == pScanner->cLiteral ) {
				pScanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Literal) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(pScanner,SCANNER_TOKEN_LITERAL);
			} else {
				simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_COMMENT :
			/* Switch State */
			if ( c == '\n' ) {
				pScanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Not TOKEN (Comment) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			} else {
				simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_MLCOMMENT :
			/* Check Multiline Comment */
			switch ( pScanner->cMLComment ) {
				case 0 :
					if ( strcmp(cStr,"*") == 0 ) {
						pScanner->cMLComment = 1 ;
						return ;
					}
					break ;
				case 1 :
					if ( strcmp(cStr,"/") == 0 ) {
						pScanner->state = SCANNER_STATE_GENERAL ;
						#if SIMPLE_SCANNEROUTPUT
						printf( "\nMultiline comments end \n" ) ;
						#endif
						/* The next step is important to avoid storing * as identifier! */
						simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
					}
					pScanner->cMLComment = 0 ;
					return ;
			}
			break ;
		case SCANNER_STATE_CHANGEKEYWORD :
			/* Switch State */
			if ( c == '\n' ) {
				pScanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Change Keyword = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_changekeyword(pScanner);
				simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			} else {
				simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_CHANGEOPERATOR :
			/* Switch State */
			if ( c == '\n' ) {
				pScanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Change operator = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_changeoperator(pScanner);
				simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			} else {
				simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_LOADSYNTAX :
			/* Switch State */
			if ( c == '\n' ) {
				pScanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Load Syntax = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_loadsyntax(pScanner);
				simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			} else {
				simple_stsimple_add_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			}
			break ;
	}
	if ( c == '\n' ) {
		pScanner->LinesCount++ ;
		#if SIMPLE_DEBUG
		printf( "Line Number : %d  \n",pScanner->LinesCount ) ;
		#endif
	}
	if ( ( c == ';' || c == '\n' ) && ( pScanner->state == SCANNER_STATE_GENERAL ) ) {
		if ( (simple_scanner_lasttokentype(pScanner) != SCANNER_TOKEN_ENDLINE ) ) {
			simple_stsimple_setfromint_gc(pScanner->pRingState,pScanner->ActiveToken,pScanner->LinesCount);
			simple_scanner_addtoken(pScanner,SCANNER_TOKEN_ENDLINE);
			#if SIMPLE_SCANNEROUTPUT
			printf( "\nTOKEN (ENDLINE)  \n" ) ;
			#endif
		} else {
			pList = simple_list_getlist(pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
			pString = simple_stsimple_new_gc(pScanner->pRingState,"");
			simple_stsimple_setfromint_gc(pScanner->pRingState,pString,pScanner->LinesCount);
			simple_list_setstsimple_gc(pScanner->pRingState,pList,2,simple_stsimple_get(pString));
			simple_stsimple_delete_gc(pScanner->pRingState,pString);
		}
	}
}

void simple_scanner_keywords ( Scanner *pScanner )
{
	assert(pScanner != NULL);
	pScanner->Keywords = simple_list_new_gc(pScanner->pRingState,0);
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"if");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"to");
	/* Logic */
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"or");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"and");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"not");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"for");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"new");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"func");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"from");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"next");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"load");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"else");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"display");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"while");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"ok");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"class");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"return");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"but");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"end");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"read");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"bye");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"exit");
	/* Try-Catch-Done */
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"try");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"catch");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"done");
	/* Switch */
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"switch");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"on");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"other");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"off");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"in");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"loop");
	/* Packages */
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"package");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"import");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"private");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"step");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"do");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"again");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"call");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"elseif");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"case");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"def");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"endfunc");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"endclass");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"endpackage");
	/*
	**  The next keywords are sensitive to the order and keywords count 
	**  if you will add new keywords revise constants and simple_scanner_checktoken() 
	*/
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"changeringkeyword");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"changeringoperator");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Keywords,"loadsyntax");
	simple_list_genhashtable_gc(pScanner->pRingState,pScanner->Keywords);
}

void simple_scanner_addtoken ( Scanner *pScanner,int type )
{
	List *pList  ;
	assert(pScanner != NULL);
	pList = simple_list_newlist_gc(pScanner->pRingState,pScanner->Tokens);
	/* Add Token Type */
	simple_list_addint_gc(pScanner->pRingState,pList,type);
	/* Add Token Text */
	simple_list_addstsimple_gc(pScanner->pRingState,pList,simple_stsimple_get(pScanner->ActiveToken));
	/* Add Token Index */
	simple_list_addint_gc(pScanner->pRingState,pList,pScanner->nTokenIndex);
	pScanner->nTokenIndex = 0 ;
	simple_scanner_floatmark(pScanner,type);
	simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
}

void simple_scanner_checktoken ( Scanner *pScanner )
{
	int nResult  ;
	char cStr[5]  ;
	/* This function determine if the TOKEN is a Keyword or Identifier or Number */
	assert(pScanner != NULL);
	/* Not Case Sensitive */
	simple_stsimple_tolower(pScanner->ActiveToken);
	nResult = simple_hashtable_findnumber(simple_list_gethashtable(pScanner->Keywords),simple_stsimple_get(pScanner->ActiveToken));
	if ( nResult > 0 ) {
		#if SIMPLE_SCANNEROUTPUT
		printf( "\nTOKEN (Keyword) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
		#endif
		if ( nResult < SIMPLE_SCANNER_CHANGERINGKEYWORD ) {
			sprintf( cStr , "%d" , nResult ) ;
			simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,cStr);
			simple_scanner_addtoken(pScanner,SCANNER_TOKEN_KEYWORD);
		}
		else if ( nResult == SIMPLE_SCANNER_CHANGERINGOPERATOR ) {
			simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			pScanner->state = SCANNER_STATE_CHANGEOPERATOR ;
		}
		else if ( nResult == SIMPLE_SCANNER_LOADSYNTAX ) {
			simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			pScanner->state = SCANNER_STATE_LOADSYNTAX ;
		}
		else {
			simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
			pScanner->state = SCANNER_STATE_CHANGEKEYWORD ;
		}
	} else {
		/* Add Identifier */
		if ( strcmp(simple_stsimple_get(pScanner->ActiveToken),"") != 0 ) {
			if ( simple_scanner_isnumber(simple_stsimple_get(pScanner->ActiveToken) ) == 0 ) {
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Identifier) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(pScanner,SCANNER_TOKEN_IDENTIFIER);
			} else {
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Number) = %s  \n",simple_stsimple_get(pScanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(pScanner,SCANNER_TOKEN_NUMBER);
			}
		}
	}
}

int simple_scanner_isnumber ( char *cStr )
{
	unsigned int x  ;
	unsigned int x2  ;
	for ( x = 0 ; x < strlen(cStr) ; x++ ) {
		/* Accept _ in the number */
		if ( (cStr[x] == '_') && (x > 0) && (x < strlen(cStr) - 1) ) {
			for ( x2 = x ; x2 < strlen(cStr) ; x2++ ) {
				cStr[x2] = cStr[x2+1] ;
			}
			x-- ;
			continue ;
		}
		/* Accept f in the end of the number */
		if ( (x > 0) && (x == strlen(cStr) - 1) && ( (cStr[x] == 'f') || (cStr[x] == 'F') ) ) {
			cStr[x] = '\0' ;
			return 1 ;
		}
		if ( (cStr[x] < 48 || cStr[x] > 57) ) {
			return 0 ;
		}
	}
	return 1 ;
}

int simple_scanner_checklasttoken ( Scanner *pScanner )
{
	assert(pScanner != NULL);
	if ( simple_list_getsize(pScanner->Tokens) == 0 ) {
		if ( pScanner->state == SCANNER_STATE_COMMENT ) {
			return 0 ;
		}
	}
	if ( pScanner->state == SCANNER_STATE_LITERAL ) {
		simple_state_cgiheader(pScanner->pRingState);
		printf( "Error (S1) : In Line %d , Literal not closed, expected \" in the end\n",pScanner->nLiteralLine ) ;
		return 0 ;
	}
	else if ( pScanner->state ==SCANNER_STATE_GENERAL ) {
		simple_scanner_checktoken(pScanner);
	}
	return 1 ;
}

int simple_scanner_isoperator ( Scanner *pScanner, const char *cStr )
{
	int nPos  ;
	assert(pScanner != NULL);
	nPos = simple_hashtable_findnumber(simple_list_gethashtable(pScanner->Operators),cStr) ;
	if ( nPos > 0 ) {
		pScanner->nTokenIndex = nPos ;
		return 1 ;
	}
	return 0 ;
}

void simple_scanner_operators ( Scanner *pScanner )
{
	assert(pScanner != NULL);
	pScanner->Operators = simple_list_new_gc(pScanner->pRingState,0);
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"+");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"-");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"*");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"/");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"%");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,".");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"(");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,")");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"=");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,",");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"!");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,">");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"<");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"[");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"]");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,":");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"{");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"}");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"&");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"|");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"~");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"^");
	simple_list_addstsimple_gc(pScanner->pRingState,pScanner->Operators,"?");
	simple_list_genhashtable_gc(pScanner->pRingState,pScanner->Operators);
}

int simple_scanner_lasttokentype ( Scanner *pScanner )
{
	int x  ;
	List *pList  ;
	assert(pScanner != NULL);
	x = simple_list_getsize(pScanner->Tokens);
	if ( x > 0 ) {
		pList = simple_list_getlist(pScanner->Tokens,x);
		return simple_list_getint(pList,1) ;
	}
	return SCANNER_TOKEN_NOTOKEN ;
}

char * simple_scanner_lasttokenvalue ( Scanner *pScanner )
{
	int x  ;
	List *pList  ;
	assert(pScanner != NULL);
	x = simple_list_getsize(pScanner->Tokens);
	if ( x > 0 ) {
		pList = simple_list_getlist(pScanner->Tokens,x);
		return simple_list_getstring(pList,2) ;
	}
	return (char *) "" ;
}

void simple_scanner_floatmark ( Scanner *pScanner,int type )
{
	List *pList  ;
	String *pString  ;
	assert(pScanner != NULL);
	switch ( pScanner->FloatMark ) {
		case 0 :
			if ( type == SCANNER_TOKEN_NUMBER ) {
				pScanner->FloatMark = 1 ;
			}
			break ;
		case 1 :
			if ( (type == SCANNER_TOKEN_OPERATOR) && ( strcmp(simple_stsimple_get(pScanner->ActiveToken) , "." ) == 0  ) ) {
				pScanner->FloatMark = 2 ;
			} else {
				pScanner->FloatMark = 0 ;
			}
			break ;
		case 2 :
			if ( type == SCANNER_TOKEN_NUMBER ) {
				pList = simple_list_getlist(pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
				pString = simple_stsimple_new_gc(pScanner->pRingState,simple_list_getstring(pList,2)) ;
				simple_list_deleteitem_gc(pScanner->pRingState,pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
				simple_list_deleteitem_gc(pScanner->pRingState,pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
				pList = simple_list_getlist(pScanner->Tokens,simple_list_getsize(pScanner->Tokens));
				simple_stsimple_add_gc(pScanner->pRingState,simple_item_getstring(simple_list_getitem(pList,2)),".");
				simple_stsimple_add_gc(pScanner->pRingState,simple_item_getstring(simple_list_getitem(pList,2)),simple_stsimple_get(pString));
				simple_stsimple_delete_gc(pScanner->pRingState,pString);
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nFloat Found, Removed 2 tokens from the end, update value to float ! \n" ) ;
				printf( "\nFloat Value = %s  \n",simple_list_getstring(pList,2) ) ;
				#endif
			}
			pScanner->FloatMark = 0 ;
			break ;
	}
}

void simple_scanner_endofline ( Scanner *pScanner )
{
	/* Add Token "End of Line" to the end of any program */
	if ( simple_scanner_lasttokentype(pScanner) != SCANNER_TOKEN_ENDLINE ) {
		simple_stsimple_setfromint_gc(pScanner->pRingState,pScanner->ActiveToken,pScanner->LinesCount);
		simple_scanner_addtoken(pScanner,SCANNER_TOKEN_ENDLINE);
		#if SIMPLE_SCANNEROUTPUT
		printf( "\nTOKEN (ENDLINE)  \n" ) ;
		#endif
	}
}

void simple_scanner_addreturn ( RingState *pRingState )
{
	List *pList  ;
	/* Add return to the end of the program */
	pList = simple_list_newlist_gc(pRingState,pRingState->pRingGenCode);
	simple_list_addint_gc(pRingState,pList,ICO_RETNULL);
}

void simple_scanner_addreturn2 ( RingState *pRingState )
{
	List *pList  ;
	/* Add return to the end of the program */
	pList = simple_list_newlist_gc(pRingState,pRingState->pRingGenCode);
	simple_list_addint_gc(pRingState,pList,ICO_RETURN);
}

void simple_scanner_addreturn3 ( RingState *pRingState, int aPara[3] )
{
	List *pList  ;
	/* Add return from executeCode to the end of the executeCode() code */
	pList = simple_list_newlist_gc(pRingState,pRingState->pRingGenCode);
	simple_list_addint_gc(pRingState,pList,ICO_RETFROMEVAL);
	simple_list_addint_gc(pRingState,pList,aPara[0]);
	simple_list_addint_gc(pRingState,pList,aPara[1]);
	simple_list_addint_gc(pRingState,pList,aPara[2]);
}

void display_tokens ( Scanner *pScanner )
{
    int x,token_type,index ;
    List *token_list  ;
    char *token_name  ;
    print_line();
    puts("   TOKENS GENERATED BY SIMPLE SCANNER");
    printf("   VERSION v%s\n", SIMPLE_VERSION); 
    print_line(); printf("\n") ;
    for ( x = 1 ; x <= simple_list_getsize(pScanner->Tokens) ; x++ ) {
        token_list = simple_list_getlist(pScanner->Tokens,x);
        token_type = simple_list_getint(token_list,SIMPLE_SCANNER_TOKENTYPE) ;
        token_name = simple_list_getstring(token_list,SIMPLE_SCANNER_TOKENVALUE) ;
        switch ( token_type ) {
            case SCANNER_TOKEN_KEYWORD :
                index = atoi(token_name) ;
                printf( "   Token: TokenType=%s,\tValue=\"%s\" \n","Keyword",SIMPLE_KEYWORDS[index-1] ) ;
                break ;
            case SCANNER_TOKEN_OPERATOR :
                printf( "   Token: TokenType=%s,\tValue=\"%s\" \n","Operator",token_name ) ;
                break ;
            case SCANNER_TOKEN_NUMBER :
                printf( "   Token: TokenType=%s,\tValue=\"%s\" \n","Number",token_name ) ;
                break ;
            case SCANNER_TOKEN_IDENTIFIER :
                printf( "   Token: TokenType=%s,\tValue=\"%s\" \n","Identifier",token_name ) ;
                break ;
            case SCANNER_TOKEN_LITERAL :
                printf( "   Token: TokenType=%s,\tValue=\"%s\" \n","Literal",token_name ) ;
                break ;
            case SCANNER_TOKEN_ENDLINE :
                //printf( "[TokenType=%s]\n","EndLine" ) ;
                break ;
        }
    }
    printf( "\n" ) ;
    print_line();
    exit(0);
}

SIMPLE_API void simple_execute ( char *cFileName, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int nGenObj,int nWarn,int argc,char *argv[] )
{
	RingState *pRingState  ;
	pRingState = simple_state_new();
	pRingState->nISCGI = nISCGI ;
	pRingState->nRun = nRun ;
	pRingState->nPrintIC = nPrintIC ;
	pRingState->nPrintICFinal = nPrintICFinal ;
	pRingState->nPrintTokens = nTokens ;
	pRingState->nPrintRules = nRules ;
	pRingState->nPrintInstruction = nIns ;
	pRingState->nGenObj = nGenObj ;
	pRingState->nWarning = nWarn ;
	pRingState->argc = argc ;
	pRingState->argv = argv ;
	if ( is_simple_file(cFileName) ) {
		simple_scanner_readfile(pRingState,cFileName);
	}
	else {
		simple_scanner_runobjfile(pRingState,cFileName);
	}
	simple_state_delete(pRingState);
}

const char * simple_scanner_getkeywordtext ( const char *cStr )
{
	return SIMPLE_KEYWORDS[atoi(cStr)-1] ;
}

void simple_scanner_runobjfile ( RingState *pRingState,char *cFileName )
{
	/* Files List */
	pRingState->pRingFilesList = simple_list_new_gc(pRingState,0);
	pRingState->pRingFilesStack = simple_list_new_gc(pRingState,0);
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesList,cFileName);
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesStack,cFileName);
	if ( simple_objfile_readfile(pRingState,cFileName) ) {
		simple_scanner_runprogram(pRingState);
	}
}

void simple_scanner_runobjstring ( RingState *pRingState,char *cString,const char *cFileName )
{
	/* Files List */
	pRingState->pRingFilesList = simple_list_new_gc(pRingState,0);
	pRingState->pRingFilesStack = simple_list_new_gc(pRingState,0);
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesList,cFileName);
	simple_list_addstsimple_gc(pRingState,pRingState->pRingFilesStack,cFileName);
	if ( simple_objfile_readstring(pRingState,cString) ) {
		simple_scanner_runprogram(pRingState);
	}
}

void simple_scanner_runprogram ( RingState *pRingState )
{
	VM *pVM  ;
	/* Add return to the end of the program */
	simple_scanner_addreturn(pRingState);
	if ( pRingState->nPrintIC ) {
		simple_parser_icg_showoutput(pRingState->pRingGenCode,1);
	}
	if ( ! pRingState->nRun ) {
		return ;
	}
	pVM = simple_vm_new(pRingState);
	simple_vm_start(pRingState,pVM);
	simple_vm_delete(pVM);
	/* Display Generated Code */
	if ( pRingState->nPrintICFinal ) {
		simple_parser_icg_showoutput(pRingState->pRingGenCode,2);
	}
}

void simple_scanner_changekeyword ( Scanner *pScanner )
{
	char *cStr  ;
	int x,nResult  ;
	String *word1, *word2, *activeword  ;
	char cStr2[2]  ;
	cStr2[1] = '\0' ;
	/* Create Strings */
	word1 = simple_stsimple_new_gc(pScanner->pRingState,"");
	word2 = simple_stsimple_new_gc(pScanner->pRingState,"");
	cStr = simple_stsimple_get(pScanner->ActiveToken) ;
	activeword = word1 ;
	for ( x = 0 ; x < simple_stsimple_size(pScanner->ActiveToken) ; x++ ) {
		if ( (cStr[x] == ' ') || (cStr[x] == '\t') ) {
			if ( (activeword == word1) && (simple_stsimple_size(activeword) >= 1) ) {
				activeword = word2 ;
			}
		}
		else {
			cStr2[0] = cStr[x] ;
			simple_stsimple_add_gc(pScanner->pRingState,activeword,cStr2);
		}
	}
	/* To Lower Case */
	simple_stsimple_lower(simple_stsimple_get(word1));
	simple_stsimple_lower(simple_stsimple_get(word2));
	/* Change Keyword */
	if ( (strcmp(simple_stsimple_get(word1),"") == 0) || (strcmp(simple_stsimple_get(word2),"") == 0) ) {
		puts("Warning : The Compiler command  ChangeRingKeyword required two words");
	}
	else {
		nResult = simple_hashtable_findnumber(simple_list_gethashtable(pScanner->Keywords),simple_stsimple_get(word1));
		if ( nResult > 0 ) {
			simple_list_setstsimple_gc(pScanner->pRingState,pScanner->Keywords,nResult,simple_stsimple_get(word2));
			simple_list_genhashtable_gc(pScanner->pRingState,pScanner->Keywords);
		}
		else {
			puts("Warning : Compiler command ChangeRingKeyword - Keyword not found !");
			printf( "Keyword :  %s\n",simple_stsimple_get(word1) ) ;
		}
	}
	/* Delete Strings */
	simple_stsimple_delete_gc(pScanner->pRingState,word1);
	simple_stsimple_delete_gc(pScanner->pRingState,word2);
}

void simple_scanner_changeoperator ( Scanner *pScanner )
{
	char *cStr  ;
	int x,nResult  ;
	String *word1, *word2, *activeword  ;
	char cStr2[2]  ;
	cStr2[1] = '\0' ;
	/* Create Strings */
	word1 = simple_stsimple_new_gc(pScanner->pRingState,"");
	word2 = simple_stsimple_new_gc(pScanner->pRingState,"");
	cStr = simple_stsimple_get(pScanner->ActiveToken) ;
	activeword = word1 ;
	for ( x = 0 ; x < simple_stsimple_size(pScanner->ActiveToken) ; x++ ) {
		if ( (cStr[x] == ' ') || (cStr[x] == '\t') ) {
			if ( (activeword == word1) && (simple_stsimple_size(activeword) >= 1) ) {
				activeword = word2 ;
			}
		}
		else {
			cStr2[0] = cStr[x] ;
			simple_stsimple_add_gc(pScanner->pRingState,activeword,cStr2);
		}
	}
	/* To Lower Case */
	simple_stsimple_lower(simple_stsimple_get(word1));
	simple_stsimple_lower(simple_stsimple_get(word2));
	/* Change Operator */
	if ( (strcmp(simple_stsimple_get(word1),"") == 0) || (strcmp(simple_stsimple_get(word2),"") == 0) ) {
		puts("Warning : The Compiler command  ChangeRingOperator requires two words");
	}
	else {
		nResult = simple_hashtable_findnumber(simple_list_gethashtable(pScanner->Operators),simple_stsimple_get(word1));
		if ( nResult > 0 ) {
			simple_list_setstsimple_gc(pScanner->pRingState,pScanner->Operators,nResult,simple_stsimple_get(word2));
			simple_list_genhashtable_gc(pScanner->pRingState,pScanner->Operators);
		}
		else {
			puts("Warning : Compiler command ChangeRingOperator - Operator not found !");
			printf( "Operator :  %s\n",simple_stsimple_get(word1) ) ;
		}
	}
	/* Delete Strings */
	simple_stsimple_delete_gc(pScanner->pRingState,word1);
	simple_stsimple_delete_gc(pScanner->pRingState,word2);
}

void simple_scanner_loadsyntax ( Scanner *pScanner )
{
	char *cFileName  ;
	SIMPLE_FILE fp  ;
	/* Must be signed char to work fine on Android, because it uses -1 as NULL instead of Zero */
	signed char c  ;
	int nSize  ;
	char cFileName2[200]  ;
	unsigned int x  ;
	cFileName = simple_stsimple_get(pScanner->ActiveToken) ;
	/* Remove Spaces and " " from file name */
	x = 0 ;
	while ( ( (cFileName[x] == ' ') || (cFileName[x] == '"') ) && (x <= strlen(cFileName)) ) {
		cFileName++ ;
	}
	x = strlen(cFileName) ;
	while ( ( (cFileName[x-1] == ' ') || (cFileName[x-1] == '"') ) && (x >= 1) ) {
		cFileName[x-1] = '\0' ;
		x-- ;
	}
	/* Support File Location in Ring/bin Folder */
	strcpy(cFileName2,cFileName);
	if ( simple_fexists(cFileName) == 0 ) {
		simple_exefolder(cFileName2);
		strcat(cFileName2,cFileName);
		if ( simple_fexists(cFileName2) == 0 ) {
			strcpy(cFileName,cFileName2);
		}
	}
	fp = SIMPLE_OPENFILE(cFileName2 , "r");
	if ( fp==NULL ) {
		printf( "\nCan't open file %s \n",cFileName ) ;
		return ;
	}
	nSize = 1 ;
	simple_stsimple_set_gc(pScanner->pRingState,pScanner->ActiveToken,"");
	SIMPLE_READCHAR(fp,c,nSize);
	while ( (c != EOF) && (nSize != 0) ) {
		simple_scanner_readchar(pScanner,c);
		SIMPLE_READCHAR(fp,c,nSize);
	}
	SIMPLE_CLOSEFILE(fp);
	simple_scanner_readchar(pScanner,'\n');
}
