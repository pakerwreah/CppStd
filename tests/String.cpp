//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "PK/String.h"

using namespace PK;

#if false // TODO
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
#endif
