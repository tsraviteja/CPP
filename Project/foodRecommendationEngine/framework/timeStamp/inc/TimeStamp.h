#pragma once

#include <ctime>
#include <iostream>

#include "TimeStampDataType.h"

namespace foodRecommendationEngine { namespace framework {namespace timeStamp {

class TimeStamp
{
public:
    /**
     * @brief gets the current date and time
     */
    static CurrentDateTimeStamp getCurrentTimeStamp();

    /**
     * @brief gets the current time in string format
     */
    static std::string getTimeInStringFormat(const CurrentTime &time);

    /**
     * @brief gets the current date in string format
     */
    static std::string getDateInStringFormat(const CurrentDate &date);
};

}}} // foodRecommendationEngine::framework::timeStamp
