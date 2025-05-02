#ifndef FACE_H
#define FACE_H

#include "../Vertex/Vertex.h"

class Face
{
public:
	explicit Face(std::vector<std::shared_ptr<Vertex>> vertices, int newId);
	void AddVertex(const std::shared_ptr<Edge>& newEdge);

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
