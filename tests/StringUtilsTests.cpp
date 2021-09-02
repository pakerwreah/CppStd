//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "PK/StringUtils.h"
#include "PK/Array.h"
#include "PK/List.h"

using namespace PK;

TEST_CASE("StringUtils - Split") {
    const String expected[] = {"a", "bcd", "e"};
    auto split = StringUtils::split("a.bcd..e.", ".");
    CHECK(split == expected);
}

TEST_CASE("StringUtils - Join") {

    SECTION("String") {
        String join;

        SECTION("Sequence") {
            Sequence<String> parts = {"a", "b", "c"};
            join = StringUtils::join(parts, ",");
        }

        SECTION("Array") {
            Array<String, 3> parts = {"a", "b", "c"};
            join = StringUtils::join(parts, ",");
        }

        SECTION("List") {
            List<String> parts = {"a", "b", "c"};
            join = StringUtils::join(parts, ",");
        }

        CHECK(join == "a,b,c");
    }

    SECTION("Integer") {
        String join;

        SECTION("Sequence") {
            Sequence parts = {1, 2, 3};
            join = StringUtils::join(parts, ",");
        }

        SECTION("Array") {
            Array<int, 3> parts = {1, 2, 3};
            join = StringUtils::join(parts, ",");
        }

        SECTION("List") {
            List parts = {1, 2, 3};
            join = StringUtils::join(parts, ",");
        }

        CHECK(join == "1,2,3");
    }
}
