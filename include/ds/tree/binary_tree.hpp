#pragma once

#include <cstddef>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

namespace ds::tree {

template <typename T>
class BinaryTree {
public:
    struct Node {
        explicit Node(const T& value) : value(value) {}

        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    BinaryTree() = default;

    [[nodiscard]] bool empty() const noexcept {
        return root_ == nullptr;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    Node* setRoot(const T& value) {
        root_ = std::make_unique<Node>(value);
        size_ = 1;
        return root_.get();
    }

    [[nodiscard]] Node* root() noexcept {
        return root_.get();
    }

    [[nodiscard]] const Node* root() const noexcept {
        return root_.get();
    }

    Node* insertLeft(Node* parent, const T& value) {
        if (parent == nullptr) {
            throw std::invalid_argument("parent must not be null");
        }
        if (parent->left != nullptr) {
            throw std::logic_error("left child already exists");
        }
        parent->left = std::make_unique<Node>(value);
        ++size_;
        return parent->left.get();
    }

    Node* insertRight(Node* parent, const T& value) {
        if (parent == nullptr) {
            throw std::invalid_argument("parent must not be null");
        }
        if (parent->right != nullptr) {
            throw std::logic_error("right child already exists");
        }
        parent->right = std::make_unique<Node>(value);
        ++size_;
        return parent->right.get();
    }

    [[nodiscard]] std::vector<T> preorder() const {
        std::vector<T> result;
        preorder(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::vector<T> inorder() const {
        std::vector<T> result;
        inorder(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::vector<T> postorder() const {
        std::vector<T> result;
        postorder(root_.get(), result);
        return result;
    }

    [[nodiscard]] std::vector<T> levelOrder() const {
        std::vector<T> result;
        if (root_ == nullptr) {
            return result;
        }

        std::queue<const Node*> pending;
        pending.push(root_.get());

        while (!pending.empty()) {
            const Node* current = pending.front();
            pending.pop();
            result.push_back(current->value);

            if (current->left != nullptr) {
                pending.push(current->left.get());
            }
            if (current->right != nullptr) {
                pending.push(current->right.get());
            }
        }

        return result;
    }

private:
    static void preorder(const Node* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->value);
        preorder(node->left.get(), result);
        preorder(node->right.get(), result);
    }

    static void inorder(const Node* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), result);
        result.push_back(node->value);
        inorder(node->right.get(), result);
    }

    static void postorder(const Node* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left.get(), result);
        postorder(node->right.get(), result);
        result.push_back(node->value);
    }

    std::unique_ptr<Node> root_;
    std::size_t size_ = 0;
};

}  // namespace ds::tree
