#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "ds/graph/adjacency_list_graph.hpp"
#include "ds/graph/adjacency_matrix_graph.hpp"
#include "ds/graph/graph_algorithms.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_adjacency_matrix_graph() {
    ds::graph::AdjacencyMatrixGraph<int> graph(4, false);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 3);

    expect(graph.hasEdge(1, 0), "undirected matrix graph should mirror edges");
    expect(graph.weight(0, 1).has_value() && *graph.weight(0, 1) == 5, "matrix graph weight should be 5");
}

void test_bfs_dfs_and_dijkstra() {
    ds::graph::AdjacencyListGraph<int> graph(5, true);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 3);
    graph.addEdge(2, 1, 4);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 7);

    expect((ds::graph::bfs(graph, 0) == std::vector<std::size_t>{0, 1, 2, 3, 4}), "bfs order should match");
    expect((ds::graph::dfs(graph, 0) == std::vector<std::size_t>{0, 1, 3, 4, 2}), "dfs order should match");

    const auto distances = ds::graph::dijkstra(graph, 0);
    expect(distances[0] == 0, "distance to source should be 0");
    expect(distances[1] == 7, "shortest path to 1 should be 7");
    expect(distances[3] == 9, "shortest path to 3 should be 9");
    expect(distances[4] == 16, "shortest path to 4 should be 16");
}

void test_topological_sort() {
    ds::graph::AdjacencyListGraph<int> dag(6, true);
    dag.addEdge(5, 2);
    dag.addEdge(5, 0);
    dag.addEdge(4, 0);
    dag.addEdge(4, 1);
    dag.addEdge(2, 3);
    dag.addEdge(3, 1);

    const auto order = ds::graph::topologicalSort(dag);
    std::vector<std::size_t> position(order.size(), 0);
    for (std::size_t i = 0; i < order.size(); ++i) {
        position[order[i]] = i;
    }

    expect(position[5] < position[2], "topological order should place 5 before 2");
    expect(position[5] < position[0], "topological order should place 5 before 0");
    expect(position[4] < position[1], "topological order should place 4 before 1");
    expect(position[2] < position[3], "topological order should place 2 before 3");
    expect(position[3] < position[1], "topological order should place 3 before 1");
}

}  // namespace

int main() {
    test_adjacency_matrix_graph();
    test_bfs_dfs_and_dijkstra();
    test_topological_sort();

    if (g_failures == 0) {
        std::cout << "[PASS] all graph tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
