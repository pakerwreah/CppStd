//
// Created by Paker on 05/09/21.
//

#pragma once

#include "PK/Collection.h"

namespace PK {

    template<typename T, typename I, size_t size>
    bool operator==(const Collection<T, I> &lhs, const T(&rhs)[size]) {

        if (lhs.length() != size) return false;

        auto i1 = lhs.begin();
        const T *i2 = rhs;

        for (; i1 != lhs.end(); i1++, i2++)
            if (*i1 != *i2) return false;

        return true;
    }
}
