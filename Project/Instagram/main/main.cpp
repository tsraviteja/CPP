#include <iostream>
#include "userChoice.h"
#include "getUserChoice.h"
#include "Instagram.h"
#include "InstagramUser.h"
#include "InstagramJsonFileHandling.h"

void displaySigUpStatus(bool signupStatus)
{
    if (signupStatus)
    {
        std::cout << "SignUp Successful!" << std::endl;
        return;
    }
    std::cout << "User is already exists!" << std::endl;
}

void displayforgotpasswordStatus(bool forgotpasswordStatus)
{
    if (forgotpasswordStatus)
    {
        std::cout << "password updated successfuy!" << std::endl;
        return;
    }
    std::cout << "Invalid user!" << std::endl;
}

void displaySiginStatus(bool signinStatus)
{
    if (signinStatus)
    {
        std::cout << "Sigout successfully!" << std::endl;
        return;
    }
    std::cout << "Inavlid user!" << std::endl;
}

int main()
{
    bool openMiniInstagram = true;
    bool signupStatus, signinStatus, forgotpasswordStatus;
    const int userMinChoice = 1, userMaxChoice = 4;

    InstagramJsonFileHandling instagramFileHandling;
    UserChoice userChoosenChoice;
    InstagramUser user;
    Instagram miniInstagram(&instagramFileHandling, &userChoosenChoice, &user);

    std::cout << "*****************MINI INSTAGRAM*****************" << std::endl;
    while (openMiniInstagram)
    {

        std::cout << "\n************************************************" << std::endl;
        std::cout << "                   LoginPage                    " << std::endl;
        std::cout << "************************************************" << std::endl;

        std::cout << "\n1.SignIn\n2.SignUp\n3.Forgotpassword\n4.Exit\n";
        int userSelectedChoice = userChoosenChoice.getUserChoice(userMinChoice, userMaxChoice);

        AuthSelection userchoice = (AuthSelection)userSelectedChoice;

        switch (userchoice)
        {
        case AuthSelection::Signin:
            signinStatus = miniInstagram.signin();
            displaySiginStatus(signinStatus);
            break;

        case AuthSelection::Signup:
            signupStatus = miniInstagram.signup();
            displaySigUpStatus(signupStatus);
            break;

        case AuthSelection::ForgotPassword:
            forgotpasswordStatus = miniInstagram.forgotpassword();
            displayforgotpasswordStatus(forgotpasswordStatus);
            break;

        case AuthSelection::Exit:
            std::cout << "Program ends!" << std::endl;
            openMiniInstagram = false;
            break;
        }
    }
    return 0;
}
