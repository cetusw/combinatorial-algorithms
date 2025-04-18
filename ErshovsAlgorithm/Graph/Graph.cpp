#include "Graph.h"
#include "../Face/Face.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>

Graph::Graph() = default;

void Graph::ReadGraphFromFile(std::istream& file)
{
	m_adjacencyMatrix.clear();

	int numVertices, edgeCount;
	file >> numVertices >> edgeCount;

	m_adjacencyMatrix.resize(numVertices, std::vector(numVertices, INF));

	int u, v;
	for (int i = 0; i < edgeCount; ++i)
	{
		file >> u >> v;
		AddEdge(AddVertex(u), AddVertex(v));
	}
}

std::shared_ptr<Vertex> Graph::AddVertex(int id)
{
	auto v = std::make_shared<Vertex>(id);
	m_vertices.push_back(v);
	return v;
}

EdgePtr Graph::AddEdge(
	const std::shared_ptr<Vertex>& startVertex, const std::shared_ptr<Vertex>& endVertex)
{
	auto e = std::make_unique<Edge>(startVertex, endVertex);
	m_edges.push_back(std::move(e));
	EdgePtr edgePtr = m_edges.back();

	startVertex->AddIncidentalEdge(edgePtr);
	endVertex->AddIncidentalEdge(edgePtr);

	return edgePtr;
}
std::shared_ptr<Face> Graph::AddFace(std::shared_ptr<Face> edges)
{
	static int faceIdCounter = 0;
	edges->SetId(faceIdCounter++);
	m_faces.push_back(edges);
	return edges;
}

void Graph::RemoveVertex(const std::shared_ptr<Vertex>& vertexToRemove)
{
	const auto edges = vertexToRemove->GetIncidentalEdges();
	while (!edges.empty())
	{
		RemoveEdge(edges.front());
	}

	const auto it
		= std::ranges::remove_if(m_vertices, [vertexToRemove](const std::shared_ptr<Vertex>& v) {
			  return v == vertexToRemove;
		  }).begin();
	m_vertices.erase(it, m_vertices.end());
}

void Graph::RemoveEdge(const EdgePtr& edgeToRemove)
{
	const auto it = std::ranges::remove_if(m_edges, [edgeToRemove](const std::shared_ptr<Edge>& e) {
		return e == edgeToRemove;
	}).begin();
	m_edges.erase(it, m_edges.end());

	edgeToRemove->GetStart()->RemoveIncidentalEdge(edgeToRemove);
	edgeToRemove->GetEnd()->RemoveIncidentalEdge(edgeToRemove);
}

Graph Graph::BuildDual(const Graph& original)
{
	Graph dual;
	std::unordered_map<std::shared_ptr<Face>, std::shared_ptr<Vertex>> faceToVertex;

	for (const auto& face : original.GetFaces())
	{
		const auto dualVertex = dual.AddVertex(face->GetId());
		faceToVertex[face] = dualVertex;
	}

	for (const auto& edge : original.GetEdges())
	{
		auto leftFace = edge->GetLeftFace();
		auto rightFace = edge->GetRightFace();

		if (leftFace && rightFace)
		{
			dual.AddEdge(faceToVertex[leftFace], faceToVertex[rightFace]);
		}
	}

	return dual;
}

std::vector<std::shared_ptr<Vertex>> Graph::GetSecondNeighborhood(
	const std::shared_ptr<Vertex>& source)
{
	std::unordered_set<std::shared_ptr<Vertex>> directNeighbors;
	std::unordered_set<std::shared_ptr<Vertex>> secondNeighbors;

	if (std::ranges::find(m_vertices, source) == m_vertices.end())
	{
		return {};
	}

	for (const EdgePtr& edge : source->GetIncidentalEdges())
	{
		const std::shared_ptr<Vertex> neighbor
			= (edge->GetStart() == source) ? edge->GetEnd() : edge->GetStart();
		directNeighbors.insert(neighbor);
	}

	for (const std::shared_ptr<Vertex>& directNeighbor : directNeighbors)
	{
		if (std::ranges::find(m_vertices, directNeighbor) == m_vertices.end())
		{
			continue;
		}

		for (const EdgePtr& edge : directNeighbor->GetIncidentalEdges())
		{
			std::shared_ptr<Vertex> candidate
				= (edge->GetStart() == directNeighbor) ? edge->GetEnd() : edge->GetStart();

			if (candidate != source && !directNeighbors.contains(candidate)
				&& std::ranges::find(m_vertices, candidate) != m_vertices.end())
			{
				secondNeighbors.insert(candidate);
			}
		}
	}

	return { secondNeighbors.begin(), secondNeighbors.end() };
}

void Graph::MergeVertices(
	const std::shared_ptr<Vertex>& target, const std::shared_ptr<Vertex>& toMerge)
{
	if (target == toMerge || toMerge->GetIsMerged())
	{
		return;
	}

	for (const auto& edge : toMerge->GetIncidentalEdges())
	{
		auto neighbor = edge->GetStart() == toMerge ? edge->GetEnd() : edge->GetStart();
		AddEdge(target, neighbor);
		edge->SetIsMerged(true);
	}

	toMerge->SetIsMerged(true);
}

std::vector<std::shared_ptr<Vertex>> Graph::GetVertices() { return m_vertices; }

std::vector<std::shared_ptr<Edge>> Graph::GetEdges() const { return m_edges; }
std::vector<std::shared_ptr<Face>> Graph::GetFaces() const { return m_faces; }

void Graph::ProcessErshovColoring()
{
	int currentColor = 0;
	std::unordered_set<std::shared_ptr<Vertex>> processed;

	while (processed.size() < m_vertices.size())
	{
		std::shared_ptr<Vertex> startVertex = nullptr;
		for (const auto& v : m_vertices)
		{
			if (!processed.contains(v))
			{
				startVertex = v;
				break;
			}
		}
		if (!startVertex)
		{
			break;
		}

		currentColor++;

		startVertex->SetColor(currentColor);
		processed.insert(startVertex);

		std::queue<std::shared_ptr<Vertex>> queue;
		auto secondNeighbors = GetSecondNeighborhood(startVertex);
		for (const auto& neighbor : secondNeighbors)
		{
			if (!processed.contains(neighbor))
			{
				queue.push(neighbor);
			}
		}

		while (!queue.empty())
		{
			auto candidate = queue.front();
			queue.pop();
			if (processed.contains(candidate))
			{
				continue;
			}

			candidate->SetColor(currentColor);
			MergeVertices(startVertex, candidate);
			processed.insert(candidate);

			auto newNeighbors = GetSecondNeighborhood(startVertex);
			for (const auto& v : newNeighbors)
			{
				if (!processed.contains(v) && v != startVertex)
				{
					queue.push(v);
				}
			}
		}
	}
}

void Graph::ProcessErshovFaceColoring()
{
	Graph dual = BuildDual(*this);

	dual.ProcessErshovColoring();

	std::unordered_map<std::shared_ptr<Face>, std::shared_ptr<Vertex>> faceToDualVertex;
	for (const auto& face : m_faces)
	{
		for (const auto& dualVertex : dual.GetVertices())
		{
			if (dualVertex->GetId() == face->GetId())
			{
				faceToDualVertex[face] = dualVertex;
				break;
			}
		}
	}

	for (auto& face : m_faces)
	{
		if (faceToDualVertex.contains(face))
		{
			face->SetColor(faceToDualVertex[face]->GetColor());
		}
	}
}

void Graph::DefineFaces()
{
	std::unordered_set<EdgePtr> visitedEdges;
	for (const auto& edge : m_edges)
	{
		if (visitedEdges.contains(edge))
		{
			continue;
		}

		std::vector<EdgePtr> cycle;
		if (FindCycleDFS(edge->GetStart(), nullptr, visitedEdges, cycle))
		{
		}
	}
}

bool Graph::FindCycleDFS(const std::shared_ptr<Vertex>& current,
	const std::shared_ptr<Vertex>& parent, std::unordered_set<EdgePtr>& visitedEdges,
	std::vector<EdgePtr>& cycle)
{
	for (const auto& edge : current->GetIncidentalEdges())
	{
		if (visitedEdges.contains(edge))
		{
			continue;
		}

		auto neighbor = (edge->GetStart() == current) ? edge->GetEnd() : edge->GetStart();

		if (neighbor == parent)
		{
			continue;
		}

		if (visitedEdges.insert(edge).second)
		{
			cycle.push_back(edge);
			if (FindCycleDFS(neighbor, current, visitedEdges, cycle))
			{
				return true;
			}
			cycle.pop_back();
		}
		else
		{
			cycle.push_back(edge);
			return true;
		}
	}
	return false;
}