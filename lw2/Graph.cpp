#include "Graph.h"

Graph::Graph() = default;

void Graph::AddEdge(const int u, const int v, const int w)
{
	const int maxVertex = std::max(u, v);
	const int requiredSize = maxVertex + 1;

	if (requiredSize > numVertices)
	{
		adjacencyMatrix.resize(requiredSize);
		for (auto& row : adjacencyMatrix)
		{
			row.resize(requiredSize, NO_EDGE);
		}
		numVertices = requiredSize;
	}

	adjacencyMatrix[u][v] = w;
}

void Graph::ReadGraphFromFile(std::ifstream& file)
{
	adjacencyMatrix.clear();
	int edgeCount;
	file >> edgeCount;
	std::string line;
	int u, v, w;
	while (std::getline(file, line) && edgeCount >= 0)
	{
		std::stringstream ss(line);
		ss >> u >> v >> w;
		AddEdge(u, v, w);
		edgeCount--;
	}
}

void Graph::processDFS(const int vertex, std::vector<bool>& visited)
{
	visited[vertex] = true;
	std::cout << vertex << " ";

	for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i)
	{
		if (adjacencyMatrix[vertex][i] != NO_EDGE && !visited[i])
		{
			processDFS(i, visited);
		}
	}
}

void Graph::DFS(const int startVertex)
{
	std::vector visited(numVertices, false);
	processDFS(startVertex, visited);
	std::cout << std::endl;
}

AdjacencyMatrix Graph::EdgesToAdjacencyMatrix(const ListOfEdges& listOfEdges)
{
	if (listOfEdges.empty())
	{
		adjacencyMatrix.clear();
	}

	for (const auto& edge : listOfEdges)
	{
		const int u = edge[0];
		const int v = edge[1];
		const int weight = edge[2];
		adjacencyMatrix[u][v] = weight;
	}

	return adjacencyMatrix;
}

ListOfEdges Graph::AdjacencyMatrixToEdges(const AdjacencyMatrix& adjacencyMatrix)
{
	ListOfEdges edges;
	const int vertexesCount = static_cast<int>(adjacencyMatrix.size());
	for (int i = 0; i < vertexesCount; i++)
	{
		for (int j = i + 1; j < vertexesCount; j++)
		{
			if (adjacencyMatrix[i][j] != NO_EDGE)
			{
				edges.push_back({ i, j, adjacencyMatrix[i][j] });
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

AdjacencyMatrix Graph::GetAdjacencyMatrix() { return adjacencyMatrix; }