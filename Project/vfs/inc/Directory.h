#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "IFileSystemComponent.h"

class Directory : public IFileSystemComponent
{
private:
    std::shared_ptr<IFileSystemComponent> parentDirectroy;
    component::componenttype componentType;
    std::string directoryname;

public:
    std::vector<std::shared_ptr<IFileSystemComponent>> childEntries;

    Directory(std::string directoryname, component::componenttype componentType, std::shared_ptr<IFileSystemComponent> parentDirectory);
    void addComponent(std::shared_ptr<IFileSystemComponent> component);
    void displayChildEntries();
    std::shared_ptr<IFileSystemComponent> getPartentDirectory();
    std::shared_ptr<IFileSystemComponent> getChildDirectory(std::string directoryname);
    std::shared_ptr<IFileSystemComponent> getFile(std::string filename);

    std::string getName() override;
    void setName(std::string name) override;
    component::componenttype getComponentType() override;
};
