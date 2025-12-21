#pragma once
#include "IFileSystemComponent.h"
#include <iostream>
#include <memory>

typedef struct
{
    std::string rootDirectory, absoultePathOfCureentDirectory;
} absolutePath;

class IFileSystem
{
public:
    virtual std::shared_ptr<IFileSystemComponent> getCurrentDirectory() = 0;
    virtual bool setCurrentDirectory(std::shared_ptr<IFileSystemComponent> newDirectory) = 0;
    virtual absolutePath getAbsolutePathOfCurrentDirectory() = 0;
    virtual ~IFileSystem() {}
};
