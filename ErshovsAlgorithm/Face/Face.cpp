#include "Face.h"
#include "../Consts.h"
#include <utility>

Face::Face(std::vector<std::shared_ptr<Vertex>> vertices, const int newId)
	: m_vertices(std::move(vertices))
	, m_color(NO_COLOR)
	, m_id(newId)
{
}

std::vector<std::shared_ptr<Vertex>>& Face::GetVertices() { return m_vertices; }
int Face::GetId() const { return m_id; }
int Face::GetColor() const { return m_color; }
void Face::SetColor(const int newColor) { m_color = newColor; }
void Face::SetId(const int newId) { m_id = newId; }