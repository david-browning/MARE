#include "mare_stmt_loop.h"

LoopStatement::LoopStatement(const Expression& condition,
									  const StmtList& stmts) :
	Statement(condition), _stmts(stmts)
{
}

LoopStatement::LoopStatement(const LoopStatement& c):
	Statement(c), _stmts(c._stmts)
{
}

LoopStatement::LoopStatement(LoopStatement&& m):
	Statement(m), _stmts(std::move(m._stmts))
{
}

LoopStatement::~LoopStatement()
{
}