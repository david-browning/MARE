#pragma once

#include <annotations.h>

typedef uint16_t mare_type_t;

/*
 Data types in the MARE programming language.
*/
enum LIB_EXPORT MARE_TYPES : mare_type_t
{
	//Unknown type
	UNDEFINED_TYPE = 0x0000,

	//Signed 8 bit integer
	INT8_TYPE = 0x0001,
	//Unsigned 8 bit integer
	CHARACTER_TYPE = 0x0002,
	//Signed 16 bit integer
	INT16_TYPE = 0x0004,
	
	//Signed 32 bit integer
	INT32_TYPE = 0x0008,

	//32 bit floating point number
	FLOAT32_TYPE = 0x0010,
	
	//Signed 64 bit integer
	INT64_TYPE = 0x0020,

	//64 bit floating point number
	FLOAT64_TYPE = 0x0040,

	//Unsigned 32 bit floating point number
	CM_TYPE = 0x0080,
	//Unsigned 32 bit floating point number
	INCH_TYPE = 0x0100,
	//Unsigned 32 bit integer
	PIXEL_TYPE = 0x0200,

	COMPOUND_TYPE = 0x0400,
	NULL_TYPE = 0x0800,

	//These are type modifiers that can be applied to any other type by OR'ing 
	//them together.

	//Function type. 
	FUNCTION_TYPE = 0x1000,

	//The type is an array
	ARRAY_TYPE = 0x4000,

	//The type cannot be modified after its declared.
	CONSTANT_TYPE = 0x2000,

	STMT_TYPE = 0xFFFF,
};

static constexpr int MARE_NUM_TYPES = 13;

typedef uint8_t mare_uint8_t;
typedef uint16_t mare_uint16_t;
typedef uint32_t mare_uint32_t;
typedef uint64_t mare_uint64_t;

typedef int8_t mare_int8_t;
typedef int16_t mare_int16_t;
typedef int32_t mare_int32_t;
typedef int64_t mare_int64_t;

typedef float mare_float32_t;
typedef double mare_float64_t;

typedef mare_int32_t mare_int_t;
typedef mare_float32_t mare_float_t;

typedef mare_int8_t mare_bool_t;
typedef mare_int8_t mare_char_t;

typedef mare_float_t mare_inch_t;
typedef mare_float_t mare_cm_t;
typedef mare_int_t mare_pixel_T;

/*
 Returns the bitwise OR of the types.
 */
inline constexpr MARE_TYPES operator| (const MARE_TYPES a, const MARE_TYPES b) noexcept
{
	return MARE_TYPES((mare_type_t)a | (mare_type_t)b);
}

/*
 Returns the bitwise AND of the types.
 */
inline constexpr MARE_TYPES operator& (const MARE_TYPES a, const MARE_TYPES b) noexcept
{
	return MARE_TYPES((mare_type_t)a & (mare_type_t)b);
}

/*
 Returns the bitwise not of the type.
 */
inline constexpr MARE_TYPES operator~(const MARE_TYPES a) noexcept
{
	return MARE_TYPES(~mare_type_t(a));
}

/*
 Returns true if type a uses the same precision as type b.
 */
inline constexpr bool operator==(const MARE_TYPES a, const MARE_TYPES b)
{
	return (mare_type_t)a == (mare_type_t)b;
}

/*
 Returns true if type a uses more precision than type b.
 */
inline constexpr bool operator>(const MARE_TYPES a, const MARE_TYPES b)
{
	return (mare_type_t)a > (mare_type_t)b;
}

/*
 Returns true if type a uses less precision than type b.
 */
inline constexpr bool operator<(const MARE_TYPES a, const MARE_TYPES b)
{
	return (mare_type_t)a < (mare_type_t)b;
}

/*
 Returns the underlying type. The underlying type is the type without the 
 constant, array, or function flags set.
 */
inline constexpr MARE_TYPES BaseMareType(_IN_ENUM_ const MARE_TYPES t) noexcept
{
	return t & ~MARE_TYPES::ARRAY_TYPE & ~MARE_TYPES::FUNCTION_TYPE & ~MARE_TYPES::CONSTANT_TYPE;
}

/*
 Returns true if the type has the constant flag set.
 */
inline constexpr bool MareTypeIsConstant(_IN_ENUM_ const MARE_TYPES t) noexcept
{
	return (t & MARE_TYPES::CONSTANT_TYPE) == MARE_TYPES::CONSTANT_TYPE;
}

/*
 Returns true if the type has the function flag set.
 */
inline constexpr bool MareTypeIsFunction(_IN_ENUM_ const MARE_TYPES t) noexcept
{
	return (t & MARE_TYPES::FUNCTION_TYPE) == MARE_TYPES::FUNCTION_TYPE;
}

/*
 Returns true if the type has the array flag set.
 */
inline constexpr bool MareTypeIsArray(_IN_ENUM_ const MARE_TYPES t) noexcept
{
	return (t & MARE_TYPES::ARRAY_TYPE) == MARE_TYPES::ARRAY_TYPE;
}

/*
 Returns true if the type is null type.
 */
inline constexpr bool MareTypeIsNull(_IN_ENUM_ const MARE_TYPES t) noexcept
{
	return (t & MARE_TYPES::NULL_TYPE) == MARE_TYPES::NULL_TYPE;
}

/*
 Prints the type, including additional flags, of the type in english.
 Ex: A float type t will print "float".
 Ex: A constant float array t will print "const float array".
 */
extern LIB_EXPORT std::ostream& operator<<(std::ostream& os, MARE_TYPES t);
