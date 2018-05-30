#pragma once
#include "IGraph.h"
#include<assert.h>
struct Edge {
private:
	int From;
	int To;
public:
	Edge(int from, int to) : From(from), To(to) {};
	int GetFrom() {
		return this->From;
	}
	int GetTo() {
		return this->To;
	}
};

class ArcGraph : public IGraph {
public:
	ArcGraph(int count);
	ArcGraph(const IGraph& graph);
	virtual ~ArcGraph();

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to);

	virtual int VerticesCount() const;
	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
	int countVertices;
	vector<Edge*>adjacencyLists;
};

ArcGraph::ArcGraph(int count) : countVertices(count) {

}

ArcGraph::ArcGraph(const IGraph& graph)
{
	countVertices = graph.VerticesCount();

	for (int from = 0; from < countVertices; from++) {

		vector<int> vertices;
		graph.GetNextVertices(from, vertices);
		while (!vertices.empty()) {
			Edge *pair = new Edge(from, vertices.back());
			adjacencyLists.push_back(pair);
			vertices.pop_back();
		}

	}
};

ArcGraph::~ArcGraph()
{
	for (int i = 0; i < adjacencyLists.size(); i++)
		delete adjacencyLists[i];
}

void ArcGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < countVertices);
	assert(to >= 0 && to < countVertices);
	Edge *pair = new Edge(from, to);
	adjacencyLists.push_back(pair);
}

int ArcGraph::VerticesCount() const
{
	return countVertices;
}

void ArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	assert(vertex >= 0 && vertex < countVertices);
	for (int i = 0; i < adjacencyLists.size(); i++) {
		if (adjacencyLists[i]->GetFrom() == vertex)
			vertices.push_back(adjacencyLists[i]->GetTo());
	}

}

void ArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{

	assert(vertex >= 0 && vertex < countVertices);
	for (int j = 0; j < adjacencyLists.size(); j++) {
		if (adjacencyLists[j]->GetTo() == vertex)
			vertices.push_back(adjacencyLists[j]->GetFrom());
	}
}