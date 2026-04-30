#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "ds/linear_list/skip_list.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_insert_find_and_order() {
    ds::linear_list::SkipList<int, std::string> skipList;
    skipList.insert(3, "three");
    skipList.insert(1, "one");
    skipList.insert(4, "four");
    skipList.insert(2, "two");

    expect(skipList.size() == 4, "size should be 4 after insert");
    expect(skipList.contains(3), "skip list should contain key 3");
    expect(skipList.at(2) == "two", "key 2 should map to two");
    expect((skipList.items() == std::vector<std::pair<int, std::string>>{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}}),
           "items should stay ordered by key");
}

void test_update_and_erase() {
    ds::linear_list::SkipList<int, std::string> skipList;
    skipList.insert(1, "one");
    skipList.insert(2, "two");
    skipList.insert(2, "TWO");

    expect(skipList.size() == 2, "updating existing key should not change size");
    expect(skipList.at(2) == "TWO", "existing key should update value");
    expect(skipList.erase(1), "erase should remove existing key");
    expect(!skipList.contains(1), "erased key should not exist");
}

void test_exception() {
    ds::linear_list::SkipList<int, std::string> skipList;
    bool threw = false;

    try {
        static_cast<void>(skipList.at(100));
    } catch (const std::out_of_range&) {
        threw = true;
    }

    expect(threw, "at on missing key should throw");
}

}  // namespace

int main() {
    test_insert_find_and_order();
    test_update_and_erase();
    test_exception();

    if (g_failures == 0) {
        std::cout << "[PASS] all skip list tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
