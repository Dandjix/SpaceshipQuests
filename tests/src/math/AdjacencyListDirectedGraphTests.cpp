//
// Created by timon on 3/9/26.
//

#include <gtest/gtest.h>

#include "quests/math/AdjacencyListDirectedGraph.h"


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

TEST(AdjacencyListDirectedGraphTestSuite, EdgesFromTest) {
    auto graph = Quests::Math::AdjacencyListDirectedGraph<int, std::string>();

    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);

    graph.addEdge(1,2,"12");
    graph.addEdge(1,3,"13");
    graph.addEdge(4,1,"41");

    auto from2 = graph.getEdgesFrom(2);
    ASSERT_TRUE(from2.empty());

    auto from4 = graph.getEdgesFrom(4);
    ASSERT_EQ(from4.size(),1);
    ASSERT_EQ(from4.at(0).first,1);
    ASSERT_EQ(from4.at(0).second,"41");

    auto from1 = graph.getEdgesFrom(1);
    ASSERT_EQ(from1.size(),2);
    ASSERT_EQ(from1.at(0).first,2);
    ASSERT_EQ(from1.at(0).second,"12");
    ASSERT_EQ(from1.at(1).first,3);
    ASSERT_EQ(from1.at(1).second,"13");

}
