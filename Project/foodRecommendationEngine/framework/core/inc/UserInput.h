#pragma once

#include <iostream>
#include <limits>

namespace foodRecommendationEngine { namespace framework { namespace core {

class UserIput
{
public:
    template <typename T>
    T takeInputFromUser(const std::string &promptMessage)
    {
        T value;
        bool takeInput = true;
        while (takeInput)
        {
            std::cout << promptMessage;
            std::cin >> value;

            if (std::cin.peek() != '\n')
            {
                std::cout << "Invalid input!!!" << std::endl;
            }
            else
            {
                takeInput = false;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return value;
    }

    std::string takeStringInputFromUser(const std::string &promptMessage)
    {
        std::string input;
        bool takeInput = true;

        while (takeInput)
        {
            std::cout << promptMessage;
            std::getline(std::cin, input);
            if (!input.empty())
            {
                takeInput = false;
            }
            else
            {
                std::cout << "Invalid input!!!" << std::endl;
            }
        }
        return input;
    }

    int takeInputChoiceFromUser(const int &minimumChoice,
                                const int &maximumChoice,
                                const std::string &promptMessage)
    {
        int userChoice;
        bool takeInput = true;
        while (takeInput)
        {
            std::cout << promptMessage;
            std::cin >> userChoice;

            if (std::cin.peek() != '\n')
            {
                std::cout << "Invalid input!!!" << std::endl;
            }
            else
            {
                if (userChoice >= minimumChoice && userChoice <= maximumChoice)
                {
                    takeInput = false;
                }
                else
                {
                    std::cout << "Invalid input!!!" << std::endl;
                }
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return userChoice;
    }
};

}}} // namespace foodRecommendationEngine::framework::core
