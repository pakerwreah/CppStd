//
// Created by Paker on 13/02/22.
//

#pragma once

#include "List.h"

namespace PK {

    template<typename K, typename V>
    struct Map {
        struct Entry {
            const K key;
            const V value;
            bool operator==(const Entry &other) const { return key == other.key && value == other.value; }
            bool operator!=(const Entry &other) const { return key != other.key || value != other.value; }
        };
        virtual size_t length() const = 0;
        virtual V *find(const K &key) const = 0;
        virtual V &operator[](const K &key) const = 0;
        virtual void insert(const K &key, const V &value) = 0;
        virtual List<Entry> entries() const = 0;
        virtual List<K> keys() const = 0;
        virtual List<V> values() const = 0;
    };
}
