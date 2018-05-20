#include "mare_linker_atomic_options.h"
#include "mare_exceptions.h"

AtomicLinkerOptions::AtomicLinkerOptions(bool throwExcept) :
	_throwExcept(throwExcept)
{
}

AtomicLinkerOptions::AtomicLinkerOptions(const AtomicLinkerOptions& c) :
	_l(c._l), _throwExcept(c._throwExcept)
{

}

AtomicLinkerOptions::AtomicLinkerOptions(AtomicLinkerOptions&& m) :
	_l(std::move(m._l)), _throwExcept(m._throwExcept)
{

}

AtomicLinkerOptions::~AtomicLinkerOptions()
{
}

void AtomicLinkerOptions::SetDPI(int dpi)
{
	std::lock_guard<std::mutex> lock(_m);
	if(_l.DPI != 0)
	{
		if(_throwExcept)
		{
			throw param_already_set();
		}

		return;
	}

	_l.DPI = dpi;
}
