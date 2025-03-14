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

	void ProcessDFS(int vertex, std::vector<bool>& visited);
	void DFS(int startVertex);
	void PrintDiscoveryFinishTimes() const;
	HamiltonianCycleResult FindMinHamiltonianCycle() const;

	AdjacencyMatrix EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges);
	ListOfEdges AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix);

	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);
	static void PrintListOfEdges(const ListOfEdges& edges);

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	int numVertices = 0;
	AdjacencyMatrix adjacencyMatrix;
	std::vector<bool> visited;
	std::vector<std::pair<int, int>> discoveryFinishTimes;
	int timeCounter = 0;
};

#endif // GRAPH_H