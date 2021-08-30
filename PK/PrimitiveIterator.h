//
// Created by Paker on 29/08/21.
//

#pragma once

namespace PK {

    namespace {
        template<typename T>
        class PrimitiveIterator : public Iterator<T, PrimitiveIterator<T>> {
        private:
            T *m_ptr;

        public:
            PrimitiveIterator(T *ptr) : m_ptr(ptr) {}

            PrimitiveIterator(const T *ptr) : m_ptr((T *) ptr) {}

            T operator*() const override { return *m_ptr; }

            // Prefix increment
            PrimitiveIterator &operator++() override {
                m_ptr++;
                return *this;
            }

            // Postfix increment
            const PrimitiveIterator operator++(int) override { // NOLINT(readability-const-return-type)
                PrimitiveIterator tmp = *this;
                m_ptr++;
                return tmp;
            }

            PrimitiveIterator operator+(int n) override {
                PrimitiveIterator tmp = *this;
                tmp.m_ptr += n;
                return tmp;
            }

            bool operator==(const PrimitiveIterator &other) override { return other.m_ptr == m_ptr; };

            bool operator!=(const PrimitiveIterator &other) override { return other.m_ptr != m_ptr; };
        };
    }
}
