#pragma once

#include <iostream>

#include "nlohmann/json.hpp"

namespace foodRecommendationEngine { namespace app { namespace server {

enum RequestType
{
    GET = 0,
    POST = 1,
    PATCH = 2,
    DELETE = 3,
    MIN = GET,
    MAX = DELETE
};

enum StatusCode
{
    OK = 200,
    CREATED = 201,
    BAD_REQUEST = 400,
    NOT_FOUND = 404
};

struct RequestMessage
{
    RequestType type;
    std::string query;
};

typedef nlohmann::ordered_json ResponseMessage;

}}}; // namespace foodRecommendationEngine::app::server
