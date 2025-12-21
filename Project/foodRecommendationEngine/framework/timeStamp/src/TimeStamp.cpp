#include "TimeStamp.h"

namespace foodRecommendationEngine { namespace framework { namespace timeStamp {

CurrentDateTimeStamp TimeStamp::getCurrentTimeStamp()
{
    auto currentDateTimeStamp = std::time(0);
    time_t istTime = currentDateTimeStamp + (5 * 3600) + (30 * 60);
    auto time = std::gmtime(&istTime);

    CurrentDateTimeStamp timeStamp;

    timeStamp.date.day = time->tm_mday;
    timeStamp.date.month = time->tm_mon + 1;
    timeStamp.date.year = time->tm_year + 1900;

    timeStamp.time.hours = time->tm_hour;
    timeStamp.time.minutes = time->tm_min;
    timeStamp.time.seconds = time->tm_sec;
    timeStamp.time.period = time->tm_hour < 12 ? "AM" : "PM";

    return timeStamp;
}

std::string TimeStamp::getDateInStringFormat(const CurrentDate &date)
{
    std::string result = std::to_string(date.year);

    result += date.month < 10 ? "-0" + std::to_string(date.month) : "-" + std::to_string(date.month);
    result += date.day < 10 ? "-0" + std::to_string(date.day) : "-" + std::to_string(date.day);

    return result;
}

std::string TimeStamp::getTimeInStringFormat(const CurrentTime &time)
{
    std::string result;

    result = time.hours < 10 ? "0" + std::to_string(time.hours) : std::to_string(time.hours);
    result += time.minutes < 10 ? ":0" + std::to_string(time.minutes) : ":" + std::to_string(time.minutes);
    result += time.seconds < 10 ? ":0" + std::to_string(time.seconds) : ":" + std::to_string(time.seconds);

    return result;
}

}}} // foodRecommendationEngine::framework::timeStamp