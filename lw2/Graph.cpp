#include "Graph.h"

#include <algorithm>

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
		if (line.empty())
		{
			continue;
		}
		std::stringstream ss(line);
		if (ss >> u >> v >> w)
		{
			AddEdge(u, v, w);
			edgeCount--;
		}
	}
}

void Graph::ProcessDFS(const int vertex, std::vector<bool>& visited)
{
	visited[vertex] = true;
	std::cout << vertex << " ";
	discoveryFinishTimes[vertex].first = ++timeCounter;

	for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i)
	{
		if (adjacencyMatrix[vertex][i] != NO_EDGE && !visited[i])
		{
			ProcessDFS(i, visited);
		}
	}

	discoveryFinishTimes[vertex].second = ++timeCounter;
}

void Graph::DFS(const int startVertex)
{
	std::vector visited(numVertices, false);
	discoveryFinishTimes.resize(numVertices, { 0, 0 });
	timeCounter = 0;

	if (startVertex >= 0 && startVertex < numVertices && !visited[startVertex])
	{
		ProcessDFS(startVertex, visited);
	}

	for (int i = 0; i < numVertices; ++i)
	{
		if (!visited[i])
		{
			ProcessDFS(i, visited);
		}
	}

	std::cout << std::endl;
}

HamiltonianCycleResult Graph::FindMinHamiltonianCycle() const
{
	HamiltonianCycleResult result;
	result.found = false;
	result.totalWeight = std::numeric_limits<int>::max();

	if (numVertices <= 1)
	{
		throw std::invalid_argument("Граф содержит менее 2 вершин");
	}

	std::vector<int> vertices;
	for (int i = 1; i < numVertices; ++i)
	{
		vertices.push_back(i);
	}

	do
	{
		std::vector<int> currentPath;
		currentPath.push_back(0);
		currentPath.insert(currentPath.end(), vertices.begin(), vertices.end());
		currentPath.push_back(0);

		bool valid = true;
		int currentWeight = 0;

		for (size_t i = 0; i < currentPath.size() - 1; ++i)
		{
			const int u = currentPath[i];
			const int v = currentPath[i + 1];

			if (adjacencyMatrix[u][v] == NO_EDGE)
			{
				valid = false;
				break;
			}
			currentWeight += adjacencyMatrix[u][v];
		}

		if (valid && currentWeight < result.totalWeight)
		{
			result.path = currentPath;
			result.totalWeight = currentWeight;
			result.found = true;
		}

	} while (std::ranges::next_permutation(vertices).found);

	return result;
}

void Graph::PrintDiscoveryFinishTimes() const
{
	std::cout << "Время первого и повторного захода в вершину:" << std::endl;
	for (size_t i = 0; i < discoveryFinishTimes.size(); ++i)
	{
		std::cout << "Вершина " << i << ": [" << discoveryFinishTimes[i].first << ", "
				  << discoveryFinishTimes[i].second << "]" << std::endl;
	}
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
		for (int j = 0; j < vertexesCount; j++)
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