#ifndef RABINVAZIRANI_H
#define RABINVAZIRANI_H
#include <vector>

#include "Graph.h"

class RabinVazirani
{
public:
	Pairs FindMaximumMatching(const Graph& graph);
	void FindMatching(size_t rows, const Pairs& edges, AdjacencyMatrix& tutteMatrix,
		std::vector<bool>& used, Pairs& matches);

private:
	static double GetRandomDouble();
	static AdjacencyMatrix GetTutteMatrix(const AdjacencyMatrix& matrix);

	Graph m_graph;
};

#endif // RABINVAZIRANI_H
