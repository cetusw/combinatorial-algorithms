#include "Network.h"
#include "RelabelToFront.h"

#include <iostream>
#include <ostream>

constexpr std::string DIR = "../Test/data/";

int main()
{
	try
	{
		Network network;
		network.ReadNetworkFromFile(DIR + "k5Graph.txt");

		RelabelToFront relabelToFront;
		relabelToFront.FindMaximumFlow(network);
		relabelToFront.PrintFlowMatrix();
	} catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}