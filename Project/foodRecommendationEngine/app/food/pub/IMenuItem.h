#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "FoodDataType.h"
#include "Item.h"

namespace foodRecommendationEngine { namespace app { namespace food {

class IMenuItem
{
public:
    virtual ~IMenuItem() {}

    virtual bool addItemToMenu(const foodItem &item) = 0;
    virtual bool deleteItemFromMenu(const uint32_t &itemId) = 0;
    virtual std::vector<std::shared_ptr<Item>> getMenuList() = 0;
    virtual bool updateItemInMenu(const foodItem &item) = 0;
};

}}} // namespace foodRecommendationEngine::app::food
