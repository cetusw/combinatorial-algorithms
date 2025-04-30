#include "Graph/Graph.h"
#include "Vertex/Vertex.h"

#include <fstream>
#include <iostream>
int main()
{
	Graph graph;
	std::ifstream file("../graph.txt");
	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
	}
	graph.ReadGraphFromFile(file);

	std::cout << "Before coloring:" << std::endl;
	for (const auto& v : graph.GetVertices())
	{
		std::cout << "Vertex " << v->GetId() << " color: " << v->GetColor() << "\n";
	}

	graph.ProcessErshovFaceColoring();

	std::cout << std::endl << "Face colors:" << std::endl;
	std::cout << graph.GetFaces().size() << std::endl;
	for (const auto& face : graph.GetFaces())
	{
		std::cout << "Face " << face->GetId() << " color: " << face->GetColor() << "\n";
	}

	return 0;
}