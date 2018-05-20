#include "mare_linker_options.h"
#include "mare_linker_atomic_options.h"
#include "mare_atom_types.h"
#include "mare_compiler_consts.h"

LINKER_OPTIONS::LINKER_OPTIONS() :
	DPI(0)
{
}

LINKER_OPTIONS::LINKER_OPTIONS(const AtomicLinkerOptions& a) :
	DPI(a.GetOptions()->DPI)
{
}

LINKER_OPTIONS::LINKER_OPTIONS(const LINKER_OPTIONS& c) :
	DPI(c.DPI)
{
}

LINKER_OPTIONS::LINKER_OPTIONS(LINKER_OPTIONS&& m) :
	DPI(m.DPI)
{
}
