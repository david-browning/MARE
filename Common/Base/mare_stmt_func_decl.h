#pragma once
#include <annotations.h>
#include "mare_symbol.h"
#include "mare_stmt.h"
#include "mare_stmt_decl.h"

class LIB_EXPORT FunctionDeclarationStatement : public Statement
{
	public:
	FunctionDeclarationStatement(const Symbol& funcSym,
										  const ParamList& args,
										  const StmtList& stmts);

	FunctionDeclarationStatement(const FunctionDeclarationStatement& c);

	FunctionDeclarationStatement(FunctionDeclarationStatement&& m);

	virtual ~FunctionDeclarationStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const FunctionDeclarationStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Symbol _s;
	StmtList _stmts;
	ParamList _args;
};