#include "mare_stmt_param.h"

ParameterStatement::ParameterStatement(const Symbol& arg) :
	Statement(NOP_STATEMENT), _s(arg)
{
}

ParameterStatement::ParameterStatement(const ParameterStatement& c):
	Statement(NOP_STATEMENT), _s(c._s)
{
}

ParameterStatement::ParameterStatement(ParameterStatement&& m):
	Statement(NOP_STATEMENT), _s(std::move(m._s))
{
}

ParameterStatement::~ParameterStatement()
{
}

void ParameterStatement::_Print(std::ostream& os) const
{
	_s.PrintDeclaration(os, _s.IsArrayType() || _s.IsCompoundType());
}
