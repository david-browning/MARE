#pragma once

#include <annotations.h>
#include "mare_literal.h"

/*
 A symbol is a literal but the data the literal holds is the symbol name.
 When printed using the << operator, this prints the symbol name.
 */
class LIB_EXPORT Symbol : public Literal
{
	public:
	Symbol(_IN_POINTER_ const IAtom &typeInfo,
			 _IN_STR_ const std::string &symName,
			 _IN_INT_ const int scope);

	virtual ~Symbol();

	/*
	 Returns the symbol name including any mutations added to it.
	 Ex: A mutation may prepend the string "_var_" to a symbol "foo".
	 	  This returns "_var_foo"
	  The mutation are usually done by the iSymbolTable when a new symbol is inserted.
	 */
	const std::string GetSymbolName() const noexcept;

	inline int GetScopeLevel() const noexcept
	{
		return _scope;
	}

	void PrintDeclaration(std::ostream &os, bool refType = false) const;

	/*
	 Returns true if the right hand symbol has lower binding strength than the left.
	 */
	friend LIB_EXPORT bool operator<(const Symbol &right, const Symbol &left);

	/*
	 Returns true if the right hand symbol has higher binding strength than the left.
	 */
	friend LIB_EXPORT bool operator>(const Symbol &right, const Symbol &left);

	/*
	 Returns true if the right and left symbols have the same name and scope.
	 */
	friend LIB_EXPORT bool operator==(const Symbol &right, const Symbol &left);

	/*
	 Prints the symbol name to the stream.
	 */
	friend LIB_EXPORT std::ostream &operator<<(std::ostream &os, const Symbol &sym)
	{
		sym._Print(os);
		return os;
	}

	private:
	virtual void _Print(std::ostream &os) const;

	/*
	 Higher the number, the lower the binding strength.
	 */
	int _scope;
};

typedef std::shared_ptr<Symbol> ParamPtr;
typedef std::vector<ParamPtr> ParamList;