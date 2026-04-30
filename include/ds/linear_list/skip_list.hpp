#pragma once

#include <cstddef>
#include <functional>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds::linear_list {

template <typename Key, typename Value, typename Compare = std::less<Key>>
class SkipList {
public:
    explicit SkipList(std::size_t maxLevel = 8, double probability = 0.5)
        : maxLevel_(maxLevel == 0 ? 1 : maxLevel),
          probability_(probability),
          head_(new Node(maxLevel_, Key{}, Value{})),
          level_(1),
          rng_(std::random_device{}()),
          distribution_(0.0, 1.0) {
        if (probability_ <= 0.0 || probability_ >= 1.0) {
            throw std::invalid_argument("probability must be in (0, 1)");
        }
    }

    ~SkipList() {
        clear();
        delete head_;
    }

    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    bool insert(const Key& key, const Value& value) {
        std::vector<Node*> update(maxLevel_, nullptr);
        Node* current = head_;

        for (std::size_t i = level_; i > 0; --i) {
            while (current->forward[i - 1] != nullptr &&
                   comp_(current->forward[i - 1]->key, key)) {
                current = current->forward[i - 1];
            }
            update[i - 1] = current;
        }

        current = current->forward[0];
        if (current != nullptr && isEqual(current->key, key)) {
            current->value = value;
            return false;
        }

        const std::size_t newLevel = randomLevel();
        if (newLevel > level_) {
            for (std::size_t i = level_; i < newLevel; ++i) {
                update[i] = head_;
            }
            level_ = newLevel;
        }

        Node* newNode = new Node(newLevel, key, value);
        for (std::size_t i = 0; i < newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }

        ++size_;
        return true;
    }

    bool erase(const Key& key) {
        std::vector<Node*> update(maxLevel_, nullptr);
        Node* current = head_;

        for (std::size_t i = level_; i > 0; --i) {
            while (current->forward[i - 1] != nullptr &&
                   comp_(current->forward[i - 1]->key, key)) {
                current = current->forward[i - 1];
            }
            update[i - 1] = current;
        }

        current = current->forward[0];
        if (current == nullptr || !isEqual(current->key, key)) {
            return false;
        }

        for (std::size_t i = 0; i < level_; ++i) {
            if (update[i]->forward[i] != current) {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }

        delete current;
        --size_;

        while (level_ > 1 && head_->forward[level_ - 1] == nullptr) {
            --level_;
        }

        return true;
    }

    [[nodiscard]] bool contains(const Key& key) const {
        return findNode(key) != nullptr;
    }

    [[nodiscard]] Value& at(const Key& key) {
        Node* node = findNode(key);
        if (node == nullptr) {
            throw std::out_of_range("key not found");
        }
        return node->value;
    }

    [[nodiscard]] const Value& at(const Key& key) const {
        const Node* node = findNode(key);
        if (node == nullptr) {
            throw std::out_of_range("key not found");
        }
        return node->value;
    }

    [[nodiscard]] std::vector<std::pair<Key, Value>> items() const {
        std::vector<std::pair<Key, Value>> result;
        Node* current = head_->forward[0];
        while (current != nullptr) {
            result.push_back({current->key, current->value});
            current = current->forward[0];
        }
        return result;
    }

private:
    struct Node {
        Node(std::size_t level, const Key& key, const Value& value)
            : key(key), value(value), forward(level, nullptr) {}

        Key key;
        Value value;
        std::vector<Node*> forward;
    };

    void clear() noexcept {
        Node* current = head_->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        for (auto& next : head_->forward) {
            next = nullptr;
        }
        size_ = 0;
        level_ = 1;
    }

    [[nodiscard]] Node* findNode(const Key& key) const {
        Node* current = head_;
        for (std::size_t i = level_; i > 0; --i) {
            while (current->forward[i - 1] != nullptr &&
                   comp_(current->forward[i - 1]->key, key)) {
                current = current->forward[i - 1];
            }
        }

        current = current->forward[0];
        if (current != nullptr && isEqual(current->key, key)) {
            return current;
        }
        return nullptr;
    }

    [[nodiscard]] bool isEqual(const Key& left, const Key& right) const {
        return !comp_(left, right) && !comp_(right, left);
    }

    [[nodiscard]] std::size_t randomLevel() {
        std::size_t newLevel = 1;
        while (newLevel < maxLevel_ && distribution_(rng_) < probability_) {
            ++newLevel;
        }
        return newLevel;
    }

    std::size_t maxLevel_;
    double probability_;
    Node* head_;
    std::size_t level_;
    std::size_t size_ = 0;
    Compare comp_;
    mutable std::mt19937 rng_;
    mutable std::uniform_real_distribution<double> distribution_;
};

}  // namespace ds::linear_list
