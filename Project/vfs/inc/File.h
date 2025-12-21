#pragma once
#include <iostream>
#include "IFile.h"

class File : public IFile
{
private:
    std::string fileContent, filename;
    component::componenttype componentType;

public:
    File(std::string filename, component::componenttype componentType);
    std::string getName() override;
    void setName(std::string name) override;
    std::string getContent() override;
    void setContent(std::string content) override;
    component::componenttype getComponentType() override;
};
