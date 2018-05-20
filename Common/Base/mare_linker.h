#pragma once
#include <annotations.h>
#include "mare_linker_options.h"
#include "mare_compiler_options.h"

/*
 The linker output is a set of strings pointing to the OS's C++ compiler and linker and
 any command line arguments that must be passed to the compiler/linker.
 */
struct MARE_LINKER_OUTPUT
{
	std::list<std::string> SourceFilePaths;
	std::list<std::string> CPPLinkerOptions;
	std::list<std::string> CPPCompilerOptions;
	std::list<std::string> CPPIncludePaths;

	std::string CPPCompiler;
	std::string WorkingDirectory;
	std::string MARELibPath;
	std::string OutputFile;

	std::string DLLMainFile;

	sys_str CPPEnviSetupCommand;
};

/*
 Fills in the fields for a MARE_LINKER_OUTPUT using the given linker options and compiler options.
 "opts" are options for the MARE compiler to use when linking. These are set at the compiler
 command line or using preprocessor directives in the source code.
 "compOpts" are compiler options for the MARE compiler to use when compiling. These are set at the
 compiler command line.
 */
extern LIB_EXPORT void CreateLinkerOutput(_IN_ const COMPILER_OPTIONS& compOpts,
															  _OUT_ MARE_LINKER_OUTPUT* linkOutput);

extern LIB_EXPORT std::string GetMARELibPath(_IN_STR_ const std::string compilerDir);

/*
 Creates the CPP file for the MARE program.
 Returns the path to the CPP file.
 */
extern LIB_EXPORT void CreateMAREProgramCodeFile(_IN_STR_ const std::string& codeFilePath,
																 _IN_STR_ const std::string& mareProgHeaderFilePath);

extern LIB_EXPORT sys_str GetVSPath();

extern LIB_EXPORT sys_str GetVCBatPath(_IN_STR_ const sys_str& vsPath);

extern LIB_EXPORT std::string GetMAREProgramLIBMainFilePath(_IN_STR_ const std::string& compilerDir);
