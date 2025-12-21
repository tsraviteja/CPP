#pragma once
#include "IFileSystem.h"
#include <iostream>

class ICommand
{
public:
    virtual void parseCommand(std::string args) = 0;
    virtual ~ICommand() {}
};
