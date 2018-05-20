#pragma once
#include <annotations.h>
#include "mare_stmt.h"
#include "mare_isymbol_table.h"
#include <regex>
#include <sstream>

class LIB_EXPORT CodeStatement : public Statement
{
	public:
	template<class SymbolID, class Scope>
	CodeStatement(const std::string& inlineCode, const ISymbolTable<SymbolID, Scope>& symTable) :
		Statement(NOP_STATEMENT), _code(inlineCode)
	{
		std::stringstream formattedCode;

		std::regex e("(\\$\\w+)|"
						 "(\\^\\S+\\()|"
						 ".");
		auto words = std::sregex_iterator(_code.begin(), _code.end(), e);
		auto wordsend = std::sregex_iterator();
		for(std::sregex_iterator i = words; i != wordsend; ++i)
		{
			std::smatch match = *i;
			std::string token = match.str();
			switch(token[0])
			{
				case '$':
				{
					std::string symName = token.c_str() + 1;
					auto sym = symTable.Lookup(symName);
					if(!sym)
					{
						throw symbol_not_defined_exception(symName);
					}
					formattedCode << *sym;
					break;
				}
				case '^':
				{
					formattedCode << "this->_rt." << token.c_str() + 1;
					break;
				}
				default:
				{
					formattedCode << token;
					break;
				}
			}
		}

		formattedCode << ';';
		_code = formattedCode.str();
	}

	CodeStatement(const CodeStatement& c) :
		Statement(NOP_STATEMENT), _code(c._code)
	{

	}

	CodeStatement(CodeStatement&& m) :
		Statement(NOP_STATEMENT)
	{
		_code = std::move(m._code);
	}

	virtual ~CodeStatement()
	{

	}

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const CodeStatement& stmt)
	{
		stmt._Print(os);
		return os;
	}

	protected:
	std::string _code;

	virtual void _Print(std::ostream& os) const
	{
		os << _code;
	}
};