//
// Created by timon on 3/9/26.
//

#include <gtest/gtest.h>

#include "math/AdjacencyListDirectedGraph.h"


TEST(AdjacencyListDirectedGraphTestSuite, GraphSimpleTest) {
    auto graph = Quests::Math::AdjacencyListDirectedGraph<int, std::string>();

    graph.addVertex(1);
    graph.addVertex(2);

    //adding edge
    graph.addEdge(1, 2, "A");

    ASSERT_TRUE(graph.hasVertex(1));
    ASSERT_TRUE(graph.hasVertex(2));

    //retrieving value
    {
        std::string edge;
        ASSERT_TRUE(graph.getEdge(1,2,&edge));
        ASSERT_EQ(edge, "A");
    }

    //only checking existence
    ASSERT_TRUE(graph.getEdge(1,2));

    //checking non-existence
    ASSERT_FALSE(graph.getEdge(2,1));
    ASSERT_FALSE(graph.getEdge(3,4));

    //throw when creating from inexistent vertex
    ASSERT_THROW(graph.addEdge(5,6,"B"), std::out_of_range);

    graph.removeEdge(1,2);

    ASSERT_FALSE(graph.getEdge(1,2));
}
