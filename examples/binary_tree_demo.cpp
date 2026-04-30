#include <iostream>

#include "ds/tree/binary_tree.hpp"

template <typename T>
void printValues(const std::vector<T>& values) {
    for (const auto& value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    ds::tree::BinaryTree<int> tree;
    auto* root = tree.setRoot(1);
    auto* left = tree.insertLeft(root, 2);
    auto* right = tree.insertRight(root, 3);
    tree.insertLeft(left, 4);
    tree.insertRight(left, 5);
    tree.insertLeft(right, 6);

    std::cout << "preorder: ";
    printValues(tree.preorder());
    std::cout << "inorder: ";
    printValues(tree.inorder());
    std::cout << "level order: ";
    printValues(tree.levelOrder());

    return 0;
}
