#pragma once

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <annotations.h>
#include <mare_dependency_graph.h>
#include "PreprocessorParser.h"
#include <mare_source_file.h>
#include <mare_linker.h>
#include <mare_linker_options.h>
#include <mare_linker_atomic_options.h>

using namespace std;
using namespace yy;

class PreprocessorScanner : public yyFlexLexer
{
	public:
	PreprocessorScanner(std::istream& in,
							  std::ostream& out,
							  const std::string& sourceFilePath,
							  std::shared_ptr<AtomicLinkerOptions>& linkerOpts);

	virtual ~PreprocessorScanner();

	using FlexLexer::yylex;
	virtual int yylex(yy::PreprocessorParser::semantic_type* const lval,
							yy::PreprocessorParser::location_type* location);

	SourceFile& GetSourceFile()
	{
		return _s;
	}

	void AddDependency(_IN_STR_ const std::string& s);

	std::shared_ptr<AtomicLinkerOptions> GetLinkerOptionsPtr()
	{
		return _l;
	}

	private:
	yy::PreprocessorParser::semantic_type* yylval = nullptr;
	yy::PreprocessorParser::location_type* loc = nullptr;

	SourceFile _s;
	std::shared_ptr<AtomicLinkerOptions> _l;
};
