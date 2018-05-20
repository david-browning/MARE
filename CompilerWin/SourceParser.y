%skeleton "lalr1.cc"
%debug
%defines
%define "parser_class_name" "SourceParser"

%error-verbose

%code requires
{
	#include <mare_expression.h>
	#include <mare_symbol.h>
	#include <mare_operator.h>
	#include <mare_literal.h>
	#include <mare_iatom.h>
	#include <mare_stmt.h>

	class SourceScanner;
	class IAtom;
	class Operator;
	class Literal;
	class Symbol;
	class Expression;
	class Statement;
}

%parse-param { SourceScanner& sourceScanner }

%{

#include "SourceScanner.h"
#include <mare_expression.h>
#include <mare_symbol.h>
#include <mare_iatom.h>
#include <mare_literal.h>
#include <mare_compiler_functions.h>
#include <mare_stmt.h>

#undef yylex
#define yylex sourceScanner.yylex

%}

%token END_TOKEN 0 "End of file"
%token COMMA "," PERIOD "." SEMICOLON ";" COLON ":" SLASH_B "\\" HAT "^"
%token BRACE_L "{" BRACE_R "}" PARENTH_L "(" PARENTH_R ")" BRACKET_L "[" BRACKET_R "]"

%token <Op>INCREMENT "++" <Op>DECREMENT "--" <Op>STAR "*" <Op>SLASH_F "/" <Op>PERCENT "%" <Op>PLUS "+" <Op>MINUS "-"
%token <Op>EQUALS "=" <Op>ANGLE_L "<" <Op>ANGLE_R ">"
%token <Op>K_AND "and" <Op>K_OR "or" <Op>K_NOT "not" 

%token K_PROGRAM "program" K_FUNCTION "function" K_RETURN "return" K_CONST "const" K_CODE "__code" K_COUNT "count" K_COMPOUND "compound_t"
%token K_IF "if" K_ELSE "else" K_END "end" K_IS "is"
K_BREAK "break" K_UNTIL "until"
%token K_CM "cm" K_INCH "inch" K_PIXEL "pixel"

%union
{
	const IAtom*		Info;
	Symbol*				Sym;
	const Operator*	Op;
	const Literal*		Lit;
	std::string*		Str;
	int					Int;
	char					Char;
	Expression*			Expr;
	StmtPtr*				Stmt;
	ParamList*			Parameters;
	StmtList*			Statements;
	ExprList*			Arguments;
}

%token <Sym> SYMBOL
%token <Str> ID
%token <Lit> CONSTANT
%token <Lit> LITERAL
%token <Info> TYPE
%type <Info> type_info param_type
%type <Parameters> parameters params param_list
%type <Arguments> arguments args arglist 
%type <Statements> stmt_list decls declaration_list
%type <Expr> expr atom factor unary relation bool bool_op
%type <Stmt> stmt function_call loop_stmt if_stmt declaration assignment inline_code

%locations
%start program

%%

program: decls 
			K_PROGRAM COLON stmt_list K_END K_PROGRAM 
			decls END_TOKEN
{
	sourceScanner.GetCPtr()->WriteProgram(*$1, *$4, *$7);
};

code_start:
{
	sourceScanner.GetCPtr()->OpenScope();
};

code_end:
{
	sourceScanner.GetCPtr()->CloseScope();
};

type_info: TYPE
{
	$$ = $1;
};

type_info: K_CONST type_info
{
	auto tInfo = *$2;
	tInfo.MakeConstant();
	$$ = new IAtom(tInfo);
}

type_info: TYPE BRACKET_L LITERAL BRACKET_R
{
	$$ = new IAtom(sourceScanner.GetCPtr()->MakeArrayType(*$1, *$3));
};

stmt_list: stmt
{
	$$ = new StmtList();
	$$->push_back(*$1);
};

stmt_list: stmt_list stmt
{
	$$ = $1;
	$$->push_back(*$2);
};

arguments: PARENTH_L args PARENTH_R 
{
	$$ = $2;
};

args:				
{ 
	$$ = new ExprList(); 
};

args:	arglist 
{ 
	$$ = $1; 
};

arglist:	expr
{ 
	$$ = new ExprList();
	$$->push_back(*$1);
};

arglist: arglist COMMA expr 
{ 
	$$->push_back(*$3);
};	

parameters:		PARENTH_L params PARENTH_R 
{ 
	$$ = $2; 
};

params:			
{ 
	//Params could be an empty list
	$$ = new ParamList(); 
};

params: param_list 
{ 
	//Params could be a list of at least one symbol
	$$ = $1;
};

param_list:		param_type ID
{
	$$ = new ParamList();
	$$->push_back(std::make_shared<Symbol>(*sourceScanner.GetCPtr()->InsertSymbol(*$2, *$1)));
};

param_list:		param_type ID COMMA param_list
{
	$$ = $4;
	$$->push_back(std::make_shared<Symbol>(*sourceScanner.GetCPtr()->InsertSymbol(*$2, *$1)));
};

param_type: type_info
{
	$$ = $1;
};

param_type: TYPE BRACKET_L BRACKET_R
{
	//Param type could be an array with an unknown size.
	$$ = new IAtom(sourceScanner.GetCPtr()->MakeArrayType(*$1, ZERO_LITERAL));
};

decls:				
{
	$$ = new StmtList();
};

decls: declaration_list
{
	$$ = $1;
};

declaration_list:	declaration
{
	$$ = new StmtList();
	$$->push_back(*$1);
};

declaration_list: declaration_list declaration
{
	$$->push_back(*$2);
};

expr:	expr PLUS factor
{
	$$ = new Expression(*$2);
	$$->SetRight(*$3);
	$$->SetLeft(*$1);
};

expr: expr MINUS factor
{
	$$ = new Expression(*$2);
	$$->SetRight(*$3);
	$$->SetLeft(*$1);
};

factor: factor SLASH_F unary
{
	$$ = new Expression(*$2);
	$$->SetRight(*$3);
	$$->SetLeft(*$1);
};

factor: factor STAR unary
{
	$$ = new Expression(*$2);
	$$->SetRight(*$3);
	$$->SetLeft(*$1);
};

factor: factor PERCENT unary
{
	$$ = new Expression(*$2);
	$$->SetRight(*$3);
	$$->SetLeft(*$1);
};

expr: factor
{
	$$ = $1;
};

factor: unary
{
	$$ = $1;
};

unary: atom
{
	$$ = $1;
};

unary: MINUS atom
{
	$$ = new Expression(*$1);
	$$->SetRight(*$2);
	$$->SetLeft(ZERO_LITERAL);
};

atom: K_COUNT ID
{
	$$ = new Expression(sourceScanner.GetCPtr()->ToArrayCountExpression(*$2));
};

atom: CONSTANT
{
	$$ = new Expression(*$1);
};

atom: LITERAL
{
	$$ = new Expression(*$1);
};

atom: LITERAL K_CM
{
	$$ = new Expression(sourceScanner.GetCPtr()->ToCMExpression(*$1));
};

atom: LITERAL K_INCH
{
	$$ = new Expression(sourceScanner.GetCPtr()->ToInchExpression(*$1));
};

atom: ID
{
	$$ = new Expression(*sourceScanner.GetCPtr()->SymbolLookup(*$1));
};

atom: ID BRACKET_L expr BRACKET_R
{
	$$ = new Expression(sourceScanner.GetCPtr()->IndexExpression(*$1, *$3));
};

atom: PARENTH_L expr PARENTH_R
{
	$$ = $2;
};

atom: ID arguments
{
	$$ = new Expression(NOP_OPERATOR);
	Expression sym = Expression(*sourceScanner.GetCPtr()->SymbolLookup(*$1));
	$$->SetRight(sym);
	$$->SetList(*$2);
};

relation: expr K_IS EQUALS expr
{
	$$ = new Expression(EQUALS_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$4);
};

relation: expr K_IS ANGLE_L EQUALS expr
{
	$$ = new Expression(LTE_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$5);
};

relation: expr K_IS ANGLE_R EQUALS expr
{
	$$ = new Expression(GTE_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$5);
};

relation: expr K_IS ANGLE_L expr
{
	$$ = new Expression(LT_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$4);
};

relation: expr K_IS ANGLE_R expr
{
	$$ = new Expression(GT_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$4);
};

relation: PARENTH_L relation PARENTH_R
{
	$$ = $2;
}

bool_op: K_NOT relation
{
	$$ = new Expression(NOT_OPERATOR);
	$$->SetLeft(*$2);
};

bool_op: bool K_OR relation
{
	$$ = new Expression(OR_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$3);
};

bool_op: relation
{
	$$ = $1;
};

bool: bool_op
{
	$$ = $1;
};

bool: bool_op K_AND relation
{
	$$ = new Expression(AND_OPERATOR);
	$$->SetLeft(*$1);
	$$->SetRight(*$3);
};

declaration: type_info ID EQUALS expr SEMICOLON
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->DeclareVariableStmt(*$2, *$1, *$4));
};

declaration: type_info ID EQUALS BRACE_L arglist BRACE_R SEMICOLON
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->DeclareVariableArrayStmt(*$2, *$1, *$5));
};

declaration: K_FUNCTION type_info ID code_start parameters COLON stmt_list code_end K_END K_FUNCTION
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->DeclareFunctionStmt(*$3, *$2, *$5, *$7));
};

declaration: K_COMPOUND ID EQUALS BRACE_L code_start decls code_end BRACE_R SEMICOLON
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->DeclareCompoundTypeStmt(*$2, *$6));
};

if_stmt: K_IF PARENTH_L bool PARENTH_R COLON code_start stmt_list code_end K_END K_IF  
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->IfStmt(*$3, *$7));
};

if_stmt: K_IF PARENTH_L bool PARENTH_R COLON code_start stmt_list code_end
			K_ELSE COLON code_start stmt_list code_end K_END K_IF  
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->IfStmt(*$3, *$7, *$12));
};

loop_stmt: K_UNTIL PARENTH_L bool PARENTH_R COLON code_start stmt_list code_end
			  K_END K_UNTIL 
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->LoopUntilStmt(*$3, *$7));
};

function_call: ID arguments
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->CallFunctionStmt(*$1, *$2));
};

inline_code: K_CODE LITERAL
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->InlineCodeStmt(*$2));
};

assignment: ID EQUALS expr
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->AssignVarStmt(*$1, *$3));
};

assignment: ID BRACKET_L expr BRACKET_R EQUALS expr
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->AssignVarStmt(*$1, *$6, *$3));
};

stmt: K_BREAK SEMICOLON
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->BreakStmt());
};

stmt: K_RETURN expr SEMICOLON
{
	$$ = new StmtPtr(sourceScanner.GetCPtr()->ReturnStmt(*$2));
};

stmt: if_stmt
{
	$$ = $1;
};

stmt: loop_stmt
{
	$$ = $1;
};

stmt: function_call SEMICOLON
{
	$$ = $1;
};

stmt: declaration
{
	$$ = $1;
};

stmt: inline_code SEMICOLON
{
	$$ = $1;
};

stmt: assignment SEMICOLON
{
	$$ = $1;
};

%%

void yy::SourceParser::error(const location_type& l, const std::string &m)
{
	std::cerr << m << " at " << l << std::endl;
}
