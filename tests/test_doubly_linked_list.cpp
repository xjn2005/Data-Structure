#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/linear_list/doubly_linked_list.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_insert_and_access() {
    ds::linear_list::DoublyLinkedList<int> list;
    list.push_front(20);
    list.push_front(10);
    list.push_back(40);
    list.insert(2, 30);

    expect(list.size() == 4, "size should be 4 after insertions");
    expect(list.at(0) == 10, "element 0 should be 10");
    expect(list.at(1) == 20, "element 1 should be 20");
    expect(list.at(2) == 30, "element 2 should be 30");
    expect(list.at(3) == 40, "element 3 should be 40");
}

void test_pop_from_both_ends() {
    ds::linear_list::DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    expect(list.pop_front() == 10, "pop_front should remove the first value");
    expect(list.pop_back() == 30, "pop_back should remove the last value");
    expect(list.size() == 1, "size should be 1 after two pops");
    expect(list.at(0) == 20, "the middle value should remain");

    expect(list.pop_back() == 20, "pop_back should remove the only value");
    expect(list.empty(), "list should be empty after removing the only value");

    list.push_front(99);
    expect(list.pop_front() == 99, "list should remain usable after becoming empty");
    expect(list.empty(), "list should be empty after the final pop");
}

void test_erase_and_bidirectional_links() {
    ds::linear_list::DoublyLinkedList<int> list;
    for (int value : {10, 20, 30, 40, 50}) {
        list.push_back(value);
    }

    expect(list.erase(2) == 30, "erase should remove a middle value");
    expect(list.at(2) == 40, "successor should reconnect after middle erase");
    expect(list.erase(3) == 50, "erase should remove the tail");
    expect(list.pop_back() == 40, "tail should move backward after erase");
    expect(list.erase(0) == 10, "erase should remove the head");
    expect(list.at(0) == 20, "head should move forward after erase");
}

void test_find_and_set() {
    ds::linear_list::DoublyLinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    const auto found = list.find(10);
    expect(found.has_value() && *found == 1, "find should locate 10 at index 1");
    expect(!list.find(100).has_value(), "find should return nullopt for a missing value");

    list.set(2, 99);
    expect(list.at(2) == 99, "set should update an element near the tail");
}

void test_exceptions() {
    ds::linear_list::DoublyLinkedList<int> list;

    bool popFrontThrew = false;
    try {
        static_cast<void>(list.pop_front());
    } catch (const std::out_of_range&) {
        popFrontThrew = true;
    }
    expect(popFrontThrew, "pop_front on an empty list should throw");

    bool popBackThrew = false;
    try {
        static_cast<void>(list.pop_back());
    } catch (const std::out_of_range&) {
        popBackThrew = true;
    }
    expect(popBackThrew, "pop_back on an empty list should throw");

    bool insertThrew = false;
    try {
        list.insert(1, 10);
    } catch (const std::out_of_range&) {
        insertThrew = true;
    }
    expect(insertThrew, "insert past the end should throw");

    bool accessThrew = false;
    try {
        static_cast<void>(list.at(0));
    } catch (const std::out_of_range&) {
        accessThrew = true;
    }
    expect(accessThrew, "at on an empty list should throw");
}

}  // namespace

int main() {
    test_insert_and_access();
    test_pop_from_both_ends();
    test_erase_and_bidirectional_links();
    test_find_and_set();
    test_exceptions();

    if (g_failures == 0) {
        std::cout << "[PASS] all doubly linked list tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
