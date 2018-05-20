#include "mare_stmt_assignment.h"

AssignmentStatement::AssignmentStatement(const Symbol& varSym, 
													  const Expression& expr):
	Statement(expr), _s(varSym)
{

}

AssignmentStatement::AssignmentStatement(const Symbol& arrSym,
													  const Expression& index,
													  const Expression& expr) :
	Statement(expr), _s(arrSym), 
	_index_p(std::make_shared<Expression>(index))
{
	
}

AssignmentStatement::AssignmentStatement(const AssignmentStatement& c):
	Statement(c), _s(c._s), _index_p(c._index_p)
{
}

AssignmentStatement::AssignmentStatement(AssignmentStatement&& m):
	Statement(std::move(m)), _s(std::move(m._s)), 
	_index_p(std::move(m._index_p))
{
}

AssignmentStatement::~AssignmentStatement()
{

}

void AssignmentStatement::_Print(std::ostream & os) const
{
	os << _s;

	if(_index_p)
	{
		os << '[' << *_index_p << ']';
	}

	os << " = " << _ret_expr_p << ";\n";
}
