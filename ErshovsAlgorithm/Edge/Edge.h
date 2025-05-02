#ifndef EDGE_H
#define EDGE_H
#include <memory>

class Vertex;
class Edge;
class Face;

class Edge
{
public:
	Edge(const std::shared_ptr<Vertex>& start, const std::shared_ptr<Vertex>& end);

	[[nodiscard]] std::shared_ptr<Vertex> GetStart() const;
	[[nodiscard]] std::shared_ptr<Vertex> GetEnd() const;
	[[nodiscard]] std::shared_ptr<Face> GetLeftFace() const;
	[[nodiscard]] std::shared_ptr<Face> GetRightFace() const;
	[[nodiscard]] bool GetIsMerged() const;

	void SetStart(const std::shared_ptr<Vertex>& newStart);
	void SetEnd(const std::shared_ptr<Vertex>& newEnd);
	void SetLeftFace(const std::shared_ptr<Face>& newFace);
	void SetRightFace(const std::shared_ptr<Face>& newFace);
	void SetIsMerged(bool isMerged);

private:
	std::shared_ptr<Vertex> m_start;
	std::shared_ptr<Vertex> m_end;
	std::shared_ptr<Face> m_leftFace;
	std::shared_ptr<Face> m_rightFace;
	bool m_isMerged;
};

#endif // EDGE_H
