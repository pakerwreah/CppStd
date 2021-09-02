//
// Created by Paker on 29/08/21.
//

#pragma once

#include <cstddef>
#include <iterator>

namespace PK {

    template<typename T, typename I = T *>
    struct Collection {

        virtual I begin() const = 0;
        virtual I end() const = 0;

        virtual size_t length() const = 0;

        bool isEmpty() const { return !length(); }

        T operator[](int pos) const { return *(this->begin() + pos); }

        T &operator[](int pos) { return *(this->begin() + pos); }

    private:
        template<typename O>
        bool compare(const O &other) const {

            auto i1 = begin();
            auto i2 = std::begin(other);

            for (; i1 != end(); i1++, i2++)
                if (*i1 != *i2) return false;

            return true;
        }

    public:
        template<size_t size>
        bool operator==(const T (&other)[size]) const {

            return length() == size && compare(other);
        }

        template<typename I2>
        bool operator==(const Collection<T, I2> &other) const {

            return length() == other.length() && compare(other);
        }

        template<size_t size>
        bool operator!=(const T (&other)[size]) const {

            return !this->template operator==(other);
        }

        template<typename I2>
        bool operator!=(const Collection<T, I2> &other) const {

            return !this->template operator==(other);
        }

        virtual ~Collection() = default;
    };
}
