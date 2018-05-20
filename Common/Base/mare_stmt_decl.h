#pragma once

#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT DeclarationStatement : public Statement
{
	public:
	DeclarationStatement(const Symbol& varSym, const Expression& expr);

	DeclarationStatement(const Symbol& arrSym, const ExprList& exprs);

	DeclarationStatement(const DeclarationStatement& c);

	DeclarationStatement(DeclarationStatement&& m);

	virtual ~DeclarationStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const DeclarationStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Symbol _s;
	ExprList _arrayExprs_p;
};

