#pragma once
#include <annotations.h>

/*
 Contains information set by the command line to pass to the compiler.
 */
struct COMPILER_OPTIONS
{
	bool IsDebugMode;
	bool IsVerbose;
	bool IsSaveStreamFile;
	bool ShowMetrics;
	bool SaveCompileFiles;

	//Path to the compiler executable.
	//It does not contain the trailing backslash.
	std::string CompilerDir;

	std::string OutFileName;

	//Directory where the output will be stored.
	//It does not contain the trailing backslash.
	std::string OutFileDir;

	//Gets the full path to the output file.
	std::string OutFile() const
	{
		return OutFileDir + '\\' + OutFileName;
	}

	//List of files to compile.
	std::vector<std::string> SourceFiles;

	//Constructs a new instance of this. All optional parameters are set to false 
	//and the list of source files is empty.
	COMPILER_OPTIONS(const std::string& executablePath)
	{
		IsDebugMode = false;
		ShowMetrics = false;
		IsSaveStreamFile = false;
		IsVerbose = false;
		SaveCompileFiles = false;
		//OutFileName = "mareprogram";
		OutFileDir = ".\\";

		auto compilerLastSlash = executablePath.find_last_of('\\', executablePath.length());
		CompilerDir = executablePath.substr(0, compilerLastSlash);
	}
};