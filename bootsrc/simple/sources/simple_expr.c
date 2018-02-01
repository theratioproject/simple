/*
**  Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> 
**  The First Step  - Start Here 
*/
#include "../includes/simple.h"
/*
**  Functions 
**  Grammar 
*/

int simple_parser_expr ( Parser *pParser )
{
	int x,nMark  ;
	List *pMark  ;
	/* Expr --> LogicNot { and|or LogicNot } */
	if ( simple_parser_logicnot(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Expr --> LogicNot");
		#endif
		while ( simple_parser_iskeyword(pParser,K_AND) || simple_parser_isoperator(pParser,"&&")  || simple_parser_iskeyword(pParser,K_OR) || simple_parser_isoperator(pParser,"||") ) {
			if ( simple_parser_iskeyword(pParser,K_AND) || simple_parser_isoperator(pParser,"&&") ) {
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_JUMPZERO2);
				pMark = simple_parser_icg_getactiveoperation(pParser);
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_logicnot(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_AND);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				nMark = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Expr --> LogicNot");
					puts("Rule : Expr --> Expr 'And' Expr");
				}
				#endif
			}
			else {
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_JUMPONE2);
				pMark = simple_parser_icg_getactiveoperation(pParser);
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_logicnot(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Expr --> LogicNot");
					puts("Rule : Expr --> Expr 'Or' Expr");
				}
				#endif
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_OR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				nMark = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark);
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_logicnot ( Parser *pParser )
{
	int x  ;
	/* LogicNot --> Not EqualOrNot */
	if ( simple_parser_iskeyword(pParser,K_NOT) || simple_parser_isoperator2(pParser,OP_NOT) ) {
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		x = simple_parser_equalornot(pParser);
		#if SIMPLE_PARSERTRACE
		if ( x == 1 ) {
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : LogicNot -> 'not' EqualOrNot ");
		}
		#endif
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_NOT);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(pParser,0);
		return x ;
	}
	x = simple_parser_equalornot(pParser);
	#if SIMPLE_PARSERTRACE
	if ( x == 1 ) {
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : LogicNot -> EqualOrNot ");
	}
	#endif
	return x ;
}

int simple_parser_equalornot ( Parser *pParser )
{
	int x  ;
	/* EqualOrNot --> Compare { =|!= Compare } */
	if ( simple_parser_compare(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : EqualOrNot --> Compare");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_EQUAL) || simple_parser_isoperator2(pParser,OP_NOT) ) {
			if ( simple_parser_isoperator2(pParser,OP_NOT) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
					simple_parser_nexttoken(pParser);
					SIMPLE_PARSER_IGNORENEWLINE ;
					x = simple_parser_compare(pParser);
					if ( x == 0 ) {
						return 0 ;
					}
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_NOTEQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(pParser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : EqualOrNot --> Compare");
						puts("Rule : EqualOrNot --> EqualOrNot '!=' EqualOrNot");
					}
					#endif
				}
				else {
					simple_parser_error(pParser,SIMPLE_PARSER_ERROR_EXPROPERATOR);
					return 0 ;
				}
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_compare(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_EQUAL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : EqualOrNot --> Compare");
					puts("Rule : EqualOrNot --> EqualOrNot '=' EqualOrNot");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_compare ( Parser *pParser )
{
	int x,nEqual  ;
	/* Compare --> BitORXOR { <|>|<=|>= BITORXOR } */
	if ( simple_parser_bitorxor(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Compare --> BitOrXOR");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_LESS) || simple_parser_isoperator2(pParser,OP_GREATER) ) {
			nEqual = 0 ;
			if ( simple_parser_isoperator2(pParser,OP_LESS) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
					nEqual = 1 ;
					simple_parser_nexttoken(pParser);
				}
				x = simple_parser_bitorxor(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				if ( nEqual == 0 ) {
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_LESS);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(pParser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : Compare --> BitOrXOR");
						puts("Rule : Compare --> Compare '<' Compare");
					}
					#endif
				}
				else {
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_LESSEQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(pParser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : Compare --> BitOrXOR");
						puts("Rule : Compare --> Compare '<=' Compare");
					}
					#endif
				}
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
					nEqual = 1 ;
					simple_parser_nexttoken(pParser);
					SIMPLE_PARSER_IGNORENEWLINE ;
				}
				x = simple_parser_bitorxor(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				if ( nEqual == 0 ) {
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_GREATER);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(pParser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : Compare --> BitOrXOR");
						puts("Rule : Compare --> Compare '>' Compare");
					}
					#endif
				}
				else {
					/* Generate Code */
					simple_parser_icg_newoperation(pParser,ICO_GREATEREQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(pParser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : Compare --> BitOrXOR");
						puts("Rule : Compare --> Compare '>=' Compare");
					}
					#endif
				}
			}
			/* Check <> */
			if ( x == 0 ) {
				return 0 ;
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_bitorxor ( Parser *pParser )
{
	int x  ;
	/* BitOrXOR --> BitAnd { | | ^ BitAnd } */
	if ( simple_parser_bitand(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitOrXOR -->  BitAnd");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_BITOR) || simple_parser_isoperator2(pParser,OP_XOR) ) {
			if ( simple_parser_isoperator2(pParser,OP_BITOR) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_bitand(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_BITOR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitOrXOR --> BitAnd");
					puts("Rule : BitOrXOR --> BitOrXOR '|' BitOrXOR");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_bitand(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_BITXOR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitOrXOR --> BitAnd");
					puts("Rule : BitOrXOR --> BitOrXOR '^' BitOrXOR");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_bitand ( Parser *pParser )
{
	int x  ;
	/* BitAnd --> BitShift { & BitShift } */
	if ( simple_parser_bitshift(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitAnd --> BitShift");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_BITAND) ) {
			simple_parser_nexttoken(pParser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_bitshift(pParser);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_BITAND);
			/* Generate Location for nPC for Operator Overloading */
			simple_parser_icg_newoperandint(pParser,0);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			{
				puts("Rule : BitAnd --> BitShift");
				puts("Rule : BitAnd --> BitAnd '&' BitAnd");
			}
			#endif
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_bitshift ( Parser *pParser )
{
	int x  ;
	/* BitShift --> Arith { << | >>  Arith } */
	if ( simple_parser_arithmetic(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitShift --> Arithmetic");
		#endif
		while ( simple_parser_isoperator(pParser,"<<") || simple_parser_isoperator(pParser,">>") ) {
			if ( simple_parser_isoperator(pParser,"<<") ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_arithmetic(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_BITSHL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitShift --> Arithmetic");
					puts("Rule : BitShift --> BitShift '<<' BitShift");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_arithmetic(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_BITSHR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitShift --> Arithmetic");
					puts("Rule : BitShift --> BitShift '>>' BitShift");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_arithmetic ( Parser *pParser )
{
	int x  ;
	/* Arithmetic --> Term { +|- Term } */
	if ( simple_parser_term(pParser) ) {
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Arithmetic --> Term");
		#endif
		x = 1 ;
		while ( simple_parser_isoperator2(pParser,OP_PLUS) || simple_parser_isoperator2(pParser,OP_MINUS) ) {
			if ( simple_parser_isoperator2(pParser,OP_PLUS) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_term(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_SUM);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Arithmetic --> Term");
					puts("Rule : Arithmetic --> Arithmetic + Arithmetic");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_term(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_SUB);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Arithmetic --> Term");
					puts("Rule : Arithmetic --> Arithmetic - Arithmetic");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_term ( Parser *pParser )
{
	int x  ;
	/* Term --> Range { *|/|% Range } */
	if ( simple_parser_range(pParser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Term --> Range");
		#endif
		while ( simple_parser_isoperator2(pParser,OP_MUL) || simple_parser_isoperator2(pParser,OP_DIV) || simple_parser_isoperator2(pParser,OP_REM) ) {
			if ( simple_parser_isoperator2(pParser,OP_MUL) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Term --> Range");
					puts("Rule : Term --> Term * Term ");
				}
				#endif
				x = simple_parser_range(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_MUL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
			}
			else if ( simple_parser_isoperator2(pParser,OP_REM) ) {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_range(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_MOD);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Term --> Range");
					puts("Rule : Term --> Term % Term ");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(pParser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_range(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_DIV);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(pParser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Term --> Range");
					puts("Rule : Term --> Term / Term ");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_range ( Parser *pParser )
{
	int x,nFlag  ;
	/* Range --> Factor : Factor */
	if ( simple_parser_factor(pParser,&nFlag) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		{
			if (nFlag) 
			
			puts("Rule : Factor --> Identifier [ {Mixer} | Assignment | PlusPlus | MinusMinus]");
			puts("Rule : Range --> Factor");
		}
		#endif
		if ( simple_parser_isoperator2(pParser,OP_RANGE) ) {
			simple_parser_nexttoken(pParser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_factor(pParser,&nFlag);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_RANGE);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			{
				if (nFlag) 
				
				puts("Rule : Factor --> Identifier [ {Mixer} | Assignment | PlusPlus | MinusMinus]");
				puts(" Range --> Factor");
				puts(" Range --> Range : Range ");
			}
			#endif
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_factor ( Parser *pParser,int *nFlag )
{
	int x,x2,x3,nLastOperation,nCount,nNOOP,nToken,nMark  ;
	List *pLoadAPos, *pList, *pMark  ;
	char lSetProperty,lequal,nBeforeEqual  ;
	char cFuncName[100]  ;
	char cKeyword[100]  ;
	/* Set Identifier Flag - is 1 when we have Factor -->Identifier */
	*nFlag = 0 ;
	/* Factor --> Identifier  {mixer} [ '=' Expr ] */
	if ( simple_parser_isidentifier(pParser) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
		simple_parser_icg_newoperand(pParser,pParser->TokenText);
		/* Generate Location for nPC of Getter */
		simple_parser_icg_newoperandint(pParser,0);
		simple_parser_nexttoken(pParser);
		/* Set Identifier Flag */
		*nFlag = 1 ;
		nToken = SIMPLE_PARSER_CURRENTTOKEN ;
		SIMPLE_PARSER_PASSNEWLINE ;
		/* Back if we don't have { */
		if ( (SIMPLE_PARSER_CURRENTTOKEN > nToken ) ) {
			if ( ! simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
				simple_parser_settoken(pParser,nToken);
			}
		}
		/* Array Index & Object Dot */
		x = simple_parser_mixer(pParser);
		if ( x == 0 ) {
			return 0 ;
		}
		/*
		**  [ [ = Expr  ] 
		**  Save State before changes by Check Operator 
		*/
		nLastOperation = simple_parser_icg_getlastoperation(pParser) ;
		pList = simple_parser_icg_getactiveoperation(pParser) ;
		/* Check Operator */
		lequal = 1 ;
		if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
			nBeforeEqual = 0 ;
		}
		else if ( simple_parser_isoperator(pParser,"+=") ) {
			nBeforeEqual = 1 ;
		}
		else if ( simple_parser_isoperator(pParser,"-=") ) {
			nBeforeEqual = 2 ;
		}
		else if ( simple_parser_isoperator(pParser,"*=") ) {
			nBeforeEqual = 3 ;
		}
		else if ( simple_parser_isoperator(pParser,"/=") ) {
			nBeforeEqual = 4 ;
		}
		else if ( simple_parser_isoperator(pParser,"%=") ) {
			nBeforeEqual = 5 ;
		}
		else if ( simple_parser_isoperator(pParser,"&=") ) {
			nBeforeEqual = 6 ;
		}
		else if ( simple_parser_isoperator(pParser,"|=") ) {
			nBeforeEqual = 7 ;
		}
		else if ( simple_parser_isoperator(pParser,"^=") ) {
			nBeforeEqual = 8 ;
		}
		else if ( simple_parser_isoperator(pParser,"<<=") ) {
			nBeforeEqual = 9 ;
		}
		else if ( simple_parser_isoperator(pParser,">>=") ) {
			nBeforeEqual = 10 ;
		}
		else {
			lequal = 0 ;
			nBeforeEqual = 0 ;
		}
		if ( (lequal == 1 ) && (pParser->nAssignmentFlag == 1) ) {
			simple_parser_nexttoken(pParser);
			/* Check if the Assignment after object attribute name */
			pLoadAPos = NULL ;
			if ( nLastOperation == ICO_LOADSUBADDRESS ) {
				lSetProperty = 1 ;
			}
			else {
				lSetProperty = 0 ;
				/* When the assignment is after LoadAddress */
				if ( nLastOperation == ICO_LOADADDRESS ) {
					pLoadAPos = pList ;
				}
			}
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENTPOINTER);
			SIMPLE_PARSER_IGNORENEWLINE ;
			pParser->nNoAssignment = 0 ;
			x = simple_parser_expr(pParser);
			#if SIMPLE_PARSERTRACE
			if ( x == 1 ) {
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Assignment -> '=' Expr ");
			}
			#endif
			/* Generate Code */
			if ( (simple_parser_icg_getlastoperation(pParser) != ICO_SETSCOPE) && (pParser->nNoAssignment==0) ) {
				/*
				**  We don't need assignment after ListEnd, because lists directly stored in the Varaible 
				**  We do this when we are not inside Brace 
				*/
				nNOOP = 0 ;
				if ( (simple_parser_icg_getlastoperation(pParser) == ICO_LISTEND) && (pParser->nBraceFlag == 0) ) {
					return x ;
				}
				else if ( (simple_parser_icg_getlastoperation(pParser) == ICO_LISTEND) && (pParser->nBraceFlag >= 1) ) {
					nNOOP = 1 ;
					/*
					**  No Assignment is required but we add ICO_NOOP instead 
					**  ICO_NOOP can be converted to Set Property when we access object attributes inside {} 
					*/
				}
				/*
				**  ICO_SETSCOPE comes after creating new object using NEW, in the case no assignment is required 
				**  Before Equal 
				**  Generate Code 
				*/
				simple_parser_icg_newoperation(pParser,ICO_BEFOREEQUAL);
				simple_parser_icg_newoperandint(pParser,nBeforeEqual);
				if ( lSetProperty == 0 ) {
					if ( nNOOP == 0 ) {
						simple_parser_icg_newoperation(pParser,ICO_ASSIGNMENT);
					}
					else {
						simple_parser_icg_newoperation(pParser,ICO_NOOP);
					}
					/* Add Assignment position to the LoadAddress Instruction */
					if ( pLoadAPos != NULL ) {
						simple_parser_icg_addoperandint(pParser,pLoadAPos,simple_parser_icg_instructionscount(pParser));
					}
				}
				else {
					simple_parser_icg_newoperation(pParser,ICO_SETPROPERTY);
				}
				/* Generate Locations for Setproperty before/after Flag & nPC of Setter */
				simple_parser_icg_newoperandint(pParser,0);
				simple_parser_icg_newoperandint(pParser,0);
				/* Locations is done also for Assignment because assignment can be changed to SetProperty by the VM */
			}
			else {
				pParser->nNoAssignment = 0 ;
			}
			return x ;
		}
		/* ++ & -- */
		if ( simple_parser_ppmm(pParser) ) {
			return 1 ;
		}
		/* Generate Code */
		if ( (simple_parser_icg_getlastoperation(pParser) != ICO_CALL) && (simple_parser_icg_getlastoperation(pParser) != ICO_BRACEEND) ) {
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
		}
		return 1 ;
	}
	/* Factor --> Number */
	if ( simple_parser_isnumber(pParser) ) {
		/* Generate Code */
		if ( strlen(pParser->TokenText) <= 15 ) {
			simple_parser_icg_newoperation(pParser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(pParser,atof(pParser->TokenText));
		}
		else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_NUMERICOVERFLOW);
			simple_parser_nexttoken(pParser);
			return 0 ;
		}
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> Number");
		#endif
		simple_parser_nexttoken(pParser);
		/* ++ and -- */
		if ( simple_parser_ppmm(pParser) ) {
			return 1 ;
		}
		/* Check using '(' after number */
		if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_USINGBRACTAFTERNUM);
			return 0 ;
		}
		return 1 ;
	}
	/* Factor --> Literal */
	if ( simple_parser_isliteral(pParser) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PUSHC);
		simple_parser_icg_newoperand(pParser,pParser->TokenText);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> Literal");
		#endif
		simple_parser_nexttoken(pParser);
		/* Array Index & Object Dot */
		x = simple_parser_mixer(pParser);
		if ( x == 0 ) {
			return 0 ;
		}
		return 1 ;
	}
	/* Factor --> Literal --> ':' Identifier */
	if ( simple_parser_isoperator2(pParser,OP_RANGE) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) || simple_parser_isanykeyword(pParser) ) {
			nCount = simple_parser_icg_instructionscount(pParser);
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_PUSHC);
			if ( simple_parser_isanykeyword(pParser) ) {
				strcpy(cKeyword,simple_scanner_getkeywordtext(pParser->TokenText));
				simple_stsimple_lower(cKeyword);
				simple_parser_icg_newoperand(pParser,cKeyword);
			}
			else {
				simple_parser_icg_newoperand(pParser,pParser->TokenText);
			}
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			{
				puts("Rule : Literal --> ':' Identifier ['=' Expr]");
				puts("Rule : Factor --> Literal");
			}
			#endif
			simple_parser_nexttoken(pParser);
			/* Hash --> '=' Expression */
			if ( simple_parser_isoperator2(pParser,OP_EQUAL) ) {
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				simple_parser_icg_insertoperation(pParser,nCount,ICO_LISTSTART);
				simple_parser_icg_insertoperation(pParser,nCount+2,ICO_LISTITEM);
				/* Go to last operation, because insert change the active operation */
				SIMPLE_PARSER_ICG_GOTOLASTOP ;
				if ( simple_parser_expr(pParser) ) {
					/* Generate Code */
					if ( simple_parser_icg_getlastoperation(pParser) != ICO_LISTEND ) {
						simple_parser_icg_newoperation(pParser,ICO_LISTITEM);
					}
					simple_parser_icg_newoperation(pParser,ICO_LISTEND);
					return 1 ;
				}
				return 0 ;
			}
			return 1 ;
		}
	}
	/* Factor --> Negative (-) Expr */
	if ( simple_parser_isoperator2(pParser,OP_MINUS) ) {
		simple_parser_nexttoken(pParser);
		x = simple_parser_expr(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_NEG);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(pParser,0);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> '-' Expr");
		#endif
		return x ;
	}
	else if ( simple_parser_isoperator2(pParser,OP_BITNOT) ) {
		/* bitnot (~) Expr */
		simple_parser_nexttoken(pParser);
		x = simple_parser_expr(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_BITNOT);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(pParser,0);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> '~' Expr");
		#endif
		return x ;
	}
	/* Factor --> & */
	else if ( simple_parser_isoperator2(pParser,OP_BITAND) ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_RETITEMREF);
		if ( simple_parser_expr(pParser) ) {
			return 1 ;
		}
	}
	/* Factor --> ( Expr ) */
	if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
		simple_parser_nexttoken(pParser);
		x = pParser->nAssignmentFlag ;
		pParser->nAssignmentFlag = 0 ;
		if ( simple_parser_expr(pParser) ) {
			pParser->nAssignmentFlag = x ;
			if ( simple_parser_isoperator2(pParser,OP_FCLOSE) ) {
				simple_parser_nexttoken(pParser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Factor --> '(' Expr ')'");
				#endif
				return 1 ;
			}
			else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_MISSPARENTHESES);
				return 0 ;
			}
		}
		return 0 ;
	}
	/* Factor --> List */
	if ( simple_parser_isoperator2(pParser,OP_LOPEN) ) {
		x = simple_parser_list(pParser) ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> List");
		#endif
		return x ;
	}
	/* Factor --> New Identifier */
	if ( simple_parser_iskeyword(pParser,K_NEW) ) {
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_NEWOBJ);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> New Identifier {'.' Identifier }  ");
		#endif
		if ( simple_parser_namedotname(pParser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_SETSCOPE);
			SIMPLE_PARSER_IGNORENEWLINE ;
			if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
				x = simple_parser_mixer(pParser);
				pParser->nNoAssignment = 1 ;
				return x ;
			}
			else if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
				/*
				**  Calling the init method using { } 
				**  Generate Code (Start Brace) 
				*/
				simple_parser_icg_newoperation(pParser,ICO_PUSHV);
				simple_parser_icg_newoperation(pParser,ICO_BRACESTART);
				simple_parser_icg_newoperation(pParser,ICO_CALLCLASSINIT);
				simple_parser_icg_newoperandint(pParser,1);
				/* Generate Code ( Call Function ) */
				simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
				simple_parser_icg_newoperand(pParser,"init");
				/* Generate Location for nPC of Getter */
				simple_parser_icg_newoperandint(pParser,0);
				/* Function Parameters */
				pParser->nFuncCallOnly = 1 ;
				simple_parser_mixer(pParser);
				pParser->nFuncCallOnly = 0 ;
				/* Generate Code (End Brace) */
				simple_parser_icg_newoperation(pParser,ICO_CALLCLASSINIT);
				simple_parser_icg_newoperandint(pParser,0);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_mixer(pParser);
				simple_parser_icg_newoperation(pParser,ICO_BRACEEND);
				pParser->nNoAssignment = 1 ;
				return x ;
			}
			pParser->nNoAssignment = 1 ;
			/*
			**  Generate Code 
			**  PUSHV enable using braces to access the object 
			*/
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
			return 1 ;
		}
	}
	/* Factor --> Anonymous Function */
	if ( simple_parser_iskeyword(pParser,K_FUNC) || simple_parser_iskeyword(pParser,K_DEF) ) {
		simple_parser_nexttoken(pParser);
		/*
		**  Generate Code 
		**  Push Function Name, then jump after the function code 
		*/
		simple_parser_icg_newoperation(pParser,ICO_PUSHC);
		/* Note : the function name must be in lower case */
		sprintf( cFuncName , "_simple_anonymous_func_%d" , SIMPLE_PARSER_OPERATIONID ) ;
		simple_parser_icg_newoperand(pParser,cFuncName);
		simple_parser_icg_newoperation(pParser,ICO_JUMP);
		pMark = simple_parser_icg_getactiveoperation(pParser);
		/* Define the Function - as public (not related to any class) */
		pList = simple_list_newlist_gc(pParser->pRingState,pParser->pRingState->pRingFunctionsMap);
		simple_list_addstsimple_gc(pParser->pRingState,pList,cFuncName);
		/* Note +1 because instruction ICO_NEWFUNC will come next */
		simple_list_addint_gc(pParser->pRingState,pList,SIMPLE_PARSER_OPERATIONID+1);
		simple_list_addstsimple_gc(pParser->pRingState,pList,simple_list_getstring(pParser->pRingState->pRingFilesStack,simple_list_getsize(pParser->pRingState->pRingFilesStack)));
		simple_list_addint_gc(pParser->pRingState,pList,0);
		simple_parser_icg_newoperation(pParser,ICO_NEWFUNC);
		simple_parser_icg_newoperand(pParser,cFuncName);
		/* Get Function Parameters */
		if ( simple_parser_isidentifier(pParser) || simple_parser_isoperator2(pParser,OP_FOPEN) ) {
			if (! simple_parser_paralist(pParser)) return 0 ;
		}
		/* Get Function Code */
		if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) ) {
			simple_parser_nexttoken(pParser);
			x = pParser->nAssignmentFlag ;
			x2 = pParser->nNoAssignment ;
			x3 = pParser->nBraceFlag ;
			pParser->nAssignmentFlag = 1 ;
			pParser->nBraceFlag = 0 ;
			while ( simple_parser_stmt(pParser) ) {
				if ( pParser->ActiveToken == pParser->TokensCount ) {
					break ;
				}
			}
			pParser->nAssignmentFlag = x ;
			pParser->nNoAssignment = x2 ;
			pParser->nBraceFlag = x3 ;
			if ( simple_parser_isoperator2(pParser,OP_BRACECLOSE) ) {
				simple_parser_nexttoken(pParser);
				/* Generate Code */
				simple_parser_icg_newoperation(pParser,ICO_RETNULL);
				nMark = simple_parser_icg_newlabel(pParser);
				simple_parser_icg_addoperandint(pParser,pMark,nMark);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : AnonymousFunction --> Func ParaList '{' Statement '}'");
				#endif
				return 1 ;
			}
		}
	}
	/* Factor --> Call Identifier ( parameters ) */
	if ( simple_parser_iskeyword(pParser,K_CALL) ) {
		simple_parser_nexttoken(pParser);
		if ( simple_parser_isidentifier(pParser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(pParser,pParser->TokenText);
			/* Generate Location for nPC of Getter */
			simple_parser_icg_newoperandint(pParser,0);
			simple_parser_nexttoken(pParser);
			/* Object Attributes */
			if ( simple_parser_objattributes(pParser) == 0 ) {
				return 0 ;
			}
			simple_parser_icg_newoperation(pParser,ICO_PUSHV);
			simple_parser_icg_newoperation(pParser,ICO_ANONYMOUS);
			if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
				return simple_parser_mixer(pParser) ;
			}
			else {
				return 0 ;
			}
		}
		else {
			return 0 ;
		}
	}
	return 0 ;
}

int simple_parser_mixer ( Parser *pParser )
{
	int x,nCallMethod,nStatus,nFlag  ;
	/*
	**  { . Identifier } 
	**  Object Attributes 
	*/
	if ( simple_parser_objattributes(pParser) == 0 ) {
		return 0 ;
	}
	/* [Index]  to access array element, Index = Expression */
	if ( simple_parser_isoperator2(pParser,OP_LOPEN) ) {
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_expr(pParser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_LOADINDEXADDRESS);
			/* Add 0 For Operator Overloading */
			simple_parser_icg_newoperandint(pParser,0);
			if ( simple_parser_isoperator2(pParser,OP_LCLOSE) ) {
				simple_parser_nexttoken(pParser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Mixer -> '[' Expr ']' ");
				#endif
				x = simple_parser_mixer(pParser);
				if ( x == 0 ) {
					return 0 ;
				}
			}
			else {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_MISSBRACKETS);
				return 0 ;
			}
		}
		else {
			return 0 ;
		}
	}
	/* |  [ ( [ Expr { , Expr } ] ) ]  ] */
	if ( simple_parser_isoperator2(pParser,OP_FOPEN) ) {
		/* Generate Code */
		nCallMethod = 0 ;
		if ( simple_parser_icg_getlastoperation(pParser) == ICO_LOADADDRESS ) {
			simple_parser_icg_setlastoperation(pParser,ICO_LOADFUNC);
			/* Delete Locations for Getter */
			simple_list_deleteitem_gc(pParser->pRingState,simple_parser_icg_getactiveoperation(pParser),3);
		}
		else if ( simple_parser_icg_getlastoperation(pParser) == ICO_LOADSUBADDRESS ) {
			simple_parser_icg_setlastoperation(pParser,ICO_LOADMETHOD);
			/* Delete Locations for Setter/Getter */
			simple_list_deleteitem_gc(pParser->pRingState,simple_parser_icg_getactiveoperation(pParser),4);
			simple_list_deleteitem_gc(pParser->pRingState,simple_parser_icg_getactiveoperation(pParser),3);
			nCallMethod = 1 ;
		}
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(pParser,OP_FCLOSE) ) {
			simple_parser_nexttoken(pParser);
			/* Generate Code */
			simple_parser_gencall(pParser,nCallMethod);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Mixer -> '(' [Expr { ',' Expr} ] ')' ");
			#endif
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_mixer(pParser);
			return x ;
		}
		while ( 1 ) {
			nFlag = pParser->nAssignmentFlag ;
			pParser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(pParser) ) {
				pParser->nAssignmentFlag = nFlag ;
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(pParser,OP_COMMA) ) {
					simple_parser_nexttoken(pParser);
				}
				else if ( simple_parser_isoperator2(pParser,OP_FCLOSE) ) {
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : Mixer -> '(' [Expr { ',' Expr} ] ')' ");
					#endif
					simple_parser_nexttoken(pParser);
					/* Generate Code */
					simple_parser_gencall(pParser,nCallMethod);
					x = simple_parser_mixer(pParser);
					return x ;
				}
				else {
					simple_parser_error(pParser,SIMPLE_PARSER_ERROR_MISSPARENTHESES);
					return 0 ;
				}
			}
			else {
				return 0 ;
			}
			SIMPLE_PARSER_IGNORENEWLINE ;
		}
	}
	/* Function Call Only */
	if ( pParser->nFuncCallOnly == 1 ) {
		return 1 ;
	}
	/* '{' {Statement} '}' */
	if ( simple_parser_isoperator2(pParser,OP_BRACEOPEN) && pParser->nControlStructureExpr == 0 ) {
		pParser->nBraceFlag++ ;
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PUSHV);
		simple_parser_icg_newoperation(pParser,ICO_BRACESTART);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Mixer --> '{' {Statement} BraceEnd");
		#endif
		/* if ismethod(self,"bracestart") bracestart() ok */
		simple_parser_gencallbracemethod(pParser,"bracestart");
		simple_parser_nexttoken(pParser);
		nStatus = pParser->nAssignmentFlag ;
		pParser->nAssignmentFlag = 1 ;
		while ( simple_parser_stmt(pParser) ) {
			if ( pParser->ActiveToken == pParser->TokensCount ) {
				break ;
			}
		}
		pParser->nAssignmentFlag = nStatus ;
		if ( simple_parser_isoperator2(pParser,OP_BRACECLOSE) ) {
			pParser->nBraceFlag-- ;
			/*
			**  Generate Code 
			**  if ismethod(self,"braceend") braceend() ok 
			*/
			simple_parser_gencallbracemethod(pParser,"braceend");
			simple_parser_icg_newoperation(pParser,ICO_BRACEEND);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : BraceEnd --> '}' ");
			#endif
			simple_parser_nexttoken(pParser);
			x = simple_parser_mixer(pParser);
			return x ;
		}
		else {
			simple_parser_error(pParser,SIMPLE_PARSER_ERROR_BRACESNOTCLOSED);
		}
	}
	/* This function return 1 because the mixer is optional and comes after identifier */
	return 1 ;
}

void simple_parser_gencall ( Parser *pParser,int nCallMethod )
{
	/* Generate Code */
	simple_parser_icg_newoperation(pParser,ICO_CALL);
	if ( nCallMethod == 1 ) {
		/* Add 0 For Operator Overloading */
		simple_parser_icg_newoperandint(pParser,0);
		/* Add 1 so the call instruction move list from aBeforeObjState to pObjState */
		simple_parser_icg_newoperandint(pParser,1);
		simple_parser_icg_newoperation(pParser,ICO_AFTERCALLMETHOD);
	}
	else {
		/* Add 0 For Operator Overloading */
		simple_parser_icg_newoperandint(pParser,0);
		/*
		**  The No Operation Instruction may be converted to AfterCallMethod during runtime 
		**  This happens when we call method like functions inside object { } 
		*/
		simple_parser_icg_newoperation(pParser,ICO_NOOP);
	}
}

int simple_parser_ppmm ( Parser *pParser )
{
	/* ++ & -- */
	if ( simple_parser_isoperator(pParser,"++") ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_PLUSPLUS);
		simple_parser_icg_newoperation(pParser,ICO_PUSHV);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : PlusPlus --> '++'");
		#endif
		return 1 ;
	}
	else if ( simple_parser_isoperator(pParser,"--") ) {
		simple_parser_nexttoken(pParser);
		/* Generate Code */
		simple_parser_icg_newoperation(pParser,ICO_MINUSMINUS);
		simple_parser_icg_newoperation(pParser,ICO_PUSHV);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : MinusMinus --> '--'");
		#endif
		return 1 ;
	}
	return 0 ;
}

void simple_parser_gencallbracemethod ( Parser *pParser,const char *cMethod )
{
	int nMark1  ;
	List *pMark  ;
	/* if ismethod(self,cMethod) cMethod() ok */
	simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
	simple_parser_icg_newoperand(pParser,"ismethod");
	simple_parser_icg_newoperation(pParser,ICO_LOADADDRESS);
	simple_parser_icg_newoperand(pParser,"self");
	simple_parser_icg_newoperandint(pParser,0);
	simple_parser_icg_newoperation(pParser,ICO_PUSHV);
	simple_parser_icg_newoperation(pParser,ICO_PUSHC);
	simple_parser_icg_newoperand(pParser,cMethod);
	simple_parser_icg_newoperation(pParser,ICO_CALL);
	simple_parser_icg_newoperation(pParser,ICO_NOOP);
	simple_parser_icg_newoperation(pParser,ICO_PUSHV);
	/* Jump */
	simple_parser_icg_newoperation(pParser,ICO_JUMPZERO);
	pMark = simple_parser_icg_getactiveoperation(pParser);
	simple_parser_icg_newoperation(pParser,ICO_LOADFUNC);
	simple_parser_icg_newoperand(pParser,cMethod);
	simple_parser_icg_newoperation(pParser,ICO_CALL);
	simple_parser_icg_newoperation(pParser,ICO_NOOP);
	simple_parser_icg_newoperation(pParser,ICO_PUSHV);
	simple_parser_icg_newoperation(pParser,ICO_FREESTACK);
	nMark1 = simple_parser_icg_newlabel(pParser);
	simple_parser_icg_addoperandint(pParser,pMark,nMark1);
}

int simple_parser_objattributes ( Parser *pParser )
{
	/* { . Identifier } */
	while ( simple_parser_isoperator2(pParser,OP_DOT) ) {
		simple_parser_nexttoken(pParser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		/* we support literal to be able to call methods contains operators in the name */
		if ( simple_parser_isidentifier(pParser) || simple_parser_isliteral(pParser) ) {
			/* Prevent Accessing the self reference from outside the object */
			if ( strcmp(pParser->TokenText,"self") == 0 ) {
				simple_parser_error(pParser,SIMPLE_PARSER_ERROR_ACCESSSELFREF);
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(pParser,ICO_LOADSUBADDRESS);
			simple_parser_icg_newoperand(pParser,pParser->TokenText);
			/* Generate Location for nPC of Getter - When we access object attribute using { } */
			simple_parser_icg_newoperandint(pParser,0);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Mixer -> '.' Identifier ");
			#endif
			simple_parser_nexttoken(pParser);
		}
		else {
			return 0 ;
		}
	}
	return 1 ;
}

