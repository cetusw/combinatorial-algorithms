#include "Network.h"

#include <fstream>
#include <iostream>
#include <sstream>

Network::Network() = default;

void Network::ReadNetworkFromFile(const std::string& filename)
{
	std::ifstream inputFile(filename);
	std::string line;

	size_t totalVertices = 0;
	while (std::getline(inputFile, line))
	{
		totalVertices++;
	}

	inputFile.clear();
	inputFile.seekg(0);

	for (size_t i = 0; i < totalVertices; ++i)
	{
		AddVertex();
	}

	size_t row = 0;
	while (std::getline(inputFile, line))
	{
		std::istringstream stringStreamLine(line);
		int capacity;
		size_t col = 0;
		while (stringStreamLine >> capacity)
		{
			if (row != col && capacity > 0)
			{
				AddEdge(row, col, capacity);
			}
			col++;
		}
		row++;
	}
}

void Network::AddEdge(size_t source, size_t destination, int capacity)
{
	m_edges.emplace_back(source, destination, capacity);
	m_graph[source].push_back(m_edges.size() - 1);
	m_edges.emplace_back(destination, source, 0);
	m_graph[destination].push_back(m_edges.size() - 1);
}

void Network::AddVertex()
{
	m_graph.resize(m_graph.size() + 1);
}

size_t Network::GetNumberOfVertices() const { return m_graph.size(); }

size_t Network::GetEdgeSource(const size_t edge) const { return m_edges[edge].source; }

size_t Network::  GetEdgeDestination(const size_t edge) const { return m_edges[edge].destination; }

int Network::GetEdgeCapacity(const size_t edge) const { return m_edges[edge].capacity; }

int Network::GetEdgeFlow(const size_t edge) const { return m_edges[edge].flow; }

size_t Network::GetNumberOfEdges() const
{
	return m_edges.size();
}

std::vector<size_t> Network::GetEdgesFrom(const size_t vertex) const
{
	if (vertex >= m_graph.size())
	{
		throw std::out_of_range("Vertex out of range graph");
	}
	return m_graph[vertex];
}

void Network::SetEdgeFlow(const size_t edge, const int flow) { m_edges[edge].flow = flow; }
