//
// Created by timon on 3/9/26.
//

#pragma once

#include <list>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <unordered_set>
#include <vector>

template<typename T>
/// <summary>
/// A graph made for representing a quest's stages. Connections are one way.
/// </summary>
class AdjacencyListDirectedGraph {
private:
    std::unordered_set<T> connected_recursive(const std::unordered_set<T> &vertices, int graphDistance) const {
        if (graphDistance == 1) {
            std::unordered_set<T> adjacentVertices;
            for (auto vertex: vertices) {
                //if (adjacencyListMap.find(vertex) == adjacencyListMap.end())
                //{
                //	continue;
                //}
                const std::vector<T> &it = adjacencyListMap.at(vertex);
                for (T vert: it) {
                    adjacentVertices.insert(vert);
                }
            }
            return adjacentVertices;
        }
        std::unordered_set<T> next = connected_recursive(vertices, graphDistance - 1);
        std::unordered_set<T> adjacentVertices = next;
        for (auto &vertex: next) {
            const auto &neighbors = adjacencyListMap.at(vertex);
            for (const auto &pair: neighbors) {
                adjacentVertices.insert(pair.first);
            }
        }
        return adjacentVertices;
    }

protected:
    std::unordered_map<T, std::vector<T> > adjacencyListMap;

public:
    AdjacencyListDirectedGraph() = default;

    ~AdjacencyListDirectedGraph() = default;

    void addVertex(T vertex) {
        // if (adjacencyListMap.contains(vertex))
        //     throw std::runtime_error("Vertex is already in the map");
        adjacencyListMap[vertex] = std::vector<T>();
    }

    void removeVertex(T vertex) {
        adjacencyListMap.erase(vertex);
    }

    bool hasVertex(T vertex) const {
        return adjacencyListMap.contains(vertex);
    }

    void addEdge(T from, T to) {
        auto &adj_list_1 = adjacencyListMap.at(from);
        adj_list_1.push_back(to);
    }

    void removeEdge(T vertex1, T vertex2) {
        auto &adj_list_1 = adjacencyListMap[vertex1];
        adj_list_1.remove_if([&](const std::pair<T, int> &edge) {
            return edge.first == vertex2;
        });
    }

    bool hasEdge(T from, T to) const {
        if (!adjacencyListMap.contains(from)) return false;
        const std::vector<T> &accessible = adjacencyListMap.at(from);
        return std::find(accessible.begin(), accessible.end(), to) != accessible.end();
    }

    std::unordered_set<T> connected(T vertex, int graphDistance = 1) const {
        if (graphDistance < 1) {
            throw std::invalid_argument("graphDistance must be at least 1");
        }

        std::unordered_set<T> vertices = {vertex};

        auto result = connected_recursive(vertices, graphDistance);
        result.erase(vertex);
        return result;
    }

    std::vector<T> getVertices() const {
        std::vector<T> vertices;
        vertices.reserve(adjacencyListMap.size());
        for (auto it = adjacencyListMap.begin(); it != adjacencyListMap.end(); it++) {
            vertices.push_back(it->first);
        }
        return vertices;
    }
};
