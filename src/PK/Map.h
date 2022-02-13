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
            bool operator==(const Entry &other) const;
            bool operator!=(const Entry &other) const;
        };

        virtual size_t length() const = 0;
        virtual V *find(const K &key) const = 0;
        virtual void insert(const K &key, const V &value) = 0;
        virtual List<Entry> entries() const = 0;

        virtual List<K> keys() const;
        virtual List<V> values() const;
        virtual V &operator[](const K &key) const;
    };

    template<typename K, typename V>
    bool Map<K, V>::Entry::operator==(const Map::Entry &other) const {
        return key == other.key && value == other.value;
    }

    template<typename K, typename V>
    bool Map<K, V>::Entry::operator!=(const Map::Entry &other) const {
        return key != other.key || value != other.value;
    }

    template<typename K, typename V>
    List<K> Map<K, V>::keys() const {
        List<K> keys;
        for (const Entry &entry: entries())
            keys.append(entry.key);
        return keys;
    }

    template<typename K, typename V>
    List<V> Map<K, V>::values() const {
        List<V> values;
        for (const Entry &entry: entries())
            values.append(entry.value);
        return values;
    }

    template<typename K, typename V>
    V &Map<K, V>::operator[](const K &key) const {
        if (V *item = find(key))
            return *item;
        throw std::range_error("Key not found");
    }
}
