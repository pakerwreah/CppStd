//
// Created by Paker on 26/08/21.
//

#include "String.h"
#include <cstring>
#include <algorithm>

namespace PK {

    String::String(const String &other) : String(other.data(), other.length()) {}

    String::String(const StringView &other) : String(other.data(), other.length()) {}

    String::String(String &&other) noexcept {

        m_length = other.m_length;
        m_data = copy_data_if_sso(other);

        other.m_length = 0;
        other.m_data = nullptr;
    }

    String::String(const char *data) : String(data, strlen(data)) {}

    String::String(const char *data, size_t length) {
        m_length = length;
        m_data = alloc_data_or_sso(m_length);
        m_data[length] = '\0';
        std::memcpy(m_data, data, length);
    }

    String::~String() {
        if (is_sso())
            m_data = nullptr;
    }

    void String::assign(const StringView &other) {

        if (!is_sso())
            delete[] m_data;

        m_length = other.length();
        m_data = alloc_data_or_sso(m_length);

        std::copy_n(other.data(), m_length, m_data);
    }

    String &String::operator=(const String &other) {
        if (&other != this) assign(other);
        return *this;
    }

    String &String::operator=(const StringView &other) {
        if (&other != this) assign(other);
        return *this;
    }

    String &String::operator=(String &&other) noexcept {

        if (&other != this) {
            if (!is_sso())
                delete[] m_data;

            m_length = other.m_length;
            m_data = copy_data_if_sso(other);

            other.m_length = 0;
            other.m_data = nullptr;
        }
        return *this;
    }

    String String::operator+(const StringView &other) const {

        size_t total_length = m_length + other.length();
        char *result = alloc_data_or_sso(total_length);

        std::copy_n(m_data, m_length, result);
        std::copy_n(other.data(), other.length() + 1, result + m_length);

        return {result, total_length};
    }

    bool String::is_sso() const { return m_length <= sso_length; }

    char *String::alloc_data_or_sso(size_t length) const {
        return length <= sso_length ? sso_begin : new char[length + 1];
    }

    char *String::copy_data_if_sso(const String &other) {
        return static_cast<char *>(
                other.is_sso()
                ? std::memcpy(sso_data, other.sso_data, other.m_length + 1)
                : other.m_data
        );
    }
}
