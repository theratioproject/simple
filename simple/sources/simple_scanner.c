

/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/*
 * File:   simple_scanner.h
 * Author: Azeez Adewale
 *
 * Created on July 10, 2017, 1:10 PM
 */

#include "../include/simple.h"

const char *external_data_path = "" ;

/* Keywords */
const char * SIMPLE_KEYWORDS[] = {"if","to","or","and","not","for","new","block",

"inherit","loop","from","call","else","display","while","class","return", "end",

"read","__exit__","break","try","catch","switch","default",

"in","continue","module","import","private","final","step","do","exec","elif",

"case"/**, "changesimplekeyword","changesimpleoperator","loadsyntax"**/} ;

/* Secondary (Not Enforced) */
const char * SIMPLE_SECONDARY_KEYWORDS[] = {"..."} ;

/* Blocks */

Scanner * new_simple_scanner ( SimpleState *sState )
{
	Scanner *scanner  ;
	scanner = (Scanner *) simple_state_malloc(sState,sizeof(Scanner));
	if ( scanner == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	scanner->sState = sState ;
	scanner->state = SCANNER_STATE_GENERAL ;
	scanner->ActiveToken = simple_string_new_gc(sState,"");
	scanner->Tokens = simple_list_new_gc(sState,0);
	simple_scanner_keywords(scanner);
	simple_scanner_operators(scanner);
	scanner->LinesCount = 1 ;
	scanner->FloatMark = 0 ;
	scanner->cMLComment = 0 ;
	scanner->nTokenIndex = 0 ;
	return scanner ;
}

Scanner * delete_simple_scanner ( Scanner *scanner )
{
	assert(scanner != NULL);
	scanner->Keywords = simple_list_delete_gc(scanner->sState,scanner->Keywords);
	scanner->Operators = simple_list_delete_gc(scanner->sState,scanner->Operators);
	scanner->Tokens = simple_list_delete_gc(scanner->sState,scanner->Tokens);
	scanner->ActiveToken = simple_string_delete_gc(scanner->sState,scanner->ActiveToken);
	simple_state_free(scanner->sState,scanner);
	return NULL ;
}

int simple_scanner_readfile ( SimpleState *sState,char *file_name )
{
	SIMPLE_FILE fp  ;
	/* Must be signed char to work fine on Android, because it uses -1 as NULL instead of Zero */
	signed char c  ;
	Scanner *scanner  ;
	VM *vm  ;
	int nCont,nRunVM,nFreeFilesList = 0 ;
	char start_up[30]  ;
	int x,nSize,is_start_file  ;
	char* simple_env_path;
	char file_name_two[200]  ; 
	char logable_name[SIMPLE_PATHSIZE] ;
	char simple_folder[100] ; 
	char module_path[SIMPLE_PATHSIZE] ;
	strcpy(logable_name,file_name); simple_justfilename(logable_name) ;
    is_start_file = 1 ; 
	/* Check file */
	if ( sState->files_list == NULL ) {
		sState->files_list = simple_list_new_gc(sState,0);
		sState->files_stack = simple_list_new_gc(sState,0);
		sState->main_file_path = file_name ;
		simple_list_addstring_gc(sState,sState->files_list,logable_name);
		simple_list_addstring_gc(sState,sState->files_stack,logable_name);
		nFreeFilesList = 1 ;
	} else {
		if ( simple_list_findstring(sState->files_list,logable_name,0) == 0) {
			simple_list_addstring_gc(sState,sState->files_list,logable_name);
			simple_list_addstring_gc(sState,sState->files_stack,logable_name);
		} else {
			//TODO : make warning level 1
			if ( sState->nWarning ) {
				//printf( "\nWarning : Duplication in FileName, %s\n",logable_name ) ;
			}
			return 1 ;
		}
	}
	if (!simple_fexists(file_name)) {
		for ( x = 1 ; x <= simple_list_getsize(sState->module_paths) ; x++ ) {
			snprintf(module_path, sizeof(module_path), "%s/%s", simple_list_getstring(sState->module_paths,x), file_name);
			if (simple_fexists(module_path)) {
				strcpy(file_name,module_path);
				break;
			}
		}
	}
	/* Switch To File Folder */
	if (is_start_file) {
		strcpy(file_name_two,file_name);
	}
	fp = SIMPLE_OPENFILE(file_name_two , "r");
	/* Avoid switching if it's the first file */
	if ( nFreeFilesList == 0 ) {
		simple_switchtofilefolder(file_name_two);
	}
	/* Read File */
	if ( fp==NULL ) {
		printf( "COMPILER ERROR 0 : Can't open file/module : %s\n", file_name) ;	
		exit(-1);
         return 0 ;
	}
	SIMPLE_READCHAR(fp,c,nSize);
	scanner = new_simple_scanner(sState);
	/* Check Startup file */
	if ( simple_fexists("startup.sim") && scanner->sState->lStartup == 0 ) {
		scanner->sState->lStartup = 1 ;
		strcpy(start_up,"call 'startup.sim'");
		/* Load "startup.sim" */
		for ( x = 0 ; x < 19 ; x++ ) {
			simple_scanner_readchar(scanner,start_up[x]);
		}
		/*
		**  Add new line
		**  We add this here instead of using \n in load 'startup.sim'
		**  To avoid increasing the line number of the code
		**  so the first line in the source code file still the first line (not second line)
		*/
		simple_string_setfromint_gc(sState,scanner->ActiveToken,0);
		simple_scanner_addtoken(scanner,SCANNER_TOKEN_ENDLINE);
	}
	nSize = 1 ;
	while ( (c != EOF) && (nSize != 0) ) {
		simple_scanner_readchar(scanner,c);
		SIMPLE_READCHAR(fp,c,nSize);
	}
	nCont = simple_scanner_checklasttoken(scanner);
	/* Add Token "End of Line" to the end of any program */
	simple_scanner_endofline(scanner);
	SIMPLE_CLOSEFILE(fp);
	/* Print Tokens */
	if ( sState->nPrintTokens ) {
		display_tokens(scanner);
	}
	/* Call Parser */
	if ( nCont == 1 ) {
		#if SIMPLE_PARSERTRACE
		if ( scanner->sState->nPrintRules ) {
			printf( "\n" ) ;
			print_line();
			puts("Grammar Rules Used by The Parser ");
			print_line();
			printf( "\nRule : Program --> {Statement}\n\nLine 1\n" ) ;
		}
		#endif
		nRunVM = simple_parser_start(scanner->Tokens,sState);
		#if SIMPLE_PARSERTRACE
		if ( scanner->sState->nPrintRules ) {
			printf( "\n" ) ;
			print_line();
			printf( "\n" ) ;
		}
		#endif
	} else {
		simple_list_deleteitem_gc(sState,sState->files_stack,simple_list_getsize(sState->files_stack));
		delete_simple_scanner(scanner);
		return 0 ;
	}
	delete_simple_scanner(scanner);
	/* Files List */
	simple_list_deleteitem_gc(sState,sState->files_stack,simple_list_getsize(sState->files_stack));
	if ( nFreeFilesList ) {
		/* Generate the Object File */
		if ( sState->generate_object ) {
			simple_object_writefile(sState);
		}
		/* Run the Program */
		#if SIMPLE_RUNVM
		if ( nRunVM == 1 ) {
			/* Add return to the end of the program */
			simple_scanner_addreturn(sState);
			if ( sState->nPrintIC ) {
				simple_parser_icg_showoutput(sState->generated_code,1);
			}
			if ( ! sState->nRun ) {
				return 1 ;
			}
			vm = simple_vm_new(sState);
			simple_vm_start(sState,vm);
			if ( ! sState->nDontDeleteTheVM ) {
				simple_vm_delete(vm);
			}
		}
		#endif
		/* Display Generated Code */
		if ( sState->nPrintICFinal ) {
			simple_parser_icg_showoutput(sState->generated_code,2);
		}
	}
	return nRunVM ;
}

void simple_scanner_readchar ( Scanner *scanner,char c )
{
	char cStr[2]  ;
	List *list  ;
	String *string  ;
	int nTokenIndex  ;
	assert(scanner != NULL);
	cStr[0] = c ;
	cStr[1] = '\0' ;
	#if SIMPLE_DEBUG
	printf("%c",c);
	printf( "\n State : %d \n  \n",scanner->state ) ;
	#endif
	switch ( scanner->state ) {
		case SCANNER_STATE_GENERAL :
			/* Check Unicode File */
			if ( simple_list_getsize(scanner->Tokens) == 0 ) {
				/* UTF8 */
				if ( strcmp(simple_string_get(scanner->ActiveToken),"\xEF\xBB\xBF") == 0 ) {
					simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
					/* Don't use reading so the new character can be scanned */
				} 
			}
			/* Check Space/Tab/New Line */
			if ( c != ' ' && c != '\n' && c != '\t' && c != '\"' && c != '\'' && c != '\r' && c != '`' ) {
				if ( simple_scanner_isoperator(scanner,cStr) ) {
					nTokenIndex = scanner->nTokenIndex ;
					simple_scanner_checktoken(scanner);
					simple_string_set_gc(scanner->sState,scanner->ActiveToken,cStr);
					#if SIMPLE_SCANNEROUTPUT
					printf( "\nTOKEN (Operator) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
					#endif
					/* Check Multiline Comment */
					if ( (strcmp(cStr,"*") == 0) && (simple_scanner_lasttokentype(scanner) ==SCANNER_TOKEN_OPERATOR) ) {
						list = simple_list_getlist(scanner->Tokens,simple_list_getsize(scanner->Tokens));
						if ( strcmp(simple_list_getstring(list,2),"/") == 0 ) {
							simple_list_deleteitem_gc(scanner->sState,scanner->Tokens,simple_list_getsize(scanner->Tokens));
							scanner->state = SCANNER_STATE_MLCOMMENT ;
							#if SIMPLE_SCANNEROUTPUT
							printf( "\nMultiline comments start, ignore /* \n" ) ;
							#endif
							return ;
						}
					}
					/* Check comment using // */
					if ( strcmp(cStr,"/") == 0 ) {
						if ( simple_scanner_lasttokentype(scanner) ==SCANNER_TOKEN_OPERATOR ) {
							if ( strcmp("/",simple_scanner_lasttokenvalue(scanner)) ==  0 ) {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								scanner->state = SCANNER_STATE_COMMENT ;
								return ;
							}
						}
					}
					/* Check << | >> operators */
					if ( ( strcmp(cStr,"<") == 0 ) | ( strcmp(cStr,">") == 0 ) ) {
						if ( strcmp(cStr,simple_scanner_lasttokenvalue(scanner)) ==  0 ) {
							if ( strcmp(cStr,"<") == 0 ) {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								simple_string_set_gc(scanner->sState,scanner->ActiveToken,"<<");
							} else {
								SIMPLE_SCANNER_DELETELASTTOKEN ;
								simple_string_set_gc(scanner->sState,scanner->ActiveToken,">>");
							}
							#if SIMPLE_SCANNEROUTPUT
							printf( "\nTOKEN (Operator) = %s , merge previous two operators in one \n",simple_string_get(scanner->ActiveToken) ) ;
							#endif
							nTokenIndex += 100 ;
						}
					}
					/* Check += -= *= /= %= &= |= ^= <<= >>= */
					else if ( strcmp(cStr,"=") == 0 ) {
						nTokenIndex += 100 ;
						if ( strcmp(simple_scanner_lasttokenvalue(scanner),"+") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"+=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"-") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"-=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"*") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"*=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"/") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"/=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"%") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"%=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"&") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"&=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"|") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"|=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"^") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set(scanner->ActiveToken,"^=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),"<<") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"<<=");
						}
						else if ( strcmp(simple_scanner_lasttokenvalue(scanner),">>") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,">>=");
						}
						else {
							nTokenIndex -= 100 ;
						}
					}
					/* Check ++ and -- */
					else if ( strcmp(cStr,"+") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(scanner),"+") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"++");
							nTokenIndex += 100 ;
						}
					}
					else if ( strcmp(cStr,"-") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(scanner),"-") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"--");
							nTokenIndex += 100 ;
						}
					}
					/* Check && and || */
					else if ( strcmp(cStr,"&") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(scanner),"&") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"&&");
							nTokenIndex += 100 ;
						}
					}
					else if ( strcmp(cStr,"|") == 0 ) {
						if ( strcmp(simple_scanner_lasttokenvalue(scanner),"|") == 0 ) {
							SIMPLE_SCANNER_DELETELASTTOKEN ;
							simple_string_set_gc(scanner->sState,scanner->ActiveToken,"||");
							nTokenIndex += 100 ;
						}
					}
					scanner->nTokenIndex = nTokenIndex ;
					simple_scanner_addtoken(scanner,SCANNER_TOKEN_OPERATOR);
				} else {
					simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
					#if SIMPLE_DEBUG
					printf( "\nActive Token = %s",simple_string_get(scanner->ActiveToken) ) ;
					#endif
				}
			} else {
				if ( simple_scanner_isoperator(scanner,simple_string_get(scanner->ActiveToken)) ) {
					simple_scanner_addtoken(scanner,SCANNER_TOKEN_OPERATOR);
				}
				else {
					simple_scanner_checktoken(scanner);
				}
			}
			/* Switch State */
			if ( c == '"' ) {
				scanner->state = SCANNER_STATE_LITERAL ;
				scanner->cLiteral = '"' ;
				scanner->nLiteralLine = scanner->LinesCount ;
			}
			else if ( c == '\'' ) {
				scanner->state = SCANNER_STATE_LITERAL ;
				scanner->cLiteral = '\'' ;
				scanner->nLiteralLine = scanner->LinesCount ;
			}
			else if ( c == '`' ) {
				scanner->state = SCANNER_STATE_LITERAL ;
				scanner->cLiteral = '`' ;
				scanner->nLiteralLine = scanner->LinesCount ;
			}
			else if ( c == '#' ) {
				scanner->state = SCANNER_STATE_COMMENT ;
			}
			break ;
		case SCANNER_STATE_LITERAL :
			/* Switch State */
			if ( c == scanner->cLiteral ) {
				scanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Literal) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(scanner,SCANNER_TOKEN_LITERAL);
			} else {
				simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_COMMENT :
			/* Switch State */
			if ( c == '\n' ) {
				scanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Not TOKEN (Comment) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			} else {
				simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_MLCOMMENT :
			/* Check Multiline Comment */
			switch ( scanner->cMLComment ) {
				case 0 :
					if ( strcmp(cStr,"*") == 0 ) {
						scanner->cMLComment = 1 ;
						return ;
					}
					break ;
				case 1 :
					if ( strcmp(cStr,"/") == 0 ) {
						scanner->state = SCANNER_STATE_GENERAL ;
						#if SIMPLE_SCANNEROUTPUT
						printf( "\nMultiline comments end \n" ) ;
						#endif
						/* The next step is important to avoid storing * as identifier! */
						simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
					}
					scanner->cMLComment = 0 ;
					return ;
			}
			break ;
		case SCANNER_STATE_CHANGEKEYWORD :
			/* Switch State */
			if ( c == '\n' ) {
				scanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Change Keyword = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_changekeyword(scanner);
				simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			} else {
				simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_CHANGEOPERATOR :
			/* Switch State */
			if ( c == '\n' ) {
				scanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Change operator = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_changeoperator(scanner);
				simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			} else {
				simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
			}
			break ;
		case SCANNER_STATE_LOADSYNTAX :
			/* Switch State */
			if ( c == '\n' ) {
				scanner->state = SCANNER_STATE_GENERAL ;
				#if SIMPLE_SCANNEROUTPUT
				printf( "\n Load Syntax = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_loadsyntax(scanner);
				simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			} else {
				simple_string_add_gc(scanner->sState,scanner->ActiveToken,cStr);
			}
			break ;
	}
	if ( c == '\n' ) {
		scanner->LinesCount++ ;
		#if SIMPLE_DEBUG
		printf( "Line Number : %d  \n",scanner->LinesCount ) ;
		#endif
	}
	if ( ( c == ';' || c == '\n' ) && ( scanner->state == SCANNER_STATE_GENERAL ) ) {
		if ( (simple_scanner_lasttokentype(scanner) != SCANNER_TOKEN_ENDLINE ) ) {
			simple_string_setfromint_gc(scanner->sState,scanner->ActiveToken,scanner->LinesCount);
			simple_scanner_addtoken(scanner,SCANNER_TOKEN_ENDLINE);
			#if SIMPLE_SCANNEROUTPUT
			printf( "\nTOKEN (ENDLINE)  \n" ) ;
			#endif
		} else {
			list = simple_list_getlist(scanner->Tokens,simple_list_getsize(scanner->Tokens));
			string = simple_string_new_gc(scanner->sState,"");
			simple_string_setfromint_gc(scanner->sState,string,scanner->LinesCount);
			simple_list_setstring_gc(scanner->sState,list,2,simple_string_get(string));
			simple_string_delete_gc(scanner->sState,string);
		}
	}
}

void simple_scanner_keywords ( Scanner *scanner )
{
	assert(scanner != NULL);
	scanner->Keywords = simple_list_new_gc(scanner->sState,0);
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"if");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"to");
	/* Logic */
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"or");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"and");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"not");
    simple_list_addstring_gc(scanner->sState,scanner->Keywords,"for");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"new");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"block");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"inherit");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"loop");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"from");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"call");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"else");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"display");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"while");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"class");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"return");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"end");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"read");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"__exit__");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"break");
	/* try-catch */
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"try");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"catch");
	/* Switch */
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"switch");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"default");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"in");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"continue");
	/* Modules */
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"module");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"import");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"private");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"final");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"step");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"do");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"exec");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"elif");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"case");
	/*
	**  The next keywords are sensitive to the order and keywords count
	**  if you will add new keywords revise constants and simple_scanner_checktoken()
	*/
	/**simple_list_addstring_gc(scanner->sState,scanner->Keywords,"changesimplekeyword");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"changesimpleoperator");
	simple_list_addstring_gc(scanner->sState,scanner->Keywords,"loadsyntax");**/
	simple_list_genhashtable_gc(scanner->sState,scanner->Keywords);
}

void simple_scanner_addtoken ( Scanner *scanner,int type )
{
	List *list  ;
	assert(scanner != NULL);
	list = simple_list_newlist_gc(scanner->sState,scanner->Tokens);
	/* Add Token Type */
	simple_list_addint_gc(scanner->sState,list,type);
	/* Add Token Text */
	simple_list_addstring_gc(scanner->sState,list,simple_string_get(scanner->ActiveToken));
	/* Add Token Index */
	simple_list_addint_gc(scanner->sState,list,scanner->nTokenIndex);
	scanner->nTokenIndex = 0 ;
	simple_scanner_floatmark(scanner,type);
	simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
}

void simple_scanner_checktoken ( Scanner *scanner )
{
	int nResult  ;
	char cStr[5]  ;
	/* This block determine if the TOKEN is a Keyword or Identifier or Number */
	assert(scanner != NULL);
	nResult = simple_hashtable_findnumber(simple_list_gethashtable(scanner->Keywords),simple_string_get(scanner->ActiveToken));
	if ( nResult > 0 ) {
		#if SIMPLE_SCANNEROUTPUT
		printf( "\nTOKEN (Keyword) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
		#endif
		if ( nResult < SIMPLE_SCANNER_CHANGERINGKEYWORD ) {
			sprintf( cStr , "%d" , nResult ) ;
			simple_string_set_gc(scanner->sState,scanner->ActiveToken,cStr);
			simple_scanner_addtoken(scanner,SCANNER_TOKEN_KEYWORD);
		}
		else if ( nResult == SIMPLE_SCANNER_CHANGERINGOPERATOR ) {
			simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			scanner->state = SCANNER_STATE_CHANGEOPERATOR ;
		}
		else if ( nResult == SIMPLE_SCANNER_LOADSYNTAX ) {
			simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			scanner->state = SCANNER_STATE_LOADSYNTAX ;
		}
		else {
			simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
			scanner->state = SCANNER_STATE_CHANGEKEYWORD ;
		}
	} else {
		/* Add Identifier */
		if ( strcmp(simple_string_get(scanner->ActiveToken),"") != 0 ) {
			if ( simple_scanner_isnumber(simple_string_get(scanner->ActiveToken) ) == 0 ) {
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Identifier) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(scanner,SCANNER_TOKEN_IDENTIFIER);
			} else {
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nTOKEN (Number) = %s  \n",simple_string_get(scanner->ActiveToken) ) ;
				#endif
				simple_scanner_addtoken(scanner,SCANNER_TOKEN_NUMBER);
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

int simple_scanner_checklasttoken ( Scanner *scanner )
{
	assert(scanner != NULL);
	if ( simple_list_getsize(scanner->Tokens) == 0 ) {
		if ( scanner->state == SCANNER_STATE_COMMENT ) {
			return 0 ;
		}
	}
	if ( scanner->state == SCANNER_STATE_LITERAL ) {
		printf( "Error (S1) : In Line %d , Literal not closed, expected \" in the end\n",scanner->nLiteralLine ) ;
		return 0 ;
	}
	else if ( scanner->state ==SCANNER_STATE_GENERAL ) {
		simple_scanner_checktoken(scanner);
	}
	return 1 ;
}

int simple_scanner_isoperator ( Scanner *scanner, const char *cStr )
{
	int nPos  ;
	assert(scanner != NULL);
	nPos = simple_hashtable_findnumber(simple_list_gethashtable(scanner->Operators),cStr) ;
	if ( nPos > 0 ) {
		scanner->nTokenIndex = nPos ;
		return 1 ;
	}
	return 0 ;
}

void simple_scanner_operators ( Scanner *scanner )
{
	assert(scanner != NULL);
	scanner->Operators = simple_list_new_gc(scanner->sState,0);
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"+");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"-");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"*");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"/");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"%");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,".");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"(");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,")");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"=");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,",");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"!");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,">");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"<");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"[");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"]");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,":");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"{");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"}");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"&");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"|");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"~");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"^");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"?");
	simple_list_addstring_gc(scanner->sState,scanner->Operators,"@");
	simple_list_genhashtable_gc(scanner->sState,scanner->Operators);
}

int simple_scanner_lasttokentype ( Scanner *scanner )
{
	int x  ;
	List *list  ;
	assert(scanner != NULL);
	x = simple_list_getsize(scanner->Tokens);
	if ( x > 0 ) {
		list = simple_list_getlist(scanner->Tokens,x);
		return simple_list_getint(list,1) ;
	}
	return SCANNER_TOKEN_NOTOKEN ;
}

char * simple_scanner_lasttokenvalue ( Scanner *scanner )
{
	int x  ;
	List *list  ;
	assert(scanner != NULL);
	x = simple_list_getsize(scanner->Tokens);
	if ( x > 0 ) {
		list = simple_list_getlist(scanner->Tokens,x);
		return simple_list_getstring(list,2) ;
	}
	return (char *) "" ;
}

void simple_scanner_floatmark ( Scanner *scanner,int type )
{
	List *list  ;
	String *string  ;
	assert(scanner != NULL);
	switch ( scanner->FloatMark ) {
		case 0 :
			if ( type == SCANNER_TOKEN_NUMBER ) {
				scanner->FloatMark = 1 ;
			}
			break ;
		case 1 :
			if ( (type == SCANNER_TOKEN_OPERATOR) && ( strcmp(simple_string_get(scanner->ActiveToken) , "." ) == 0  ) ) {
				scanner->FloatMark = 2 ;
			} else {
				scanner->FloatMark = 0 ;
			}
			break ;
		case 2 :
			if ( type == SCANNER_TOKEN_NUMBER ) {
				list = simple_list_getlist(scanner->Tokens,simple_list_getsize(scanner->Tokens));
				string = simple_string_new_gc(scanner->sState,simple_list_getstring(list,2)) ;
				simple_list_deleteitem_gc(scanner->sState,scanner->Tokens,simple_list_getsize(scanner->Tokens));
				simple_list_deleteitem_gc(scanner->sState,scanner->Tokens,simple_list_getsize(scanner->Tokens));
				list = simple_list_getlist(scanner->Tokens,simple_list_getsize(scanner->Tokens));
				simple_string_add_gc(scanner->sState,simple_item_getstring(simple_list_getitem(list,2)),".");
				simple_string_add_gc(scanner->sState,simple_item_getstring(simple_list_getitem(list,2)),simple_string_get(string));
				simple_string_delete_gc(scanner->sState,string);
				#if SIMPLE_SCANNEROUTPUT
				printf( "\nFloat Found, Removed 2 tokens from the end, update value to float ! \n" ) ;
				printf( "\nFloat Value = %s  \n",simple_list_getstring(list,2) ) ;
				#endif
			}
			scanner->FloatMark = 0 ;
			break ;
	}
}

void simple_scanner_endofline ( Scanner *scanner )
{
	/* Add Token "End of Line" to the end of any program */
	if ( simple_scanner_lasttokentype(scanner) != SCANNER_TOKEN_ENDLINE ) {
		simple_string_setfromint_gc(scanner->sState,scanner->ActiveToken,scanner->LinesCount);
		simple_scanner_addtoken(scanner,SCANNER_TOKEN_ENDLINE);
		#if SIMPLE_SCANNEROUTPUT
		printf( "\nTOKEN (ENDLINE)  \n" ) ;
		#endif
	}
}

void simple_scanner_addreturn ( SimpleState *sState )
{
	List *list  ;
	/* Add return to the end of the program */
	list = simple_list_newlist_gc(sState,sState->generated_code);
	simple_list_addint_gc(sState,list,ICO_RETNULL);
}

void simple_scanner_addreturn2 ( SimpleState *sState )
{
	List *list  ;
	/* Add return to the end of the program */
	list = simple_list_newlist_gc(sState,sState->generated_code);
	simple_list_addint_gc(sState,list,ICO_RETURN);
}

void simple_scanner_addreturn3 ( SimpleState *sState, int aPara[3] )
{
	List *list  ;
	/* Add return from executeCode to the end of the executeCode() code */
	list = simple_list_newlist_gc(sState,sState->generated_code);
	simple_list_addint_gc(sState,list,ICO_RETFROMEVAL);
	simple_list_addint_gc(sState,list,aPara[0]);
	simple_list_addint_gc(sState,list,aPara[1]);
	simple_list_addint_gc(sState,list,aPara[2]);
}

void display_tokens ( Scanner *scanner )
{
    int x,token_type,index ;
    List *token_list  ;
    char *token_name  ;
    print_line();
    puts("   TOKENS GENERATED BY SIMPLE SCANNER");
    printf("   VERSION v%s\n", SIMPLE_VERSION);
    print_line(); printf("\n") ;
    for ( x = 1 ; x <= simple_list_getsize(scanner->Tokens) ; x++ ) {
        token_list = simple_list_getlist(scanner->Tokens,x);
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
    print_line();
    exit(0);
}

SIMPLE_API void simple_execute ( char *file_name, int nISCGI,int nRun,int nPrintIC,int nPrintICFinal,int nTokens,int nRules,int nIns,int generate_object,int nWarn,int argc,char *argv[], int skip_error)
{
	SimpleState *sState  ;
	sState = simple_state_new();
	sState->nISCGI = nISCGI ;
	sState->nRun = nRun ;
	sState->nPrintIC = nPrintIC ;
	sState->nPrintICFinal = nPrintICFinal ;
	sState->nPrintTokens = nTokens ;
	sState->nPrintRules = nRules ;
	sState->nPrintInstruction = nIns ;
	sState->generate_object = generate_object ; 
	sState->nWarning = nWarn ;
	sState->skip_error= skip_error ;
	sState->argc = argc ;
	sState->argv = argv ;
	if (sState->nISCGI)
		simple_state_cgiheader(sState);
	if ( is_simple_file(file_name) ) {
		simple_scanner_readfile(sState,file_name);
	}
	else {
		simple_scanner_runobject(sState,file_name);
	}
	finalize_simple_state(sState);
}

void simple_scanner_runobject( SimpleState *sState,char *file_name )
{
	/* Files List */
	sState->files_list = simple_list_new_gc(sState,0);
	sState->files_stack = simple_list_new_gc(sState,0);
	simple_list_addstring_gc(sState,sState->files_list,file_name);
	simple_list_addstring_gc(sState,sState->files_stack,file_name);
	if ( simple_object_readfile(sState,file_name) ) {
		simple_scanner_runprogram(sState);
	}
}

void simple_scanner_runobjstring ( SimpleState *sState,char *string,const char *file_name )
{
	/* Files List */
	sState->files_list = simple_list_new_gc(sState,0);
	sState->files_stack = simple_list_new_gc(sState,0);
	simple_list_addstring_gc(sState,sState->files_list,file_name);
	simple_list_addstring_gc(sState,sState->files_stack,file_name);
	if ( simple_object_readstring(sState,string) ) {
		simple_scanner_runprogram(sState);
	}
}

const char * simple_scanner_getkeywordtext ( const char *cStr )
{
	return SIMPLE_KEYWORDS[atoi(cStr)-1] ;
}

const char * simple_secondary_keyword_value(SCANNER_SECONDARY_KEYWORD position) 
{
	return SIMPLE_SECONDARY_KEYWORDS[position-1] ;
}

void simple_scanner_runprogram ( SimpleState *sState )
{
	VM *vm  ;
	/* Add return to the end of the program */
	simple_scanner_addreturn(sState);
	if ( sState->nPrintIC ) {
		simple_parser_icg_showoutput(sState->generated_code,1);
	}
	if ( ! sState->nRun ) {
		return ;
	}
	vm = simple_vm_new(sState);
	simple_vm_start(sState,vm);
	simple_vm_delete(vm); 
	/* Display Generated Code */
	if ( sState->nPrintICFinal ) {
		simple_parser_icg_showoutput(sState->generated_code,2);
	}
}

void simple_scanner_changekeyword ( Scanner *scanner )
{
	char *cStr  ;
	int x,nResult  ;
	String *word1, *word2, *activeword  ;
	char cStr2[2]  ;
	cStr2[1] = '\0' ;
	/* Create Strings */
	word1 = simple_string_new_gc(scanner->sState,"");
	word2 = simple_string_new_gc(scanner->sState,"");
	cStr = simple_string_get(scanner->ActiveToken) ;
	activeword = word1 ;
	for ( x = 0 ; x < simple_string_size(scanner->ActiveToken) ; x++ ) {
		if ( (cStr[x] == ' ') || (cStr[x] == '\t') ) {
			if ( (activeword == word1) && (simple_string_size(activeword) >= 1) ) {
				activeword = word2 ;
			}
		}
		else {
			cStr2[0] = cStr[x] ;
			simple_string_add_gc(scanner->sState,activeword,cStr2);
		}
	}
	/* Change Keyword */
	if ( (strcmp(simple_string_get(word1),"") == 0) || (strcmp(simple_string_get(word2),"") == 0) ) {
		puts("Warning : The Compiler command  ChangeSimpleKeyword required two words");
	}
	else {
		nResult = simple_hashtable_findnumber(simple_list_gethashtable(scanner->Keywords),simple_string_get(word1));
		if ( nResult > 0 ) {
			simple_list_setstring_gc(scanner->sState,scanner->Keywords,nResult,simple_string_get(word2));
			simple_list_genhashtable_gc(scanner->sState,scanner->Keywords);
		}
		else {
			puts("Warning : Compiler command ChangeSimpleKeyword - Keyword not found !");
			printf( "Keyword :  %s\n",simple_string_get(word1) ) ;
		}
	}
	/* Delete Strings */
	simple_string_delete_gc(scanner->sState,word1);
	simple_string_delete_gc(scanner->sState,word2);
}

void simple_scanner_changeoperator ( Scanner *scanner )
{
	char *cStr  ;
	int x,nResult  ;
	String *word1, *word2, *activeword  ;
	char cStr2[2]  ;
	cStr2[1] = '\0' ;
	/* Create Strings */
	word1 = simple_string_new_gc(scanner->sState,"");
	word2 = simple_string_new_gc(scanner->sState,"");
	cStr = simple_string_get(scanner->ActiveToken) ;
	activeword = word1 ;
	for ( x = 0 ; x < simple_string_size(scanner->ActiveToken) ; x++ ) {
		if ( (cStr[x] == ' ') || (cStr[x] == '\t') ) {
			if ( (activeword == word1) && (simple_string_size(activeword) >= 1) ) {
				activeword = word2 ;
			}
		}
		else {
			cStr2[0] = cStr[x] ;
			simple_string_add_gc(scanner->sState,activeword,cStr2);
		}
	}
	/* Change Operator */
	if ( (strcmp(simple_string_get(word1),"") == 0) || (strcmp(simple_string_get(word2),"") == 0) ) {
		puts("Warning : The Compiler command  ChangeSimpleOperator requires two words");
	}
	else {
		nResult = simple_hashtable_findnumber(simple_list_gethashtable(scanner->Operators),simple_string_get(word1));
		if ( nResult > 0 ) {
			simple_list_setstring_gc(scanner->sState,scanner->Operators,nResult,simple_string_get(word2));
			simple_list_genhashtable_gc(scanner->sState,scanner->Operators);
		}
		else {
			puts("Warning : Compiler command ChangeSimpleOperator - Operator not found !");
			printf( "Operator :  %s\n",simple_string_get(word1) ) ;
		}
	}
	/* Delete Strings */
	simple_string_delete_gc(scanner->sState,word1);
	simple_string_delete_gc(scanner->sState,word2);
}

void simple_scanner_loadsyntax ( Scanner *scanner )
{
	char *file_name  ;
	SIMPLE_FILE fp  ;
	/* Must be signed char to work fine on Android, because it uses -1 as NULL instead of Zero */
	signed char c  ;
	int nSize  ;
	char file_name_two[200]  ;
	unsigned int x  ;
	file_name = simple_string_get(scanner->ActiveToken) ;
	/* Remove Spaces and " " from file name */
	x = 0 ;
	while ( ( (file_name[x] == ' ') || (file_name[x] == '"') ) && (x <= strlen(file_name)) ) {
		file_name++ ;
	}
	x = strlen(file_name) ;
	while ( ( (file_name[x-1] == ' ') || (file_name[x-1] == '"') ) && (x >= 1) ) {
		file_name[x-1] = '\0' ;
		x-- ;
	}
	/* Support File Location in Simple/bin Folder */
	strcpy(file_name_two,file_name);
	if ( simple_fexists(file_name) == 0 ) {
		simple_exefolder(file_name_two);
		strcat(file_name_two,file_name);
		if ( simple_fexists(file_name_two) == 0 ) {
			strcpy(file_name,file_name_two);
		}
	}
	fp = SIMPLE_OPENFILE(file_name_two , "r");
	if ( fp==NULL ) {
		printf( "\nCan't open file %s \n",file_name ) ;
		return ;
	}
	nSize = 1 ;
	simple_string_set_gc(scanner->sState,scanner->ActiveToken,"");
	SIMPLE_READCHAR(fp,c,nSize);
	while ( (c != EOF) && (nSize != 0) ) {
		simple_scanner_readchar(scanner,c);
		SIMPLE_READCHAR(fp,c,nSize);
	}
	SIMPLE_CLOSEFILE(fp);
	simple_scanner_readchar(scanner,'\n');
}
