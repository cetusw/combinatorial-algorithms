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
	static Pairs AdjacencyMatrixToEdges(const AdjacencyMatrix& matrix);
	static void PrintAdjacencyMatrix(const AdjacencyMatrix& adj);

	static bool GetInvertedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& invertedMatrix);
	static double GetDeterminant(const AdjacencyMatrix& matrix);
	static AdjacencyMatrix GetMinor(const AdjacencyMatrix& matrix, int skipRow, int skipColumn);
	static AdjacencyMatrix GetTranspose(const AdjacencyMatrix& matrix);

	static constexpr int NO_EDGE = std::numeric_limits<int>::max();

private:
	static void GetExtendedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& extendedMatrix);
	static void GetRowWithMaxElement(
		const size_t& currentRow, const AdjacencyMatrix& extendedMatrix, size_t& rowWithMaxElement);
	static void SwapRows(
		const size_t& rowWithMaxElement, const size_t& currentRow, AdjacencyMatrix& extendedMatrix);
	static void NormalizeRow(AdjacencyMatrix& extendedMatrix, const size_t& currentRow);
	static void ResetRowsToZero(AdjacencyMatrix& extendedMatrix, const size_t& currentRow);
	static void ExtractInvertedMatrix(
		AdjacencyMatrix& invertedMatrix, const AdjacencyMatrix& extendedMatrix);

	int m_numVertices = 0;
	AdjacencyMatrix m_adjacencyMatrix;
};
#endif // GRAPH_H