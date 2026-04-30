#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds::graph {

template <typename Weight = int>
class AdjacencyMatrixGraph {
public:
    explicit AdjacencyMatrixGraph(std::size_t vertexCount, bool directed = false)
        : matrix_(vertexCount, std::vector<std::optional<Weight>>(vertexCount, std::nullopt)),
          directed_(directed) {}

    [[nodiscard]] std::size_t vertexCount() const noexcept {
        return matrix_.size();
    }

    [[nodiscard]] bool isDirected() const noexcept {
        return directed_;
    }

    void addEdge(std::size_t from, std::size_t to, const Weight& weight = Weight{1}) {
        checkVertex(from);
        checkVertex(to);
        matrix_[from][to] = weight;
        if (!directed_) {
            matrix_[to][from] = weight;
        }
    }

    [[nodiscard]] bool hasEdge(std::size_t from, std::size_t to) const {
        checkVertex(from);
        checkVertex(to);
        return matrix_[from][to].has_value();
    }

    [[nodiscard]] std::optional<Weight> weight(std::size_t from, std::size_t to) const {
        checkVertex(from);
        checkVertex(to);
        return matrix_[from][to];
    }

    [[nodiscard]] std::vector<std::pair<std::size_t, Weight>> neighbors(std::size_t vertex) const {
        checkVertex(vertex);
        std::vector<std::pair<std::size_t, Weight>> result;
        for (std::size_t to = 0; to < matrix_[vertex].size(); ++to) {
            if (matrix_[vertex][to].has_value()) {
                result.emplace_back(to, *matrix_[vertex][to]);
            }
        }
        return result;
    }

private:
    void checkVertex(std::size_t vertex) const {
        if (vertex >= matrix_.size()) {
            throw std::out_of_range("vertex out of range");
        }
    }

    std::vector<std::vector<std::optional<Weight>>> matrix_;
    bool directed_;
};

}  // namespace ds::graph
