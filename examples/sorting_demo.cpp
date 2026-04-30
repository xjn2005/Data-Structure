#include <iostream>
#include <vector>

#include "ds/sorting/sorting.hpp"

template <typename T>
void printVector(const std::vector<T>& data) {
    for (const auto& value : data) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> values{49, 38, 65, 97, 76, 13, 27, 49, 10};
    std::vector<int> copy = values;

    ds::sorting::quickSort(copy);
    printVector(copy);

    copy = values;
    ds::sorting::mergeSort(copy);
    printVector(copy);

    copy = values;
    ds::sorting::radixSort(copy);
    printVector(copy);

    return 0;
}
