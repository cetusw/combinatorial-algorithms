#include "Graph.h"
#include "../Face/Face.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>

Graph::Graph() = default;

void Graph::ReadGraphFromFile(std::istream& file)
{
	m_faces.clear();
	m_vertices.clear();
	m_edges.clear();

	int faceId = 0;
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::vector<std::shared_ptr<Vertex>> faceVertices;
		int vertexId;

		while (ss >> vertexId)
		{
			auto it = std::ranges::find_if(
				m_vertices, [vertexId](const auto& v) { return v->GetId() == vertexId; });

			if (it != m_vertices.end())
			{
				faceVertices.push_back(*it);
			}
			else
			{
				auto newVertex = AddVertex(vertexId);
				faceVertices.push_back(newVertex);
			}
		}

		std::vector<std::shared_ptr<Edge>> faceEdges;
		const size_t n = faceVertices.size();

		auto newFace = std::make_shared<Face>(faceVertices, ++faceId);
		m_faces.push_back(newFace);

		for (size_t i = 0; i < n; ++i)
		{
			auto& v1 = faceVertices[i];
			auto& v2 = faceVertices[(i + 1) % n];

			std::shared_ptr<Edge> existingEdge = FindEdge(v1, v2);

			if (!existingEdge)
			{
				std::shared_ptr<Edge> newEdge = AddEdge(v1, v2);
				newEdge->SetLeftFace(m_faces.back());
				faceEdges.push_back(newEdge);
			}
			else
			{
				existingEdge->SetRightFace(m_faces.back());
				faceEdges.push_back(existingEdge);
			}
		}
	}
}

std::shared_ptr<Edge> Graph::FindEdge(const std::shared_ptr<Vertex>& v1, const std::shared_ptr<Vertex>& v2)
{
	for (const auto& edge : m_edges)
	{
		if ((edge->GetStart() == v1 && edge->GetEnd() == v2)
			|| (edge->GetStart() == v2 && edge->GetEnd() == v1))
		{
			return edge;
		}
	}
	return nullptr;
}

std::shared_ptr<Vertex> Graph::AddVertex(int id)
{
	auto v = std::make_shared<Vertex>(id);
	m_vertices.push_back(v);
	return v;
}

std::shared_ptr<Edge> Graph::AddEdge(
	const std::shared_ptr<Vertex>& startVertex, const std::shared_ptr<Vertex>& endVertex)
{
	if (startVertex == endVertex) return nullptr;
	if (FindEdge(startVertex, endVertex)) return nullptr;
	auto e = std::make_unique<Edge>(startVertex, endVertex);
	m_edges.push_back(std::move(e));
	std::shared_ptr<Edge> edgePtr = m_edges.back();

	startVertex->AddIncidentalEdge(edgePtr);
	endVertex->AddIncidentalEdge(edgePtr);

	return edgePtr;
}
std::shared_ptr<Face> Graph::AddFace(const std::vector<std::shared_ptr<Vertex>>& vertices)
{
	static int faceIdCounter = 0;
	const auto face = std::make_shared<Face>(vertices, faceIdCounter++);
	m_faces.push_back(face);
	return face;
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

void Graph::RemoveEdge(const std::shared_ptr<Edge>& edgeToRemove)
{
	const auto it = std::ranges::remove_if(m_edges, [edgeToRemove](const std::shared_ptr<Edge>& e) {
		return e == edgeToRemove;
	}).begin();
	m_edges.erase(it, m_edges.end());

	edgeToRemove->GetStart()->RemoveIncidentalEdge(edgeToRemove);
	edgeToRemove->GetEnd()->RemoveIncidentalEdge(edgeToRemove);
}

Graph Graph::BuildDual(const Graph& originalGraph)
{
	Graph dual;
	std::unordered_map<std::shared_ptr<Face>, std::shared_ptr<Vertex>> faceToVertex;

	for (const auto& face : originalGraph.GetFaces())
	{
		const auto dualVertex = dual.AddVertex(face->GetId());
		faceToVertex[face] = dualVertex;
	}

	for (const auto& edge : originalGraph.GetEdges())
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
	std::unordered_set<std::shared_ptr<Vertex>> directNeighbors{};
	std::unordered_set<std::shared_ptr<Vertex>> secondNeighbors{};

	if (std::ranges::find(m_vertices, source) == m_vertices.end())
	{
		return {};
	}

	for (const std::shared_ptr<Edge>& edge : source->GetIncidentalEdges())
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

		for (const std::shared_ptr<Edge>& edge : directNeighbor->GetIncidentalEdges())
		{
			std::shared_ptr<Vertex> candidate
				= (edge->GetStart() == directNeighbor) ? edge->GetEnd() : edge->GetStart();

			if (candidate != source
				&& !directNeighbors.contains(candidate)
				&& std::ranges::find(m_vertices, candidate) != m_vertices.end()
				&& !candidate->GetIsMerged())
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

	for (const auto& edge : target->GetIncidentalEdges())
	{
		auto neighbor = edge->GetStart() == target ? edge->GetEnd() : edge->GetStart();
		if (!FindEdge(target, neighbor))
		{
			AddEdge(target, neighbor);
		}
		RemoveEdge(edge);
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

		auto secondNeighbors = GetSecondNeighborhood(startVertex);
		while (!secondNeighbors.empty())
		{
			for (const auto& candidate : secondNeighbors)
			{
				if (!processed.contains(candidate))
				{
					candidate->SetColor(currentColor);
					MergeVertices(startVertex, candidate);
					processed.insert(candidate);
					secondNeighbors = GetSecondNeighborhood(startVertex);
					break;
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