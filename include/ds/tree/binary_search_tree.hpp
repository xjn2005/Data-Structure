#pragma once

#include <cstddef>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

namespace ds::tree {

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree() = default;

    [[nodiscard]] bool empty() const noexcept {
        return root_ == nullptr;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    void insert(const T& value) {
        insert(root_, value);
    }

    [[nodiscard]] bool contains(const T& value) const noexcept {
        Node* current = root_.get();
        while (current != nullptr) {
            if (value < current->value) {
                current = current->left.get();
            } else if (current->value < value) {
                current = current->right.get();
            } else {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] std::optional<T> min() const noexcept {
        const Node* current = root_.get();
        if (current == nullptr) {
            return std::nullopt;
        }
        while (current->left != nullptr) {
            current = current->left.get();
        }
        return current->value;
    }

    [[nodiscard]] std::optional<T> max() const noexcept {
        const Node* current = root_.get();
        if (current == nullptr) {
            return std::nullopt;
        }
        while (current->right != nullptr) {
            current = current->right.get();
        }
        return current->value;
    }

    bool erase(const T& value) {
        return erase(root_, value);
    }

    [[nodiscard]] std::vector<T> inorder() const {
        std::vector<T> result;
        inorder(root_.get(), result);
        return result;
    }

private:
    struct Node {
        explicit Node(const T& value) : value(value) {}

        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    void insert(std::unique_ptr<Node>& node, const T& value) {
        if (node == nullptr) {
            node = std::make_unique<Node>(value);
            ++size_;
            return;
        }

        if (value < node->value) {
            insert(node->left, value);
        } else if (node->value < value) {
            insert(node->right, value);
        }
    }

    bool erase(std::unique_ptr<Node>& node, const T& value) {
        if (node == nullptr) {
            return false;
        }

        if (value < node->value) {
            return erase(node->left, value);
        }
        if (node->value < value) {
            return erase(node->right, value);
        }

        if (node->left == nullptr) {
            node = std::move(node->right);
        } else if (node->right == nullptr) {
            node = std::move(node->left);
        } else {
            Node* successor = node->right.get();
            while (successor->left != nullptr) {
                successor = successor->left.get();
            }
            node->value = successor->value;
            static_cast<void>(erase(node->right, successor->value));
            return true;
        }

        --size_;
        return true;
    }

    static void inorder(const Node* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), result);
        result.push_back(node->value);
        inorder(node->right.get(), result);
    }

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

}  // namespace ds::tree
