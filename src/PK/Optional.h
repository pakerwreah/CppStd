//
// Created by Paker on 05/09/21.
//

#pragma once

namespace PK {

    template<typename T>
    class Optional {
    private:
        T *m_data;

    public:
        Optional(T *data) : m_data(data) {}

        void clear() { m_data = nullptr; }

        T operator*() const {
            if (!m_data)
                throw std::runtime_error("Cannot dereference nullptr");
            return *m_data;
        }

        T *operator->() const { return m_data; }

        operator bool() const { return m_data != nullptr; }

        bool operator==(const T &other) const {
            return m_data != nullptr && *m_data == other;
        }

        template<typename V>
        Optional &operator=(const V &value) {
            if (!m_data)
                throw std::runtime_error("Cannot assign to nullptr");
            *m_data = value;
            return *this;
        }

        Optional &operator=(const T *value) {
            m_data = value;
            return *this;
        }
    };
}
