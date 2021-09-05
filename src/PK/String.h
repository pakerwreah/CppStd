//
// Created by Paker on 26/08/21.
//

#pragma once

#include "StringView.h"

namespace PK {

    class String final : public StringView {
    private:
        // small string optimization
        static constexpr int sso_length = 50;
        char sso_data[sso_length]{};
        char *sso_begin = sso_data;

        bool is_sso() const;
        char *alloc_data_or_sso(size_t length) const;
        char *copy_data_if_sso(const String &other);

        String(size_t length);

    public:
        String(const String &other);
        String(const StringView &other);
        String(String &&other) noexcept;
        String(const char *data = "");
        String(const char *data, size_t length);

        ~String() override;

        String &operator=(const String &other);
        String &operator=(String &&other) noexcept;
        friend String operator+(const StringView &lhs, const StringView &rhs);
    };
}
