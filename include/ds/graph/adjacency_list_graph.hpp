#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds::graph {

template <typename Weight = int>
class AdjacencyListGraph {
public:
    struct Edge {
        std::size_t to;
        Weight weight;
    };

    explicit AdjacencyListGraph(std::size_t vertexCount, bool directed = false)
        : adjacency_(vertexCount), directed_(directed) {}

    [[nodiscard]] std::size_t vertexCount() const noexcept {
        return adjacency_.size();
    }

    [[nodiscard]] bool isDirected() const noexcept {
        return directed_;
    }

    void addEdge(std::size_t from, std::size_t to, const Weight& weight = Weight{1}) {
        checkVertex(from);
        checkVertex(to);
        adjacency_[from].push_back({to, weight});
        if (!directed_) {
            adjacency_[to].push_back({from, weight});
        }
    }

    [[nodiscard]] const std::vector<Edge>& neighbors(std::size_t vertex) const {
        checkVertex(vertex);
        return adjacency_[vertex];
    }

private:
    void checkVertex(std::size_t vertex) const {
        if (vertex >= adjacency_.size()) {
            throw std::out_of_range("vertex out of range");
        }
    }

    std::vector<std::vector<Edge>> adjacency_;
    bool directed_;
};

}  // namespace ds::graph
