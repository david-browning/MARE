#include "mare_compiler_functions.h"
#include "mare_exceptions.h"

LIB_EXPORT std::string TrimQuotations(_IN_STR_ const std::string& str)
{
	std::string ret(str);
	ret.erase(std::remove(ret.begin(), ret.end(), '\"'), ret.end());
	return ret;
}

char* TrimQuotations(_IN_STR_ const char* str)
{
	const size_t numChars = strlen(str);
	if (numChars < 2)
	{
		throw bad_string_format_exception();
	}

	//subtract 2 for the quotations but add 1 for the terminator.
	char* ret = new char[numChars - 1];

	uint8_t quoteCount = 0;
	int i = 0;
	while (*str)
	{
		if (*str == '"')
		{
			quoteCount++;
			//Do not copy the quote to ret.
		}
		else
		{
			ret[i] = *str;
			i++;
		}

		str++;
	}

	//Check to make sure there are 2 quotes.
	if (quoteCount != 2)
	{
		delete[] ret;
		throw bad_string_format_exception();
	}

	ret[i] = '\0';
	return ret;
}
