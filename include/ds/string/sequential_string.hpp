#pragma once

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace ds::string {

class SequentialString {
public:
    static constexpr std::size_t npos = std::string_view::npos;

    SequentialString() = default;

    explicit SequentialString(const char* text) : SequentialString(std::string_view(text == nullptr ? "" : text)) {}

    explicit SequentialString(std::string_view text) : data_(text.begin(), text.end()) {}

    [[nodiscard]] std::size_t size() const noexcept {
        return data_.size();
    }

    [[nodiscard]] bool empty() const noexcept {
        return data_.empty();
    }

    [[nodiscard]] const char* data() const noexcept {
        return data_.empty() ? "" : data_.data();
    }

    [[nodiscard]] char& operator[](std::size_t index) {
        return data_[index];
    }

    [[nodiscard]] const char& operator[](std::size_t index) const {
        return data_[index];
    }

    [[nodiscard]] char& at(std::size_t index) {
        if (index >= data_.size()) {
            throw std::out_of_range("SequentialString index out of range");
        }
        return data_[index];
    }

    [[nodiscard]] const char& at(std::size_t index) const {
        if (index >= data_.size()) {
            throw std::out_of_range("SequentialString index out of range");
        }
        return data_[index];
    }

    void clear() noexcept {
        data_.clear();
    }

    void pushBack(char ch) {
        data_.push_back(ch);
    }

    void append(std::string_view suffix) {
        data_.insert(data_.end(), suffix.begin(), suffix.end());
    }

    void append(const char* suffix) {
        append(std::string_view(suffix == nullptr ? "" : suffix));
    }

    void append(const SequentialString& suffix) {
        append(suffix.view());
    }

    void insert(std::size_t pos, std::string_view fragment) {
        if (pos > data_.size()) {
            throw std::out_of_range("SequentialString insert position out of range");
        }
        data_.insert(data_.begin() + static_cast<std::ptrdiff_t>(pos), fragment.begin(), fragment.end());
    }

    void erase(std::size_t pos, std::size_t count = 1) {
        if (pos > data_.size()) {
            throw std::out_of_range("SequentialString erase position out of range");
        }
        const std::size_t end = std::min(data_.size(), pos + count);
        data_.erase(
            data_.begin() + static_cast<std::ptrdiff_t>(pos),
            data_.begin() + static_cast<std::ptrdiff_t>(end));
    }

    [[nodiscard]] SequentialString substr(std::size_t pos, std::size_t count = npos) const {
        if (pos > data_.size()) {
            throw std::out_of_range("SequentialString substr position out of range");
        }
        const std::size_t length = std::min(count, data_.size() - pos);
        return SequentialString(view().substr(pos, length));
    }

    [[nodiscard]] int compare(const SequentialString& other) const noexcept {
        const auto lhs = view();
        const auto rhs = other.view();
        const int result = lhs.compare(rhs);
        if (result < 0) {
            return -1;
        }
        if (result > 0) {
            return 1;
        }
        return 0;
    }

    [[nodiscard]] std::string_view view() const noexcept {
        return std::string_view(data(), data_.size());
    }

    [[nodiscard]] std::string toStdString() const {
        return std::string(data_.begin(), data_.end());
    }

private:
    std::vector<char> data_;
};

inline bool operator==(const SequentialString& lhs, const SequentialString& rhs) noexcept {
    return lhs.view() == rhs.view();
}

inline bool operator!=(const SequentialString& lhs, const SequentialString& rhs) noexcept {
    return !(lhs == rhs);
}

inline std::vector<std::size_t> buildKmpNext(std::string_view pattern) {
    std::vector<std::size_t> next(pattern.size(), 0);
    std::size_t matched = 0;

    for (std::size_t i = 1; i < pattern.size(); ++i) {
        while (matched > 0 && pattern[i] != pattern[matched]) {
            matched = next[matched - 1];
        }
        if (pattern[i] == pattern[matched]) {
            ++matched;
        }
        next[i] = matched;
    }

    return next;
}

inline std::size_t naiveFind(std::string_view text, std::string_view pattern, std::size_t startPos = 0) {
    if (startPos > text.size()) {
        throw std::out_of_range("naiveFind start position out of range");
    }
    if (pattern.empty()) {
        return startPos;
    }
    if (pattern.size() > text.size() - startPos) {
        return SequentialString::npos;
    }

    for (std::size_t i = startPos; i + pattern.size() <= text.size(); ++i) {
        std::size_t j = 0;
        while (j < pattern.size() && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == pattern.size()) {
            return i;
        }
    }

    return SequentialString::npos;
}

inline std::size_t kmpFind(std::string_view text, std::string_view pattern, std::size_t startPos = 0) {
    if (startPos > text.size()) {
        throw std::out_of_range("kmpFind start position out of range");
    }
    if (pattern.empty()) {
        return startPos;
    }
    if (pattern.size() > text.size() - startPos) {
        return SequentialString::npos;
    }

    const auto next = buildKmpNext(pattern);
    std::size_t matched = 0;

    for (std::size_t i = startPos; i < text.size(); ++i) {
        while (matched > 0 && text[i] != pattern[matched]) {
            matched = next[matched - 1];
        }
        if (text[i] == pattern[matched]) {
            ++matched;
        }
        if (matched == pattern.size()) {
            return i + 1 - pattern.size();
        }
    }

    return SequentialString::npos;
}

inline std::vector<std::size_t> kmpFindAll(std::string_view text, std::string_view pattern) {
    std::vector<std::size_t> matches;
    if (pattern.empty()) {
        for (std::size_t i = 0; i <= text.size(); ++i) {
            matches.push_back(i);
        }
        return matches;
    }
    if (pattern.size() > text.size()) {
        return matches;
    }

    const auto next = buildKmpNext(pattern);
    std::size_t matched = 0;

    for (std::size_t i = 0; i < text.size(); ++i) {
        while (matched > 0 && text[i] != pattern[matched]) {
            matched = next[matched - 1];
        }
        if (text[i] == pattern[matched]) {
            ++matched;
        }
        if (matched == pattern.size()) {
            matches.push_back(i + 1 - pattern.size());
            matched = next[matched - 1];
        }
    }

    return matches;
}

inline std::size_t naiveFind(const SequentialString& text, const SequentialString& pattern, std::size_t startPos = 0) {
    return naiveFind(text.view(), pattern.view(), startPos);
}

inline std::size_t kmpFind(const SequentialString& text, const SequentialString& pattern, std::size_t startPos = 0) {
    return kmpFind(text.view(), pattern.view(), startPos);
}

inline std::vector<std::size_t> kmpFindAll(const SequentialString& text, const SequentialString& pattern) {
    return kmpFindAll(text.view(), pattern.view());
}

}  // namespace ds::string
