#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>

namespace ds::linear_list {

template <typename T>
class SinglyLinkedList {
public:
    SinglyLinkedList() = default;

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        if (empty()) {
            tail_ = newNode.get();
        } else {
            newNode->next = std::move(head_);
        }
        head_ = std::move(newNode);
        ++size_;
    }

    void push_back(const T& value) {
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

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("insert index out of range");
        }

        if (index == 0) {
            push_front(value);
            return;
        }

        if (index == size_) {
            push_back(value);
            return;
        }

        Node* previous = nodeAt(index - 1);
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(previous->next);
        previous->next = std::move(newNode);
        ++size_;
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front on empty list");
        }

        T removed = head_->value;
        head_ = std::move(head_->next);
        --size_;

        if (empty()) {
            tail_ = nullptr;
        }

        return removed;
    }

    T erase(std::size_t index) {
        checkIndex(index);

        if (index == 0) {
            return pop_front();
        }

        Node* previous = nodeAt(index - 1);
        std::unique_ptr<Node> removed = std::move(previous->next);
        previous->next = std::move(removed->next);

        if (previous->next == nullptr) {
            tail_ = previous;
        }

        --size_;
        return removed->value;
    }

    [[nodiscard]] std::optional<std::size_t> find(const T& value) const noexcept {
        Node* current = head_.get();
        std::size_t index = 0;

        while (current != nullptr) {
            if (current->value == value) {
                return index;
            }
            current = current->next.get();
            ++index;
        }

        return std::nullopt;
    }

    [[nodiscard]] const T& at(std::size_t index) const {
        return nodeAt(index)->value;
    }

    T& at(std::size_t index) {
        return nodeAt(index)->value;
    }

    void set(std::size_t index, const T& value) {
        at(index) = value;
    }

private:
    struct Node {
        explicit Node(const T& value) : value(value) {}

        T value;
        std::unique_ptr<Node> next;
    };

    [[nodiscard]] Node* nodeAt(std::size_t index) {
        checkIndex(index);

        Node* current = head_.get();
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current;
    }

    [[nodiscard]] const Node* nodeAt(std::size_t index) const {
        checkIndex(index);

        const Node* current = head_.get();
        for (std::size_t i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current;
    }

    void checkIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
    }

    std::unique_ptr<Node> head_;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};

}  // namespace ds::linear_list
