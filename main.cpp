#include "PK/Array.h"
#include "PK/List.h"
#include "PK/String.h"
#include "PK/StringUtils.h"

#include <iostream>
#include <cassert>

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"

inline const char *bool_str(bool b) { return b ? "true" : "false"; }

void testString() {
    String text = "Hello, World!";
    std::cout << text << " - length: " << text.length() << std::endl;

    String text_copy = text;
    std::cout << "Copy: " << text_copy << " - length: " << text_copy.length() << std::endl;

    String text_move = std::move(text_copy);
    assert(!text_copy); // NOLINT(bugprone-use-after-move)
    std::cout << "Move: " << text_move << " - length: " << text_move.length() << std::endl;

    std::cout << std::endl << "Range loop:";

    for (char c: text)
        std::cout << " " << c;

    std::cout << std::endl << std::endl;
}

void testArray() {
    std::cout << "#----- Array -----#" << std::endl;

    Array<int, 5> array = {1, 2, 3, 4, 5};

    std::cout << "Is empty: " << bool_str(array.is_empty()) << std::endl;

    std::cout << "Range loop:";

    for (int i: array)
        std::cout << " " << i;

    std::cout << std::endl << "Index loop:";

    for (int i = 0; i < array.length(); i++)
        std::cout << " " << array[i];

    std::cout << std::endl << "Iterator loop:";

    for (auto it = array.begin(); it != array.end(); it++)
        std::cout << " " << *it;

    std::cout << std::endl << std::endl;
}

void testList() {
    std::cout << "#----- List -----#" << std::endl;

    List<int> list;

    std::cout << "Is empty: " << bool_str(list.is_empty()) << std::endl;

    std::cout << "Appending..." << std::endl;

    for (int i = 1; i <= 5; i++)
        list.append(i);

    std::cout << "Is empty: " << bool_str(list.is_empty()) << std::endl;

    std::cout << "Range loop:";

    for (int i: list)
        std::cout << " " << i;

    std::cout << std::endl << "Index loop:";

    for (int i = 0; i < list.length(); i++)
        std::cout << " " << list[i];

    std::cout << std::endl << "Iterator loop:";

    for (auto it = list.begin(); it != list.end(); it++)
        std::cout << " " << *it;

    std::cout << std::endl << std::endl;
}

void testStringUtils() {
    std::cout << "#----- StringUtils -----#" << std::endl;

    std::cout << std::endl << "Split:";

    auto split = StringUtils::split("a.bcd..e.", ".");
    for (auto s: split)
        std::cout << " " << s;

    std::cout << std::endl;

    Array<String, 3> array_parts = {"a", "b", "c"};
    std::cout << "Array join: " << StringUtils::join(array_parts, ",") << std::endl;

    List<String> list_parts = {"a", "b", "c"};
    std::cout << "List join: " << StringUtils::join(list_parts, ",") << std::endl;

    std::cout << std::endl;
}

int main() {

    testString();

    testArray();

    testList();

    testStringUtils();

    return 0;
}

#pragma clang diagnostic pop
