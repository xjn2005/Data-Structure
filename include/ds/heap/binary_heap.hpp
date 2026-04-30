#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds::heap {

template <typename T, typename Compare = std::less<T>>
class BinaryHeap {
public:
    BinaryHeap() = default;

    explicit BinaryHeap(const std::vector<T>& values) : data_(values) {
        buildHeap();
    }

    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    [[nodiscard]] const T& top() const {
        if (empty()) {
            throw std::out_of_range("top on empty heap");
        }
        return data_.front();
    }

    void push(const T& value) {
        data_.push_back(value);
        siftUp(data_.size() - 1);
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty heap");
        }

        T result = data_.front();
        data_.front() = data_.back();
        data_.pop_back();
        if (!empty()) {
            siftDown(0);
        }
        return result;
    }

    [[nodiscard]] const std::vector<T>& data() const noexcept {
        return data_;
    }

private:
    void buildHeap() {
        for (std::size_t i = data_.size() / 2; i > 0; --i) {
            siftDown(i - 1);
        }
    }

    void siftUp(std::size_t index) {
        while (index > 0) {
            const std::size_t parent = (index - 1) / 2;
            if (!comp_(data_[parent], data_[index])) {
                break;
            }
            std::swap(data_[parent], data_[index]);
            index = parent;
        }
    }

    void siftDown(std::size_t index) {
        while (true) {
            std::size_t selected = index;
            const std::size_t left = index * 2 + 1;
            const std::size_t right = index * 2 + 2;

            if (left < data_.size() && comp_(data_[selected], data_[left])) {
                selected = left;
            }
            if (right < data_.size() && comp_(data_[selected], data_[right])) {
                selected = right;
            }
            if (selected == index) {
                break;
            }

            std::swap(data_[index], data_[selected]);
            index = selected;
        }
    }

    std::vector<T> data_;
    Compare comp_;
};

}  // namespace ds::heap
