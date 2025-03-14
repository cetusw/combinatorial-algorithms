#include "Graph.h"
#include "Types.h"
#include <iostream>

int main(const int argc, const char * argv[])
{
	Graph g;
	std::ifstream input(argv[1]);
	g.ReadGraphFromFile(input);

	ListOfEdges edges = g.AdjacencyMatrixToEdges(g.GetAdjacencyMatrix());

	std::cout << "Список рёбер:\n";
	Graph::PrintListOfEdges(edges);

	AdjacencyMatrix adj = g.EdgesToAdjacencyMatrix(edges);

	std::cout << "Матрица смежности:\n";
	Graph::PrintAdjacencyMatrix(adj);

	g.DFS(8);
	g.PrintDiscoveryFinishTimes();
	std::cout << g.FindMinHamiltonianCycle().totalWeight << std::endl;

	return 0;
}