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

	AdjacencyMatrix extendedMatrix(rows, std::vector(rows * 2, 0.0));
	GetExtendedMatrix(matrix, extendedMatrix);

	for (size_t i = 0; i < rows; ++i)
	{
		size_t rowWithMaxElement = i;
		GetRowWithMaxElement(i, extendedMatrix, rowWithMaxElement);

		if (std::fabs(extendedMatrix[rowWithMaxElement][i]) < 1e-10)
		{
			return false;
		}

		SwapRows(rowWithMaxElement, i, extendedMatrix);
		NormalizeRow(extendedMatrix, i);
		ResetRowsToZero(extendedMatrix, i);
	}

	ExtractInvertedMatrix(invertedMatrix, extendedMatrix);

	return true;
}

void Graph::GetExtendedMatrix(const AdjacencyMatrix& matrix, AdjacencyMatrix& extendedMatrix)
{
	const size_t rows = matrix.size();
	for (size_t i = 0; i < rows; ++i)
	{
		std::copy(matrix[i].begin(), matrix[i].end(), extendedMatrix[i].begin());
		extendedMatrix[i][rows + i] = 1.0;
	}
}

void Graph::GetRowWithMaxElement(
	const size_t& currentRow, const AdjacencyMatrix& extendedMatrix, size_t& rowWithMaxElement)
{
	for (size_t j = currentRow; j < extendedMatrix.size(); ++j)
	{
		if (std::fabs(extendedMatrix[j][currentRow])
			> std::fabs(extendedMatrix[rowWithMaxElement][currentRow]))
		{
			rowWithMaxElement = j;
		}
	}
}

void Graph::SwapRows(
	const size_t& rowWithMaxElement, const size_t& currentRow, AdjacencyMatrix& extendedMatrix)
{
	if (rowWithMaxElement != currentRow)
	{
		std::swap(extendedMatrix[currentRow], extendedMatrix[rowWithMaxElement]);
	}
}

void Graph::NormalizeRow(AdjacencyMatrix& extendedMatrix, const size_t& currentRow)
{
	const double div = extendedMatrix[currentRow][currentRow];
	for (size_t j = 0; j < extendedMatrix.size() * 2; ++j)
	{
		extendedMatrix[currentRow][j] /= div;
	}
}

void Graph::ResetRowsToZero(AdjacencyMatrix& extendedMatrix, const size_t& currentRow)
{
	for (size_t j = 0; j < extendedMatrix.size(); ++j)
	{
		if (j != currentRow)
		{
			const double factor = extendedMatrix[j][currentRow];
			for (size_t k = 0; k < extendedMatrix.size() * 2; ++k)
			{
				extendedMatrix[j][k] -= factor * extendedMatrix[currentRow][k];
			}
		}
	}
}

void Graph::ExtractInvertedMatrix(AdjacencyMatrix& invertedMatrix, const AdjacencyMatrix& extendedMatrix)
{
	invertedMatrix.resize(extendedMatrix.size());
	for (size_t i = 0; i < extendedMatrix.size(); ++i)
	{
		invertedMatrix[i].resize(extendedMatrix[i].size());
		for (size_t j = 0; j < extendedMatrix.size(); ++j)
		{
			invertedMatrix[i][j] = extendedMatrix[i][j + extendedMatrix.size()];
		}
	}
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