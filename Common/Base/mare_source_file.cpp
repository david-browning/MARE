#include "mare_source_file.h"

SourceFile::SourceFile()
{
}

SourceFile::SourceFile(const std::string& filepath) :
	_filepath(filepath), _indegree(0)
{
	#ifdef _WINDOWS
	auto lastSlash = filepath.find_last_of('\\');
	#else
	auto lastSlash = filepath.find_last_of('/');
	#endif

	_filename = filepath.substr(lastSlash + 1, filepath.length());
}

SourceFile::SourceFile(const SourceFile& c) :
	_filepath(c._filepath), _deps(c._deps), _indegree(c._indegree),
	_filename(c._filename)
{

}

SourceFile::SourceFile(SourceFile && m):
	_filepath(std::move(m._filepath)), _deps(std::move(m._deps)), _indegree(m._indegree),
	_filename(std::move(m._filename))
{
}

void SourceFile::operator=(const SourceFile & r)
{
	_filepath = r._filepath;
	_deps = r._deps;
	_indegree = r._indegree;
	_filename = r._filename;
}
SourceFile::~SourceFile()
{
}

void SourceFile::AddDependency(std::string dep_p)
{
	auto it = std::find(_deps.begin(), _deps.end(), dep_p);
	if(it == _deps.end())
	{
		_deps.push_back(dep_p);
	}
}