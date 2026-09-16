/**********************************************************
 * @file IMockRequest.h
 * @brief Mock request class header file for testing API request operations.
 * @date  27-06-2026
 **********************************************************/

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

        MOCK_METHOD1(get, Response(const char *url));
        MOCK_METHOD2(post, Response(const char *url, const std::string &requestBody));
        MOCK_METHOD2(patch, Response(const char *url, const std::string &requestBody));
        MOCK_METHOD2(put, Response(const char *url, const std::string &requestBody));
        MOCK_METHOD1(delete$, Response(const char *url));
};

} // namespace API
