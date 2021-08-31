//
// Created by Paker on 26/08/21.
//

#pragma once

#include "Sequence.h"

namespace PK {

    class String final : public Sequence<char> {
    private:
        // small string optimization
        static constexpr int sso_length = 50;
        char sso_data[sso_length]{};
        char *sso_begin = sso_data;

        bool is_sso() const;
        char *alloc_or_sso(size_t length) const;

    public:
        String(const String &other);
        String(String &&other) noexcept;
        String(const char *data = "");
        String(const char *data, size_t length);

        ~String() override;

        String &operator=(const String &other);
        String &operator=(String &&other) noexcept;

        operator const char *() { return data(); }
    };
}
