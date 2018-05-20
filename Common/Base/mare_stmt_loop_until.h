#pragma once
#include <annotations.h>
#include "mare_stmt_loop.h"

class LIB_EXPORT LoopUntilStatement : public LoopStatement
{
	public:
	LoopUntilStatement(const Expression& condition,
							 const StmtList& stmts);

	LoopUntilStatement(const LoopUntilStatement& c);

	LoopUntilStatement(LoopUntilStatement&& m);

	virtual ~LoopUntilStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const LoopUntilStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;
};