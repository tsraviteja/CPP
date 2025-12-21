#pragma once

#include "IHandler.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 4096

namespace foodRecommendationEngine { namespace app { namespace client {
class Handler : public IHandler
{
public:
   Handler();
   ~Handler();

   /**
    * @{
    * @file IHandler method
    */
   Server::ResponseMessage handleRequest(
       const Server::RequestMessage &requestMessage) override;

   /**
    * @}
    */

    std::string serializeRequestMessage(const Server::RequestMessage &requestMessage);
    Server::ResponseMessage deserializedResponseMessage(const std::string &response);

private:
   int sock = 0;
   struct sockaddr_in serv_addr;
   char writeBuffer[WRITE_BUFFER_SIZE];
};
}}} // namespace foodRecommendationEngine::app::client
