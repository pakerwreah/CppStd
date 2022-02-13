//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "TestUtils.h"
#include "PK/Sequence.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "bugprone-use-after-move"
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

TEST_CASE("Sequence") {

    SECTION("Empty") {

        SECTION("YES") {
            Sequence<int> sequence;
            CHECK(sequence.empty());
            CHECK(sequence.length() == 0);
        }

        SECTION("NO") {
            Sequence sequence = {1};
            CHECK_FALSE(sequence.empty());
            CHECK(sequence.length() == 1);
        }
    }

    SECTION("Contains") {
        Sequence sequence = {1, 2, 3};
        CHECK(sequence.contains(2));
        CHECK_FALSE(sequence.contains(5));
    }

    SECTION("Loops") {
        int expected[] = {1, 2, 3, 4, 5};
        Sequence sequence = {1, 2, 3, 4, 5};

        SECTION("Range loop") {
            int i = 0;
            for (int s: sequence)
                CHECK(s == expected[i++]);
        }

        SECTION("Index loop") {
            for (int i = 0; i < sequence.length(); i++)
                CHECK(sequence[i] == expected[i]);
        }

        SECTION("Iterator loop") {
            int i = 0;
            for (auto it = sequence.begin(); it != sequence.end(); it++)
                CHECK(*it == expected[i++]);
        }
    }

    SECTION("Constructors") {
        int expected[] = {1, 2, 3};
        Sequence sequence = {1, 2, 3};

        SECTION("Copy") {
            Sequence copy = sequence;
            CHECK(sequence.begin() != nullptr);
            CHECK(sequence.length() == 3);
            CHECK(copy.length() == 3);
            CHECK(sequence == expected);
            CHECK(copy == expected);
        }

        SECTION("Move") {
            auto begin = sequence.begin();
            Sequence moved = std::move(sequence);
            CHECK(sequence.begin() == nullptr);
            CHECK(sequence.length() == 0);
            CHECK(moved.begin() == begin);
            CHECK(moved.length() == 3);
            CHECK(moved == expected);
        }
    }

    SECTION("Subscript") {
        int expected[] = {1, 2, -3};
        Sequence sequence = {1, 2, 3};
        sequence[2] = -3;
        CHECK(sequence == expected);
    }

    SECTION("Assignment") {
        int expected[] = {1, 2, 3};
        Sequence sequence = {1, 2, 3};

        SECTION("Copy") {
            Sequence copy = {0};
            copy = sequence;
            CHECK(sequence.begin() != nullptr);
            CHECK(copy.begin() != sequence.begin());
            CHECK(sequence.length() == 3);
            CHECK(copy.length() == 3);
            CHECK(sequence == expected);
            CHECK(copy == expected);
        }

        SECTION("Move") {
            auto begin = sequence.begin();
            Sequence moved = {0};
            moved = std::move(sequence);
            CHECK(sequence.begin() == nullptr);
            CHECK(sequence.length() == 0);
            CHECK(moved.begin() == begin);
            CHECK(moved.length() == 3);
            CHECK(moved == expected);
        }
    }

    SECTION("Concat") {
        int expected[] = {1, 2, 3, 4, 5};
        Sequence sequence1 = {1, 2, 3};
        Sequence sequence2 = {4, 5};
        CHECK(sequence1 + sequence2 == expected);
    }

    SECTION("Compare") {

        Sequence sequence = {1, 2, 3};

        SECTION("Equals") {
            CHECK(sequence == sequence);
            CHECK_FALSE(sequence != sequence);

            CHECK(Sequence{1, 2, 3} == sequence);
            CHECK_FALSE(Sequence{1, 2, -3} == sequence);

            CHECK(Sequence{1, 2, -3} != sequence);
            CHECK_FALSE(Sequence{1, 2, 3} != sequence);
        }

        SECTION("Less") {
            CHECK(Sequence{1, 2} < sequence);
            CHECK(Sequence{1, 2, 2} < sequence);
            CHECK_FALSE(Sequence{1, 2, 3} < sequence);
            CHECK_FALSE(Sequence{1, 2, 4} < sequence);
            CHECK_FALSE(Sequence{1, 2, 3, 4} < sequence);
        }
    }

    SECTION("Sort") {

        int expected[] = {1, 2, 3, 4, 5};
        Sequence sequence = {4, 3, 5, 1, 2};

        CHECK(sequence.sorted() == expected);
    }
}

#pragma clang diagnostic pop
