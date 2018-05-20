#pragma once
#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT AssignmentStatement : public Statement
{
	public:
	AssignmentStatement(const Symbol& varSym, const Expression& expr);

	AssignmentStatement(const Symbol& arrSym, const Expression& index, const Expression& expr);

	AssignmentStatement(const AssignmentStatement& c);

	AssignmentStatement(AssignmentStatement&& m);

	virtual ~AssignmentStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const AssignmentStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Symbol _s;
	std::shared_ptr<Expression> _index_p;
};