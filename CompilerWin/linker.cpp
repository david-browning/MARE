#include "linker.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <experimental/filesystem>
#include <filesystem>
using namespace std::experimental::filesystem;

#else

#endif

void RunLinker(const COMPILER_OPTIONS& compOpts, const MARE_LINKER_OUTPUT& linker)
{
	//Construct the commands used to invoke the CPP compiler
	sys_str setupEnviCommand = L" /Q /k \"" + linker.CPPEnviSetupCommand + L"\"\n";
	std::string cdCommand = "cd \"" + linker.WorkingDirectory + "\"\n";

	std::stringstream vcCompilerCommandStream;
	//Write the compiler program to the stream.
	vcCompilerCommandStream << linker.CPPCompiler << " ";

	//Write each of the source files to the stream.
	for(auto file : linker.SourceFilePaths)
	{
		//Put the file in double quotes.
		vcCompilerCommandStream << '\"' << file << "\" ";
	}

	vcCompilerCommandStream << '\"' << linker.DLLMainFile << "\" ";

	//Write the compiler options to the stream.
	for(auto opt : linker.CPPCompilerOptions)
	{
		vcCompilerCommandStream << opt << " ";
	}

	//Write the include directories to the stream.
	for(auto incDir : linker.CPPIncludePaths)
	{
		//Put the directories in double quotes.
		vcCompilerCommandStream << "/I\"" + incDir + "\" ";
	}

   vcCompilerCommandStream << "/I\"C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.16299.0\\ucrt\" ";

	//Now write the linker commands to the stream.
	vcCompilerCommandStream << "/link ";

	vcCompilerCommandStream << "/OUT:\"" << linker.OutputFile << "\" " <<
		"/LIBPATH:\"" << compOpts.CompilerDir << "\" " <<
		"\"" << linker.MARELibPath << "\" ";

	for(auto opt : linker.CPPLinkerOptions)
	{
		vcCompilerCommandStream << opt << " ";
	}

	vcCompilerCommandStream << "\n";

	std::string vcCompilerCommand = vcCompilerCommandStream.str();
	std::string exitCommand = "exit\n";

	if(compOpts.IsDebugMode)
	{
		std::clog << "\n------------------Compiler Commands------------------\n";
		std::clog << setupEnviCommand << std::endl;
		std::clog << cdCommand << std::endl;
		std::clog << vcCompilerCommand << std::endl << std::endl;
	}


	//Create a pipe that this program can use to write text to the VC compiler program.

	//Setup security attributes for the pipe.
	SECURITY_ATTRIBUTES pipeSecAttrs;
	pipeSecAttrs.nLength = sizeof(pipeSecAttrs);
	pipeSecAttrs.bInheritHandle = TRUE;
	pipeSecAttrs.lpSecurityDescriptor = nullptr;

	//Handles for the VC compiler.
	HANDLE linkerInRd = nullptr;
	HANDLE linkerInWr = nullptr;
	HANDLE suppressedFile = nullptr;

	//Create the pipe.
	if(!CreatePipe(&linkerInRd, &linkerInWr, &pipeSecAttrs, 0))
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}

	//This program will spawn the VC compiler.
	//Allow the VC compiler to inherit handles from this program.
	if(!SetHandleInformation(linkerInWr, HANDLE_FLAG_INHERIT, 0))
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}

	STARTUPINFO startupInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_PREVENTPINNING;
	startupInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	startupInfo.hStdInput = linkerInRd;

	//If not debug mode:
	if(!(compOpts.IsDebugMode))
	{
		//Create a null file to redirect the CPP compiler's output to.
		//If in debug mode, this gets skipped and and the CPP compiler writes to std out.
		CREATEFILE2_EXTENDED_PARAMETERS cf2Params;
		cf2Params.dwSize = sizeof(cf2Params);
		cf2Params.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
		cf2Params.dwFileFlags = FILE_FLAG_DELETE_ON_CLOSE;
		cf2Params.dwSecurityQosFlags = SECURITY_ANONYMOUS;
		cf2Params.lpSecurityAttributes = &pipeSecAttrs;
		cf2Params.hTemplateFile = nullptr;

		suppressedFile = CreateFile2(L"null.txt", GENERIC_WRITE, FILE_SHARE_WRITE, CREATE_ALWAYS, &cf2Params);
		if(suppressedFile == INVALID_HANDLE_VALUE)
		{
			throw std::system_error(std::error_code(GetLastError(), std::system_category()));
		}

		startupInfo.hStdOutput = suppressedFile;
	}

	PROCESS_INFORMATION processInfo;
	memset(&processInfo, 0, sizeof(processInfo));

	//Get the path to CMD. This is the program to launch.
	wchar_t cmd[MAX_PATH];
	size_t nSize = _countof(cmd);
	_wgetenv_s(&nSize, cmd, TEXT("COMSPEC"));

	sys_str workingDirectoryW(linker.WorkingDirectory.begin(), linker.WorkingDirectory.end());

	//Launch CMD and call the setup environment command.
	if(!CreateProcess(cmd,
							const_cast<wchar_t*>(setupEnviCommand.c_str()),
							nullptr,
							nullptr,
							TRUE,
							0,
							nullptr,
							workingDirectoryW.c_str(),
							&startupInfo,
							&processInfo))
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}

	DWORD bytesWritten = 0;

	//Write the command to change directory to where the MARE C++ files are.
	DWORD bytesToWrite = cdCommand.size();
	WriteFile(linkerInWr, cdCommand.c_str(), bytesToWrite, &bytesWritten, nullptr);

	//Write the command to compile the MARE C++ files using the VC compiler.
	bytesToWrite = vcCompilerCommand.size();
	WriteFile(linkerInWr, vcCompilerCommand.c_str(), bytesToWrite, &bytesWritten, nullptr);

	//Exit the VC compiler process.
	bytesToWrite = exitCommand.size();
	WriteFile(linkerInWr, exitCommand.c_str(), bytesToWrite, &bytesWritten, nullptr);

	//Wait for the VC compiler process to terminate.
	WaitForSingleObject(processInfo.hProcess, INFINITE);

	//Check that the VC compiler terminated properly.
	DWORD cmdExitStatus = 1;
	if(!GetExitCodeProcess(processInfo.hProcess, &cmdExitStatus))
	{
		throw std::system_error(std::error_code(GetLastError(), std::system_category()));
	}

	if(cmdExitStatus != 0)
	{
		throw std::runtime_error("The VC compiler did not exit correctly.");
	}

	//Close all the handles.
	if(suppressedFile)
	{
		CloseHandle(suppressedFile);
	}
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	CloseHandle(linkerInRd);
	CloseHandle(linkerInWr);
}

void CleanupCompileFiles(const COMPILER_OPTIONS& compOpts,
								 const MARE_LINKER_OUTPUT& linker)
{
	for(auto sourceFile : linker.SourceFilePaths)
	{
		sys_str sourceFileW(sourceFile.begin(), sourceFile.end());
		DeleteFile(sourceFileW.c_str());
	}

	const auto compilerFile = compOpts.OutFile();
	sys_str compilerFileW(compilerFile.begin(), compilerFile.end());
	DeleteFile(compilerFileW.c_str());

	sys_str compilerFileWOBJ = compilerFileW + TEXT(".obj");
	sys_str compilerFileWLIB = compilerFileW + TEXT(".lib");
	sys_str compilerFileWEXP = compilerFileW + TEXT(".exp");

	DeleteFile(compilerFileWOBJ.c_str());
	DeleteFile(compilerFileWLIB.c_str());
	DeleteFile(compilerFileWEXP.c_str());

	auto dllFileOBJ = compOpts.OutFileDir + "\\mare_dllmain.obj";
	sys_str dllFileOBJW(dllFileOBJ.begin(), dllFileOBJ.end());
	DeleteFile(dllFileOBJW.c_str());
}
