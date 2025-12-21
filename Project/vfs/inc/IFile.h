#pragma once
#include <iostream>
#include "IFileSystemComponent.h"

class IFile : public IFileSystemComponent
{
public:
    virtual std::string getName() = 0;
    virtual void setName(std::string name) = 0;
    virtual std::string getContent() = 0;
    virtual void setContent(std::string content) = 0;
    virtual component::componenttype getComponentType() = 0;
};