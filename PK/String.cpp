//
// Created by Paker on 26/08/21.
//

#include <cstring>
#include "String.h"

namespace PK {

    String::String(const char *data) : String(data, strlen(data)) {}

    String::String(const char *data, size_t length) {

        m_length = length;
        m_data = length < sso_length ? sso_data : new char[length + 1];
        m_data[length] = '\0';
        memcpy(m_data, data, length);
    }

    String::~String() {
        if (m_data != sso_data)
            delete[] m_data;
    }
}
