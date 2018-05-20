#pragma once

#include <annotations.h>
#include "mare_literal.h"

/*
 An operator is a literal where the data is a string.
 Printing this prints the operator symbol.
 */
class LIB_EXPORT Operator : public Literal
{
	public:
	/*
	 Constructor.
	 "operatorStr" is the string representation of an operator.
	 Ex: +, -, --
	 One operator does not have a string representation and it is the index operator "[]".
	 The index operator is a special case and is only valid when it is a branch of an
	 expression. Use the constant "INDEX_OPERATOR" for indexing arrays in an expression.
	 */
	Operator(_IN_STR_ const std::string& operatorStr);

	/*
	 Copy constructor.
	 */
	Operator(const Operator& op);

	/*
	 Move constructor.
	 */
	Operator(Operator&& m);

	/*
	 Destructor
	 */
	virtual ~Operator();

	/*
	 Returns true if the right operator is the same as the left operator.
	 */
	friend bool operator==(const Operator& l, const Operator& r);

	/*
	 Prints the operator to output.
	 */
	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const Operator& op)
	{
		op._Print(os);
		return os;
	}

	private:
	virtual void _Print(std::ostream& os) const;
};

static const Operator INCREMENT_OPERATOR("++");
static const Operator DECREMENT_OPERATOR("--");
static const Operator MULTIPLY_OPERATOR("*");
static const Operator DIVIDE_OPERATOR("/");
static const Operator MODULO_OPERATOR("%");
static const Operator ADD_OPERATOR("+");
static const Operator SUBTRACT_OPERATOR("-");
static const Operator HAT_OPERATOR("^");
static const Operator BRACKET_OPERATOR_L("[");
static const Operator BRACKET_OPERATOR_R("]");
static const Operator INDEX_OPERATOR("idx");
static const Operator SCOPE_OPERATOR(".");

static const Operator EQUALS_OPERATOR("==");
static const Operator LT_OPERATOR("<");
static const Operator GT_OPERATOR(">");
static const Operator LTE_OPERATOR("<=");
static const Operator GTE_OPERATOR(">=");
static const Operator NOT_OPERATOR("!");
static const Operator AND_OPERATOR("&&");
static const Operator OR_OPERATOR("||");

/*
 The NOP_OPERATOR is used in special cases when an expression does not need an operator.
 */
static const Operator NOP_OPERATOR("");