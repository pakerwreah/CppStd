//
// Created by Paker on 30/08/21.
//

#include "StringUtils.h"
#include "List.h"

namespace PK::StringUtils {

    Sequence<String> split(const String &string, const String &separator) {

        List<String> parts;
        char *token, *ptr = string.begin();

        while ((token = strsep(&ptr, separator.data())) != nullptr) {
            if (*token != '\0')
                parts.append(token);
        }

        return std::move(parts);
    }
}
