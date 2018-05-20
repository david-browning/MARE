#pragma once
#include <annotations.h>
#include "mare_expression.h"
#include "mare_operator.h"

class LIB_EXPORT Statement
{
	public:
	Statement(const Statement& c);

	Statement(Statement&& m);

	Statement(const Operator& op);

	Statement(const Expression& retExpr_p);

	virtual ~Statement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const Statement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Expression _ret_expr_p;
};

static const Statement NOP_STATEMENT(NOP_OPERATOR);

typedef std::shared_ptr<Statement> StmtPtr;
typedef std::vector<StmtPtr> StmtList;