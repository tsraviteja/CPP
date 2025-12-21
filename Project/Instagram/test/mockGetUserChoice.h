#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include "getUserChoice.h"

class MockGetUserChoice : public UserChoice
{
public:
    MOCK_METHOD(bool, isValidUserChoice, (int, int));
    MOCK_METHOD(int, getNumericCharacter, (std::string));
    MOCK_METHOD(bool, isDigit, (char));
    MOCK_METHOD(int, getUserChoice, (int, int), (override));
};
