#pragma once

#include <mare_linker.h>

extern void RunLinker(const COMPILER_OPTIONS& compOpts, const MARE_LINKER_OUTPUT& linker);

extern void CleanupCompileFiles(const COMPILER_OPTIONS& compOpts, 
										  const MARE_LINKER_OUTPUT& linker);