#include "Handler.h"
#include "Logger.h"

using Logger = foodRecommendationEngine::framework::logger::Logger;

namespace foodRecommendationEngine{ namespace app { namespace client{

Handler::Handler()
{
    sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed, Server not responds please try again!!!" << std::endl;
        exit(0);
    }
}

Handler::~Handler() {
    std::memset(writeBuffer, 0, WRITE_BUFFER_SIZE);
    close(sock);
}

Server::ResponseMessage Handler::handleRequest(
       const Server::RequestMessage &requestMessage)
{
    Logger::debug("Handler::handleRequest - entry");
    std::memset(writeBuffer, 0, WRITE_BUFFER_SIZE);

    auto request = serializeRequestMessage(requestMessage);

    send(sock, request.c_str(), READ_BUFFER_SIZE, 0);
    read(sock, writeBuffer, WRITE_BUFFER_SIZE);

    std::string result = writeBuffer;
    auto response = deserializedResponseMessage(result);
    Logger::debug("Handler::handleRequest - response from server " + result);

    Logger::debug("Handler::handlerRequest - existing");
    return response;
}

Server::ResponseMessage Handler::deserializedResponseMessage(const std::string &response)
{
    Logger::debug("Handler::deserializedResponseMessage - entering");
    Server::ResponseMessage serailizedResponse;
    try
    {
        serailizedResponse = Server::ResponseMessage::parse(response);
    }
    catch(nlohmann::ordered_json::parse_error &e)
    {
        std::string erorrMessage = e.what();
        Logger::error("nlohmann parsing got failed " + erorrMessage);
    }
    Logger::debug("Handler::deserializedResponseMessage - exiting");
    return serailizedResponse;
}

std::string Handler::serializeRequestMessage(const Server::RequestMessage &requestMessage)
{
    Logger::debug("Handler::serializeRequestMessage - entering");
    std::string request = std::to_string(static_cast<int>(requestMessage.type));
    Logger::debug("request type ::"+ request);
    request += requestMessage.query;
    Logger::debug("Handler::serializeRequestMessage - exiting");
    return request;
}

}}} // namespace foodRecommendationEngine::app::client
