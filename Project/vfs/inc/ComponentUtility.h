#pragma once
#include <iostream>
#include <map>

namespace component
{
    enum componenttype
    {
        DIRECTORY = 0,
        FILE = 1
    };
};

namespace commands
{
    enum command
    {
        CD,
        LS,
        MKDIR,
        TOUCH,
        RM,
        ECHO,
        CAT,
        FIND,
        PWD
    };
};

namespace color
{
    const std::string RESET = "\033[0m";
    const std::string GREEN = "\033[92m";
    const std::string BLUE = "\033[34m";
};
