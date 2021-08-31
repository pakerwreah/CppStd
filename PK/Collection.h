//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Iterable.h"
#include <cstddef>

namespace PK {

    template<typename T, typename I = T *>
    struct Collection : public Iterable<T, I> {

        virtual size_t length() const = 0;

        bool is_empty() const { return !length(); }
    };
}
