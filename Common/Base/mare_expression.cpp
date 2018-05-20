#include "mare_expression.h"
#include "mare_compiler_type_comparator.h"

Expression::Expression(_IN_ const IAtom& typeInfo) :
	Literal(typeInfo), _isIndexOp(false)
{
	_root_p = nullptr;
}

Expression::Expression(_IN_ const Literal& lit) :
	Literal(lit), _isIndexOp(false)
{
	SetRoot(std::make_shared<Literal>(lit));
}

Expression::Expression(_IN_ const Symbol& sym) :
	Literal(sym), _isIndexOp(false)
{
	SetRoot(std::make_shared<Symbol>(sym));
}

Expression::Expression(_IN_ const Operator& op) :
	Literal(op) //, _isIndexOp(false)
{
	SetRoot(std::make_shared<Operator>(op));
	// if(op == INDEX_OPERATOR)
	// {
	// 	_isIndexOp = true;
	// }
}

Expression::Expression(_IN_ const Symbol& arrName, 
							  const Expression& idx) :
	Literal(arrName), _isIndexOp(true)
{
	Symbol noArrayType(arrName);
	noArrayType.UpdateTypeInfo(idx);

	SetRoot(std::make_shared<Operator>(INDEX_OPERATOR));
	SetLeft(noArrayType);
	SetRight(idx);
}

Expression::Expression(const Expression& c) :
	Literal(c), _exprList(c._exprList), _isIndexOp(c._isIndexOp)
{
	if(c._root_p.get())
	{
		SetRoot(c._root_p);
	}

	if(c._left_p.get())
	{
		SetLeft(c._left_p);
	}

	if(c._right_p.get())
	{
		SetRight(c._right_p);
	}
}

Expression::~Expression()
{

}

void Expression::SetRoot(_IN_POINTER_ const std::shared_ptr<Literal>& root)
{
	UpdateTypeInfo(*root);
	_root_p = root;
}

void Expression::SetRight(_IN_POINTER_ const std::shared_ptr<Literal>& expr)
{
	//Check that the types are compatible.
	IAtom opResult(NO_TYPE_INFO);

	//If there is another child, check that the new child is compatible with the other.
	if(_left_p)
	{
		if(!IsTypesOperatable(*_left_p, *expr, &opResult))
		{
			//Types not compatible.
			throw type_mismatch_exception();
		}

		//Update this's type
		UpdateTypeInfo(opResult);
	}
	//There is no other child 
	else
	{
		//Update this's type
		UpdateTypeInfo(*expr);
	}

	_right_p = expr;
}

void Expression::SetRight(const Expression & expr)
{
	SetRight(std::make_shared<Expression>(expr));
}

void Expression::SetLeft(_IN_POINTER_ const std::shared_ptr<Literal>& expr)
{
	//Check that the types are compatible.
	IAtom opResult(NO_TYPE_INFO);

	//If there is another child, check that the new child is compatible with the other.
	if(_right_p)
	{
		if(!IsTypesOperatable(*_right_p, *expr, &opResult))
		{
			//Types not compatible.
			throw type_mismatch_exception();
		}

		//Update this's type
		UpdateTypeInfo(opResult);
	}
	//There is no other child 
	else
	{
		//Update this's type
		UpdateTypeInfo(*expr);
	}

	_left_p = expr;
}

void Expression::SetLeft(const Expression& expr)
{
	SetLeft(std::make_shared<Expression>(expr));
}

void Expression::SetList(const std::vector<Expression>& exprs)
{
	_exprList = exprs;
}

void Expression::operator=(const Expression& l)
{
	UpdateTypeInfo(*l._root_p);
	SetRoot(l._root_p);
	SetLeft(l._left_p);
	SetRight(l._right_p);
	//_isIndexOp = l._isIndexOp;
}

void Expression::_Print(std::ostream& os) const
{
	for(auto x : _exprList)
	{
		os << x << " ";
	}

	if(_left_p)
	{
		os << *_left_p;
	}

	if(_root_p)
	{
		 if(_isIndexOp)
		 {
		 	os << "[";
		 }
		 else
		 {
			os << *_root_p;
		 }
	}

	if(_right_p)
	{
		os << *_right_p;
		 if(_isIndexOp)
		 {
		 	os << "]";
		 }
	}
}