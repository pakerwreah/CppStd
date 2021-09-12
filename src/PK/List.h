//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Collection.h"
#include "ListIterator.h"
#include <initializer_list>

namespace PK {

    template<typename T>
    class List final : public Collection<T, ListIterator<T>> {
    private:
        using Iterator = ListIterator<T>;
        using Node = typename Iterator::Node;

        Node *m_begin = nullptr;
        Node *m_end = nullptr;
        size_t m_length = 0;

        void removeNode(Node *&ptr) {

            *(ptr->next ? &ptr->next->prev : &m_end) = ptr->prev;
            *(ptr->prev ? &ptr->prev->next : &m_begin) = ptr->next;

            auto next = ptr->next;

            delete ptr;
            ptr = next;

            m_length--;
        }

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

        ~List() override { removeAll(); }

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

        Iterator begin() const override { return {m_begin}; }

        Iterator end() const override { return {nullptr}; }

        size_t length() const override { return m_length; }

        void removeAll() {

            for (auto ptr = m_begin; ptr;) {
                auto next = ptr->next;
                delete ptr;
                ptr = next;
            }
            m_begin = nullptr;
            m_end = nullptr;
            m_length = 0;
        }

        void removeAt(size_t pos) {

            auto ptr = m_begin;
            while (pos--) ptr = ptr->next;
            removeNode(ptr);
        }

        void remove(Iterator &iterator) { removeNode(iterator.m_ptr); }

        void append(const T &item) {

            m_length++;

            auto new_node = new Node{item};

            if (!m_begin) {
                m_begin = new_node;
                m_end = new_node;
            } else {
                m_end->next = new_node;
                new_node->prev = m_end;
                m_end = new_node;
            }
        }
    };
}
