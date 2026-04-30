#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/queue/linked_queue.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_push_pop_front_back() {
    ds::queue::LinkedQueue<int> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    expect(queue.size() == 3, "size should be 3 after push");
    expect(queue.front() == 10, "front should be 10");
    expect(queue.back() == 30, "back should be 30");
    expect(queue.pop() == 10, "first pop should return 10");
    expect(queue.front() == 20, "front should move to 20");
    expect(queue.pop() == 20, "second pop should return 20");
    expect(queue.pop() == 30, "third pop should return 30");
    expect(queue.empty(), "queue should be empty after pops");
}

void test_exception() {
    ds::queue::LinkedQueue<int> queue;
    bool threw = false;

    try {
        static_cast<void>(queue.front());
    } catch (const std::out_of_range&) {
        threw = true;
    }

    expect(threw, "front on empty queue should throw");
}

}  // namespace

int main() {
    test_push_pop_front_back();
    test_exception();

    if (g_failures == 0) {
        std::cout << "[PASS] all linked queue tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
