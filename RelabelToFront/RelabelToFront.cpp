#include "RelabelToFront.h"

#include <iomanip>
#include <iostream>
#include <list>
#include <ostream>

RelabelToFront::RelabelToFront() = default;

int RelabelToFront::FindMaximumFlow(const Network& network)
{
	m_network = network;
	InitializePreflow();

	std::vector<size_t> list;
	for (size_t vertex = 1; vertex < network.GetNumberOfVertices() - 1; vertex++)
	{
		list.push_back(vertex);
	}

	size_t i = 0;
	while (i != list.size())
	{
		size_t vertex = list[i];
		const size_t previousHeight = m_height[vertex];

		Discharge(vertex);

		if (m_height[vertex] > previousHeight)
		{
			list.erase(list.begin() + static_cast<int>(i));
			list.insert(list.begin(), vertex);
			i = 0;
		}
		else
		{
			i++;
		}
	}

	std::vector flowMatrix(
		m_network.GetNumberOfVertices(), std::vector(m_network.GetNumberOfVertices(), 0));
	for (size_t e = 0; e < m_network.GetNumberOfEdges(); ++e)
	{
		size_t u = m_network.GetEdgeSource(e);
		size_t v = m_network.GetEdgeDestination(e);
		int f = m_network.GetEdgeFlow(e);
		if (f > 0)
		{
			flowMatrix[u][v] = f;
		}
	}

	std::cout << "Максимальный поток = " << m_excessFlow[0] << "\n\n";
	std::cout << "Матрица потока:\n";
	for (int u = 0; u < m_network.GetNumberOfVertices(); ++u)
	{
		for (int v = 0; v < m_network.GetNumberOfVertices(); ++v)
		{
			std::cout << std::setw(5) << flowMatrix[u][v];
		}
		std::cout << "\n";
	}

	return m_excessFlow[0];
}

void RelabelToFront::InitializePreflow()
{
	m_height.resize(m_network.GetNumberOfVertices());
	m_excessFlow.resize(m_network.GetNumberOfVertices());
	m_current.resize(m_network.GetNumberOfVertices());

	m_height.assign(m_height.size(), 0);
	m_excessFlow.assign(m_excessFlow.size(), 0);
	m_current.assign(m_current.size(), 0);

	for (size_t vertex = 0; vertex < m_network.GetNumberOfVertices(); vertex++)
	{
		for (const size_t edge : m_network.GetEdgesFrom(vertex))
		{
			m_network.SetEdgeFlow(edge, 0);
			m_network.SetEdgeFlow(edge ^ 1, 0);
		}
	}

	for (const size_t edge : m_network.GetEdgesFrom(0))
	{
		m_network.SetEdgeFlow(edge, m_network.GetEdgeCapacity(edge));
		m_network.SetEdgeFlow(edge ^ 1, -m_network.GetEdgeCapacity(edge));
		m_excessFlow[m_network.GetEdgeDestination(edge)] = m_network.GetEdgeCapacity(edge);
		m_excessFlow[0] -= m_network.GetEdgeCapacity(edge);
	}

	m_height[0] = m_network.GetNumberOfVertices();
}
void RelabelToFront::Discharge(const size_t vertex)
{
	std::cout << "Discharging vertex: " << vertex
			  << ", excess: " << m_excessFlow[vertex]
			  << ", height: " << m_height[vertex] << std::endl;

	while (m_excessFlow[vertex] > 0)
	{
		std::cout << m_excessFlow[vertex] << std::endl;
		if (m_current[vertex] >= m_network.GetEdgesFrom(vertex).size())
		{
			Relabel(vertex);
			m_current[vertex] = 0;
		}
		else
		{
			const size_t edge = m_network.GetEdgesFrom(vertex)[m_current[vertex]];
			const size_t destination = m_network.GetEdgeDestination(edge);
			if (m_network.GetEdgeCapacity(edge) - m_network.GetEdgeFlow(edge) > 0
				&& m_height[vertex] == m_height[destination] + 1)
			{
				Push(edge);
			}
			else
			{
				m_current[vertex]++;
			}
		}
	}
}

void RelabelToFront::Relabel(const size_t vertex)
{
	size_t minimumHeight = m_height[vertex];

	for (const size_t edge : m_network.GetEdgesFrom(vertex))
	{
		if (m_network.GetEdgeCapacity(edge) - m_network.GetEdgeFlow(edge) <= 0)
		{
			continue;
		}
		const size_t destination = m_network.GetEdgeDestination(edge);
		minimumHeight = std::min(minimumHeight, m_height[destination]);
	}

	m_height[vertex] = minimumHeight + 1;
}

void RelabelToFront::Push(const size_t edge)
{
	const size_t source = m_network.GetEdgeSource(edge);
	const size_t destination = m_network.GetEdgeDestination(edge);

	const int delta = std::min(
		m_excessFlow[source], m_network.GetEdgeCapacity(edge) - m_network.GetEdgeFlow(edge));

	m_network.SetEdgeFlow(edge, m_network.GetEdgeFlow(edge) + delta);
	m_network.SetEdgeFlow(edge ^ 1, -m_network.GetEdgeFlow(edge));
	m_excessFlow[source] -= delta;
	m_excessFlow[destination] += delta;
}
