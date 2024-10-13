#pragma once

#include <cstddef>
template <typename Key>
class Hash_function final {
public:
    unsigned long operator()(const Key& key, unsigned long table_size) const
    {
        unsigned long hash = 0;
        const char* bytes = reinterpret_cast<const char*>(&key);
        unsigned long size = sizeof(Key);
        for (size_t i = 0; i < size; ++i) {
            hash = hash * 31 + bytes[i];
        }
        return hash % table_size;
    }
};