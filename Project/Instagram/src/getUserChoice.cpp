#include <iostream>
#include "getUserChoice.h"

bool UserChoice::isValidUserChoice(int userChoice, int userMinChoice, int userMaxChoice)
{
    if (userChoice >= userMinChoice && userChoice <= userMaxChoice)
    {
        return true;
    }
    return false;
}

bool UserChoice::isDigit(char character)
{
    if (character >= '0' && character <= '9')
    {
        return true;
    }
    return false;
}

int UserChoice::getNumericCharacter(std::string userInput)
{
    int sum = 0;
    for (int iterate = 0; userInput[iterate] != '\0'; iterate++)
    {
        bool isNumericCharacter = isDigit(userInput[iterate]);
        if (isNumericCharacter)
        {
            sum += sum * 10 + userInput[iterate] - 48;
        }
        else
        {
            return -1;
        }
    }
    return sum;
}

int UserChoice::getUserChoice(int userMinChoice, int userMaxChoice)
{
    std::string userInput;
    int userChoice;
    bool isValidChoice = true;
    do
    {
        std::cout << "\nEnter your choice between " << userMinChoice << " and " << userMaxChoice << " :";
        std::cin >> userInput;

        userChoice = getNumericCharacter(userInput);
        isValidChoice = isValidUserChoice(userChoice, userMinChoice, userMaxChoice);

        if (!isValidChoice)
        {
            std::cout << "\nInvalid choice try again!\n"
                      << std::endl;
        }

    } while (!isValidChoice);

    return userChoice;
}
