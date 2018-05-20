#include "mare_linker.h"
#include "mare_exceptions.h"
#include "mare_compiler_consts.h"

#ifdef _WINDOWS

#define EXCEPTIONS_HANDLING "/EHsc"
#define LIBRARY_FLAGS "/DLL /LD"
#define WARN_LEVEL "/W3"
#define APP_SUPPORT "" //Set to ZW for Windows Apps
#define OPTIMIZATION_LEVEL "/O2 /OPT:REF"
#define SUPRESS_BANNER "/NOLOGO"
#define SUBSYSTEM_VERSION "/SUBSYSTEM:WINDOWS"
#define TARGET_ARCH "/MACHINE:X64"
#define POOL_STRINGS "/GF"
#define CALLING_CONVENTION "/Gd"
#define MULTITHREADED_LIBRARY "/MD"
#define CPP_STANDARD "/std:c++17"
#define LINKER_FLAGS "/NXCOMPAT /DYNAMICBASE"
#define ADDITIONAL_FLAGS "/MP"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <ShlObj.h>
#include <Shlwapi.h>
#include <experimental/filesystem>
#include <filesystem>
using namespace std::experimental::filesystem;

#else

#endif

static const std::list<std::string> CPP_COMPILER_OPTIONS = 
{
	EXCEPTIONS_HANDLING,
	LIBRARY_FLAGS,
	WARN_LEVEL,
	APP_SUPPORT,
	POOL_STRINGS,
	CALLING_CONVENTION,
	MULTITHREADED_LIBRARY,
	CPP_STANDARD,
	ADDITIONAL_FLAGS,
};

static const std::list<std::string> CPP_LINKER_OPTIONS =
{
	LINKER_FLAGS,
	SUBSYSTEM_VERSION,
	TARGET_ARCH,
	SUPRESS_BANNER,
	//OPTIMIZATION_LEVEL,
};

void CreateLinkerOutput(_IN_ const COMPILER_OPTIONS& compOpts,
								_OUT_ MARE_LINKER_OUTPUT* linkOutput)
{
	//Get the paths to files used with the CPP compiler.
	auto codeFilePath = compOpts.OutFile() + ".cpp";

	//Create the CPP file.
	CreateMAREProgramCodeFile(codeFilePath, compOpts.OutFileName);

	//Get CPP compiler paths.
	auto vsPath = GetVSPath();
	auto vcBATPath = GetVCBatPath(vsPath);

	linkOutput->CPPCompilerOptions = CPP_COMPILER_OPTIONS;
	linkOutput->CPPLinkerOptions = CPP_LINKER_OPTIONS;
	linkOutput->CPPIncludePaths = std::list<std::string>
	{
		compOpts.OutFileDir,
		compOpts.CompilerDir + "\\Include",
	};

	linkOutput->SourceFilePaths = std::list<std::string>
	{
		codeFilePath,
	};

	linkOutput->DLLMainFile = GetMAREProgramLIBMainFilePath(compOpts.CompilerDir),


	linkOutput->CPPCompiler = "cl.exe";
	linkOutput->WorkingDirectory = compOpts.OutFileDir;
	linkOutput->MARELibPath = GetMARELibPath(compOpts.CompilerDir);
	linkOutput->OutputFile = compOpts.OutFileName + ".dll";
	linkOutput->CPPEnviSetupCommand = vcBATPath;
}

std::string GetMARELibPath(_IN_STR_ const std::string compilerDir)
{
	return "marecommon.lib";
}

void CreateMAREProgramCodeFile(_IN_STR_ const std::string& codeFilePath,
										 _IN_STR_ const std::string& mareProgHeaderFilePath)
{
	std::fstream codeFileStream(codeFilePath, std::iostream::trunc | std::ios::out);
	codeFileStream << "#include \"" << mareProgHeaderFilePath << "\"\n\n";
	codeFileStream << "void " << LIB_EXPORT_STR << ' ' << MARE_PROGRAM_ENTRY << "(MareRT& runtime)\n";
	codeFileStream << "{\n";
	codeFileStream << '\t' << MARE_PROG_CLASS_NAME << " prog(runtime);\n";
	codeFileStream << "\tprog.Run();\n";
	codeFileStream << "}\n\n";
}

sys_str GetVSPath()
{
	//Search Program Files for Microsoft Visual Studio
	//Search Program Files (x86) for Microsoft Visual Studio

	static const sys_str vsFolder = TEXT("Microsoft Visual Studio");

	//Get the Program Files folder.
	sys_str programFilesDir = TEXT("C:\\Program Files (x86)");

	//If Visual Studio is not in Program Files, get the Program Files (x86) folder.


	sys_str vsPath = programFilesDir + TEXT('\\') + vsFolder;


	//Get the latest VS version.
	for(auto& p : directory_iterator(vsPath))
	{
		if(p.path().filename() <= L"9" && p.path() >= vsPath)
		{
			vsPath = p.path();
		}
	}

	//Get the VS Edition folder.
	for(auto& p : directory_iterator(vsPath))
	{
		if(p.path() >= vsPath)
		{
			vsPath = p.path();
		}
	}

	return vsPath;
}

sys_str GetVCBatPath(_IN_STR_ const sys_str& vsPath)
{
	return vsPath + TEXT("\\VC\\Auxiliary\\Build\\vcvars64.bat");
}

std::string GetMAREProgramLIBMainFilePath(_IN_STR_ const std::string& compilerDir)
{
	return compilerDir + "\\Include\\mare_dllmain.cpp";
}
