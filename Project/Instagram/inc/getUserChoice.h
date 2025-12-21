#pragma once
#include <iostream>
#include "IGetUserChoice.h"

class UserChoice : public IGetUserChoice
{

public:
    int getUserChoice(int userMinChoice, int userMaxChoice) override;

private:
    bool isValidUserChoice(int userChoice, int userMinChoice, int userMaxChoice);
    int getNumericCharacter(std::string userInput);
    bool isDigit(char character);
};
