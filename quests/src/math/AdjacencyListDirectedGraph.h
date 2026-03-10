//
// Created by timon on 3/9/26.
//

#pragma once

#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <vector>
#include <algorithm>

namespace Quests::Math {
    template<typename T_Vertex, typename T_Edge>
    /// <summary>
    /// A graph made for representing a quest's stages. Connections are one way.
    /// </summary>
    class AdjacencyListDirectedGraph {
    private:
        std::unordered_set<T_Vertex> connected_recursive(const std::unordered_set<T_Vertex> &vertices,
                                                         int graphDistance) const {
            if (graphDistance == 1) {
                std::unordered_set<T_Vertex> adjacentVertices;
                for (auto vertex: vertices) {
                    //if (adjacencyListMap.find(vertex) == adjacencyListMap.end())
                    //{
                    //	continue;
                    //}
                    const std::vector<T_Vertex> &it = adjacencyListMap.at(vertex);
                    for (T_Vertex vert: it) {
                        adjacentVertices.insert(vert);
                    }
                }
                return adjacentVertices;
            }
            std::unordered_set<T_Vertex> next = connected_recursive(vertices, graphDistance - 1);
            std::unordered_set<T_Vertex> adjacentVertices = next;
            for (auto &vertex: next) {
                const auto &neighbors = adjacencyListMap.at(vertex);
                for (const auto &pair: neighbors) {
                    adjacentVertices.insert(pair.first);
                }
            }
            return adjacentVertices;
        }

    protected:
        std::unordered_map<T_Vertex, std::vector<std::pair<T_Vertex, T_Edge> > > adjacencyListMap;

    public:
        AdjacencyListDirectedGraph() = default;

        ~AdjacencyListDirectedGraph() = default;

        void addVertex(T_Vertex vertex) {
            // if (adjacencyListMap.contains(vertex))
            //     throw std::runtime_error("Vertex is already in the map");
            adjacencyListMap[vertex] = std::vector<std::pair<T_Vertex, T_Edge> >();
        }

        void removeVertex(T_Vertex vertex) {
            adjacencyListMap.erase(vertex);
        }

        bool hasVertex(T_Vertex vertex) const {
            return adjacencyListMap.contains(vertex);
        }

        void addEdge(T_Vertex from, T_Vertex to, T_Edge edge) {
            auto &adj_list_1 = adjacencyListMap.at(from);
            adj_list_1.push_back({to, edge});
        }


        void removeEdge(T_Vertex from, T_Vertex to) {
            auto &adj_list_1 = adjacencyListMap.at(from);
            adj_list_1.erase(
                std::remove_if(adj_list_1.begin(), adj_list_1.end(),
                               //edge pair is a pair with first the destination vertex and second the value associated with the edge
                               [&to](const std::pair<T_Vertex, T_Edge> &edge_pair) {
                                   return edge_pair.first == to;
                               }),
                adj_list_1.end()
            );
        }

        /**
         * Checks and returns the edge AB between two vertices A and B (directional)
         * @param from vertex A
         * @param to vertex B
         * @param edge the value associated with AB is written to this address. If you only want to check edge existence,
         * leave this at nullptr
         * @return true iff the edge AB exists
         */
        bool getEdge(T_Vertex from, T_Vertex to, T_Edge *edge = nullptr) const {
            if (!adjacencyListMap.contains(from)) return false;
            const std::vector<std::pair<T_Vertex, T_Edge> > &accessible = adjacencyListMap.at(from);
            auto it = std::find_if(accessible.begin(), accessible.end(),
                                   [&to]
                           (std::pair<T_Vertex, T_Edge> vertex_edge_pair) {
                                       return vertex_edge_pair.first == to;
                                   });
            if (it == accessible.end()) return false;
            if (edge != nullptr)*edge = it->second;
            return true;
        }


        std::unordered_set<T_Vertex> connected(T_Vertex vertex, int graphDistance = 1) const {
            if (graphDistance < 1) {
                throw std::invalid_argument("graphDistance must be at least 1");
            }

            std::unordered_set<T_Vertex> vertices = {vertex};

            auto result = connected_recursive(vertices, graphDistance);
            result.erase(vertex);
            return result;
        }

        std::vector<T_Vertex> getVertices() const {
            std::vector<T_Vertex> vertices;
            vertices.reserve(adjacencyListMap.size());
            for (auto it = adjacencyListMap.begin(); it != adjacencyListMap.end(); it++) {
                vertices.push_back(it->first);
            }
            return vertices;
        }
    };
}
