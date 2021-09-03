//
// Created by Paker on 03/09/21.
//

#include "StringView.h"
#include <ostream>

namespace PK {

    const char *StringView::data() const { return m_data; }

    size_t StringView::length() const { return m_length; }

    char *StringView::begin() const { return m_data; }

    char *StringView::end() const { return m_data + m_length; }

    StringView::StringView(const char *data) : StringView(data, strlen(data)) {}

    StringView::StringView(const char *data, size_t length) : m_data(const_cast<char *>(data)), m_length(length) {}

    bool operator==(const StringView &lhs, const char *rhs) { return std::strcmp(lhs.data(), rhs) == 0; }

    bool operator!=(const StringView &lhs, const char *rhs) { return !(lhs == rhs); }

    std::ostream &operator<<(std::ostream &os, const StringView &string) { return os << string.data(); }
}
