//
// Created by Paker on 29/08/21.
//

#pragma once

#include "Collection.h"
#include "PrimitiveIterator.h"

namespace PK {

    template<typename T, int count>
    class Array : public Collection<T, PrimitiveIterator<T>> {
    private:
        using Iterator = PrimitiveIterator<T>;

        T m_data[count]{};

    public:
        Array(std::initializer_list<T> data) {
            memcpy(m_data, data.begin(), count * sizeof(T));
        }

        Iterator begin() const override { return {m_data}; }

        Iterator end() const override { return {m_data + count}; }

        size_t length() const override { return count; }
    };
}
