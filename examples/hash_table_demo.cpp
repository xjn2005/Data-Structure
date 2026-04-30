#include <iostream>
#include <string>

#include "ds/hash/hash_table.hpp"

int main() {
    ds::hash::HashTable<std::string, int> table;
    table.put("apple", 3);
    table.put("banana", 5);
    table.put("orange", 7);

    std::cout << "contains banana: " << std::boolalpha << table.contains("banana") << '\n';
    std::cout << "orange -> " << table.at("orange") << '\n';

    table.put("banana", 8);
    std::cout << "banana -> " << table.at("banana") << '\n';

    return 0;
}
