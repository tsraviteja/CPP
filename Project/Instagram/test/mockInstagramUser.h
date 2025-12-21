#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include "InstagramUser.h"

class MockInstagramUser : public InstagramUser
{
public:
    MOCK_METHOD(std::string, getUserName, (), (override));
    MOCK_METHOD(std::string, getUserPassword, (), (override));
    MOCK_METHOD(std::string, getSecretQuestion, (), (override));
    MOCK_METHOD(std::string, getSecretAnswer, (), (override));

    MOCK_METHOD(void, takeInputForUserName, (), (override));
    MOCK_METHOD(void, takeInputForPassword, (std::string), (override));
    MOCK_METHOD(void, takeInputForSecretQuestion, (), (override));
    MOCK_METHOD(void, takeInputForSecretAnswer, (), (override));
    MOCK_METHOD(void, setSecretQuestion, (std::string), (override));
    MOCK_METHOD(void, takeConfirmpassword, (), (override));
};
