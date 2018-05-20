#pragma once

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <annotations.h>
#include <mare_linker_atomic_options.h>
#include <mare_compiler_options.h>
#include "CMDLParser.h"

using namespace yy;
using namespace std;

class CMDLScanner : public yyFlexLexer
{
	public:
	CMDLScanner(std::istream& in,
					std::ostream& out,
					std::shared_ptr<COMPILER_OPTIONS>& compOpts,
					std::shared_ptr<AtomicLinkerOptions>& linkerOpts);

	virtual ~CMDLScanner();

	using FlexLexer::yylex;
	virtual int yylex(yy::CMDLParser::semantic_type* const lval,
							yy::CMDLParser::location_type* location);

	void SetDebugMode();

	void SetSaveStreamFile();

	void SetShowHelp();

	void SetShowVersion();

	void SetShowMetrics();

	void SetOutFile(const std::string& filename);

	void AddSourceFile(const std::string& file);

	void SetDPI(int dpi);

	void SetVerbose();

	private:
	yy::CMDLParser::semantic_type* yylval = nullptr;
	yy::CMDLParser::location_type* loc = nullptr;

	std::shared_ptr<COMPILER_OPTIONS> _opts;
	std::shared_ptr<AtomicLinkerOptions> _l;
};
