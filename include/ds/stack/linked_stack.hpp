#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ds::stack {

template <typename T>
class LinkedStack {
public:
    LinkedStack() = default;

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    void push(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(top_);
        top_ = std::move(newNode);
        ++size_;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty stack");
        }

        T removed = top_->value;
        top_ = std::move(top_->next);
        --size_;
        return removed;
    }

    [[nodiscard]] const T& top() const {
        if (empty()) {
            throw std::out_of_range("top on empty stack");
        }
        return top_->value;
    }

private:
    struct Node {
        explicit Node(const T& value) : value(value) {}

        T value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> top_;
    std::size_t size_ = 0;
};

}  // namespace ds::stack
