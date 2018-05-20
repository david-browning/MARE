#include "mare_stmt_if.h"

IfStatement::IfStatement(const Expression& conditional,
								 const StmtList& trueStmts):
	Statement(conditional), _trueStmts(trueStmts)
{
	
}

IfStatement::IfStatement(const Expression& conditional,
								 const StmtList& trueStmts, 
								 const StmtList& falseStmts):
	Statement(conditional), _trueStmts(trueStmts), _falseStmts(falseStmts)
{
}

IfStatement::~IfStatement()
{

}

void IfStatement::_Print(std::ostream& os) const
{
	os << _ret_expr_p << std::endl;

	
		os << "{" << std::endl;
		for(auto it = _trueStmts.begin(); it != _trueStmts.end(); ++it)
		{
			os << **it << std::endl;
		}
		os << "}" << std::endl;


	if(!_falseStmts.empty())
	{
		os << "{" << std::endl;
		for(auto it = _falseStmts.begin(); it != _falseStmts.end(); ++it)
		{
			os << **it << std::endl;
		}
		os << "}" << std::endl;
		os << NOP_OPERATOR << std::endl;
	}
	else
	{
		os << NOP_OPERATOR << std::endl;
	}
}
