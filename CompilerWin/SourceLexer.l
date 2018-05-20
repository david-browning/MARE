%{

#include "SourceScanner.h"
#include <mare_iatom.h>
#include <mare_compiler_functions.h>
#include <mare_operator.h>

using namespace std;

#undef YY_DECL
#define YY_DECL int SourceScanner::yylex(yy::SourceParser::semantic_type* const lval, \
													  yy::SourceParser::location_type* location)

using TOKENS = yy::SourceParser::token;

#define yyterminate() return( TOKENS::END_TOKEN )

#define YY_NO_UNISTD_H

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option nodefault
%option noyywrap
%option yylineno

%%

%{
	yylval = lval;
%}
	
	/* Keywords */
program				return TOKENS::K_PROGRAM;
function			return TOKENS::K_FUNCTION;
return				return TOKENS::K_RETURN;
const				return TOKENS::K_CONST;
count				return TOKENS::K_COUNT;

__code				return TOKENS::K_CODE;

if					return TOKENS::K_IF;
else				return TOKENS::K_ELSE;
end					return TOKENS::K_END;

is					return TOKENS::K_IS;

break				return TOKENS::K_BREAK;
until				return TOKENS::K_UNTIL;

cm					return TOKENS::K_CM;
inch				return TOKENS::K_INCH;

	/* Types */
float_t				{
						yylval->Info = &FLOAT32_TYPE_INFO;
						return TOKENS::TYPE;
					}

float64_t			{
						yylval->Info = &FLOAT64_TYPE_INFO;
						return TOKENS::TYPE;
					}

int_t				{
						yylval->Info = &INT_TYPE_INFO;
						return TOKENS::TYPE;
					}

int64_t				{
						yylval->Info = &INT64_TYPE_INFO;
						return TOKENS::TYPE;
					}

char_t				{
						yylval->Info = &CHAR_TYPE_INFO;
						return TOKENS::TYPE;
					}

null_t				{
						yylval->Info = &NULL_TYPE_INFO;
						return TOKENS::TYPE;
					}
compound_t			return TOKENS::K_COMPOUND;



	/* Constants */
TRUE				{
						yylval->Lit = &TRUE_LITERAL;
						return TOKENS::CONSTANT;
					}

FALSE				{
						yylval->Lit = &FALSE_LITERAL;
						return TOKENS::CONSTANT;
					}

PAGE_WIDTH			{
						auto lit = GetPageWidthLiteral();
						yylval->Lit = lit;
						return TOKENS::CONSTANT;
					}

PAGE_HEIGHT 		{
						auto lit = GetPageHeightLiteral();
						yylval->Lit = lit;
						return TOKENS::CONSTANT;
					}

PI					{
						yylval->Lit = &PI_LITERAL;
						return TOKENS::LITERAL;
					}

,					return TOKENS::COMMA;
\.					return TOKENS::PERIOD;
;					return TOKENS::SEMICOLON;
\:					return TOKENS::COLON;
\\					return TOKENS::SLASH_B;
\{					return TOKENS::BRACE_L;
\}					return TOKENS::BRACE_R;
\(					return TOKENS::PARENTH_L;
\)					return TOKENS::PARENTH_R;
\[					return TOKENS::BRACKET_L;
\]					return TOKENS::BRACKET_R;

	/* Operators */
\+\+				{
						yylval->Op = &Operator(INCREMENT_OPERATOR);
						return TOKENS::INCREMENT;
					}
\-\-				{
						yylval->Op = &DECREMENT_OPERATOR;
						return TOKENS::DECREMENT;
					}
\*					{
						yylval->Op = &MULTIPLY_OPERATOR;
						return TOKENS::STAR;
					}
\/					{
						yylval->Op = &DIVIDE_OPERATOR;
						return TOKENS::SLASH_F;
					}
\%					{
						yylval->Op = &MODULO_OPERATOR;
						return TOKENS::PERCENT;
					}
\+					{
						yylval->Op = &ADD_OPERATOR;
						return TOKENS::PLUS;
					}
\-					{
						yylval->Op = &SUBTRACT_OPERATOR;
						return TOKENS::MINUS;
					}
\=					{
						yylval->Op = &EQUALS_OPERATOR;
						return TOKENS::EQUALS;
					}
\<					{
						yylval->Op = &LT_OPERATOR;
						return TOKENS::ANGLE_L;
					}
\>					{
						yylval->Op = &GT_OPERATOR;
						return TOKENS::ANGLE_R;
					}
\^					{
						yylval->Op = &HAT_OPERATOR;
						return TOKENS::HAT;
					}
or					{
						yylval->Op = &NOT_OPERATOR;
						return TOKENS::K_OR;
					}
and					{	
						yylval->Op = &AND_OPERATOR;
						return TOKENS::K_AND;
					}
not					{
						yylval->Op = &NOT_OPERATOR;
						return TOKENS::K_NOT;
					}

	

	/* Compilation Modifiers */
#.+					;

	/* Literals */
([0-9]+)|((0x)|(0X)([0-9]|[A-F])+) {
						int64_t number = stoi(yytext);
						yylval->Lit = new Literal(INT_TYPE_INFO_C, &number, sizeof(number));
						return TOKENS::LITERAL;
					}

[0-9]+\.[0-9]+d		{
						double number = std::stod(yytext);
						yylval->Lit = new Literal(FLOAT64_TYPE_INFO, &number, sizeof(number));
						return TOKENS::LITERAL;
					}

[0-9]+\.[0-9]+		{
						float number = (float)std::stod(yytext);
						yylval->Lit = new Literal(FLOAT32_TYPE_INFO, &number, sizeof(number));
						return TOKENS::LITERAL;
					}

\'.\'				{
						auto c = yytext[1];
						yylval->Lit = new Literal(CHAR_TYPE_INFO_C, &c, sizeof(c));
						return TOKENS::LITERAL;
					}

\".*\"				{
						auto s = TrimQuotations(yytext);
						yylval->Lit = new Literal(STRING_TYPE_INFO_C, s.c_str(), s.size());
						return TOKENS::LITERAL;
					}

	/* Variables */
(_|[A-Z]|[a-z])+([A-Z]|[a-z]|[0-9]|_)* {
						yylval->Str = new std::string(yytext);
						return TOKENS::ID;
					}

	/* stuff to ignore */
[[:space:]]			;
\/\/.*				;
\t+					;
.					std::cerr << "Unexpected symbol " << yytext << " at line " << yylineno << std::endl;
<<EOF>>				return TOKENS::END_TOKEN;

%%
