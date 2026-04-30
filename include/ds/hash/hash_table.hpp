#pragma once

#include <cstddef>
#include <functional>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ds::hash {

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashTable {
public:
    explicit HashTable(std::size_t bucketCount = 16)
        : buckets_(bucketCount == 0 ? 16 : bucketCount) {}

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    void put(const Key& key, const Value& value) {
        ensureLoadFactor();
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return;
            }
        }
        bucket.push_back({key, value});
        ++size_;
    }

    [[nodiscard]] bool contains(const Key& key) const {
        const auto& bucket = buckets_[bucketIndex(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] Value& at(const Key& key) {
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw std::out_of_range("key not found");
    }

    [[nodiscard]] const Value& at(const Key& key) const {
        const auto& bucket = buckets_[bucketIndex(key)];
        for (const auto& entry : bucket) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        throw std::out_of_range("key not found");
    }

    bool erase(const Key& key) {
        auto& bucket = buckets_[bucketIndex(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

private:
    [[nodiscard]] std::size_t bucketIndex(const Key& key) const {
        return hasher_(key) % buckets_.size();
    }

    void ensureLoadFactor() {
        if (size_ * 4 < buckets_.size() * 3) {
            return;
        }
        rehash(buckets_.size() * 2);
    }

    void rehash(std::size_t newBucketCount) {
        std::vector<std::list<std::pair<Key, Value>>> newBuckets(newBucketCount);

        for (auto& bucket : buckets_) {
            for (auto& entry : bucket) {
                const std::size_t index = hasher_(entry.first) % newBucketCount;
                newBuckets[index].push_back(entry);
            }
        }

        buckets_ = std::move(newBuckets);
    }

    std::vector<std::list<std::pair<Key, Value>>> buckets_;
    std::size_t size_ = 0;
    Hash hasher_;
};

}  // namespace ds::hash
