#pragma once

#include <annotations.h>
#include "mare_source_file.h"

/*
 This is an ordered graph of the source files used in a MARE program. The graph sorts
 the source files by their dependencies into a list. The list is ordered from files that 
 contain no dependencies, to files that are dependent on the files earlier in the list.
 */
class LIB_EXPORT DependencyGraph
{
 public:
	/*
	 Constructor.
	 Constructs an empty graph.
	 */
	DependencyGraph();

	/*
	 Destructor
	 */
	virtual ~DependencyGraph();

	/*
	 Adds a source file to the dependency graph.
	 If the source file is already in the graph, it is not added.
	 */
	void Insert(const SourceFile &dep);

	/*
	 Sorts the graph into an ordered list so that the first element has no dependencies and
	 the last element depends on the elements before it.
	 */
	void Sort();

	/*
	 Returns the begining iterator for the source files in the graph.
	 */
	inline auto BeginGraph() const
	{
		return _graph.begin();
	}

	/*
	 Returns the ending iterator for the source files in the graph.
	 */
	inline auto EndGraph() const
	{
		return _graph.end();
	}

 private:
	/*
	 List of source files in the graph.
	 */
	std::vector<SourceFile> _graph;

	/*
	 Predicate to compare to source files.
	 */
	struct SOURCE_COMPARATOR
	{
		SOURCE_COMPARATOR(SourceFile *p)
		{
			_p = p;
		}

		bool operator()(const SourceFile &m) const
		{
			//return _p->GetFilePath() == m.GetFilePath();
			return *_p == m;
		}

		SourceFile *_p;
	};
};