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
	void ReadGraphFromFile(std::ifstream& file);
	void AddInfinity(Matrix& matrix);
	void FindMinCycle(const Matrix& m, const Edges& path, double& bottomLimit);
	bool IsCycleFound() const;
	double GetCycleWeight() const;
	const Edges& GetCyclePath() const;
	AdjacencyMatrix GetAdjacencyMatrix();
	void SetAdjacencyMatrix(const AdjacencyMatrix& matrix);
	void SetEdge(int row, int col, int value);

	void ProcessDFS(int vertex, std::vector<bool>& visited);
	void DFS(int startVertex);
	void PrintDiscoveryFinishTimes() const;
	[[nodiscard]] HamiltonianCycleResult FindMinHamiltonianCycle() const;
	void PrintHamiltonianCycle(const HamiltonianCycleResult& result);

	double SubtractFromMatrix(Matrix& matrix);
	std::vector<ZeroInfo> FindBestZeros(const Matrix& matrix);

	AdjacencyMatrix EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges);
	ListOfEdges AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix);

	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);
	static void PrintListOfEdges(const ListOfEdges& edges);

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	int m_numVertices = 0;
	AdjacencyMatrix m_adjacencyMatrix;
	std::vector<bool> m_visited;
	std::vector<std::pair<int, int>> m_discoveryFinishTimes;
	int m_timeCounter = 0;
	std::vector<int> m_rowOriginIndexes;
	std::vector<int> m_colOrigIndexes;
	double m_record = INF;
	HamiltonianCycleResult m_bestCycle;
};

#endif // GRAPH_H