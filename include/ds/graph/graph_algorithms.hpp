#pragma once

#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

namespace ds::graph {

template <typename Weight>
std::vector<std::size_t> bfs(const AdjacencyListGraph<Weight>& graph, std::size_t start) {
    if (start >= graph.vertexCount()) {
        throw std::out_of_range("start vertex out of range");
    }

    std::vector<std::size_t> order;
    std::vector<bool> visited(graph.vertexCount(), false);
    std::queue<std::size_t> pending;

    visited[start] = true;
    pending.push(start);

    while (!pending.empty()) {
        const std::size_t current = pending.front();
        pending.pop();
        order.push_back(current);

        for (const auto& edge : graph.neighbors(current)) {
            if (!visited[edge.to]) {
                visited[edge.to] = true;
                pending.push(edge.to);
            }
        }
    }

    return order;
}

template <typename Weight>
void dfsVisit(const AdjacencyListGraph<Weight>& graph, std::size_t vertex, std::vector<bool>& visited, std::vector<std::size_t>& order) {
    visited[vertex] = true;
    order.push_back(vertex);

    for (const auto& edge : graph.neighbors(vertex)) {
        if (!visited[edge.to]) {
            dfsVisit(graph, edge.to, visited, order);
        }
    }
}

template <typename Weight>
std::vector<std::size_t> dfs(const AdjacencyListGraph<Weight>& graph, std::size_t start) {
    if (start >= graph.vertexCount()) {
        throw std::out_of_range("start vertex out of range");
    }

    std::vector<std::size_t> order;
    std::vector<bool> visited(graph.vertexCount(), false);
    dfsVisit(graph, start, visited, order);
    return order;
}

template <typename Weight>
std::vector<Weight> dijkstra(const AdjacencyListGraph<Weight>& graph, std::size_t start) {
    if (start >= graph.vertexCount()) {
        throw std::out_of_range("start vertex out of range");
    }

    const Weight inf = std::numeric_limits<Weight>::max();
    std::vector<Weight> distance(graph.vertexCount(), inf);
    using State = std::pair<Weight, std::size_t>;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pending;

    distance[start] = Weight{};
    pending.push({Weight{}, start});

    while (!pending.empty()) {
        const auto [currentDistance, vertex] = pending.top();
        pending.pop();

        if (currentDistance != distance[vertex]) {
            continue;
        }

        for (const auto& edge : graph.neighbors(vertex)) {
            if (distance[vertex] == inf) {
                continue;
            }
            const Weight candidate = static_cast<Weight>(distance[vertex] + edge.weight);
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                pending.push({candidate, edge.to});
            }
        }
    }

    return distance;
}

template <typename Weight>
std::vector<std::size_t> topologicalSort(const AdjacencyListGraph<Weight>& graph) {
    if (!graph.isDirected()) {
        throw std::logic_error("topological sort requires a directed graph");
    }

    std::vector<std::size_t> indegree(graph.vertexCount(), 0);
    for (std::size_t vertex = 0; vertex < graph.vertexCount(); ++vertex) {
        for (const auto& edge : graph.neighbors(vertex)) {
            ++indegree[edge.to];
        }
    }

    std::queue<std::size_t> pending;
    for (std::size_t vertex = 0; vertex < indegree.size(); ++vertex) {
        if (indegree[vertex] == 0) {
            pending.push(vertex);
        }
    }

    std::vector<std::size_t> order;
    while (!pending.empty()) {
        const std::size_t current = pending.front();
        pending.pop();
        order.push_back(current);

        for (const auto& edge : graph.neighbors(current)) {
            --indegree[edge.to];
            if (indegree[edge.to] == 0) {
                pending.push(edge.to);
            }
        }
    }

    if (order.size() != graph.vertexCount()) {
        throw std::logic_error("graph contains a cycle");
    }

    return order;
}

}  // namespace ds::graph
