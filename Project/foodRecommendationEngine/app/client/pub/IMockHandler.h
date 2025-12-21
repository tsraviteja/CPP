#pragma once

#include "IHandler.h"

#include <gmock/gmock.h>

namespace foodRecommendationEngine{ namespace app { namespace client {

class IMockHandler : public IHandler
{
public:
    IMockHandler() {}
    virtual ~IMockHandler() {}

    MOCK_METHOD1(handleRequest, Server::ResponseMessage(const Server::RequestMessage &requestMessage));
};

}}} // namespace foodRecommendationEngine::app::client
