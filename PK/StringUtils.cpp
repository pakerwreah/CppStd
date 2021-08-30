//
// Created by Paker on 30/08/21.
//

#include "StringUtils.h"
#include <cstring>

namespace PK::StringUtils {

    List<String> split(const String &string, const String &separator) {
        List<String> parts;
        char *token, *ptr = const_cast<char *>(string.data());

        while ((token = strsep(&ptr, separator.data())) != nullptr) {
            if (*token != '\0')
                parts.append(token);
        }

        return parts;
    }
}
