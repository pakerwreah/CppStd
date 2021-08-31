//
// Created by Paker on 26/08/21.
//

#include <cstring>
#include "String.h"

namespace PK {

    String::String(const String &other) : String(other.m_data, other.m_length) {}

    String::String(String &&other) noexcept: Sequence(std::move(other)) {}

    String::String(const char *data) : String(data, strlen(data)) {}

    String::String(const char *data, size_t length) {
        m_length = length;
        m_data = alloc_or_sso(m_length);
        m_data[length] = '\0';
        std::memcpy(m_data, data, length);
    }

    String::~String() {
        if (is_sso())
            m_data = nullptr;
    }

    String &String::operator=(const String &other) {

        if (&other != this) {
            if (!is_sso())
                delete[] m_data;

            m_length = other.length();
            m_data = alloc_or_sso(m_length);

            std::copy_n(other.data(), m_length, m_data);
        }
        return *this;
    }

    String &String::operator=(String &&other) noexcept {

        if (&other != this) {
            if (!is_sso())
                delete[] m_data;

            m_length = other.length();
            m_data = other.begin();

            other.m_length = 0;
            other.m_data = nullptr;
        }
        return *this;
    }

    bool String::is_sso() const { return m_length <= sso_length; }

    char *String::alloc_or_sso(size_t length) const { return length <= sso_length ? sso_begin : new char[length + 1]; }
}
