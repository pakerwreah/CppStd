//
// Created by Paker on 04/09/21.
//

#pragma once

#include "Hash.h"
#include "Map.h"

namespace PK {

    template<typename K, typename V>
    class HashMap : public Map<K, V> {
    private:
        using Entry = typename HashMap::Entry;

        struct Node {
            const size_t hash;
            const K key;
            V value;

            Node(const K &key, const V &value) : hash(Hash::make(key)), key{key}, value{value} {}
        };

        size_t m_length = 0;
        size_t m_capacity = 16;
        List<Node> **map = alloc(m_capacity);

        List<Node> **alloc(size_t capacity) const {

            auto **new_map = new List<Node> *[capacity];

            for (int i = 0; i < capacity; i++)
                new_map[i] = nullptr;

            return new_map;
        }

        void resize(size_t new_capacity) {

            List<Node> **new_map = alloc(new_capacity);

            size_t copied = 0;
            for (int i = 0; i < m_capacity && copied < m_length; i++) {
                if (!map[i]) continue;
                for (const Node &node: *map[i]) {

                    size_t new_pos = node.hash % new_capacity;
                    List<Node> *list = new_map[new_pos];

                    if (!list) new_map[new_pos] = (list = new List<Node>);
                    list->append(node);
                    copied++;
                }
            }

            m_capacity = new_capacity;

            delete[] map;
            map = new_map;
        }

        V *find(const K &key, size_t pos) const {

            const List<Node> *list = map[pos];

            if (list) {
                for (Node &node: *list) {
                    if (node.key == key)
                        return &node.value;
                }
            }

            return nullptr;
        }

    public:
        size_t capacity() const { return m_capacity; }

        size_t length() const override { return m_length; }

        V *find(const K &key) const override {
            return find(key, Hash::make(key) % m_capacity);
        }

        void insert(const K &key, const V &value) override {

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

            List<Node> *list = map[pos];
            if (!list) map[pos] = (list = new List<Node>);

            list->append({key, value});
            m_length++;
        }

        List<Entry> entries() const override {
            List<Entry> entries;
            for (int i = 0; i < m_capacity; i++) {
                if (!map[i]) continue;
                for (const Node &node: *map[i])
                    entries.append({node.key, node.value});
            }
            return entries;
        }
    };
}
