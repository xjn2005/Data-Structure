#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds::sorting {

template <typename T, typename Compare = std::less<T>>
void insertionSort(std::vector<T>& data, Compare comp = Compare()) {
    for (std::size_t i = 1; i < data.size(); ++i) {
        T key = data[i];
        std::size_t j = i;
        while (j > 0 && comp(key, data[j - 1])) {
            data[j] = data[j - 1];
            --j;
        }
        data[j] = key;
    }
}

template <typename T, typename Compare = std::less<T>>
void binaryInsertionSort(std::vector<T>& data, Compare comp = Compare()) {
    for (std::size_t i = 1; i < data.size(); ++i) {
        T key = data[i];
        std::size_t left = 0;
        std::size_t right = i;

        while (left < right) {
            const std::size_t mid = left + (right - left) / 2;
            if (comp(key, data[mid])) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        for (std::size_t j = i; j > left; --j) {
            data[j] = data[j - 1];
        }
        data[left] = key;
    }
}

template <typename T, typename Compare = std::less<T>>
void shellSort(std::vector<T>& data, Compare comp = Compare()) {
    for (std::size_t gap = data.size() / 2; gap > 0; gap /= 2) {
        for (std::size_t i = gap; i < data.size(); ++i) {
            T key = data[i];
            std::size_t j = i;
            while (j >= gap && comp(key, data[j - gap])) {
                data[j] = data[j - gap];
                j -= gap;
            }
            data[j] = key;
        }
    }
}

template <typename T, typename Compare = std::less<T>>
void bubbleSort(std::vector<T>& data, Compare comp = Compare()) {
    for (std::size_t end = data.size(); end > 1; --end) {
        bool swapped = false;
        for (std::size_t i = 1; i < end; ++i) {
            if (comp(data[i], data[i - 1])) {
                std::swap(data[i], data[i - 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            return;
        }
    }
}

template <typename T, typename Compare>
std::size_t partition(std::vector<T>& data, std::size_t low, std::size_t high, Compare comp) {
    const T pivot = data[high];
    std::size_t i = low;

    for (std::size_t j = low; j < high; ++j) {
        if (!comp(pivot, data[j])) {
            std::swap(data[i], data[j]);
            ++i;
        }
    }

    std::swap(data[i], data[high]);
    return i;
}

template <typename T, typename Compare>
void quickSortImpl(std::vector<T>& data, std::size_t low, std::size_t high, Compare comp) {
    if (low >= high) {
        return;
    }

    const std::size_t pivotIndex = partition(data, low, high, comp);
    if (pivotIndex > 0) {
        quickSortImpl(data, low, pivotIndex - 1, comp);
    }
    quickSortImpl(data, pivotIndex + 1, high, comp);
}

template <typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T>& data, Compare comp = Compare()) {
    if (data.empty()) {
        return;
    }
    quickSortImpl(data, 0, data.size() - 1, comp);
}

template <typename T, typename Compare = std::less<T>>
void selectionSort(std::vector<T>& data, Compare comp = Compare()) {
    for (std::size_t i = 0; i < data.size(); ++i) {
        std::size_t selected = i;
        for (std::size_t j = i + 1; j < data.size(); ++j) {
            if (comp(data[j], data[selected])) {
                selected = j;
            }
        }
        if (selected != i) {
            std::swap(data[i], data[selected]);
        }
    }
}

template <typename T, typename Compare>
void heapify(std::vector<T>& data, std::size_t heapSize, std::size_t root, Compare comp) {
    std::size_t selected = root;
    const std::size_t left = root * 2 + 1;
    const std::size_t right = root * 2 + 2;

    if (left < heapSize && comp(data[selected], data[left])) {
        selected = left;
    }
    if (right < heapSize && comp(data[selected], data[right])) {
        selected = right;
    }
    if (selected != root) {
        std::swap(data[root], data[selected]);
        heapify(data, heapSize, selected, comp);
    }
}

template <typename T, typename Compare = std::less<T>>
void heapSort(std::vector<T>& data, Compare comp = Compare()) {
    if (data.empty()) {
        return;
    }

    for (std::size_t i = data.size() / 2; i > 0; --i) {
        heapify(data, data.size(), i - 1, comp);
    }

    for (std::size_t end = data.size(); end > 1; --end) {
        std::swap(data[0], data[end - 1]);
        heapify(data, end - 1, 0, comp);
    }
}

template <typename T, typename Compare>
void merge(std::vector<T>& data, std::vector<T>& buffer, std::size_t left, std::size_t mid, std::size_t right, Compare comp) {
    std::size_t i = left;
    std::size_t j = mid + 1;
    std::size_t k = left;

    while (i <= mid && j <= right) {
        if (!comp(data[j], data[i])) {
            buffer[k++] = data[i++];
        } else {
            buffer[k++] = data[j++];
        }
    }

    while (i <= mid) {
        buffer[k++] = data[i++];
    }
    while (j <= right) {
        buffer[k++] = data[j++];
    }

    for (std::size_t index = left; index <= right; ++index) {
        data[index] = buffer[index];
    }
}

template <typename T, typename Compare>
void mergeSortImpl(std::vector<T>& data, std::vector<T>& buffer, std::size_t left, std::size_t right, Compare comp) {
    if (left >= right) {
        return;
    }

    const std::size_t mid = left + (right - left) / 2;
    mergeSortImpl(data, buffer, left, mid, comp);
    mergeSortImpl(data, buffer, mid + 1, right, comp);
    merge(data, buffer, left, mid, right, comp);
}

template <typename T, typename Compare = std::less<T>>
void mergeSort(std::vector<T>& data, Compare comp = Compare()) {
    if (data.empty()) {
        return;
    }

    std::vector<T> buffer(data.size());
    mergeSortImpl(data, buffer, 0, data.size() - 1, comp);
}

inline void countingSort(std::vector<int>& data) {
    if (data.empty()) {
        return;
    }

    const auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
    const int minValue = *minIt;
    const int maxValue = *maxIt;
    const std::size_t range = static_cast<std::size_t>(maxValue - minValue + 1);

    std::vector<std::size_t> counts(range, 0);
    for (int value : data) {
        ++counts[static_cast<std::size_t>(value - minValue)];
    }

    std::size_t index = 0;
    for (std::size_t i = 0; i < counts.size(); ++i) {
        while (counts[i]-- > 0) {
            data[index++] = static_cast<int>(i) + minValue;
        }
    }
}

inline void radixSort(std::vector<int>& data) {
    if (data.empty()) {
        return;
    }

    for (int value : data) {
        if (value < 0) {
            throw std::invalid_argument("radixSort only supports non-negative integers");
        }
    }

    const int maxValue = *std::max_element(data.begin(), data.end());
    std::vector<int> output(data.size());

    for (int exp = 1; maxValue / exp > 0; exp *= 10) {
        std::vector<int> count(10, 0);

        for (int value : data) {
            ++count[(value / exp) % 10];
        }

        for (std::size_t i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }

        for (std::size_t i = data.size(); i > 0; --i) {
            const int value = data[i - 1];
            const int digit = (value / exp) % 10;
            output[static_cast<std::size_t>(--count[digit])] = value;
        }

        data = output;
    }
}

}  // namespace ds::sorting
