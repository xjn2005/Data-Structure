#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/stack/linked_stack.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_push_pop_and_top() {
    ds::stack::LinkedStack<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    expect(stack.size() == 3, "size should be 3 after push");
    expect(stack.top() == 30, "top should be 30");
    expect(stack.pop() == 30, "first pop should return 30");
    expect(stack.pop() == 20, "second pop should return 20");
    expect(stack.top() == 10, "top should be 10 after pops");
}

void test_exception() {
    ds::stack::LinkedStack<int> stack;
    bool threw = false;

    try {
        static_cast<void>(stack.pop());
    } catch (const std::out_of_range&) {
        threw = true;
    }

    expect(threw, "pop on empty stack should throw");
}

}  // namespace

int main() {
    test_push_pop_and_top();
    test_exception();

    if (g_failures == 0) {
        std::cout << "[PASS] all linked stack tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
