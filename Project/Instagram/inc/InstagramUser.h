#pragma once
#include <iostream>
#include "IInstagramUser.h"

class InstagramUser : public IInstagramUser
{
private:
    std::string username, password, confirmpassword, secretQuestion, secretAnswer;
    void displaySecretQuestions();

public:
    InstagramUser();
    std::string getUserName() override;
    std::string getUserPassword() override;
    std::string getSecretQuestion() override;
    std::string getSecretAnswer() override;

    void takeInputForUserName() override;
    void takeInputForPassword(std::string userPrompt) override;
    void takeInputForSecretQuestion() override;
    void takeInputForSecretAnswer() override;
    void setSecretQuestion(std::string secretquestion) override;
    void takeConfirmpassword() override;
};