//
// Created by Paker on 13/02/22.
//

#include "catch.hpp"
#include "PK/TreeMap.h"
#include "PK/StringUtils.h"

using namespace PK;

TEST_CASE("Tree") {

    TreeMap<String, String> tree;

    for (int i = 1; i <= 3; i++)
        tree.insert("Key " + StringUtils::to_string(i), "Value " + StringUtils::to_string(i));

    SECTION("Key not found") {
        CHECK_THROWS_MATCHES(tree["Key 0"], std::range_error, Catch::Message("Key not found"));
    }

    SECTION("Subscript - Get") {
        CHECK(tree["Key 1"] == "Value 1");
        CHECK(tree["Key 2"] == "Value 2");
        CHECK(tree["Key 3"] == "Value 3");
    }

    SECTION("Subscript - Assign") {
        tree["Key 2"] = "XYZ";
        CHECK(tree["Key 2"] == "XYZ");
    }

    SECTION("Replace") {
        tree.insert("Key 2", "XYZ");
        CHECK(tree["Key 2"] == "XYZ");
        CHECK(tree.length() == 3);
    }

    SECTION("Find") {
        CHECK_FALSE(tree.find("Key 0"));
        CHECK(tree.find("Key 1"));
    }

    SECTION("Length") {
        CHECK(tree.length() == 3);
        CHECK(tree.entries().length() == 3);
        CHECK(tree.keys().length() == 3);
        CHECK(tree.values().length() == 3);
    }

    SECTION("Keys") {
        CHECK(tree.keys() == List<String>{"Key 1", "Key 2", "Key 3"});
    }

    SECTION("Values") {
        CHECK(tree.values() == List<String>{"Value 1", "Value 2", "Value 3"});
    }

    SECTION("Entries") {
        CHECK(tree.entries() == List<Map<String, String>::Entry>{
                {"Key 1", "Value 1"},
                {"Key 2", "Value 2"},
                {"Key 3", "Value 3"}
        });
    }
}
