#include "mare_stmt_compound_decl.h"

CompoundDeclStatement::CompoundDeclStatement(const std::string& typeName,
															const StmtList& stmts) :
	Statement(NOP_OPERATOR), _stmts(stmts)
{
}

CompoundDeclStatement::CompoundDeclStatement(const CompoundDeclStatement& c) :
	Statement(NOP_OPERATOR), _stmts(c._stmts)
{
}

CompoundDeclStatement::CompoundDeclStatement(CompoundDeclStatement&& m) :
	Statement(NOP_OPERATOR)
{
	_stmts = std::move(m._stmts);
}

CompoundDeclStatement::~CompoundDeclStatement()
{
}

void CompoundDeclStatement::_Print(std::ostream& os) const
{
}
