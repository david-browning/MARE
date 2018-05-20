#include "mare_stmt_ret.h"

ReturnStatement::ReturnStatement(const Expression& retExpr) :
	Statement(retExpr)
{
}

ReturnStatement::ReturnStatement(const ReturnStatement& c) :
	Statement(c._ret_expr_p)
{
}

ReturnStatement::ReturnStatement(ReturnStatement&& m) :
	Statement(std::move(m._ret_expr_p))
{
}

ReturnStatement::~ReturnStatement()
{
}

void ReturnStatement::_Print(std::ostream& os) const
{
	os << "return " << _ret_expr_p << ";";
}
