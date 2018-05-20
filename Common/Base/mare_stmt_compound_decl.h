#pragma once
#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT CompoundDeclStatement : public Statement
{
	public:
	CompoundDeclStatement(const std::string& typeName, const StmtList& stmts);

	CompoundDeclStatement(const CompoundDeclStatement& c);

	CompoundDeclStatement(CompoundDeclStatement&& m);

	virtual ~CompoundDeclStatement();

	protected:
	virtual void _Print(std::ostream& os) const;
	StmtList _stmts;
};