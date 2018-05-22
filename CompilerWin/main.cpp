#include <annotations.h>
#include <cmdarg_parser.h>
#include <direct.h>
#include <mare_dependency_graph.h>
#include <mare_compiler_functions.h>
#include <mare_linker_options.h>
#include <mare_linker.h>
#include <mare_linker_atomic_options.h>
#include <mare_envi.h>
#include <experimental/filesystem>
#include <filesystem>
using namespace std::experimental::filesystem;

#include "SourceScanner.h"
#include "PreprocessorScanner.h"
#include "PreprocessorParser.h"
#include "SourceParser.h"
#include "linker.h"

static constexpr int E_NO_INPUT = 1;
static constexpr int E_NO_OUTPUT = 2;
static constexpr int E_BAD_CMDL = 3;
static constexpr int E_PREPROCESSOR = 4;
static constexpr int E_BAD_INPUT = 5;
static constexpr int E_STREAM_ERROR = 6;
static constexpr int E_BAD_OUTPUT = 7;
static constexpr int E_EXCEPTION = 8;

static const std::string ADDITIONAL_MODS_SUB_DIR = std::string("Modules");

static const std::string OUTPUT_OPTION_LONG = "outfile";
static const char OUTPUT_OPTION_SHORT = 'o';

static const std::string DEBUG_OPTION_LONG = "debug";
static const char DEBUG_OPTION_SHORT = 'd';


static const std::string VERBOSE_OPTION_LONG = "verbose";
static const char VERBOSE_OPTION_SHORT = 'v';

static const std::string STREAM_OPTION_LONG = "stream";
static const char STREAM_OPTION_SHORT = 'Z';

static const std::string HELP_OPTION_LONG = "help";
static const char HELP_OPTION_SHORT = 'h';

static const std::string VERSION_OPTION_LONG = "version";
static const char VERSION_OPTION_SHORT = 'V';

static const std::string METRICS_OPTION_LONG = "metrics";
static const char METRICS_OPTION_SHORT = 'M';

static const std::string SAVE_COMPILER_FILES_OPTION_LONG = "nocleanup";
static const char SAVE_COMPILER_FILES_OPTION_SHORT = 'C';

static const std::string VERIFY_COMPILER_OPTION_LONG = "verify";
static const char VERIFY_COMPILER_OPTION_SHORT = 'X';

void PrintHelp()
{
	std::cout << "Usage: mare [options] -" << OUTPUT_OPTION_SHORT << "<file> | --" << OUTPUT_OPTION_LONG << " <file> file..." <<
		std::endl << "Options:" << std::endl;
	std::cout << "-" << OUTPUT_OPTION_SHORT << "<file>" << std::endl;
	std::cout << "--" << OUTPUT_OPTION_LONG << " <file>" << std::endl;
	std::cout << "--" << DEBUG_OPTION_LONG << " | -" << DEBUG_OPTION_SHORT << "" << std::endl;
	std::cout << "--" << VERBOSE_OPTION_LONG << " | -" << VERBOSE_OPTION_SHORT << "" << std::endl;
	std::cout << "--" << STREAM_OPTION_LONG << " | -" << STREAM_OPTION_SHORT << "" << std::endl;
	std::cout << "--" << HELP_OPTION_LONG << " | -" << HELP_OPTION_SHORT << "" << std::endl;
	std::cout << "--" << VERSION_OPTION_LONG << std::endl;
	std::cout << "--" << METRICS_OPTION_LONG << std::endl;
	std::cout << "--" << SAVE_COMPILER_FILES_OPTION_LONG << std::endl;
   std::cout << "--" << VERIFY_COMPILER_OPTION_LONG << std::endl;

	std::cout << std::endl;
}

void PrintVersion()
{
	std::cout << "MARE Version " << (int)MARE_VERSION_MAJOR << "." << (int)MARE_VERSION_MINOR << std::endl;
}

int main(int argc, char** argv)
{
	std::cerr << "MARE Compiler\n";
	std::cerr << "Copyright (C) " << MARE_COPYRIGHT_YEAR << " David Browning. All rights reserved.\n\n";

	int result = 0;

	auto linkerOptsPtr = std::make_shared<AtomicLinkerOptions>(true);
	COMPILER_OPTIONS compOpts(argv[0]);

	std::list<std::string> argvList;
	for(int i = 1; i < argc; i++)
	{
		argvList.push_back(argv[i]);
	}

	std::list<cmdarg_option<char, std::string>> commandLineOptions =
	{
		cmdarg_option<char, std::string>(OUTPUT_OPTION_SHORT, true, &OUTPUT_OPTION_LONG),
		cmdarg_option<char, std::string>(DEBUG_OPTION_SHORT, false, &DEBUG_OPTION_LONG),
		cmdarg_option<char, std::string>(VERBOSE_OPTION_SHORT, false, &VERBOSE_OPTION_LONG),
		cmdarg_option<char, std::string>(STREAM_OPTION_SHORT, false, &VERBOSE_OPTION_LONG),
		cmdarg_option<char, std::string>(HELP_OPTION_SHORT, false, &HELP_OPTION_LONG),
		cmdarg_option<char, std::string>(VERSION_OPTION_SHORT, false, &VERSION_OPTION_LONG),
		cmdarg_option<char, std::string>(METRICS_OPTION_SHORT, false, &METRICS_OPTION_LONG),
		cmdarg_option<char, std::string>(SAVE_COMPILER_FILES_OPTION_SHORT, false, &SAVE_COMPILER_FILES_OPTION_LONG),
	};

	cmdarg_parser<char, std::string> cmdParser(commandLineOptions, argvList);

	for(auto it = cmdParser.cbegin(); it != cmdParser.cend(); ++it)
	{
		switch(it->ShortOption)
		{
			case OUTPUT_OPTION_SHORT:
			{
				std::string filename = it->Argument;

				#ifdef _WIN32
				auto lastSlash = filename.find_last_of('\\');
				#else
				auto lastSlash = filename.find_last_of('/');
				#endif

				//Assign the file name.
				compOpts.OutFileName = filename.substr(lastSlash + 1, filename.length());

				//Make sure there actually is something in the filename.
				if(compOpts.OutFileName == "")
				{
					std::cerr << "No name was given for the output file.\n";
					return E_BAD_CMDL;
				}

				//Get the directory from the file name. If no directory was included, then
				//_opts->OutFileDir will be ".\"
				auto relativeDir = filename.substr(0, lastSlash + 1);
				path relativeDirPath(relativeDir);
				auto absDirPath = system_complete(relativeDirPath);
				compOpts.OutFileDir = absDirPath.string();

				//If there is a trailing "\", then delete it.
				//This happens if the "filename" is just a file name and includes no directory info.
				if(*(compOpts.OutFileDir.end() - 1) == '\\')
				{
					compOpts.OutFileDir.erase(compOpts.OutFileDir.end() - 1);
				}

				break;
			}
			case DEBUG_OPTION_SHORT:
			{
				compOpts.IsDebugMode = true;
				compOpts.IsVerbose = true;
				break;
			}
			case VERBOSE_OPTION_SHORT:
			{
				compOpts.IsVerbose = true;
				break;
			}
			case STREAM_OPTION_SHORT:
			{
				compOpts.IsSaveStreamFile = true;
				break;
			}
			case HELP_OPTION_SHORT:
			{
				PrintHelp();
				return 0;
			}
			case METRICS_OPTION_SHORT:
			{
				compOpts.ShowMetrics = true;
				break;
			}
			case VERSION_OPTION_SHORT:
			{
				PrintVersion();
				break;
			}
			case SAVE_COMPILER_FILES_OPTION_SHORT:
			{
				compOpts.SaveCompileFiles = true;
				break;
			}
			case cmdarg_parser<char, std::string>::NO_SHORT_OPTION_CHAR:
			{
				compOpts.SourceFiles.push_back(it->Argument);
				break;
			}
			default:
			{
				std::cerr << "Unknown option " << it->Argument << std::endl;
				break;
			}
		}
	}

	//Error if no input files are specified
	if(compOpts.SourceFiles.empty())
	{
		std::cerr << "No program files were specified." << std::endl;
		return E_NO_INPUT;
	}

	//Error if the output file is not specified.
	if(compOpts.OutFileName.empty())
	{
		std::cerr << "No output file was specified." << std::endl;
		return E_NO_OUTPUT;
	}

	if(compOpts.IsDebugMode)
	{
		std::clog << "The output file is \"" << compOpts.OutFile() << "\"\n\n";
	}

	//Add additional dependencies from the compiler path.
	std::string additionalModFilesDir = compOpts.CompilerDir + "\\" + ADDITIONAL_MODS_SUB_DIR;
	auto additionalModules = EnumerateMareFiles(additionalModFilesDir);
	compOpts.SourceFiles.insert(compOpts.SourceFiles.end(), additionalModules.begin(), additionalModules.end());

	//Create a dependency graph.
	DependencyGraph graph;
	//For each source file
	for(auto it = compOpts.SourceFiles.begin(); it != compOpts.SourceFiles.end(); ++it)
	{
		//Open a file stream to the source file.
		std::fstream sfile(*it, std::ios::in);
		if(!sfile.is_open())
		{
			std::cerr << "Could not open " << *it << std::endl;
			return E_BAD_INPUT;
		}

		//Run it through the preprocessor to get its dependencies. 
		PreprocessorScanner presc(sfile, cout, *it, linkerOptsPtr);
		PreprocessorParser preparser(presc);
		result = preparser.parse();
		sfile.close();

		if(result != 0)
		{
			std::cerr << "Preprocessor Error " << result << "." << std::endl;
			return result;
		}

		//Add those dependencies to the dependency graph.
		graph.Insert(presc.GetSourceFile());
	}

	//Sort the graph so we know what order to compile the files.
	graph.Sort();

	//Open the stream file.
	std::stringstream codeStream;

	//Write each source file, in order, to the stream file.
	if(compOpts.IsVerbose)
	{
		std::clog << "Writing source files to stream." << std::endl;
	}

	for(auto it = graph.BeginGraph(); it != graph.EndGraph(); ++it)
	{
		codeStream << *it << std::endl << std::endl;
		if(compOpts.IsDebugMode)
		{
			std::clog << "Wrote " << it->GetFilePath() << " to stream." << std::endl;
		}
	}

	codeStream.flush();

	//Open the out file;
	//Since C++ does not create parent directories when opening a file, do it here.

	if(_mkdir(compOpts.OutFileDir.c_str()) == -1 && errno == ENOENT)
	{
		std::cerr << "The outfile is not well formed." << std::endl;
		return E_BAD_CMDL;
	}

	//Open the output header file. 
	std::fstream outFile(compOpts.OutFile(), std::ios::trunc | std::ios::out);
	if(!outFile.is_open())
	{
		std::cerr << "Could not open \"" << compOpts.OutFile() << "\" for writing." << std::endl;
		std::cerr << "Does the file already exist?" << std::endl;
		return E_BAD_OUTPUT;
	}

	//Save the stream file if requested.
	if(compOpts.IsSaveStreamFile)
	{
		if(compOpts.IsVerbose)
		{
			std::clog << "Saving stream file..." << std::endl;
		}

		std::fstream streamFile("./mare.stream", std::ios::trunc | std::ios::out);
		if(!streamFile.is_open())
		{
			std::cerr << "Could not open mare.stream for writing." << std::endl;
			return E_STREAM_ERROR;
		}

		streamFile << codeStream.rdbuf();
		codeStream.seekg(0, ios::beg);
		streamFile.flush();
		streamFile.close();
	}

	if(compOpts.IsDebugMode)
	{
		std::clog << "Parsing stream file..." << std::endl;
	}

	if(compOpts.IsVerbose)
	{
		std::clog << "Compiling..." << std::endl;
	}

	//Pass the stream file to the parser.
	SourceScanner srcscr(codeStream, outFile, false, std::cerr);
	SourceParser srcpsr(srcscr);
	#ifndef DEBUG
	try
	{
		result = srcpsr.parse();
	}
	catch(const exception& e)
	{
		std::cerr << e.what() << std::endl;
		return E_EXCEPTION;
	}
	#else
	result = srcpsr.parse();
	#endif

	//Done with the code stream.

	//Done with the out file.
	outFile.flush();
	outFile.close();

	//Link only if compilation was successful.
	if(result == 0)
	{
		if(compOpts.IsVerbose)
		{
			std::clog << "Linking..." << std::endl;
		}

		MARE_LINKER_OUTPUT linkInfo;
		try
		{
			CreateLinkerOutput(compOpts, &linkInfo);
			RunLinker(compOpts, linkInfo);
		}
		catch(std::exception& e)
		{
			std::cerr << "Could not link.\n";
			std::cerr << e.what() << std::endl;
			result = 1;
		}

		if(!compOpts.SaveCompileFiles)
		{
			CleanupCompileFiles(compOpts, linkInfo);
		}
	}

	if(compOpts.ShowMetrics)
	{
		srcscr.GetCPtr()->PrintMetrics(std::cout);
	}

	//Notify the user on the status of the compilation process.
	if(result != 0)
	{
		std::cout << "Your code could not be compiled." << std::endl;
	}
	else
	{
		std::cout << "\nYour code compiled successfully." << std::endl;
	}

	return result;
}