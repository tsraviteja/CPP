#include "File.h"

File::File(std::string filename, component::componenttype componentType)
{
    this->filename = filename;
    this->fileContent = "";
    this->componentType = componentType;
}

std::string File::getName()
{
    return filename;
}

void File::setName(std::string name)
{
    filename = name;
}

std::string File::getContent()
{
    return fileContent;
}

void File::setContent(std::string newContent)
{
    fileContent = newContent;
}

component::componenttype File::getComponentType()
{
    return componentType;
}
