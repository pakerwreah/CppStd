//
// Created by Paker on 31/08/21.
//

#pragma once

namespace PK {

    template<typename T, typename I>
    struct Iterator {
        virtual T operator*() const = 0;
        virtual T &operator*() = 0;
        virtual I &operator++() = 0;
        virtual const I operator++(int) = 0;
        virtual I operator+(int n) const = 0;
        virtual bool operator==(const I &other) const = 0;
        virtual bool operator!=(const I &other) const = 0;
        virtual ~Iterator() = default;
    };
}
