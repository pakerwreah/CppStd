//
// Created by Paker on 01/09/21.
//

#include "catch.hpp"
#include "PK/StringUtils.h"

using namespace PK;

#if false // TODO
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
#endif
