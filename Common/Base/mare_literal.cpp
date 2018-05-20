#include "mare_literal.h"
#include <array>

Literal::Literal(_IN_POINTER_ const IAtom& typeInfo,
					  _IN_CAN_BE_NULL_ const void* data_p,
					  _IN_SIZE_ size_t dataSize,
					  _IN_OPT_ bool printString)
	: IAtom(typeInfo), _printString(printString)
{
	if (data_p)
	{
		_size = dataSize;
		_data = new uint8_t[dataSize];
		memcpy(_data, data_p, _size);
	}
	else
	{
		_data = nullptr;
	}
}

Literal::Literal(const Literal& other) :
	IAtom(other), _printString(other._printString)
{
	if (other._data)
	{
		this->_size = other._size;
		_data = new uint8_t[this->_size];
		memcpy(_data, other._data, _size);
	}
}

Literal::Literal(Literal&& m) :
	IAtom(m), _printString(m._printString)
{
	if(m._data)
	{
		this->_size = m._size;
		_data = new uint8_t[this->_size];
		memcpy(_data, m._data, _size);
		m._DeleteData();
	}
}

Literal::~Literal()
{
	_DeleteData();
	_size = 0;
}

size_t Literal::GetDataAsInt() const
{
	if(IsArrayType())
	{
		throw type_mismatch_exception();
	}

	switch(GetBaseType())
	{
		case INT8_TYPE:
		{
			return size_t(*reinterpret_cast<mare_int8_t*>(_data));
			break;
		}
		case INT16_TYPE:
		{
			return size_t(*reinterpret_cast<mare_int16_t*>(_data));
			break;
		}
		case INT32_TYPE:
		{
			return size_t(*reinterpret_cast<mare_int32_t*>(_data));
			break;
		}
		case INT64_TYPE:
		{
			return size_t(*reinterpret_cast<mare_int64_t*>(_data));
		}
		default:
		{
			throw type_mismatch_exception();
		}
	}
}

void Literal::_DeleteData()
{
	if (_data)
	{
		delete[] _data;
		_size = 0;
		_data = nullptr;
	}
}

void Literal::_Print(std::ostream& os) const
{
	if (_data)
	{
		const size_t arraySize = IsArrayType() ? GetArrayCount() : size_t(1);
		for (size_t i = 0; i < arraySize; i++)
		{
			if(_printString)
			{
				std::string s((char*)_data, _size);
				os << s;
			}
			else
			{
				switch(GetBaseType())
				{
					case INT8_TYPE:
					{
						os << *(reinterpret_cast<mare_int8_t*>(_data) + i);
						break;
					}
					case INT16_TYPE:
					{
						os << *(reinterpret_cast<mare_int16_t*>(_data) + i);
						break;
					}
					case INT64_TYPE:
					{
						os << *(reinterpret_cast<mare_int64_t*>(_data) + i);
						break;
					}
					case INT32_TYPE:
					{
						os << *(reinterpret_cast<mare_int32_t*>(_data) + i);
						break;
					}
					case FLOAT32_TYPE:
					{
						os << "float(" << *(reinterpret_cast<mare_float32_t*>(_data) + i) << ')';
						break;
					}
					case FLOAT64_TYPE:
					{
						os << "double(" << *(reinterpret_cast<mare_float64_t*>(_data) + i) << ')';
						break;
					}
					case CHARACTER_TYPE:
					{
						os << (char)*(reinterpret_cast<mare_char_t*>(_data) + i);
						break;
					}
					case STMT_TYPE:
					case COMPOUND_TYPE:
					case UNDEFINED_TYPE:
					case NULL_TYPE:
					default:
					{
						os << "Non-literal type";
						break;
					}
				}
			}
		}
	}

}
