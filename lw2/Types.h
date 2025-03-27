// Types.h
#ifndef TYPES_H
#define TYPES_H

#include <array>
#include <limits>
#include <vector>

using ListOfEdges = std::vector<std::array<int, 3>>;
using AdjacencyMatrix = std::vector<std::vector<int>>;
using Edges = std::vector<std::pair<int, int>>;
inline int INF = std::numeric_limits<int>::max();

struct HamiltonianCycleResult {
	Edges path;
	int totalWeight;
	bool found;
};

struct ZeroInfo {
	size_t row;
	size_t col;
	double penalty;
};

#endif // TYPES_H
