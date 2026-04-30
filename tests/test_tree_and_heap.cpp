#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "ds/heap/binary_heap.hpp"
#include "ds/tree/binary_search_tree.hpp"
#include "ds/tree/binary_tree.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_binary_tree() {
    ds::tree::BinaryTree<int> tree;
    auto* root = tree.setRoot(1);
    auto* left = tree.insertLeft(root, 2);
    auto* right = tree.insertRight(root, 3);
    tree.insertLeft(left, 4);
    tree.insertRight(left, 5);
    tree.insertLeft(right, 6);

    expect((tree.preorder() == std::vector<int>{1, 2, 4, 5, 3, 6}), "binary tree preorder should match");
    expect((tree.inorder() == std::vector<int>{4, 2, 5, 1, 6, 3}), "binary tree inorder should match");
    expect((tree.levelOrder() == std::vector<int>{1, 2, 3, 4, 5, 6}), "binary tree level order should match");
}

void test_binary_search_tree() {
    ds::tree::BinarySearchTree<int> bst;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        bst.insert(value);
    }

    expect(bst.contains(40), "bst should contain 40");
    expect(!bst.contains(100), "bst should not contain 100");
    expect(bst.min().has_value() && *bst.min() == 20, "bst min should be 20");
    expect(bst.max().has_value() && *bst.max() == 80, "bst max should be 80");
    expect(bst.erase(30), "bst erase should remove existing node");
    expect((bst.inorder() == std::vector<int>{20, 40, 50, 60, 70, 80}), "bst inorder after erase should match");
}

void test_binary_heap() {
    ds::heap::BinaryHeap<int> heap;
    for (int value : {10, 40, 20, 60, 30}) {
        heap.push(value);
    }

    std::vector<int> popped;
    while (!heap.empty()) {
        popped.push_back(heap.pop());
    }

    expect((popped == std::vector<int>{60, 40, 30, 20, 10}), "max heap pop order should be descending");

    ds::heap::BinaryHeap<int, std::greater<int>> minHeap;
    for (int value : {10, 40, 20, 60, 30}) {
        minHeap.push(value);
    }
    expect(minHeap.top() == 10, "min heap top should be 10");
}

}  // namespace

int main() {
    test_binary_tree();
    test_binary_search_tree();
    test_binary_heap();

    if (g_failures == 0) {
        std::cout << "[PASS] all tree and heap tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
