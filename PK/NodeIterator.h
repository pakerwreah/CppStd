//
// Created by Paker on 29/08/21.
//

#pragma once

namespace PK {

    namespace {
        template<typename T>
        struct Node {
            T data;
            Node *next = nullptr;
        };

        template<typename T>
        class NodeIterator {
        private:
            Node<T> *m_ptr;

        public:
            NodeIterator(Node<T> *ptr) : m_ptr(ptr) {}

            T operator*() const { return m_ptr->data; }

            // Prefix increment
            NodeIterator &operator++() {
                m_ptr = m_ptr->next;
                return *this;
            }

            // Postfix increment
            NodeIterator operator++(int) { // NOLINT(cert-dcl21-cpp)
                NodeIterator tmp = *this;
                m_ptr = m_ptr->next;
                return tmp;
            }

            NodeIterator operator+(int n) {
                NodeIterator tmp = *this;
                while(n--) tmp++;
                return tmp;
            }

            bool operator==(const NodeIterator &other) { return other.m_ptr == m_ptr; };

            bool operator!=(const NodeIterator &other) { return other.m_ptr != m_ptr; };
        };
    }
}
