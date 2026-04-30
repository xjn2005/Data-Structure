#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ds/sorting/sorting.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

template <typename SortFn>
void expectSorted(const std::string& name, SortFn sortFn) {
    std::vector<int> data{49, 38, 65, 97, 76, 13, 27, 49, 10, -5, 0};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    sortFn(data);
    expect(data == expected, name + " should sort ascending");
}

template <typename SortFn>
void expectSortedDescending(const std::string& name, SortFn sortFn) {
    std::vector<int> data{4, 1, 8, 3, 9, 2};
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end(), std::greater<int>());

    sortFn(data);
    expect(data == expected, name + " should support custom comparator");
}

void test_comparison_sorts() {
    expectSorted("insertionSort", [](auto& data) { ds::sorting::insertionSort(data); });
    expectSorted("binaryInsertionSort", [](auto& data) { ds::sorting::binaryInsertionSort(data); });
    expectSorted("shellSort", [](auto& data) { ds::sorting::shellSort(data); });
    expectSorted("bubbleSort", [](auto& data) { ds::sorting::bubbleSort(data); });
    expectSorted("quickSort", [](auto& data) { ds::sorting::quickSort(data); });
    expectSorted("selectionSort", [](auto& data) { ds::sorting::selectionSort(data); });
    expectSorted("heapSort", [](auto& data) { ds::sorting::heapSort(data); });
    expectSorted("mergeSort", [](auto& data) { ds::sorting::mergeSort(data); });

    expectSortedDescending("insertionSort", [](auto& data) { ds::sorting::insertionSort(data, std::greater<int>()); });
    expectSortedDescending("quickSort", [](auto& data) { ds::sorting::quickSort(data, std::greater<int>()); });
    expectSortedDescending("heapSort", [](auto& data) { ds::sorting::heapSort(data, std::greater<int>()); });
    expectSortedDescending("mergeSort", [](auto& data) { ds::sorting::mergeSort(data, std::greater<int>()); });
}

void test_counting_sort() {
    std::vector<int> data{4, -1, 3, 4, 2, -1, 0};
    ds::sorting::countingSort(data);
    expect((data == std::vector<int>{-1, -1, 0, 2, 3, 4, 4}), "countingSort should handle duplicates and negatives");
}

void test_radix_sort() {
    std::vector<int> data{170, 45, 75, 90, 802, 24, 2, 66};
    ds::sorting::radixSort(data);
    expect((data == std::vector<int>{2, 24, 45, 66, 75, 90, 170, 802}), "radixSort should sort non-negative integers");
}

void test_radix_sort_negative_guard() {
    std::vector<int> data{3, -1, 2};
    bool threw = false;

    try {
        ds::sorting::radixSort(data);
    } catch (const std::invalid_argument&) {
        threw = true;
    }

    expect(threw, "radixSort should reject negative integers");
}

}  // namespace

int main() {
    test_comparison_sorts();
    test_counting_sort();
    test_radix_sort();
    test_radix_sort_negative_guard();

    if (g_failures == 0) {
        std::cout << "[PASS] all sorting tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
