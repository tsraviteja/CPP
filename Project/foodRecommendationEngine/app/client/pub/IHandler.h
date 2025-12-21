#pragma once

#include <iostream>

#include "ServerDataType.h"

namespace Server = foodRecommendationEngine::app::server;

namespace foodRecommendationEngine{ namespace app { namespace client {
class IHandler
{
public:
    /**
     * Destrutor
     */
    virtual ~IHandler() {}

    /**
     * @brief Handle the request of the client
     * 
     * @param requestMessage [in] - request message to handler
     * @return Server::ResponseMessage - return reponse with status code,
     * body and error message if fails to process the request 
     */
    virtual Server::ResponseMessage handleRequest(
        const Server::RequestMessage &requestMessage) = 0;
};

}}} // namespace foodRecommendationEngine::app::client
