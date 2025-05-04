#include "Edge.h"

Edge::Edge(const std::shared_ptr<Vertex>& start, const std::shared_ptr<Vertex>& end)
	: m_start(start)
	, m_end(end)
{
}

std::shared_ptr<Vertex> Edge::GetStart() const { return m_start; }
std::shared_ptr<Vertex> Edge::GetEnd() const { return m_end; }
std::shared_ptr<Face> Edge::GetLeftFace() const { return m_leftFace; }
std::shared_ptr<Face> Edge::GetRightFace() const { return m_rightFace; }

void Edge::SetStart(const std::shared_ptr<Vertex>& newStart) { m_start = newStart; }
void Edge::SetEnd(const std::shared_ptr<Vertex>& newEnd) { m_end = newEnd; }
void Edge::SetLeftFace(const std::shared_ptr<Face>& newFace) { m_leftFace = newFace; }
void Edge::SetRightFace(const std::shared_ptr<Face>& newFace) { m_rightFace = newFace; }
