
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

/*
**  The First Step  - Start Here 
*/

#include "../include/simple.h"
/*
**  Blocks 
**  Grammar 
*/

int simple_parser_expr ( Parser *parser )
{
	int x,nMark  ;
	List *pMark  ;
	/* Expr --> LogicNot { and|or LogicNot } */
	if ( simple_parser_logicnot(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Expr --> LogicNot");
		#endif
		while ( simple_parser_iskeyword(parser,KEYWORD_AND) || simple_parser_isoperator(parser,"&&")  || simple_parser_iskeyword(parser,KEYWORD_OR) || simple_parser_isoperator(parser,"||") ) {
			if ( simple_parser_iskeyword(parser,KEYWORD_AND) || simple_parser_isoperator(parser,"&&") ) {
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_JUMPZERO2);
				pMark = simple_parser_icg_getactiveoperation(parser);
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_logicnot(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_AND);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				nMark = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark);
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
				simple_parser_icg_newoperation(parser,ICO_JUMPONE2);
				pMark = simple_parser_icg_getactiveoperation(parser);
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_logicnot(parser);
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
				simple_parser_icg_newoperation(parser,ICO_OR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				nMark = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark);
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_logicnot ( Parser *parser )
{
	int x  ;
	/* LogicNot --> Not EqualOrNot */
	if ( simple_parser_iskeyword(parser,KEYWORD_NOT) || simple_parser_isoperator2(parser,OP_NOT) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		x = simple_parser_equalornot(parser);
		#if SIMPLE_PARSERTRACE
		if ( x == 1 ) {
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : LogicNot -> 'not' EqualOrNot ");
		}
		#endif
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_NOT);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(parser,0);
		return x ;
	}
	x = simple_parser_equalornot(parser);
	#if SIMPLE_PARSERTRACE
	if ( x == 1 ) {
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : LogicNot -> EqualOrNot ");
	}
	#endif
	return x ;
}

int simple_parser_equalornot ( Parser *parser )
{
	int x  ;
	/* EqualOrNot --> Compare { =|!= Compare } */
	if ( simple_parser_compare(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : EqualOrNot --> Compare");
		#endif
		while ( simple_parser_isoperator2(parser,OP_EQUAL) || simple_parser_isoperator2(parser,OP_NOT) ) {
			if ( simple_parser_isoperator2(parser,OP_NOT) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
					simple_parser_nexttoken(parser); SIMPLE_PARSER_IGNORENEWLINE ;
					x = simple_parser_compare(parser);
					if ( x == 0 ) {
						return 0 ;
					}
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_NOTEQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(parser,0);
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					{
						puts("Rule : EqualOrNot --> Compare");
						puts("Rule : EqualOrNot --> EqualOrNot '!=' EqualOrNot");
					}
					#endif
				}
				else {
					parser_error(parser,PARSER_ERROR_EXPROPERATOR);
					return 0 ;
				}
			}
			else {
				simple_parser_nexttoken(parser);
				accept_token_token( parser, OP_EQUAL);
                                SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_compare(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_EQUAL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : EqualOrNot --> Compare");
					puts("Rule : EqualOrNot --> EqualOrNot '==' EqualOrNot");
				}
				#endif
			}
		}
		return x ;
	}
	return 0 ;
}

int simple_parser_compare ( Parser *parser )
{
	int x,nEqual  ;
	/* Compare --> BitORXOR { <|>|<=|>= BITORXOR } */
	if ( simple_parser_bitorxor(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Compare --> BitOrXOR");
		#endif
		while ( simple_parser_isoperator2(parser,OP_LESS) || simple_parser_isoperator2(parser,OP_GREATER) ) {
			nEqual = 0 ;
			if ( simple_parser_isoperator2(parser,OP_LESS) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
					nEqual = 1 ;
					simple_parser_nexttoken(parser);
				}
				x = simple_parser_bitorxor(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				if ( nEqual == 0 ) {
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_LESS);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(parser,0);
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
					simple_parser_icg_newoperation(parser,ICO_LESSEQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(parser,0);
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
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
					nEqual = 1 ;
					simple_parser_nexttoken(parser);
					SIMPLE_PARSER_IGNORENEWLINE ;
				}
				x = simple_parser_bitorxor(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				if ( nEqual == 0 ) {
					/* Generate Code */
					simple_parser_icg_newoperation(parser,ICO_GREATER);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(parser,0);
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
					simple_parser_icg_newoperation(parser,ICO_GREATEREQUAL);
					/* Generate Location for nPC for Operator Overloading */
					simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_bitorxor ( Parser *parser )
{
	int x  ;
	/* BitOrXOR --> BitAnd { | | ^ BitAnd } */
	if ( simple_parser_bitand(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitOrXOR -->  BitAnd");
		#endif
		while ( simple_parser_isoperator2(parser,OP_BITOR) || simple_parser_isoperator2(parser,OP_XOR) ) {
			if ( simple_parser_isoperator2(parser,OP_BITOR) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_bitand(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_BITOR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitOrXOR --> BitAnd");
					puts("Rule : BitOrXOR --> BitOrXOR '|' BitOrXOR");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_bitand(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_BITXOR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_bitand ( Parser *parser )
{
	int x  ;
	/* BitAnd --> BitShift { & BitShift } */
	if ( simple_parser_bitshift(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitAnd --> BitShift");
		#endif
		while ( simple_parser_isoperator2(parser,OP_BITAND) ) {
			simple_parser_nexttoken(parser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_bitshift(parser);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_BITAND);
			/* Generate Location for nPC for Operator Overloading */
			simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_bitshift ( Parser *parser )
{
	int x  ;
	/* BitShift --> Arith { << | >>  Arith } */
	if ( simple_parser_arithmetic(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : BitShift --> Arithmetic");
		#endif
		while ( simple_parser_isoperator(parser,"<<") || simple_parser_isoperator(parser,">>") ) {
			if ( simple_parser_isoperator(parser,"<<") ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_arithmetic(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_BITSHL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : BitShift --> Arithmetic");
					puts("Rule : BitShift --> BitShift '<<' BitShift");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_arithmetic(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_BITSHR);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_arithmetic ( Parser *parser )
{
	int x  ;
	/* Arithmetic --> Term { +|- Term } */
	if ( simple_parser_term(parser) ) {
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Arithmetic --> Term");
		#endif
		x = 1 ;
		while ( simple_parser_isoperator2(parser,OP_PLUS) || simple_parser_isoperator2(parser,OP_MINUS) ) {
			if ( simple_parser_isoperator2(parser,OP_PLUS) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_term(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_SUM);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Arithmetic --> Term");
					puts("Rule : Arithmetic --> Arithmetic + Arithmetic");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_term(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_SUB);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_term ( Parser *parser )
{
	int x  ;
	/* Term --> Range { *|/|% Range } */
	if ( simple_parser_range(parser) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Term --> Range");
		#endif
		while ( simple_parser_isoperator2(parser,OP_MUL) || simple_parser_isoperator2(parser,OP_DIV) || simple_parser_isoperator2(parser,OP_REM) ) {
			if ( simple_parser_isoperator2(parser,OP_MUL) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Term --> Range");
					puts("Rule : Term --> Term * Term ");
				}
				#endif
				x = simple_parser_range(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_MUL);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
			}
			else if ( simple_parser_isoperator2(parser,OP_REM) ) {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_range(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_MOD);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				{
					puts("Rule : Term --> Range");
					puts("Rule : Term --> Term % Term ");
				}
				#endif
			}
			else {
				simple_parser_nexttoken(parser);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_range(parser);
				if ( x == 0 ) {
					return 0 ;
				}
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_DIV);
				/* Generate Location for nPC for Operator Overloading */
				simple_parser_icg_newoperandint(parser,0);
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

int simple_parser_range ( Parser *parser )
{
	int x,nFlag  ;
	/* Range --> Factor : Factor */
	if ( simple_parser_factor(parser,&nFlag) ) {
		x = 1 ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		{
			if (nFlag) 
			
			puts("Rule : Factor --> Identifier [ {Mixer} | Assignment | PlusPlus | MinusMinus]");
			puts("Rule : Range --> Factor");
		}
		#endif
		if ( simple_parser_isoperator2(parser,OP_RANGE) ) {
			simple_parser_nexttoken(parser);
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_factor(parser,&nFlag);
			if ( x == 0 ) {
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_RANGE);
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

int simple_parser_factor ( Parser *parser,int *nFlag )
{
	int x,x2,x3,nLastOperation,count,nNOOP,nToken,nMark  ;
	List *pLoadAPos, *list, *pMark  ;
	char lSetProperty,lequal,nBeforeEqual  ;
	char cBlockName[100]  ;
	char keyword[100]  ;
	/* Set Identifier Flag - is 1 when we have Factor -->Identifier */
	*nFlag = 0 ;
	/* Factor --> Identifier  {mixer} [ '=' Expr ] */
	if ( simple_parser_isidentifier(parser) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
		simple_parser_icg_newoperand(parser,parser->TokenText);
		/* Generate Location for nPC of Getter */
		simple_parser_icg_newoperandint(parser,0);
		simple_parser_nexttoken(parser);
		/* Set Identifier Flag */
		*nFlag = 1 ;
		nToken = SIMPLE_PARSER_CURRENTTOKEN ;
		SIMPLE_PARSER_PASSNEWLINE ;
		/* Back if we don't have { */
		if ( (SIMPLE_PARSER_CURRENTTOKEN > nToken ) ) {
			if ( ! simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
				simple_parser_settoken(parser,nToken);
			}
		}
		/* Array Index & Object Dot */
		x = simple_parser_mixer(parser);
		if ( x == 0 ) {
			return 0 ;
		}
		/*
		**  [ [ = Expr  ] 
		**  Save State before changes by Check Operator 
		*/
		nLastOperation = simple_parser_icg_getlastoperation(parser) ;
		list = simple_parser_icg_getactiveoperation(parser) ;
		/* Check Operator */
		lequal = 1 ;
		if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
			nBeforeEqual = 0 ;
		}
		else if ( simple_parser_isoperator(parser,"+=") ) {
			nBeforeEqual = 1 ;
		}
		else if ( simple_parser_isoperator(parser,"-=") ) {
			nBeforeEqual = 2 ;
		}
		else if ( simple_parser_isoperator(parser,"*=") ) {
			nBeforeEqual = 3 ;
		}
		else if ( simple_parser_isoperator(parser,"/=") ) {
			nBeforeEqual = 4 ;
		}
		else if ( simple_parser_isoperator(parser,"%=") ) {
			nBeforeEqual = 5 ;
		}
		else if ( simple_parser_isoperator(parser,"&=") ) {
			nBeforeEqual = 6 ;
		}
		else if ( simple_parser_isoperator(parser,"|=") ) {
			nBeforeEqual = 7 ;
		}
		else if ( simple_parser_isoperator(parser,"^=") ) {
			nBeforeEqual = 8 ;
		}
		else if ( simple_parser_isoperator(parser,"<<=") ) {
			nBeforeEqual = 9 ;
		}
		else if ( simple_parser_isoperator(parser,">>=") ) {
			nBeforeEqual = 10 ;
		}
		else {
			lequal = 0 ;
			nBeforeEqual = 0 ;
		}
		if ( (lequal == 1 ) && (parser->nAssignmentFlag == 1) ) {
			simple_parser_nexttoken(parser);
			/* Check if the Assignment after object attribute name */
			pLoadAPos = NULL ;
			if ( nLastOperation == ICO_LOADSUBADDRESS ) {
				lSetProperty = 1 ;
			}
			else {
				lSetProperty = 0 ;
				/* When the assignment is after LoadAddress */
				if ( nLastOperation == ICO_LOADADDRESS ) {
					pLoadAPos = list ;
				}
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_ASSIGNMENTPOINTER);
			SIMPLE_PARSER_IGNORENEWLINE ;
			parser->nNoAssignment = 0 ;
			x = simple_parser_expr(parser);
			#if SIMPLE_PARSERTRACE
			if ( x == 1 ) {
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Assignment -> '=' Expr ");
			}
			#endif
			/* Generate Code */
			if ( (simple_parser_icg_getlastoperation(parser) != ICO_SETSCOPE) && (parser->nNoAssignment==0) ) {
				/*
				**  We don't need assignment after ListEnd, because lists directly stored in the Varaible 
				**  We do this when we are not inside Brace 
				*/
				nNOOP = 0 ;
				if ( (simple_parser_icg_getlastoperation(parser) == ICO_LISTEND) && (parser->nBraceFlag == 0) ) {
					return x ;
				}
				else if ( (simple_parser_icg_getlastoperation(parser) == ICO_LISTEND) && (parser->nBraceFlag >= 1) ) {
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
				simple_parser_icg_newoperation(parser,ICO_BEFOREEQUAL);
				simple_parser_icg_newoperandint(parser,nBeforeEqual);
				if ( lSetProperty == 0 ) {
					if ( nNOOP == 0 ) {
						simple_parser_icg_newoperation(parser,ICO_ASSIGNMENT);
					}
					else {
						simple_parser_icg_newoperation(parser,ICO_NOOP);
					}
					/* Add Assignment position to the LoadAddress Instruction */
					if ( pLoadAPos != NULL ) {
						simple_parser_icg_addoperandint(parser,pLoadAPos,simple_parser_icg_instructionscount(parser));
					}
				}
				else {
					simple_parser_icg_newoperation(parser,ICO_SETPROPERTY);
				}
				/* Generate Locations for Setproperty before/after Flag & nPC of Setter */
				simple_parser_icg_newoperandint(parser,0);
				simple_parser_icg_newoperandint(parser,0);
				/* Locations is done also for Assignment because assignment can be changed to SetProperty by the VM */
			}
			else {
				parser->nNoAssignment = 0 ;
			}
			return x ;
		}
		/* ++ & -- */
		if ( simple_parser_ppmm(parser) ) {
			return 1 ;
		}
		/* Generate Code */
		if ( (simple_parser_icg_getlastoperation(parser) != ICO_CALL) && (simple_parser_icg_getlastoperation(parser) != ICO_BRACEEND) ) {
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
		}
		return 1 ;
	}
	/* Factor --> Number */
	if ( simple_parser_isnumber(parser) ) {
		/* Generate Code */
		if ( strlen(parser->TokenText) <= 15 ) {
			simple_parser_icg_newoperation(parser,ICO_PUSHN);
			simple_parser_icg_newoperanddouble(parser,atof(parser->TokenText));
		}
		else {
			parser_error(parser,PARSER_ERROR_NUMERICOVERFLOW);
			simple_parser_nexttoken(parser);
			return 0 ;
		}
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> Number");
		#endif
		simple_parser_nexttoken(parser);
		/* ++ and -- */
		if ( simple_parser_ppmm(parser) ) {
			return 1 ;
		}
		/* Check using '(' after number */
		if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
			parser_error(parser,PARSER_ERROR_USINGBRACTAFTERNUM);
			return 0 ;
		}
		return 1 ;
	}
	/* Factor --> Literal */
	if ( simple_parser_isliteral(parser) ) {
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_PUSHC);
		simple_parser_icg_newoperand(parser,parser->TokenText);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> Literal");
		#endif
		simple_parser_nexttoken(parser);
		/* Array Index & Object Dot */
		x = simple_parser_mixer(parser);
		if ( x == 0 ) {
			return 0 ;
		}
		return 1 ;
	}
	/* Factor --> Literal --> ':' Identifier */
	if ( simple_parser_isoperator2(parser,OP_RANGE) ) {
		simple_parser_nexttoken(parser);
		if ( simple_parser_isidentifier(parser) || simple_parser_isanykeyword(parser) ) {
			count = simple_parser_icg_instructionscount(parser);
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_PUSHC);
			if ( simple_parser_isanykeyword(parser) ) {
				strcpy(keyword,simple_scanner_getkeywordtext(parser->TokenText));
				simple_parser_icg_newoperand(parser,keyword);
			}
			else {
				simple_parser_icg_newoperand(parser,parser->TokenText);
			}
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			{
				puts("Rule : Literal --> ':' Identifier ['=' Expr]");
				puts("Rule : Factor --> Literal");
			}
			#endif
			simple_parser_nexttoken(parser);
			/* Hash --> '=' Expression */
			if ( simple_parser_isoperator2(parser,OP_EQUAL) ) {
				simple_parser_nexttoken(parser);
				/* Generate Code */
				simple_parser_icg_insertoperation(parser,count,ICO_LISTSTART);
				simple_parser_icg_insertoperation(parser,count+2,ICO_LISTITEM);
				/* Go to last operation, because insert change the active operation */
				SIMPLE_PARSER_ICG_GOTOLASTOP ;
				if ( simple_parser_expr(parser) ) {
					/* Generate Code */
					if ( simple_parser_icg_getlastoperation(parser) != ICO_LISTEND ) {
						simple_parser_icg_newoperation(parser,ICO_LISTITEM);
					}
					simple_parser_icg_newoperation(parser,ICO_LISTEND);
					return 1 ;
				}
				return 0 ;
			}
			return 1 ;
		}
	}
	/* Factor --> Negative (-) Expr */
	if ( simple_parser_isoperator2(parser,OP_MINUS) ) {
		simple_parser_nexttoken(parser);
		x = simple_parser_expr(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_NEG);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(parser,0);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> '-' Expr");
		#endif
		return x ;
	}
	else if ( simple_parser_isoperator2(parser,OP_BITNOT) ) {
		/* bitnot (~) Expr */
		simple_parser_nexttoken(parser);
		x = simple_parser_expr(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_BITNOT);
		/* Generate Location for nPC for Operator Overloading */
		simple_parser_icg_newoperandint(parser,0);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> '~' Expr");
		#endif
		return x ;
	}
	/* Factor --> & */
	else if ( simple_parser_isoperator2(parser,OP_BITAND) ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_RETITEMREF);
		if ( simple_parser_expr(parser) ) {
			return 1 ;
		}
	}
	/* Factor --> ( Expr ) */
	if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
		simple_parser_nexttoken(parser);
		x = parser->nAssignmentFlag ;
		parser->nAssignmentFlag = 0 ;
		if ( simple_parser_expr(parser) ) {
			parser->nAssignmentFlag = x ;
			if ( simple_parser_isoperator2(parser,OP_FCLOSE) ) {
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Factor --> '(' Expr ')'");
				#endif
				return 1 ;
			}
			else {
				parser_error(parser,PARSER_ERROR_MISSPARENTHESES);
				return 0 ;
			}
		}
		return 0 ;
	}
	/* Factor --> List */
	if ( simple_parser_isoperator2(parser,OP_LOPEN) ) {
		x = simple_parser_list(parser) ;
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> List");
		#endif
		return x ;
	}
	/* Factor --> New Identifier */
	if ( simple_parser_iskeyword(parser,KEYWORD_NEW) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_NEWOBJ); 
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Factor --> New Identifier {'.' Identifier }  ");
		#endif
		if ( simple_parser_namedotname(parser) ) {
			/* Generate Code */ 
			simple_parser_icg_newoperation(parser,ICO_SETSCOPE);
			SIMPLE_PARSER_IGNORENEWLINE ;
			if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
				x = simple_parser_mixer(parser);
				parser->nNoAssignment = 1 ;
				return x ;
			}
			else if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
				/*
				**  Calling the init method using { } 
				**  Generate Code (Start Brace) 
				*/
				simple_parser_icg_newoperation(parser,ICO_PUSHV);
				simple_parser_icg_newoperation(parser,ICO_BRACESTART);
				simple_parser_icg_newoperation(parser,ICO_CALLCLASSINIT);
				simple_parser_icg_newoperandint(parser,1);
				/* Generate Code ( Call Block ) */
				simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
				simple_parser_icg_newoperand(parser,"Init");
				/* Generate Location for nPC of Getter */
				simple_parser_icg_newoperandint(parser,0);
				/* Block Parameters */
				parser->nBlockCallOnly = 1 ;
				simple_parser_mixer(parser);
				parser->nBlockCallOnly = 0 ;
				/* Generate Code (End Brace) */
				simple_parser_icg_newoperation(parser,ICO_CALLCLASSINIT);
				simple_parser_icg_newoperandint(parser,0);
				SIMPLE_PARSER_IGNORENEWLINE ;
				x = simple_parser_mixer(parser);
				simple_parser_icg_newoperation(parser,ICO_BRACEEND);
				parser->nNoAssignment = 1 ;
				return x ;
			}
			parser->nNoAssignment = 1 ;
			/*
			**  Generate Code 
			**  PUSHV enable using braces to access the object 
			*/
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			return 1 ;
		}
	}
	/* Factor --> Anonymous Block */
	if ( simple_parser_iskeyword(parser,KEYWORD_BLOCK) ) {
		simple_parser_nexttoken(parser);
		/*
		**  Generate Code 
		**  Push Block Name, then jump after the block code 
		*/
		simple_parser_icg_newoperation(parser,ICO_PUSHC);
		/* Note : the block name must be in lower case */
		sprintf( cBlockName , "_simple_anonymous_block_%d" , SIMPLE_PARSER_OPERATIONID ) ;
		simple_parser_icg_newoperand(parser,cBlockName);
		simple_parser_icg_newoperation(parser,ICO_JUMP);
		pMark = simple_parser_icg_getactiveoperation(parser);
		/* Define the Block - as public (not related to any class) */
		list = simple_list_newlist_gc(parser->sState,parser->sState->blocks_map);
		simple_list_addstring_gc(parser->sState,list,cBlockName);
		/* Note +1 because instruction ICO_NEWBLOCK will come next */
		simple_list_addint_gc(parser->sState,list,SIMPLE_PARSER_OPERATIONID+1);
		simple_list_addstring_gc(parser->sState,list,simple_list_getstring(parser->sState->files_stack,simple_list_getsize(parser->sState->files_stack)));
		simple_list_addint_gc(parser->sState,list,0);
		simple_parser_icg_newoperation(parser,ICO_NEWBLOCK);
		simple_parser_icg_newoperand(parser,cBlockName);
		/* Get Block Parameters */
		if ( simple_parser_isidentifier(parser) || simple_parser_isoperator2(parser,OP_FOPEN) ) {
			if (simple_parser_paralist(parser) == -1) return 0 ;
		}
		/* Get Block Code */
		if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) ) {
			simple_parser_nexttoken(parser);
			x = parser->nAssignmentFlag ;
			x2 = parser->nNoAssignment ;
			x3 = parser->nBraceFlag ;
			parser->nAssignmentFlag = 1 ;
			parser->nBraceFlag = 0 ;
			while ( simple_parser_stmt(parser) ) {
				if ( parser->ActiveToken == parser->TokensCount ) {
					break ;
				}
			}
			parser->nAssignmentFlag = x ;
			parser->nNoAssignment = x2 ;
			parser->nBraceFlag = x3 ;
			if ( simple_parser_isoperator2(parser,OP_BRACECLOSE) ) {
				simple_parser_nexttoken(parser);
				/* Generate Code */
				simple_parser_icg_newoperation(parser,ICO_RETNULL);
				nMark = simple_parser_icg_newlabel(parser);
				simple_parser_icg_addoperandint(parser,pMark,nMark);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : AnonymousBlock --> Block ParaList '{' Statement '}'");
				#endif
				return 1 ;
			}
		}
	}
	/* Factor --> Call Identifier ( parameters ) */
	if ( simple_parser_iskeyword(parser,KEYWORD_CALL) ) {
		simple_parser_nexttoken(parser);
		if ( simple_parser_isidentifier(parser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
			simple_parser_icg_newoperand(parser,parser->TokenText);
			/* Generate Location for nPC of Getter */
			simple_parser_icg_newoperandint(parser,0);
			simple_parser_nexttoken(parser);
			/* Object Attributes */
			if ( simple_parser_objattributes(parser) == 0 ) {
				return 0 ;
			}
			simple_parser_icg_newoperation(parser,ICO_PUSHV);
			simple_parser_icg_newoperation(parser,ICO_ANONYMOUS);
			if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
				return simple_parser_mixer(parser) ;
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

int simple_parser_mixer ( Parser *parser )
{
	int x,nCallMethod,nStatus,nFlag  ;
	/*
	**  { . Identifier } 
	**  Object Attributes 
	*/
	if ( simple_parser_objattributes(parser) == 0 ) {
		return 0 ;
	}
	/* [Index]  to access array element, Index = Expression */
	if ( simple_parser_isoperator2(parser,OP_LOPEN) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_expr(parser) ) {
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_LOADINDEXADDRESS);
			/* Add 0 For Operator Overloading */
			simple_parser_icg_newoperandint(parser,0);
			if ( simple_parser_isoperator2(parser,OP_LCLOSE) ) {
				simple_parser_nexttoken(parser);
				#if SIMPLE_PARSERTRACE
				SIMPLE_STATE_CHECKPRINTRULES 
				
				puts("Rule : Mixer -> '[' Expr ']' ");
				#endif
				x = simple_parser_mixer(parser);
				if ( x == 0 ) {
					return 0 ;
				}
			}
			else {
				parser_error(parser,PARSER_ERROR_MISSBRACKETS);
				return 0 ;
			}
		}
		else {
			return 0 ;
		}
	}
	/* |  [ ( [ Expr { , Expr } ] ) ]  ] */
	if ( simple_parser_isoperator2(parser,OP_FOPEN) ) {
		/* Generate Code */
		nCallMethod = 0 ;
		if ( simple_parser_icg_getlastoperation(parser) == ICO_LOADADDRESS ) {
			simple_parser_icg_setlastoperation(parser,ICO_LOADBLOCK);
			/* Delete Locations for Getter */
			simple_list_deleteitem_gc(parser->sState,simple_parser_icg_getactiveoperation(parser),3);
		}
		else if ( simple_parser_icg_getlastoperation(parser) == ICO_LOADSUBADDRESS ) {
			simple_parser_icg_setlastoperation(parser,ICO_LOADMETHOD);
			/* Delete Locations for Setter/Getter */
			simple_list_deleteitem_gc(parser->sState,simple_parser_icg_getactiveoperation(parser),4);
			simple_list_deleteitem_gc(parser->sState,simple_parser_icg_getactiveoperation(parser),3);
			nCallMethod = 1 ;
		}
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		if ( simple_parser_isoperator2(parser,OP_FCLOSE) ) {
			simple_parser_nexttoken(parser);
			/* Generate Code */
			simple_parser_gencall(parser,nCallMethod);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Mixer -> '(' [Expr { ',' Expr} ] ')' ");
			#endif
			SIMPLE_PARSER_IGNORENEWLINE ;
			x = simple_parser_mixer(parser);
			return x ;
		}
		while ( 1 ) {
			nFlag = parser->nAssignmentFlag ;
			parser->nAssignmentFlag = 0 ;
			if ( simple_parser_expr(parser) ) {
				parser->nAssignmentFlag = nFlag ;
				SIMPLE_PARSER_IGNORENEWLINE ;
				if ( simple_parser_isoperator2(parser,OP_COMMA) ) {
					simple_parser_nexttoken(parser);
				}
				else if ( simple_parser_isoperator2(parser,OP_FCLOSE) ) {
					#if SIMPLE_PARSERTRACE
					SIMPLE_STATE_CHECKPRINTRULES 
					
					puts("Rule : Mixer -> '(' [Expr { ',' Expr} ] ')' ");
					#endif
					simple_parser_nexttoken(parser);
					/* Generate Code */
					simple_parser_gencall(parser,nCallMethod);
					x = simple_parser_mixer(parser);
					return x ;
				}
				else {
					parser_error(parser,PARSER_ERROR_MISSPARENTHESES);
					return 0 ;
				}
			}
			else {
				return 0 ;
			}
			SIMPLE_PARSER_IGNORENEWLINE ;
		}
	}
	/* Block Call Only */
	if ( parser->nBlockCallOnly == 1 ) {
		return 1 ;
	}
	/* '{' {Statement} '}' */
	if ( simple_parser_isoperator2(parser,OP_BRACEOPEN) && parser->nControlStructureExpr == 0 ) {
		parser->nBraceFlag++ ;
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_PUSHV);
		simple_parser_icg_newoperation(parser,ICO_BRACESTART);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : Mixer --> '{' {Statement} [BraceOpen]Open");
		#endif
		/* if HasBlock(self,"Open") Open() end */
		simple_parser_gencallbracemethod(parser,"Open");
		simple_parser_nexttoken(parser);
		nStatus = parser->nAssignmentFlag ;
		parser->nAssignmentFlag = 1 ;
		while ( simple_parser_stmt(parser) ) {
			if ( parser->ActiveToken == parser->TokensCount ) {
				break ;
			}
		}
		parser->nAssignmentFlag = nStatus ;
		if ( simple_parser_isoperator2(parser,OP_BRACECLOSE) ) {
			parser->nBraceFlag-- ;
			/*
			**  Generate Code 
			**  if HasBlock(self,"Close") Close() end 
			*/
			simple_parser_gencallbracemethod(parser,"Close");
			simple_parser_icg_newoperation(parser,ICO_BRACEEND);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : [BraceClose]Close --> '}' ");
			#endif
			simple_parser_nexttoken(parser);
			x = simple_parser_mixer(parser);
			return x ;
		}
		else {
			parser_error(parser,PARSER_ERROR_BRACESNOTCLOSED);
		}
	}
	/* This block return 1 because the mixer is optional and comes after identifier */
	return 1 ;
}

void simple_parser_gencall ( Parser *parser,int nCallMethod )
{
	/* Generate Code */
	simple_parser_icg_newoperation(parser,ICO_CALL);
	if ( nCallMethod == 1 ) {
		/* Add 0 For Operator Overloading */
		simple_parser_icg_newoperandint(parser,0);
		/* Add 1 so the call instruction move list from aBeforeObjState to pObjState */
		simple_parser_icg_newoperandint(parser,1);
		simple_parser_icg_newoperation(parser,ICO_AFTERCALLMETHOD);
	}
	else {
		/* Add 0 For Operator Overloading */
		simple_parser_icg_newoperandint(parser,0);
		/*
		**  The No Operation Instruction may be converted to AfterCallMethod during runtime 
		**  This happens when we call method like blocks inside object { } 
		*/
		simple_parser_icg_newoperation(parser,ICO_NOOP);
	}
}

int simple_parser_ppmm ( Parser *parser )
{
	/* ++ & -- */
	if ( simple_parser_isoperator(parser,"++") ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_PLUSPLUS);
		simple_parser_icg_newoperation(parser,ICO_PUSHV);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : PlusPlus --> '++'");
		#endif
		return 1 ;
	}
	else if ( simple_parser_isoperator(parser,"--") ) {
		simple_parser_nexttoken(parser);
		/* Generate Code */
		simple_parser_icg_newoperation(parser,ICO_MINUSMINUS);
		simple_parser_icg_newoperation(parser,ICO_PUSHV);
		#if SIMPLE_PARSERTRACE
		SIMPLE_STATE_CHECKPRINTRULES 
		
		puts("Rule : MinusMinus --> '--'");
		#endif
		return 1 ;
	}
	return 0 ;
}

void simple_parser_gencallbracemethod ( Parser *parser,const char *cMethod )
{
	int nMark1  ;
	List *pMark  ;
	/* if HasBlock(self,cMethod) cMethod() end */
	simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
	simple_parser_icg_newoperand(parser,"HasBlock");
	simple_parser_icg_newoperation(parser,ICO_LOADADDRESS);
	simple_parser_icg_newoperand(parser,"self");
	simple_parser_icg_newoperandint(parser,0);
	simple_parser_icg_newoperation(parser,ICO_PUSHV);
	simple_parser_icg_newoperation(parser,ICO_PUSHC);
	simple_parser_icg_newoperand(parser,cMethod);
	simple_parser_icg_newoperation(parser,ICO_CALL);
	simple_parser_icg_newoperation(parser,ICO_NOOP);
	simple_parser_icg_newoperation(parser,ICO_PUSHV);
	/* Jump */
	simple_parser_icg_newoperation(parser,ICO_JUMPZERO);
	pMark = simple_parser_icg_getactiveoperation(parser);
	simple_parser_icg_newoperation(parser,ICO_LOADBLOCK);
	simple_parser_icg_newoperand(parser,cMethod);
	simple_parser_icg_newoperation(parser,ICO_CALL);
	simple_parser_icg_newoperation(parser,ICO_NOOP);
	simple_parser_icg_newoperation(parser,ICO_PUSHV);
	simple_parser_icg_newoperation(parser,ICO_FREESTACK);
	nMark1 = simple_parser_icg_newlabel(parser);
	simple_parser_icg_addoperandint(parser,pMark,nMark1);
}

int simple_parser_objattributes ( Parser *parser )
{
	/* { . Identifier } */
	while ( simple_parser_isoperator2(parser,OP_DOT) ) {
		simple_parser_nexttoken(parser);
		SIMPLE_PARSER_IGNORENEWLINE ;
		/* we support literal to be able to call methods contains operators in the name */
		if ( simple_parser_isidentifier(parser) || simple_parser_isliteral(parser) ) {
			/* Prevent Accessing the self reference from outside the object */
			if ( strcmp(parser->TokenText,"self") == 0 ) {
				parser_error(parser,PARSER_ERROR_ACCESSSELFREF);
				return 0 ;
			}
			/* Generate Code */
			simple_parser_icg_newoperation(parser,ICO_LOADSUBADDRESS);
			simple_parser_icg_newoperand(parser,parser->TokenText);
			/* Generate Location for nPC of Getter - When we access object attribute using { } */
			simple_parser_icg_newoperandint(parser,0);
			#if SIMPLE_PARSERTRACE
			SIMPLE_STATE_CHECKPRINTRULES 
			
			puts("Rule : Mixer -> '.' Identifier ");
			#endif
			simple_parser_nexttoken(parser);
		}
		else {
			return 0 ;
		}
	}
	return 1 ;
}

