#pragma once
#include "IGraph.h"
#include<assert.h>
#include <unordered_set>

using namespace std;
class SetGraph : public IGraph {
public:
	SetGraph(int count);
	SetGraph(const IGraph& graph);
	virtual ~SetGraph();

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to);

	virtual int VerticesCount() const;
	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
	int countVertices;
	vector<unordered_set<int>> hashTablesList;
};

int SetGraph::VerticesCount() const
{
	return countVertices;
}

SetGraph::SetGraph(int count) : countVertices(count) {
	hashTablesList.resize(count);
}

SetGraph::SetGraph(const IGraph& graph)
{
	countVertices = graph.VerticesCount();
	hashTablesList.resize(countVertices);
	for (int from = 0; from < countVertices; from++) {

		vector<int> vertices;
		graph.GetNextVertices(from, vertices);
		while (!vertices.empty()) {
			hashTablesList[from].insert(vertices.back());
			vertices.pop_back();
		}

	}
};

SetGraph::~SetGraph()
{
	hashTablesList.clear();
}

void SetGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < countVertices);
	assert(to >= 0 && to < countVertices);
	hashTablesList[from].insert(to);
}



void SetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	assert(vertex >= 0 && vertex < countVertices);
	unordered_set<int> ::iterator itr;
	for (itr = hashTablesList[vertex].begin(); itr != hashTablesList[vertex].end(); itr++)
		 vertices.push_back(*itr);


}

void SetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{

	assert(vertex >= 0 && vertex < countVertices);
	for (int i = 0; i < countVertices; i++)
	{
		if (hashTablesList[i].find(vertex) != hashTablesList[i].end())
			vertices.push_back(i);
	}
	
	
}