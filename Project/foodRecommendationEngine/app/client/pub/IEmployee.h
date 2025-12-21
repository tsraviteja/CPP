#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "UserDataType.h"
#include "Item.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

namespace foodRecommendationEngine { namespace app { namespace client {

class IEmployee
{
public:
    virtual void setId(const int &id) = 0;
    virtual int getId() = 0;
    virtual std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() = 0;
    virtual std::vector<DataType::DialyMenuItemData> viewDailyMenuItem(const foodRecommendationEngine::app::food::MealType &mealType) = 0;
    virtual bool provideFeedback(const DataType::FeedbackData &feedbackData) = 0;
    virtual bool voteForDailyMenuItem(const int &itemId) = 0;
};
}}} // namespace foodRecommendationEngine::app::client
