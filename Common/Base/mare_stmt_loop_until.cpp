#include "mare_stmt_loop_until.h"

LoopUntilStatement::LoopUntilStatement(const Expression& condition,
													const StmtList& stmts) :
	LoopStatement(condition, stmts)
{
}

LoopUntilStatement::LoopUntilStatement(const LoopUntilStatement& c):
	LoopStatement(c)
{
}

LoopUntilStatement::LoopUntilStatement(LoopUntilStatement&& m):
	LoopStatement(m)
{
}

LoopUntilStatement::~LoopUntilStatement()
{
}

void LoopUntilStatement::_Print(std::ostream& os) const
{
	os << "while(!(" << this->_ret_expr_p << "))\n";
	os << "\t\t{\n";

	for(auto& e : this->_stmts)
	{
		os << "\t\t\t" << *e << std::endl;
	}

	os << "\t\t}\n";
}
