// graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "IGraph.h"
#include "ArcGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

#include<iostream>
#include<queue>
#include<assert.h>

using std::vector;
using std::cout;
using std::queue;





void BFS(const IGraph& graph, int vertex, void(*visit)(int))
{
	vector<bool> visited(graph.VerticesCount(), false);
	queue<int> qu;
	qu.push(vertex);
	visited[vertex] = true;

	while (qu.size() != 0) {
		int current = qu.front();
		qu.pop();
		visit(current);
		vector<int> adjacentVertices;
		graph.GetNextVertices(current, adjacentVertices);
		for (int i = 0; i < adjacentVertices.size(); i++) {
			if (!visited[adjacentVertices[i]]) {
				qu.push(adjacentVertices[i]);
				visited[adjacentVertices[i]] = true;
			}
		}
	}
}
//int BFS2(const IGraph& graph, int vertex,  int to)
//{
//	vector<bool> visited(graph.VerticesCount(), false);
//	vector<int> lengths(graph.VerticesCount(), 0);// количетсво ребер до кажлой вершины   ++(graph.VerticesCount^2));
//	queue<int> qu;
//	vector<int> shortest(graph.VerticesCount, 0);
//	qu.push(vertex);
//	visited[vertex] = true;
//	int count = 0;
//	while (qu.size() != 0) {
//		int current = qu.front();
//		visited[current] = true;
//		qu.pop();
//		//count++;
//		
//		//if (shortest[current] > )
//		if (current == to) break;
//		vector<int> adjacentVertices;
//		graph.GetNextVertices(current, adjacentVertices);
//		for (int i = 0; i < adjacentVertices.size(); i++) {
//			if (!visited[adjacentVertices[i]]) {
//				qu.push(adjacentVertices[i]);
//				//visited[adjacentVertices[i]] = true;
//				lengths[adjacentVertices[i]]+=(lengths[current]+1);
//			}
//		}
//	}
//
//	return lengths[to];
//}



int main()
{
	//MatrixGraph graph(7);
	//ListGraph graph(7);
	//SetGraph graph(7);
	ArcGraph graph(7);
	
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 5);
	graph.AddEdge(1, 2);
	graph.AddEdge(1, 3);
	graph.AddEdge(1, 5);
	graph.AddEdge(1, 6);
	graph.AddEdge(3, 2);
	graph.AddEdge(3, 6);
	graph.AddEdge(4, 3);
	graph.AddEdge(5, 4);
	graph.AddEdge(5, 6);
	graph.AddEdge(6, 4);
	ArcGraph x (*new SetGraph ( *new ListGraph(*new MatrixGraph(graph))));
	
	
	BFS(graph, 5, [](int vertex) { cout << vertex << " "; });
	cout << endl;
	BFS(x, 5, [](int vertex) { cout << vertex << " "; });
	//int v, n, u, w;
	//cin >> v;
	//cin >> n;
	//int from, to;
	//ListGraph graph(v);
	//for (int i = 0; i < n; i++)
	//{
	//	cin >> from >> to;
	//	graph.AddEdge(from, to);
	//}
	//cin >> u >> w;
	//cout << BFS2(graph, u, w);


	return 0;
}