/**********************************************************
 * @file RequestDataType.h
 * @brief Request data type definitions for API request operations.
 * @date  27-06-2026
 **********************************************************/

#pragma once

#include <iostream>

#include "nlohmann/json.hpp"

namespace API
{
    typedef nlohmann::json Json;

    enum class StatusCode
    {
        OK = 200,
        CREATED = 201,
        BAD_REQUEST = 400,
        NOT_FOUND = 404,
        SERVICE_UNAVAILABLE = 503,
        INTERNAL_SERVER_ERROR = 500
    };

    typedef std::pair<StatusCode, Json> Response;
}; // namespace API
