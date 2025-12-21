#include "Employee.h"

#include "Logger.h"
#include "TimeStamp.h"

using FoodItem = foodRecommendationEngine::app::food::foodItem;
using Item = foodRecommendationEngine::app::food::Item;
using Logger = foodRecommendationEngine::framework::logger::Logger;
using MealType = foodRecommendationEngine::app::food::MealType;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;
using TimeStamp = foodRecommendationEngine::framework::timeStamp::TimeStamp;

namespace foodRecommendationEngine { namespace app { namespace client {

Employee::Employee(std::shared_ptr<IHandler> handler) 
                : handler_(handler)
{
    Logger::debug("Employee::Employee - constructed");
}

int Employee::getId()
{
    return id_;
}

void Employee::setId(const int &id)
{
    id_ = id;
}

bool Employee::provideFeedback(const DataType::FeedbackData &feedbackData)
{
    Logger::debug("Employee::provideFeedback - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::POST;
    requestMessage.query = "insert into Feedback values(" + std::to_string(feedbackData.employeeId) +
                            "," + std::to_string(feedbackData.itemId) + "," + std::to_string(feedbackData.rating) +
                            ",'" + feedbackData.comment + "','" + feedbackData.momRecipe + "')";
    Logger::debug("query is :" + requestMessage.query);
    auto response = handler_->handleRequest(requestMessage);
    auto result = false;
    if (response["status_code"] == StatusCode::CREATED)
    {
        result = true;
    }
    Logger::debug("Employee::provideFeedback - exiting");
    return result;
}

void Employee::setMenuItemList(const nlohmann::ordered_json &jsonData)
{
    Logger::debug("Employee::setMenuItemList - entering");
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
    Logger::debug("Employee::setMenuItemList - exting");
}

void Employee::setDialymenuItemList(const nlohmann::ordered_json &jsonData)
{
    Logger::debug("Employee::setDialymenuItemList - entering");
    for(const auto &dailyMenuItem : jsonData["body"])
    {
        DataType::DialyMenuItemData item;
        item.dailyMenuItemId = dailyMenuItem["dailyMenuItemId"];
        item.itemId = dailyMenuItem["itemId"];
        item.mealType = dailyMenuItem["mealType"];
        dailyMenuItemList_.push_back(item);
    }
    Logger::debug("Employee::setDialymenuItemList - exiting");
}

std::vector<DataType::DialyMenuItemData> Employee::viewDailyMenuItem(const foodRecommendationEngine::app::food::MealType &mealType)
{
    Logger::debug("Employee::viewDailyMenuItem - entering");
    dailyMenuItemList_.clear();
    auto mealTypeLiteral = foodRecommendationEngine::app::food::MealTypeLiteral.at(mealType);
    auto timeStamp = TimeStamp::getCurrentTimeStamp();
    auto date = TimeStamp::getDateInStringFormat(timeStamp.date);
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    std::string query = "select * from DailyMenuItem where mealType = '" + mealTypeLiteral + 
                        "' and dailyMenuItemId = '" + date + "'";
    requestMessage.query = query;
    auto response = handler_->handleRequest(requestMessage);
    if (response["status_code"] == StatusCode::OK)
    {
        setDialymenuItemList(response);
    }
    Logger::debug("Employee::viewDailyMenuItem - exiting");
    return dailyMenuItemList_;
}

bool Employee::voteForDailyMenuItem(const int &itemId)
{
    Logger::debug("Employee::voteForDailyMenuItem - entering");
    auto result = false;
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::POST;
    auto timestamp = TimeStamp::getCurrentTimeStamp();
    auto date = TimeStamp::getDateInStringFormat(timestamp.date);
    auto mealType = getMealTypeOfDialyMenuItem(itemId, date);

    std::string query = "insert into VoteDailyMenuItem values('" + date + "'," + std::to_string(itemId) +
                        "," + std::to_string(id_) + ",'" + mealType + "')";

    requestMessage.query = query;
    auto response = handler_->handleRequest(requestMessage);
    if (response["status_code"] == StatusCode::CREATED)
    {
        result = true;
    }

    Logger::debug("Employee::voteForDailyMenuItem - exiting");
    return result;
}

std::string Employee::getMealTypeOfDialyMenuItem(const int &itemId, const std::string &date)
{
    Logger::debug("Employee::getMealTypeOfDialyMenuItem");
    std::string mealType;
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select mealType from DailyMenuItem where dailyMenuItemId ='" + date + "' and" +
                           " itemId="+std::to_string(itemId);
    auto response = handler_->handleRequest(requestMessage);
    if (response["status_code"] == StatusCode::OK)
    {
        mealType = response["body"][0]["mealType"];
    }
    Logger::debug("Employee::getMealTypeOfDialyMenuItem");
    return mealType;
}

std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> Employee::viewMenuList()
{
    Logger::debug("Employee::viewMenuList - entering");
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

    Logger::debug("Employee::viewMenuList - exiting");
    return menuItemList_;
}

int Employee::getCountOfItemInMenu()
{
   Logger::debug("Employee::getCountOfItemInMenu - entering");
   auto totalCountOfItem = 0;
   server::RequestMessage requestMessage;
   requestMessage.type = RequestType::GET;
   requestMessage.query = "select count(itemId) from MenuItem";

   auto response = handler_->handleRequest(requestMessage);
   if (response["status_code"] == StatusCode::OK)
   {
        totalCountOfItem = response["body"][0]["count(itemId)"];
   }
   Logger::debug("Employee::getCountOfItemInMenu- exiting");
   return  totalCountOfItem;
}
}}} // namespace foodRecommendationEngine::app::client
