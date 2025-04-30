//
// Created by cetus on 4/3/25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "../Edge/Edge.h"
#include "../Face/Face.h"
#include "../Vertex/Vertex.h"

#include <limits>
#include <memory>
#include <unordered_set>
#include <vector>

using AdjacencyMatrix = std::vector<std::vector<int>>;
inline int INF = std::numeric_limits<int>::max();

class Graph
{
public:
	Graph();

	void ReadGraphFromFile(std::istream& file);

	std::shared_ptr<Vertex> AddVertex(int id);
	EdgePtr AddEdge(
		const std::shared_ptr<Vertex>& startVertex, const std::shared_ptr<Vertex>& endVertex);
	std::shared_ptr<Face> AddFace(const std::vector<std::shared_ptr<Vertex>>& vertices);

	void RemoveVertex(const std::shared_ptr<Vertex>& vertexToRemove);
	void RemoveEdge(const EdgePtr& edgeToRemove);

	static Graph BuildDual(const Graph& originalGraph);
	std::vector<std::shared_ptr<Vertex>> GetSecondNeighborhood(
		const std::shared_ptr<Vertex>& source);
	void MergeVertices(
		const std::shared_ptr<Vertex>& target, const std::shared_ptr<Vertex>& toMerge);

	std::vector<std::shared_ptr<Vertex>> GetVertices();
	[[nodiscard]] std::vector<std::shared_ptr<Edge>> GetEdges() const;
	[[nodiscard]] std::vector<std::shared_ptr<Face>> GetFaces() const;

	void ProcessErshovColoring();
	void ProcessErshovFaceColoring();

	EdgePtr FindEdge(const std::shared_ptr<Vertex>& v1, const std::shared_ptr<Vertex>& v2);

private:
	std::vector<std::shared_ptr<Vertex>> m_vertices;
	std::vector<EdgePtr> m_edges;
	std::vector<std::shared_ptr<Face>> m_faces;
	int m_vertexCounter = 0;
	AdjacencyMatrix m_adjacencyMatrix;
	double m_record = INF;
};

#endif // GRAPH_H
