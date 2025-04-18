#include "Graph/Graph.h"
#include "Vertex/Vertex.h"

#include <iostream>
int main()
{
	Graph graph;
	const std::shared_ptr<Vertex> A = graph.AddVertex(0);
	const std::shared_ptr<Vertex> B = graph.AddVertex(1);
	const std::shared_ptr<Vertex> C = graph.AddVertex(2);
	const std::shared_ptr<Vertex> D = graph.AddVertex(3);
	const std::shared_ptr<Vertex> E = graph.AddVertex(4);

	graph.AddEdge(A, B);
	graph.AddEdge(B, C);
	graph.AddEdge(C, D);
	graph.AddEdge(D, E);
	graph.AddEdge(A, C);
	graph.AddEdge(B, D);

	const std::shared_ptr<Vertex> F = graph.AddVertex(5);
	const std::shared_ptr<Vertex> G = graph.AddVertex(6);
	graph.AddEdge(F, G);
	graph.AddEdge(G, E);

	std::cout << "Before coloring:\n";
	for (const auto& v : graph.GetVertices())
	{
		std::cout << "Vertex " << v->GetId() << " color: " << v->GetColor() << "\n";
	}

	graph.ProcessErshovColoring();

	std::cout << "\nFace colors:\n";
	std::cout << graph.GetFaces().size() << std::endl;
	for (const auto& v : graph.GetVertices())
	{
		std::cout << "Vertex " << v->GetId() << " color: " << v->GetColor() << "\n";
	}

	return 0;
}