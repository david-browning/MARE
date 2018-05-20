#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <annotations.h>
#include "SourceParser.h"
#include <mare_compiler.h>

using namespace std;

class SourceScanner : public yyFlexLexer
{
	public:
	SourceScanner(std::istream& in,
					  std::ostream& out,
					  bool supressErrs = false,
					std::ostream& err = std::cerr);

	virtual ~SourceScanner();

	using FlexLexer::yylex;
	virtual int yylex(yy::SourceParser::semantic_type* const lval,
							yy::SourceParser::location_type* location);

	inline MARECompiler* GetCPtr() 
	{
		_c.SetLineNumber(yylineno);
		return &_c;
	}

	private:
	yy::SourceParser::semantic_type* yylval = nullptr;
	yy::SourceParser::location_type* loc = nullptr;

	MARECompiler _c;
	
};
