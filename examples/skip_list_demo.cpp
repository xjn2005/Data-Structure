#include <iostream>
#include <string>

#include "ds/linear_list/skip_list.hpp"

int main() {
    ds::linear_list::SkipList<int, std::string> skipList;
    skipList.insert(3, "three");
    skipList.insert(1, "one");
    skipList.insert(4, "four");
    skipList.insert(2, "two");

    std::cout << "size: " << skipList.size() << '\n';
    std::cout << "contains 3: " << std::boolalpha << skipList.contains(3) << '\n';
    std::cout << "key 2 -> " << skipList.at(2) << '\n';

    for (const auto& [key, value] : skipList.items()) {
        std::cout << key << ':' << value << ' ';
    }
    std::cout << '\n';

    skipList.erase(3);
    for (const auto& [key, value] : skipList.items()) {
        std::cout << key << ':' << value << ' ';
    }
    std::cout << '\n';

    return 0;
}
