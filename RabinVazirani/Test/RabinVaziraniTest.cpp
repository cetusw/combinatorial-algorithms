#include "../Graph.h"
#include "../RabinVazirani.h"
#include <gtest/gtest.h>

constexpr std::string DIR = "../Test/data/";

void RabinVaziraniTest(const std::string& filename, const Pairs& expectedPairs)
{
	Graph graph;
	graph.ReadGraphFromFile(DIR + filename);

	RabinVazirani rabinVazirani;
	const Pairs maxMatching = rabinVazirani.FindMaximumMatching(graph);

	EXPECT_EQ(expectedPairs, maxMatching);
}

TEST(RabinVazirani, Ordinary) { RabinVaziraniTest("ordinaryGraph.txt", { { 0, 2 }, { 1, 3 } }); }
TEST(RabinVazirani, K5) { RabinVaziraniTest("fullGraph.txt", {{0, 1}, {2, 5}, {4, 3}}); }
TEST(RabinVazirani, Line) { RabinVaziraniTest("lineGraph.txt", {{0, 1}, {2, 3}}); }
TEST(RabinVazirani, Cycle) { RabinVaziraniTest("cycleGraph.txt", {{0, 1}, {2, 3}}); }