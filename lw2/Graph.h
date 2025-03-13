#ifndef GRAPH_H
#define GRAPH_H

#include "Types.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <vector>

class Graph
{
public:
	Graph();
	void AddEdge(int u, int v, int w);
	void ReadGraphFromFile(std::ifstream& file);
	AdjacencyMatrix GetAdjacencyMatrix();

	void processDFS(int vertex, std::vector<bool>& visited);
	void DFS(int startVertex);

	AdjacencyMatrix EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges);
	static ListOfEdges AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix);

	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);
	static void PrintListOfEdges(const ListOfEdges& edges);

private:
	int numVertices = 0;
	static constexpr int NO_EDGE = std::numeric_limits<int>::max();
	AdjacencyMatrix adjacencyMatrix;
	std::vector<bool> visited;
};

#endif // GRAPH_H