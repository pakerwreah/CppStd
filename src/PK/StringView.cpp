//
// Created by Paker on 03/09/21.
//

#include "StringView.h"

namespace PK {

    StringView::StringView(const char *data) : StringView(data, strlen(data)) {}

    StringView::StringView(const char *data, size_t length) : m_data(const_cast<char *>(data)), m_length(length) {}

    const char *StringView::data() const { return m_data; }

    size_t StringView::length() const { return m_length; }

    StringView StringView::substring(size_t start, size_t length) const { return {m_data + start, length}; }

    int StringView::indexOf(const StringView &other) const {

        if (length() < other.length()) return -1;

        size_t max = length() - other.length();

        for (int i = 0; i <= max; i++) {
            if (substring(i, other.length()) == other)
                return i;
        }

        return -1;
    }

    bool StringView::contains(const StringView &other) const { return indexOf(other) >= 0; }

    char *StringView::begin() const { return m_data; }

    char *StringView::end() const { return m_data + m_length; }

    bool operator==(const StringView &lhs, const char *rhs) { return lhs == StringView(rhs); }

    bool operator!=(const StringView &lhs, const char *rhs) { return !(lhs == rhs); }

    std::ostream &operator<<(std::ostream &os, const StringView &string) { return os << string.data(); }
}
