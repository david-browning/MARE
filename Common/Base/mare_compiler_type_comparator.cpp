#include "mare_compiler_type_comparator.h"

static const std::bitset<MARE_NUM_TYPES>__assignableMatrix[MARE_NUM_TYPES] =
{
	/*Un*/{ 0b0000000000000 },
	/*08*/{ 0b0000000000110 },
	/*ch*/{ 0b0000000000110 },
	/*16*/{ 0b0000000001110 },
	/*32*/{ 0b0000000011110 },
	/*f3*/{ 0b0000000111110 },
	/*64*/{ 0b0000001011110 },
	/*f6*/{ 0b0000011111110 },
	/*cm*/{ 0b0011111111110 },
	/*in*/{ 0b0011111111110 },
	/*pi*/{ 0b0000000000000 },
	/*cp*/{ 0b0000000000010 },
	/*nu*/{ 0b0000000000000 },
};

static const std::bitset<MARE_NUM_TYPES> __operatableMatrix[MARE_NUM_TYPES] =
{
	/*Un*/{ 0b1111111111111 },
	/*08*/{ 0b0111111111100 },
	/*ch*/{ 0b0111111111100 },
	/*16*/{ 0b0111111111100 },
	/*32*/{ 0b0111111111100 },
	/*f3*/{ 0b0111111111100 },
	/*64*/{ 0b0111111111100 },
	/*f6*/{ 0b0111111111100 },
	/*cm*/{ 0b0111111111100 },
	/*in*/{ 0b0111111111100 },
	/*pi*/{ 0b0111111111100 },
	/*cp*/{ 0b0000000000010 },
	/*nu*/{ 0b0000000000000 },
};

//Returns -1 if there was a domain error.
inline int TypeIndex(_IN_ENUM_ MARE_TYPES t) noexcept
{
	//index = log2(t) + 1
	double l = log2((double)t) + 1;
	if(l - (int)l != 0)
	{
		return -1;
	}

	return (int)l;
}

bool IsTypesAssignable(_IN_ const IAtom & left, _IN_ const IAtom & right, _IN_OPT_ bool declaringConstVar) noexcept
{
	const auto l = TypeIndex(left.GetBaseType());
	const auto r = TypeIndex(right.GetBaseType());

	//Check that the index worked and that the left is not constant.
	//This allows for function variables to be assigned. 
	if((!declaringConstVar && left.IsConstantType()) ||
		left.IsFunctionType() ||
		l == -1 ||
		r == -1)
	{
		return false;
	}

	//If its an array type, check that the number of elements is equal.
	const bool leftArray = left.IsArrayType();
	const bool rightArray = right.IsArrayType();
	if(leftArray && rightArray)
	{
		auto leftArrayCount = left.GetArrayCount();
		auto rightArrayCount = right.GetArrayCount();

		if((leftArrayCount != 0 && rightArrayCount != 0) && (left.GetArrayCount() != right.GetArrayCount()))
		{
			return false;
		}
	}
	else if(leftArray != rightArray)
	{
		return false;
	}

	//If its a compound type
	if(left.IsCompoundType() && right.IsCompoundType())
	{
		//Check that the sub-types are the same.
		auto largs = left.ArgBegin();
		auto rargs = right.ArgBegin();

		if(left.GetArgumentCount() != right.GetArgumentCount())
		{
			return false;
		}

		for(;
			 largs != left.ArgEnd() || rargs != right.ArgEnd();
			 largs++, rargs++)

		{
			if(!IsTypesAssignable(*largs, *rargs))
			{
				return false;
			}
		}
	}

	bool res = __assignableMatrix[l][r];
	return res;
}

bool IsArrayIndexTypeAssignable(_IN_ const IAtom & left, _IN_ const IAtom & right) noexcept
{
	const auto l = TypeIndex(left.GetBaseType());
	const auto r = TypeIndex(right.GetBaseType());

	//Check that the index worked and that the left is not constant.
	//This allows for function variables to be assigned. 
	if(left.IsConstantType() || left.IsFunctionType() || l == -1 || r == -1)
	{
		return false;
	}

	//If its a compound type
	if(left.IsCompoundType() && right.IsCompoundType())
	{
		//Check that the sub-types are the same.
		auto largs = left.ArgBegin();
		auto rargs = right.ArgBegin();

		if(left.GetArgumentCount() != right.GetArgumentCount())
		{
			return false;
		}

		for(;
			 largs != left.ArgEnd() || rargs != right.ArgEnd();
			 largs++, rargs++)

		{
			if(!IsTypesAssignable(*largs, *rargs))
			{
				return false;
			}
		}
	}

	bool res = __assignableMatrix[l][r];
	return res;
}

bool IsTypesOperatable(_IN_ const IAtom & left, 
							  _IN_ const IAtom & right, 
							  _OUT_ IAtom * result_p) noexcept
{
	const auto lb = left.GetBaseType();
	const auto rb = right.GetBaseType();
	int l = TypeIndex(lb);
	int r = TypeIndex(rb);

	if(l == -1 || r == -1)
	{
		return false;
	}

	//Cannot operate on compound types, arrays.
	//Do not check for compound type here because the lookup matrix gives the answer.
	if(left.IsArrayType() || right.IsArrayType())
	{
		return false;
	}

	if(rb > lb)
	{
		*result_p = right;
	}
	else
	{
		*result_p = left;
	}

	return __operatableMatrix[l][r];
}
