#include "PreprocessorScanner.h"
#include <mare_exceptions.h>

PreprocessorScanner::PreprocessorScanner(std::istream& in,
													  std::ostream& out,
													  const std::string& sourceFilePath,
													  std::shared_ptr<AtomicLinkerOptions>& linkerOpts) :
	yyFlexLexer(in, out), _s(sourceFilePath), _l(linkerOpts)
{
	loc = new yy::PreprocessorParser::location_type();
}

PreprocessorScanner::~PreprocessorScanner()
{
	delete loc;
}

void PreprocessorScanner::AddDependency(_IN_STR_ const std::string& s)
{
	_s.AddDependency(s);
}
