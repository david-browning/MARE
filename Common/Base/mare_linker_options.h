#pragma once 
#include <annotations.h>

extern class AtomicLinkerOptions __alinkeropts__;

/*
 Stores options that apply to a MARE program. 
 */
struct LIB_EXPORT LINKER_OPTIONS
{
	/*
	 Default constructor.
	 */
	LINKER_OPTIONS();

	/*
	 Constructs this from an AtomicLinkerOptions class.
	 */
	LINKER_OPTIONS(const AtomicLinkerOptions& a);

	/*
	 Copy constructor.
	 */
	LINKER_OPTIONS(const LINKER_OPTIONS& c);

	/*
	 Move constructor.
	 */
	LINKER_OPTIONS(LINKER_OPTIONS&& m);

	/*
	 Pixels per inch.
	 */
	int DPI;
};
