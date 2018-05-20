#include "mare_stmt.h"

Statement::Statement(const Statement& c) :
	_ret_expr_p(c._ret_expr_p)
{
}

Statement::Statement(Statement&& m) :
	_ret_expr_p(std::move(m._ret_expr_p))
{
}

Statement::Statement(const Operator& op) :
	_ret_expr_p(op)
{
}

Statement::Statement(const Expression& retExpr) :
	_ret_expr_p(retExpr)
{
}

Statement::~Statement()
{

}

void Statement::_Print(std::ostream& os) const
{
	os << _ret_expr_p;
}
