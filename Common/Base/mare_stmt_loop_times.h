#pragma once
#include <annotations.h>
#include "mare_stmt_loop.h"

class LIB_EXPORT LoopTimesStatement : public LoopStatement
{
	public:
	LoopTimesStatement(const Expression& condition,
							 const StmtList& stmts);

	LoopTimesStatement(const LoopTimesStatement& c);

	LoopTimesStatement(LoopTimesStatement&& m);

	virtual ~LoopTimesStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const LoopTimesStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;
};