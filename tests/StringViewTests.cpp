//
// Created by Paker on 03/09/21.
//

#include "lib/catch.hpp"
#include "PK/String.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"

TEST_CASE("StringView") {

    SECTION("Constructor") {

        const char *text = "Hello";
        StringView sv = text;
        CHECK(sv.length() == 5);
        CHECK(sv.begin() == text);
        CHECK(sv.end() == text + 5);
    }

    SECTION("String") {

        String string = "Hello";
        StringView sv = string;
        CHECK(sv.length() == string.length());
        CHECK(sv.begin() == string.begin());
        CHECK(sv.end() == string.end());
    }

    SECTION("Copy") {

        StringView sv1 = "Hello";
        StringView sv2 = sv1;
        CHECK(sv1.length() == sv2.length());
        CHECK(sv1.begin() == sv2.begin());
        CHECK(sv1.end() == sv2.end());
    }

    SECTION("Equals") {

        StringView string = "Hello";

        SECTION("YES") {
            StringView other = "Hello";
            CHECK(string == other);
        }

        SECTION("NO") {
            StringView other = "Hellu";
            CHECK_FALSE(string == other);
        }
    }

    SECTION("Less") {

        StringView string = "Hello";

        CHECK(StringView("Hell") < string);
        CHECK(StringView("Helli") < string);
        CHECK_FALSE(StringView("Hello") < string);
        CHECK_FALSE(StringView("Hellu") < string);
        CHECK_FALSE(StringView("Hello!") < string);
    }

    SECTION("Substring") {

        StringView string = "Hello World!";
        CHECK(string.substring(6, 5) == "World");
    }

    SECTION("IndexOf") {

        StringView string = "Hello World!";

        SECTION("Begin") {
            CHECK(string.indexOf("Hello World!") == 0);
        }

        SECTION("Middle") {
            CHECK(string.indexOf("World!") == 6);
        }

        SECTION("Not found") {
            CHECK(string.indexOf("Worlds") == -1);
        }
    }

    SECTION("Contains") {

        StringView string = "Hello World!";

        SECTION("YES - Equal") {
            CHECK(string.contains("Hello World!"));
        }

        SECTION("YES - Smaller") {
            CHECK(string.contains("World"));
        }

        SECTION("NO - Bigger") {
            CHECK_FALSE(string.contains("Hello World!!!"));
        }

        SECTION("NO - Smaller") {
            CHECK_FALSE(string.contains("Hellu"));
        }
    }
}

#pragma clang diagnostic pop
