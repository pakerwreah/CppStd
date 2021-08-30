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
        if (m_length >= sso_length)
            delete[] m_data;
    }

    String::String(const String &other) : String(other.m_data, other.m_length) {}

    String::String(String &&other) noexcept: m_data(other.m_data), m_length(other.m_length) {
        other.m_length = 0;
        other.m_data = nullptr;
    }
}