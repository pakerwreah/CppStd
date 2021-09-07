//
// Created by Paker on 29/08/21.
//

#pragma once

#include <cstddef>

namespace PK {

    template<typename T, typename I = T *>
    struct Collection {

        virtual ~Collection() = default;

        virtual I begin() const = 0;
        virtual I end() const = 0;

        virtual size_t length() const = 0;

        [[nodiscard]] bool empty() const { return !length(); }

        bool contains(const T &value) const {
            for (const T &item: *this) {
                if (item == value)
                    return true;
            }
            return false;
        }

        T operator[](int pos) const { return *(this->begin() + pos); }

        T &operator[](int pos) { return *(this->begin() + pos); }

        template<typename I2>
        bool operator==(const Collection<T, I2> &other) const { return equals(other); }

        template<typename I2>
        bool operator!=(const Collection<T, I2> &other) const { return !equals(other); }

        template<typename I2>
        bool operator<(const Collection<T, I2> &other) const {

            if (&other == this) return false;

            if (length() > other.length()) return false;
            if (length() < other.length()) return true;

            auto i1 = begin();
            auto i2 = other.begin();

            for (; i1 != end(); i1++, i2++)
                if (*i1 != *i2) return *i1 < *i2;

            return false;
        }

    private:
        template<typename I2>
        bool equals(const Collection<T, I2> &other) const {

            if (&other == this) return true;

            if (length() != other.length()) return false;

            auto i1 = begin();
            auto i2 = other.begin();

            for (; i1 != end(); i1++, i2++)
                if (*i1 != *i2) return false;

            return true;
        }
    };
}
