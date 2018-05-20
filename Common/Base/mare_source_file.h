#pragma once
#include <annotations.h>

/*
 A source file is a node in a dependency graph. It is an abstract handle to a file that gets 
 compiled, along with others, into a MARE program.
 */
class LIB_EXPORT SourceFile
{
	public:

	/*
	 Default constructor.
	 TODO: Delete this?
	 */
	SourceFile();

	/*
	 Constructor
	 Creates an abstract handle to the MARE source file located at "filepath".
	 */
	SourceFile(const std::string& filepath);

	/*
	 Copy constructor.
	 */
	SourceFile(const SourceFile& c);

	/*
	 Move constructor.
	 */
	SourceFile(SourceFile&& m);

	/*
	 Destructor.
	 */
	virtual ~SourceFile();

	/*
	 Returns true if the right SourceFile points to the same SourceFile as the left.
	 */
	friend LIB_EXPORT bool operator==(const SourceFile& l, const SourceFile& r)
	{
		return l._filename == r._filename;
	}

	/*
	 Assigns the right-hand Source file to this.
	 */
	void operator=(const SourceFile& r);

	/*
	 Returns an iterator to the begining of this source file's list of dependencies.
	 */
	inline auto BeginDeps()
	{
		return _deps.begin();
	}

	/*
	 Returns an iterator the the end of this source file;s list of dependencies.
	 */
	inline auto EndDeps()
	{
		return _deps.end();
	}
	
	/*
	 Increments the indegree of this source file.
	 This is meant to only be called by the MARE dependency graph. Developers should not call
	 this function
	 */
	inline void IncrementIndegree()
	{
		_indegree++;
	}

	/*
	 Decrements the indegree of this source file.
	 This is meant to only be called by the MARE dependency graph. Developers should not call
	 this function
	 */
	inline void DecrementIndegree()
	{
		_indegree--;
	}

	/*
	 Returns the path to the source file.
	 */
	inline const std::string& GetFilePath() const noexcept
	{
		return _filepath;
	}

	/*
	 Returns the file name of the source file. This is not the entire path.
	 */
	inline const std::string& GetFileName() const noexcept
	{
		return _filename;
	}

	/*
	 Gets the indegree of this source file.
	 This is meant to only be called by the MARE dependency graph. Developers should not call
	 this function
	 */
	inline unsigned int GetIndegree() const
	{
		return _indegree;
	}

	/*
	 Adds a dependency to this source file's list of dependencies. The preprocessor
	 parser calls this function when scanning source files.
	 */
	void AddDependency(std::string dep_p);

	/*
	 Writes the contents of the file to the ostream.
	 */
	friend LIB_EXPORT std::ostream& operator<<(std::ostream& os, const SourceFile& sc)
	{
		std::fstream f(sc._filepath, std::ios::in);
		return os << f.rdbuf();
	}

	private:
	/*
	 Path to the source file.
	 */
	std::string _filepath;

	/*
	 Name of the source file. Includes extention.
	 */
	std::string _filename;

	/*
	 List of files this source file depends on.
	 */
	std::vector<std::string> _deps;

	/*
	 The indegree of this element when its a member of a dependency graph.
	 */
	unsigned int _indegree = 0;
};

