#pragma once
#include "InstagramUser.h"
#include "nlohmann/json.hpp"
#include "IInstagram.h"
#include "getUserChoice.h"
#include "InstagramJsonFileHandling.h"

class Instagram : IInstagram
{
private:
    nlohmann::ordered_json instagramJsonData;
    std::string instagramUserdataFile;
    InstagramJsonFileHandling *instagramFileHandling;
    UserChoice *userChoosenChoice;
    InstagramUser *user;

protected:
    bool verifyTheUserDetails(std::string username, std::string password);
    bool verifyTheUserDetails(std::string username);
    bool updateUserPassword();
    bool verifyWithUserSecretAnswer(std::string username, std::string userAnswer);

    nlohmann::ordered_json getUserDataInJsonFormat();
    std::string getSecretquestion(std::string username);

    void gotoHomePage(std::string username);
    void gotoFeedPage(std::string username);

public:
    Instagram(InstagramJsonFileHandling *instagramFileHandling, UserChoice *userChoosenChoice, InstagramUser *user);
    bool signup() override;
    bool signin() override;
    bool forgotpassword() override;
};
