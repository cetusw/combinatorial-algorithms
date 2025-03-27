#include "Graph.h"
#include "Matrix.h"

#include <algorithm>
#include <numeric>

Graph::Graph() = default;

void Graph::AddEdge(const int u, const int v, const int w)
{
	const int maxVertex = std::max(u, v);
	const int requiredSize = maxVertex + 1;

	if (requiredSize > m_numVertices)
	{
		m_adjacencyMatrix.resize(requiredSize);
		for (auto& row : m_adjacencyMatrix)
		{
			row.resize(requiredSize, NO_EDGE);
		}
		m_numVertices = requiredSize;
	}

	m_adjacencyMatrix[u][v] = w;
	m_adjacencyMatrix[v][u] = w;
}

void Graph::ReadGraphFromFile(std::ifstream& file)
{
	m_adjacencyMatrix.clear();

	int numVertices, edgeCount;
	file >> numVertices >> edgeCount;

	m_adjacencyMatrix.resize(numVertices, std::vector(numVertices, INF));

	int u, v, w;
	for (int i = 0; i < edgeCount; ++i)
	{
		file >> u >> v >> w;
		m_adjacencyMatrix[u][v] = w;
		m_adjacencyMatrix[v][u] = w;
	}
}

void Graph::PrintDiscoveryFinishTimes() const
{
	std::cout << "Время первого и повторного захода в вершину:" << std::endl;
	for (size_t i = 0; i < m_discoveryFinishTimes.size(); ++i)
	{
		std::cout << "Вершина " << i << ": [" << m_discoveryFinishTimes[i].first << ", "
				  << m_discoveryFinishTimes[i].second << "]" << std::endl;
	}
}

AdjacencyMatrix Graph::EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges)
{
	if (listOfEdges.empty())
	{
		m_adjacencyMatrix.clear();
	}

	for (const auto& edge : listOfEdges)
	{
		const int u = edge[0];
		const int v = edge[1];
		const int weight = edge[2];
		m_adjacencyMatrix[u][v] = weight;
	}

	return m_adjacencyMatrix;
}

ListOfEdges Graph::AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix)
{
	ListOfEdges edges;
	const int vertexesCount = static_cast<int>(adjacencyMatrix.size());
	for (int i = 0; i < vertexesCount; i++)
	{
		for (int j = 0; j < vertexesCount; j++)
		{
			if (adjacencyMatrix[i][j] != NO_EDGE)
			{
				edges.push_back(
					{ i, j, adjacencyMatrix[i][j] });
			}
		}
	}
	return edges;
}

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

void Graph::PrintListOfEdges(const ListOfEdges& edges)
{
	for (const auto& edge : edges)
	{
		std::cout << edge[0] << "	" << edge[1] << "	" << edge[2] << std::endl;
	}
	std::cout << std::endl;
}

int Graph::SubtractFromMatrix(Matrix& matrix)
{
	int totalReduction = 0;
	const size_t size = matrix.GetSize();

	for (size_t row = 0; row < size; ++row)
	{
		int minVal = INF;
		for (size_t col = 0; col < size; ++col)
		{
			if (matrix(row, col) < minVal)
			{
				minVal = matrix(row, col);
			}
		}

		if (minVal != INF && minVal != 0)
		{
			for (size_t col = 0; col < size; ++col)
			{
				if (matrix(row, col) != INF)
				{
					matrix(row, col) -= minVal;
				}
			}
			totalReduction += minVal;
		}
	}

	for (size_t col = 0; col < size; ++col)
	{
		int minVal = INF;
		for (size_t row = 0; row < size; ++row)
		{
			if (matrix(row, col) < minVal)
			{
				minVal = matrix(row, col);
			}
		}

		if (minVal != INF && minVal != 0)
		{
			for (size_t row = 0; row < size; ++row)
			{
				if (matrix(row, col) != INF)
				{
					matrix(row, col) -= minVal;
				}
			}
			totalReduction += minVal;
		}
	}

	return totalReduction;
}

std::vector<ZeroInfo> Graph::FindBestZeros(const Matrix& matrix)
{
	std::vector<ZeroInfo> zeros;
	const size_t size = matrix.GetSize();

	for (size_t row = 0; row < size; ++row)
	{
		for (size_t col = 0; col < size; ++col)
		{
			if (matrix(row, col) == 0)
			{
				int row_min = INF;
				int col_min = INF;

				for (size_t c = 0; c < size; ++c)
				{
					if (c != col && matrix(row, c) < row_min)
					{
						row_min = matrix(row, c);
					}
				}

				for (size_t r = 0; r < size; ++r)
				{
					if (r != row && matrix(r, col) < col_min)
					{
						col_min = matrix(r, col);
					}
				}

				const int penalty
					= (row_min == INF ? 0 : row_min) + (col_min == INF ? 0 : col_min);
				zeros.push_back({ row, col, penalty });
			}
		}
	}

	std::ranges::sort(
		zeros, [](const ZeroInfo& a, const ZeroInfo& b) { return a.penalty > b.penalty; });

	return zeros;
}

void Graph::AddInfinity(Matrix& matrix)
{
	const size_t size = matrix.GetSize();

	if (size < 2)
	{
		return;
	}

	const size_t lastRemovedRow = matrix.GetLastRemovedRow();
	const size_t lastRemovedCol = matrix.GetLastRemovedColumn();

	const size_t currentRow = matrix.FindCurrentRowIndex(lastRemovedCol);
	const size_t currentCol = matrix.FindCurrentColumnIndex(lastRemovedRow);

	if (currentRow != static_cast<size_t>(-1) && currentCol != static_cast<size_t>(-1))
	{
		matrix(currentRow, currentCol) = INF;
	}
}

void Graph::FindMinCycle(const Matrix& m, const Edges& path, int& bottomLimit)
{
	if (m.GetSize() < 2)
	{
		if (path.size() == m_numVertices - 1)
		{
			const size_t startVertex = path.front().first;
			const size_t endVertex = path.back().second;

			if (m_adjacencyMatrix[startVertex][endVertex] != INF)
			{
				const int totalWeight = bottomLimit + m_adjacencyMatrix[startVertex][endVertex];
				if (totalWeight < m_record)
				{
					m_record = totalWeight;
					m_bestCycle.path = path;
					m_bestCycle.path.emplace_back(endVertex, startVertex);
					m_bestCycle.totalWeight = totalWeight;
					m_bestCycle.found = true;
				}
			}
		}
		return;
	}
	if (m.GetSize() == 2)
	{
		const int a = m(0, 1);
		const int b = m(1, 0);

		if (a != INF && b != INF)
		{
			auto newPath = path;
			newPath.emplace_back(m.RowIndex(0), m.ColumnIndex(1));
			newPath.emplace_back(m.RowIndex(1), m.ColumnIndex(0));

			const int totalWeight = bottomLimit + a + b;

			if (totalWeight < m_record)
			{
				m_record = totalWeight;
				m_bestCycle.path = newPath;
				m_bestCycle.totalWeight = totalWeight;
				m_bestCycle.found = true;
			}
		}
		return;
	}
	Matrix matrix(m);
	bottomLimit += SubtractFromMatrix(matrix);
	if (bottomLimit > m_record)
	{
		return;
	}

	const auto zeros = FindBestZeros(matrix);
	if (zeros.empty())
	{
		return;
	}
	const auto edge = zeros.front();
	auto newMatrix(matrix);
	newMatrix.RemoveRowColumn(edge.row, edge.col);
	auto newPath(path);
	newPath.emplace_back(matrix.RowIndex(edge.row), matrix.ColumnIndex(edge.col));
	AddInfinity(newMatrix);
	FindMinCycle(newMatrix, newPath, bottomLimit);
	newMatrix = matrix;
	newMatrix(edge.row, edge.col) = INF;
	FindMinCycle(newMatrix, path, bottomLimit);
}

bool Graph::IsCycleFound() const { return m_bestCycle.found; }

int Graph::GetCycleWeight() const { return m_bestCycle.totalWeight; }

const Edges& Graph::GetCyclePath() const { return m_bestCycle.path; }

AdjacencyMatrix Graph::GetAdjacencyMatrix() { return m_adjacencyMatrix; }