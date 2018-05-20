#pragma once
#include <annotations.h>
#include "mare_stmt_decl.h"
#include "mare_symbol.h"

class LIB_EXPORT FunctionCallStatement : public Statement
{
	public:
	FunctionCallStatement(const Symbol& funcSym, const ExprList& args);

	FunctionCallStatement(const FunctionCallStatement& c);

	FunctionCallStatement(FunctionCallStatement&& m);

	virtual ~FunctionCallStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const FunctionCallStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Symbol _s;
	ExprList _args;
};