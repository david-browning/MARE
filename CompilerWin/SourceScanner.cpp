#include "SourceScanner.h"

SourceScanner::SourceScanner(std::istream& in,
									  std::ostream& out,
									  bool supressErrs,
									  std::ostream& err)
	:yyFlexLexer(in, out), _c(out, supressErrs, err)
{
	loc = new yy::SourceParser::location_type();
}

SourceScanner::~SourceScanner()
{
	delete loc;
}
