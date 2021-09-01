#include "PK/Array.h"
#include "PK/List.h"
#include "PK/String.h"
#include "PK/StringUtils.h"

#include <iostream>
#include <cassert>

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
#pragma ide diagnostic ignored "bugprone-use-after-move"

inline const char *bool_str(bool b) { return b ? "true" : "false"; }

void testSequence() {
    std::cout << std::endl << "#----- Sequence -----#" << std::endl;

    Sequence sequence = {1, 2, 3, 4, 5};

    std::cout << "Is empty: " << bool_str(sequence.isEmpty()) << std::endl;

    std::cout << "Range loop:";

    for (int i: sequence)
        std::cout << " " << i;

    std::cout << std::endl << "Index loop:";

    sequence[2] = -3;

    for (int i = 0; i < sequence.length(); i++)
        std::cout << " " << sequence[i];

    std::cout << std::endl << "Iterator loop:";

    for (auto it = sequence.begin(); it != sequence.end(); it++)
        std::cout << " " << *it;

    std::cout << std::endl << "Copy:";

    Sequence copy = sequence;
    assert(sequence.begin() != nullptr);
    assert(!sequence.isEmpty());
    assert(!copy.isEmpty());
    for (int i: copy)
        std::cout << " " << i;

    std::cout << std::endl << "Move:";

    Sequence moved = std::move(sequence);
    assert(sequence.begin() == nullptr);
    assert(sequence.isEmpty());
    assert(!moved.isEmpty());
    for (int i: moved)
        std::cout << " " << i;

    std::cout << std::endl << "Move Assignment:";
    moved = std::move(copy);
    assert(copy.begin() == nullptr);
    assert(copy.end() == nullptr);
    assert(copy.isEmpty());
    assert(!moved.isEmpty());
    for (int i: moved)
        std::cout << " " << i;

    std::cout << std::endl << "Copy Assignment:";
    copy = {1, 2, 3};
    for (int i: copy)
        std::cout << " " << i;

    std::cout << std::endl;
}

void testString() {
    std::cout << std::endl << "#----- String -----#" << std::endl;

    String text = "Hello, World!";
    std::cout << text << " - length: " << text.length() << std::endl;

    String text_copy = text;
    std::cout << "Copy: " << text_copy << " - length: " << text_copy.length() << std::endl;

    String text_move = std::move(text_copy);
    assert(!text_copy);
    std::cout << "Move: " << text_move << " - length: " << text_move.length() << std::endl;

    std::cout << "Range loop:";

    for (char c: text)
        std::cout << " " << c;

    std::cout << std::endl << "Join: " << StringUtils::join(text, " ") << std::endl;
}

void testArray() {
    std::cout << std::endl << "#----- Array -----#" << std::endl;

    Array<int, 5> array = {1, 2, 3, 4, 5};

    std::cout << "Is empty: " << bool_str(array.isEmpty()) << std::endl;

    std::cout << "Range loop:";

    for (int i: array)
        std::cout << " " << i;

    std::cout << std::endl << "Index loop:";

    array[2] = -3;

    for (int i = 0; i < array.length(); i++)
        std::cout << " " << array[i];

    std::cout << std::endl << "Iterator loop:";

    for (auto it = array.begin(); it != array.end(); it++)
        std::cout << " " << *it;

    std::cout << std::endl;
}

void testList() {
    std::cout << std::endl << "#----- List -----#" << std::endl;

    List<int> list;

    std::cout << "Is empty: " << bool_str(list.isEmpty()) << std::endl;

    std::cout << "Appending..." << std::endl;

    for (int i = 1; i <= 5; i++)
        list.append(i);

    std::cout << "Is empty: " << bool_str(list.isEmpty()) << std::endl;

    std::cout << "Range loop:";

    for (int i: list)
        std::cout << " " << i;

    std::cout << std::endl << "Index loop:";

    list[2] = -3;

    for (int i = 0; i < list.length(); i++)
        std::cout << " " << list[i];

    std::cout << std::endl << "Iterator loop:";

    for (auto it = list.begin(); it != list.end(); it++)
        std::cout << " " << *it;

    std::cout << std::endl << "Copy:";

    List copy = list;
    assert(list.begin() != nullptr);
    assert(!list.isEmpty());
    assert(!copy.isEmpty());
    for (int i: copy)
        std::cout << " " << i;

    std::cout << std::endl << "Move:";

    List moved = std::move(list);
    assert(list.begin() == nullptr);
    assert(list.isEmpty());
    assert(!moved.isEmpty());
    for (int i: moved)
        std::cout << " " << i;

    std::cout << std::endl << "Move Assignment:";
    moved = std::move(copy);
    assert(copy.begin() == nullptr);
    assert(copy.end() == nullptr);
    assert(copy.isEmpty());
    assert(!moved.isEmpty());
    for (int i: moved)
        std::cout << " " << i;

    std::cout << std::endl << "Copy Assignment:";
    copy = {1, 2, 3};
    for (int i: copy)
        std::cout << " " << i;

    std::cout << std::endl << "Remove at begin:";
    copy.removeAt(0);
    assert(copy.length() == 2);
    for (int i: copy)
        std::cout << " " << i;

    copy = {1, 2, 3};
    std::cout << std::endl << "Remove at 1:";
    copy.removeAt(1);
    assert(copy.length() == 2);
    for (int i: copy)
        std::cout << " " << i;

    copy = {1, 2, 3};
    std::cout << std::endl << "Remove at end:";
    copy.removeAt(2);
    assert(copy.length() == 2);
    for (int i: copy)
        std::cout << " " << i;

    std::cout << std::endl << "Remove all";

    copy.removeAll();
    assert(copy.begin() == nullptr);
    assert(copy.end() == nullptr);
    assert(copy.isEmpty());
    assert(!moved.isEmpty());

    std::cout << std::endl;
}

void testStringUtils() {
    std::cout << std::endl << "#----- StringUtils -----#" << std::endl;

    std::cout << "Split:";

    auto split = StringUtils::split("a.bcd..e.", ".");
    for (auto s: split)
        std::cout << " " << s;

    std::cout << std::endl;

    Array<String, 3> array_parts = {"a", "b", "c"};
    Array<int, 3> array_parts_int = {1, 2, 3};
    std::cout << "Array join (String): " << StringUtils::join(array_parts, ",") << std::endl;
    std::cout << "Array join (int): " << StringUtils::join(array_parts_int, ",") << std::endl;

    List<String> list_parts = {"a", "b", "c"};
    List list_parts_int = {1, 2, 3};
    std::cout << "List join (String): " << StringUtils::join(list_parts, ",") << std::endl;
    std::cout << "List join (int): " << StringUtils::join(list_parts_int, ",") << std::endl;
}

int main() {

    testSequence();

    testString();

    testArray();

    testList();

    testStringUtils();

    return 0;
}

#pragma clang diagnostic pop
