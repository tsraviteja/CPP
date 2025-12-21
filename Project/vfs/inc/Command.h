#pragma once
#include <vector>
#include "ICommand.h"
#include "IFileSystem.h"

class Command : public ICommand
{
private:
    IFileSystem &fileSystem;
    std::shared_ptr<IFileSystemComponent> tempCurrentDirectory, previousDirectory;
    std::vector<std::string> command;
    std::string commandArgs;
    bool isValidContent;

    void excecuteMkdirCommand();
    void excecuteLsCommand();
    void excecuteTouchCommand();
    void excecuteCdCommand();
    void excecuteRmCommand();
    void excecuteCommand(std::string shellCommand);
    void excecuteRmflagRCommamd();
    void excecuteRmflagDCommamd();
    void excecutePwdCommand();
    void excecuteEchoCommand();
    void excecuteCatCommand();
    void excecuteFindCommand();

    std::string fetchValidContentInStringFormatFromCommand();
    std::vector<std::string> parseCommandArgs();
    std::string removeWideWhiteSpacesInCommandArgs();
    std::shared_ptr<IFileSystemComponent> fetchParentDirector(std::shared_ptr<IFileSystemComponent> temp);
    void createDirectories(std::shared_ptr<IFileSystemComponent> currentDirectory, int start);
    void createFiles(std::shared_ptr<IFileSystemComponent> currentDirectory, int start);

public:
    Command(IFileSystem &filesystem);
    void parseCommand(std::string args) override;
};
