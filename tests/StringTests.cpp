//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "PK/String.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "bugprone-use-after-move"
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

TEST_CASE("String - Loops") {
    const char *expected = "Hello, World!";
    String text = "Hello, World!";

    SECTION("Range loop") {
        int i = 0;
        for (char c: text)
            CHECK(c == expected[i++]);
    }

    SECTION("Index loop") {
        for (int i = 0; i < text.length(); i++)
            CHECK(text[i] == expected[i]);
    }

    SECTION("Iterator loop") {
        int i = 0;
        for (auto it = text.begin(); it != text.end(); it++)
            CHECK(*it == expected[i++]);
    }
}

TEST_CASE("String - Constructors") {
    const char *expected = "Hello, World!";
    String text = "Hello, World!";

    SECTION("Length") {
        CHECK(text.length() == 13);
    }

    SECTION("Copy") {
        String copy = text;

        CHECK(copy.length() == 13);
        CHECK(copy.begin() != text.begin());
        CHECK(copy == expected);

        CHECK(text.length() == 13);
        CHECK(text.begin() != nullptr);
    }

    SECTION("Move - SSO") {
        auto begin = text.begin();
        String moved = std::move(text);

        CHECK(moved.length() == 13);
        CHECK(moved.begin() != begin);
        CHECK(moved == expected);

        CHECK(text.length() == 0);
        CHECK(text.begin() == nullptr);
    }

    SECTION("Move") {
        const char *long_expected = "Hello, World! Hello, World! Hello, World! Hello, World!";
        String long_text = "Hello, World! Hello, World! Hello, World! Hello, World!";
        auto begin = long_text.begin();
        String moved = std::move(long_text);

        CHECK(moved.length() == 55);
        CHECK(moved.begin() == begin);
        CHECK(moved == long_expected);

        CHECK(long_text.length() == 0);
        CHECK(long_text.begin() == nullptr);
    }
}

TEST_CASE("String - Assignment") {
    const char *expected = "Hello";
    String text = "Hello";

    SECTION("Copy") {
        String copy = "";
        copy = text;

        CHECK(copy.begin() != text.begin());
        CHECK(copy.length() == 5);
        CHECK(copy == expected);

        CHECK(text.begin() != nullptr);
        CHECK(text.length() == 5);
        CHECK(text == expected);
    }

    SECTION("Move - SSO") {
        auto begin = text.begin();
        String moved = "";
        moved = std::move(text);

        CHECK(moved.begin() != begin);
        CHECK(moved.length() == 5);
        CHECK(moved == expected);

        CHECK(text.begin() == nullptr);
        CHECK(text.length() == 0);
    }

    SECTION("Move") {
        const char *long_expected = "Hello, World! Hello, World! Hello, World! Hello, World!";
        String long_text = "Hello, World! Hello, World! Hello, World! Hello, World!";
        auto begin = long_text.begin();
        String moved = "";
        moved = std::move(long_text);

        CHECK(moved.begin() == begin);
        CHECK(moved.length() == 55);
        CHECK(moved == long_expected);

        CHECK(long_text.begin() == nullptr);
        CHECK(long_text.length() == 0);
    }
}

TEST_CASE("String - Concat") {
    const char *expected = "Hello, World!";
    String text1 = "Hello";
    String text2 = "World!";
    CHECK(text1 + ", " + text2 == expected);
}

TEST_CASE("String - Equals") {

    CHECK(String("Hello") == String("Hello"));
    CHECK(String("Hellu") != String("Hello"));
    CHECK_FALSE(String("Hellu") == String("Hello"));

    const char *other = "Hello";

    CHECK(String("Hello") == other);
    CHECK_FALSE(String("Hellu") == other);

    CHECK(other == String("Hello"));
    CHECK_FALSE(other == String("Hellu"));

    CHECK(String("Hellu") != other);
    CHECK_FALSE(String("Hello") != other);

    CHECK(other != String("Hellu"));
    CHECK_FALSE(other != String("Hello"));
}
