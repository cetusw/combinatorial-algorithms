#ifndef GRAPH_H
#define GRAPH_H

#include "Matrix.h"
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
	void ReadGraphFromFile(std::istream& file);
	AdjacencyMatrix GetAdjacencyMatrix();
	AdjacencyMatrix EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges);
	ListOfEdges AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix);
	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);
	static void PrintListOfEdges(const ListOfEdges& edges);

	void FindMinCycle(const Matrix& m, const Edges& path, int& bottomLimit);
	int SubtractFromMatrix(Matrix& matrix);
	std::vector<ZeroInfo> FindBestZeros(const Matrix& matrix);
	void AddInfinity(Matrix& matrix);
	bool IsCycleFound() const;
	int GetCycleWeight() const;
	const Edges& GetCyclePath() const;

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	int m_numVertices = 0;
	AdjacencyMatrix m_adjacencyMatrix;
	double m_record = INF;
	HamiltonianCycleResult m_bestCycle;
};

#endif // GRAPH_H