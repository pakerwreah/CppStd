//
// Created by Paker on 26/08/21.
//

#include <cstring>
#include "String.h"
#include <ostream>

namespace PK {

    String::String(const String &other) : String(other.m_data, other.m_length) {}

    String::String(String &&other) noexcept {

        m_length = other.m_length;
        m_data = copy_if_sso(other);

        other.m_length = 0;
        other.m_data = nullptr;
    }

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

            m_length = other.m_length;
            m_data = alloc_or_sso(m_length);

            std::copy_n(other.m_data, m_length, m_data);
        }
        return *this;
    }

    String &String::operator=(String &&other) noexcept {

        if (&other != this) {
            if (!is_sso())
                delete[] m_data;

            m_length = other.m_length;
            m_data = copy_if_sso(other);

            other.m_length = 0;
            other.m_data = nullptr;
        }
        return *this;
    }

    String String::operator+(const String &other) const {

        size_t total_length = m_length + other.m_length;
        char *result = alloc_or_sso(total_length);

        std::copy_n(m_data, m_length, result);
        std::copy_n(other.m_data, other.m_length + 1, result + m_length);

        return {result, total_length};
    }

    bool String::is_sso() const { return m_length <= sso_length; }

    char *String::alloc_or_sso(size_t length) const {
        return length <= sso_length ? sso_begin : new char[length + 1];
    }

    char *String::copy_if_sso(const String &other) {
        return static_cast<char *>(
                other.is_sso()
                ? std::memcpy(sso_data, other.sso_data, other.m_length + 1)
                : other.m_data
        );
    }

    bool operator==(const String &lhs, const char *rhs) { return std::strcmp(lhs.data(), rhs) == 0; }

    bool operator!=(const String &lhs, const char *rhs) { return !(lhs == rhs); }

    bool operator==(const char *lhs, const String &rhs) { return rhs == lhs; }

    bool operator!=(const char *lhs, const String &rhs) { return rhs != lhs; }

    std::ostream &operator<<(std::ostream &os, const PK::String &string) { return os << string.data(); }
}
