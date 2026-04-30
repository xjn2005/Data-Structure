#include <iostream>

#include "ds/tree/binary_search_tree.hpp"

int main() {
    ds::tree::BinarySearchTree<int> bst;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        bst.insert(value);
    }

    std::cout << "contains 40: " << std::boolalpha << bst.contains(40) << '\n';
    std::cout << "min: " << *bst.min() << '\n';
    std::cout << "max: " << *bst.max() << '\n';

    bst.erase(30);
    for (int value : bst.inorder()) {
        std::cout << value << ' ';
    }
    std::cout << '\n';

    return 0;
}
