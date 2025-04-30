#include "../Graph/Graph.h"
#include <gtest/gtest.h>

#include <fstream>

constexpr std::string DIR = "../Test/data/";

void ErshovAlgorithmTest(const std::string& fileName, const std::vector<int>& expectedFaces)
{
	Graph graph;
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
	}
	graph.ReadGraphFromFile(file);
	graph.ProcessErshovFaceColoring();
	std::vector<int> resultFaces;
	for (const auto& face : graph.GetFaces())
	{
		resultFaces.push_back(face->GetColor());
	}
	EXPECT_EQ(expectedFaces, resultFaces);
}

TEST(ErshovAlgorithm, EmptyGraph) { ErshovAlgorithmTest(DIR + "emptyGraph.txt", {}); }

TEST(ErshovAlgorithm, TriangleGraph)
{
	ErshovAlgorithmTest(DIR + "triangleGraph.txt", { 1, 2 });
}

TEST(ErshovAlgorithm, ManyTriangleGraph)
{
	ErshovAlgorithmTest(DIR + "testTrianglesGraph.txt", { 1, 2, 1, 3 });
}

TEST(ErshovAlgorithm, PlanarGraph)
{
	ErshovAlgorithmTest(DIR + "planarGraph.txt", { 1, 2, 3, 4, 5, 4, 3, 1, 2, 5 });
}

TEST(ErshovAlgorithm, K5Graph)
{
	ErshovAlgorithmTest(DIR + "k5Graph.txt", { 1, 2, 1, 3, 2, 3, 4 });
}

TEST(ErshovAlgorithm, WithBridgeGraph)
{
	ErshovAlgorithmTest(DIR + "withBridgeGraph.txt", { 1, 2, 3, 4 });
}