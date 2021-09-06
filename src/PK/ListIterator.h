//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Iterator.h"

namespace PK {

    template<typename T>
    class ListIterator final : public Iterator<T, ListIterator<T>> {
    private:
        template<typename>
        friend
        class List;

        struct Node {
            T data;
            Node *prev = nullptr;
            Node *next = nullptr;
        };

        Node *m_ptr;

        ListIterator(Node *node) : m_ptr(node) {}

    public:
        // Prefix increment
        ListIterator &operator++() override {
            m_ptr = m_ptr->next;
            return *this;
        }

        // Postfix increment
        const ListIterator operator++(int) override { // NOLINT(readability-const-return-type)
            ListIterator tmp = *this;
            m_ptr = m_ptr->next;
            return tmp;
        }

        ListIterator operator+(int n) const override {
            ListIterator tmp = *this;
            while (0 < n--) ++tmp;
            return tmp;
        }

        T &operator*() override { return m_ptr->data; }

        operator bool() const override { return m_ptr; }

        bool operator==(const ListIterator &other) const override { return other.m_ptr == m_ptr; };

        bool operator!=(const ListIterator &other) const override { return other.m_ptr != m_ptr; };
    };
}
