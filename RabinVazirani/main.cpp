#include "Graph.h"
#include "RabinVazirani.h"

constexpr std::string DIR = "../Test/data/";

int main()
{
	Graph graph;
	graph.ReadGraphFromFile(DIR + "superLargeGraph.txt");

	RabinVazirani rabinVazirani;
	Pairs maxMatching = rabinVazirani.FindMaximumMatching(graph);

	if (maxMatching.size() == 0)
	{
		std::cout << "В графе нет максимального паросочетания" << std::endl;
	}

	for (const auto [source, destination] : maxMatching)
	{
		std::cout << source << " " << destination << std::endl;
	}
}