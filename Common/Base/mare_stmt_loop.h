#pragma once
#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT LoopStatement : public Statement
{
	public:
	LoopStatement(const Expression& condition, const StmtList& stmts);

	LoopStatement(const LoopStatement& c);

	LoopStatement(LoopStatement&& m);

	virtual ~LoopStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const LoopStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const = 0;

	StmtList _stmts;
};