//
// Created by cetus on 4/3/25.
//

#ifndef FACE_H
#define FACE_H

#include "../Interface/IGraphElement.h"
#include <list>

class Face : public IGraphElement
{
public:
	explicit Face(std::list<EdgePtr> edges, int newId);
	void AddEdge(const EdgePtr& newEdge);

	std::list<EdgePtr>& GetEdges();
	[[nodiscard]] int GetId() const;
	[[nodiscard]] int GetColor() const;

	void SetColor(int newColor);
	void SetId(int newId);

private:
	std::list<EdgePtr> m_edges;
	int m_color;
	int m_id;
};

#endif // FACE_H
