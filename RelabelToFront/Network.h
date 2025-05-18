#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>

struct Edge
{
	size_t source;
	size_t destination;
	int capacity;
	int flow;
	Edge(const size_t source, const size_t destination, const int capacity)
		: source(source)
		, destination(destination)
		, capacity(capacity)
		, flow(0)
	{
	}
};

class Network
{
public:
	Network();
	~Network() = default;

	void ReadNetworkFromFile(const std::string& filename);
	void AddEdge(size_t source, size_t destination, int capacity);
	void AddVertex();

	[[nodiscard]] size_t GetNumberOfVertices() const;
	[[nodiscard]] size_t GetEdgeSource(size_t edge) const;
	[[nodiscard]] size_t GetEdgeDestination(size_t edge) const;
	[[nodiscard]] int GetEdgeCapacity(size_t edge) const;
	[[nodiscard]] int GetEdgeFlow(size_t edge) const;
	[[nodiscard]] size_t GetNumberOfEdges() const;
	[[nodiscard]] std::vector<size_t> GetEdgesFrom(size_t vertex) const;
	[[nodiscard]] std::vector<size_t> GetEdgesTo(size_t vertex) const;

	void SetEdgeFlow(size_t edge, int flow);

private:
	std::vector<Edge> m_edges;
	std::vector<std::vector<size_t>> m_graph;
	std::vector<std::vector<size_t>> m_reversedGraph;
};

#endif // NETWORK_H
