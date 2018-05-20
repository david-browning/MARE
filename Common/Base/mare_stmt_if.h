#pragma once
#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT IfStatement : public Statement
{
	public:
	IfStatement(const Expression& conditional, const StmtList& trueStmts);

	IfStatement(const Expression& conditional, const StmtList& trueStmts, const StmtList& falseStmts);

	virtual ~IfStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const IfStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;
	StmtList _trueStmts;
	StmtList _falseStmts;
};