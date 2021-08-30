//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Collection.h"
#include "PrimitiveIterator.h"
#include <initializer_list>
#include <cassert>
#include <algorithm>

namespace PK {

    template<typename T, size_t count>
    class Array : public Collection<T, PrimitiveIterator<T>> {
    private:
        T m_data[count]{};

    public:
        Array(std::initializer_list<T> items) {
            assert(items.size() == count);
            std::copy(items.begin(),  items.end(), m_data);
        }

        PrimitiveIterator<T> begin() const override { return {m_data}; }

        PrimitiveIterator<T> end() const override { return {m_data + count}; }

        size_t length() const override { return count; }
    };
}
