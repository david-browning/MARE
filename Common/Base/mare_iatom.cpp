#include "mare_iatom.h"
#include "mare_exceptions.h"

IAtom::IAtom(_IN_ENUM_ MARE_TYPES type) :
	_type(type), _arrayCount(0)
{
}

IAtom::IAtom(const IAtom& other)
{
	UpdateTypeInfo(other);
}

IAtom::IAtom(IAtom&& m) :
	_type(m._type), _arrayCount(m._arrayCount), _args(std::move(m._args))
{
}

IAtom::~IAtom()
{
	_type = MARE_TYPES::UNDEFINED_TYPE;
}

void IAtom::UpdateTypeInfo(const IAtom& typeInfo)
{
	this->_type = typeInfo._type;
	this->_arrayCount = typeInfo._arrayCount;
	if (!typeInfo._args.empty())
	{
		std::copy(typeInfo._args.begin(), typeInfo._args.end(), std::back_inserter(_args));
	}
}

void IAtom::AppendArgument(_IN_ const IAtom& type)
{
	if (!IsFunctionType() && !IsCompoundType())
	{
		throw invalid_type_exception();
	}

	_args.push_back(type);
}

void IAtom::MakeArray(_IN_SIZE_ size_t arrayCount) noexcept
{
	_type = _type | MARE_TYPES::ARRAY_TYPE;
	_arrayCount = arrayCount;
}

size_t IAtom::GetArrayCount() const
{
	if (!IsArrayType())
	{
		throw invalid_type_exception();
	}

	return _arrayCount;
}

size_t IAtom::GetArgumentCount() const
{
	if (!IsFunctionType() && !IsCompoundType())
	{
		throw invalid_type_exception();
	}

	return _args.size();
}

void IAtom::_Print(std::ostream& os) const
{
	os << GetBaseType();
}
