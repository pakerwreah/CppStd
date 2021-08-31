//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Iterator.h"

namespace PK {

    namespace {
        template<typename T>
        struct Node {
            T data;
            Node *next = nullptr;
        };

        template<typename T>
        class NodeIterator : public Iterator<T, NodeIterator<T>> {
        private:
            Node<T> *m_ptr;

        public:
            NodeIterator(Node<T> *ptr) : m_ptr(ptr) {}

            // Prefix increment
            NodeIterator &operator++() override {
                m_ptr = m_ptr->next;
                return *this;
            }

            // Postfix increment
            const NodeIterator operator++(int) override { // NOLINT(readability-const-return-type)
                NodeIterator tmp = *this;
                m_ptr = m_ptr->next;
                return tmp;
            }

            NodeIterator operator+(int n) const override {
                NodeIterator tmp = *this;
                while (n--) ++tmp;
                return tmp;
            }

            T operator*() const override { return m_ptr->data; }

            T &operator*() override { return m_ptr->data; }

            bool operator==(const NodeIterator &other) const override { return other.m_ptr == m_ptr; };

            bool operator!=(const NodeIterator &other) const override { return other.m_ptr != m_ptr; };
        };
    }
}
