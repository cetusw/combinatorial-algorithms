#include "RabinVazirani.h"

#include <iomanip>
#include <random>

constexpr double MAX_RANDOM_DOUBLE = 1009.0;

Pairs RabinVazirani::FindMaximumMatching(const Graph& graph)
{
	m_graph = graph;
	AdjacencyMatrix tutteMatrix = GetTutteMatrix(m_graph.GetAdjacencyMatrix());

	const size_t rows = tutteMatrix.size();
	std::vector used(rows, true);
	Pairs matchingPairs;
	FindMatching(rows, m_graph.AdjacencyMatrixToEdges(m_graph.GetAdjacencyMatrix()), tutteMatrix, used, matchingPairs);
	return matchingPairs;
}

void RabinVazirani::FindMatching(const size_t rows, const Pairs& edges,
	 AdjacencyMatrix& tutteMatrix, std::vector<bool>& used, Pairs& matches)
{
	int unusedVertices = 0;
	for (const bool unusedVertex : used)
	{
		if (unusedVertex)
		{
			unusedVertices++;
		}
	}

	if (unusedVertices < 2)
	{
		return;
	}

	AdjacencyMatrix invertedMatrix(rows, std::vector<double>(rows));
	if (!m_graph.GetInvertedMatrix(tutteMatrix, invertedMatrix))
	{
		return;
	}

	for (auto [u, v] : edges)
	{
		if (!used[u] || !used[v])
		{
			continue;
		}

		if (invertedMatrix[v][u] != 0)
		{
			matches.emplace_back(u, v);
			used[u] = used[v] = false;
			for (size_t i = 0; i < rows; i++)
			{
				tutteMatrix[u][i] = tutteMatrix[v][i] = 0;
				tutteMatrix[i][u] = tutteMatrix[i][v] = 0;
			}
			FindMatching(rows, edges, tutteMatrix, used, matches);
		}
	}
}

double RabinVazirani::GetRandomDouble()
{
	std::mt19937_64 rng{ std::random_device{}() };
	std::uniform_real_distribution dist{ 1.0, MAX_RANDOM_DOUBLE };
	return dist(rng);
}

AdjacencyMatrix RabinVazirani::GetTutteMatrix(const AdjacencyMatrix& matrix)
{
	const size_t rows = matrix.size();
	AdjacencyMatrix tutteMatrix(rows, std::vector<double>(rows));

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			if (matrix[i][j] == Graph::NO_EDGE && !tutteMatrix[i][j])
			{
				tutteMatrix[i][j] = 0;
			}
			else
			{
				tutteMatrix[j][i] = GetRandomDouble();
				tutteMatrix[i][j] = -tutteMatrix[j][i];
			}
		}
	}

	return tutteMatrix;
}