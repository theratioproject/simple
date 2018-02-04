
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
/* Grammar */

int simple_parser_class ( Parser *parser )
{
	List *pList,*pList2,*pList3  ;
	int x  ;
	String *pString  ;
	/* Statement --> Class Identifier  [ From Identifier ] */
	if ( simple_parser_iskeyword(parser,KEYWORD_CLASS) ) {
		simple_parser_nexttoken(parser);
		if ( simple_parser_isidentifier(parser) ) {
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(parser,ICO_RETNULL);
			simple_parser_icg_newoperation(parser,ICO_NEWCLASS);
			simple_parser_icg_newoperand(parser,parser->TokenText);
			/* Add Class to Classes Table */
			pList = parser->ClassesMap ;
			/* Check Class Redefinition */
			if ( simple_list_getsize(pList) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(pList,x),1),parser->TokenText) == 0 ) {
						parser_error(parser,PARSER_ERROR_CLASSREDEFINE);
						return 0 ;
					}
				}
			}
			pList = simple_list_newlist_gc(parser->pSimpleState,pList);
			simple_list_addstring_gc(parser->pSimpleState,pList,parser->TokenText);
			simple_list_addint_gc(parser->pSimpleState,pList,simple_list_getsize(parser->GenCode));
			/* Add class pointer to generated code */
			simple_parser_icg_newoperandpointer(parser,pList);
			simple_parser_nexttoken(parser);
			/* [From Identifer] */
			if ( simple_parser_isoperator2(parser,OP_RANGE) || simple_parser_isoperator2(parser,OP_LESS) ) {
				simple_parser_nexttoken(parser);
				if ( simple_parser_namedotname(parser) ) {
					/* Generate Code */
					pList3 = simple_parser_icg_getactiveoperation(parser);
					/* Check if parent class name = subclass name */
					if ( strcmp(simple_list_getstring(pList,1),simple_list_getstring(pList3,4)) == 0 ) {
						parser_error(parser,PARSER_ERROR_PARENTLIKESUBCLASS);
						return 0 ;
					}
					/* Set Parent Class Name in Classes Map */
					simple_list_addstring_gc(parser->pSimpleState,pList,simple_list_getstring(pList3,4));
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : Statement  --> 'Class' Identifier 'From' [ModulesName'.']Identifier");
					#endif
				} else {
					parser_error(parser,PARSER_ERROR_PRENTCLASSNAME);
					return 0 ;
				}
			} else {
				/* Set Parent Class Name In Classes Map */
				simple_list_addstring_gc(parser->pSimpleState,pList,"");
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Statement  --> 'Class' Identifier ");
				#endif
			}
			/* Add Method/Functions List to Class in Class Table */
			pList2 = simple_list_newlist_gc(parser->pSimpleState,pList);
			/* Add Flag ( IS Parent Class information collected  ) */
			simple_list_addint_gc(parser->pSimpleState,pList,0);
			/* Set Active Functions List to be Class Methods */
			parser->FunctionsMap = pList2 ;
			/* Make class visible using ModulesName.ClassName if we have modules */
			if ( parser->ClassesMap != parser->pSimpleState->pSimpleClassesMap ) {
				/* Get Modules Name */
				pList3 = simple_list_getlist(parser->pSimpleState->pSimpleModulessMap,simple_list_getsize(parser->pSimpleState->pSimpleModulessMap));
				pString = simple_string_new_gc(parser->pSimpleState,simple_list_getstring(pList3,1));
				/* Add pointer to the Modules in the Class List */
				simple_list_addpointer_gc(parser->pSimpleState,pList,pList3);
				/* Add List point to General Classes point to the class in the modules */
				pList2 = simple_list_newlist_gc(parser->pSimpleState,parser->pSimpleState->pSimpleClassesMap);
				simple_list_addstring_gc(parser->pSimpleState,pList2,"");
				simple_list_addpointer_gc(parser->pSimpleState,pList2,pList);
				/* Ignore Adding Pointer to File Name */
				simple_list_addpointer_gc(parser->pSimpleState,pList2,NULL);
				/* Add Class Name to Modules Name */
				simple_string_add_gc(parser->pSimpleState,pString,".");
				simple_string_add_gc(parser->pSimpleState,pString,simple_list_getstring(pList,1));
				simple_list_setstsimple_gc(parser->pSimpleState,pList2,1,simple_string_get(pString));
				simple_string_delete_gc(parser->pSimpleState,pString);
			} else {
				/* Add pointer to the Modules in the Class List */
				simple_list_addpointer_gc(parser->pSimpleState,pList,NULL);
			}
			parser->nClassStart = 1 ;
			/* Create label to be used by Private */
			parser->nClassMark = simple_parser_icg_newlabel2(parser);
			parser->nPrivateFlag = 0 ;
			/* Generate Code - Set The File Name */
			simple_parser_icg_newoperation(parser,ICO_FILENAME);
			simple_parser_icg_newoperand(parser,simple_list_getstring(parser->pSimpleState->pSimpleFilesStack,simple_list_getsize(parser->pSimpleState->pSimpleFilesStack)));
			/* Set Global Scope */
			simple_parser_icg_newoperation(parser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(parser,simple_list_getint(parser->pSimpleState->aCustomGlobalScopeStack,simple_list_getsize(parser->pSimpleState->aCustomGlobalScopeStack)));
			/* Support using { } around the class code and using 'end' after the content */
			return simple_parser_bracesandend(parser,1,KEYWORD_END) ;
		} else {
			parser_error(parser,PARSER_ERROR_CLASSNAME);
			return 0 ;
		}
	}
	/* Statement --> block Identifier [PARALIST] */
	if ( simple_parser_iskeyword(parser,KEYWORD_BLOCK) ) {
		simple_parser_nexttoken(parser);
		if ( simple_parser_isidentifier(parser) ) {
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(parser,ICO_RETNULL);
			simple_parser_icg_newoperation(parser,ICO_NEWBLOCK);
			simple_parser_icg_newoperand(parser,parser->TokenText);
			/* Add function to Functions Table */
			pList2 = parser->FunctionsMap ;
			/* Check Function Redefinition */
			if ( simple_list_getsize(pList2) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(pList2,x),1),parser->TokenText) == 0 ) {
						parser_error(parser,PARSER_ERROR_BLOCKREDEFINE);
						return 0 ; 
					}
				}
			}
			pList2 = simple_list_newlist_gc(parser->pSimpleState,pList2);
			simple_list_addstring_gc(parser->pSimpleState,pList2,parser->TokenText);
			simple_list_addint_gc(parser->pSimpleState,pList2,simple_list_getsize(parser->GenCode));
			simple_list_addstring_gc(parser->pSimpleState,pList2,simple_list_getstring(parser->pSimpleState->pSimpleFilesStack,simple_list_getsize(parser->pSimpleState->pSimpleFilesStack)));
			if ( parser->nClassStart == 1 ) {
				simple_list_addint_gc(parser->pSimpleState,pList2,parser->nPrivateFlag);
			} else {
				simple_list_addint_gc(parser->pSimpleState,pList2,0);
			}
			simple_parser_nexttoken(parser);
			if ( simple_parser_isidentifier(parser) || simple_parser_isoperator2(parser,OP_FOPEN) ) {
				x = simple_parser_paralist(parser);
			} else {
				x = 1 ;
			}
			/* Set Global Scope */
			simple_parser_icg_newoperation(parser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(parser,simple_list_getint(parser->pSimpleState->aCustomGlobalScopeStack,simple_list_getsize(parser->pSimpleState->aCustomGlobalScopeStack)));
			if ( x ) {
				/* Support using { } around the function code and using 'end' after the content */
				return simple_parser_bracesandend(parser,0,KEYWORD_END) ;
			}
			#if SIMPLE_PARSERTRACE
			if ( x == 1 ) {
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Statement  --> 'block' Identifier ([ParaList])");
			}
			#endif
			return x ;
		} else {
			parser_error(parser,PARSER_ERROR_BLOCKNAME);
			return 0 ;
		}
	}
	/* Statement --> Modules Identifier { '.' Identifier } */
	if ( simple_parser_iskeyword(parser,KEYWORD_MODULE) ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_MODULE);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Modules' Identifier{'.'identifier}");
		#endif
		if ( simple_parser_namedotname(parser) ) {
			/* Add Modules to Moduless List */
			pList = simple_parser_icg_getactiveoperation(parser);
			/* Check early definition of the modules */
			for ( x = 1 ; x <= simple_list_getsize(parser->pSimpleState->pSimpleModulessMap) ; x++ ) {
				pList3 = simple_list_getlist(parser->pSimpleState->pSimpleModulessMap,x);
				if ( strcmp(simple_list_getstring(pList3,1),simple_list_getstring(pList,2)) == 0 ) {
					parser->ClassesMap = simple_list_getlist(pList3,2);
					return 1 ;
				}
			}
			pList2 = simple_list_newlist_gc(parser->pSimpleState,parser->pSimpleState->pSimpleModulessMap);
			/* Add Modules Name */
			simple_list_addstring_gc(parser->pSimpleState,pList2,simple_list_getstring(pList,2));
			/* Add Modules Classes List */
			parser->ClassesMap = simple_list_newlist_gc(parser->pSimpleState,pList2);
			/* Support using { } around the modules code and using 'end' after the content */
			return simple_parser_bracesandend(parser,1,KEYWORD_END) ;
		} else {
			return 0 ;
		}
	}
	/* Statement --> Private */
	if ( simple_parser_iskeyword(parser,KEYWORD_PRIVATE) ) {
		simple_parser_nexttoken(parser);
		if ( parser->nClassStart == 1 ) {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_RETNULL);
			/* Change Label After Class to BlockFlag to Jump to Private */
			pList = simple_parser_icg_getoperationlist(parser,parser->nClassMark);
			simple_list_setint_gc(parser->pSimpleState,pList,1,ICO_BLOCKFLAG);
			simple_list_addint_gc(parser->pSimpleState,pList,simple_parser_icg_newlabel(parser));
			simple_parser_icg_newoperation(parser,ICO_PRIVATE);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Private'");
			#endif
			parser->nPrivateFlag = 1 ;
			return 1 ;
		} else {
			parser_error(parser,PARSER_ERROR_NOCLASSDEFINED);
			return 0 ;
		}
	}
	return simple_parser_stmt(parser) ;
}

int simple_parser_stmt ( Parser *parser )
{
	int x,nMark1,nMark2,nMark3,nStart,nEnd,nPerformanceLocations,nFlag,nLoadModules  ;
	String *pString  ;
	List *pMark,*pMark2,*pMark3,*pList2  ;
	double nNum1  ;
	char cStr[50]  ;
	char cFileName[SIMPLE_PATHSIZE]  ;
	char cCurrentDir[SIMPLE_PATHSIZE]  ;
	nPerformanceLocations = 0 ;
	nLoadModules = 0 ;
	assert(parser != NULL);
	/* Statement --> Load Literal */
	if ( simple_parser_iskeyword(parser,KEYWORD_CALL) ) {
            simple_parser_nexttoken(parser); 
		if ( simple_parser_isliteral(parser) ) {
			/* Check File in the simple/bin folder */
			strcpy(cFileName,parser->TokenText);
			if ( simple_fexists(parser->TokenText) == 0 ) {
				simple_exefolder(cFileName);
				strcat(cFileName,parser->TokenText);
				if ( simple_fexists(cFileName) == 0 ) {
					strcpy(cFileName,parser->TokenText);
				}
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_FILENAME);
			simple_parser_icg_newoperand(parser,cFileName);
			simple_parser_icg_newoperation(parser,ICO_BLOCKFLAG);
			pMark = simple_parser_icg_getactiveoperation(parser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'call' Literal");
			#endif
			/* No package at the start of the file */
			parser->ClassesMap = parser->pSimpleState->pSimpleClassesMap ;
			/* Save the Current Directory */
			simple_currentdir(cCurrentDir);
			/* Read The File */
			x = simple_scanner_readfile(parser->pSimpleState,cFileName);
			/* Restore the Current Directory */
			simple_chdir(cCurrentDir);
			/*
			**  Generate Code
			**  Return NULL
			*/
			simple_parser_icg_newoperation(parser,ICO_RETNULL);
			nMark1 = simple_parser_icg_newlabel(parser);
			simple_parser_icg_addoperandint(parser,pMark,nMark1);
			/* Set Active File */
			simple_parser_icg_newoperation(parser,ICO_FILENAME);
			simple_parser_icg_newoperand(parser,simple_list_getstring(parser->pSimpleState->pSimpleFilesStack,simple_list_getsize(parser->pSimpleState->pSimpleFilesStack)));
			simple_parser_icg_newoperation(parser,ICO_FREESTACK);
			simple_parser_nexttoken(parser); 
                        /**if (isPointer(parser)) {
                            return loadPackage(parser);
                        }**/
			return x ;
		} else {
                    /* Generate Code */
                    simple_parser_icg_newoperation(parser,ICO_IMPORT);
                    #if SIMPLE_PARSERTRACE
                    SIMPLE_STATE_CHECKPRINTRULES

                    puts("Rule : Statement  --> 'Import' Identifier{'.'identifier}");
                    #endif
                    return simple_parser_namedotname(parser) ;
                } 
		return 0 ;
	}
	/* Statement --> display Expr */
	if ( simple_parser_iskeyword(parser,KEYWORD_DISPLAY)) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_USEDISPLAYBLOCKTION
		/* Generate code to use the display function */
		simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
		simple_parser_icg_newoperand(parser,"simplevm_display");
		/* Parameters */
		nFlag = parser->nAssignmentFlag ;
		parser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(parser);
		parser->nAssignmentFlag = nFlag ;
		simple_parser_icg_newoperation(parser,ICO_CALL);
		simple_parser_icg_newoperandint(parser,0);
		simple_parser_icg_newoperation(parser,ICO_NOOP);
		simple_parser_icg_newoperation(parser,ICO_FREESTACK);
		#else
		/*
		**  Generate code using the display Command Instruction 
		**  Generate Code 
		*/
		simple_parser_icg_newoperation(parser,ICO_BLOCKEXE);
		parser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(parser);
		parser->nAssignmentFlag = 1 ;
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_DISPLAY);
		#endif
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'See' Expr");
		#endif
		return x ;
	}
	/* Statement --> ? Expr */
	if ( simple_parser_isoperator(parser,"?") ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_BLOCKEXE);
		parser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(parser);
		parser->nAssignmentFlag = 1 ;
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_DISPLAY);
		/* Print New Line */
		simple_parser_icg_newoperation(parser,ICO_PUSHC);
		simple_parser_icg_newoperand(parser,"\n");
		simple_parser_icg_newoperation(parser,ICO_DISPLAY);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> '?' Expr");
		#endif
		return x ;
	}
	/* Statement --> read Identifier */
	if ( simple_parser_iskeyword(parser,KEYWORD_READ) ) {
		simple_parser_nexttoken(parser);
		if ( simple_parser_isidentifier(parser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(parser,parser->TokenText);
			simple_parser_nexttoken(parser);
			x = simple_parser_mixer(parser);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'read' Identifier|ListItem|Object.Attribute");
			#endif
			#if SIMPLE_USEGIVEBLOCKTION
			/* Generate code to use the read function */
			simple_parser_icg_newoperation(parser,ICO_ASSIGNMENTPOINTER);
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"ringvm_read");
			simple_parser_icg_newoperation(parser,ICO_CALL);
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperation(parser,ICO_NOOP);
			simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperation(parser,ICO_FREESTACK);
			#else
			simple_parser_icg_newoperation(parser,ICO_GIVE);
			#endif
			return 1 ;
		} else {
			parser_error(parser,PARSER_ERROR_VARNAME);
			return 0 ;
		}
	}
	/* Statement --> for Identifier = Expr to Expr {Statement} loop  |  for Identifier in Expr {Statemen */
	if ( simple_parser_iskeyword(parser,KEYWORD_FOR) ) {
		simple_parser_nexttoken(parser); 
                //to accept the lambda/pointer -> as start of expression
                //AcceptTokenToken( parser, OP_MINUS); AcceptTokenToken( parser, OP_GREATER);
		if ( simple_parser_isidentifier(parser) ) {
			pString = simple_string_new_gc(parser->pSimpleState,parser->TokenText);
			simple_parser_nexttoken(parser);
			if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
				/*
				**  Generate Code
				**  Mark for Exit command to go to outside the loop
				*/
				simple_parser_icg_newoperation(parser,ICO_EXITMARK);
				pMark3 = simple_parser_icg_getactiveoperation(parser);
				simple_parser_icg_newoperation(parser,ICO_LOADAFIRST);
				simple_parser_icg_newoperand(parser,simple_string_get(pString));
				simple_parser_nexttoken(parser);
				parser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(parser) ) {
					/*
					**  Generate Code
					**  Before Equal ( = ) not += , -= ,... etc
					*/
					simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
					simple_parser_icg_newoperandint(parser,0);
					simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
					nMark1 = simple_parser_icg_newlabel(parser);
					simple_parser_icg_newoperation(parser,ICO_LOADAPUSHV);
					simple_parser_icg_newoperand(parser,simple_string_get(pString));
					if ( simple_parser_iskeyword(parser,KEYWORD_TO) ) {
						simple_parser_nexttoken(parser);
						parser->nAssignmentFlag = 0 ; 
						if ( simple_parser_csexpr(parser) ) {
							parser->nAssignmentFlag = 1 ;
							/* Generate Code */ 
							if ( (simple_parser_icg_getlastoperation(parser) == ICO_PUSHN) && (simple_parser_icg_newlabel(parser) == (nMark1+2)) ) {
								/*
								**  We check nMark2+2 to avoid executing next instructions when we have expr
								**  for example for x = 1 to 10+5
								*/
								nNum1 = simple_list_getdouble(parser->ActiveGenCodeList,2) ;
								simple_parser_icg_deletelastoperation(parser);
								simple_parser_icg_setlastoperation(parser,ICO_JUMPVARLENUM);
								simple_parser_icg_newoperanddouble(parser,nNum1);
								/* Add Locations Needed for Instruction change for performance */
								nPerformanceLocations = 1 ;
							} else {
								simple_parser_icg_newoperation(parser,ICO_JUMPFOR);
							}
							pMark = simple_parser_icg_getactiveoperation(parser);
							/* Step <expr> */
							x = simple_parser_step(parser,&nMark1);
							if ( x == 0 ) {
								simple_string_delete_gc(parser->pSimpleState,pString);
								return 0 ;
							} 
							#if SIMPLE_PARSERTRACE
							SIMPLE_STATE_CHECKPRINTRULES

							puts("Rule : Statement  --> 'for' Identifier '=' Expr to Expr ['step' Expr]");
							#endif
							while ( simple_parser_stmt(parser) ) {
								if ( parser->ActiveToken == parser->TokensCount ) {
									break ;
								}
							} 
							if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
								/* Generate Code */
								nMark3 = simple_parser_icg_newlabel(parser); 
								/* Increment Jump */
								simple_parser_icg_newoperation(parser,ICO_INCJUMP);
								simple_parser_icg_newoperand(parser,simple_string_get(pString));
								simple_parser_icg_newoperandint(parser,nMark1);
								/* Add Locations needed for instruction change for performance */
								simple_parser_icg_newoperandint(parser,0);
								simple_parser_icg_newoperandint(parser,0);
								nMark2 = simple_parser_icg_newlabel(parser);
								simple_parser_icg_addoperandint(parser,pMark,nMark2);
								/* Performance Locations */
								if ( nPerformanceLocations ) {
									/* Add Locations Needed for Instruction JUMPVARLENUM change for performance */
									simple_parser_icg_addoperandint(parser,pMark,0);
									simple_parser_icg_addoperandint(parser,pMark,0);
								}
								/* Set Exit Mark */
								simple_parser_icg_addoperandint(parser,pMark3,nMark2);
								/* Set Loop Mark */
								simple_parser_icg_addoperandint(parser,pMark3,nMark3);
								/* End Loop (Remove Exit Mark) */
								simple_parser_icg_newoperation(parser,ICO_POPEXITMARK);
								/* POP Step */
								simple_parser_icg_newoperation(parser,ICO_POPSTEP);
								simple_parser_nexttoken(parser);
								#if SIMPLE_PARSERTRACE
								SIMPLE_STATE_CHECKPRINTRULES

								puts("Rule : Next --> 'next'");
								#endif
								simple_string_delete_gc(parser->pSimpleState,pString);
								return 1 ;
							} else {
								parser_error(parser,PARSER_ERROR_END);
							}
						}
					}
				} 
			} else if ( simple_parser_iskeyword(parser,KEYWORD_IN) ) {
				/* Generate Code */
				sprintf( cStr , "n_sys_var_%d" , simple_parser_icg_instructionscount(parser) ) ;
				/* Mark for Exit command to go to outside the loop */
				simple_parser_icg_newoperation(parser,ICO_EXITMARK);
				pMark3 = simple_parser_icg_getactiveoperation(parser);
				simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
				simple_parser_icg_newoperand(parser,cStr);
				simple_parser_icg_newoperation(parser,ICO_PUSHN);
				simple_parser_icg_newoperanddouble(parser,1.0);
				/* Before Equal ( = ) not += , -= ,... etc */
				simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
				simple_parser_icg_newoperandint(parser,0);
				simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_newoperation(parser,ICO_LOADAPUSHV);
				simple_parser_icg_newoperand(parser,cStr);
				simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
				simple_parser_icg_newoperand(parser,"len");
				nStart = simple_parser_icg_instructionscount(parser) + 1 ;
				simple_parser_nexttoken(parser);
				parser->nAssignmentFlag = 0 ;
				if ( simple_parser_csexpr(parser) ) {
					parser->nAssignmentFlag = 1 ;
					/* Generate Code */
					nEnd = simple_parser_icg_instructionscount(parser) ;
					/* Note (nEnd-1) , -1 to remove instruction PushV (avoid error with for x in string) */
					if ( simple_parser_icg_getlastoperation(parser) == ICO_PUSHV ) {
						nEnd-- ;
					}
					simple_parser_icg_newoperation(parser,ICO_CALL);
					/* Generate 0 For Operator OverLoading */
					simple_parser_icg_newoperandint(parser,0);
					simple_parser_icg_newoperation(parser,ICO_JUMPFOR);
					pMark = simple_parser_icg_getactiveoperation(parser);
					simple_parser_icg_newoperation(parser,ICO_LOADAFIRST);
					simple_parser_icg_newoperand(parser,simple_string_get(pString));
					simple_parser_icg_duplicate(parser,nStart,nEnd);
					simple_parser_icg_newoperation(parser,ICO_LOADAPUSHV);
					simple_parser_icg_newoperand(parser,cStr);
					simple_parser_icg_newoperation(parser,ICO_LOADINDEXADDRESS);
					/* Generate 0 For Operator OverLoading */
					simple_parser_icg_newoperandint(parser,0);
					/* Item by reference */
					simple_parser_icg_newoperation(parser,ICO_SETREFERENCE);
					/* Step <expr> */
					x = simple_parser_step(parser,&nMark1);
					if ( x == 0 ) {
						simple_string_delete_gc(parser->pSimpleState,pString);
						return 0 ;
					}
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES

					puts("Rule : Statement  --> 'for' Identifier 'in' Expr  ['step' Expr]");
					#endif
					while ( simple_parser_stmt(parser) ) {
						if ( parser->ActiveToken == parser->TokensCount ) {
							break ;
						}
					}
					if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
						simple_parser_nexttoken(parser);
						/* Generate Code */
						nMark3 = simple_parser_icg_newlabel(parser);
						/* Increment Jump */
						simple_parser_icg_newoperation(parser,ICO_INCJUMP);
						simple_parser_icg_newoperand(parser,cStr);
						simple_parser_icg_newoperandint(parser,nMark1);
						/* Add Locations needed for instruction change for performance */
						simple_parser_icg_newoperandint(parser,0);
						simple_parser_icg_newoperandint(parser,0);
						nMark2 = simple_parser_icg_newlabel(parser);
						simple_parser_icg_addoperandint(parser,pMark,nMark2);
						/* Set Exit Mark */
						simple_parser_icg_addoperandint(parser,pMark3,nMark2);
						/* Set Loop Mark */
						simple_parser_icg_addoperandint(parser,pMark3,nMark3);
						/* End Loop (Remove Exit Mark) */
						simple_parser_icg_newoperation(parser,ICO_POPEXITMARK);
						/* POP Step */
						simple_parser_icg_newoperation(parser,ICO_POPSTEP);
						/* Remove Reference Value */
						simple_parser_icg_newoperation(parser,ICO_LOADAFIRST);
						simple_parser_icg_newoperand(parser,simple_string_get(pString));
						simple_parser_icg_newoperation(parser,ICO_KILLREFERENCE);
						simple_parser_icg_newoperation(parser,ICO_PUSHN);
						simple_parser_icg_newoperanddouble(parser,1.0);
						/* Before Equal ( = ) not += , -= ,... etc */
						simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
						simple_parser_icg_newoperandint(parser,0);
						simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
						#if SIMPLE_PARSERTRACE
						SIMPLE_STATE_CHECKPRINTRULES

						puts("Rule : Next --> 'Next'");
						#endif
						simple_string_delete_gc(parser->pSimpleState,pString);
						return 1 ;
					} else {
						parser_error(parser,PARSER_ERROR_END);
					}
				}
			}
			simple_string_delete_gc(parser->pSimpleState,pString);
		} 
                return 0 ;
	}
	/* Statement --> if Expr Statements done */
	if ( simple_parser_iskeyword(parser,KEYWORD_IF) ) {
		simple_parser_nexttoken(parser);
                //to accept the lambda/pointer -> as start of expression
                //AcceptTokenToken( parser, OP_MINUS); AcceptTokenToken( parser, OP_GREATER);
		parser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(parser) ) {
			parser->nAssignmentFlag = 1 ;
			/*
			**  First Condition
			**  Generate Code
			*/
			simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(parser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'if' Expr {Statement} { else if } [Else] Ok");
			#endif
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			/* Generate Code */
			pList2 = simple_list_new_gc(parser->pSimpleState,0);
			simple_parser_icg_newoperation(parser,ICO_JUMP);
			simple_list_addpointer_gc(parser->pSimpleState,pList2,simple_parser_icg_getactiveoperation(parser));
			/* { 'else if' Statements } 'else' Statements */  
			while (simple_parser_iskeyword(parser,KEYWORD_ELSEIF) ) {
				/* Generate Code */ 
				nMark1 = simple_parser_icg_newlabel(parser); 
				simple_parser_icg_addoperandint(parser,pMark,nMark1);
				simple_parser_nexttoken(parser); 
                                //to accept the lambda/pointer -> as start of expression
                                //AcceptTokenToken( parser, OP_MINUS); AcceptTokenToken( parser, OP_GREATER);
				parser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(parser) ) {
					parser->nAssignmentFlag = 1 ;
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
					pMark = simple_parser_icg_getactiveoperation(parser);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES

					puts("Rule : Else If  --> 'else if' Expr {Statement}");
					#endif
					while ( simple_parser_stmt(parser) ) {
						if ( parser->ActiveToken == parser->TokensCount ) {
							break ;
						}
					}
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_JUMP);
					simple_list_addpointer_gc(parser->pSimpleState,pList2,simple_parser_icg_getactiveoperation(parser));
				} 
			}
			if ( simple_parser_iskeyword(parser,KEYWORD_ELSE) ) {
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark1);
				pMark = NULL ;
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : Else  --> 'Else' {Statement} ");
				#endif
				while ( simple_parser_stmt(parser) ) {
					if ( parser->ActiveToken == parser->TokensCount ) {
						break ;
					}
				}
			}
			if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(parser,pMark,nMark1);
				}
				if ( simple_list_getsize(pList2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
						simple_parser_icg_addoperandint(parser,((List *) simple_list_getpointer(pList2,x)),nMark1);
					}
				}
				simple_list_delete_gc(parser->pSimpleState,pList2);
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : End  --> 'end'");
				#endif
				return 1 ;
			} else {
				parser_error(parser, PARSER_ERROR_END);
				simple_list_delete_gc(parser->pSimpleState,pList2);
			}
		}
		return 0 ;
	}
	/* Statement --> do Statements while Expr */
	if ( simple_parser_iskeyword(parser,KEYWORD_DO) ) {
		/*
		**  Generate Code
		**  Mark for Exit command to go to outsize the loop
		*/
		simple_parser_icg_newoperation(parser,ICO_EXITMARK);
		pMark3 = simple_parser_icg_getactiveoperation(parser);
		nMark1 = simple_parser_icg_newlabel(parser);
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES

		puts("Rule : Statement  --> 'do' {Statement} while");
		#endif
                accept_token_token(parser, OP_BRACEOPEN);
		while ( simple_parser_stmt(parser) ) {
			if ( parser->ActiveToken == parser->TokensCount ) {
				break ;
			}
		} accept_token_token(parser, OP_BRACECLOSE);
		if ( simple_parser_iskeyword(parser, KEYWORD_WHILE) ) {
			/* Generate Code */ 
			simple_parser_nexttoken(parser);
                        //to accept the lambda/pointer -> as start of expression
                        //AcceptTokenToken( parser, OP_MINUS); AcceptTokenToken( parser, OP_GREATER);
			parser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(parser) ) {
				/* Generate Code (Test Condition) */
				simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
				pMark = simple_parser_icg_getactiveoperation(parser);
				/* Generate Code */
				nMark3 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_newoperation(parser,ICO_JUMP);
				simple_parser_icg_newoperandint(parser,nMark1);
				nMark2 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark2);
				/* Set Exit Mark */
				simple_parser_icg_addoperandint(parser,pMark3,nMark2);
				/* Set Loop Mark */
				simple_parser_icg_addoperandint(parser,pMark3,nMark3);
				/* End Loop (Remove Exit Mark) */
				simple_parser_icg_newoperation(parser,ICO_POPEXITMARK);
				parser->nAssignmentFlag = 1 ;
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : While  --> 'while' Expr");
				#endif
				return 1 ;
			}
		} else {
			parser_error(parser,PARSER_ERROR_END);
		}
		return 0 ;
	}
        /*Statement --> while Expr Statements end */
	if ( simple_parser_iskeyword(parser, KEYWORD_WHILE) ) {
		/*
		**  Generate Code
		**  Mark for Exit command to go to outsize the loop
		*/
		simple_parser_icg_newoperation(parser,ICO_EXITMARK);
		pMark3 = simple_parser_icg_getactiveoperation(parser);
		nMark1 = simple_parser_icg_newlabel(parser);
		simple_parser_nexttoken(parser);
                //to accept the pointer -> as start of expression
                //AcceptTokenToken( parser, OP_MINUS); AcceptTokenToken( parser, OP_GREATER);
		parser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(parser) ) {
			parser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(parser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'while' Expr {Statement} end");
			#endif
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
				/* Generate Code */
				nMark3 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_newoperation(parser,ICO_JUMP);
				simple_parser_icg_newoperandint(parser,nMark1);
				nMark2 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark2);
				/* Set Exit Mark */
				simple_parser_icg_addoperandint(parser,pMark3,nMark2);
				/* Set Loop Mark */
				simple_parser_icg_addoperandint(parser,pMark3,nMark3);
				/* End Loop (Remove Exit Mark) */
				simple_parser_icg_newoperation(parser,ICO_POPEXITMARK);
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : End --> 'end'");
				#endif
				return 1 ;
			} else {
				parser_error(parser,PARSER_ERROR_END);
			}
		}
		return 0 ;
	}
        /* Statement --> Return Expr */
	if ( simple_parser_iskeyword(parser, KEYWORD_RETURN) ) {
		simple_parser_nexttoken(parser);
		x = 1 ;
		if ( simple_parser_isendline(parser) == 0 ) {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_FREELOADASCOPE);
			simple_parser_icg_newoperation(parser,ICO_BLOCKEXE);
			parser->nAssignmentFlag = 0 ;
			x = simple_parser_expr(parser);
			parser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_ENDBLOCKEXE);
			if ( x ) {
				simple_parser_icg_newoperation(parser,ICO_RETURN);
			}
			else {
				simple_parser_icg_newoperation(parser,ICO_RETNULL);
			}
		} else {
			/*
			**  Generate Code
			**  Return NULL
			*/
			simple_parser_icg_newoperation(parser,ICO_RETNULL);
		}
		#if SIMPLE_PARSERTRACE
		if ( x == 1 ) {
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'return'");
		}
		#endif
		return x ;
	}
	/* Statement --> try {Statement} catch {Statement} finally */
	if ( simple_parser_iskeyword(parser,KEYWORD_TRY) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
			simple_parser_nexttoken(parser);
			parser->nControlStructureBrace++ ;
		}
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_TRY);
		pMark = simple_parser_icg_getactiveoperation(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Try' {Statement} Catch Done");
		#endif
		while ( simple_parser_stmt(parser) ) {
			if ( parser->ActiveToken == parser->TokensCount ) {
				break ;
			}
		}
		if ( simple_parser_iskeyword(parser,KEYWORD_CATCH) ) {
			simple_parser_nexttoken(parser);
			/*
			**  Generate Code 
			**  Jump from end of try block to label after done 
			*/
			simple_parser_icg_newoperation(parser,ICO_JUMP);
			pMark2 = simple_parser_icg_getactiveoperation(parser);
			nMark1 = simple_parser_icg_newlabel(parser);
			simple_parser_icg_addoperandint(parser,pMark,nMark1);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Catch --> 'Catch' {Statement}");
			#endif
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			if ( simple_parser_iskeyword(parser,KEYWORD_FINALLY) || simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Done --> 'Done'");
				#endif
				simple_parser_nexttoken(parser);
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_JUMP);
				pMark3 = simple_parser_icg_getactiveoperation(parser);
				nMark2 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark2,nMark2);
				simple_parser_icg_newoperation(parser,ICO_DONE);
				nMark3 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark3,nMark3);
				return 1 ;
			} else {
				parser_error(parser,PARSER_ERROR_END);
			}
		} else {
			parser_error(parser,PARSER_ERROR_NOCATCH);
		}
	}
	/* Statement --> __exit (Close the Program) */
	if ( simple_parser_iskeyword(parser,KEYWORD_EXIT) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES

		puts("Rule : Statement  --> '__exit' ");
		#endif
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_EXITPROGRAM);
		return 1 ;
	}
	/* Statement --> break (Go to outside the loop) */
	if ( simple_parser_iskeyword(parser,KEYWORD_BREAK) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES

		puts("Rule : Statement  --> 'break' ");
		#endif
		/* Check Number  (Exit from more than one loop) */
		if ( simple_parser_isnumber(parser) || simple_parser_isidentifier(parser) ) {
			if ( ! simple_parser_expr(parser) ) {
				return 0 ;
			}
		}
		else {
			simple_parser_icg_newoperation(parser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(parser,1.0);
		}
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_EXIT);
		return 1 ;
	}
	/* Statement --> continue (Continue) */
	if ( simple_parser_iskeyword(parser,KEYWORD_CONTINUE) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES

		puts("Rule : Statement  --> 'continue'");
		#endif
		/* Check Number  (Continue from more than one loop) */
		if ( simple_parser_isnumber(parser) || simple_parser_isidentifier(parser) ) {
			if ( ! simple_parser_expr(parser) ) {
				return 0 ;
			}
		}
		else {
			simple_parser_icg_newoperation(parser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(parser,1.0);
		}
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_LOOP);
		return 1 ;
	}
	/* Statement --> Switch  Expr { ON|CASE Expr {Statement} } OFF */
	if ( simple_parser_iskeyword(parser,KEYWORD_SWITCH) ) {
		simple_parser_nexttoken(parser);
		parser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(parser) ) {
			parser->nAssignmentFlag = 1 ;
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'switch' Expr {case} [Other] default");
			#endif
			SIMPLE_PARSER_IGNORENEWLINE ;
			/* ON|CASE Statements */
			pList2 = simple_list_new_gc(parser->pSimpleState,0);
			pMark = NULL ;
			while (simple_parser_iskeyword(parser,KEYWORD_CASE) ) {
				simple_parser_nexttoken(parser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(parser,pMark,nMark1);
				}
				simple_parser_icg_newoperation(parser,ICO_DUPLICATE);
				parser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(parser) ) {
					parser->nAssignmentFlag = 1 ;
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_EQUAL);
					simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
					pMark = simple_parser_icg_getactiveoperation(parser);
					simple_parser_icg_newoperation(parser,ICO_FREESTACK);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES

					puts("Rule : CASE --> 'case' Expr {Statement}");
					#endif
					while ( simple_parser_stmt(parser) ) {
						if ( parser->ActiveToken == parser->TokensCount ) {
							break ;
						}
					}
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_JUMP);
					simple_list_addpointer_gc(parser->pSimpleState,pList2,simple_parser_icg_getactiveoperation(parser));
				}
			}
			/* default */
			if ( simple_parser_iskeyword(parser,KEYWORD_DEFAULT) ) {
				simple_parser_nexttoken(parser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(parser,pMark,nMark1);
					pMark = NULL ;
				}
				simple_parser_icg_newoperation(parser,ICO_FREESTACK);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : DEFAULT --> 'default' {Statement}");
				#endif
				while ( simple_parser_stmt(parser) ) {
					if ( parser->ActiveToken == parser->TokensCount ) {
						break ;
					}
				}
			}
			/* end */
			if (simple_parser_csbraceend(parser) || simple_parser_iskeyword(parser,KEYWORD_END) ) {
				simple_parser_nexttoken(parser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(parser,pMark,nMark1);
				}
				if ( simple_list_getsize(pList2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
						simple_parser_icg_addoperandint(parser,((List *) simple_list_getpointer(pList2,x)),nMark1);
					}
				}
				simple_list_delete_gc(parser->pSimpleState,pList2);
				simple_parser_icg_newoperation(parser,ICO_FREESTACK);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : End --> 'end'");
				#endif
				return 1 ;
			} else {
				parser_error(parser,PARSER_ERROR_END);
			}
		} else {
			parser_error(parser,PARSER_ERROR_SWITCHEXPR);
		}
	}
	/* Statement --> epslion */
	if ( simple_parser_epslion(parser) ) {
		return 1 ;
	}
	/* Statement --> Expr */
	if ( simple_parser_expr(parser) ) {
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> Expr ");
		#endif
		/*
		**  Generate Code 
		**  Call expreval() if we are inside { } 
		*/
		if ( parser->nBraceFlag ) {
			/* if ismethod(self,"braceexpreval") braceexpreval() ok */
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"ismethod");
			simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(parser,"self");
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			simple_parser_icg_newoperation(parser,ICO_PUSHC);
			simple_parser_icg_newoperand(parser,"braceexpreval");
			simple_parser_icg_newoperation(parser,ICO_CALL);
			simple_parser_icg_newoperation(parser,ICO_NOOP);
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			/* Jump */
			simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(parser);
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"braceexpreval");
			/* Duplicate Stack */
			simple_parser_icg_newoperation(parser,ICO_DUPLICATE);
			simple_parser_icg_newoperation(parser,ICO_CALL);
			simple_parser_icg_newoperation(parser,ICO_NOOP);
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			simple_parser_icg_newoperation(parser,ICO_FREESTACK);
			nMark1 = simple_parser_icg_newlabel(parser);
			simple_parser_icg_addoperandint(parser,pMark,nMark1);
		}
		simple_parser_icg_newoperation(parser,ICO_FREESTACK);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_paralist ( Parser *parser )
{
	int nStart  ;
	const char *cToken  ;
	/* Check ( */
	nStart = 0 ;
	if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
		simple_parser_nexttoken(parser);
		nStart = 1 ;
	}
	/* ParaList --> Epslion */
	if ( simple_parser_isendline(parser) || (nStart && simple_parser_isoperator2(parser,OP_FCLOSE) ) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : ParaList --> Epslion ");
		#endif
		return 1 ;
	}
	/* ParaList --> [ Identifier { , Identifier }  ] */
	if ( simple_parser_isidentifier(parser) ) {
		cToken = parser->TokenText ;
		simple_parser_nexttoken(parser);
		/* Support Type Identifiter */
		if ( nStart && simple_parser_isidentifier(parser) ) {
			cToken = parser->TokenText ;
			simple_parser_nexttoken(parser);
		}
		/* Generate Code */
		simple_parser_icg_newoperand(parser,cToken);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : ParaList --> Identifier {',' Identifier}");
		#endif
		while ( simple_parser_isoperator2(parser,OP_COMMA) ) {
			simple_parser_nexttoken(parser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			if ( simple_parser_isidentifier(parser) ) {
				cToken = parser->TokenText ;
				simple_parser_nexttoken(parser);
				/* Support Type Identifiter */
				if ( nStart && simple_parser_isidentifier(parser) ) {
					cToken = parser->TokenText ;
					simple_parser_nexttoken(parser);
				}
				/* Generate Code */
				simple_parser_icg_newoperand(parser,cToken);
			} else {
				parser_error(parser,PARSER_ERROR_PARALIST);
				return 0 ;
			}
		}
		if ( nStart && simple_parser_isoperator2(parser,OP_FCLOSE) ) {
			simple_parser_nexttoken(parser);
		}
		return 1 ;
	} else {
		parser_error(parser,PARSER_ERROR_PARALIST);
		return 0 ;
	}
}

int simple_parser_list ( Parser *parser )
{
	/* "["  [ Expr { , Expr } ] "]" */
	if ( simple_parser_isoperator2(parser,OP_LOPEN) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_LISTSTART);
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(parser,OP_LCLOSE) ) {
			simple_parser_nexttoken(parser);
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_LISTEND);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : List --> '[' Expr { ',' Expr } ']' ");
			#endif
			return 1 ;
		}
		while ( 1 ) {
			parser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(parser) ) {
				/* Generate Code */
				if ( simple_parser_icg_getlastoperation(parser) != ICO_LISTEND ) {
					simple_parser_icg_newoperation(parser,ICO_LISTITEM);
				}
				parser->nAssignmentFlag = 1 ;
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(parser,OP_COMMA) ) {
					simple_parser_nexttoken(parser);
				}
				else if ( simple_parser_isoperator2(parser,OP_LCLOSE) ) {
					simple_parser_nexttoken(parser);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : List --> '[' Expr { ',' Expr } ']' ");
					#endif
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_LISTEND);
					return 1 ;
				} else {
					parser_error(parser,PARSER_ERROR_LISTITEM);
					return 0 ;
				}
			} else {
				parser_error(parser,PARSER_ERROR_LISTITEM);
				return 0 ;
			}
			SIMPLE_PARSER_IGNORENEWLINE ;
		}
	}
	return 0 ;
}

int simple_parser_epslion ( Parser *parser )
{
	if ( simple_parser_isendline(parser) ) {
		/* Generate Code */
		if ( parser->pSimpleState->lNoLineNumber == 0 ) {
			simple_parser_icg_newoperation(parser,ICO_NEWLINE);
			simple_parser_icg_newoperandint(parser,atoi(parser->TokenText));
		}
		parser->nLineNumber = atoi(parser->TokenText) ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		printf( "\nLine %d \n",parser->nLineNumber ) ;
		#endif
		if ( simple_parser_nexttoken(parser) ) {
			return 1 ;
		}
		if ( parser->TokensCount == 1 ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_passepslion ( Parser *parser )
{
	/* used after factor - identifier to allow {  } in new line */
	if ( simple_parser_isendline(parser) ) {
		parser->nLineNumber = atoi(parser->TokenText) ;
		if ( simple_parser_nexttoken(parser) ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_namedotname ( Parser *parser )
{
	String *pString  ;
	if ( simple_parser_isidentifier(parser) ) {
		/* Get Token Text */
		pString = simple_string_new_gc(parser->pSimpleState,parser->TokenText);
		simple_parser_nexttoken(parser);
		while ( simple_parser_isoperator2(parser,OP_DOT) ) {
			simple_parser_nexttoken(parser);
			simple_string_add_gc(parser->pSimpleState,pString,".");
			if ( simple_parser_isidentifier(parser) ) {
				simple_string_add_gc(parser->pSimpleState,pString,parser->TokenText);
				simple_parser_nexttoken(parser);
			} else {
				parser_error(parser,PARSER_ERROR_MODULENAME);
				simple_string_delete(pString);
				return 0 ;
			}
		}
		/* Generate Code */
		simple_parser_icg_newoperand(parser,simple_string_get(pString));
		simple_string_delete_gc(parser->pSimpleState,pString);
		return 1 ;
	} else {
		parser_error(parser,PARSER_ERROR_MODULENAME);
		return 0 ;
	}
}

int simple_parser_step ( Parser *parser,int *nMark1 )
{
	/* Step <expr> */
	parser->nInsertFlag = 1 ;
	parser->nInsertCounter = *nMark1-1 ;
	if ( simple_parser_iskeyword(parser,KEYWORD_STEP) ) {
		simple_parser_nexttoken(parser);
		parser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(parser) ) {
			parser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_STEPNUMBER);
		} else {
			return 0 ;
		}
	} else {
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_PUSHN);
		simple_parser_icg_newoperanddouble(parser,1.0);
		simple_parser_icg_newoperation(parser,ICO_STEPNUMBER);
	}
	*nMark1 = parser->nInsertCounter + 1 ;
	parser->nInsertFlag = 0 ;
	parser->nInsertCounter = 0 ;
	return 1 ;
}

int simple_parser_csexpr ( Parser *parser )
{
	int nOutput  ;
	parser->nControlStructureExpr = 1 ;
	nOutput = simple_parser_expr(parser);
	parser->nControlStructureExpr = 0 ;
	SIMPLE_PARSER_IGNORENEWLINE ;
	if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
		simple_parser_nexttoken(parser);
		parser->nControlStructureBrace++ ;
	}
	return nOutput ;
}

int simple_parser_csbraceend ( Parser *parser )
{
	if ( (parser->nControlStructureBrace >= 1) && simple_parser_isoperator2(parser,OP_BRACECLOSE) ) {
		parser->nControlStructureBrace-- ;
		return 1 ;
	}
	return 0 ;
}

int simple_parser_bracesandend ( Parser *parser,int lClass,SCANNER_KEYWORD nKeyword )
{
	/*
	**  This function is used to support braces { } around moduless/classes/functions 
	**  Also support using 'end' after moduless/classes/functions 
	**  IF The Parameter : lClass = True we call simple_parser_class() instead of simple_parser_stmt() 
	**  When we support braces { } 
	**  But the support for 'end' always uses simple_parser_class() 
	**  Support using { } 
	*/
	SIMPLE_PARSER_IGNORENEWLINE ;
	if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
		simple_parser_nexttoken(parser);
		if ( lClass ) {
			while ( simple_parser_class(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
		}
		else {
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
		}
		if ( simple_parser_isoperator2(parser,OP_BRACECLOSE) ) {
			simple_parser_nexttoken(parser);
			return 1 ;
		}
		return 0 ;
	}
	/* Support using End */
	while ( simple_parser_class(parser) ) {
		if ( parser->ActiveToken == parser->TokensCount ) {
			break ;
		}
	}
	if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_iskeyword(parser,nKeyword) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : End --> 'End'");
		#endif
	}
	return 1 ;
}
