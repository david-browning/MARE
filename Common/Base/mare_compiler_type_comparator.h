#pragma once

#include <annotations.h>
#include "mare_iatom.h"
#include "mare_compiler_functions.h"
#include <type_traits>

/*
 Returns true if the right type can be assigned to the left type.

 Set declaringConstVar to true if the statement where the assignment occurs is a 
 declaration statement and the right is being assigned to a constant left type. 
 */
extern LIB_EXPORT bool IsTypesAssignable(_IN_ const IAtom& left,
										 _IN_ const IAtom& right, 
										 _IN_OPT_ bool declaringConstVar = false) noexcept;

/*
 Returns true if each element in the right array can be assigned to the corresponding element
 in the left array.
 */
extern LIB_EXPORT bool IsArrayIndexTypeAssignable(_IN_ const IAtom& left, 
												  _IN_ const IAtom& right) noexcept;

/*
 Returns true if a binary operator can be applied to the left and right types.

 result_p is a pointer to an IAtom that will recieve the resultant type of the operation.
 Ex: Adding a float and an integer will have a result of float.
 */
extern LIB_EXPORT bool IsTypesOperatable(_IN_ const IAtom& left,
										 _IN_ const IAtom& right,
										 _OUT_ IAtom* result_p) noexcept;
