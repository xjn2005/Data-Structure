#include <iostream>

#include "ds/linear_list/doubly_linked_list.hpp"

int main() {
    ds::linear_list::DoublyLinkedList<int> list;

    list.push_back(10);
    list.push_back(30);
    list.push_front(5);
    list.insert(2, 20);

    std::cout << "size: " << list.size() << '\n';
    std::cout << "empty: " << std::boolalpha << list.empty() << '\n';

    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list.at(i) << ' ';
    }
    std::cout << '\n';

    list.pop_front();
    list.pop_back();
    list.set(1, 99);

    if (const auto index = list.find(99); index.has_value()) {
        std::cout << "find 99 at: " << *index << '\n';
    }

    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list.at(i) << ' ';
    }
    std::cout << '\n';

    return 0;
}
