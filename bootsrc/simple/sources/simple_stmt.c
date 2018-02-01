/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/simple.h"
/* Grammar */

int simple_parser_class ( Parser *pParser )
{
	List *pList,*pList2,*pList3  ;
	int x  ;
	char *pString  ;
	/* Statement --> Class Identifier  [ From Identifier ] */
	if ( simple_parser_iskeyword(pParser,K_CLASS) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) ) {
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(pParser,ICO_RETNULL);
			simple_parser_icg_newoperation(pParser,ICO_NEWCLASS);
			simple_parser_icg_newoperand(pParser,pParser->TokenText);
			/* Add Class to Classes Table */
			pList = pParser->ClassesMap ;
			/* Check Class Redefinition */
			if ( simple_list_getsize(pList) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(pList,x),1),pParser->TokenText) == 0 ) {
						simple_parser_error(pParser,SIMPLE_PARSER_ERROR_CLASSREDEFINE);
						return 0 ;
					}
				}
			}
			pList = simple_list_newlist_gc(pParser->pRingState,pList);
			simple_list_addstsimple_gc(pParser->pRingState,pList,pParser->TokenText);
			simple_list_addint_gc(pParser->pRingState,pList,simple_list_getsize(pParser->GenCode));
			/* Add class pointer to generated code */
			simple_parser_icg_newoperandpointer(pParser,pList);
			simple_parser_nexttoken(pParser);
			/* [From Identifer] */
			if ( simple_parser_iskeyword(pParser,K_FROM) || simple_parser_isoperator2(pParser,OP_RANGE) || simple_parser_isoperator2(pParser,OP_LESS) ) {
				simple_parser_nexttoken(pParser);
				if ( simple_parser_namedotname(pParser) ) {
					/* Generate Code */
					pList3 = simple_parser_icg_getactiveoperation(pParser);
					/* Check if parent class name = subclass name */
					if ( strcmp(simple_list_getstring(pList,1),simple_list_getstring(pList3,4)) == 0 ) {
						simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PARENTLIKESUBCLASS);
						return 0 ;
					}
					/* Set Parent Class Name in Classes Map */
					simple_list_addstsimple_gc(pParser->pRingState,pList,simple_list_getstring(pList3,4));
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : Statement  --> 'Class' Identifier 'From' [PackageName'.']Identifier");
					#endif
				} else {
					simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PRENTCLASSNAME);
					return 0 ;
				}
			} else {
				/* Set Parent Class Name In Classes Map */
				simple_list_addstsimple_gc(pParser->pRingState,pList,"");
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Statement  --> 'Class' Identifier ");
				#endif
			}
			/* Add Method/Functions List to Class in Class Table */
			pList2 = simple_list_newlist_gc(pParser->pRingState,pList);
			/* Add Flag ( IS Parent Class information collected  ) */
			simple_list_addint_gc(pParser->pRingState,pList,0);
			/* Set Active Functions List to be Class Methods */
			pParser->FunctionsMap = pList2 ;
			/* Make class visible using PackageName.ClassName if we have package */
			if ( pParser->ClassesMap != pParser->pRingState->pRingClassesMap ) {
				/* Get Package Name */
				pList3 = simple_list_getlist(pParser->pRingState->pRingPackagesMap,simple_list_getsize(pParser->pRingState->pRingPackagesMap));
				pString = simple_stsimple_new_gc(pParser->pRingState,simple_list_getstring(pList3,1));
				/* Add pointer to the Package in the Class List */
				simple_list_addpointer_gc(pParser->pRingState,pList,pList3);
				/* Add List point to General Classes point to the class in the package */
				pList2 = simple_list_newlist_gc(pParser->pRingState,pParser->pRingState->pRingClassesMap);
				simple_list_addstsimple_gc(pParser->pRingState,pList2,"");
				simple_list_addpointer_gc(pParser->pRingState,pList2,pList);
				/* Ignore Adding Pointer to File Name */
				simple_list_addpointer_gc(pParser->pRingState,pList2,NULL);
				/* Add Class Name to Package Name */
				simple_stsimple_add_gc(pParser->pRingState,pString,".");
				simple_stsimple_add_gc(pParser->pRingState,pString,simple_list_getstring(pList,1));
				simple_list_setstsimple_gc(pParser->pRingState,pList2,1,simple_stsimple_get(pString));
				simple_stsimple_delete_gc(pParser->pRingState,pString);
			} else {
				/* Add pointer to the Package in the Class List */
				simple_list_addpointer_gc(pParser->pRingState,pList,NULL);
			}
			pParser->nClassStart = 1 ;
			/* Create label to be used by Private */
			pParser->nClassMark = simple_parser_icg_newlabel2(pParser);
			pParser->nPrivateFlag = 0 ;
			/* Generate Code - Set The File Name */
			simple_parser_icg_newoperation(pParser,ICO_FILENAME);
			simple_parser_icg_newoperand(pParser,simple_list_getstring(pParser->pRingState->pRingFilesStack,simple_list_getsize(pParser->pRingState->pRingFilesStack)));
			/* Set Global Scope */
			simple_parser_icg_newoperation(pParser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(pParser,simple_list_getint(pParser->pRingState->aCustomGlobalScopeStack,simple_list_getsize(pParser->pRingState->aCustomGlobalScopeStack)));
			/* Support using { } around the class code and using 'end' after the content */
			return simple_parser_bracesandend(pParser,1,K_ENDCLASS) ;
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_CLASSNAME);
			return 0 ;
		}
	}
	/* Statement --> Func|Def Identifier [PARALIST] */
	if ( simple_parser_iskeyword(pParser,K_FUNC) || simple_parser_iskeyword(pParser,K_DEF) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) ) {
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(pParser,ICO_RETNULL);
			simple_parser_icg_newoperation(pParser,ICO_NEWFUNC);
			simple_parser_icg_newoperand(pParser,pParser->TokenText);
			/* Add function to Functions Table */
			pList2 = pParser->FunctionsMap ;
			/* Check Function Redefinition */
			if ( simple_list_getsize(pList2) > 0 ) {
				for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
					if ( strcmp(simple_list_getstring(simple_list_getlist(pList2,x),1),pParser->TokenText) == 0 ) {
						simple_parser_error(pParser,SIMPLE_PARSER_ERROR_FUNCREDEFINE);
						return 0 ;
					}
				}
			}
			pList2 = simple_list_newlist_gc(pParser->pRingState,pList2);
			simple_list_addstsimple_gc(pParser->pRingState,pList2,pParser->TokenText);
			simple_list_addint_gc(pParser->pRingState,pList2,simple_list_getsize(pParser->GenCode));
			simple_list_addstsimple_gc(pParser->pRingState,pList2,simple_list_getstring(pParser->pRingState->pRingFilesStack,simple_list_getsize(pParser->pRingState->pRingFilesStack)));
			if ( pParser->nClassStart == 1 ) {
				simple_list_addint_gc(pParser->pRingState,pList2,pParser->nPrivateFlag);
			} else {
				simple_list_addint_gc(pParser->pRingState,pList2,0);
			}
			simple_parser_nexttoken(pParser);
			if ( simple_parser_isidentifier(pParser) || simple_parser_isoperator2(pParser,OP_FOPEN) ) {
				x = simple_parser_paralist(pParser);
			} else {
				x = 1 ;
			}
			/* Set Global Scope */
			simple_parser_icg_newoperation(pParser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(pParser,simple_list_getint(pParser->pRingState->aCustomGlobalScopeStack,simple_list_getsize(pParser->pRingState->aCustomGlobalScopeStack)));
			if ( x ) {
				/* Support using { } around the function code and using 'end' after the content */
				return simple_parser_bracesandend(pParser,0,K_ENDFUNC) ;
			}
			#if SIMPLE_PARSERTRACE
			if ( x == 1 ) {
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Statement  --> 'Func' Identifier [ParaList]");
			}
			#endif
			return x ;
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_FUNCNAME);
			return 0 ;
		}
	}
	/* Statement --> Package Identifier { '.' Identifier } */
	if ( simple_parser_iskeyword(pParser,K_PACKAGE) ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PACKAGE);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Package' Identifier{'.'identifier}");
		#endif
		if ( simple_parser_namedotname(pParser) ) {
			/* Add Package to Packages List */
			pList = simple_parser_icg_getactiveoperation(pParser);
			/* Check early definition of the package */
			for ( x = 1 ; x <= simple_list_getsize(pParser->pRingState->pRingPackagesMap) ; x++ ) {
				pList3 = simple_list_getlist(pParser->pRingState->pRingPackagesMap,x);
				if ( strcmp(simple_list_getstring(pList3,1),simple_list_getstring(pList,2)) == 0 ) {
					pParser->ClassesMap = simple_list_getlist(pList3,2);
					return 1 ;
				}
			}
			pList2 = simple_list_newlist_gc(pParser->pRingState,pParser->pRingState->pRingPackagesMap);
			/* Add Package Name */
			simple_list_addstsimple_gc(pParser->pRingState,pList2,simple_list_getstring(pList,2));
			/* Add Package Classes List */
			pParser->ClassesMap = simple_list_newlist_gc(pParser->pRingState,pList2);
			/* Support using { } around the package code and using 'end' after the content */
			return simple_parser_bracesandend(pParser,1,K_ENDPACKAGE) ;
		} else {
			return 0 ;
		}
	}
	/* Statement --> Private */
	if ( simple_parser_iskeyword(pParser,K_PRIVATE) ) {
		simple_parser_nexttoken(pParser);
		if ( pParser->nClassStart == 1 ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_RETNULL);
			/* Change Label After Class to BlockFlag to Jump to Private */
			pList = simple_parser_icg_getoperationlist(pParser,pParser->nClassMark);
			simple_list_setint_gc(pParser->pRingState,pList,1,ICO_BLOCKFLAG);
			simple_list_addint_gc(pParser->pRingState,pList,simple_parser_icg_newlabel(pParser));
			simple_parser_icg_newoperation(pParser,ICO_PRIVATE);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Private'");
			#endif
			pParser->nPrivateFlag = 1 ;
			return 1 ;
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NOCLASSDEFINED);
			return 0 ;
		}
	}
	return simple_parser_stmt(pParser) ;
}

int simple_parser_stmt ( Parser *pParser )
{
	int x,nMark1,nMark2,nMark3,nStart,nEnd,nPerformanceLocations,nFlag,nLoadPackage  ;
	char *pString  ;
	List *pMark,*pMark2,*pMark3,*pList2  ;
	double nNum1  ;
	char cStr[50]  ;
	char cFileName[SIMPLE_PATHSIZE]  ;
	char cCurrentDir[SIMPLE_PATHSIZE]  ;
	nPerformanceLocations = 0 ;
	nLoadPackage = 0 ;
	assert(pParser != NULL);
	/* Statement --> Load Literal */
	if ( simple_parser_iskeyword(pParser,K_LOAD) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_iskeyword(pParser,K_PACKAGE) ) {
			simple_parser_nexttoken(pParser);
			nLoadPackage = 1 ;
			pParser->pRingState->nCustomGlobalScopeCounter++ ;
			simple_list_addint_gc(pParser->pRingState,pParser->pRingState->aCustomGlobalScopeStack,pParser->pRingState->nCustomGlobalScopeCounter);
		}
		if ( simple_parser_isliteral(pParser) ) {
			/* Check File in the Ring/bin folder */
			strcpy(cFileName,pParser->TokenText);
			if ( simple_fexists(pParser->TokenText) == 0 ) {
				simple_exefolder(cFileName);
				strcat(cFileName,pParser->TokenText);
				if ( simple_fexists(cFileName) == 0 ) {
					strcpy(cFileName,pParser->TokenText);
				}
			}
			/*
			**  Generate Code 
			**  Load Package - New Global Scope 
			*/
			if ( nLoadPackage ) {
				simple_parser_icg_newoperation(pParser,ICO_NEWGLOBALSCOPE);
			}
			simple_parser_icg_newoperation(pParser,ICO_FILENAME);
			simple_parser_icg_newoperand(pParser,cFileName);
			simple_parser_icg_newoperation(pParser,ICO_BLOCKFLAG);
			pMark = simple_parser_icg_getactiveoperation(pParser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Load' Literal");
			#endif
			/* Set Global Scope */
			simple_parser_icg_newoperation(pParser,ICO_SETGLOBALSCOPE);
			simple_parser_icg_newoperandint(pParser,simple_list_getint(pParser->pRingState->aCustomGlobalScopeStack,simple_list_getsize(pParser->pRingState->aCustomGlobalScopeStack)));
			/* No package at the start of the file */
			pParser->ClassesMap = pParser->pRingState->pRingClassesMap ;
			/* Save the Current Directory */
			simple_currentdir(cCurrentDir);
			/* Read The File */
			x = simple_scanner_readfile(pParser->pRingState,cFileName);
			/* Restore the Current Directory */
			simple_chdir(cCurrentDir);
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(pParser,ICO_RETNULL);
			nMark1 = simple_parser_icg_newlabel(pParser);
			simple_parser_icg_addoperandint(pParser,pMark,nMark1);
			/* Load Package - End Global Scope */
			if ( nLoadPackage ) {
				simple_parser_icg_newoperation(pParser,ICO_ENDGLOBALSCOPE);
				simple_list_deletelastitem_gc(pParser->pRingState,pParser->pRingState->aCustomGlobalScopeStack);
				/* Set Global Scope */
				simple_parser_icg_newoperation(pParser,ICO_SETGLOBALSCOPE);
				simple_parser_icg_newoperandint(pParser,simple_list_getint(pParser->pRingState->aCustomGlobalScopeStack,simple_list_getsize(pParser->pRingState->aCustomGlobalScopeStack)));
			}
			/* Set Active File */
			simple_parser_icg_newoperation(pParser,ICO_FILENAME);
			simple_parser_icg_newoperand(pParser,simple_list_getstring(pParser->pRingState->pRingFilesStack,simple_list_getsize(pParser->pRingState->pRingFilesStack)));
			simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
			simple_parser_nexttoken(pParser);
			return x ;
		}
		return 0 ;
	}
	/* Statement --> See|Put Expr */
	if ( simple_parser_iskeyword(pParser,K_SEE) | simple_parser_iskeyword(pParser,K_PUT) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_USESEEFUNCTION
		/* Generate code to use the SEE function */
		simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
		simple_parser_icg_newoperand(pParser,"ringvm_see");
		/* Parameters */
		nFlag = pParser->nAssignmentFlag ;
		pParser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(pParser);
		pParser->nAssignmentFlag = nFlag ;
		simple_parser_icg_newoperation(pParser,ICO_CALL);
		simple_parser_icg_newoperandint(pParser,0);
		simple_parser_icg_newoperation(pParser,ICO_NOOP);
		simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
		#else
		/*
		**  Generate code using the SEE Command Instruction 
		**  Generate Code 
		*/
		simple_parser_icg_newoperation(pParser,ICO_FUNCEXE);
		pParser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(pParser);
		pParser->nAssignmentFlag = 1 ;
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PRINT);
		#endif
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'See' Expr");
		#endif
		return x ;
	}
	/* Statement --> ? Expr */
	if ( simple_parser_isoperator(pParser,"?") ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_FUNCEXE);
		pParser->nAssignmentFlag = 0 ;
		x = simple_parser_expr(pParser);
		pParser->nAssignmentFlag = 1 ;
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PRINT);
		/* Print New Line */
		simple_parser_icg_newoperation(pParser,ICO_PUSHC);
		simple_parser_icg_newoperand(pParser,"\n");
		simple_parser_icg_newoperation(pParser,ICO_PRINT);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> '?' Expr");
		#endif
		return x ;
	}
	/* Statement --> Give|Get Identifier */
	if ( simple_parser_iskeyword(pParser,K_GIVE) | simple_parser_iskeyword(pParser,K_GET) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(pParser,pParser->TokenText);
			simple_parser_nexttoken(pParser);
			x = simple_parser_mixer(pParser);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Give' Identifier|ListItem|Object.Attribute");
			#endif
			#if SIMPLE_USEGIVEFUNCTION
			/* Generate code to use the GIVE function */
			simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENTPOINTER);
			simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
			simple_parser_icg_newoperand(pParser,"ringvm_give");
			simple_parser_icg_newoperation(pParser,ICO_CALL);
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_icg_newoperation(pParser,ICO_NOOP);
			simple_parser_icg_newoperation(pParser,ICO_BEFOREEQUAL);
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENT);
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
			#else
			simple_parser_icg_newoperation(pParser,ICO_GIVE);
			#endif
			return 1 ;
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_VARNAME);
			return 0 ;
		}
	}
	/* Statement --> For Identifier = Expr to Expr {Statement} Next  |  For Identifier in Expr {Statemen */
	if ( simple_parser_iskeyword(pParser,K_FOR) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) ) {
			pString = simple_stsimple_new_gc(pParser->pRingState,pParser->TokenText);
			simple_parser_nexttoken(pParser);
			if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
				/*
				**  Generate Code 
				**  Mark for Exit command to go to outside the loop 
				*/
				simple_parser_icg_newoperation(pParser,ICO_EXITMARK);
				pMark3 = simple_parser_icg_getactiveoperation(pParser);
				simple_parser_icg_newoperation(pParser,ICO_LOADAFIRST);
				simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
				simple_parser_nexttoken(pParser);
				pParser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(pParser) ) {
					/*
					**  Generate Code 
					**  Before Equal ( = ) not += , -= ,... etc 
					*/
					simple_parser_icg_newoperation(pParser,ICO_BEFOREEQUAL);
					simple_parser_icg_newoperandint(pParser,0);
					simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENT);
					nMark1 = simple_parser_icg_newlabel(pParser);
					simple_parser_icg_newoperation(pParser,ICO_LOADAPUSHV);
					simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
					if ( simple_parser_iskeyword(pParser,K_TO) ) {
						simple_parser_nexttoken(pParser);
						pParser->nAssignmentFlag = 0 ;
						if ( simple_parser_csexpr(pParser) ) {
							pParser->nAssignmentFlag = 1 ;
							/* Generate Code */
							if ( (simple_parser_icg_getlastoperation(pParser) == ICO_PUSHN) && (simple_parser_icg_newlabel(pParser) == (nMark1+2)) ) {
								/*
								**  We check nMark2+2 to avoid executing next instructions when we have expr 
								**  for example for x = 1 to 10+5 
								*/
								nNum1 = simple_list_getdouble(pParser->ActiveGenCodeList,2) ;
								simple_parser_icg_deletelastoperation(pParser);
								simple_parser_icg_setlastoperation(pParser,ICO_JUMPVARLENUM);
								simple_parser_icg_newoperanddouble(pParser,nNum1);
								/* Add Locations Needed for Instruction change for performance */
								nPerformanceLocations = 1 ;
							} else {
								simple_parser_icg_newoperation(pParser,ICO_JUMPFOR);
							}
							pMark = simple_parser_icg_getactiveoperation(pParser);
							/* Step <expr> */
							x = simple_parser_step(pParser,&nMark1);
							if ( x == 0 ) {
								simple_stsimple_delete_gc(pParser->pRingState,pString);
								return 0 ;
							}
							#if SIMPLE_PARSERTRACE
							SIMPLE_STATE_CHECKPRINTRULES 
							
							puts("Rule : Statement  --> 'For' Identifier '=' Expr to Expr ['step' Expr]");
							#endif
							while ( simple_parser_stmt(pParser) ) {
								if ( pParser->ActiveToken == pParser->TokensCount ) {
									break ;
								}
							}
							if ( simple_parser_iskeyword(pParser,K_NEXT) || simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
								/* Generate Code */
								nMark3 = simple_parser_icg_newlabel(pParser);
								/* Increment Jump */
								simple_parser_icg_newoperation(pParser,ICO_INCJUMP);
								simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
								simple_parser_icg_newoperandint(pParser,nMark1);
								/* Add Locations needed for instruction change for performance */
								simple_parser_icg_newoperandint(pParser,0);
								simple_parser_icg_newoperandint(pParser,0);
								nMark2 = simple_parser_icg_newlabel(pParser);
								simple_parser_icg_addoperandint(pParser,pMark,nMark2);
								/* Performance Locations */
								if ( nPerformanceLocations ) {
									/* Add Locations Needed for Instruction JUMPVARLENUM change for performance */
									simple_parser_icg_addoperandint(pParser,pMark,0);
									simple_parser_icg_addoperandint(pParser,pMark,0);
								}
								/* Set Exit Mark */
								simple_parser_icg_addoperandint(pParser,pMark3,nMark2);
								/* Set Loop Mark */
								simple_parser_icg_addoperandint(pParser,pMark3,nMark3);
								/* End Loop (Remove Exit Mark) */
								simple_parser_icg_newoperation(pParser,ICO_POPEXITMARK);
								/* POP Step */
								simple_parser_icg_newoperation(pParser,ICO_POPSTEP);
								simple_parser_nexttoken(pParser);
								#if SIMPLE_PARSERTRACE
								SIMPLE_STATE_CHECKPRINTRULES 
								
								puts("Rule : Next --> 'Next'");
								#endif
								simple_stsimple_delete_gc(pParser->pRingState,pString);
								return 1 ;
							} else {
								simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NEXT);
							}
						}
					}
				}
			}
			else if ( simple_parser_iskeyword(pParser,K_IN) ) {
				/* Generate Code */
				sprintf( cStr , "n_sys_var_%d" , simple_parser_icg_instructionscount(pParser) ) ;
				/* Mark for Exit command to go to outside the loop */
				simple_parser_icg_newoperation(pParser,ICO_EXITMARK);
				pMark3 = simple_parser_icg_getactiveoperation(pParser);
				simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
				simple_parser_icg_newoperand(pParser,cStr);
				simple_parser_icg_newoperation(pParser,ICO_PUSHN);
				simple_parser_icg_newoperanddouble(pParser,1.0);
				/* Before Equal ( = ) not += , -= ,... etc */
				simple_parser_icg_newoperation(pParser,ICO_BEFOREEQUAL);
				simple_parser_icg_newoperandint(pParser,0);
				simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENT);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_newoperation(pParser,ICO_LOADAPUSHV);
				simple_parser_icg_newoperand(pParser,cStr);
				simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
				simple_parser_icg_newoperand(pParser,"len");
				nStart = simple_parser_icg_instructionscount(pParser) + 1 ;
				simple_parser_nexttoken(pParser);
				pParser->nAssignmentFlag = 0 ;
				if ( simple_parser_csexpr(pParser) ) {
					pParser->nAssignmentFlag = 1 ;
					/* Generate Code */
					nEnd = simple_parser_icg_instructionscount(pParser) ;
					/* Note (nEnd-1) , -1 to remove instruction PushV (avoid error with for x in string) */
					if ( simple_parser_icg_getlastoperation(pParser) == ICO_PUSHV ) {
						nEnd-- ;
					}
					simple_parser_icg_newoperation(pParser,ICO_CALL);
					/* Generate 0 For Operator OverLoading */
					simple_parser_icg_newoperandint(pParser,0);
					simple_parser_icg_newoperation(pParser,ICO_JUMPFOR);
					pMark = simple_parser_icg_getactiveoperation(pParser);
					simple_parser_icg_newoperation(pParser,ICO_LOADAFIRST);
					simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
					simple_parser_icg_duplicate(pParser,nStart,nEnd);
					simple_parser_icg_newoperation(pParser,ICO_LOADAPUSHV);
					simple_parser_icg_newoperand(pParser,cStr);
					simple_parser_icg_newoperation(pParser,ICO_LOADINDEXADDRESS);
					/* Generate 0 For Operator OverLoading */
					simple_parser_icg_newoperandint(pParser,0);
					/* Item by reference */
					simple_parser_icg_newoperation(pParser,ICO_SETREFERENCE);
					/* Step <expr> */
					x = simple_parser_step(pParser,&nMark1);
					if ( x == 0 ) {
						simple_stsimple_delete_gc(pParser->pRingState,pString);
						return 0 ;
					}
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : Statement  --> 'For' Identifier 'in' Expr  ['step' Expr]");
					#endif
					while ( simple_parser_stmt(pParser) ) {
						if ( pParser->ActiveToken == pParser->TokensCount ) {
							break ;
						}
					}
					if ( simple_parser_iskeyword(pParser,K_NEXT) || simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
						simple_parser_nexttoken(pParser);
						/* Generate Code */
						nMark3 = simple_parser_icg_newlabel(pParser);
						/* Increment Jump */
						simple_parser_icg_newoperation(pParser,ICO_INCJUMP);
						simple_parser_icg_newoperand(pParser,cStr);
						simple_parser_icg_newoperandint(pParser,nMark1);
						/* Add Locations needed for instruction change for performance */
						simple_parser_icg_newoperandint(pParser,0);
						simple_parser_icg_newoperandint(pParser,0);
						nMark2 = simple_parser_icg_newlabel(pParser);
						simple_parser_icg_addoperandint(pParser,pMark,nMark2);
						/* Set Exit Mark */
						simple_parser_icg_addoperandint(pParser,pMark3,nMark2);
						/* Set Loop Mark */
						simple_parser_icg_addoperandint(pParser,pMark3,nMark3);
						/* End Loop (Remove Exit Mark) */
						simple_parser_icg_newoperation(pParser,ICO_POPEXITMARK);
						/* POP Step */
						simple_parser_icg_newoperation(pParser,ICO_POPSTEP);
						/* Remove Reference Value */
						simple_parser_icg_newoperation(pParser,ICO_LOADAFIRST);
						simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
						simple_parser_icg_newoperation(pParser,ICO_KILLREFERENCE);
						simple_parser_icg_newoperation(pParser,ICO_PUSHN);
						simple_parser_icg_newoperanddouble(pParser,1.0);
						/* Before Equal ( = ) not += , -= ,... etc */
						simple_parser_icg_newoperation(pParser,ICO_BEFOREEQUAL);
						simple_parser_icg_newoperandint(pParser,0);
						simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENT);
						#if SIMPLE_PARSERTRACE
						SIMPLE_STATE_CHECKPRINTRULES 
						
						puts("Rule : Next --> 'Next'");
						#endif
						simple_stsimple_delete_gc(pParser->pRingState,pString);
						return 1 ;
					} else {
						simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NEXT);
					}
				}
			}
			simple_stsimple_delete_gc(pParser->pRingState,pString);
		}
		return 0 ;
	}
	/* Statement --> IF Expr Statements OK */
	if ( simple_parser_iskeyword(pParser,K_IF) ) {
		simple_parser_nexttoken(pParser);
		pParser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(pParser) ) {
			pParser->nAssignmentFlag = 1 ;
			/*
			**  First Condition 
			**  Generate Code 
			*/
			simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(pParser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'If' Expr {Statement} { But } [Else] Ok");
			#endif
			while ( simple_parser_stmt(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
			/* Generate Code */
			pList2 = simple_list_new_gc(pParser->pRingState,0);
			simple_parser_icg_newoperation(pParser,ICO_JUMP);
			simple_list_addpointer_gc(pParser->pRingState,pList2,simple_parser_icg_getactiveoperation(pParser));
			/* { 'But' Statements } 'Else' Statements */
			while ( simple_parser_iskeyword(pParser,K_BUT) || simple_parser_iskeyword(pParser,K_ELSEIF) ) {
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark1);
				simple_parser_nexttoken(pParser);
				pParser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(pParser) ) {
					pParser->nAssignmentFlag = 1 ;
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
					pMark = simple_parser_icg_getactiveoperation(pParser);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : But  --> 'But' Expr {Statement}");
					#endif
					while ( simple_parser_stmt(pParser) ) {
						if ( pParser->ActiveToken == pParser->TokensCount ) {
							break ;
						}
					}
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_JUMP);
					simple_list_addpointer_gc(pParser->pRingState,pList2,simple_parser_icg_getactiveoperation(pParser));
				}
			}
			if ( simple_parser_iskeyword(pParser,K_ELSE) || simple_parser_iskeyword(pParser,K_OTHER) ) {
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark1);
				pMark = NULL ;
				simple_parser_nexttoken(pParser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Else  --> 'Else' {Statement} ");
				#endif
				while ( simple_parser_stmt(pParser) ) {
					if ( pParser->ActiveToken == pParser->TokensCount ) {
						break ;
					}
				}
			}
			if ( simple_parser_iskeyword(pParser,K_OK) || simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(pParser,pMark,nMark1);
				}
				if ( simple_list_getsize(pList2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
						simple_parser_icg_addoperandint(pParser,((List *) simple_list_getpointer(pList2,x)),nMark1);
					}
				}
				simple_list_delete_gc(pParser->pRingState,pList2);
				simple_parser_nexttoken(pParser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Ok  --> 'OK'");
				#endif
				return 1 ;
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_OK);
				simple_list_delete_gc(pParser->pRingState,pList2);
			}
		}
		return 0 ;
	}
	/* Statement --> WHILE Expr Statements END */
	if ( simple_parser_iskeyword(pParser,K_WHILE) ) {
		/*
		**  Generate Code 
		**  Mark for Exit command to go to outsize the loop 
		*/
		simple_parser_icg_newoperation(pParser,ICO_EXITMARK);
		pMark3 = simple_parser_icg_getactiveoperation(pParser);
		nMark1 = simple_parser_icg_newlabel(pParser);
		simple_parser_nexttoken(pParser);
		pParser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(pParser) ) {
			pParser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(pParser);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'While' Expr {Statement} End");
			#endif
			while ( simple_parser_stmt(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
			if ( simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
				/* Generate Code */
				nMark3 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_newoperation(pParser,ICO_JUMP);
				simple_parser_icg_newoperandint(pParser,nMark1);
				nMark2 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark2);
				/* Set Exit Mark */
				simple_parser_icg_addoperandint(pParser,pMark3,nMark2);
				/* Set Loop Mark */
				simple_parser_icg_addoperandint(pParser,pMark3,nMark3);
				/* End Loop (Remove Exit Mark) */
				simple_parser_icg_newoperation(pParser,ICO_POPEXITMARK);
				simple_parser_nexttoken(pParser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : End --> 'End'");
				#endif
				return 1 ;
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_END);
			}
		}
		return 0 ;
	}
	/* Statement --> DO Statements AGAIN Expr */
	if ( simple_parser_iskeyword(pParser,K_DO) ) {
		/*
		**  Generate Code 
		**  Mark for Exit command to go to outsize the loop 
		*/
		simple_parser_icg_newoperation(pParser,ICO_EXITMARK);
		pMark3 = simple_parser_icg_getactiveoperation(pParser);
		nMark1 = simple_parser_icg_newlabel(pParser);
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Do' {Statement} Again");
		#endif
		while ( simple_parser_stmt(pParser) ) {
			if ( pParser->ActiveToken == pParser->TokensCount ) {
				break ;
			}
		}
		if ( simple_parser_iskeyword(pParser,K_AGAIN) ) {
			/* Generate Code */
			simple_parser_nexttoken(pParser);
			pParser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(pParser) ) {
				/* Generate Code (Test Condition) */
				simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
				pMark = simple_parser_icg_getactiveoperation(pParser);
				/* Generate Code */
				nMark3 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_newoperation(pParser,ICO_JUMP);
				simple_parser_icg_newoperandint(pParser,nMark1);
				nMark2 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark2);
				/* Set Exit Mark */
				simple_parser_icg_addoperandint(pParser,pMark3,nMark2);
				/* Set Loop Mark */
				simple_parser_icg_addoperandint(pParser,pMark3,nMark3);
				/* End Loop (Remove Exit Mark) */
				simple_parser_icg_newoperation(pParser,ICO_POPEXITMARK);
				pParser->nAssignmentFlag = 1 ;
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Again  --> 'Again' Expr");
				#endif
				return 1 ;
			}
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_AGAIN);
		}
		return 0 ;
	}
	/* Statement --> Return Expr */
	if ( simple_parser_iskeyword(pParser,K_RETURN) ) {
		simple_parser_nexttoken(pParser);
		x = 1 ;
		if ( simple_parser_isendline(pParser) == 0 ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_FREELOADASCOPE);
			simple_parser_icg_newoperation(pParser,ICO_FUNCEXE);
			pParser->nAssignmentFlag = 0 ;
			x = simple_parser_expr(pParser);
			pParser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_ENDFUNCEXE);
			if ( x ) {
				simple_parser_icg_newoperation(pParser,ICO_RETURN);
			}
			else {
				simple_parser_icg_newoperation(pParser,ICO_RETNULL);
			}
		} else {
			/*
			**  Generate Code 
			**  Return NULL 
			*/
			simple_parser_icg_newoperation(pParser,ICO_RETNULL);
		}
		#if SIMPLE_PARSERTRACE
		if ( x == 1 ) {
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Return'");
		}
		#endif
		return x ;
	}
	/* Statement --> Try {Statement} Catch {Statement} Done */
	if ( simple_parser_iskeyword(pParser,K_TRY) ) {
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
			simple_parser_nexttoken(pParser);
			pParser->nControlStructureBrace++ ;
		}
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_TRY);
		pMark = simple_parser_icg_getactiveoperation(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Try' {Statement} Catch Done");
		#endif
		while ( simple_parser_stmt(pParser) ) {
			if ( pParser->ActiveToken == pParser->TokensCount ) {
				break ;
			}
		}
		if ( simple_parser_iskeyword(pParser,K_CATCH) ) {
			simple_parser_nexttoken(pParser);
			/*
			**  Generate Code 
			**  Jump from end of try block to label after done 
			*/
			simple_parser_icg_newoperation(pParser,ICO_JUMP);
			pMark2 = simple_parser_icg_getactiveoperation(pParser);
			nMark1 = simple_parser_icg_newlabel(pParser);
			simple_parser_icg_addoperandint(pParser,pMark,nMark1);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Catch --> 'Catch' {Statement}");
			#endif
			while ( simple_parser_stmt(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
			if ( simple_parser_iskeyword(pParser,K_DONE) || simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Done --> 'Done'");
				#endif
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_JUMP);
				pMark3 = simple_parser_icg_getactiveoperation(pParser);
				nMark2 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark2,nMark2);
				simple_parser_icg_newoperation(pParser,ICO_DONE);
				nMark3 = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark3,nMark3);
				return 1 ;
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NODONE);
			}
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NOCATCH);
		}
	}
	/* Statement --> Bye (Close the Program) */
	if ( simple_parser_iskeyword(pParser,K_BYE) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Bye' ");
		#endif
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_BYE);
		return 1 ;
	}
	/* Statement --> Exit (Go to outside the loop) */
	if ( simple_parser_iskeyword(pParser,K_EXIT) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Exit' ");
		#endif
		/* Check Number  (Exit from more than one loop) */
		if ( simple_parser_isnumber(pParser) || simple_parser_isidentifier(pParser) ) {
			if ( ! simple_parser_expr(pParser) ) {
				return 0 ;
			}
		}
		else {
			simple_parser_icg_newoperation(pParser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(pParser,1.0);
		}
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_EXIT);
		return 1 ;
	}
	/* Statement --> Loop (Continue) */
	if ( simple_parser_iskeyword(pParser,K_LOOP) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Loop'");
		#endif
		/* Check Number  (Continue from more than one loop) */
		if ( simple_parser_isnumber(pParser) || simple_parser_isidentifier(pParser) ) {
			if ( ! simple_parser_expr(pParser) ) {
				return 0 ;
			}
		}
		else {
			simple_parser_icg_newoperation(pParser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(pParser,1.0);
		}
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_LOOP);
		return 1 ;
	}
	/* Statement --> Switch  Expr { ON|CASE Expr {Statement} } OFF */
	if ( simple_parser_iskeyword(pParser,K_SWITCH) ) {
		simple_parser_nexttoken(pParser);
		pParser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(pParser) ) {
			pParser->nAssignmentFlag = 1 ;
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Statement  --> 'Switch' Expr {ON} [Other] OFF");
			#endif
			SIMPLE_PARSER_IGNORENEWLINE ;
			/* ON|CASE Statements */
			pList2 = simple_list_new_gc(pParser->pRingState,0);
			pMark = NULL ;
			while ( simple_parser_iskeyword(pParser,K_ON) || simple_parser_iskeyword(pParser,K_CASE) ) {
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(pParser,pMark,nMark1);
				}
				simple_parser_icg_newoperation(pParser,ICO_DUPLICATE);
				pParser->nAssignmentFlag = 0 ;
				if ( simple_parser_expr(pParser) ) {
					pParser->nAssignmentFlag = 1 ;
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_EQUAL);
					simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
					pMark = simple_parser_icg_getactiveoperation(pParser);
					simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : ON --> 'on' Expr {Statement}");
					#endif
					while ( simple_parser_stmt(pParser) ) {
						if ( pParser->ActiveToken == pParser->TokensCount ) {
							break ;
						}
					}
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_JUMP);
					simple_list_addpointer_gc(pParser->pRingState,pList2,simple_parser_icg_getactiveoperation(pParser));
				}
			}
			/* Other */
			if ( simple_parser_iskeyword(pParser,K_OTHER) || simple_parser_iskeyword(pParser,K_ELSE) ) {
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(pParser,pMark,nMark1);
					pMark = NULL ;
				}
				simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Other --> 'Other' {Statement}");
				#endif
				while ( simple_parser_stmt(pParser) ) {
					if ( pParser->ActiveToken == pParser->TokensCount ) {
						break ;
					}
				}
			}
			/* OFF */
			if ( simple_parser_iskeyword(pParser,K_OFF) || simple_parser_iskeyword(pParser,K_END) || simple_parser_csbraceend(pParser) ) {
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				nMark1 = simple_parser_icg_newlabel(pParser);
				if ( pMark != NULL ) {
					simple_parser_icg_addoperandint(pParser,pMark,nMark1);
				}
				if ( simple_list_getsize(pList2) > 0 ) {
					for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
						simple_parser_icg_addoperandint(pParser,((List *) simple_list_getpointer(pList2,x)),nMark1);
					}
				}
				simple_list_delete_gc(pParser->pRingState,pList2);
				simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : OFF --> 'Off'");
				#endif
				return 1 ;
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_SWITCHOFF);
			}
		} else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_SWITCHEXPR);
		}
	}
	/* Statement --> Import Identifier { '.' Identifier } */
	if ( simple_parser_iskeyword(pParser,K_IMPORT) ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_IMPORT);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> 'Import' Identifier{'.'identifier}");
		#endif
		return simple_parser_namedotname(pParser) ;
	}
	/* Statement --> epslion */
	if ( simple_parser_epslion(pParser) ) {
		return 1 ;
	}
	/* Statement --> Expr */
	if ( simple_parser_expr(pParser) ) {
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Statement  --> Expr ");
		#endif
		/*
		**  Generate Code 
		**  Call expreval() if we are inside { } 
		*/
		if ( pParser->nBraceFlag ) {
			/* if ismethod(self,"braceexpreval") braceexpreval() ok */
			simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
			simple_parser_icg_newoperand(pParser,"ismethod");
			simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(pParser,"self");
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
			simple_parser_icg_newoperation(pParser,ICO_PUSHC);
			simple_parser_icg_newoperand(pParser,"braceexpreval");
			simple_parser_icg_newoperation(pParser,ICO_CALL);
			simple_parser_icg_newoperation(pParser,ICO_NOOP);
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
			/* Jump */
			simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
			pMark = simple_parser_icg_getactiveoperation(pParser);
			simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
			simple_parser_icg_newoperand(pParser,"braceexpreval");
			/* Duplicate Stack */
			simple_parser_icg_newoperation(pParser,ICO_DUPLICATE);
			simple_parser_icg_newoperation(pParser,ICO_CALL);
			simple_parser_icg_newoperation(pParser,ICO_NOOP);
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
			simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
			nMark1 = simple_parser_icg_newlabel(pParser);
			simple_parser_icg_addoperandint(pParser,pMark,nMark1);
		}
		simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
		return 1 ;
	}
	return 0 ;
}

int simple_parser_paralist ( Parser *pParser )
{
	int nStart  ;
	const char *cToken  ;
	/* Check ( */
	nStart = 0 ;
	if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
		simple_parser_nexttoken(pParser);
		nStart = 1 ;
	}
	/* ParaList --> Epslion */
	if ( simple_parser_isendline(pParser) || (nStart && simple_parser_isoperator2(pParser,OP_FCLOSE) ) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : ParaList --> Epslion ");
		#endif
		return 1 ;
	}
	/* ParaList --> [ Identifier { , Identifier }  ] */
	if ( simple_parser_isidentifier(pParser) ) {
		cToken = pParser->TokenText ;
		simple_parser_nexttoken(pParser);
		/* Support Type Identifiter */
		if ( nStart && simple_parser_isidentifier(pParser) ) {
			cToken = pParser->TokenText ;
			simple_parser_nexttoken(pParser);
		}
		/* Generate Code */
		simple_parser_icg_newoperand(pParser,cToken);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : ParaList --> Identifier {',' Identifier}");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_COMMA) ) {
			simple_parser_nexttoken(pParser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			if ( simple_parser_isidentifier(pParser) ) {
				cToken = pParser->TokenText ;
				simple_parser_nexttoken(pParser);
				/* Support Type Identifiter */
				if ( nStart && simple_parser_isidentifier(pParser) ) {
					cToken = pParser->TokenText ;
					simple_parser_nexttoken(pParser);
				}
				/* Generate Code */
				simple_parser_icg_newoperand(pParser,cToken);
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PARALIST);
				return 0 ;
			}
		}
		if ( nStart && simple_parser_isoperator2(pParser,OP_FCLOSE) ) {
			simple_parser_nexttoken(pParser);
		}
		return 1 ;
	} else {
		simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PARALIST);
		return 0 ;
	}
}

int simple_parser_list ( Parser *pParser )
{
	/* "["  [ Expr { , Expr } ] "]" */
	if ( simple_parser_isoperator2(pParser,OP_LOPEN) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_LISTSTART);
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(pParser,OP_LCLOSE) ) {
			simple_parser_nexttoken(pParser);
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_LISTEND);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : List --> '[' Expr { ',' Expr } ']' ");
			#endif
			return 1 ;
		}
		while ( 1 ) {
			pParser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(pParser) ) {
				/* Generate Code */
				if ( simple_parser_icg_getlastoperation(pParser) != ICO_LISTEND ) {
					simple_parser_icg_newoperation(pParser,ICO_LISTITEM);
				}
				pParser->nAssignmentFlag = 1 ;
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(pParser,OP_COMMA) ) {
					simple_parser_nexttoken(pParser);
				}
				else if ( simple_parser_isoperator2(pParser,OP_LCLOSE) ) {
					simple_parser_nexttoken(pParser);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : List --> '[' Expr { ',' Expr } ']' ");
					#endif
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_LISTEND);
					return 1 ;
				} else {
					simple_parser_error(pParser,SIMPLE_PARSER_ERROR_LISTITEM);
					return 0 ;
				}
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_LISTITEM);
				return 0 ;
			}
			SIMPLE_PARSER_IGNORENEWLINE ;
		}
	}
	return 0 ;
}

int simple_parser_epslion ( Parser *pParser )
{
	if ( simple_parser_isendline(pParser) ) {
		/* Generate Code */
		if ( pParser->pRingState->lNoLineNumber == 0 ) {
			simple_parser_icg_newoperation(pParser,ICO_NEWLINE);
			simple_parser_icg_newoperandint(pParser,atoi(pParser->TokenText));
		}
		pParser->nLineNumber = atoi(pParser->TokenText) ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		printf( "\nLine %d \n",pParser->nLineNumber ) ;
		#endif
		if ( simple_parser_nexttoken(pParser) ) {
			return 1 ;
		}
		if ( pParser->TokensCount == 1 ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_passepslion ( Parser *pParser )
{
	/* used after factor - identifier to allow {  } in new line */
	if ( simple_parser_isendline(pParser) ) {
		pParser->nLineNumber = atoi(pParser->TokenText) ;
		if ( simple_parser_nexttoken(pParser) ) {
			return 1 ;
		}
	}
	return 0 ;
}

int simple_parser_namedotname ( Parser *pParser )
{
	char *pString  ;
	if ( simple_parser_isidentifier(pParser) ) {
		/* Get Token Text */
		pString = simple_stsimple_new_gc(pParser->pRingState,pParser->TokenText);
		simple_parser_nexttoken(pParser);
		while ( simple_parser_isoperator2(pParser,OP_DOT) ) {
			simple_parser_nexttoken(pParser);
			simple_stsimple_add_gc(pParser->pRingState,pString,".");
			if ( simple_parser_isidentifier(pParser) ) {
				simple_stsimple_add_gc(pParser->pRingState,pString,pParser->TokenText);
				simple_parser_nexttoken(pParser);
			} else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PACKAGENAME);
				simple_stsimple_delete(pString);
				return 0 ;
			}
		}
		/* Generate Code */
		simple_parser_icg_newoperand(pParser,simple_stsimple_get(pString));
		simple_stsimple_delete_gc(pParser->pRingState,pString);
		return 1 ;
	} else {
		simple_parser_error(pParser,SIMPLE_PARSER_ERROR_PACKAGENAME);
		return 0 ;
	}
}

int simple_parser_step ( Parser *pParser,int *nMark1 )
{
	/* Step <expr> */
	pParser->nInsertFlag = 1 ;
	pParser->nInsertCounter = *nMark1-1 ;
	if ( simple_parser_iskeyword(pParser,K_STEP) ) {
		simple_parser_nexttoken(pParser);
		pParser->nAssignmentFlag = 0 ;
		if ( simple_parser_csexpr(pParser) ) {
			pParser->nAssignmentFlag = 1 ;
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_STEPNUMBER);
		} else {
			return 0 ;
		}
	} else {
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PUSHN);
		simple_parser_icg_newoperanddouble(pParser,1.0);
		simple_parser_icg_newoperation(pParser,ICO_STEPNUMBER);
	}
	*nMark1 = pParser->nInsertCounter + 1 ;
	pParser->nInsertFlag = 0 ;
	pParser->nInsertCounter = 0 ;
	return 1 ;
}

int simple_parser_csexpr ( Parser *pParser )
{
	int nOutput  ;
	pParser->nControlStructureExpr = 1 ;
	nOutput = simple_parser_expr(pParser);
	pParser->nControlStructureExpr = 0 ;
	SIMPLE_PARSER_IGNORENEWLINE ;
	if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
		simple_parser_nexttoken(pParser);
		pParser->nControlStructureBrace++ ;
	}
	return nOutput ;
}

int simple_parser_csbraceend ( Parser *pParser )
{
	if ( (pParser->nControlStructureBrace >= 1) && simple_parser_isoperator2(pParser,OP_BRACECLOSE) ) {
		pParser->nControlStructureBrace-- ;
		return 1 ;
	}
	return 0 ;
}

int simple_parser_bracesandend ( Parser *pParser,int lClass,SCANNER_KEYWORD nKeyword )
{
	/*
	**  This function is used to support braces { } around packages/classes/functions 
	**  Also support using 'end' after packages/classes/functions 
	**  IF The Parameter : lClass = True we call simple_parser_class() instead of simple_parser_stmt() 
	**  When we support braces { } 
	**  But the support for 'end' always uses simple_parser_class() 
	**  Support using { } 
	*/
	SIMPLE_PARSER_IGNORENEWLINE ;
	if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
		simple_parser_nexttoken(pParser);
		if ( lClass ) {
			while ( simple_parser_class(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
		}
		else {
			while ( simple_parser_stmt(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
		}
		if ( simple_parser_isoperator2(pParser,OP_BRACECLOSE) ) {
			simple_parser_nexttoken(pParser);
			return 1 ;
		}
		return 0 ;
	}
	/* Support using End */
	while ( simple_parser_class(pParser) ) {
		if ( pParser->ActiveToken == pParser->TokensCount ) {
			break ;
		}
	}
	if ( simple_parser_iskeyword(pParser,K_END) || simple_parser_iskeyword(pParser,nKeyword) ) {
		simple_parser_nexttoken(pParser);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : End --> 'End'");
		#endif
	}
	return 1 ;
}
