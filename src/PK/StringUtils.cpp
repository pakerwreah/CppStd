//
// Created by Paker on 30/08/21.
//

#include "StringUtils.h"
#include <iomanip>

namespace PK::StringUtils {

    List<String> split(const String &string, const String &separator) {

        List<String> parts;
        char *token, *ptr = string.begin();

        while ((token = strsep(&ptr, separator.data())) != nullptr) {
            if (*token != '\0')
                parts.append(token);
        }

        return parts;
    }

    String to_string(bool value) { return value ? "true" : "false"; }

    String to_string(int value) { return std::to_string(value).c_str(); }

    String to_string(double value, int precision) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(precision) << value;
        return stream.str().c_str();
    }
}
