#pragma once

#include <annotations.h>
#include <functional>
#include "mare_symbol.h"

/*
 Keeps track of a list of symbols, including their scope.
 Symbols can be inserted, and when their scope closes, symbols in that
 scope are destroyed.

 If using a scope type that is not a numeric type, overload these operators for
 the Scope: ==, =, -, +, destructor, >, <, default constructor
 */
template <class SymbolID = std::string, class Scope = int>
class ISymbolTable
{
	public:
	ISymbolTable(_IN_FUNCTION_ const std::function<SymbolID(const SymbolID&)> symMutator) :
		_symMutator(symMutator), _scopeLevel()
	{

	}

	virtual ~ISymbolTable()
	{

	}

	/*
	 Inserts a symbol with name symName into the table and returns a pointer to the newly
	 inserted symbol.
	 Throw symbol_already_defined_exception if the symbol already exists.
	 */
	virtual Symbol* Insert(_IN_ const SymbolID& symName,
								  _IN_POINTER_ const IAtom& typeInfo_p)
	{
		auto mangledName = _symMutator(symName);
		Symbol* ret = nullptr;
		_m.lock();

		auto it = std::find_if(_table.begin(), _table.end(), isNameEqual(mangledName));
		if(it == _table.end())
		{
			//A symbol was not found. Insert a new one.
			_table.emplace_front(typeInfo_p, mangledName, _scopeLevel);
			ret = &_table.front();
		}
		else
		{
			//A duplicate symbol was found.
			_m.unlock();
			//throw symbol_already_declared_exception(symName);
			return nullptr;
		}

		_m.unlock();
		return ret;
	}

	/*
	 Searches the table for the symbol with name symName and returns a pointer to the symbol.
	 Throws symbol_not_defined_exception if the symbol was not found.
	 */
	virtual const Symbol* Lookup(_IN_STR_ const SymbolID& symName) const
	{
		auto mangledName = _symMutator(symName);
		const Symbol* ret = nullptr;
		_m.lock();

		auto it = std::find_if(_table.begin(), _table.end(), isNameEqual(mangledName));
		if(it != _table.end())
		{
			//The symbol was found.
			ret = &*it;
		}
		else
		{
			//Symbol not found.
			_m.unlock();
			//throw symbol_not_defined_exception(symName);
			return nullptr;
		}

		_m.unlock();
		return ret;
	}

	/*
	 Increases the scope level. Symbols added are added to the new scope. When the scope is closed,
	 the symbols are removed.
	 */
	virtual void OpenScope()
	{
		_m.lock();
		//The only reason I didn't use the increment operator is so the scope type
		//does not need to overload it.
		_scopeLevel = _scopeLevel + 1;
		_m.unlock();
	}

	/*
	 Decrements the scope. Symbols with the old scope level are removed.
	 */
	virtual void CloseScope()
	{
		_m.lock();
		if(_scopeLevel - 1 < 0)
		{
			//Just unload the mutex if someone tries to close too many scopes.
			_m.unlock();
			return;
		}

		//Decrement the scope level and remove all symbols who's scope is higher than the 
		//decremented scope.
		//The only reason I didn't use the decrement operator is so the scope type
		//does not need to overload it.
		_scopeLevel = _scopeLevel - 1;
		_table.remove_if(isOutOfScope(_scopeLevel));

		_m.unlock();
	}

	/*
	 Returns the current scope level.
	 */
	inline Scope GetCurrentLevel() const
	{
		return _scopeLevel;
	}

	protected:
	 //The current scope level.
	Scope _scopeLevel;

	//Mutex locks many operations so the symbol table can be read and write by parallel operations.
	mutable std::mutex _m;

	//List of symbols
	std::list<Symbol> _table;

	std::function<SymbolID(const SymbolID&)> _symMutator;

	/*
	 Used as a predicate to determine if a symbol is out of scope.
	 */
	struct LIB_EXPORT isOutOfScope
	{
		isOutOfScope(_IN_INT_ Scope curScope)
		{
			_curScope = curScope;
		}

		/*
		 Returns true if symbol sym is outside the scope.
		 */
		bool operator()(const Symbol &sym)
		{
			return sym.GetScopeLevel() > _curScope;
		}

		Scope _curScope;
	};

	/*
	 Used as a predicate to determine if two symbols share the same name.
	 */
	struct LIB_EXPORT isNameEqual
	{
		isNameEqual(const SymbolID& name) : _name(name)
		{
		}

		~isNameEqual()
		{
		}

		/*
		 Returns true if the symbol names are the same.
		 */
		bool operator()(const Symbol &sym)
		{
			return sym.GetSymbolName() == _name;
		}

		SymbolID _name;
	};
};
