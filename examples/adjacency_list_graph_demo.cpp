#include <iostream>
#include <limits>

#include "ds/graph/adjacency_list_graph.hpp"
#include "ds/graph/graph_algorithms.hpp"

template <typename T>
void printOrder(const std::vector<T>& values) {
    for (const auto& value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    ds::graph::AdjacencyListGraph<int> weightedGraph(5, true);
    weightedGraph.addEdge(0, 1, 10);
    weightedGraph.addEdge(0, 2, 3);
    weightedGraph.addEdge(2, 1, 4);
    weightedGraph.addEdge(1, 3, 2);
    weightedGraph.addEdge(2, 3, 8);
    weightedGraph.addEdge(3, 4, 7);

    std::cout << "bfs: ";
    printOrder(ds::graph::bfs(weightedGraph, 0));
    std::cout << "dfs: ";
    printOrder(ds::graph::dfs(weightedGraph, 0));

    std::cout << "dijkstra: ";
    for (const auto distance : ds::graph::dijkstra(weightedGraph, 0)) {
        if (distance == std::numeric_limits<int>::max()) {
            std::cout << "INF ";
        } else {
            std::cout << distance << ' ';
        }
    }
    std::cout << '\n';

    ds::graph::AdjacencyListGraph<int> dag(6, true);
    dag.addEdge(5, 2);
    dag.addEdge(5, 0);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);

    std::cout << "topological sort: ";
    printOrder(ds::graph::topologicalSort(dag));

    return 0;
}
