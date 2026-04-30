#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ds/disjoint_set/disjoint_set.hpp"
#include "ds/hash/hash_table.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_disjoint_set() {
    ds::disjoint_set::DisjointSet dsu(6);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    expect(dsu.connected(0, 2), "0 and 2 should be connected");
    expect(!dsu.connected(2, 4), "2 and 4 should not be connected");
    expect(dsu.componentSize(1) == 3, "component size of 1 should be 3");
    expect(dsu.unite(2, 4), "unite should merge two components");
    expect(dsu.connected(0, 4), "0 and 4 should be connected after merge");
}

void test_hash_table() {
    ds::hash::HashTable<std::string, int> table;
    table.put("apple", 3);
    table.put("banana", 5);
    table.put("orange", 7);

    expect(table.contains("banana"), "hash table should contain banana");
    expect(table.at("orange") == 7, "orange should map to 7");

    table.put("banana", 8);
    expect(table.at("banana") == 8, "banana should update to 8");
    expect(table.erase("apple"), "erase should remove apple");
    expect(!table.contains("apple"), "apple should be removed");
}

}  // namespace

int main() {
    test_disjoint_set();
    test_hash_table();

    if (g_failures == 0) {
        std::cout << "[PASS] all disjoint set and hash table tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
