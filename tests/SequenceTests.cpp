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

TEST_CASE("Sequence - Empty") {
    SECTION("YES") {
        Sequence<int> sequence;
        CHECK(sequence.isEmpty());
        CHECK(sequence.length() == 0);
    }

    SECTION("NO") {
        Sequence sequence = {1};
        CHECK_FALSE(sequence.isEmpty());
        CHECK(sequence.length() == 1);
    }
}

TEST_CASE("Sequence - Contains") {
    Sequence sequence = {1, 2, 3};
    CHECK(sequence.contains(2));
    CHECK_FALSE(sequence.contains(5));
}

TEST_CASE("Sequence - Loops") {
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

TEST_CASE("Sequence - Constructors") {
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

TEST_CASE("Sequence - Subscript") {
    int expected[] = {1, 2, -3};
    Sequence sequence = {1, 2, 3};
    sequence[2] = -3;
    CHECK(sequence == expected);
}

TEST_CASE("Sequence - Assignment") {
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

TEST_CASE("Sequence - Concat") {
    int expected[] = {1, 2, 3, 4, 5};
    Sequence sequence1 = {1, 2, 3};
    Sequence sequence2 = {4, 5};
    CHECK(sequence1 + sequence2 == expected);
}

TEST_CASE("Sequence - Equals") {

    Sequence sequence = {1, 2, 3};
    CHECK(sequence == sequence);
    CHECK_FALSE(sequence != sequence);

    CHECK(Sequence{1, 2, 3} == Sequence{1, 2, 3});
    CHECK_FALSE(Sequence{1, 2, -3} == Sequence{1, 2, 3});

    CHECK(Sequence{1, 2, -3} != Sequence{1, 2, 3});
    CHECK_FALSE(Sequence{1, 2, 3} != Sequence{1, 2, 3});

    int other[] = {1, 2, 3};
    CHECK(Sequence{1, 2, 3} == other);
    CHECK_FALSE(Sequence{1, 2, -3} == other);
}

#pragma clang diagnostic pop
