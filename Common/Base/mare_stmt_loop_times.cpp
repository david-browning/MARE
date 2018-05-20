#include "mare_stmt_loop_times.h"

LoopTimesStatement::LoopTimesStatement(const Expression& condition,
													const StmtList& stmts) :
	LoopStatement(condition, stmts)
{
}

LoopTimesStatement::LoopTimesStatement(const LoopTimesStatement& c):
	LoopStatement(c)
{
}

LoopTimesStatement::LoopTimesStatement(LoopTimesStatement&& m) :
	LoopStatement(m)
{
}

LoopTimesStatement::~LoopTimesStatement()
{

}

void LoopTimesStatement::_Print(std::ostream& os) const
{

}
