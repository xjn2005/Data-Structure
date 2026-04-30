#include <iostream>

#include "ds/queue/linked_queue.hpp"

int main() {
    ds::queue::LinkedQueue<int> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    std::cout << "size: " << queue.size() << '\n';
    std::cout << "front: " << queue.front() << '\n';
    std::cout << "back: " << queue.back() << '\n';

    while (!queue.empty()) {
        std::cout << queue.pop() << ' ';
    }
    std::cout << '\n';

    return 0;
}
