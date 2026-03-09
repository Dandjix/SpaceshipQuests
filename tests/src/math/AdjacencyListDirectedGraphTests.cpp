//
// Created by timon on 3/9/26.
//

#include <gtest/gtest.h>

#include "math/AdjacencyListDirectedGraph.h"

TEST(AdjacencyListDirectedGraphTestSuite, GraphSimpleTest) {
    auto graph = AdjacencyListDirectedGraph<int>();

    graph.addVertex(1);
    graph.addVertex(2);

    graph.addEdge(1, 2);

    ASSERT_TRUE(graph.hasVertex(1));
    ASSERT_TRUE(graph.hasVertex(2));

    ASSERT_TRUE(graph.hasEdge(1,2));
    ASSERT_FALSE(graph.hasEdge(2,1));

    ASSERT_FALSE(graph.hasEdge(3,4));

    ASSERT_THROW(graph.addEdge(5,6), std::out_of_range);
}
