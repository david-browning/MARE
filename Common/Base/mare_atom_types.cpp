#include "mare_atom_types.h"

std::ostream& operator<<(std::ostream& os, MARE_TYPES t)
{
	if(MareTypeIsConstant(t))
	{
		os << "const ";
	}

	switch(BaseMareType(t))
	{
		case NULL_TYPE:
		{
			os << "null";
			break;
		}
		case INT8_TYPE:
		{
			os << "int8";
			break;
		}
		case INT16_TYPE:
		{
			os << "int16";
			break;
		}
		case INT32_TYPE:
		{
			os << "int32";
			break;
		}
		case INT64_TYPE:
		{
			os << "int64";
			break;
		}
		case FLOAT32_TYPE:
		{
			os << "float32";
			break;
		}
		case FLOAT64_TYPE:
		{
			os << "float64";
			break;
		}
		case CHARACTER_TYPE:
		{
			os << "character";
			break;
		}
		default:
		{
			return os << "unknown";
		}
	}

	if(MareTypeIsArray(t))
	{
		os << " array";
	}

	if(MareTypeIsFunction(t))
	{
		os << " function";
	}

	return os;
}

