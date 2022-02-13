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

TEST_CASE("String") {

    SECTION("Loops") {
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

    SECTION("Constructors") {
        const char *expected = "Hello, World!";
        String text = "Hello, World!";

        SECTION("Length") {
            CHECK(text.length() == 13);
        }

        SECTION("StringView") {
            String copy = StringView("Hello, World!");
            CHECK(copy.length() == 13);
            CHECK(copy.begin() != text.begin());
            CHECK(copy == expected);
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

    SECTION("Assignment") {

        SECTION("Copy - SSO <- SSO") {
            String text = "Hello";
            String copy = "Hello World!";
            copy = text;

            CHECK(copy.begin() != text.begin());
            CHECK(copy.length() == 5);
            CHECK(copy == "Hello");

            CHECK(text.begin() != nullptr);
            CHECK(text.length() == 5);
            CHECK(text == "Hello");
        }

        SECTION("Copy - Long <- SSO") {
            String copy = "Hello, World! Hello, World! Hello, World! Hello, World!";
            String other = "Hello, World!";
            copy = other;

            CHECK(copy.begin() != other.begin());
            CHECK(copy.length() == 13);
            CHECK(copy == "Hello, World!");

            CHECK(other.begin() != nullptr);
            CHECK(other.length() == 13);
            CHECK(other == "Hello, World!");
        }

        SECTION("Copy - Long <- Long") {
            String copy = "Hello, World! Hello, World! Hello, World! Hello, World!";
            String other = "Hello, World! Hello, World! Hello, World! Hello, World! Copy";
            copy = other;

            CHECK(copy.begin() != other.begin());
            CHECK(copy.length() == 60);
            CHECK(copy == "Hello, World! Hello, World! Hello, World! Hello, World! Copy");

            CHECK(other.begin() != nullptr);
            CHECK(other.length() == 60);
            CHECK(other == "Hello, World! Hello, World! Hello, World! Hello, World! Copy");
        }

        SECTION("Move - SSO <- SSO") {
            String text = "Hello";
            String copy = "Hello World!";
            copy = std::move(text);

            CHECK(copy.begin() != text.begin());
            CHECK(copy.length() == 5);
            CHECK(copy == "Hello");

            CHECK(text.begin() == nullptr);
            CHECK(text.length() == 0);
        }

        SECTION("Move - Long <- SSO") {
            String other = "Hello, World!";
            auto begin = other.begin();
            String moved = "Hello, World! Hello, World! Hello, World! Hello, World!";
            moved = std::move(other);

            CHECK(moved.begin() != begin);
            CHECK(moved.length() == 13);
            CHECK(moved == "Hello, World!");

            CHECK(other.begin() == nullptr);
            CHECK(other.length() == 0);
        }

        SECTION("Move - Long <- Long") {
            String other = "Hello, World! Hello, World! Hello, World! Hello, World! Move";
            auto begin = other.begin();
            String moved = "Hello, World! Hello, World! Hello, World! Hello, World!";
            moved = std::move(other);

            CHECK(moved.begin() == begin);
            CHECK(moved.length() == 60);
            CHECK(moved == "Hello, World! Hello, World! Hello, World! Hello, World! Move");

            CHECK(other.begin() == nullptr);
            CHECK(other.length() == 0);
        }
    }

    SECTION("Concat") {
        const char *expected = "Hello, World!";
        String text1 = "Hello";
        String text2 = "World!";
        CHECK(text1 + ", " + text2 == expected);
    }

    SECTION("Equals") {

        CHECK(String("Hello") == String("Hello"));
        CHECK(String("Hellu") != String("Hello"));
        CHECK_FALSE(String("Hellu") == String("Hello"));

        const char *text = "Hello";

        CHECK(String("Hello") == text);
        CHECK_FALSE(String("Hellu") == text);

        CHECK(String("Hellu") != text);
        CHECK_FALSE(String("Hello") != text);
    }
}
