//
// Created by Paker on 26/08/21.
//

#pragma once

#include "Collection.h"

namespace PK {

    class String : public Collection<char> {
    private:
        // small string optimization
        static constexpr int sso_length = 50;
        char sso_data[sso_length]{};
        char *m_data;
        size_t m_length;

    public:
        String(const char *data = "");
        String(const char *data, size_t length);
        String(const String &other);
        String(String &&other) noexcept;

        virtual ~String();

        String &operator=(const String &other) = default;

        const char *data() const { return m_data; }

        operator const char *() { return m_data; }

        size_t length() const override { return m_length; }

        char *begin() const override { return m_data; }

        char *end() const override { return m_data + m_length; }
    };
}
