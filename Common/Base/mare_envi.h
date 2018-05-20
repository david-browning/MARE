#pragma once
#include <annotations.h>

/*
 Returns a list of all files in dir that have the extension MARE_FILE_EXT.
 See MARE_FILE_EXT for what the extension is.
 */
extern LIB_EXPORT std::vector<std::string> EnumerateMareFiles(const std::string& dir);
