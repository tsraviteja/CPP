#include <iostream>
#include <algorithm>
#include "Directory.h"
#include "File.h"
#include "Command.h"
#include "CommandMapper.h"

Command::Command(IFileSystem &filesystem) : fileSystem(filesystem)
{
    tempCurrentDirectory = filesystem.getCurrentDirectory();
}

std::string Command::removeWideWhiteSpacesInCommandArgs()
{
    std::string temp = commandArgs;
    std::string commandArgsRemovedWhiteSpace = "";
    bool isOneSpaceAdded = false;

    for (int index = 0; index < commandArgs.size(); index++)
    {
        int letter = temp[index];
        if (letter == ' ')
        {
            if (!isOneSpaceAdded)
            {
                isOneSpaceAdded == true;
                commandArgsRemovedWhiteSpace += letter;
            }
        }
        else
        {
            isOneSpaceAdded = false;
            commandArgsRemovedWhiteSpace += letter;
        }
    }
    return commandArgsRemovedWhiteSpace;
}

std::vector<std::string> Command::parseCommandArgs()
{
    std::vector<std::string> command;
    std::string word = "";

    for (int index = 0; index < commandArgs.size(); index++)
    {
        if (commandArgs[index] == ' ')
        {
            command.push_back(word);
            word = "";
        }
        else if (commandArgs[index] == '/')
        {
            command.push_back(word);
            word = "";
            command.push_back("/");
        }
        else
        {
            word += commandArgs[index];
        }
    }
    if (!word.empty())
    {
        command.push_back(word);
    }

    return command;
}

std::shared_ptr<IFileSystemComponent> Command::fetchParentDirector(std::shared_ptr<IFileSystemComponent> temp)
{
    auto directory = std::dynamic_pointer_cast<Directory>(temp);
    return directory->getPartentDirectory();
}

void Command::createDirectories(std::shared_ptr<IFileSystemComponent> currentDirectory, int start)
{
    auto temp = std::dynamic_pointer_cast<Directory>(currentDirectory);

    for (int index = start; index < command.size(); index++)
    {
        if (command[index - 1] != "/")
        {
            temp = std::dynamic_pointer_cast<Directory>(previousDirectory);
        }
        auto directory = temp->getChildDirectory(command[index]);
        if (directory == nullptr)
        {
            auto component = std::make_shared<Directory>(command[index], component::componenttype::DIRECTORY, temp);
            temp->addComponent(component);
        }
        else
        {
            std::cout << command[index] << " Directory is alreday exists!" << std::endl;
        }
    }
}

void Command::createFiles(std::shared_ptr<IFileSystemComponent> currentDirectory, int start)
{
    auto temp = std::dynamic_pointer_cast<Directory>(currentDirectory);

    for (int index = start; index < command.size(); index++)
    {
        if (command[index - 1] != "/")
        {
            temp = std::dynamic_pointer_cast<Directory>(previousDirectory);
        }
        auto directory = temp->getFile(command[index]);
        if (directory == nullptr)
        {
            auto component = std::make_shared<File>(command[index], component::componenttype::FILE);
            temp->addComponent(component);
        }
        else
        {
            std::cout << command[index] << " File is alreday exists!" << std::endl;
        }
    }
}

void Command::excecuteMkdirCommand()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());
    previousDirectory = temp;

    if (command.size() < 2)
    {
        std::cout << "In sufficient command!" << std::endl;
    }
    else
    {
        if (command[1] == "/")
        {
            std::cout << "Invalid command!" << std::endl;
        }
        else
        {
            int startIndex = 1;
            for (auto index = command.begin() + 1; index != command.end(); index++)
            {
                if (*index == "..")
                {
                    auto directory = temp->getPartentDirectory();
                    if (directory != nullptr)
                    {
                        temp = std::dynamic_pointer_cast<Directory>(directory);
                    }
                }
                else if (*index == "." && *(index + 1) == "/")
                {
                    // donothing
                }
                else if (*index == "/")
                {
                    // donothing
                }
                else
                {
                    auto directory = temp->getChildDirectory(*index);
                    if (directory == nullptr)
                    {
                        createDirectories(temp, startIndex);
                        break;
                    }
                    temp = std::dynamic_pointer_cast<Directory>(directory);
                }
                startIndex++;
            }
        }
    }
}

void Command::excecuteTouchCommand()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());
    previousDirectory = temp;

    if (command.size() < 2)
    {
        std::cout << "In sufficient command!" << std::endl;
    }
    else
    {
        if (command[1] == "/")
        {
            std::cout << "Invalid command!" << std::endl;
        }
        else
        {
            int startIndex = 1;
            for (auto index = command.begin() + 1; index != command.end(); index++)
            {
                if (*index == "..")
                {
                    auto directory = temp->getPartentDirectory();
                    if (directory != nullptr)
                    {
                        temp = std::dynamic_pointer_cast<Directory>(directory);
                    }
                }
                else if (*index == "." && *(index + 1) == "/")
                {
                    // donothing
                }
                else if (*index == "/")
                {
                    // donothing
                }
                else
                {
                    auto directory = temp->getChildDirectory(*index);
                    auto file = temp->getFile(*index);

                    if (directory == nullptr)
                    {
                        createFiles(temp, startIndex);
                        break;
                    }

                    temp = std::dynamic_pointer_cast<Directory>(directory);
                }
                startIndex++;
            }
        }
    }
}

void Command::excecuteCdCommand()
{
    bool needsToChangeThePath = true;
    if (command.size() == 1)
    {
        fileSystem.setCurrentDirectory(tempCurrentDirectory);
    }
    else if (command[1] == "/")
    {
        std::cout << "No such file or directory" << std::endl;
    }
    else
    {
        auto temp = fileSystem.getCurrentDirectory();
        auto directory = std::dynamic_pointer_cast<Directory>(temp);

        for (auto index = command.begin() + 1; index != command.end(); index++)
        {
            if (*index == "..")
            {
                temp = directory->getPartentDirectory();
                if (temp == nullptr)
                {
                    temp = tempCurrentDirectory;
                }
                directory = std::dynamic_pointer_cast<Directory>(temp);
            }
            else if (*index == "." && *(index) == "/")
            {
                // do nothing
            }
            else
            {
                temp = directory->getChildDirectory(*(index));
                if (temp == nullptr)
                {
                    needsToChangeThePath = false;
                    break;
                }
                directory = std::dynamic_pointer_cast<Directory>(temp);
            }
        }
        if (needsToChangeThePath && directory == nullptr)
        {
            fileSystem.setCurrentDirectory(tempCurrentDirectory);
        }
        else if (needsToChangeThePath)
        {
            fileSystem.setCurrentDirectory(directory);
        }
        else
        {
            std::cout << "Invalid path!" << std::endl;
        }
    }
}

void Command::excecuteRmCommand()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());

    if (command[1] == "-r")
    {
        excecuteRmflagRCommamd();
    }
    else if (command[1] == "-d")
    {
        excecuteRmflagDCommamd();
    }
    else
    {
        if (temp->childEntries.size() != 0)
        {
            for (int index = 1; index < command.size(); index++)
            {
                temp->childEntries.erase(std::remove_if(temp->childEntries.begin(), temp->childEntries.end(), [=](const std::shared_ptr<IFileSystemComponent> ptr)
                                                        { if (ptr->getComponentType() == component::componenttype::FILE && ptr->getName() == command[index])
                                                        {
                                                           return true;
                                                        }
                                                      return false; }),
                                         temp->childEntries.end());
            }
        }
        else
        {
            std::cout << "Directory is empty!" << std::endl;
        }
    }
}

void Command::excecuteRmflagRCommamd()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());

    if (temp->childEntries.size() != 0)
    {
        for (int index = 1; index < command.size(); index++)
        {
            temp->childEntries.erase(std::remove_if(temp->childEntries.begin(), temp->childEntries.end(), [=](const std::shared_ptr<IFileSystemComponent> ptr)
                                                    { 
                                                        auto directory = std::dynamic_pointer_cast<Directory>(ptr);
                                                        if (directory != nullptr && directory->getName() == command[index])
                                                        {
                                                           return true;
                                                        }
                                                      return false; }),
                                     temp->childEntries.end());
        }
    }
    else
    {
        std::cout << "Directory is empty!" << std::endl;
    }
}
void Command::excecuteRmflagDCommamd()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());

    if (temp->childEntries.size() != 0)
    {
        for (int index = 1; index < command.size(); index++)
        {
            temp->childEntries.erase(std::remove_if(temp->childEntries.begin(), temp->childEntries.end(), [=](const std::shared_ptr<IFileSystemComponent> ptr)
                                                    { 
                                                        auto directory = std::dynamic_pointer_cast<Directory>(ptr);
                                                        if (directory != nullptr && directory->getName() == command[index] && directory->childEntries.size() == 0)
                                                        {
                                                           return true;
                                                        }
                                                      return false; }),
                                     temp->childEntries.end());
        }
    }
    else
    {
        std::cout << "Directory is empty!" << std::endl;
    }
}

void Command::excecutePwdCommand()
{
    if (command.size() == 1)
    {
        absolutePath path = fileSystem.getAbsolutePathOfCurrentDirectory();
        if (!path.absoultePathOfCureentDirectory.empty())
        {
            std::cout << path.absoultePathOfCureentDirectory << std::endl;
        }
        else
        {
            std::cout << "/" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid command!" << std::endl;
    }
}

std::string Command::fetchValidContentInStringFormatFromCommand()
{
    std::string fileContent = "", tempFileContent = "";
    std::string content = command[1];

    for (auto index = command.begin() + 1; index != command.end() - 2; index++)
    {
        tempFileContent += *(index) + " ";
    }

    for (int index = 1; index < tempFileContent.length() - 2; index++)
    {
        fileContent += tempFileContent[index];
    }

    int length = tempFileContent.length();

    if (tempFileContent[0] == '"' && tempFileContent[length - 2] == '"')
    {
        isValidContent = true;
    }
    else
    {
        isValidContent = false;
    }
    return fileContent;
}

void Command::excecuteEchoCommand()
{

    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());
    bool isFileFound = false;
    auto pointer = command.end() - 1;
    std::string filename = *(pointer);
    std::string fileContent = fetchValidContentInStringFormatFromCommand();

    if (isValidContent && *(pointer - 1) == ">")
    {
        for (auto entries : temp->childEntries)
        {
            auto temp = std::dynamic_pointer_cast<File>(entries);
            if (temp != nullptr && temp->getComponentType() == component::componenttype::FILE && temp->getName() == filename)
            {
                temp->setContent(fileContent);
                isFileFound = true;
            }
        }
        if (!isFileFound)
        {
            std::cout << "File not found!" << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid command!" << std::endl;
    }
}

void Command::excecuteCatCommand()
{
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());
    bool isFileFound = false;
    std::string filename = command[1];

    for (auto &entries : temp->childEntries)
    {
        auto temp = std::dynamic_pointer_cast<File>(entries);
        if (temp != nullptr && temp->getComponentType() == component::componenttype::FILE && temp->getName() == filename)
        {
            std::string fileContent = temp->getContent();
            if (fileContent.empty())
            {
                std::cout << "file is empty!" << std::endl;
            }
            else
            {
                std::cout << fileContent << std::endl;
            }
            isFileFound = true;
        }
    }
    if (!isFileFound)
    {
        std::cout << "File is not found!" << std::endl;
    }
}

void Command::excecuteFindCommand()
{
    auto pointer = command.end() - 1;
    std::string filename = "", iname = "", filePath = "";

    if (command.size() >= 6)
    {
        filename = *(pointer), filePath = "";
        iname = *(pointer - 1);
    }

    bool isDirectoryFound = true, isFileFound = true;
    auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());

    if (iname == "-name" && filename != "")
    {
        for (auto index = command.begin() + 1; index != command.end() - 2; index++)
        {
            if (*index == "" || *index == "/")
            {
                // donothing
            }
            else if (*index == "." && *(index + 1) == "/")
            {
                index++;
            }

            else if (*(index) == "..")
            {
                auto directory = temp->getPartentDirectory();
                if (directory != nullptr)
                {
                    temp = std::dynamic_pointer_cast<Directory>(directory);
                }
            }
            else
            {
                auto directory = temp->getChildDirectory(*(index));
                if (directory == nullptr)
                {
                    isDirectoryFound = false;
                    break;
                }
                temp = std::dynamic_pointer_cast<Directory>(directory);
                filePath = filePath + ('/' + temp->getName());
            }
        }
        if (isDirectoryFound)
        {
            for (auto file : temp->childEntries)
            {
                auto fileComponent = std::dynamic_pointer_cast<File>(file);

                if (fileComponent != nullptr && fileComponent->getName() == filename)
                {
                    std::cout << filePath << '/' << filename << std::endl;
                }
                else
                {
                    std::cout << filename << " is not a file" << std::endl;
                }
            }
        }
        else
        {
            std::cout << "No directory found!" << std::endl;
        }
    }
    else
    {
        std::cout << "Inavlid command !" << std::endl;
    }
}

void Command::excecuteLsCommand()
{
    if (commandArgs.length() > 2)
    {
        std::cout << "Two many arguments!" << std::endl;
    }
    else
    {
        auto temp = std::dynamic_pointer_cast<Directory>(fileSystem.getCurrentDirectory());

        if (temp->getComponentType() == component::componenttype::DIRECTORY)
        {
            temp->displayChildEntries();
        }
    }
}

void Command::excecuteCommand(std::string shellCommand)
{
    auto commandtype = commandTypes.find(shellCommand);
    int commandValue = -1;

    if (commandtype != commandTypes.end())
    {
        commandValue = commandtype->second;
    }

    commands::command execeute = (commands::command)commandValue;

    switch (execeute)
    {
    case commands::command::LS:
        excecuteLsCommand();
        break;

    case commands::command::CD:
        excecuteCdCommand();
        break;

    case commands::command::MKDIR:
        excecuteMkdirCommand();
        break;

    case commands::command::TOUCH:
        excecuteTouchCommand();
        break;

    case commands::command::RM:
        excecuteRmCommand();
        break;

    case commands::command::ECHO:
        excecuteEchoCommand();
        break;

    case commands::command::CAT:
        excecuteCatCommand();
        break;

    case commands::command::FIND:
        excecuteFindCommand();
        break;

    case commands::command::PWD:
        excecutePwdCommand();
        break;

    default:
        std::cout << "Invalid command entered!" << std::endl;
    }
}

void Command::parseCommand(std::string args)
{
    commandArgs = "";
    command.clear();
    commandArgs = args;
    bool isFirstCommandWasParsed = false;
    std::string shellCommand = "";

    for (int index = 0; !isFirstCommandWasParsed && index < args.length(); index++)
    {
        if (args[index] == ' ')
        {
            isFirstCommandWasParsed = true;
        }
        else
        {
            shellCommand = shellCommand + args[index];
        }
    }

    commandArgs = removeWideWhiteSpacesInCommandArgs();
    command = parseCommandArgs();

    excecuteCommand(shellCommand);
}
