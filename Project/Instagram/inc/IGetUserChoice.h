#pragma once

class IGetUserChoice
{
public:
    virtual int getUserChoice(int userMinChoice, int userMaxChoice) = 0;
};
