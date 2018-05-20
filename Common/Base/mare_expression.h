#pragma once

#include <annotations.h>
#include "mare_literal.h"
#include "mare_operator.h"
#include "mare_symbol.h"

/*
 An expression is a binary tree where the two children are literals, symbols, or expressions.
 The root is most-likely going to be an operator.
 */
class LIB_EXPORT Expression : public Literal
{
	public:
	Expression(_IN_ const IAtom& typeInfo);

	Expression(_IN_ const Literal& lit);

	Expression(_IN_ const Symbol& sym);

	Expression(_IN_ const Operator& op);

	Expression(_IN_ const Symbol& arrName, const Expression& idx);

	/*
	 Copy constructor.
	 */
	Expression(const Expression& c);

	/*
	 Destructor
	 */
	virtual ~Expression();

	virtual void SetRoot(_IN_POINTER_ const std::shared_ptr<Literal>& root_p);

	/*
	 Sets the left child to the expression "expr_p" and updates the expression's type.
	 If the right or left child types are not compatible, this throws a type_mismatch_exception. 
	 */
	virtual void SetRight(_IN_POINTER_ const std::shared_ptr<Literal>& expr_p);

	/*
	 Sets the left child to the expression "expr_p" and updates the expression's type.
	 If the right or left child types are not compatible, this throws a type_mismatch_exception. 
	 */
	virtual void SetRight(const Expression& expr);

	/*
	 Sets the left child to the expression "expr_p" and updates the expression's type.
	 If the right or left child types are not compatible, this throws a type_mismatch_exception. 
	 */
	virtual void SetLeft(_IN_POINTER_ const std::shared_ptr<Literal>& expr_p);

	/*
	 Sets the left child to the expression "expr_p" and updates the expression's type.
	 If the right or left child types are not compatible, this throws a type_mismatch_exception. 
	 */
	virtual void SetLeft(const Expression& expr);

	/*
	 Sets a third child element to a list of expressions. The list is printed in order when 
	 using the << operator. The expression list does not affect the expression's type.
	 Only 1 expression list can be set for an expression. Calling this again will overwrite
	 the current expression list. 
	 When this class is constructed, the expression list is empty.
	 */
	virtual void SetList(const std::vector<Expression>& exprs);

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const Expression& expr)
	{
		expr._Print(os);
		return os;
	}

	/*
	 Copies the right operand to this.
	 */
	void operator=(const Expression& l);

	protected:
	virtual void _Print(std::ostream& os) const;

	std::shared_ptr<Literal> _right_p;
	std::shared_ptr<Literal> _left_p;
	std::shared_ptr<Literal> _root_p;

	/*
	 List of expressions to print. This is used when calling a function.
	 The right child is the function symbol and the expression list is the list of
	 arguments passed to the function.
	 */
	std::vector<Expression> _exprList;

	bool _isIndexOp;
};

typedef std::vector<Expression> ExprList;