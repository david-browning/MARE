#include "mare_envi.h"
#include "mare_exceptions.h"
#include "mare_compiler_consts.h"

#ifdef _WINDOWS

#include <experimental/filesystem>
#include <filesystem>
using namespace std::experimental::filesystem;

#else

#include <filesystem>
using namespace std::filesystem;

#endif

std::vector<std::string> EnumerateMareFiles(const std::string& dir)
{
	//Find all files that end with the MARE_FILE_EXT.
	std::vector<std::string> files;
	for(auto& p : directory_iterator(dir))
	{
		std::string path = p.path().u8string();
		size_t start = path.length() - MARE_FILE_EXT.length();
		size_t end = MARE_FILE_EXT.length();
		if(path.compare(start, end, MARE_FILE_EXT) == 0)
		{
			files.push_back(path);
		}
	}

	return files;
}
