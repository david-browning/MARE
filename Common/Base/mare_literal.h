#pragma once
#include <annotations.h>
#include "mare_iatom.h"
#include "mare_compiler_consts.h"

class LIB_EXPORT Literal : public IAtom
{
	public:
	/*
	 Constructs a new Literal.
	  typeInfo the the type of the literal.
	 "data_p" is a pointer to the literal's data. The contents the pointer points to are copied into the
	 class so the data can go out of scope.
	 dataCount is number of bytes data_p points to.
	 Set "printString" to true if the data is a char* and should be printed as a string when using
	 the << operator on this.
	 */
	Literal(_IN_POINTER_ const IAtom& typeInfo,
			  _IN_CAN_BE_NULL_ const void* data_p = nullptr,
			  _IN_SIZE_ size_t dataSize = 0, 
			  _IN_OPT_ bool printString = false);

	/*
	 Copy constructor.
	 */
	Literal(const Literal& other);

	/*
	 Move constructor.
	 */
	Literal(Literal&& m);

	/*
	 Destructor
	 */
	virtual ~Literal();

	/*
	 Throws a type mismatch exception if the data is not an int.
	 */
	size_t GetDataAsInt() const;

	/*
	 Adds data to the literal. If literal already has data, it is free'd. 
	 If "data_p" points to an array, set "arrayCount" to the number of elements in the array.
	 Only set "arrayCount" if "data_p" points to an array. "arrayCount" is the number of elements
	 pointed to by "data_p". It is not the number of bytes in the array.
	 */
	template<typename T>
	void AddData(_IN_POINTER_ const T* data_p, _IN_SIZE_ const size_t arrayCount = 1)
	{
		_DeleteData();
		constexpr size_t tSize = sizeof(T);
		_data = new T[tSize / arrayCount];
		memcpy(_data, data_p, arrayCount * tSize);
	}

	/*
	 Returns the number of bytes large the literal's data is.
	 Ex: If the literal is a 64bit integer, this returns 8.
	 */
	inline size_t GetDataSize() const noexcept
	{
		return _size;
	}

	/*
	 Returns a constant pointer to the literal's data.
	 Use the template to return a pointer to any type.
	 */
	template<typename T>
	inline const T* GetDataPointer() const noexcept
	{
		return (T*)_data;
	}

	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const Literal& lit)
	{
		lit._Print(os);
		return os;
	}

	protected:

	/*
	 Frees the memory pointed to by "_data".
	 */
	void _DeleteData();

	virtual void _Print(std::ostream& os) const;

	/*
	 Points to the literal's data.
	 */
	void* _data = nullptr;

	/*
	 Number of bytes "_data" points to.
	 */
	size_t _size = 0;

	/*
	 If true, "_data" is interpreted as a char* and printed as a string when using the <<
	 operator on this.
	 */
	bool _printString;
};

/*
 Zero as a 64-bit MARE integer.
 */
static constexpr mare_int64_t UINT64_ZERO(0);

/*
 The literal value zero.
 */
static const Literal ZERO_LITERAL(INT_TYPE_INFO_C, &UINT64_ZERO, sizeof(UINT64_ZERO));

/*
 Pi, stored in a literal.
 */
static const Literal PI_LITERAL(FLOAT64_TYPE_INFO_C, &PI_D, sizeof(PI_D));

/*
 False, stored in a literal.
 */
static const Literal FALSE_LITERAL(INT8_TYPE_INFO, &MARE_FALSE, sizeof(MARE_FALSE));

/*
 True, stored in a literal.
 */
static const Literal TRUE_LITERAL(INT8_TYPE_INFO, &MARE_TRUE, sizeof(MARE_TRUE));

/*
 Number of pixels in a centimeter, stored in a literal.
 */
static const Literal PIXELS_PER_CM_LITERAL(FLOAT32_TYPE_INFO, &PIXELS_PER_CM, sizeof(PIXELS_PER_CM));

/*
 Number of pixels in an inch, stored in a literal.
 */
static const Literal PIXELS_PER_INCH_LITERAL(FLOAT32_TYPE_INFO, &PIXELS_PER_INCH, sizeof(PIXELS_PER_INCH));

static const Literal* GetPageWidthLiteral()
{
	auto w = GetMAREPageWidth();
	return new Literal(INT_TYPE_INFO_C, &w, sizeof(w));
}

static const Literal* GetPageHeightLiteral()
{
	auto h = GetMAREPageHeight();
	return new Literal(INT_TYPE_INFO_C, &h, sizeof(h));
}