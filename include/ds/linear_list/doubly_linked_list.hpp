#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>

namespace ds::linear_list {

template <typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList() = default;

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    void push_front(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        Node* newHead = newNode.get();
        newNode->next = std::move(head_);

        if (newNode->next != nullptr) {
            newNode->next->previous = newHead;
        } else {
            tail_ = newHead;
        }

        head_ = std::move(newNode);
        ++size_;
    }

    void push_back(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        Node* newTail = newNode.get();
        newNode->previous = tail_;

        if (empty()) {
            head_ = std::move(newNode);
        } else {
            tail_->next = std::move(newNode);
        }

        tail_ = newTail;
        ++size_;
    }

    T pop_front() {
        if (empty()) {
            throw std::out_of_range("pop_front on empty list");
        }

        T removed = head_->value;
        head_ = std::move(head_->next);
        --size_;

        if (head_ != nullptr) {
            head_->previous = nullptr;
        } else {
            tail_ = nullptr;
        }

        return removed;
    }

    T pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back on empty list");
        }

        T removed = tail_->value;

        if (size_ == 1) {
            head_.reset();
            tail_ = nullptr;
        } else {
            tail_ = tail_->previous;
            tail_->next.reset();
        }

        --size_;
        return removed;
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

        Node* current = nodeAt(index);
        Node* previous = current->previous;
        auto newNode = std::make_unique<Node>(value);
        Node* inserted = newNode.get();

        newNode->previous = previous;
        newNode->next = std::move(previous->next);
        newNode->next->previous = inserted;
        previous->next = std::move(newNode);
        ++size_;
    }

    T erase(std::size_t index) {
        checkIndex(index);

        if (index == 0) {
            return pop_front();
        }

        if (index + 1 == size_) {
            return pop_back();
        }

        Node* current = nodeAt(index);
        Node* previous = current->previous;
        std::unique_ptr<Node> removed = std::move(previous->next);
        previous->next = std::move(removed->next);
        previous->next->previous = previous;
        --size_;
        return removed->value;
    }

    [[nodiscard]] std::optional<std::size_t> find(const T& value) const noexcept {
        const Node* current = head_.get();
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
        Node* previous = nullptr;
        std::unique_ptr<Node> next;
    };

    [[nodiscard]] Node* nodeAt(std::size_t index) {
        checkIndex(index);

        if (index < size_ / 2) {
            Node* current = head_.get();
            for (std::size_t i = 0; i < index; ++i) {
                current = current->next.get();
            }
            return current;
        }

        Node* current = tail_;
        for (std::size_t i = size_ - 1; i > index; --i) {
            current = current->previous;
        }
        return current;
    }

    [[nodiscard]] const Node* nodeAt(std::size_t index) const {
        checkIndex(index);

        if (index < size_ / 2) {
            const Node* current = head_.get();
            for (std::size_t i = 0; i < index; ++i) {
                current = current->next.get();
            }
            return current;
        }

        const Node* current = tail_;
        for (std::size_t i = size_ - 1; i > index; --i) {
            current = current->previous;
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
