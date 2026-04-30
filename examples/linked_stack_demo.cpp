#include <iostream>

#include "ds/stack/linked_stack.hpp"

int main() {
    ds::stack::LinkedStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "size: " << stack.size() << '\n';
    std::cout << "top: " << stack.top() << '\n';

    while (!stack.empty()) {
        std::cout << stack.pop() << ' ';
    }
    std::cout << '\n';

    return 0;
}
