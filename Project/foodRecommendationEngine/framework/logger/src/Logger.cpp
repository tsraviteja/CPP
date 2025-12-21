#include "Logger.h"
#include "TimeStamp.h"

using TimeStamp = foodRecommendationEngine::framework::timeStamp::TimeStamp;

namespace foodRecommendationEngine { namespace framework { namespace logger{ 

std::string Logger::loggerFilePath_  = "../.build/log.log";

void Logger::debug(const std::string &debugStatement)
{
    std::ofstream input(loggerFilePath_, std::ios::app);
    auto timeStamp = TimeStamp::getCurrentTimeStamp();

    auto date = TimeStamp::getDateInStringFormat(timeStamp.date);
    auto time = TimeStamp::getTimeInStringFormat(timeStamp.time);

    auto statement = "[" + date + " - " + time + "]  Logger::debug::" + debugStatement;

    if(input.is_open())
    {
        input << statement << "\n";
        input.close();
    }
}

void Logger::error(const std::string &errorStatement)
{
    std::ofstream input(loggerFilePath_, std::ios::app);
    auto timeStamp = TimeStamp::getCurrentTimeStamp();

    auto date = TimeStamp::getDateInStringFormat(timeStamp.date);
    auto time = TimeStamp::getTimeInStringFormat(timeStamp.time);

    auto statement = "[" + date + " - " + time + "]  Logger::error::" + errorStatement;

    if(input.is_open())
    {
        input << statement << "\n";
        input.close();
    }
}

}}} // foodRecommendationEngine::framework::logger
