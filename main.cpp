#include <iostream>

#include "PK/String.h"
#include "PK/Array.h"
#include "PK/List.h"

using namespace PK;

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"

inline const char* bool_str(bool b) { return b ? "true" : "false"; }

int main() {
    String text = "Hello, World!";
    std::cout << text << " - length: " << text.length() << std::endl;

    std::cout << std::endl;

    for (char c: text)
        std::cout << c << " ";

    std::cout << std::endl << std::endl;

    std::cout << "#----- Array -----#" << std::endl;

    Array<int, 5> array = {1, 2, 3, 4, 5};

    std::cout << "Is empty: " << bool_str(array.is_empty()) << std::endl;

    std::cout << "Range loop: ";

    for (int i: array)
        std::cout << i << " ";

    std::cout << std::endl << "Index loop: ";

    for (int i = 0; i < array.length(); i++)
        std::cout << array[i] << " ";

    std::cout << std::endl << "Iterator loop: ";

    for (auto it = array.begin(); it != array.end(); it++)
        std::cout << *it << " ";

    std::cout << std::endl << std::endl;

    std::cout << "#----- List -----#" << std::endl;

    List<int> list;

    std::cout << "Is empty: " << bool_str(list.is_empty()) << std::endl;

    std::cout << "Appending..." << std::endl;

    for (int i = 1; i <= 5; i++)
        list.append(i);

    std::cout << "Is empty: " << bool_str(list.is_empty()) << std::endl;

    std::cout << "Range loop: ";

    for (int i: list)
        std::cout << i << " ";

    std::cout << std::endl << "Index loop: ";

    for (int i = 0; i < list.length(); i++)
        std::cout << list[i] << " ";

    std::cout << std::endl << "Iterator loop: ";

    for (auto it = list.begin(); it != list.end(); it++)
        std::cout << *it << " ";

    std::cout << std::endl;

    return 0;
}

#pragma clang diagnostic pop
