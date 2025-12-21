#include "InstagramUser.h"
#include "getUserChoice.h"
#include "Secretquestions.h"

InstagramUser::InstagramUser()
{
    username = "";
    password = "";
    secretQuestion = "";
    secretAnswer = "";
    confirmpassword = "";
}

std::string InstagramUser::getUserName()
{
    return username;
}

std::string InstagramUser::getUserPassword()
{
    return password;
}

std::string InstagramUser::getSecretQuestion()
{
    return secretQuestion;
}

std::string InstagramUser::getSecretAnswer()
{
    return secretAnswer;
}

void InstagramUser::takeInputForUserName()
{
    std::cout << "\nEnter username :";
    std::cin >> username;
}

void InstagramUser::takeInputForPassword(std::string userPrompt)
{
    std::cout <<userPrompt;
    std::cin >> password;
}

void InstagramUser::takeInputForSecretQuestion()
{
    UserChoice userChoice;
    std::cout << "\nPlease select one question to answer\n";

    displaySecretQuestions();
    const int choice = userChoice.getUserChoice(1, 5);

    secretQuestion = Secretquestions.at(choice);
}

void InstagramUser::displaySecretQuestions()
{
    for (auto mapIndex : Secretquestions)
    {
        std::cout << mapIndex.first << ")" << mapIndex.second << std::endl;
    }
}

void InstagramUser::takeInputForSecretAnswer()
{
    if (secretQuestion != "")
    {
        std::cout <<"\n" << secretQuestion << "\nAnswer :";
        std::cin >> secretAnswer;
    }
}

void InstagramUser::setSecretQuestion(std::string secretquestion)
{
    secretQuestion = secretquestion;
}

void InstagramUser::takeConfirmpassword()
{
    std::cout << "Enter confirmapssword :";
    std::cin >> confirmpassword;

    if (confirmpassword == password)
    {
        return;
    }
    std::cout<<"password mismatching!"<<std::endl;
    takeInputForPassword(std::string("\nEnter new password :"));
    takeConfirmpassword();
}
