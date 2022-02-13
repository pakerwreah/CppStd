//
// Created by Paker on 05/09/21.
//

#include "catch.hpp"
#include "PK/Optional.h"

using namespace PK;

TEST_CASE("Optional") {

    SECTION("Int") {

        Optional<int> opt(nullptr);

        CHECK_THROWS_MATCHES(opt = 1, std::runtime_error, Catch::Message("Cannot assign to nullptr"));
        CHECK_THROWS_MATCHES(*opt, std::runtime_error, Catch::Message("Cannot dereference nullptr"));

        int tmp = 1;
        CHECK_NOTHROW(opt = Optional(&tmp));
        CHECK(opt == 1);
        CHECK(*opt == 1);

        CHECK_NOTHROW(opt = 0);
        CHECK(opt == 0);
        CHECK(*opt == 0);

        CHECK(opt);
        opt.clear();
        CHECK_FALSE(opt);
    }

    SECTION("Object") {

        struct Test {
            int value;
        };

        Test obj = {1};

        Optional<Test> optional(&obj);

        CHECK(optional->value == 1);
    }
}
