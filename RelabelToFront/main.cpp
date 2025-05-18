#include "Network.h"
#include "RelabelToFront.h"

#include <iostream>
#include <ostream>
int main()
{
	try
	{
		Network network;
		network.ReadNetworkFromFile("../networkExample.txt");
		// std::cout << network.GetNumberOfVertices() << std::endl;

		RelabelToFront relabelToFront;
		const int maxFlow = relabelToFront.FindMaximumFlow(network);
		std::cout << "Максимальный поток: " << maxFlow << std::endl;
	} catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}