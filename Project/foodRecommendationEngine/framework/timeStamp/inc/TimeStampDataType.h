#pragma once

#include <iostream>

namespace foodRecommendationEngine { namespace framework { namespace timeStamp {

struct CurrentDate
{
    int day;
    int month;
    int year;
};

struct CurrentTime
{
    int hours;
    int minutes;
    int seconds;
    std::string period;
};

struct CurrentDateTimeStamp
{
    CurrentDate date;
    CurrentTime time;
};

}}} // foodRecommendationEngine::framework::timeStamp
