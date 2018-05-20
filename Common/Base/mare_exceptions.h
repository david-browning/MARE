#pragma once
#pragma warning(push)
#pragma warning(disable : 4275)
#include <annotations.h>
#include <exception>

/*
 Thrown when the type is not valid for the operation.
 Ex: Trying to count how many elements are in an array when the type is not an array type.
 */
class LIB_EXPORT invalid_type_exception : public std::exception
{
 public:
	invalid_type_exception() : std::exception("The type is not valid.")
	{
	}
};

/*
 Thrown when the compiler encounters text that is not an operator, known constant, preprocessor 
 directive, or keyword and the text was not declared as a symbol.
 */
class LIB_EXPORT symbol_not_defined_exception : public std::exception
{
 public:
	symbol_not_defined_exception(const std::string &symName) : 
		std::exception(std::string(symName + " was not declared.").c_str())
	{
	}
};

/*
 Thrown when trying to declare a symbol when there is another symbol with the same name in the 
 same or larger scope.
 */
class LIB_EXPORT symbol_already_declared_exception : public std::exception
{
 public:
	symbol_already_declared_exception(const std::string &symName) : 
		std::exception(std::string(symName + " was already declared.").c_str())
	{
	}
};

/*
 Thrown when trying to declare a symbol constant in a context that does not allow it.
 Ex: You cannot assign an expression to a constant symbol.
 */
class LIB_EXPORT constant_not_allowed_exception : public std::exception
{
 public:
	constant_not_allowed_exception() : std::exception("Constant not allowed here.")
	{
	}
};

/*
 Thrown when indexing an array where the index is less than 0 or greater than the 
 number of items in the array - 1.
 */
class LIB_EXPORT index_out_of_bounds_exception : public std::exception
{
 public:
	index_out_of_bounds_exception() : std::exception("Index out of bounds.")
	{
	}
};

/*
 Thrown when trying to assign or operator on two types that are not compatible.
 */
class LIB_EXPORT type_mismatch_exception : public std::exception
{
 public:
	type_mismatch_exception() : std::exception("The types are not compatible.")
	{
	}
};

//TODO: delete this?
class LIB_EXPORT too_many_calls_exception : public std::exception
{
 public:
	virtual const char *what() const throw()
	{
		return "The function was called too many times.";
	}
};

/*
 Thrown when a string is not in the expected format. Usually this will occur when the string
 should be a filepath, or an enumeration and the string is not a member of the enumeration.
 */
class LIB_EXPORT bad_string_format_exception : public std::exception
{
 public:
	bad_string_format_exception() : std::exception("The string is not formatted correctly.")
	{
	}
};

/*
 Thrown when trying to treat a symbol as a function, when it is not a function.
 */
class LIB_EXPORT not_function_type_exception : public std::exception
{
 public:
	not_function_type_exception() : std::exception("The type is not a function.")
	{
	}
};

/*
 Thrown when a required dependency, such as a referenced source file, is not found.
 This usually means the source file was not found, or not added to a dependency graph.
 */
class LIB_EXPORT dependency_not_found_exception : public std::exception
{
 public:
	dependency_not_found_exception(const std::string dep) : std::exception(std::string("Dependency" + dep + " was not found.").c_str())
	{
	}
};

/*
 Thrown when calling a function or declaring an array with the wrong number of arguments.
 */
class LIB_EXPORT wrong_argument_count_exception : public std::exception
{
 public:
	wrong_argument_count_exception() : std::exception("Incorrect number of arguments.")
	{
	}
};

/*
 Thrown when a parameter was set for a second time when it only should be set once.
 */
class LIB_EXPORT param_already_set : public std::exception
{
 public:
	param_already_set() : std::exception("The parameter was already set.")
	{
	}
};

/*
 TODO: Delete this?
 */
class LIB_EXPORT envi_var_not_found_exception : public std::exception
{
 public:
	envi_var_not_found_exception() : std::exception("Environment variable not found.")
	{
	}
};

/*
 Throw when a required linker option is not set.
 */
class LIB_EXPORT linker_not_set_exception : public std::exception
{
 public:
	linker_not_set_exception(const std::string &opt) : std::exception(std::string("The linker option " + opt + " is missing.").c_str())
	{
	}
};

/*
 Thrown when a Windows registry item, or Linux configuration, is not found.
 */
class LIB_EXPORT registry_not_found_exception : public std::exception
{
 public:
	registry_not_found_exception() : std::exception("Registry value not found.")
	{
	}
};

#pragma warning(pop)