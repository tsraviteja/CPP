#include <iostream>
#include "FileSystem.h"
#include "Command.h"
#include "ComponentUtility.h"

int main()
{
    FileSystem fileSystem;
    Command command(fileSystem);

    while (true)
    {
        std::string userCommand = "";
        absolutePath path = fileSystem.getAbsolutePathOfCurrentDirectory();

        std::cout << color::GREEN << path.rootDirectory << color::RESET << ":" << color::BLUE << "~" << path.absoultePathOfCureentDirectory << color::RESET << "$ ";
        std::getline(std::cin, userCommand);

        if (userCommand == "Quit")
        {
            break;
        }
        else
        {
            command.parseCommand(userCommand);
        }
    }
    return 0;
}
