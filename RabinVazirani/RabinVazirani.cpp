#include "RabinVazirani.h"

#include <iomanip>
#include <random>

constexpr double MAX_RANDOM_DOUBLE = 1000.0;

Pairs RabinVazirani::FindMaximumMatching(const Graph& graph)
{
	m_graph = graph;
	AdjacencyMatrix tutteMatrix = GetTutteMatrix(m_graph.GetAdjacencyMatrix());

	const size_t vertices = tutteMatrix.size();
	std::vector used(vertices, false);
	Pairs matchingPairs;
	FindMatching(vertices, m_graph.AdjacencyMatrixToEdges(m_graph.GetAdjacencyMatrix()), tutteMatrix, used, matchingPairs);
	return matchingPairs;
}

void RabinVazirani::FindMatching(const size_t vertices, const Pairs& edges,
	 AdjacencyMatrix& tutteMatrix, std::vector<bool>& used, Pairs& matches)
{
	int unusedVertices = 0;
	for (const bool usedVertex : used)
	{
		if (!usedVertex)
		{
			unusedVertices++;
		}
	}
	if (unusedVertices < 2)
	{
		return;
	}

	AdjacencyMatrix invertedMatrix(vertices, std::vector<double>(vertices));
	if (!m_graph.GetInvertedMatrix(tutteMatrix, invertedMatrix))
	{
		return;
	}

	for (auto [u, v] : edges)
	{
		if (used[u] || used[v])
		{
			continue;
		}

		if (invertedMatrix[v][u] != 0)
		{
			matches.emplace_back(u, v);
			used[u] = true;
			used[v] = true;
			for (size_t i = 0; i < vertices; i++)
			{
				tutteMatrix[u][i] = 0;
				tutteMatrix[v][i] = 0;
				tutteMatrix[i][u] = 0;
				tutteMatrix[i][v] = 0;
			}
			FindMatching(vertices, edges, tutteMatrix, used, matches);
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
	const size_t vertices = matrix.size();
	AdjacencyMatrix tutteMatrix(vertices, std::vector<double>(vertices));

	for (size_t i = 0; i < vertices; ++i)
	{
		for (size_t j = 0; j < vertices; ++j)
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