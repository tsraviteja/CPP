#pragma once
#include <iostream>
#include <map>

std::map<std::string, int> commandTypes{
    {"cd", 0},
    {"ls", 1},
    {"mkdir", 2},
    {"touch", 3},
    {"rm", 4},
    {"echo", 5},
    {"cat", 6},
    {"find", 7},
    {"pwd", 8}};
