#include "Edge.h"

Edge::Edge(const std::shared_ptr<Vertex>& start, const std::shared_ptr<Vertex>& end)
	: m_start(start)
	, m_end(end)
	, m_next(nullptr)
	, m_prev(nullptr)
	, m_isMerged(false)
{
}

std::shared_ptr<Vertex> Edge::GetStart() const { return m_start; }
std::shared_ptr<Vertex> Edge::GetEnd() const { return m_end; }
Edge* Edge::GetNext() const { return m_next; }
Edge* Edge::GetPrev() const { return m_prev; }
std::shared_ptr<Face> Edge::GetLeftFace() const { return m_leftFace; }
std::shared_ptr<Face> Edge::GetRightFace() const { return m_rightFace; }
bool Edge::GetIsMerged() const { return m_isMerged; }

void Edge::SetStart(const std::shared_ptr<Vertex>& newStart) { m_start = newStart; }
void Edge::SetEnd(const std::shared_ptr<Vertex>& newEnd) { m_end = newEnd; }
void Edge::SetNext(Edge* newNext) { m_next = newNext; }
void Edge::SetPrev(Edge* newPrev) { m_prev = newPrev; }
void Edge::SetLeftFace(const std::shared_ptr<Face>& newFace) { m_leftFace = newFace; }
void Edge::SetRightFace(const std::shared_ptr<Face>& newFace) { m_rightFace = newFace; }
void Edge::SetIsMerged(const bool isMerged) { m_isMerged = isMerged; }
