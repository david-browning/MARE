%skeleton "lalr1.cc"
%debug
%defines
%define "parser_class_name" "PreprocessorParser"

%error-verbose

%code requires
{
	#include <string>
	class PreprocessorScanner;
	class string;
}

%parse-param { PreprocessorScanner& preScanner }

%{

using namespace std;
#include <iostream>
#include "PreprocessorScanner.h"

#undef yylex
#define yylex preScanner.yylex

%}

%token MODULE "#module"
%token INCLUDE "#using"
%token STRING "string"
%token INTEGER "number"
%token END_TOKEN 0 "End of file"

%union
{
	 std::string*	Str;
	 int				Int;
}

%type <Str> STRING
%type <Int> imports import_list INTEGER

%locations

%%

header: imports code_list END_TOKEN;

code_list: code
{
};

code_list: code_list code
{
};

code:
{
	
};

code: STRING
{

};

code: INTEGER
{
};

imports: 
{
	 $$ = 0;
};

imports: import_list
{
	 $$ =  $1;
};

import_list: import
{
	 $$ = 1;
};

import_list: import_list import
{
	 $$ = $$ + 1;
};

import: MODULE
{

};

import: INCLUDE STRING
{
	preScanner.AddDependency(*$2);
	delete $2;
};

%%

void yy::PreprocessorParser::error(const location_type& l, const std::string &m)
{
	std::cerr << m << " at " << l << std::endl;
}