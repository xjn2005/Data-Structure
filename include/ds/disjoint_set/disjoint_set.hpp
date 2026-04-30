#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace ds::disjoint_set {

class DisjointSet {
public:
    explicit DisjointSet(std::size_t size)
        : parent_(size), rank_(size, 0), setSize_(size, 1) {
        for (std::size_t i = 0; i < size; ++i) {
            parent_[i] = i;
        }
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return parent_.size();
    }

    std::size_t find(std::size_t x) {
        checkIndex(x);
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    bool unite(std::size_t a, std::size_t b) {
        std::size_t rootA = find(a);
        std::size_t rootB = find(b);

        if (rootA == rootB) {
            return false;
        }

        if (rank_[rootA] < rank_[rootB]) {
            std::swap(rootA, rootB);
        }

        parent_[rootB] = rootA;
        setSize_[rootA] += setSize_[rootB];

        if (rank_[rootA] == rank_[rootB]) {
            ++rank_[rootA];
        }

        return true;
    }

    [[nodiscard]] bool connected(std::size_t a, std::size_t b) {
        return find(a) == find(b);
    }

    [[nodiscard]] std::size_t componentSize(std::size_t x) {
        return setSize_[find(x)];
    }

private:
    void checkIndex(std::size_t index) const {
        if (index >= parent_.size()) {
            throw std::out_of_range("index out of range");
        }
    }

    std::vector<std::size_t> parent_;
    std::vector<std::size_t> rank_;
    std::vector<std::size_t> setSize_;
};

}  // namespace ds::disjoint_set
