#include <iostream>

#include "ds/linear_list/sequential_list.hpp"

int main() {
    ds::linear_list::SequentialList<int> list(10);

    for (int i = 0; i < 10; ++i) {
        list.push_back(i * 10);
    }

    std::cout << "size: " << list.size() << '\n';
    std::cout << "empty: " << std::boolalpha << list.empty() << '\n';

    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list.at(i) << ' ';
    }
    std::cout << '\n';

    list.erase(5);
    list.set(1, 1314);

    if (const auto index = list.find(20); index.has_value()) {
        list.set(*index, 520);
    }

    for (std::size_t i = 0; i < list.size(); ++i) {
        std::cout << list.at(i) << ' ';
    }
    std::cout << '\n';

    return 0;
}
