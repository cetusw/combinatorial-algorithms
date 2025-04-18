#include "Vertex.h"
#include "../Consts.h"

Vertex::Vertex(const int newId)
	: m_id(newId)
	, m_color(NO_COLOR)
	, m_isMerged(false)
{
}

void Vertex::AddIncidentalEdge(const EdgePtr& newEdge) { m_incidentEdges.push_back(newEdge); }

void Vertex::RemoveIncidentalEdge(const EdgePtr& edgeToRemove)
{
	const auto it = std::ranges::find(m_incidentEdges, edgeToRemove);
	if (it != m_incidentEdges.end())
	{
		m_incidentEdges.erase(it);
	}
}

int Vertex::GetId() const { return m_id; }

int Vertex::GetColor() const { return m_color; }

std::vector<EdgePtr> Vertex::GetIncidentalEdges() const { return m_incidentEdges; }
bool Vertex::GetIsMerged() const { return m_isMerged; }

void Vertex::SetColor(const int newColor) { m_color = newColor; }
void Vertex::SetId(const int newId) { m_id = newId; }
void Vertex::SetIsMerged(const bool isMerged) { m_isMerged = isMerged; }
