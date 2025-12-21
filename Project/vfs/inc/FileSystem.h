#pragma once
#include "IFileSystem.h"
#include <iostream>
#include <memory>
#include <vector>

class FileSystem : public IFileSystem
{
private:
    std::shared_ptr<IFileSystemComponent> currentDirectory;

public:
    FileSystem();
    std::shared_ptr<IFileSystemComponent> getCurrentDirectory() override;
    bool setCurrentDirectory(std::shared_ptr<IFileSystemComponent> newDirectory) override;
    absolutePath getAbsolutePathOfCurrentDirectory() override;
};
