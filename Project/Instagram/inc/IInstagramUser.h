#pragma once
#include <iostream>

class IInstagramUser
{
public:
    virtual std::string getUserName() = 0;
    virtual std::string getUserPassword() = 0;
    virtual std::string getSecretQuestion() = 0;
    virtual std::string getSecretAnswer() = 0;

    virtual void takeInputForUserName() = 0;
    virtual void takeInputForPassword(std::string userPrompt) = 0;
    virtual void takeInputForSecretQuestion() = 0;
    virtual void takeInputForSecretAnswer() = 0;
    virtual void setSecretQuestion(std::string secretquestion) = 0;
    virtual void takeConfirmpassword() = 0;
};