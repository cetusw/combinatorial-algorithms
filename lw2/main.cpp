#include "Graph.h"
#include "Types.h"
#include <iostream>

int main(const int argc, const char* argv[])
{
	Graph g;
	std::ifstream input(argv[1]);
	g.ReadGraphFromFile(input);

	ListOfEdges edges = g.AdjacencyMatrixToEdges(g.GetAdjacencyMatrix());

	Matrix matrix(g.GetAdjacencyMatrix());
	Edges path;
	int bot = 0;
	g.FindMinCycle(matrix, path, bot);

	if (g.IsCycleFound())
	{
		std::cout << g.GetCycleWeight() << " ";
		bool isStart = true;
		for (const auto& edge : g.GetCyclePath())
		{
			if (isStart)
			{
				std::cout << edge.first << " " << edge.second << " ";
				isStart = false;
			}
			else
			{
				std::cout << edge.second << " ";
			}
		}
	}
	else
	{
		std::cout << "Гамильтонов цикл не найден" << std::endl;
	}
	return 0;
}