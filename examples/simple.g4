
grammar simple;

@header {
package simple;
} 


sourceFile
	: (stmt)* EOF
	| (blockDecl)* EOF
	| (declBlock)* EOF
	;
 
stmt
	: 'final'? type? assignment ';'?
	| ( 'display' | '@' ) (basicExpression ( arithmethicOperator '('? basicExpression ')'? )*?) ';'?
	| 'read' Identifier
	| moduleDecl
	| blockDecl
	| classDecl
	| tryCatchStmt
	| declBlock ';'?
	| expression ';'?
	| ifStmt
	| switchStmt
	| doWhileStmt
	| whileStmt
	| forStmt
	| 'break' Number?
	| 'continue'
	| '__exit__'
	| 'private'
	| '\r'? '\n' ';'?
	;
 
type 
	: 'int'
	| 'string'
	| 'list'
	| 'pointer'
	| Identifier
	;
	
assignment
	: Identifier assignmentOperator ( Identifier | Number | String | List | invokeBlock )
	| Identifier assignmentOperator classInit
	| Identifier assignmentOperator propertyStmt
	;
	
callFile
	: 'call' (Identifier DotAccessIdentifier*)? (Identifier ( Space*? '/' Space*? Identifier)*)? ';'?
	| 'call' String ';'?
	;
	
importModule
	: 'import' Identifier DotAccessIdentifier* ';'?
	;
	
moduleDecl
	: 'module' Identifier DotAccessIdentifier* ';'?
	;
	
blockDecl
	: 'block' Identifier '('? parameters? ')'? '{'? stmt* (returnStmt)? '}'? 'end'? Space*?
	;
	
returnStmt
	: 'return' ( basicExpression | stmt* ) ';'?
	;

classDecl
	: 'call' Identifier inheritClass?
	;
	
inheritClass
	: ':' Identifier DotAccessIdentifier*? 
	;
	
classInit
	: 'new' Identifier DotAccessIdentifier*? ( '(' ( (basicExpression | stmt) (',' (basicExpression | stmt))*? )? ')' )?
	;
	
propertyStmt
	: propertyAccess ('=' ( Identifier | Number | String | List | invokeBlock ))? 
	| propertyAccess '=' classInit 
	;
	
propertyAccess
	: Identifier DotAccessIdentifier*
	;
	
declBlock
	: Identifier '{' stmt*? '}'
	| ( propertyStmt | assignment | classInit ) '{' stmt*? '}'
	;
	
parameters 
	:  Space*? type? Identifier '...'? ( Space*? ',' Space*? type? Identifier '...'?)* 
	;
	
invokeBlock
	: 'invoke'? propertyAccess '(' ( (basicExpression | stmt) (',' (basicExpression | stmt))*? )? ')'
	;
	
tryCatchStmt
	: 'try' '{'? stmt*? 'catch' stmt*? '}'? 'end'? Space*?
	;
	
arithmethicOperator
	: '+' | '-' | '*' | '/' | '%' | '++' | '--'
	;
	
relationalOperators
	: '==' | '!=' | '>' | '<' | '>=' | '<='
	;
	
logicalOperator
	: 'or' | 'and' | 'not'
	| '||' | '&&' | '!'
	;
	
bitwiseOperator
	: '&' | '|' | '^' | '~' | '<<' | '>>'
	;
	
assignmentOperator
	: '=' | '+=' | '-=' | '*=' | '/=' | '%=' | '<<=' | '>>=' | '&=' | '|=' | '^='
	;
	
conditionalStmt
	: (( 'not' | '!' )? expression  ( relationalOperators expression)*)  (logicalOperator expression  ( relationalOperators expression)*)*?
	;
	
ifStmt 
	: 'if' conditionalStmt '{'? stmt*? ( elifStmt )*? ( elseStmt )? '}'? 'end'?
	;
	
elifStmt 
	: 'elif' conditionalStmt stmt*?
	;
	
elseStmt 
	: 'else' stmt*?
	;
	
switchStmt
	: 'switch' '('? basicExpression? ')'? '{'? ( Space*? 'case' basicExpression (logicalOperator basicExpression)*? stmt*?)*? defaultCase? '}'? 'end'?
	;
	
switchCase
	: 
	;
	
defaultCase
	: 'default' stmt*?
	;
	
whileStmt
	: 'while' conditionalStmt '{'? stmt*? '}'? 'end'?
	;
	
doWhileStmt
	: 'do' '{'? stmt*? '}'? 'while' conditionalStmt
	;
	
forStmt
	: 'for' '('? ( forLoopRange | forLoopIteration ) ')'? '{'? stmt*? '}'? 'end'?
	;
	
forLoopRange
	: assignment 'to' basicExpression ( 'step' arithmethicOperator? Number )?
	;
	
forLoopIteration
	: Identifier 'in' basicExpression
	;
	
arithmethicExpr
	: (basicExpression arithmethicOperator basicExpression)+
	;

expression
	: basicExpression
	| callFile
	| importModule
	| classInit 
	| propertyStmt
	| expression arithmethicOperator
	| arithmethicExpr
	;

basicExpression
	: invokeBlock  
	| Identifier
	| Number
	| String
	| List
	;
 
Identifier
	: [a-zA-Z_] [a-zA-Z_0-9]*
	;
	
DotAccessIdentifier
	: ( Space*? '.' Space*? Identifier)
	;

Number
	: ('0'..'9') '.'? ('0'..'9')*
	;

String
	: ["] ( ~["\r\n\\] | '\\' ~[\r\n] )* ["]
	| ['] ( ~['\r\n\\] | '\\' ~[\r\n] )* [']
	| [`] ( ~['\r\n\\] | '\\' ~[\r\n] )* [`]
	;
 
List 
	: '[' Space*? ( Identifier | Number | String | List ) ( Space*? ',' Space*? ( Identifier | Number | String | List ))* Space*? ']'
	;
 
Space
	: [ \t\r\n\u000C] -> skip
	;
	
BlockComment 
    : '/*' .*? '*/' -> skip
    ;
	
SingleLineComment
	: ( '//' | '#' ) ~[\n\r]* -> skip
	;