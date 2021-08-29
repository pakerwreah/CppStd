//
// Created by Paker on 29/08/21.
//

#pragma once

#include <cstddef>

namespace PK {

    template<typename Iterator>
    struct Iterable {
        virtual Iterator begin() const = 0;
        virtual Iterator end() const = 0;
    };

    template<typename T, typename Iterator>
    struct Collection : public Iterable<Iterator> {

        virtual size_t length() const = 0;

        bool is_empty() const { return !length(); }

        T operator[](int pos) const { return *(this->begin() + pos); }
    };
}
