#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/linear_list/singly_linked_list.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_insert_and_access() {
    ds::linear_list::SinglyLinkedList<int> list;
    list.push_back(10);
    list.push_back(30);
    list.insert(1, 20);

    expect(list.size() == 3, "size should be 3 after insert");
    expect(list.at(0) == 10, "element 0 should be 10");
    expect(list.at(1) == 20, "element 1 should be 20");
    expect(list.at(2) == 30, "element 2 should be 30");
}

void test_push_front_and_erase() {
    ds::linear_list::SinglyLinkedList<int> list;
    list.push_front(2);
    list.push_front(1);
    list.push_back(3);

    const int removed = list.erase(1);
    expect(removed == 2, "erase should return removed value");
    expect(list.size() == 2, "size should be 2 after erase");
    expect(list.at(1) == 3, "remaining element should shift correctly");
}

void test_find_and_set() {
    ds::linear_list::SinglyLinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    const auto found = list.find(10);
    expect(found.has_value() && *found == 1, "find should locate 10 at index 1");

    list.set(1, 99);
    expect(list.at(1) == 99, "set should update element");
}

void test_exception() {
    ds::linear_list::SinglyLinkedList<int> list;
    bool threw = false;

    try {
        static_cast<void>(list.pop_front());
    } catch (const std::out_of_range&) {
        threw = true;
    }

    expect(threw, "pop_front on empty list should throw");
}

}  // namespace

int main() {
    test_insert_and_access();
    test_push_front_and_erase();
    test_find_and_set();
    test_exception();

    if (g_failures == 0) {
        std::cout << "[PASS] all singly linked list tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
