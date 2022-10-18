//
// Created by Paker on 05/09/21.
//

#include "catch.hpp"
#include "PK/Optional.h"

using namespace PK;

TEST_CASE("Optional") {

    SECTION("Boolean") {

        Optional<int> opt(0);
        CHECK(opt);
        opt = nullptr;
        CHECK_FALSE(opt);
    }

    SECTION("Cold assignment") {

        Optional<int> opt(nullptr);
        CHECK_FALSE(opt);
        CHECK_THROWS_MATCHES(*opt, std::runtime_error, Catch::Message("Cannot dereference nullptr"));

        opt = 1;
        CHECK(*opt == 1);
    }

    SECTION("Memory isolation") {

        int tmp = 1;
        Optional<int> opt(&tmp);
        CHECK(*opt == 1);

        opt = 0;
        CHECK(*opt == 0);
        CHECK(tmp == 1);

        tmp = 2;
        CHECK(*opt == 0);
    }

    SECTION("Object") {

        struct Test {
            int value;
        };

        Test test1 = {1};
        Optional<Test> opt(&test1);
        CHECK(opt->value == 1);

        Test test2 = {2};
        opt = test2;
        CHECK(opt->value == 2);
        CHECK(test1.value == 1);

        opt = nullptr;
        CHECK_FALSE(opt);
        opt = test2;
        CHECK(opt->value == 2);
    }

    SECTION("Equals") {

        Optional<int> opt1(1), opt2(1);
        CHECK(opt1 == opt2);

        opt2 = 2;
        CHECK(opt1 != opt2);

        opt1 = nullptr;
        CHECK(opt1 != opt2);

        opt2 = nullptr;
        CHECK(opt1 == opt2);
    }
}
