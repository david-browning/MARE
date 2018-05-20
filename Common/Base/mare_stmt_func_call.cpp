#include "mare_stmt_func_call.h"

FunctionCallStatement::FunctionCallStatement(const Symbol& funcSym,
															const ExprList& args) :
	Statement(NOP_OPERATOR), _s(funcSym), _args(args)
{
}

FunctionCallStatement::FunctionCallStatement(const FunctionCallStatement& c) :
	Statement(c), _s(c._s), _args(c._args)
{
}

FunctionCallStatement::FunctionCallStatement(FunctionCallStatement&& m):
	Statement(m), _s(std::move(m._s))
{
	_args = std::move(m._args);
}

FunctionCallStatement::~FunctionCallStatement()
{
}

void FunctionCallStatement::_Print(std::ostream& os) const
{
	os << _s;
	
	//Check if the function call is templated.
	bool templated = false;
	for(size_t i = 0; i < _args.size(); i++)
	{
		if(_args[i].IsTemplateType())
		{
			templated = true;
			if(i == 0)
			{
				os << '<';
			}

			if(_args[i].IsArrayType())
			{
				auto arrayCount = _args[i].GetArrayCount();
				if(arrayCount == 0)
				{
					std::string varCount = std::string(_args[i].GetDataPointer<char>()) + std::string("_COUNT");
					Literal l(INT64_TYPE_INFO_C, varCount.c_str(), varCount.length(), true);
					os << l;
				}
				else
				{
					os << arrayCount;
				}
			}
			else
			{
				throw invalid_type_exception();
			}

			if(i + 1 < _args.size())
			{
				os << ", ";
			}
		}
	}

	if(templated)
	{
		os << '>';
	}

	os << "(";

	for(auto it = _args.begin(); it != _args.end(); ++it)
	{
		os << *it;
		if(it + 1 != _args.end())
		{
			os << ", ";
		}
	}

	os << ");";
}
