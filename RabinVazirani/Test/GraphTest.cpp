#include <gtest/gtest.h>
#include "../Graph.h"

TEST(GraphTest, GetTranspose) {
    Graph graph;
	const AdjacencyMatrix matrix = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    const AdjacencyMatrix expected = {
        {1.0, 4.0, 7.0},
        {2.0, 5.0, 8.0},
        {3.0, 6.0, 9.0}
    };
    EXPECT_EQ(graph.GetTranspose(matrix), expected);
}

TEST(GraphTest, GetMinor) {
    Graph graph;
    const AdjacencyMatrix matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const AdjacencyMatrix minor = graph.GetMinor(matrix, 0, 1);
    const AdjacencyMatrix expected = {
        {4, 6},
        {7, 9}
    };
    EXPECT_EQ(minor, expected);
}

TEST(GraphTest, GetDeterminant) {
    Graph graph;
    const AdjacencyMatrix m1 = {{5.0}};
    EXPECT_DOUBLE_EQ(graph.GetDeterminant(m1), 5.0);

    const AdjacencyMatrix m2 = {{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_DOUBLE_EQ(graph.GetDeterminant(m2), -2.0);

    const AdjacencyMatrix m3 = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    EXPECT_NEAR(graph.GetDeterminant(m3), 0.0, 1e-6);
}

TEST(GraphTest, GetInvertedMatrix) {
    Graph graph;
    const AdjacencyMatrix original = {{1.0, 2.0}, {3.0, 4.0}};
	AdjacencyMatrix inverted;
    ASSERT_TRUE(graph.GetInvertedMatrix(original, inverted));

	AdjacencyMatrix product(2, std::vector(2, 0.0));
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                product[i][j] += original[i][k] * inverted[k][j];
            }
        }
    }

    EXPECT_NEAR(product[0][0], 1.0, 1e-6);
    EXPECT_NEAR(product[1][1], 1.0, 1e-6);
    EXPECT_NEAR(product[0][1], 0.0, 1e-6);
    EXPECT_NEAR(product[1][0], 0.0, 1e-6);

    const AdjacencyMatrix singular = {{1.0, 2.0}, {2.0, 4.0}};
    EXPECT_FALSE(graph.GetInvertedMatrix(singular, inverted));
}
