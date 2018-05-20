#pragma once

#include <annotations.h>
#include "mare_stmt.h"

class LIB_EXPORT ParameterStatement : public Statement
{
	public:
	ParameterStatement(const Symbol& arg);
	ParameterStatement(const ParameterStatement& c);
	ParameterStatement(ParameterStatement&& m);

	virtual ~ParameterStatement();

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const ParameterStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	virtual void _Print(std::ostream& os) const;

	Symbol _s;

};