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

        List(const List &other) {
            for (const auto &item: other)
                append(item);
        }

        List(std::initializer_list<T> items) {
            for (const auto &item: items)
                append(item);
        }

        List(List &&other) noexcept: m_begin(other.m_begin), m_end(other.m_end), m_length(other.m_length) {
            other.m_begin = nullptr;
            other.m_end = nullptr;
            other.m_length = 0;
        }

        List &operator=(const List &other) {

            if (&other != this) {
                removeAll();

                for (const auto &item: other)
                    append(item);
            }
            return *this;
        }

        List &operator=(List &&other) noexcept {

            if (&other != this) {
                removeAll();

                m_begin = other.m_begin;
                m_end = other.m_end;
                m_length = other.m_length;

                other.m_begin = nullptr;
                other.m_end = nullptr;
                other.m_length = 0;
            }
            return *this;
        }

        NodeIterator<T> begin() const override { return {m_begin}; }

        NodeIterator<T> end() const override { return {nullptr}; }

        size_t length() const override { return m_length; }

        void removeAll() {
            for (auto ptr = m_begin; ptr;) {
                auto tmp = ptr;
                ptr = ptr->next;
                delete tmp;
            }
            m_begin = nullptr;
            m_end = nullptr;
            m_length = 0;
        }

        void removeAt(size_t pos) {

            if (pos == 0) {
                auto tmp = m_begin;
                m_begin = tmp->next;
                delete tmp;
                m_length--;
                return;
            }

            auto ptr = m_begin;
            auto next = ptr->next;
            for (--pos; next && pos; pos--) {
                ptr = ptr->next;
                next = next->next;
            }

            if (next) {
                ptr->next = next->next;
                delete next;
                m_length--;
            }
        }

        void append(const T &item) {

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
