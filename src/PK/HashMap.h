//
// Created by Paker on 04/09/21.
//

#pragma once

#include "List.h"
#include "Hash.h"

namespace PK {

    template<typename K, typename V, typename Hash = Hash<K>>
    class HashMap {
    public:
        struct Entry {
            const K key;
            V value;
        };

    private:
        struct HashNode : public Entry {
            const size_t hash;

            HashNode(const K &key, const V &value)
                    : Entry{key, value}
                    , hash(Hash::make(key)) {}
        };

        size_t m_length = 0;
        size_t capacity = 16;
        List<HashNode> **map = new List<HashNode> *[capacity];

        V *find(const K &key, size_t pos) const {

            const List<HashNode> *list = map[pos];

            if (list) {
                for (Entry &entry: *list) {
                    if (entry.key == key)
                        return &entry.value;
                }
            }

            return nullptr;
        }

    public:
        HashMap() {
            for (int i = 0; i < capacity; i++)
                map[i] = nullptr;
        }

        size_t length() const { return m_length; }

        V *find(const K &key) const {
            return find(key, Hash::make(key) % capacity);
        }

        V &operator[](const K &key) const {

            auto item = find(key);

            if (!item)
                throw std::range_error("Key not found");

            return *item;
        }

        void set(const K &key, const V &value) {

            size_t pos = Hash::make(key) % capacity;

            if (auto *item = find(key, pos)) {
                *item = value;
                return;
            }

            List<HashNode> *list = map[pos];
            if (!list) map[pos] = (list = new List<HashNode>);

            list->append({key, value});
            m_length++;
        }

        List<Entry> entries() const {
            List<Entry> entries;
            for (int i = 0; i < capacity; i++) {
                if (!map[i]) continue;
                for (const Entry &entry: *map[i])
                    entries.append(entry);
            }
            return entries;
        }

        List<K> keys() const {
            List<K> keys;
            for (const Entry &entry: entries())
                keys.append(entry.key);
            return keys;
        }

        List<V> values() const {
            List<V> values;
            for (const Entry &entry: entries())
                values.append(entry.value);
            return values;
        }
    };
}
