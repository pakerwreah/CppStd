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

#pragma clang diagnostic pop
