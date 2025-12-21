#pragma once

#include "IEmployee.h"

#include <memory>

#include "Handler.h"

namespace foodRecommendationEngine { namespace app { namespace client
{
class Employee : public IEmployee
{
public:
    explicit Employee(std::shared_ptr<IHandler> handler);

    /**
     * @{
     * @file IEmployee methods
     */

    void setId(const int &id) override;
    int getId() override;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() override;
    std::vector<DataType::DialyMenuItemData> viewDailyMenuItem(const foodRecommendationEngine::app::food::MealType &mealType) override;
    bool provideFeedback(const DataType::FeedbackData &feedbackData) override;
    bool voteForDailyMenuItem(const int &itemId) override;

    /**
     * @}
     */

    int getCountOfItemInMenu();
    void setMenuItemList(const nlohmann::ordered_json &jsonData);
    void setDialymenuItemList(const nlohmann::ordered_json &jsonData);
    std::string getMealTypeOfDialyMenuItem(const int &itemId, const std::string &date);

private:
    int id_;
    std::shared_ptr<IHandler> handler_;
    std::vector<DataType::DialyMenuItemData> dailyMenuItemList_;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> menuItemList_;
};
}}} // namespace foodRecommendationEngine::app::client
