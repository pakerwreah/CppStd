//
// Created by Paker on 03/09/21.
//

#include "catch.hpp"
#include "PK/String.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"
#pragma ide diagnostic ignored "cppcoreguidelines-slicing"

TEST_CASE("StringView - Constructor") {

    const char *text = "Hello";
    StringView sv = text;
    CHECK(sv.length() == 5);
    CHECK(sv.begin() == text);
    CHECK(sv.end() == text + 5);
}

TEST_CASE("StringView - String") {

    String string = "Hello";
    StringView sv = string;
    CHECK(sv.length() == string.length());
    CHECK(sv.begin() == string.begin());
    CHECK(sv.end() == string.end());
}

TEST_CASE("StringView - Copy") {

    StringView sv1 = "Hello";
    StringView sv2 = sv1;
    CHECK(sv1.length() == sv2.length());
    CHECK(sv1.begin() == sv2.begin());
    CHECK(sv1.end() == sv2.end());
}

TEST_CASE("StringView - Equals") {

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

TEST_CASE("StringView - Substring") {

    StringView string = "Hello World!";
    CHECK(string.substring(6, 5) == "World");
}

TEST_CASE("StringView - IndexOf") {

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

TEST_CASE("StringView - Contains") {

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

#pragma clang diagnostic pop
