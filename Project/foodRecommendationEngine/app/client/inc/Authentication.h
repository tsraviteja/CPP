#pragma once

#include "IAuthentication.h"
#include "Handler.h"
#include "ServerDataType.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class Authentication : public IAutentication
{
public:
    /**
     * constructor
     */
    explicit Authentication(std::shared_ptr<IHandler> handler);

    /**
     * @{
     * @file IAuthentication methods
     */

    bool login(const u_int32_t &id, const std::string &password, 
        const foodRecommendationEngine::app::client::dataType::UserType &userType) override;
    bool logout(const u_int32_t &id) override;

    /**
     * @}
     */

    /**
     * @brief Get the login query request message
     * 
     * @param id [in] -user Id
     * @param password [in] - user password
     * @param userType [in] - client type enum
     * @return foodRecommendationEngine::app::Server::RequestMessage - 
     * request message contains request type and query. 
     */
    foodRecommendationEngine::app::server::RequestMessage getLoginQueryRequestMessage(
        const u_int32_t &id, const std::string &password,
        const foodRecommendationEngine::app::client::dataType::UserType &userType);

    /**
     * @brief Get the logout query request message
     * 
     * @param id [in] -user Id
     * @return foodRecommendationEngine::app::Server::RequestMessage - 
     * request message contains request type and query. 
     */
    foodRecommendationEngine::app::server::RequestMessage getLogoutQueryRequestMessage(
        const u_int32_t &id);

private:
    std::shared_ptr<IHandler> handler_;
};

}}} // namespace foodRecommendationEngine::app::client
