//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Collection.h"
#include <initializer_list>
#include <cassert>
#include <algorithm>

namespace PK {

    template<typename T, size_t count>
    class Array : public Collection<T> {
    private:
        T m_data[count]{};
        T* m_begin = m_data;

    public:
        Array(std::initializer_list<T> items) {
            assert(items.size() == count);
            std::copy(items.begin(), items.end(), m_data);
        }

        T *begin() const override { return m_begin; }

        T *end() const override { return m_begin + count; }

        size_t length() const override { return count; }
    };
}
