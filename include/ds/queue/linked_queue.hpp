#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>

namespace ds::queue {

template <typename T>
class LinkedQueue {
public:
    LinkedQueue() = default;

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    void push(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        Node* newTail = newNode.get();

        if (empty()) {
            head_ = std::move(newNode);
        } else {
            tail_->next = std::move(newNode);
        }

        tail_ = newTail;
        ++size_;
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("pop on empty queue");
        }

        T removed = head_->value;
        head_ = std::move(head_->next);
        --size_;

        if (empty()) {
            tail_ = nullptr;
        }

        return removed;
    }

    [[nodiscard]] const T& front() const {
        if (empty()) {
            throw std::out_of_range("front on empty queue");
        }
        return head_->value;
    }

    [[nodiscard]] const T& back() const {
        if (empty()) {
            throw std::out_of_range("back on empty queue");
        }
        return tail_->value;
    }

private:
    struct Node {
        explicit Node(const T& value) : value(value) {}

        T value;
        std::unique_ptr<Node> next;
    };

    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds::queue
