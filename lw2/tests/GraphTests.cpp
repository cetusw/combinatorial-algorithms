#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include <catch2/catch_approx.hpp>
#include "../Graph.h"
#include <vector>

TEST_CASE("FindMinHamiltonianCycle TEST") {
    SECTION("Граф с двумя вершинами") {
        Graph g;
        g.AddEdge(0, 1, 10);
        g.AddEdge(1, 0, 15);
        auto [path, totalWeight, found] = g.FindMinHamiltonianCycle();

        REQUIRE(found);
        REQUIRE(totalWeight == 25);
        REQUIRE(path == std::vector<int>{0, 1, 0});
    }

    SECTION("Три вершины с несколькими циклами") {
        Graph g;
        g.AddEdge(0, 1, 1);
        g.AddEdge(1, 2, 2);
        g.AddEdge(2, 0, 3);
        g.AddEdge(0, 2, 10);
        g.AddEdge(2, 1, 5);
        auto [path, totalWeight, found] = g.FindMinHamiltonianCycle();

        REQUIRE(found);
        REQUIRE(totalWeight == 6);
        REQUIRE(path == std::vector<int>{0, 1, 2, 0});
    }

    SECTION("Нет цикла") {
        Graph g;
        g.AddEdge(0, 1, 1);
        g.AddEdge(1, 2, 2);
        auto result = g.FindMinHamiltonianCycle();

        REQUIRE_FALSE(result.found);
    }

    SECTION("Меньше 2 вершин") {
        Graph g;
        g.AddEdge(0, 0, 0);
        REQUIRE_THROWS_AS(g.FindMinHamiltonianCycle(), std::invalid_argument);
    }

	SECTION("Граф с большим количеством вершин и рёбер") {
    	Graph g;
    	g.AddEdge(0, 1, 1);
    	g.AddEdge(1, 2, 2);
    	g.AddEdge(2, 3, 3);
    	g.AddEdge(3, 4, 4);
    	g.AddEdge(4, 0, 5);
    	g.AddEdge(0, 2, 6);
    	g.AddEdge(1, 3, 7);
    	g.AddEdge(2, 4, 8);
    	g.AddEdge(3, 0, 9);
    	g.AddEdge(4, 1, 10);
    	auto [path, totalWeight, found] = g.FindMinHamiltonianCycle();

    	REQUIRE(found);
    	REQUIRE(totalWeight == 15);
    	REQUIRE(path == std::vector<int>{0, 1, 2, 3, 4, 0});
    }

	SECTION("Граф с несколькими вершинами и несколькими циклами с одинаковым весом") {
    	Graph g;
    	g.AddEdge(0, 1, 1);
    	g.AddEdge(1, 2, 1);
    	g.AddEdge(2, 3, 1);
    	g.AddEdge(3, 0, 1);
    	g.AddEdge(0, 2, 1);
    	g.AddEdge(1, 3, 1);
    	auto [path, totalWeight, found] = g.FindMinHamiltonianCycle();

    	REQUIRE(found);
    	REQUIRE(totalWeight == 4);
    	REQUIRE((path == std::vector<int>{0, 1, 2, 3, 0} || path == std::vector<int>{0, 2, 1, 3, 0}));
    }
}
