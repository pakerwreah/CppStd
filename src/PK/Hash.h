//
// Created by Paker on 05/09/21.
//

#pragma once

#include "String.h"

namespace PK {

    template<typename T>
    struct Hash {
        static size_t make(const T &value) {
            return std::hash<T>()(value);
        }
    };
}

namespace std {

    template<>
    struct hash<PK::StringView> {
        size_t operator()(const PK::StringView &key) const {
            return hash<string>()(key.data());
        }
    };

    template<>
    struct hash<PK::String> : public hash<PK::StringView> {
    };
}
