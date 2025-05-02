#ifndef VERTEX_H
#define VERTEX_H

#include "../Edge/Edge.h"
#include <vector>

class Vertex
{
public:
	explicit Vertex(int newId);

	void AddIncidentalEdge(const std::shared_ptr<Edge>& newEdge);
	void RemoveIncidentalEdge(const std::shared_ptr<Edge>& edgeToRemove);

	[[nodiscard]] int GetId() const;
	[[nodiscard]] int GetColor() const;
	[[nodiscard]] std::vector<std::shared_ptr<Edge>> GetIncidentalEdges() const;
	[[nodiscard]] bool GetIsMerged() const;

	void SetColor(int newColor);
	void SetId(int newId);
	void SetIsMerged(bool isMerged);

private:
	int m_id;
	int m_color;
	std::vector<std::shared_ptr<Edge>> m_incidentEdges;
	bool m_isMerged;
};

#endif // VERTEX_H
