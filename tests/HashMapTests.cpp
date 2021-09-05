//
// Created by Paker on 04/09/21.
//

#include "catch.hpp"
#include "PK/HashMap.h"
#include "PK/StringUtils.h"

using namespace PK;

TEST_CASE("HashMap") {

    HashMap<String, String> map;

    for (int i = 1; i <= 3; i++)
        map.set("Key " + StringUtils::to_string(i), "Value " + StringUtils::to_string(i));

    SECTION("Key not found") {
        CHECK_THROWS_MATCHES(map["Key 0"], std::range_error, Catch::Message("Key not found"));
    }

    SECTION("Subscript - Get") {
        CHECK(map["Key 1"] == "Value 1");
        CHECK(map["Key 2"] == "Value 2");
        CHECK(map["Key 3"] == "Value 3");
    }

    SECTION("Subscript - Assign") {
        map["Key 2"] = "XYZ";
        CHECK(map["Key 2"] == "XYZ");
    }

    SECTION("Replace") {
        map.set("Key 2", "XYZ");
        CHECK(map["Key 2"] == "XYZ");
        CHECK(map.length() == 3);
    }

    SECTION("Find") {
        CHECK_FALSE(map.find("Key 0"));
        CHECK(map.find("Key 1"));
    }

    SECTION("Length") {
        CHECK(map.length() == 3);
        CHECK(map.entries().length() == 3);
        CHECK(map.keys().length() == 3);
        CHECK(map.values().length() == 3);
    }
}
