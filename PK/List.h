//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Collection.h"
#include "NodeIterator.h"
#include <initializer_list>

namespace PK {

    template<typename T>
    class List : public Collection<T, NodeIterator<T>> {
    private:
        Node<T> *m_begin = nullptr;
        Node<T> *m_end = nullptr;
        size_t m_length = 0;

    public:
        List() = default;

        List(std::initializer_list<T> items) {
            for (const auto &item: items)
                append(item);
        }

        NodeIterator<T> begin() const override { return {m_begin}; }

        NodeIterator<T> end() const override { return {nullptr}; }

        size_t length() const override { return m_length; }

        void append(T item) {

            auto new_node = new Node<T>{item};

            if (!m_begin) {
                m_begin = new_node;
                m_end = m_begin;
            } else {
                m_end->next = new_node;
                m_end = new_node;
            }

            m_length++;
        }
    };
}