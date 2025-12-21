#pragma once

#include <fstream>
#include <iostream>
#include <ostream>

namespace foodRecommendationEngine { namespace framework { namespace logger {

class Logger
{
public:
    /**
     * @brief logger statement for debug
     *
     * @param debugStatement [in] - logger debug statement
     */
    static void debug(const std::string &debugStatement);

    /**
     * @brief logger statement for error
     *
     * @param errorStatement [in] - logger error statement
     */
    static void error(const std::string &errorStatement);

private:
    static std::string loggerFilePath_;
};

}}} // namespace foodRecommendationEngine::framework::logger
