#pragma once
#include <iostream>
#include "ComponentUtility.h"

class IFileSystemComponent
{
public:
    virtual std::string getName() = 0;
    virtual void setName(std::string name) = 0;
    virtual component::componenttype getComponentType() = 0;
    virtual ~IFileSystemComponent() {};
};
