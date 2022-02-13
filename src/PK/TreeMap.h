//
// Created by Paker on 13/02/22.
//

#pragma once

#include "Map.h"

namespace PK {

    template<typename K, typename V>
    class TreeMap final : public Map<K, V> {
    private:
        using Entry = typename TreeMap::Entry;

        struct Node {
            const K key;
            V value;
            Node *left = nullptr;
            Node *right = nullptr;
            int height = 1;

            Node(const K &key, const V &value) : key{key}, value{value} {}
        };

        Node *root = nullptr;
        size_t m_length = 0;

        int heightOf(Node *node) const {
            return node ? node->height : 0;
        }

        int balanceOf(Node *node) const {
            return node ? heightOf(node->left) - heightOf(node->right) : 0;
        }

        Node *leftRotate(Node *node) const {

            Node *new_root = node->right;
            Node *left = new_root->left;

            new_root->left = node;
            node->right = left;

            node->height = std::max(heightOf(node->left), heightOf(node->right)) + 1;
            new_root->height = std::max(heightOf(new_root->left), heightOf(new_root->right)) + 1;

            return new_root;
        }

        Node *rightRotate(Node *node) const {

            Node *new_root = node->left;
            Node *right = new_root->right;

            new_root->right = node;
            node->left = right;

            node->height = std::max(heightOf(node->left), heightOf(node->right)) + 1;
            new_root->height = std::max(heightOf(new_root->left), heightOf(new_root->right)) + 1;

            return new_root;
        }

        Node *insert(Node *node, K key, V value) {

            if (!node) {
                ++m_length;
                return new Node(key, value);
            }

            if (key < node->key)
                node->left = insert(node->left, key, value);
            else if (key > node->key)
                node->right = insert(node->right, key, value);
            else {
                node->value = value;
                return node;
            }

            node->height = std::max(heightOf(node->left), heightOf(node->right)) + 1;

            int balance = balanceOf(node);

            // left-left
            if (balance > 1 && key < node->left->key)
                return rightRotate(node);

            // right-right
            if (balance < -1 && key > node->right->key)
                return leftRotate(node);

            // left-right
            if (balance > 1 && key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            // right-left
            if (balance < -1 && key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }

            return node;
        }

        V *find(Node *node, const K &key) const {

            if (!node)
                return nullptr;

            if (key == node->key)
                return &node->value;

            return find(key < node->key ? node->left : node->right, key);
        }

        void appendEntriesOf(Node *node, List<Entry> &entries) const {
            if (!node) return;
            appendEntriesOf(node->left, entries);
            entries.append({node->key, node->value});
            appendEntriesOf(node->right, entries);
        }

    public:
        size_t length() const override { return m_length; }

        V *find(const K &key) const override { return find(root, key); }

        void insert(const K &key, const V &value) override {
            root = insert(root, key, value);
        }

        List<Entry> entries() const override {
            List<Entry> entries;
            appendEntriesOf(root, entries);
            return entries;
        }
    };
}
