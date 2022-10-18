//
// Created by Paker on 05/09/21.
//

#pragma once

namespace PK {

    template<typename T>
    class Optional {
    private:
        const T *m_data;
        bool is_copy;

    public:
        explicit Optional(T *data) : m_data(data), is_copy(false) {}
        explicit Optional(const T &data) : m_data(new T(data)), is_copy(true) {}

        T operator*() const {
            if (!m_data)
                throw std::runtime_error("Cannot dereference nullptr");
            return *m_data;
        }

        const T *operator->() const { return m_data; }

        explicit operator bool() const { return m_data != nullptr; }

        bool operator==(const Optional &other) const {
            return equals(other);
        }

        bool operator!=(const Optional &other) const {
            return !equals(other);
        }

        Optional &operator=(const T &value) {
            if (is_copy)
                delete m_data;
            m_data = new T(value);
            is_copy = true;
            return *this;
        }

        Optional &operator=(const T *value) {
            if (is_copy)
                delete m_data;
            m_data = value;
            is_copy = false;
            return *this;
        }

    private:
        bool equals(const Optional &other) const {
            return this == &other
                   || m_data == other.m_data
                   || (m_data != nullptr && other.m_data != nullptr && *m_data == *(other.m_data));
        }
    };
}
