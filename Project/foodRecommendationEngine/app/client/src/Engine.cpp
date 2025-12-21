#include  <regex>

#include "Engine.h"

#include "Logger.h"
#include "Utility.h"

using FoodItem = foodRecommendationEngine::app::food::foodItem;
using Item = foodRecommendationEngine::app::food::Item;
using Logger = foodRecommendationEngine::framework::logger::Logger;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;
using Utility = foodRecommendationEngine::framework::core::Utility;

namespace foodRecommendationEngine { namespace app { namespace client {

Engine::Engine(std::shared_ptr<IHandler> handler)
            : handler_(handler)
{
    Logger::debug("Engine::Engine -Constructed");
}

std::vector<engineDataType::RecommendedFoodItem> Engine::getRecommendedFoodItems(const std::string &mealType)
{
    Logger::debug("Engine::getRecommendedFoodItems - entering");
    std::vector<engineDataType::RecommendedFoodItem> recommendedFoodItems;
    auto aveargeRatingOfFoodItem = getHighestAverageRatingByFoodItem(mealType);
    int count = aveargeRatingOfFoodItem.size();

    for (auto index = 0; index < engineDataType::MAXIMUM_RECOMMENDING_FOOD_ITEM && index < count; index++)
    {
        engineDataType::RecommendedFoodItem recommendedFoodItem;
        recommendedFoodItem.item = getItemDetails(aveargeRatingOfFoodItem[index]["itemId"]);
        recommendedFoodItem.averageRating = 0;
        if (aveargeRatingOfFoodItem[index]["Average_rating"].is_string())
        {
            auto rating = Utility::parseToDouble(aveargeRatingOfFoodItem[index]["Average_rating"]);
            if (rating.first)
            {
                recommendedFoodItem.averageRating = rating.second;
            }
        }
        else
        {
            recommendedFoodItem.averageRating = aveargeRatingOfFoodItem[index]["Average_rating"];
        }
        auto commentsOfFoodItem = getCommentsbyFoodItemId(aveargeRatingOfFoodItem[index]["itemId"]);
        recommendedFoodItem.averageSentimentalScore = getAveargeSentimentalScoreForItem(commentsOfFoodItem);
        recommendedFoodItem.averageCompositeScore = (recommendedFoodItem.averageRating + 
                                                     recommendedFoodItem.averageSentimentalScore) / 2;
        recommendedFoodItems.push_back(recommendedFoodItem);
    }
    if (count > 0)
    {
        sortRecommendedFoodItems(recommendedFoodItems);
    }
    Logger::debug("Engine::getRecommendedFoodItems - exiting");
    return recommendedFoodItems;
}

std::shared_ptr<Item> Engine::getItemDetails(const int &itemId)
{
    Logger::debug("Engine::getItemDetails - entering");
    std::shared_ptr<Item> itemDetails;
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select * from MenuItem where itemId=" + std::to_string(itemId);

    auto result = handler_->handleRequest(requestMessage);
    if (result["status_code"] == StatusCode::OK)
    {
        auto menuItem = result["body"][0];
        FoodItem item;
        item.id = menuItem["itemId"];
        item.name = menuItem["itemName"];
        item.price = menuItem["price"];
        item.isAvailable = menuItem["isAvailable"] == 1 ? true : false;
        itemDetails = std::make_shared<Item>(item); 
    }
    Logger::debug("Engine::getItemDetails - exiting");
    return itemDetails;
}

void Engine::sortRecommendedFoodItems(std::vector<engineDataType::RecommendedFoodItem> &recommendedFoodItems)
{
    Logger::debug("Engine::sortRecommendedFoodItems - entering");
    auto itemCount = recommendedFoodItems.size();
    for (size_t index1 = 0; index1 < itemCount; index1++)
    {
        for (size_t index2 = 0; index2 < itemCount - index1 - 1; index2++)
        {
            if (recommendedFoodItems[index2].averageCompositeScore < recommendedFoodItems[index2 + 1].averageCompositeScore)
            {
                auto temp = recommendedFoodItems[index2];
                recommendedFoodItems[index2] = recommendedFoodItems[index2 + 1];
                recommendedFoodItems[index2 + 1] = temp;
            }
        }
    }
    Logger::debug("Engine::sortRecommendedFoodItems - exiting");
}

double Engine::getAveargeSentimentalScoreForItem(const nlohmann::json &itemData)
{
    Logger::debug("Engine::getAveargeSentimentalScoreForItem - entering");
    double averageSentimentalScore = 0;

    if (!itemData.empty() && itemData.is_array())
    {
        double sumOfSentimentalScore = 0;
        Utility uitility;
        auto keyCount = 0;
        for (const auto &item : itemData)
        {
            std::string comment = item["comment"];
            for (const auto &pair : engineDataType::SentementalScore)
            {
                auto key = pair.first;
                auto position = uitility.searchSubString(comment, key);
                if (position >= 0)
                {
                    keyCount++;
                    auto score = engineDataType::SentementalScore.at(key);
                    sumOfSentimentalScore += score;
                }
            }
        }
        averageSentimentalScore = sumOfSentimentalScore / keyCount;
    }
    Logger::debug("Engine::getAveargeSentimentalScoreForItem - exiting");
    return averageSentimentalScore;
}

nlohmann::ordered_json Engine::getHighestAverageRatingByFoodItem(const std::string &mealType)
{
    Logger::debug("Engine::getAverageRatingByFoodItem - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select f.itemId, avg(f.rating) as Average_rating from Feedback f "
                           "inner join MenuItem m on f.itemId = m.itemId where m.isAvailable = true and mealType ='" + mealType + "' " +
                           "group by f.itemId having Average_rating >= " + std::to_string(engineDataType::HIGHEST_AVERAGE_RATING) + 
                           "limit " + std::to_string(engineDataType::MAXIMUM_RECOMMENDING_FOOD_ITEM);

    auto result = handler_->handleRequest(requestMessage);
    nlohmann::ordered_json aveargeRatingOfFoodItem;
    if (result["status_code"] == StatusCode::OK)
    {
        aveargeRatingOfFoodItem = result["body"];
    }
    Logger::debug("Engine::getAverageRatingByFoodItem - exiting");
    return aveargeRatingOfFoodItem;
}

nlohmann::json Engine::getCommentsbyFoodItemId(const int itemId)
{
    Logger::debug("Engine::getCommentsbyFoodItem - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select itemId, comment from Feedback where itemId = "+ std::to_string(itemId);
    Logger::debug("query from engine :" + requestMessage.query);
    auto result = handler_->handleRequest(requestMessage);
    nlohmann::json commentsOfFoodItem;
    if (result["status_code"] == StatusCode::OK)
    {
        commentsOfFoodItem = result["body"];
    }
    Logger::debug("Engine::getCommentsbyFoodItem - exiting");
    return commentsOfFoodItem;
}

}}} // namespace foodRecommendationEngine::app::client
