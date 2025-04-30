#ifndef FACE_H
#define FACE_H

#include "../Interface/IGraphElement.h"
#include "../Vertex/Vertex.h"

#include <list>

class Face : public IGraphElement
{
public:
	explicit Face(std::vector<std::shared_ptr<Vertex>> vertices, int newId);
	void AddVertex(const EdgePtr& newEdge);

	std::vector<std::shared_ptr<Vertex>>& GetVertices();
	[[nodiscard]] int GetId() const;
	[[nodiscard]] int GetColor() const;

	void SetColor(int newColor);
	void SetId(int newId);

private:
	std::vector<std::shared_ptr<Vertex>> m_vertices;
	int m_color;
	int m_id;
};

#endif // FACE_H
