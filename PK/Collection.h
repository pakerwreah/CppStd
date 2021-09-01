//
// Created by Paker on 29/08/21.
//

#pragma once

#include <cstddef>

namespace PK {

    template<typename T, typename I = T *>
    struct Collection {

        virtual I begin() const = 0;
        virtual I end() const = 0;

        virtual size_t length() const = 0;

        bool isEmpty() const { return !length(); }

        T operator[](int pos) const { return *(this->begin() + pos); }

        T &operator[](int pos) { return *(this->begin() + pos); }

        virtual ~Collection() = default;
    };
}
