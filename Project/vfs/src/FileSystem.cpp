#include "FileSystem.h"
#include "Directory.h"
#include "File.h"
#include "ComponentUtility.h"

FileSystem::FileSystem()
{
    currentDirectory = std::make_shared<Directory>("root", component::componenttype::DIRECTORY, nullptr);
}

absolutePath FileSystem::getAbsolutePathOfCurrentDirectory()
{
    std::vector<std::string> parentDirectries;
    absolutePath path;
    path.rootDirectory = "";
    path.absoultePathOfCureentDirectory = "";

    auto temp = std::dynamic_pointer_cast<Directory>(getCurrentDirectory());

    while (temp != nullptr)
    {
        parentDirectries.push_back(temp->getName());
        temp = std::dynamic_pointer_cast<Directory>(temp->getPartentDirectory());
    }

    if (parentDirectries.size() != 1)
    {
        auto it = parentDirectries.end() - 1;
        path.rootDirectory = *(it);

        for (it = it - 1; it != parentDirectries.begin() - 1; it--)
        {
            path.absoultePathOfCureentDirectory = path.absoultePathOfCureentDirectory + "/" + *(it);
        }
    }
    else
    {
        path.rootDirectory = parentDirectries[0];
    }
    return path;
}

std::shared_ptr<IFileSystemComponent> FileSystem::getCurrentDirectory()
{
    return currentDirectory;
}

bool FileSystem::setCurrentDirectory(std::shared_ptr<IFileSystemComponent> newDirectory)
{
    bool isCurrentDirectoryIsUpdated = false;
    if (newDirectory != nullptr)
    {
        currentDirectory = newDirectory;
        isCurrentDirectoryIsUpdated = true;
    }

    return isCurrentDirectoryIsUpdated;
}
