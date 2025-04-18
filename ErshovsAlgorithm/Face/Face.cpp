#include "Face.h"
#include "../Consts.h"
#include <utility>

Face::Face(std::list<EdgePtr> edges, const int newId)
	: m_edges(std::move(edges))
	, m_color(NO_COLOR)
	, m_id(newId)
{
}

void Face::AddEdge(const EdgePtr& newEdge) { m_edges.push_back(newEdge); }
std::list<EdgePtr>& Face::GetEdges() { return m_edges; }
int Face::GetId() const { return m_id; }
int Face::GetColor() const { return m_color; }
void Face::SetColor(const int newColor) { m_color = newColor; }
void Face::SetId(const int newId) { m_id = newId; }