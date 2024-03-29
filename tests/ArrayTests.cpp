//
// Created by Paker on 01/09/21.
//

#include "lib/catch.hpp"
#include "TestUtils.h"
#include "PK/Array.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"

TEST_CASE("Array") {

    SECTION("Empty") {

        SECTION("YES") {
            Array<int, 0> array = {};
            CHECK(array.empty());
            CHECK(array.length() == 0);
        }

        SECTION("NO") {
            Array<int, 1> array = {1};
            CHECK_FALSE(array.empty());
            CHECK(array.length() == 1);
        }
    }

    SECTION("Loops") {
        int expected[] = {1, 2, 3, 4, 5};
        Array<int, 5> array = {1, 2, 3, 4, 5};

        SECTION("Range loop") {
            int i = 0;
            for (int s: array)
                CHECK(s == expected[i++]);
        }

        SECTION("Index loop") {
            for (int i = 0; i < array.length(); i++)
                CHECK(array[i] == expected[i]);
        }

        SECTION("Iterator loop") {
            int i = 0;
            for (auto it = array.begin(); it != array.end(); it++)
                CHECK(*it == expected[i++]);
        }
    }

    SECTION("Constructors") {
        int expected[] = {1, 2, 3};
        Array<int, 3> array = {1, 2, 3};

        SECTION("Copy") {
            Array copy = array;
            CHECK(array.begin() != nullptr);
            CHECK(copy.begin() != array.begin());
            CHECK(array.length() == 3);
            CHECK(copy.length() == 3);
            CHECK(array == expected);
            CHECK(copy == expected);
        }
    }

    SECTION("Subscript") {
        int expected[] = {1, 2, -3};
        Array<int, 3> array = {1, 2, 3};
        array[2] = -3;
        CHECK(array == expected);
    }

    SECTION("Equals") {

        CHECK(Array<int, 3>{1, 2, 3} == Array<int, 3>{1, 2, 3});
        CHECK_FALSE(Array<int, 3>{1, 2, -3} == Array<int, 3>{1, 2, 3});

        CHECK(Array<int, 3>{1, 2, -3} != Array<int, 3>{1, 2, 3});
        CHECK_FALSE(Array<int, 3>{1, 2, 3} != Array<int, 3>{1, 2, 3});

        int other[] = {1, 2, 3};
        CHECK(Array<int, 3>{1, 2, 3} == other);
        CHECK_FALSE(Array<int, 3>{1, 2, -3} == other);
    }
}

#pragma clang diagnostic pop
