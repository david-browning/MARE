#include "mare_operator.h"

Operator::Operator(_IN_STR_ const std::string& operatorStr)
	: Literal(NO_TYPE_INFO, operatorStr.c_str(), operatorStr.size() + 1)
{

}

Operator::Operator(const Operator& op)
	: Literal(NO_TYPE_INFO, op._data, op._size)
{
}

Operator::Operator(Operator && m) :
	Literal(NO_TYPE_INFO, m._data, m._size)
{
}

Operator::~Operator()
{
}

void Operator::_Print(std::ostream& os) const
{
	os << GetDataPointer<char>();
}

bool operator==(const Operator & l, const Operator & r)
{
	size_t memSize = std::min<size_t>(l._size, r._size);
	return memcmp(l._data, r._data, memSize) == 0;
}
