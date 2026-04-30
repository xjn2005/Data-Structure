#include <iostream>

#include "ds/graph/adjacency_matrix_graph.hpp"

int main() {
    ds::graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 3, 2);

    for (std::size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        std::cout << vertex << ": ";
        for (const auto& [to, weight] : graph.neighbors(vertex)) {
            std::cout << '(' << to << ',' << weight << ") ";
        }
        std::cout << '\n';
    }

    return 0;
}
