#include "Graph.h"
#include "RabinVazirani.h"

constexpr std::string DIR = "../Test/data/";

int main()
{
	Graph graph;
	graph.ReadGraphFromFile(DIR + "k5Graph.txt");

	RabinVazirani rabinVazirani;
	Pairs maxMatching = rabinVazirani.FindMaximumMatching(graph);

	for (const auto [source, destination] : maxMatching)
	{
		std::cout << source << " " << destination << std::endl;
	}
}