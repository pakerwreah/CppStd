//
// Created by Paker on 31/08/21.
//

#pragma once

namespace PK {

    template<typename T, typename I>
    struct Iterable {
        virtual I begin() const = 0;
        virtual I end() const = 0;

        T operator[](int pos) const { return *(this->begin() + pos); }

        T &operator[](int pos) { return *(this->begin() + pos); }

        virtual ~Iterable() = default;
    };
}
