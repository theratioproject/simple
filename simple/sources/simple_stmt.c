
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: Azeez Adewale
 *
 * Created on July 10, 2017, 1:10 PM
 */


#include "../include/simple.h"
/* Grammar */

int simple_parser_class ( Parser *parser )
{
	List *list,*list2,*list3  ;
	int x  ;
	String *string, *blockid  ;
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
			list = parser->ClassesMap ;
			/* Check Class Redefinition */
			if ( simple_list_getsize(list) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(list,x),1),parser->TokenText) == 0 ) {
						parser_error(parser,PARSER_ERROR_CLASSREDEFINE);
						return 0 ;
					}
				}
			}
			list = simple_list_newlist_gc(parser->sState,list);
			simple_list_addstring_gc(parser->sState,list,parser->TokenText);
			simple_list_addint_gc(parser->sState,list,simple_list_getsize(parser->GenCode));
			/* Add class pointer to generated code */
			simple_parser_icg_newoperandpointer(parser,list);
			simple_parser_nexttoken(parser);
			/* [From Identifer] */
			if ( simple_parser_isoperator2(parser,OP_RANGE) || simple_parser_isoperator2(parser,OP_LESS) ) {
				simple_parser_nexttoken(parser);
				if ( simple_parser_namedotname(parser) ) {
					/* Generate Code */
					list3 = simple_parser_icg_getactiveoperation(parser);
					/* Check if parent class name = subclass name */
					if ( strcmp(simple_list_getstring(list,1),simple_list_getstring(list3,4)) == 0 ) {
						parser_error(parser,PARSER_ERROR_PARENTLIKESUBCLASS);
						return 0 ;
					}
					/* Set Parent Class Name in Classes Map */
					simple_list_addstring_gc(parser->sState,list,simple_list_getstring(list3,4));
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
				simple_list_addstring_gc(parser->sState,list,"");
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Statement  --> 'Class' Identifier ");
				#endif
			}
			/* Add Method/Blocks List to Class in Class Table */
			list2 = simple_list_newlist_gc(parser->sState,list);
			/* Add Flag ( IS Parent Class information collected  ) */
			simple_list_addint_gc(parser->sState,list,0);
			/* Set Active Blocks List to be Class Methods */
			parser->BlocksMap = list2 ;
			/* Make class visible using ModulesName.ClassName if we have modules */
			if ( parser->ClassesMap != parser->sState->classes_map ) {
				/* Get Modules Name */
				list3 = simple_list_getlist(parser->sState->modules_map,simple_list_getsize(parser->sState->modules_map));
				string = simple_string_new_gc(parser->sState,simple_list_getstring(list3,1));
				/* Add pointer to the Modules in the Class List */
				simple_list_addpointer_gc(parser->sState,list,list3);
				/* Add List point to General Classes point to the class in the modules */
				list2 = simple_list_newlist_gc(parser->sState,parser->sState->classes_map);
				simple_list_addstring_gc(parser->sState,list2,"");
				simple_list_addpointer_gc(parser->sState,list2,list);
				/* Ignore Adding Pointer to File Name */
				simple_list_addpointer_gc(parser->sState,list2,NULL);
				/* Add Class Name to Modules Name */
				simple_string_add_gc(parser->sState,string,".");
				simple_string_add_gc(parser->sState,string,simple_list_getstring(list,1));
				simple_list_setstring_gc(parser->sState,list2,1,simple_string_get(string));
				simple_string_delete_gc(parser->sState,string);
			} else {
				/* Add pointer to the Modules in the Class List */
				simple_list_addpointer_gc(parser->sState,list,NULL);
			}
			parser->nClassStart = 1 ;
			/* Create label to be used by Private */
			parser->nClassMark = simple_parser_icg_newlabel2(parser);
			parser->nPrivateFlag = 0 ;
			/* Generate Code - Set The File Name */
			simple_parser_icg_newoperation(parser,ICO_FILENAME);
			simple_parser_icg_newoperand(parser,simple_list_getstring(parser->sState->files_stack,simple_list_getsize(parser->sState->files_stack)));
			/* Set Global Scope */
			simple_parser_icg_newoperation(parser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(parser,simple_list_getint(parser->sState->aCustomGlobalScopeStack,simple_list_getsize(parser->sState->aCustomGlobalScopeStack)));
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
			/* Add block to Blocks Table */
			list2 = parser->BlocksMap ;
			/* Check Block Redefinition */
			if ( simple_list_getsize(list2) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(list2) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(list2,x),1),parser->TokenText) == 0 ) {
						parser_error(parser,PARSER_ERROR_BLOCKREDEFINE);
						return 0 ; 
					}
				}
			}
			blockid = simple_string_new_gc(parser->sState,parser->TokenText);
			simple_parser_nexttoken(parser);
			if ( simple_parser_isidentifier(parser) || simple_parser_isoperator2(parser,OP_FOPEN) ) {
				x = simple_parser_paralist(parser);
			} else {
				x = 1 ;
			}
			//printf("param count : %i\n",x);
			x = 1 ;
			//add block to stack
			list2 = simple_list_newlist_gc(parser->sState,list2);
			simple_list_addstring_gc(parser->sState,list2,blockid->str);
			simple_list_addint_gc(parser->sState,list2,simple_list_getsize(parser->GenCode));
			simple_list_addstring_gc(parser->sState,list2,simple_list_getstring(parser->sState->files_stack,simple_list_getsize(parser->sState->files_stack)));
			if ( parser->nClassStart == 1 ) {
				simple_list_addint_gc(parser->sState,list2,parser->nPrivateFlag);
			} else {
				simple_list_addint_gc(parser->sState,list2,0);
			}
			//end add block to stack
			
			/* Set Global Scope */
			simple_parser_icg_newoperation(parser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(parser,simple_list_getint(parser->sState->aCustomGlobalScopeStack,simple_list_getsize(parser->sState->aCustomGlobalScopeStack)));
			if ( x ) {
				/* Support using { } around the block code and using 'end' after the content */
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
			list = simple_parser_icg_getactiveoperation(parser);
			/* Check early definition of the modules */
			for ( x = 1 ; x <= simple_list_getsize(parser->sState->modules_map) ; x++ ) {
				list3 = simple_list_getlist(parser->sState->modules_map,x);
				if ( strcmp(simple_list_getstring(list3,1),simple_list_getstring(list,2)) == 0 ) {
					parser->ClassesMap = simple_list_getlist(list3,2);
					return 1 ;
				}
			}
			list2 = simple_list_newlist_gc(parser->sState,parser->sState->modules_map);
			/* Add Modules Name */
			simple_list_addstring_gc(parser->sState,list2,simple_list_getstring(list,2));
			/* Add Modules Classes List */
			parser->ClassesMap = simple_list_newlist_gc(parser->sState,list2);
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
			list = simple_parser_icg_getoperationlist(parser,parser->nClassMark);
			simple_list_setint_gc(parser->sState,list,1,ICO_BLOCKFLAG);
			simple_list_addint_gc(parser->sState,list,simple_parser_icg_newlabel(parser));
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
	
	/* Statement --> final */
	if ( simple_parser_iskeyword(parser,KEYWORD_FINAL) ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		/* Change Label After Class to BlockFlag to Jump to Final */
		simple_parser_icg_newoperation(parser,ICO_FINAL);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Final'");
		#endif
		return 1 ;
	}
	return simple_parser_stmt(parser) ;
}

int simple_parser_stmt ( Parser *parser )
{
	int x,nMark1,nMark2,nMark3,nStart,nEnd,nPerformanceLocations,nFlag,nLoadModules,call_type,is_last_module  ;
	String *string, *module_name, *main_module_name ;  ;
	List *pMark,*pMark2,*pMark3,*list2  ;
	double nNum1  ;
	char cStr[50]  ;
	char file_name[SIMPLE_PATHSIZE]  ;
	char cCurrentDir[SIMPLE_PATHSIZE]  ;
	nPerformanceLocations = 0 ;
	nLoadModules = 0 ;
	call_type = 0;
	is_last_module = 0;
	assert(parser != NULL);
	/* Statement --> Load Literal */
	if ( simple_parser_iskeyword(parser,KEYWORD_FROM) ) {
            simple_parser_nexttoken(parser); 
		if ( simple_parser_isliteral(parser) || simple_parser_isidentifier(parser)) {
			if (simple_parser_isliteral(parser)) {
				strcpy(file_name,parser->TokenText);
			} else {
				module_name = simple_string_new_gc(parser->sState,parser->TokenText);
				main_module_name = simple_string_new_gc(parser->sState,parser->TokenText);
				simple_parser_nexttoken(parser);
				while ( simple_parser_isoperator2(parser,OP_DOT) || simple_parser_isoperator(parser, "/") ) {
					simple_parser_nexttoken(parser);
					simple_string_add_gc(parser->sState,module_name,"/");
					if ( simple_parser_isidentifier(parser) ) {
						simple_string_add_gc(parser->sState,module_name,parser->TokenText);
						simple_parser_nexttoken(parser);
						if (simple_parser_isoperator2(parser,OP_DOT) || simple_parser_isoperator(parser, "/")) {
							simple_parser_previoustoken (parser);
							simple_string_add_gc(parser->sState,main_module_name,".");
							simple_string_add_gc(parser->sState,main_module_name,parser->TokenText);
							simple_parser_nexttoken(parser);
						} 
					} else {
						parser_error(parser,PARSER_ERROR_MODULENAME);
						simple_string_delete(module_name);
						simple_string_delete(main_module_name);
						return 0;
					}
				}
				simple_string_add_gc(parser->sState,module_name,".sim");
				strcpy(file_name,module_name->str);
				call_type = 1 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_FILENAME);
			simple_parser_icg_newoperand(parser,file_name);
			simple_parser_icg_newoperation(parser,ICO_BLOCKFLAG);
			pMark = simple_parser_icg_getactiveoperation(parser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'call' Literal|module");
			#endif
			/* No package at the start of the file */
			parser->ClassesMap = parser->sState->classes_map ;
			/* Save the Current Directory */
			simple_currentdir(cCurrentDir);
			/* Read The File */
			x = simple_scanner_readfile(parser->sState,file_name);
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
			simple_parser_icg_newoperand(parser,simple_list_getstring(parser->sState->files_stack,simple_list_getsize(parser->sState->files_stack)));
			simple_parser_icg_newoperation(parser,ICO_FREESTACK);
			if (call_type == 1) {
				simple_parser_icg_newoperation(parser,ICO_IMPORT);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : Statement  --> '?'['@'] Identifier{'.'identifier}");
				#endif
				simple_parser_icg_newoperand(parser,simple_string_get(main_module_name));
				simple_string_delete_gc(parser->sState,main_module_name);
				return 1;
			}
			return x ;
		} else {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_IMPORT);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES

			puts("Rule : Statement  --> 'call' Identifier{'.'identifier}");
			#endif
			return simple_parser_namedotname(parser) ;
		} 
		return 0 ;
	}
	/* Statement --> display Expr */
	if ( simple_parser_iskeyword(parser,KEYWORD_DISPLAY)) {
		simple_parser_nexttoken(parser); 
		#if SIMPLE_USEDISPLAYBLOCK
		/* Generate code to use the display block */
		simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
		simple_parser_icg_newoperand(parser,"display");
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
		
		puts("Rule : Statement  --> 'display' Expr");
		#endif
		return x ;
	}
	/* Statement --> @ Expr */
	/* This is most useful for web development to avoid so much typing*/
	if ( simple_parser_isoperator(parser,"@") ) {
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
		
		puts("Rule : Statement  --> '@' Expr");
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
			#if SIMPLE_USEREADBLOCK
			/* Generate code to use the read block */
			simple_parser_icg_newoperation(parser,ICO_ASSIGNMENTPOINTER);
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"read");
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
			string = simple_string_new_gc(parser->sState,parser->TokenText);
			simple_parser_nexttoken(parser);
			if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
				/*
				**  Generate Code
				**  Mark for Exit command to go to outside the loop
				*/
				simple_parser_icg_newoperation(parser,ICO_EXITMARK);
				pMark3 = simple_parser_icg_getactiveoperation(parser);
				simple_parser_icg_newoperation(parser,ICO_LOADAFIRST);
				simple_parser_icg_newoperand(parser,simple_string_get(string));
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
					simple_parser_icg_newoperand(parser,simple_string_get(string));
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
								simple_string_delete_gc(parser->sState,string);
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
								simple_parser_icg_newoperand(parser,simple_string_get(string));
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
								simple_string_delete_gc(parser->sState,string);
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
				simple_parser_icg_newoperanddouble(parser,0);
				/* Before Equal ( = ) not += , -= ,... etc */
				simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
				simple_parser_icg_newoperandint(parser,0);
				simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_newoperation(parser,ICO_LOADAPUSHV);
				simple_parser_icg_newoperand(parser,cStr);
				simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
				simple_parser_icg_newoperand(parser,"LengthOf");
				nStart = simple_parser_icg_instructionscount(parser) + 1 ;
				simple_parser_nexttoken(parser);
				parser->nAssignmentFlag = 0 ;
				if ( simple_parser_csexpr(parser) ) {
					parser->nAssignmentFlag = 1 ;
					/* Generate Code */
					nEnd = simple_parser_icg_instructionscount(parser) ;
					simple_parser_icg_newoperation(parser,ICO_CALL);
					/* Generate 0 For Operator OverLoading */
					simple_parser_icg_newoperandint(parser,0);
					simple_parser_icg_newoperation(parser,ICO_MINUSMINUS);
					simple_parser_icg_newoperation(parser,ICO_JUMPFOR);
					pMark = simple_parser_icg_getactiveoperation(parser);
					simple_parser_icg_newoperation(parser,ICO_LOADAFIRST);
					simple_parser_icg_newoperand(parser,simple_string_get(string));
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
						simple_string_delete_gc(parser->sState,string);
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
						simple_parser_icg_newoperand(parser,simple_string_get(string));
						simple_parser_icg_newoperation(parser,ICO_KILLREFERENCE);
						simple_parser_icg_newoperation(parser,ICO_PUSHN);
						simple_parser_icg_newoperanddouble(parser,1.0);
						/* Before Equal ( = ) not += , -= ,... etc */
						simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
						simple_parser_icg_newoperandint(parser,0);
						simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
						#if SIMPLE_PARSERTRACE
						SIMPLE_STATE_CHECKPRINTRULES

						puts("Rule :End --> 'End'");
						#endif
						simple_string_delete_gc(parser->sState,string);
						return 1 ;
					} else {
						parser_error(parser,PARSER_ERROR_END);
					}
				}
			}
			simple_string_delete_gc(parser->sState,string);
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

			puts("Rule : Statement  --> 'if' expr {statement} { elif } [else] }");
			#endif
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			/* Generate Code */
			list2 = simple_list_new_gc(parser->sState,0);
			simple_parser_icg_newoperation(parser,ICO_JUMP);
			simple_list_addpointer_gc(parser->sState,list2,simple_parser_icg_getactiveoperation(parser));
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

					puts("Rule : elif  --> 'elif' expr {statement}");
					#endif
					while ( simple_parser_stmt(parser) ) {
						if ( parser->ActiveToken == parser->TokensCount ) {
							break ;
						}
					}
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_JUMP);
					simple_list_addpointer_gc(parser->sState,list2,simple_parser_icg_getactiveoperation(parser));
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

				puts("Rule : Else  --> 'else' {statement} ");
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
				if ( simple_list_getsize(list2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(list2) ; x++ ) {
						simple_parser_icg_addoperandint(parser,((List *) simple_list_getpointer(list2,x)),nMark1);
					}
				}
				simple_list_delete_gc(parser->sState,list2);
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES

				puts("Rule : End  --> 'end'");
				#endif
				return 1 ;
			} else {
				parser_error(parser, PARSER_ERROR_END);
				simple_list_delete_gc(parser->sState,list2);
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
	/* Statement --> try {Statement} catch {Statement} */
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
		
		puts("Rule : Statement  --> 'Try' {Statement} Catch ");
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
			**  Jump from end of try block to label after }
			*/
			simple_parser_icg_newoperation(parser,ICO_JUMP);
			pMark2 = simple_parser_icg_getactiveoperation(parser);
			nMark1 = simple_parser_icg_newlabel(parser);
			simple_parser_icg_addoperandint(parser,pMark,nMark1);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Catch --> 'catch' {Statement}");
			#endif
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			if ( simple_parser_iskeyword(parser,KEYWORD_END) || simple_parser_csbraceend(parser) ) {
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : end --> 'end'");
				#endif
				simple_parser_nexttoken(parser);
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_JUMP);
				pMark3 = simple_parser_icg_getactiveoperation(parser);
				nMark2 = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark2,nMark2);
				simple_parser_icg_newoperation(parser,ICO_FREE_TRY);
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
	/* Statement --> __exit__ (Close the Program) */
	if ( simple_parser_iskeyword(parser,KEYWORD_EXIT) ) {
		simple_parser_nexttoken(parser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES

		puts("Rule : Statement  --> '__exit__' ");
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

			puts("Rule : Statement  --> 'switch' Expr {case} [other] default");
			#endif
			SIMPLE_PARSER_IGNORENEWLINE ;
			/* ON|CASE Statements */
			list2 = simple_list_new_gc(parser->sState,0);
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
					simple_list_addpointer_gc(parser->sState,list2,simple_parser_icg_getactiveoperation(parser));
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
				if ( simple_list_getsize(list2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(list2) ; x++ ) {
						simple_parser_icg_addoperandint(parser,((List *) simple_list_getpointer(list2,x)),nMark1);
					}
				}
				simple_list_delete_gc(parser->sState,list2);
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
	/* Statement --> Import Identifier { '.' Identifier } */
	if ( simple_parser_iskeyword(parser,KEYWORD_IMPORT) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_IMPORT);
		#if RING_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Import' Identifier{'.'identifier}");
		#endif
		return simple_parser_namedotname(parser) ;
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
		**  Call exprEval() if we are inside { } 
		*/
		if ( parser->nBraceFlag ) {
			/* if isblock(self,"exprEval") exprEval() end */
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"HasBlock");
			simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(parser,"self");
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			simple_parser_icg_newoperation(parser,ICO_PUSHC);
			simple_parser_icg_newoperand(parser,"ExprEval");
			simple_parser_icg_newoperation(parser,ICO_CALL);
			simple_parser_icg_newoperation(parser,ICO_NOOP);
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			/* Jump */
			simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(parser);
			simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
			simple_parser_icg_newoperand(parser,"ExprEval");
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
	int nStart, param_count, is_variadic, x  ;
	const char *cToken  ;
	/* Check ( */
	nStart = 0 ;
	param_count = 0 ;
	is_variadic = 0 ;
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
		return param_count ;
	}
	/* ParaList --> [ Identifier { , Identifier }  ] */ 
	if ( simple_parser_isidentifier(parser)) { 
		cToken = parser->TokenText ;
		simple_parser_nexttoken(parser); 
		/* Support Type Identifiter */
		if ( nStart && simple_parser_isidentifier(parser) ) {
			cToken = parser->TokenText ;
			simple_parser_nexttoken(parser);
		} 
		if (simple_parser_isoperator2(parser,OP_DOT)) {
			for (x = 0; x < 3; x++) {
				if (!simple_parser_isoperator2(parser,OP_DOT)) {
					parser_error(parser,PARSER_ERROR_INVALID_VARIADIC);
					return -1 ;
				}
				simple_parser_nexttoken(parser); 
			}
			is_variadic = 1 ;
		}
		/* Generate Code */
		simple_parser_icg_newoperand(parser,cToken);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : ParaList --> Identifier {',' Identifier}");
		#endif
		if (is_variadic) {
			simple_parser_icg_newoperand(parser,simple_secondary_keyword_value(KEYWORD_VARIADIC));
		}
		while ( simple_parser_isoperator2(parser,OP_COMMA) ) {
			simple_parser_nexttoken(parser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			if ( simple_parser_isidentifier(parser)) {
				if (is_variadic) {
					parser_error(parser,PARSER_ERROR_ALREADY_VARIADIC);
					return -1 ;
				}		
				cToken = parser->TokenText ;				
				simple_parser_nexttoken(parser);
				/* Support Type Identifiter */
				if ( nStart && (simple_parser_isidentifier(parser))) {
					cToken = parser->TokenText ;
					simple_parser_nexttoken(parser);
				}
				if (simple_parser_isoperator2(parser,OP_DOT)) {
					for (x = 0; x < 3; x++) {
						if (!simple_parser_isoperator2(parser,OP_DOT)) {
							parser_error(parser,PARSER_ERROR_INVALID_VARIADIC);
							return -1 ;
						}
						simple_parser_nexttoken(parser); 
					}
					is_variadic = 1 ;
				}
				/* Generate Code */
				param_count++ ;
				simple_parser_icg_newoperand(parser,cToken);
				if (is_variadic) {
					simple_parser_icg_newoperand(parser,simple_secondary_keyword_value(KEYWORD_VARIADIC));
				}
			} else {
				parser_error(parser,PARSER_ERROR_PARALIST);
				return -1 ;
			}
		}
		if ( nStart && simple_parser_isoperator2(parser,OP_FCLOSE) ) {
			simple_parser_nexttoken(parser);
		}
		return param_count ;
	} else {
		parser_error(parser,PARSER_ERROR_PARALIST);
		return -1 ;
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
		if ( parser->sState->lNoLineNumber == 0 ) {
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
	String *string ;
	if ( simple_parser_isidentifier(parser) ) {
		/* Get Token Text */
		string = simple_string_new_gc(parser->sState,parser->TokenText);
		simple_parser_nexttoken(parser);
		while ( simple_parser_isoperator2(parser,OP_DOT) ) {
			simple_parser_nexttoken(parser);
			simple_string_add_gc(parser->sState,string,".");
			if ( simple_parser_isidentifier(parser) ) {
				simple_string_add_gc(parser->sState,string,parser->TokenText);
				simple_parser_nexttoken(parser);
			} else {
				parser_error(parser,PARSER_ERROR_MODULENAME);
				simple_string_delete(string);
				return 0 ;
			}
		}
		/* Generate Code */
		simple_parser_icg_newoperand(parser,simple_string_get(string));
		simple_string_delete_gc(parser->sState,string);
		if (simple_parser_isoperator2(parser, OP_COMMA)) {
			simple_parser_nexttoken(parser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_IMPORT);
			#if RING_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Import' Identifier,{'.'identifier}");
			#endif
			return simple_parser_namedotname(parser);
		}
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
	**  This block is used to support braces { } around moduless/classes/blocks 
	**  Also support using 'end' after moduless/classes/blocks 
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
