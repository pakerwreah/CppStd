//
// Created by Paker on 29/08/21.
//

#pragma once

#include <type_traits>

namespace PK {

    template<typename T, typename I>
    struct Iterator {
        virtual T operator*() const = 0;
        virtual I &operator++() = 0;
        virtual const I operator++(int) = 0;
        virtual I operator+(int n) = 0;
        virtual bool operator==(const I &other) = 0;
        virtual bool operator!=(const I &other) = 0;
    };

    template<typename T, typename I>
    struct Iterable {
        static_assert(std::is_base_of_v<Iterator<T, I>, I>, "Template argument 'I' should be an 'Iterator'");

        virtual I begin() const = 0;
        virtual I end() const = 0;

        T operator[](int pos) const { return *(this->begin() + pos); }
    };

    template<typename T, typename I>
    struct Collection : public Iterable<T, I> {

        virtual size_t length() const = 0;

        bool is_empty() const { return !length(); }
    };
}