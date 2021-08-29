//
// Created by Paker on 29/08/21.
//

#pragma once

namespace PK {

    namespace {
        template<typename T>
        class PrimitiveIterator {
        private:
            T *m_ptr;

        public:
            PrimitiveIterator(T *ptr) : m_ptr(ptr) {}

            PrimitiveIterator(const T *ptr) : m_ptr((T *) ptr) {}

            T operator*() const { return *m_ptr; }

            // Prefix increment
            PrimitiveIterator &operator++() {
                m_ptr++;
                return *this;
            }

            // Postfix increment
            PrimitiveIterator operator++(int) { // NOLINT(cert-dcl21-cpp)
                PrimitiveIterator tmp = *this;
                m_ptr++;
                return tmp;
            }

            PrimitiveIterator operator+(int n) {
                PrimitiveIterator tmp = *this;
                tmp.m_ptr += n;
                return tmp;
            }

            bool operator==(const PrimitiveIterator &other) { return other.m_ptr == m_ptr; };

            bool operator!=(const PrimitiveIterator &other) { return other.m_ptr != m_ptr; };
        };
    }
}
