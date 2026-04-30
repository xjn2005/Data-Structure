#include <iostream>

#include "ds/heap/binary_heap.hpp"

int main() {
    ds::heap::BinaryHeap<int> heap;
    for (int value : {10, 40, 20, 60, 30}) {
        heap.push(value);
    }

    std::cout << "top: " << heap.top() << '\n';
    while (!heap.empty()) {
        std::cout << heap.pop() << ' ';
    }
    std::cout << '\n';

    return 0;
}
