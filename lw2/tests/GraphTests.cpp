#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include "../Graph.h"
#include <vector>

TEST_CASE("Test 1: Один цикл") {
    Graph g;
    std::istringstream input(
        "4 4\n"
        "0 1 1\n"
        "1 2 1\n"
        "2 3 1\n"
        "3 0 1\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE(g.IsCycleFound());
    REQUIRE(g.GetCycleWeight() == 4);

    std::vector expected = {0, 1, 2, 3, 0};
    std::vector<int> actual;
    for (const auto& edge : g.GetCyclePath()) {
        actual.push_back(edge.first);
    }
    actual.push_back(g.GetCyclePath().back().second);

    REQUIRE(actual == expected);
}

TEST_CASE("Test 2: Граф с альтернативными путями") {
    Graph g;
    std::istringstream input(
        "4 8\n"
        "0 1 10\n"
        "0 2 5\n"
        "1 2 2\n"
        "1 3 8\n"
        "2 1 3\n"
        "2 3 4\n"
        "3 0 2\n"
        "3 1 7\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE(g.IsCycleFound());
    REQUIRE(g.GetCycleWeight() == 18);

    std::vector expected = {0, 2, 1, 3, 0};
    std::vector<int> actual;
    for (const auto& edge : g.GetCyclePath()) {
        actual.push_back(edge.first);
    }
    actual.push_back(g.GetCyclePath().back().second);

    REQUIRE(actual == expected);
}

TEST_CASE("Test 3: Несколько циклов") {
	Graph g;
	std::istringstream input(
		"4 8\n"
		"0 1 1\n"
		"1 2 1\n"
		"2 3 1\n"
		"3 0 1\n"
		"0 2 5\n"
		"2 0 5\n"
		"1 3 5\n"
		"3 1 5\n"
	);
	g.ReadGraphFromFile(input);

	Matrix matrix(g.GetAdjacencyMatrix());
	Edges path;
	int bottomLimit = 0;
	g.FindMinCycle(matrix, path, bottomLimit);

	REQUIRE(g.IsCycleFound());
	REQUIRE(g.GetCycleWeight() == 4);

	std::vector expected = {0, 2, 1, 3, 0};
	std::vector<int> actual;
	for (const auto& edge : g.GetCyclePath()) {
		actual.push_back(edge.first);
	}
	actual.push_back(g.GetCyclePath().back().second);

	REQUIRE(actual == expected);
}

TEST_CASE("Test 4: Нет цикла") {
    Graph g;
    std::istringstream input(
        "3 2\n"
        "0 1 1\n"
        "1 2 1\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE_FALSE(g.IsCycleFound());
}

TEST_CASE("Test 5: Полный граф") {
    Graph g;
    std::istringstream input(
        "3 6\n"
        "0 1 1\n"
        "1 0 2\n"
        "0 2 3\n"
        "2 0 4\n"
        "1 2 5\n"
        "2 1 6\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE(g.IsCycleFound());
    REQUIRE(g.GetCycleWeight() == 10);

	std::vector expected = {0, 1, 2, 0};
	std::vector<int> actual;
	for (const auto& edge : g.GetCyclePath()) {
		actual.push_back(edge.first);
	}
	actual.push_back(g.GetCyclePath().back().second);

	REQUIRE(actual == expected);
}

TEST_CASE("Test 6: Пустой граф") {
    Graph g;
    std::istringstream input("0 0");
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
	g.FindMinCycle(matrix, path, bottomLimit);

	REQUIRE_FALSE(g.IsCycleFound());
}

TEST_CASE("Test 7: Одна вершина") {
    Graph g;
    std::istringstream input("1 0");
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
	g.FindMinCycle(matrix, path, bottomLimit);

	REQUIRE_FALSE(g.IsCycleFound());
}

TEST_CASE("Test 8: Две вершины с циклом") {
    Graph g;
    std::istringstream input(
        "2 2\n"
        "0 1 5\n"
        "1 0 3\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE(g.IsCycleFound());
    REQUIRE(g.GetCycleWeight() == 8);

	std::vector expected = {0, 1, 0};
	std::vector<int> actual;
	for (const auto& edge : g.GetCyclePath()) {
		actual.push_back(edge.first);
	}
	actual.push_back(g.GetCyclePath().back().second);

	REQUIRE(actual == expected);
}

TEST_CASE("Test 9: Линейный граф") {
    Graph g;
    std::istringstream input(
        "4 3\n"
        "0 1 1\n"
        "1 2 1\n"
        "2 3 1\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE_FALSE(g.IsCycleFound());
}

TEST_CASE("Test 10: Граф с вершиной, в которую невозможно попасть") {
    Graph g;
    std::istringstream input(
        "4 5\n"
        "0 1 1\n"
        "1 2 1\n"
        "2 3 1\n"
        "3 1 5\n"
        "0 3 10\n"
    );
    g.ReadGraphFromFile(input);

    Matrix matrix(g.GetAdjacencyMatrix());
    Edges path;
    int bottomLimit = 0;
    g.FindMinCycle(matrix, path, bottomLimit);

    REQUIRE_FALSE(g.IsCycleFound());
}

