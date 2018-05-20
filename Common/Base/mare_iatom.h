#pragma once

#include <annotations.h>
#include "mare_exceptions.h"
#include "mare_atom_types.h"

/*
 MARE symbols, operators, and expressions are typed. This stores the type info for any of 
 these elements. These elements inherit this class.
 Statement are typed, but are of type STATEMENT_TYPE.
 */
class LIB_EXPORT IAtom
{
	public:
	/*
	 Constructor.
	 "type" is the type of the atom. type can be any ration combination of the MARE_TYPES
	 enumeration.
	 An irrational combination would be declaring a type with the FLOAT32 and INT64 flags set.
	 */
	IAtom(_IN_ENUM_ MARE_TYPES type);

	/*
	 Copy constructor.
	 */
	IAtom(const IAtom& other);

	/*
	 Move contructor.
	 */
	IAtom(IAtom&& m);

	/*
	 Destructor.
	 */
	virtual ~IAtom();

	/*
	 Copies the type info from "typeInfo" into this.
	 */
	void UpdateTypeInfo(const IAtom& typeInfo);

	/*
	 Returns true if this is a function type.
	 */
	inline bool IsFunctionType() const noexcept
	{
		return MareTypeIsFunction(_type);
	}

	/*
	 Returns true if this is an array type.
	 */
	inline bool IsArrayType() const noexcept
	{
		return MareTypeIsArray(_type);
	}

	/*
	 TODO: Hide this?
	 Returns true if the type is an array type and the array count is zero.
	 This is used when a declaring function with an array type argument, but the size 
	 of the array is not known at compile time.
	 */
	inline bool IsTemplateType() const noexcept
	{
		return IsArrayType() && GetArrayCount() == 0;
	}

	/*
	 Returns true if the type is as compound type.
	 */
	inline bool IsCompoundType() const noexcept
	{
		return (_type & MARE_TYPES::COMPOUND_TYPE) == MARE_TYPES::COMPOUND_TYPE;
	}

	/*
	 Returns true if the type is constant.
	 */
	inline bool IsConstantType() const noexcept
	{
		return MareTypeIsConstant(_type);
	}

	/*
	 Returns true if the type is the null type.
	 */
	inline bool IsNullType() const noexcept
	{
		return MareTypeIsNull(_type);
	}

	/*
	 Returns the base type of the atom. The base type is the type without the constant or array.
	*/
	inline MARE_TYPES GetBaseType() const noexcept
	{
		return BaseMareType(_type);
	}

	/*
	 Returns this' MARE_TYPE.
	 */
	inline MARE_TYPES GetType() const noexcept
	{
		return _type;
	}

	/*
	 Appends a type to the list of arguments for this type.
	 If the type is not a function type or compound type, this throws invalid_type_exception.
	 */
	void AppendArgument(_IN_ const IAtom& type);

	/*
	 Modifies the type info so the type is an array with "arrayCount" number of elements.
	 */
	void MakeArray(_IN_SIZE_ size_t arrayCount) noexcept;

	/*
	 Modifies the type info so the type is a function type.
	 After changing a type to a function, the number of function arguments is zero.
	 Use "AppendArgument" to add arguments to the function.
	 */
	void MakeFunction() noexcept
	{
		_type = _type | MARE_TYPES::FUNCTION_TYPE;
	}

	/*
	 Modifies the type info so the type is constant.
	 */
	void MakeConstant() noexcept
	{
		_type = _type | MARE_TYPES::CONSTANT_TYPE;
	}

	/*
	 Returns the number of elements in this type if its an array type.
	 If this is not an array type, this thrown invalid_type_exception.
	 */
	size_t GetArrayCount() const;

	/*
	 Return the number of arguments in this type if its a compound or function type.
	 If this is not a function or compound type, this throws invalid_type_exception.
	 */
	size_t GetArgumentCount() const;

	/*
	 Returns an iterator to the first argument in this type.
	 If this type is not a function type or compound type, this throws 
	 invalid_type_exceptions.
	 */
	inline auto ArgBegin() const
	{
		if (!IsFunctionType() && !IsCompoundType())
		{
			throw invalid_type_exception();
		}

		return _args.cbegin();
	}

	/*
	 Returns an iterator to the last argument in this type.
	 If this type is not a function type or compound type, this throws
	 invalid_type_exceptions.
	 */
	inline auto ArgEnd() const
	{
		if (!IsFunctionType() && !IsCompoundType())
		{
			throw invalid_type_exception();
		}

		return _args.cend();
	}
	
	/*
	 Returns true if the right-hand type is the same type, and has the same arguments, as the 
	 left-hand type.
	 */
	friend LIB_EXPORT bool operator==(const IAtom& l, const IAtom& r)
	{
		return (l._type == r._type) &&
			(l._args == r._args) && (l._arrayCount == r._arrayCount);
	}

	/*
	 Copies the type info from the right-hand value into this.
	 */
	void operator=(const IAtom& r)
	{
		UpdateTypeInfo(r);
	}

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const IAtom& atom)
	{
		atom._Print(os);
		return os;
	}

	private:
	MARE_TYPES _type;
	std::list<IAtom> _args;
	size_t _arrayCount;

	virtual void _Print(std::ostream& os) const;
};


static const IAtom NO_TYPE_INFO = IAtom(MARE_TYPES::UNDEFINED_TYPE);
static const IAtom INT8_TYPE_INFO = IAtom(MARE_TYPES::INT8_TYPE);
static const IAtom NULL_TYPE_INFO = IAtom(MARE_TYPES::NULL_TYPE);
static const IAtom CHAR_TYPE_INFO = IAtom(MARE_TYPES::CHARACTER_TYPE);
static const IAtom INT_TYPE_INFO = IAtom(MARE_TYPES::INT32_TYPE);
static const IAtom INT64_TYPE_INFO = IAtom(MARE_TYPES::INT64_TYPE);
static const IAtom FLOAT32_TYPE_INFO = IAtom(MARE_TYPES::FLOAT32_TYPE);
static const IAtom FLOAT64_TYPE_INFO = IAtom(MARE_TYPES::FLOAT64_TYPE);
static const IAtom COMPOUND_TYPE_INFO = IAtom(MARE_TYPES::COMPOUND_TYPE);

static const IAtom FLOAT32_TYPE_INFO_C = IAtom(MARE_TYPES::FLOAT32_TYPE | MARE_TYPES::CONSTANT_TYPE);
static const IAtom FLOAT64_TYPE_INFO_C = IAtom(MARE_TYPES::FLOAT64_TYPE | MARE_TYPES::CONSTANT_TYPE);

static const IAtom INT_TYPE_INFO_C = IAtom(MARE_TYPES::INT32_TYPE | MARE_TYPES::CONSTANT_TYPE);
static const IAtom INT64_TYPE_INFO_C = IAtom(MARE_TYPES::INT64_TYPE | MARE_TYPES::CONSTANT_TYPE);
static const IAtom CHAR_TYPE_INFO_C = IAtom(MARE_TYPES::CHARACTER_TYPE | MARE_TYPES::CONSTANT_TYPE);
static const IAtom STRING_TYPE_INFO_C = IAtom(MARE_TYPES::CHARACTER_TYPE | MARE_TYPES::ARRAY_TYPE | MARE_TYPES::CONSTANT_TYPE);
