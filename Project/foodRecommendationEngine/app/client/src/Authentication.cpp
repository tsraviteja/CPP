#include "Authentication.h"
#include "Logger.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

using Logger = foodRecommendationEngine::framework::logger::Logger;
using RequestMessage = foodRecommendationEngine::app::server::RequestMessage;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;

namespace foodRecommendationEngine { namespace app { namespace client {

Authentication::Authentication(std::shared_ptr<IHandler> handler) : handler_(handler)
{
    Logger::debug("Authentication::Authentication - constructed");
}

bool Authentication::login(const u_int32_t &id, const std::string &password, const DataType::UserType &userType)
{
    Logger::debug("Authentication::login - entering");
    auto requestMessage = getLoginQueryRequestMessage(id, password, userType);
    auto response = handler_->handleRequest(requestMessage);
    bool success = false;

    if (response["status_code"] == StatusCode::OK)
    {
        success = true;
        Logger::debug("Login is Succesful !!!");
    }
    Logger::debug("Authentication::login - exiting");
    return success;
}

bool Authentication::logout(const u_int32_t &id)
{
    Logger::debug("Authentication::logout - entering");
    Logger::debug("Authentication::logout - exiting");
    return true;
}

RequestMessage Authentication::getLoginQueryRequestMessage(const u_int32_t &id,
                                                           const std::string &password,
                                                           const DataType::UserType &userType)
{
    Logger::debug("Authentication::getLoginQueryRequestMessage - entering");

    RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    std::string query = "select id, password, role from User where Id =" + std::to_string(id) + 
                        " and password = '" + password + "' and role = '" + 
                        DataType::UserTypeLiteralForm.at(userType) + "'";
    requestMessage.query = query;
    Logger::debug("query is :" + query);

    Logger::debug("Authentication::getLoginQueryRequestMessage - exiting");
    return requestMessage;
}

RequestMessage Authentication::getLogoutQueryRequestMessage(const u_int32_t &id)
{
    Logger::debug("Authentication::getLogoutQueryRequestMessage - entering");

    RequestMessage requestMessage;
    requestMessage.type = RequestType::PATCH;
    std::string query = "select id, password, loginStatus from User where Id =" + std::to_string(id);
    requestMessage.query = query;

    Logger::debug("Authentication::getLogoutQueryRequestMessage - exiting");
    return requestMessage;
}

}}} // namespace foodRecommendationEngine::app::client
