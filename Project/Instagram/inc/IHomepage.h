#pragma once
#include <iostream>
#include "nlohmann/json.hpp"

class IHomepage
{
public:
    virtual bool postAMessage() = 0;
    virtual bool displayMyPost() = 0;
};
