#include "Admin.h"
#include "Logger.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

using FoodItem = foodRecommendationEngine::app::food::foodItem;
using Item = foodRecommendationEngine::app::food::Item;
using MealType = foodRecommendationEngine::app::food::MealType;
using Logger = foodRecommendationEngine::framework::logger::Logger;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;

namespace foodRecommendationEngine { namespace app { namespace client{

Admin::Admin(std::shared_ptr<IHandler> handler)
            : handler_(handler)
{
    Logger::debug("Admin::Admin constructor constructed");
}

bool Admin::addMenuItem(const FoodItem &item)
{
    auto id = std::to_string(item.id);
    bool result = false;

    Logger::debug("Admin::addFoodItem  - entering, ItemId{"+ id + "}");
    auto requestMessage = getAddMenuItemRequestMessage(item);
    auto response = handler_->handleRequest(requestMessage);

    if (response["status_code"] == server::StatusCode::CREATED)
    {
        result = true;
    }
    Logger::debug("Admin::addFoodItem  - exiting, ItemId{"+ id + "}");
    return result;
}

bool Admin::addUser(const DataType::UserData &data)
{
    Logger::debug("Admin::addUser - entering");
    auto requestMessage = getAddUserRequestMessage(data);
    auto response = handler_->handleRequest(requestMessage);
    auto success = false;
    if (response["status_code"] == StatusCode::CREATED)
    {
        success = true;
    }
    Logger::debug("Admin::addUser - exiting");
    return success;
}

bool Admin::deleteUser(const uint32_t &id)
{
    Logger::debug("Admin::deleteUser - entering");
    auto requestMessage = getDeleteUserRequestMessage(id);
    auto response = handler_->handleRequest(requestMessage);

    auto success = false;
    if (response["status_code"] == StatusCode::OK)
    {
        success = true;
    }
    Logger::debug("Admin::deleteUser - exiting");
    return success;
}

bool Admin::deleteMenuItem(const uint32_t &id)
{
    bool result = false;
    Logger::debug("Admin::deleteMenuItem  - entering");
    auto requestMessage = getDeleteMenuItemRequestMessage(id);
    auto response = handler_->handleRequest(requestMessage);

    if (response["status_code"] == server::StatusCode::OK)
    {
        result = true;
    }
    Logger::debug("Admin::deleteMenuItem  - exiting");
    return result;
}

bool Admin::updateMenuItem(const FoodItem &item)
{
    auto id = std::to_string(item.id);
    bool result = false;

    Logger::debug("Admin::addFoodItem  - entering, ItemId{"+ id + "}");
    auto requestMessage = getUpdateMenuItemRequestMessage(item);
    auto response = handler_->handleRequest(requestMessage);

    if (response["status_code"] == server::StatusCode::OK)
    {
        result = true;
    }
    Logger::debug("Admin::addFoodItem  - exiting, ItemId{"+ id + "}");
    return result;
}

void Admin::setMenuItemList(const nlohmann::ordered_json &jsonData)
{
    Logger::debug("Admin::setMenuItemList - entering");
    for(const auto &menuItem : jsonData["body"])
    {
        FoodItem item;
        item.id = menuItem["itemId"];
        item.name = menuItem["itemName"];
        item.price = menuItem["price"];
        item.isAvailable = menuItem["isAvailable"] == 1 ? true : false;
        std::string mealTypeLiteral = menuItem["mealType"];
        MealType mealtype;

        for (const auto &pair : foodRecommendationEngine::app::food::MealTypeLiteral)
        {
            if (pair.second == mealTypeLiteral)
            {
                mealtype = pair.first;
            }
        }
        item.mealType = mealtype;

        auto foodItem = std::make_shared<Item>(item);
        menuItemList_.push_back(foodItem);
    }
    Logger::debug("Admin::setMenuItemList - exting");
}

std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> Admin::viewMenuList()
{
    Logger::debug("Admin::viewMenuList - entering");
    menuItemList_.clear();
    auto menuItemCount = getCountOfItemInMenu();
    auto limit = 5;
    auto offset = 0;

    server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;

    while (menuItemCount > 0)
    {
        requestMessage.query = "select * from MenuItem limit " + std::to_string(limit) +
                               " offset " + std::to_string(offset);

        auto response = handler_->handleRequest(requestMessage);
        setMenuItemList(response);
        limit += 5;
        offset += 5;
        menuItemCount -= 5;

    }

    Logger::debug("Admin::viewMenuList - exiting");
    return menuItemList_;
}

int Admin::getCountOfItemInMenu()
{
   Logger::debug("Admin::getCountOfItemInMenu - entering");
   auto totalCountOfItem = 0;
   server::RequestMessage requestMessage;
   requestMessage.type = RequestType::GET;
   requestMessage.query = "select count(itemId) from MenuItem";

   auto response = handler_->handleRequest(requestMessage);
   if (response["status_code"] == StatusCode::OK)
   {
        totalCountOfItem = response["body"][0]["count(itemId)"];
   }
   Logger::debug("Admin::getCountOfItemInMenu- exiting");
   return  totalCountOfItem;
}

void Admin::setId(const uint32_t &id)
{
    id_ = id;
}

uint32_t Admin::getId()
{
    return id_;
}

server::RequestMessage Admin::getAddMenuItemRequestMessage(const FoodItem &item)
{
    Logger::debug("Admin::getAddMenuItemRequestMessage - entering");
    server::RequestMessage requestMessage;
    requestMessage.type = RequestType::POST;

    auto status = item.isAvailable ? "1" : "0";
    auto mealType = foodRecommendationEngine::app::food::MealTypeLiteral.at(item.mealType);
    auto query = "insert into MenuItem values(" + std::to_string(item.id) + ",'" + 
                  item.name + "'," + std::to_string(item.price) + ",'" + mealType + "',"  + status +")";

    requestMessage.query = query;
    Logger::debug("Admin::getAddMenuItemRequestMessage - exiting");
    return requestMessage;
}

server::RequestMessage Admin::getUpdateMenuItemRequestMessage(const FoodItem &item)
{
    Logger::debug("Admin::getUpdateMenuItemRequestMessage - entering");
    server::RequestMessage requestMessage;
    requestMessage.type = RequestType::PATCH;

    auto status = item.isAvailable ? "1" : "0";
    auto mealType = foodRecommendationEngine::app::food::MealTypeLiteral.at(item.mealType);
    auto query = "update MenuItem set itemName = '" + item.name + "', price =" +
                 std::to_string(item.price) + ", isAvailable  = " + status + 
                 ", mealType='" + mealType + "' where itemId  = " + std::to_string(item.id);
    requestMessage.query = query;

    Logger::debug("Admin::getUpdateMenuItemRequestMessage - exiting");
    return requestMessage;
}

server::RequestMessage Admin::getDeleteMenuItemRequestMessage(const uint32_t &itemId)
{
    Logger::debug("Admin::getDeleteMenuItemRequestMessage - entering");
    server::RequestMessage requestMessage;
    requestMessage.type = RequestType::DELETE;

    auto query = "delete from MenuItem where itemId =" + std::to_string(itemId);
    requestMessage.query = query;
    Logger::debug("Admin::getDeleteMenuItemRequestMessage - exiting");
    return requestMessage;
}

server::RequestMessage Admin::getAddUserRequestMessage(const DataType::UserData &data)
{
    Logger::debug("Admin::getAddUserRequestMessage - entring");

    server::RequestMessage request;
    request.type = RequestType::POST;

    std::string query = "insert into User values(" + std::to_string(data.id) +
                        ",'" + data.name + "'," + "'" + data.password + "'," +
                        "'" + DataType::UserTypeLiteralForm.at(data.role) + "')";

    request.query = query;

    Logger::debug("Admin::getAddUserRequestMessage - existing");
    return request;
}

server::RequestMessage Admin::getDeleteUserRequestMessage(const uint32_t &id)
{
    Logger::debug("Admin::getDeleteUserRequestMessage - entring");

    server::RequestMessage request;
    request.type = RequestType::DELETE;
    std::string query = "delete from User where id = '" + std::to_string(id) + "'";
    request.query = query;

    Logger::debug("Admin::getDeleteUserRequestMessage - existing");
    return request;
}

}}} // namespace foodRecommendationEngine::app::client
