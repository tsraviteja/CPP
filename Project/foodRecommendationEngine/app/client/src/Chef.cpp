#include "Chef.h"

#include "Logger.h"
#include "TimeStamp.h"

using CurrentTime = foodRecommendationEngine::framework::timeStamp::CurrentTime;
using FoodItem = foodRecommendationEngine::app::food::foodItem;
using Item = foodRecommendationEngine::app::food::Item;
using Logger = foodRecommendationEngine::framework::logger::Logger;
using MealType = foodRecommendationEngine::app::food::MealType;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;
using TimeStamp = foodRecommendationEngine::framework::timeStamp::TimeStamp;

namespace foodRecommendationEngine { namespace app { namespace client {

Chef::Chef(std::shared_ptr<IHandler> handler, std::shared_ptr<IEngine> engine) 
                : handler_(handler), engine_(engine)
{
    Logger::debug("Chef::Chef - constructed");
}

int Chef::getId()
{
    return id_;
}

void Chef::setId(const int &id)
{
    id_ = id;
}

void Chef::setEmployeeResponse(const nlohmann::ordered_json &jsonData)
{
    Logger::debug("Chef::setEmployeeResponse - entering");
    for (const auto &voteData : jsonData["body"])
    {
        DataType::EmployeeResponse employeeResponse;
        employeeResponse.itemId = voteData["itemId"];
        employeeResponse.mealType = voteData["mealType"];
        employeeResponse.totalVotes = voteData["totalVotes"];

        employeeResponse_.push_back(employeeResponse);
    }
    Logger::debug("Chef::setEmployeeResponse - exiting");
}

std::vector<DataType::EmployeeResponse> Chef::viewEmployeeResponse()
{
    Logger::debug("Chef::viewEmployeeResponse - entering");
    employeeResponse_.clear();
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    for(const auto &mealType : foodRecommendationEngine::app::food::MealTypeLiteral)
    {
        std::string query = "select itemId, mealType, count(employeeId) as totalVotes"
                            " from VoteDailyMenuItem where mealType='" + mealType.second +"' group by itemId, mealType"
                            " order by totalVotes desc, mealType, itemId limit 10";

        requestMessage.query = query;
        auto response = handler_->handleRequest(requestMessage);
        if (response["status_code"] == StatusCode::OK)
        {
            setEmployeeResponse(response);
        }
    }
    Logger::debug("Chef::viewEmployeeResponse - exiting");
    return employeeResponse_;
}

std::string Chef::getMealTypeLiteral(const foodRecommendationEngine::app::food::MealType &mealType)
{
    Logger::debug("Chef::getMealType - entering");
    std::string mealTypeLiteral;
    if (foodRecommendationEngine::app::food::MealTypeLiteral.count(mealType) > 0)
    {
        mealTypeLiteral = foodRecommendationEngine::app::food::MealTypeLiteral.at(mealType);
    }
    Logger::debug("Chef::getMealType - exiting");
    return mealTypeLiteral;
}

Server::RequestMessage Chef::getDailyMenuRequestMessage(const DataType::RollOutMenuItemData &rollOutMenuItemData)
{
    Logger::debug("Chef::getDailyMenuRequestMessage - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::POST;
    auto currentTime = TimeStamp::getCurrentTimeStamp();
    auto mealType = getMealTypeLiteral(rollOutMenuItemData.mealType);
    auto date = TimeStamp::getDateInStringFormat(currentTime.date);
    auto itemId = rollOutMenuItemData.itemId;
    const std::string query = "insert into DailyMenuItem values('" + date + "'," + std::to_string(itemId) +
                              ",'" + mealType + "')";

    requestMessage.query = query;
    Logger::debug("Chef::getDailyMenuRequestMessage - exiting");
    return requestMessage;
}

std::vector<engineDataType::RecommendedFoodItem> 
        Chef::getRecommendedItemsFromEngine(const foodRecommendationEngine::app::food::MealType &mealType)
{
    Logger::debug("Chef::getRecommendedItemsFromEngine - entering");
    auto mealTypeLiteral = foodRecommendationEngine::app::food::MealTypeLiteral.at(mealType);
    Logger::debug("Chef::getRecommendedItemsFromEngine - exiting");
    return engine_->getRecommendedFoodItems(mealTypeLiteral);
}

bool Chef::rollOutDialyMenuItem(const DataType::RollOutMenuItemData &rollOutMenuItemData)
{
    Logger::debug("Chef::rollOutDialyMenuItem - entering");
    auto requestMessage = getDailyMenuRequestMessage(rollOutMenuItemData);
    auto result = false;
    auto response = handler_->handleRequest(requestMessage);
    if(response["status_code"] == StatusCode::CREATED)
    {
        result = true;
    }
    Logger::debug("Chef::rollOutDialyMenuItem - exiting");
    return result;
}

void Chef::setMenuItemList(const nlohmann::ordered_json &jsonData)
{
    Logger::debug("Chef::setMenuItemList - entering");
    for(const auto &menuItem : jsonData["body"])
    {
        FoodItem item;
        item.id = menuItem["itemId"];
        item.name = menuItem["itemName"];
        item.price = menuItem["price"];
        item.isAvailable = menuItem["isAvailable"] == 1 ? true : false;
        auto mealTypeLiteral = menuItem["mealType"];
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
    Logger::debug("Chef::setMenuItemList - exting");
}

std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> Chef::viewMenuList()
{
    Logger::debug("Chef::viewMenuList - entering");
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

    Logger::debug("Chef::viewMenuList - exiting");
    return menuItemList_;
}

int Chef::getCountOfItemInMenu()
{
   Logger::debug("Chef::getCountOfItemInMenu - entering");
   auto totalCountOfItem = 0;
   server::RequestMessage requestMessage;
   requestMessage.type = RequestType::GET;
   requestMessage.query = "select count(itemId) from MenuItem";

   auto response = handler_->handleRequest(requestMessage);
   if (response["status_code"] == StatusCode::OK)
   {
        totalCountOfItem = response["body"][0]["count(itemId)"];
   }
   Logger::debug("Chef::getCountOfItemInMenu- exiting");
   return  totalCountOfItem;
}
}}} // namespace foodRecommendationEngine::app::client
