//
// Created by Paker on 31/08/21.
//

#pragma once

#include "Collection.h"
#include <algorithm>

namespace PK {

    template<typename T>
    class Sequence : public Collection<T> {
    protected:
        size_t m_length = 0;
        T *m_data = nullptr;

        Sequence(size_t length) {
            m_length = length;
            m_data = new T[m_length];
        }

    public:
        Sequence() = default;

        Sequence(std::initializer_list<T> items) : Sequence(items.size()) {
            std::copy(items.begin(), items.end(), m_data);
        }

        Sequence(const T *data, size_t length) : Sequence(length) {
            std::copy_n(data, length, m_data);
        }

        Sequence(const Sequence &other) : Sequence(other.m_data, other.m_length) {}

        Sequence(Sequence &&other) noexcept: m_data(other.m_data), m_length(other.m_length) {
            other.m_length = 0;
            other.m_data = nullptr;
        }

        Sequence &operator=(const Sequence &other) {

            if (&other != this) {
                delete[] m_data;

                m_length = other.m_length;
                m_data = new T[m_length];

                std::copy_n(other.m_data, m_length, m_data);
            }
            return *this;
        }

        Sequence &operator=(Sequence &&other) noexcept {

            if (&other != this) {
                delete[] m_data;

                m_length = other.m_length;
                m_data = other.m_data;

                other.m_length = 0;
                other.m_data = nullptr;
            }
            return *this;
        }

        Sequence operator+(const Sequence &other) const {
            Sequence result(m_length + other.m_length);
            std::copy_n(m_data, m_length, result.m_data);
            std::copy_n(other.m_data, other.m_length, result.m_data + m_length);
            return result;
        }

        template<typename I>
        Sequence(const Collection<T, I> &other) : Sequence(other.length()) {
            std::copy(other.begin(), other.end(), m_data);
        }

        template<typename I>
        Sequence(Collection<T, I> &&other) noexcept : Sequence(other.length()) {
            std::move(other.begin(), other.end(), m_data);
        }

        ~Sequence() override {
            m_length = 0;

            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
            }
        }

        const T *data() const { return m_data; }

        T *begin() const override { return m_data; }

        T *end() const override { return m_data + m_length; }

        size_t length() const override { return m_length; }
    };
}
