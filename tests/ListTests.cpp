//
// Created by Paker on 01/09/21.
//

#include "lib/catch.hpp"
#include "TestUtils.h"
#include "PK/List.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "bugprone-use-after-move"
#pragma ide diagnostic ignored "performance-unnecessary-copy-initialization"

TEST_CASE("List") {

    SECTION("Empty") {

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

    SECTION("Loops") {
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

    SECTION("Constructors") {
        int expected[] = {1, 2, 3};
        List list = {1, 2, 3};

        SECTION("Copy") {
            List copy = list;
            CHECK(list.begin());
            CHECK(list.length() == 3);
            CHECK(copy.length() == 3);
            CHECK(list == expected);
            CHECK(copy == expected);
        }

        SECTION("Move") {
            auto begin = list.begin();
            List moved = std::move(list);
            CHECK_FALSE(list.begin());
            CHECK(list.length() == 0);
            CHECK(moved.begin() == begin);
            CHECK(moved.length() == 3);
            CHECK(moved == expected);
        }
    }

    SECTION("Subscript") {
        int expected[] = {1, 2, -3};
        List list = {1, 2, 3};
        list[2] = -3;
        CHECK(list == expected);
    }

    SECTION("Assignment") {
        int expected[] = {1, 2, 3};
        List list = {1, 2, 3};

        SECTION("Copy") {
            List copy = {0};
            copy = list;
            CHECK(list.begin());
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
            CHECK_FALSE(list.begin());
            CHECK(list.length() == 0);
            CHECK(moved.begin() == begin);
            CHECK(moved.length() == 3);
            CHECK(moved == expected);
        }
    }

    SECTION("Remove") {
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
            }

            CHECK(list.length() == 2);
            CHECK(list == expected);
        }

        SECTION("All") {
            list.removeAll();
            CHECK_FALSE(list.begin());
            CHECK(list.length() == 0);
        }
    }

    SECTION("Append") {

        SECTION("Empty") {
            int expected[] = {1};
            List<int> list;

            list.append(1);

            CHECK(list.length() == 1);
            CHECK(list == expected);
        }

        SECTION("Not empty") {
            int expected[] = {1, 2};
            List list = {1};

            list.append(2);

            CHECK(list.length() == 2);
            CHECK(list == expected);
        }
    }

    SECTION("Insert") {

        SECTION("Empty") {
            int expected[] = {1};
            List<int> list;

            list.insert(1, 0);

            CHECK(list.length() == 1);
            CHECK(list == expected);
        }

        SECTION("Begin") {
            List list = {2, 3};
            int expected[] = {1, 2, 3};

            CHECK(list.length() == 2);

            list.insert(1, 0);

            CHECK(list.length() == 3);
            CHECK(list == expected);
        }

        SECTION("Middle") {
            List list = {1, 3};
            int expected[] = {1, 2, 3};

            CHECK(list.length() == 2);

            list.insert(2, 1);

            CHECK(list.length() == 3);
            CHECK(list == expected);
        }

        SECTION("End") {
            List list = {1, 2};
            int expected[] = {1, 2, 3};

            CHECK(list.length() == 2);

            list.insert(3, 2);

            CHECK(list.length() == 3);
            CHECK(list == expected);
        }
    }

    SECTION("Equals") {

        CHECK(List{1, 2, 3} == List{1, 2, 3});
        CHECK_FALSE(List{1, 2, -3} == List{1, 2, 3});

        CHECK(List{1, 2, -3} != List{1, 2, 3});
        CHECK_FALSE(List{1, 2, 3} != List{1, 2, 3});

        int other[] = {1, 2, 3};
        CHECK(List{1, 2, 3} == other);
        CHECK_FALSE(List{1, 2, -3} == other);
    }
}

#pragma clang diagnostic pop
