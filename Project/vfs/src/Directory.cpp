#include "Directory.h"
#include "File.h"

Directory::Directory(std::string directoryname, component::componenttype componentType, std::shared_ptr<IFileSystemComponent> parentDirectory)
{
    this->directoryname = directoryname;
    this->componentType = componentType;
    this->parentDirectroy = parentDirectory;
}

std::string Directory::getName()
{
    return directoryname;
}

void Directory::setName(std::string name)
{
    directoryname = name;
}

component::componenttype Directory::getComponentType()
{
    return componentType;
}

void Directory::addComponent(std::shared_ptr<IFileSystemComponent> component)
{
    this->childEntries.push_back(component);
    // std::cout << childEntries.size() << std::endl;
}

std::shared_ptr<IFileSystemComponent> Directory::getPartentDirectory()
{
    return parentDirectroy;
}

void Directory::displayChildEntries()
{
    bool isAnychildEntriesFound = false;
    for (auto temp : childEntries)
    {
        isAnychildEntriesFound = true;

        auto directorycomponent = std::dynamic_pointer_cast<Directory>(temp);
        if (directorycomponent == nullptr)
        {
            auto filecomponent = std::dynamic_pointer_cast<File>(temp);
            std::cout << color::GREEN << filecomponent->getName() << " " << color::RESET;
        }
        else
        {
            std::cout << color::BLUE << directorycomponent->getName() << " " << color::RESET;
        }
    }
    if (isAnychildEntriesFound)
    {
        std::cout << "\n";
    }
}

std::shared_ptr<IFileSystemComponent> Directory::getFile(std::string filename)
{
    std::shared_ptr<IFileSystemComponent> findingDirectory = nullptr;

    for (auto file : childEntries)
    {
        if (file->getComponentType() == component::componenttype::FILE && file->getName() == filename)
        {
            findingDirectory = file;
            break;
        }
    }
    return findingDirectory;
}

std::shared_ptr<IFileSystemComponent> Directory::getChildDirectory(std::string directoryname)
{
    std::shared_ptr<IFileSystemComponent> findingDirectory = nullptr;

    for (auto childDirectory : childEntries)
    {
        if (childDirectory->getComponentType() == component::componenttype::DIRECTORY && childDirectory->getName() == directoryname)
        {
            findingDirectory = childDirectory;
            break;
        }
    }
    return findingDirectory;
}
