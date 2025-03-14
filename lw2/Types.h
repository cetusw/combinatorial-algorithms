// Types.h
#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <array>

using ListOfEdges = std::vector<std::array<int, 3>>;
using AdjacencyMatrix = std::vector<std::vector<int>>;
using Edges = std::vector<int>;

struct HamiltonianCycleResult {
	std::vector<int> path;
	int totalWeight;
	bool found;
};

#endif // TYPES_H
