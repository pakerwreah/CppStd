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
        size_t m_capacity = 16;
        List<HashNode> **map = alloc(m_capacity);

        List<HashNode> **alloc(size_t capacity) const {

            auto **new_map = new List<HashNode> *[capacity];

            for (int i = 0; i < capacity; i++)
                new_map[i] = nullptr;

            return new_map;
        }

        void resize(size_t new_capacity) {

            List<HashNode> **new_map = alloc(new_capacity);

            size_t copied = 0;
            for (int i = 0; i < m_capacity && copied < m_length; i++) {
                if (!map[i]) continue;
                for (const HashNode &node: *map[i]) {

                    size_t new_pos = node.hash % new_capacity;
                    List<HashNode> *list = new_map[new_pos];

                    if (!list) new_map[new_pos] = (list = new List<HashNode>);
                    list->append(node);
                    copied++;
                }
            }

            m_capacity = new_capacity;

            delete[] map;
            map = new_map;
        }

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
        size_t length() const { return m_length; }

        size_t capacity() const { return m_capacity; }

        V *find(const K &key) const {
            return find(key, Hash::make(key) % m_capacity);
        }

        V &operator[](const K &key) const {

            auto item = find(key);

            if (!item)
                throw std::range_error("Key not found");

            return *item;
        }

        void set(const K &key, const V &value) {

            size_t hash = Hash::make(key);
            size_t pos = hash % m_capacity;

            if (auto *item = find(key, pos)) {
                *item = value;
                return;
            }

            if (m_length >= m_capacity * 0.75) {
                size_t new_capacity = m_capacity * 2;
                resize(new_capacity);
                pos = hash % new_capacity;
            }

            List<HashNode> *list = map[pos];
            if (!list) map[pos] = (list = new List<HashNode>);

            list->append({key, value});
            m_length++;
        }

        List<Entry> entries() const {
            List<Entry> entries;
            for (int i = 0; i < m_capacity; i++) {
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
