#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>

namespace ds::linear_list {

template <typename T>
class SequentialList {
public:
    explicit SequentialList(std::size_t initialCapacity = 10)
        : elements_(std::make_unique<T[]>(initialCapacity)),
          size_(0),
          capacity_(initialCapacity) {
        if (initialCapacity == 0) {
            throw std::invalid_argument("initial capacity must be greater than 0");
        }
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t capacity() const noexcept {
        return capacity_;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("insert index out of range");
        }

        ensureCapacity();

        for (std::size_t i = size_; i > index; --i) {
            elements_[i] = elements_[i - 1];
        }

        elements_[index] = value;
        ++size_;
    }

    void push_back(const T& value) {
        insert(size_, value);
    }

    T erase(std::size_t index) {
        checkIndex(index);

        T removed = elements_[index];
        for (std::size_t i = index; i + 1 < size_; ++i) {
            elements_[i] = elements_[i + 1];
        }

        --size_;
        return removed;
    }

    [[nodiscard]] std::optional<std::size_t> find(const T& value) const noexcept {
        for (std::size_t i = 0; i < size_; ++i) {
            if (elements_[i] == value) {
                return i;
            }
        }
        return std::nullopt;
    }

    [[nodiscard]] const T& at(std::size_t index) const {
        checkIndex(index);
        return elements_[index];
    }

    T& at(std::size_t index) {
        checkIndex(index);
        return elements_[index];
    }

    void set(std::size_t index, const T& value) {
        at(index) = value;
    }

private:
    void ensureCapacity() {
        if (size_ < capacity_) {
            return;
        }

        const std::size_t newCapacity = capacity_ * 2;
        auto newElements = std::make_unique<T[]>(newCapacity);

        for (std::size_t i = 0; i < size_; ++i) {
            newElements[i] = elements_[i];
        }

        elements_ = std::move(newElements);
        capacity_ = newCapacity;
    }

    void checkIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
    }

    std::unique_ptr<T[]> elements_;
    std::size_t size_;
    std::size_t capacity_;
};

}  // namespace ds::linear_list
