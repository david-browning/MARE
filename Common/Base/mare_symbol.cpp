#include "mare_symbol.h"
#include "mare_expression.h"

Symbol::Symbol(_IN_POINTER_ const IAtom& typeInfo,
					_IN_STR_ const std::string& symName,
					_IN_INT_ const int scope) :
	Literal(typeInfo, symName.c_str(), symName.size() + 1)
{
	_scope = scope;
}

Symbol::~Symbol()
{
	_scope = -1;
}

const std::string Symbol::GetSymbolName() const noexcept
{
	return std::string(Literal::GetDataPointer<char>());
}

void Symbol::PrintDeclaration(std::ostream& os, bool refType) const
{
	if(IsConstantType())
	{
		os << "const ";
	}
	
	bool isArrayType = IsArrayType();
	if(isArrayType)
	{
		os << "std::array<";
	}

	switch(BaseMareType(GetBaseType()))
	{
		case NULL_TYPE:
		{
			os << "void";
			break;
		}
		case INT8_TYPE:
		{
			os << "int8_t";
			break;
		}
		case INT16_TYPE:
		{
			os << "int16_t";
			break;
		}
		case INT32_TYPE:
		{
			os << "int32_t";
			break;
		}
		case INT64_TYPE:
		{
			os << "int64_t";
			break;
		}
		case FLOAT32_TYPE:
		{
			os << "float";
			break;
		}
		case FLOAT64_TYPE:
		{
			os << "double";
			break;
		}
		case CHARACTER_TYPE:
		{
			os << "char";
			break;
		}
		default:
		{
			os << "auto";
		}
	}

	if(isArrayType)
	{
		os << ", ";
		auto arrayCount = GetArrayCount();

		if(arrayCount == 0)
		{
			os << GetSymbolName() + std::string("_COUNT");
		}
		else
		{
			os << arrayCount;
		}

		 os << '>';
	}

	if(refType)
	{
		os << '&';
	}

	os << ' ' << *this;
}

void Symbol::_Print(std::ostream & os) const
{
	os << GetSymbolName();
}

bool LIB_EXPORT operator<(const Symbol& right, const Symbol& left)
{
	return right._scope > left._scope;
}

bool LIB_EXPORT operator>(const Symbol& right, const Symbol& left)
{
	return right._scope < left._scope;
}

bool LIB_EXPORT operator==(const Symbol& right, const Symbol& left)
{
	return (left.GetSymbolName() == right.GetSymbolName()) && (right._scope == left._scope);
}
