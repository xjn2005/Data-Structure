#include <iostream>
#include <vector>

#include "ds/string/sequential_string.hpp"

int main() {
    ds::string::SequentialString text("ababcabcacbab");
    ds::string::SequentialString pattern("abcac");

    text.append("!");
    text.erase(text.size() - 1);

    const std::size_t naivePos = ds::string::naiveFind(text, pattern);
    const std::size_t kmpPos = ds::string::kmpFind(text, pattern);
    const std::vector<std::size_t> allMatches = ds::string::kmpFindAll(
        ds::string::SequentialString("aaaaa"),
        ds::string::SequentialString("aa"));

    std::cout << "text: " << text.toStdString() << '\n';
    std::cout << "pattern: " << pattern.toStdString() << '\n';
    std::cout << "naive match position: " << naivePos << '\n';
    std::cout << "kmp match position: " << kmpPos << '\n';
    std::cout << "all matches in aaaaa for aa:";
    for (std::size_t pos : allMatches) {
        std::cout << ' ' << pos;
    }
    std::cout << '\n';

    return 0;
}
