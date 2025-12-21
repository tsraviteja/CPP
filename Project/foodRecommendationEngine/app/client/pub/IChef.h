#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "UserDataType.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

namespace foodRecommendationEngine{ namespace app { namespace client
{
class IChef
{
public:
    virtual void setId(const int &id) = 0;
    virtual int getId() = 0;
    virtual std::vector<engineDataType::RecommendedFoodItem> 
        getRecommendedItemsFromEngine(const foodRecommendationEngine::app::food::MealType &mealType) = 0;
    virtual bool rollOutDialyMenuItem(const DataType::RollOutMenuItemData &rollOutMenuItemData) = 0;
    virtual std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() = 0;
    virtual std::vector<DataType::EmployeeResponse> viewEmployeeResponse() = 0;
};
}}} // namespace foodRecommendationEngine::app::client
