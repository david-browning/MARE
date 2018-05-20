#include "mare_stmt_decl.h"

DeclarationStatement::DeclarationStatement(const Symbol& varSym, 
														 const Expression& expr):
	Statement(expr), _s(varSym)
{
}

DeclarationStatement::DeclarationStatement(const Symbol& arrSym,
														 const ExprList& exprs):
	Statement(NOP_STATEMENT), _s(arrSym)

{
	_arrayExprs_p = exprs;
}

DeclarationStatement::DeclarationStatement(const DeclarationStatement& c):
	Statement(c), _s(c._s)

{
	_arrayExprs_p = c._arrayExprs_p;
}

DeclarationStatement::DeclarationStatement(DeclarationStatement&& m):
	Statement(m), _s(std::move(m._s))
{
	_arrayExprs_p = std::move(m._arrayExprs_p);
}

DeclarationStatement::~DeclarationStatement()
{
}

void DeclarationStatement::_Print(std::ostream& os) const
{
	_s.PrintDeclaration(os);

	if(!_arrayExprs_p.empty())
	{
		os << " = { ";

		for(auto it = _arrayExprs_p.begin(); it != _arrayExprs_p.end(); ++it)
		{
			os << *it;
			if(it + 1 != _arrayExprs_p.end())
			{
				os << ", ";
			}
		}
		os << " }";
	}
	else
	{
		os << " = " << this->_ret_expr_p;
	}

	os << ';';
}
