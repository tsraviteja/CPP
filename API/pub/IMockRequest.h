#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IRequest.h"

namespace API {

class IMockRequest : public IRequest
{
    public:
        IMockRequest() {};
        ~IMockRequest() {};

        MOCK_METHOD1(get, std::pair<int, json>(const char *url));
        MOCK_METHOD2(post, std::pair<int, json>(const char *url, const std::string &requestBody));
        MOCK_METHOD2(patch, std::pair<int, json>(const char *url, const std::string &requestBody));
        MOCK_METHOD2(put, std::pair<int, json>(const char *url, const std::string &requestBody));
        MOCK_METHOD1(delete$, std::pair<int, json>(const char *url));
};

} // namespace API
