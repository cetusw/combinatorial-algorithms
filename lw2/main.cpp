#include "Graph.h"
#include "Types.h"
#include <iostream>

int main(const int argc, const char * argv[])
{
	Graph g;
	std::ifstream input(argv[1]);
	g.ReadGraphFromFile(input);

	ListOfEdges edges = g.AdjacencyMatrixToEdges(g.GetAdjacencyMatrix());

	Matrix matrix(g.GetAdjacencyMatrix());
	Edges path;
	double bot = 0;
	g.FindMinCycle(matrix, path, bot);

	if (g.IsCycleFound()) {
		std::cout << "Minimal cycle weight: " << g.GetCycleWeight() << std::endl;
		std::cout << "Path:" << std::endl;
		for (const auto& edge : g.GetCyclePath()) {
			std::cout << edge.first << " -> " << edge.second << std::endl;
		}
	} else {
		std::cout << "Hamiltonian cycle not found!" << std::endl;
	}
	return 0;
}