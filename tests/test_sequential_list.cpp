#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/linear_list/sequential_list.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_insert_and_access() {
    ds::linear_list::SequentialList<int> list(2);
    list.push_back(10);
    list.push_back(20);
    list.insert(1, 15);

    expect(list.size() == 3, "size should be 3 after insert");
    expect(list.at(0) == 10, "element 0 should be 10");
    expect(list.at(1) == 15, "element 1 should be 15");
    expect(list.at(2) == 20, "element 2 should be 20");
}

void test_erase() {
    ds::linear_list::SequentialList<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }

    const int removed = list.erase(2);
    expect(removed == 2, "erase should return removed value");
    expect(list.size() == 4, "size should be 4 after erase");
    expect(list.at(2) == 3, "element 2 should shift to 3 after erase");
}

void test_find() {
    ds::linear_list::SequentialList<int> list;
    list.push_back(7);
    list.push_back(9);
    list.push_back(11);

    const auto found = list.find(9);
    const auto missing = list.find(100);

    expect(found.has_value() && *found == 1, "find should locate 9 at index 1");
    expect(!missing.has_value(), "find should return nullopt for missing element");
}

void test_exception() {
    ds::linear_list::SequentialList<int> list;
    bool threw = false;

    try {
        static_cast<void>(list.at(0));
    } catch (const std::out_of_range&) {
        threw = true;
    }

    expect(threw, "at(0) on empty list should throw");
}

}  // namespace

int main() {
    test_insert_and_access();
    test_erase();
    test_find();
    test_exception();

    if (g_failures == 0) {
        std::cout << "[PASS] all sequential list tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
