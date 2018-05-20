#pragma once
#include <annotations.h>
#include "mare_linker_options.h"

/*
 This class wraps the LINKER_OPTIONS so the values can be set
 atomically. 
 */
class LIB_EXPORT AtomicLinkerOptions
{
public:
	/*
	 Constructor
	 Set "throwExcept" to true to throw exceptions if a linker option was already set.
	  If "throwExcept" is false and the set functions are called multiple times, the new
	  "set" value is not set.
	 */
	AtomicLinkerOptions(bool throwExcept);

	/*
	 Copy constructor.
	 */
	AtomicLinkerOptions(const AtomicLinkerOptions& c);

	/*
	 Move constructor. 
	 */
	AtomicLinkerOptions(AtomicLinkerOptions&& m);

	/*
	 Destructor.
	 */
	virtual ~AtomicLinkerOptions();

	/*
	 Sets the pixels per inch.
	 If this class, when constructed, was set to throw exceptions then calling this function after
	 the DPI was already set throws an exception. Otherwise, the new value is not set and silently 
	 ignored.
	 */
	void SetDPI(int dpi);

	inline const LINKER_OPTIONS* GetOptions() const
	{
		return &_l;
	}

	private:
	//The linker options this atomic class wraps.
	LINKER_OPTIONS _l;

	//If true, setting linker options multiple times throws an exception.
	bool _throwExcept;

	//Mutex to lock for atomic operations.
	std::mutex _m;
};