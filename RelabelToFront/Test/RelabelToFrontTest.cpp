#include "../Network.h"
#include "../RelabelToFront.h"
#include <gtest/gtest.h>

#include <fstream>

constexpr std::string DIR = "../Test/data/";

void RelabelToFrontTest(const std::string& fileName, const int expectedMaxFlow)
{
	Network network;
	network.ReadNetworkFromFile(fileName);

	RelabelToFront relabelToFront;
	const int maxFlow = relabelToFront.FindMaximumFlow(network);\

	EXPECT_EQ(expectedMaxFlow, maxFlow);
}

TEST(RelabelToFront, EmptyGraph) { RelabelToFrontTest(DIR + "emptyGraph.txt", 0); }
TEST(RelabelToFront, OrdinaryGraph) { RelabelToFrontTest(DIR + "ordinaryGraph.txt", 15); }
TEST(RelabelToFront, CycleGraph) { RelabelToFrontTest(DIR + "cycleGraph.txt", 5); }
TEST(RelabelToFront, K5Graph) { RelabelToFrontTest(DIR + "k5Graph.txt", 939); }
TEST(RelabelToFront, K5WithReversePathsGraph) { RelabelToFrontTest(DIR + "k5WithReversePathsGraph.txt", 1040); }
TEST(RelabelToFront, LineGraph) { RelabelToFrontTest(DIR + "lineGraph.txt", 3); }
TEST(RelabelToFront, ZeroGraph) { RelabelToFrontTest(DIR + "zeroGraph.txt", 0); }
