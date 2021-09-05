//
// Created by Paker on 30/08/21.
//

#pragma once

#include "List.h"
#include "String.h"
#include <sstream>

namespace PK::StringUtils {

    String to_string(bool value);
    String to_string(int value);
    String to_string(double value, int precision);

    template<typename T, typename I>
    String join(const Collection<T, I> &items, const char *glue) {
        std::ostringstream os;
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it != items.begin())
                os << glue;
            os << *it;
        }
        return os.str().c_str();
    }

    List<String> split(const String &string, const String &separator);
}
