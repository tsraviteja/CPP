#include "InstagramUser.h"
#include "nlohmann/json.hpp"
#include "Instagram.h"
#include "InstagramJsonFileHandling.h"
#include "Homepage.h"
#include "Feedpage.h"
#include "userChoice.h"

Instagram::Instagram(InstagramJsonFileHandling *instagramFileHandling, UserChoice *userChoosenChoice, InstagramUser *user)
{
    instagramUserdataFile = "../InstagramDataStorage/InstagramUserData.json";
    this->instagramFileHandling = instagramFileHandling;
    this->userChoosenChoice = userChoosenChoice;
    this->user = user;
}

nlohmann::ordered_json Instagram::getUserDataInJsonFormat()
{
    nlohmann::ordered_json userData = {
        {"username", user->getUserName()},
        {"password", user->getUserPassword()},
        {"secretquestion", user->getSecretQuestion()},
        {"secretanswer", user->getSecretAnswer()}};

    return userData;
}

bool Instagram::updateUserPassword()
{
    bool updatedPasswordStatus = false;

    for (auto &userData : instagramJsonData["Instagramusers"])
    {
        if (userData["username"] == user->getUserName())
        {
            userData["password"] = user->getUserPassword();
            updatedPasswordStatus = instagramFileHandling->writeInstagramJsonFileData(instagramUserdataFile, instagramJsonData);
        }
    }
    return updatedPasswordStatus;
}

std::string Instagram::getSecretquestion(std::string username)
{
    std::string secretequestion;
    for (auto user : instagramJsonData["Instagramusers"])
    {
        if (user["username"] == username)
        {
            secretequestion = user["secretquestion"];
            break;
        }
    }
    return secretequestion;
}

bool Instagram::verifyWithUserSecretAnswer(std::string username, std::string userAnswer)
{
    bool isCorrectUseranswer = false;
    for (auto user : instagramJsonData["Instagramusers"])
    {
        if (user["username"] == username && user["secretanswer"] == userAnswer)
        {
            isCorrectUseranswer = true;
            break;
        }
    }
    return isCorrectUseranswer;
}

bool Instagram::signin()
{
    user->takeInputForUserName();
    user->takeInputForPassword(std::string("Enter password :"));

    std::string username = user->getUserName();
    std::string password = user->getUserPassword();
    bool isValidUser = verifyTheUserDetails(username, password);

    if (isValidUser)
    {
        gotoHomePage(username);
    }

    return isValidUser;
}

bool Instagram::forgotpassword()
{
    user->takeInputForUserName();

    std::string username = user->getUserName();
    bool isValidUsername = verifyTheUserDetails(username);
    bool forgotPasswordStatus = false;

    if (isValidUsername)
    {
        std::string secretquestion = getSecretquestion(username);
        user->setSecretQuestion(secretquestion);
        user->takeInputForSecretAnswer();
        std::string secretanswer = user->getSecretAnswer();
        bool isSecretanswerCorrect = verifyWithUserSecretAnswer(username, secretanswer);

        if (isSecretanswerCorrect)
        {
            user->takeInputForPassword(std::string("\nEnter new password :"));
            user->takeConfirmpassword();
            forgotPasswordStatus = updateUserPassword();
        }
    }
    return forgotPasswordStatus;
}

bool Instagram::signup()
{
    bool addUserStatus;

    user->takeInputForUserName();

    std::string username = user->getUserName();
    bool isUserAlreayHadAccount = verifyTheUserDetails(username);

    if (isUserAlreayHadAccount)
    {
        addUserStatus = false;
    }
    else
    {
        user->takeInputForPassword(std::string("Enter password :"));
        user->takeInputForSecretQuestion();
        user->takeInputForSecretAnswer();

        nlohmann::ordered_json &usersData = instagramJsonData["Instagramusers"];
        nlohmann::ordered_json userData = getUserDataInJsonFormat();

        usersData.push_back(userData);
        instagramFileHandling->writeInstagramJsonFileData(instagramUserdataFile, instagramJsonData);
        addUserStatus = true;
    }
    return addUserStatus;
}

bool Instagram::verifyTheUserDetails(std::string username)
{
    bool isUserAlreadyExist = false;
    instagramJsonData = instagramFileHandling->getInstagramJsonFileData(instagramUserdataFile);

    for (auto user : instagramJsonData["Instagramusers"])
    {
        if (user["username"] == username)
        {
            isUserAlreadyExist = true;
        }
    }
    return isUserAlreadyExist;
}

bool Instagram::verifyTheUserDetails(std::string username, std::string password)
{
    bool isValidUser = false;

    instagramJsonData = instagramFileHandling->getInstagramJsonFileData(instagramUserdataFile);

    for (auto user : instagramJsonData["Instagramusers"])
    {
        if (user["username"] == username && user["password"] == password)
        {
            isValidUser = true;
            username = user["username"];
        }
    }
    return isValidUser;
}

void Instagram::gotoFeedPage(std::string username)
{
    bool inFeedPage = true, likeStatus;
    const int userMinChoice = 1, userMaxChoice = 4;
    InstagramJsonFileHandling instagramFileHandling;
    Feedpage feedPage(username, &instagramFileHandling);
    PostInfo postData = feedPage.firtPostInInstagram();

    while (inFeedPage)
    {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "                   FeedPage                    " << std::endl;
        std::cout << "************************************************" << std::endl;

        if (postData.post != "")
        {
            std::cout << "Post :" << postData.post << std::endl;
            std::cout << "Posted by :" << postData.posterName << std::endl;
        }
        else
        {
            std::cout << "No post Found or can't move" << std::endl;
        }

        std::cout << "\n1.Move to next post\n2.Move back to previous post\n3.like\n4.move back to previous menu\n";
        int userSelectedChoice = userChoosenChoice->getUserChoice(userMinChoice, userMaxChoice);
        feedOptions userchoice = (feedOptions)userSelectedChoice;

        switch (userchoice)
        {
        case feedOptions::movenext:
            postData = feedPage.moveToNextPost();
            break;

        case feedOptions::moveback:
            postData = feedPage.moveBackToPreviousPost();
            break;

        case feedOptions::like:
            likeStatus = feedPage.likePost(postData);
            if (likeStatus)
            {
                std::cout << "You liked the post :" << postData.post << std::endl;
            }
            else
            {
                std::cout << "You removed like from the post :" << postData.post << std::endl;
            }
            break;

        case feedOptions::gotoToPreviousMenu:
            inFeedPage = false;
            break;
        }
    }
}

void Instagram::gotoHomePage(std::string username)
{
    bool inHomePage = true, isAnyPostMadeByUser;
    const int userMinChoice = 1, userMaxChoice = 4;
    InstagramJsonFileHandling instagramFileHandling;
    Homepage homePage(username, &instagramFileHandling);

    while (inHomePage)
    {
        std::cout << "\n************************************************" << std::endl;
        std::cout << "                   HomePage                    " << std::endl;
        std::cout << "************************************************" << std::endl;

        std::cout << "\n1.Post a message\n2.Goto my post\n3.GoTo Feed\n4.SignOut\n";
        int userSelectedChoice = userChoosenChoice->getUserChoice(userMinChoice, userMaxChoice);
        userChoice userchoice = (userChoice)userSelectedChoice;

        switch (userchoice)
        {
        case userChoice::postAMessage:
            homePage.postAMessage();
            std::cout << "Posted a message!" << std::endl;
            break;

        case userChoice::gotoMyPosts:
            isAnyPostMadeByUser = homePage.displayMyPost();
            if (!isAnyPostMadeByUser)
            {
                std::cout << "User not posted any message!" << std::endl;
            }
            break;

        case userChoice::gotoToFeed:
            gotoFeedPage(username);
            break;

        case userChoice::Signout:
            inHomePage = false;
            break;
        }
    }
}
