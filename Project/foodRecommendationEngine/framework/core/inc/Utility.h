#pragma once

#include <iostream>

namespace foodRecommendationEngine { namespace framework { namespace core {

class Utility
{
    public:

    /**
     * @brief get length of string
     *
     * @param input [in] - input string for length of it
     * @return length of the string input
     */
    static int getLength(const std::string &input);

     /**
     * @brief checks for numeric character or not
     *
     * @param character [in] - input checks for numeric character
     * @return true or false
     */
    static bool isNumericCharacter(const char &character);

    /**
     * @brief power to base based on raisingPower
     * 
     * @return int - power of base to raisingPower
     */
    static int power(int base, int raisingPower);

    /**
     * @brief parse the string input to integer
     *
     * @param input [in] - input parameter for parsing to integer
     * @return std::pair<bool, int> [out]
     * bool - result success or failure
     * int - sucess then parased value
     */
    static std::pair<bool, int> parseToInteger(const std::string &input);

    /**
     * @brief parse the string input to double
     *
     * @param input [in] - input parameter for parsing to double
     * @return std::pair<bool, double> [out]
     * bool - result success or failure
     * double - sucess then parased value
     */
    static std::pair<bool, double> parseToDouble(const std::string &input);

    /**
     * @brief parse the user choice
     *
     * @param userChoice [in] - user choice in string formatt
     * @param minimumChoice [in] - minimum choice that user can be selected
     * @param maximumChoice [in] - maximum choice that user can be selected
     * @returns std::pair<bool, int> 
     * 1.bool - results true for success false for failure
     * 2.int - if success parsed user choice else 0
     */
    static std::pair<bool, int> parseUserChoice(const std::string &userChoice,
                                                const int &minimumChoice,
                                                const int &maximumChoice);

    int searchSubString(const std::string &text, const std::string &subString);
};

}}} // namespace foodRecommendationEngine::framework::core
