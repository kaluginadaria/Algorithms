#pragma once
#include "IGraph.h"
#include<assert.h>
class MatrixGraph : public IGraph {
public:
	MatrixGraph(int count);
	MatrixGraph(const IGraph& graph);
	virtual ~MatrixGraph();

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to);

	virtual int VerticesCount() const;
	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
	int countVertices;
	bool  **adjacencyLists;
};

MatrixGraph::MatrixGraph(int count) : countVertices(count) {
	adjacencyLists = new bool *[countVertices];
	for (int from = 0; from < countVertices; from++) {
		adjacencyLists[from] = new bool[countVertices];
		for (int to = 0; to < countVertices; to++) {
			adjacencyLists[from][to] = 0;
		}
	}

}

MatrixGraph::MatrixGraph(const IGraph& graph)
{
	countVertices = graph.VerticesCount();
	adjacencyLists = new bool *[countVertices];
	for (int from = 0; from < countVertices; from++) {
		adjacencyLists[from] = new bool[countVertices];
		for (int to = 0; to < countVertices; to++) {
			adjacencyLists[from][to] = 0;
		}
		vector<int> vertices;
		graph.GetNextVertices(from, vertices);
		while (!vertices.empty()) {
			adjacencyLists[from][vertices.back()] = 1;
			vertices.pop_back();
		}


	}
};

MatrixGraph::~MatrixGraph()
{
	for (int i = 0; i < countVertices; i++)
	{
		delete[]adjacencyLists[i];
	}

	delete[] adjacencyLists;
}

void MatrixGraph::AddEdge(int from, int to)
{
	assert(from >= 0 && from < countVertices);
	assert(to >= 0 && to < countVertices);
	adjacencyLists[from][to] = 1;
}

int MatrixGraph::VerticesCount() const
{
	return countVertices;
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	assert(vertex >= 0 && vertex < countVertices);
	for (int to = 0; to < countVertices; to++)
		if (adjacencyLists[vertex][to] == 1)	vertices.push_back(to);
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{

	assert(vertex >= 0 && vertex < countVertices);
	for (int from = 0; from < countVertices; from++)
		if (adjacencyLists[from][vertex] == 1)	vertices.push_back(from);
}
