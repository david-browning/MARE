#include "mare_dependency_graph.h"
#include "mare_exceptions.h"
#include <queue>

DependencyGraph::DependencyGraph()
{
}

DependencyGraph::~DependencyGraph()
{
}

void DependencyGraph::Insert(const SourceFile& dep)
{
	auto it = std::find(_graph.begin(), _graph.end(), dep);
	if(it == _graph.end())
	{
		_graph.push_back(dep);
	}
}

void DependencyGraph::Sort()
{
	const auto verts = _graph.size();
	auto l = std::vector<std::vector<SourceFile*>>(verts);
	for(size_t i = 0; i < verts; i++)
	{
		for(auto it = _graph.at(i).BeginDeps(); it != _graph.at(i).EndDeps(); ++it)
		{
			SourceFile* s = nullptr;
			for(size_t k = 0; k < verts; k++)
			{
				if(_graph.at(k).GetFileName() == *it)
				{
					s = _graph.data() + k;
				}
			}

			if(!s)
			{
				throw dependency_not_found_exception(*it);
			}

			s->IncrementIndegree();
			l[i].push_back(s);
		}
	}

	std::vector<SourceFile> res(verts);
	std::queue<size_t> q;

	for(size_t u = 0; u < verts; u++)
	{
		if(_graph[u].GetIndegree() == 0)
		{
			q.push(u);
		}
	}

	size_t i = 0;
	while(!q.empty())
	{
		auto u = q.front();
		q.pop();

		res[verts - 1 - i] = _graph[u];
		i++;

		for(auto v = l[u].begin(); v != l[u].end(); ++v)
		{
			(*v)->DecrementIndegree();
			if((*v)->GetIndegree() == 0)
			{
				q.push(*v - _graph.data());
			}
		}

	}
	_graph = std::move(res);
}
