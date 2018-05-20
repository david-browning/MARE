%{

#include "PreprocessorScanner.h"
#include <mare_compiler_functions.h>

using namespace std;

#undef YY_DECL
#define YY_DECL int PreprocessorScanner::yylex(yy::PreprocessorParser::semantic_type* const lval, \
											   yy::PreprocessorParser::location_type* location)

using TOKENS = yy::PreprocessorParser::token;

#define yyterminate() return ( TOKENS::END_TOKEN )

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option nodefault
%option noyywrap

%%

#module					return TOKENS::MODULE;
#using					return TOKENS::INCLUDE;
[0-9]+					{
								lval->Int = stoi(yytext);
								return TOKENS::INTEGER;
						};
\".+\"					{
								lval->Str = new std::string(TrimQuotations(yytext));
								return TOKENS::STRING;
						};
[[:space:]]				;
\/\/.*					;
\t+						;
.       				;
<<EOF>>					return TOKENS::END_TOKEN;

%%