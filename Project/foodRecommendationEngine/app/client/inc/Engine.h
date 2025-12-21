#pragma once

#include "IEngine.h"

#include "Handler.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class Engine : public IEngine
{
public:
    explicit Engine(std::shared_ptr<IHandler> handler);

    /**
     * @{
     * @file IEngine Method
     */

    std::vector<engineDataType::RecommendedFoodItem> getRecommendedFoodItems(const std::string &mealType) override;

    /**
     * @}
     */

    nlohmann::ordered_json getHighestAverageRatingByFoodItem(const std::string &mealType);
    nlohmann::json getCommentsbyFoodItemId(const int itemId);
    double getAveargeSentimentalScoreForItem(const nlohmann::json &itemData);
    std::shared_ptr<foodRecommendationEngine::app::food::Item> getItemDetails(const int &itemId);
    void sortRecommendedFoodItems(std::vector<engineDataType::RecommendedFoodItem> &recommendedFoodItems);

private:
    std::shared_ptr<IHandler> handler_;
    std::vector<engineDataType::RecommendedFoodItem> recommmendedFoodItems_;
};

}}} // namespace foodRecommendationEngine::app::client
