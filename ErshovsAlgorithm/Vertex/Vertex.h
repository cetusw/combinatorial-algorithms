#ifndef VERTEX_H
#define VERTEX_H
#include <vector>

#include "../Edge/Edge.h"

class Vertex
{
public:
	explicit Vertex(int newId);

	void AddIncidentalEdge(const EdgePtr& newEdge);
	void RemoveIncidentalEdge(const EdgePtr& edgeToRemove);

	[[nodiscard]] int GetId() const;
	[[nodiscard]] int GetColor() const;
	[[nodiscard]] std::vector<EdgePtr> GetIncidentalEdges() const;
	[[nodiscard]] bool GetIsMerged() const;

	void SetColor(int newColor);
	void SetId(int newId);
	void SetIsMerged(bool isMerged);

private:
	int m_id;
	int m_color;
	std::vector<EdgePtr> m_incidentEdges;
	bool m_isMerged;
};

#endif // VERTEX_H
