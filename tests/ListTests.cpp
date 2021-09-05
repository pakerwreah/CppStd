//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "TestUtils.h"
#include "PK/List.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "bugprone-use-after-move"
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

TEST_CASE("List - Empty") {

    SECTION("YES") {
        List<int> list;
        CHECK(list.empty());
        CHECK(list.length() == 0);
    }

    SECTION("NO") {
        List list = {1};
        CHECK_FALSE(list.empty());
        CHECK(list.length() == 1);
    }
}

TEST_CASE("List - Loops") {
    int expected[] = {1, 2, 3, 4, 5};
    List list = {1, 2, 3, 4, 5};

    SECTION("Range loop") {
        int i = 0;
        for (int s: list)
            CHECK(s == expected[i++]);
    }

    SECTION("Index loop") {
        for (int i = 0; i < list.length(); i++)
            CHECK(list[i] == expected[i]);
    }

    SECTION("Iterator loop") {
        int i = 0;
        for (auto it = list.begin(); it != list.end(); it++)
            CHECK(*it == expected[i++]);
    }
}

TEST_CASE("List - Constructors") {
    int expected[] = {1, 2, 3};
    List list = {1, 2, 3};

    SECTION("Copy") {
        List copy = list;
        CHECK(list.begin() != nullptr);
        CHECK(list.length() == 3);
        CHECK(copy.length() == 3);
        CHECK(list == expected);
        CHECK(copy == expected);
    }

    SECTION("Move") {
        auto begin = list.begin();
        List moved = std::move(list);
        CHECK(list.begin() == nullptr);
        CHECK(list.length() == 0);
        CHECK(moved.begin() == begin);
        CHECK(moved.length() == 3);
        CHECK(moved == expected);
    }
}

TEST_CASE("List - Subscript") {
    int expected[] = {1, 2, -3};
    List list = {1, 2, 3};
    list[2] = -3;
    CHECK(list == expected);
}

TEST_CASE("List - Assignment") {
    int expected[] = {1, 2, 3};
    List list = {1, 2, 3};

    SECTION("Copy") {
        List copy = {0};
        copy = list;
        CHECK(list.begin() != nullptr);
        CHECK(copy.begin() != list.begin());
        CHECK(list.length() == 3);
        CHECK(copy.length() == 3);
        CHECK(list == expected);
        CHECK(copy == expected);
    }

    SECTION("Move") {
        auto begin = list.begin();
        List moved = {0};
        moved = std::move(list);
        CHECK(list.begin() == nullptr);
        CHECK(list.length() == 0);
        CHECK(moved.begin() == begin);
        CHECK(moved.length() == 3);
        CHECK(moved == expected);
    }
}

TEST_CASE("List - Remove") {
    List list = {1, 2, 3};

    SECTION("Begin") {
        int expected[] = {2, 3};

        SECTION("Index") {
            list.removeAt(0);
        }

        SECTION("Iterator") {
            auto it = list.begin();
            list.remove(it);
            CHECK(it);
            CHECK(it != nullptr);
        }

        CHECK(list.length() == 2);
        CHECK(list == expected);
    }

    SECTION("Middle") {
        int expected[] = {1, 3};

        SECTION("Index") {
            list.removeAt(1);
        }

        SECTION("Iterator") {
            auto it = list.begin() + 1;
            list.remove(it);
            CHECK(it);
            CHECK(it != nullptr);
        }

        CHECK(list.length() == 2);
        CHECK(list == expected);
    }

    SECTION("End") {
        int expected[] = {1, 2};

        SECTION("Index") {
            list.removeAt(2);
        }

        SECTION("Iterator") {
            auto it = list.begin() + 2;
            list.remove(it);
            CHECK_FALSE(it);
            CHECK(it == nullptr);
        }

        CHECK(list.length() == 2);
        CHECK(list == expected);
    }

    SECTION("All") {
        list.removeAll();
        CHECK(list.begin() == nullptr);
        CHECK(list.length() == 0);
    }
}

TEST_CASE("List - Equals") {

    CHECK(List{1, 2, 3} == List{1, 2, 3});
    CHECK_FALSE(List{1, 2, -3} == List{1, 2, 3});

    CHECK(List{1, 2, -3} != List{1, 2, 3});
    CHECK_FALSE(List{1, 2, 3} != List{1, 2, 3});

    int other[] = {1, 2, 3};
    CHECK(List{1, 2, 3} == other);
    CHECK_FALSE(List{1, 2, -3} == other);
}

#pragma clang diagnostic pop
