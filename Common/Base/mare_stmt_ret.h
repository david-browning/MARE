#pragma once
#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT ReturnStatement : public Statement
{
	public:
	ReturnStatement(const Expression& retExpr);

	ReturnStatement(const ReturnStatement& c);

	ReturnStatement(ReturnStatement&& m);

	virtual ~ReturnStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const ReturnStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;
};