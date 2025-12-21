#pragma once

#include "IHandler.h"
#include "IAdmin.h"

namespace foodRecommendationEngine { namespace app { namespace client {
class Admin : public IAdmin
{
public:
    /**
     * Constructor
     */
    explicit Admin(std::shared_ptr<IHandler> handler);

    /**
     * @{
     * @file IAdmin methods
     */

    void setId(const uint32_t &Id) override;
    uint32_t getId() override;
    bool addUser(const foodRecommendationEngine::app::client::dataType::UserData &data) override;
    bool deleteUser(const uint32_t &id) override;
    bool addMenuItem(const foodRecommendationEngine::app::food::foodItem &item) override;
    bool updateMenuItem(const foodRecommendationEngine::app::food::foodItem &item) override;
    bool deleteMenuItem(const uint32_t &itemId) override;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() override;

    /**
     * @}
     */

    int getCountOfItemInMenu();
    Server::RequestMessage getAddMenuItemRequestMessage(const foodRecommendationEngine::app::food::foodItem &item);
    Server::RequestMessage getUpdateMenuItemRequestMessage(const foodRecommendationEngine::app::food::foodItem &item);
    Server::RequestMessage getDeleteMenuItemRequestMessage(const uint32_t &itemId);
    Server::RequestMessage getAddUserRequestMessage(const foodRecommendationEngine::app::client::dataType::UserData &data);
    Server::RequestMessage getDeleteUserRequestMessage(const uint32_t &id);
    void setMenuItemList(const nlohmann::ordered_json &jsonData);

private:
    uint32_t id_;
    std::shared_ptr<IHandler> handler_;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> menuItemList_;
};
}}} // namespace foodRecommendationEngine::app::client
