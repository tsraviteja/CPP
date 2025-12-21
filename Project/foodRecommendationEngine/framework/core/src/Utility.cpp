#include "Utility.h"

namespace foodRecommendationEngine { namespace framework { namespace core {

std::pair<bool, int> Utility::parseToInteger(const std::string &input)
{
    std::pair<bool, int> result;
    result.first = true;

    auto length = getLength(input);
    int parseInteger = 0;

    for(auto index = 0; index < length; index++)
    {
        auto isNumeric = isNumericCharacter(input[index]);
        if(isNumeric)
        {
            parseInteger = parseInteger * 10 + input[index] - 48;
        }
        else
        {
            result.first = false;
            break;
        }
    }

    if(result.first)
    {
        result.second = parseInteger;
    }

    return result;
}

std::pair<bool,double> Utility::parseToDouble(const std::string &userInput)
{
    std::pair<bool, double> result{0.0, false};
    int inputlength = getLength(userInput);
    bool isDotFound = false;
    int dotFoundAtPosition, currentPosition;

    if (inputlength > 0)
    {
        result.first = true;
        for (int index = 0; index < inputlength; index++)
        {
            currentPosition = index;
            if (isNumericCharacter(userInput[index]))
            {
                result.second = result.second * 10 + (userInput[index] - 48);
            }
            else if (userInput[index] == '.' && !isDotFound)
            {
                isDotFound = true;
                dotFoundAtPosition = index;
            }
            else
            {
                result.first = false;
                result.second = 0;
                break;
            }
        }
    }
    if (result.first)
    {
        int tensPower = power(10, (currentPosition - dotFoundAtPosition - 1));
        result.second = result.second / tensPower;
    }
    return result;
}

int Utility::searchSubString(const std::string &text, const std::string &subString)
{
    const int max = 256;
    int table[max];
    auto subStringLength = getLength(subString);
    auto textLength = getLength(text);

    for(auto index = 0; index < max; index++)
    {
        table[index] = subStringLength;
    }
    
    for(auto index = 0; index < subStringLength - 1; index++)
    {
        table[subString[index]] = subStringLength - 1 - index;
    }

    auto index = subStringLength - 1;
    int length;
    while(index < textLength)
    {
        length = 0;
        while(length < subStringLength && subString[subStringLength - 1 - length] == text[index-length])
        {
            length++;
        }
        if(length == subStringLength)
        {
            return (index - subStringLength + 1);
        }
        index = index + table[text[index]];
    }
    return -1;
}

int Utility::power(int base, int raisingPower)
{
    int result = base;

    if (raisingPower >= 1)
    {
        for (int count = 0; count < raisingPower; count++)
        {
            result = result * base;
        }
    }
    return result;
}

int Utility::getLength(const std::string &input)
{
    int length = 0;

    for(auto index = 0; input[index] != '\0'; index++)
    {
        length++;
    }

    return length;
}

bool Utility::isNumericCharacter(const char &character)
{
    bool result = false;

    if (character >= '0' && character <= '9')
    {
        result = true;
    }

    return result;
}

std::pair<bool, int> Utility::parseUserChoice(const std::string &userChoice,
                                              const int &minimumChoice,
                                              const int &maximumChoice)
{
    auto result = parseToInteger(userChoice);

    if (result.first)
    {
        if (result.second < minimumChoice && result.second > maximumChoice)
        {
            result.first = false;
            result.second = 0;
        }
    }
    return result;
}

}}} // namespace foodRecommendationEngine::app::client
