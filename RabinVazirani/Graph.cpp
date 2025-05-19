#include "Graph.h"

#include <random>

Graph::Graph() = default;

void Graph::ReadGraphFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	if (!inputFile.is_open())
	{
		std::cerr << "Could not open file " << filename << std::endl;
	}

	m_adjacencyMatrix.clear();

	int numVertices, edgeCount;
	inputFile >> numVertices >> edgeCount;

	m_adjacencyMatrix.resize(numVertices, std::vector(numVertices, static_cast<double>(INF)));

	int u, v, w;
	for (int i = 0; i < edgeCount; ++i)
	{
		inputFile >> u >> v >> w;
		AddEdge(u, v, w);
	}
}

void Graph::AddEdge(const int u, const int v, const int w) { m_adjacencyMatrix[u][v] = w; }

void Graph::PrintAdjacencyMatrix(const AdjacencyMatrix& adj)
{
	for (const auto& row : adj)
	{
		for (const auto& element : row)
		{
			if (element == NO_EDGE)
			{
				std::cout << "∞" << "	";
				continue;
			}
			std::cout << element << "	";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool Graph::GetInvertedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& invertedMatrix)
{
	const size_t rows = matrix.size();
	const double determinant = GetDeterminant(matrix);
	if (determinant == 0.0)
	{
		return false;
	}

	AdjacencyMatrix cofactor(rows, std::vector<double>(rows));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			auto minor = GetMinor(matrix, i, j);
			const double minorDeterminant = GetDeterminant(minor);
			cofactor[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minorDeterminant;
		}
	}

	auto newMatrix = GetTranspose(cofactor);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < rows; ++j)
		{
			newMatrix[i][j] /= determinant;
		}
	}

	invertedMatrix = std::move(newMatrix);
	return true;
}

double Graph::GetDeterminant(const AdjacencyMatrix& matrix)
{
	const size_t rows = matrix.size();
	if (rows == 0)
	{
		return 0;
	}
	if (rows == 1)
	{
		return matrix[0][0];
	}
	if (rows == 2)
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}

	double determinant = 0.0;
	int sign = 1;
	for (int j = 0; j < rows; ++j)
	{
		const AdjacencyMatrix minor = GetMinor(matrix, 0, j);
		determinant += sign * matrix[0][j] * GetDeterminant(minor);
		sign = -sign;
	}

	return determinant;
}

AdjacencyMatrix Graph::GetMinor(
	const AdjacencyMatrix& matrix, const int skipRow, const int skipColumn)
{
	const size_t rows = matrix.size();
	AdjacencyMatrix minor;

	for (size_t i = 0; i < rows; ++i)
	{
		if (i == skipRow)
		{
			continue;
		}
		std::vector<double> row;
		for (int j = 0; j < rows; ++j)
		{
			if (j == skipColumn)
			{
				continue;
			}
			row.push_back(matrix[i][j]);
		}
		minor.push_back(row);
	}

	return minor;
}

AdjacencyMatrix Graph::GetTranspose(const AdjacencyMatrix& matrix)
{
	const size_t rows = matrix.size();

	AdjacencyMatrix transposedMatrix(rows, std::vector<double>(rows));
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < rows; ++j)
		{
			transposedMatrix[j][i] = matrix[i][j];
		}
	}

	return transposedMatrix;
}

AdjacencyMatrix Graph::GetAdjacencyMatrix() { return m_adjacencyMatrix; }

Pairs Graph::AdjacencyMatrixToEdges(const AdjacencyMatrix& matrix)
{
	Pairs edges;
	const int vertexesCount = static_cast<int>(matrix.size());
	for (int i = 0; i < vertexesCount; i++)
	{
		for (int j = 0; j < vertexesCount; j++)
		{
			if (matrix[i][j] != NO_EDGE)
			{
				edges.push_back({ i, j });
			}
		}
	}
	return edges;
}