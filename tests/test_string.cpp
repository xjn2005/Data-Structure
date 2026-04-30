#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ds/string/sequential_string.hpp"

namespace {

int g_failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++g_failures;
        std::cerr << "[FAIL] " << message << '\n';
    }
}

void test_sequential_string_basic_operations() {
    ds::string::SequentialString text("data");
    text.pushBack('-');
    text.append("structure");

    expect(text.toStdString() == "data-structure", "append and pushBack should extend the string");

    text.insert(5, "and-");
    expect(text.toStdString() == "data-and-structure", "insert should place characters at the given position");

    text.erase(5, 4);
    expect(text.toStdString() == "data-structure", "erase should remove a substring");

    const auto sub = text.substr(5, 9);
    expect(sub.toStdString() == "structure", "substr should extract the requested range");
}

void test_compare_and_bounds() {
    ds::string::SequentialString alpha("alpha");
    ds::string::SequentialString beta("beta");

    expect(alpha.compare(beta) < 0, "compare should report lexicographical ordering");
    expect(beta.compare(alpha) > 0, "compare should report reverse lexicographical ordering");
    expect(alpha.compare(ds::string::SequentialString("alpha")) == 0, "compare should report equality");

    bool threw = false;
    try {
        static_cast<void>(alpha.at(99));
    } catch (const std::out_of_range&) {
        threw = true;
    }
    expect(threw, "at should guard out-of-range access");
}

void test_kmp_prefix_table() {
    const auto next = ds::string::buildKmpNext("ababaca");
    expect((next == std::vector<std::size_t>{0, 0, 1, 2, 3, 0, 1}), "buildKmpNext should compute the prefix table");
}

void test_pattern_matching() {
    ds::string::SequentialString text("ababcabcacbab");
    ds::string::SequentialString pattern("abcac");

    expect(ds::string::naiveFind(text, pattern) == 5, "naiveFind should locate the first match");
    expect(ds::string::kmpFind(text, pattern) == 5, "kmpFind should locate the first match");
    expect(ds::string::kmpFind(text, ds::string::SequentialString("xyz")) == ds::string::SequentialString::npos,
           "kmpFind should return npos for missing patterns");

    const auto matches = ds::string::kmpFindAll(
        ds::string::SequentialString("aaaaa"),
        ds::string::SequentialString("aa"));
    expect((matches == std::vector<std::size_t>{0, 1, 2, 3}), "kmpFindAll should support overlapping matches");
}

void test_empty_pattern_and_position_checks() {
    expect(ds::string::naiveFind(std::string_view("abc"), std::string_view("")) == 0,
           "empty pattern should match at the beginning");
    expect(ds::string::kmpFind(std::string_view("abc"), std::string_view(""), 2) == 2,
           "empty pattern should match at the given start position");

    const auto matches = ds::string::kmpFindAll(std::string_view("abc"), std::string_view(""));
    expect((matches == std::vector<std::size_t>{0, 1, 2, 3}), "empty pattern should match every boundary");

    bool threw = false;
    try {
        static_cast<void>(ds::string::kmpFind(std::string_view("abc"), std::string_view("a"), 4));
    } catch (const std::out_of_range&) {
        threw = true;
    }
    expect(threw, "kmpFind should reject invalid start positions");
}

}  // namespace

int main() {
    test_sequential_string_basic_operations();
    test_compare_and_bounds();
    test_kmp_prefix_table();
    test_pattern_matching();
    test_empty_pattern_and_position_checks();

    if (g_failures == 0) {
        std::cout << "[PASS] all string tests passed\n";
        return EXIT_SUCCESS;
    }

    std::cerr << "[FAIL] total failures: " << g_failures << '\n';
    return EXIT_FAILURE;
}
