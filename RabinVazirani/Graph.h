#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<double>>;
using Pairs = std::vector<std::pair<int, int>>;
constexpr int INF = std::numeric_limits<int>::max();

class Graph
{
public:
	Graph();
	void AddEdge(int u, int v, int w);
	void ReadGraphFromFile(const std::string& filename);
	AdjacencyMatrix GetAdjacencyMatrix();
	Pairs AdjacencyMatrixToEdges(const AdjacencyMatrix& matrix);
	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);

	bool GetInvertedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& invertedMatrix);
	double GetDeterminant(const AdjacencyMatrix& matrix);
	AdjacencyMatrix GetMinor(const AdjacencyMatrix& matrix, int skipRow, int skipColumn);
	AdjacencyMatrix GetTranspose(const AdjacencyMatrix& matrix);

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	int m_numVertices = 0;
	AdjacencyMatrix m_adjacencyMatrix;
};
#endif // GRAPH_H