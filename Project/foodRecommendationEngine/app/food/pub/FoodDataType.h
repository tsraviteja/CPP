#pragma once

#include <iostream>
#include <map>

namespace foodRecommendationEngine { namespace app { namespace food {


enum MealType
{
    BREAKFAST = 1,
    LUNCH = 2,
    DINNER = 3,
    MIN = BREAKFAST,
    MAX = DINNER
};

const std::map<MealType, std::string> MealTypeLiteral{
    {BREAKFAST, "Breakfast"},
    {LUNCH, "Lunch"},
    {DINNER, "Dinner"}
};

struct foodItem
{
    foodItem() {}
    foodItem(const foodItem &item)
        : id(item.id),
          name(item.name),
          price(item.price),
          isAvailable (item.isAvailable),
          mealType(item.mealType) {}
    int id;
    std::string name;
    double price;
    bool isAvailable;
    MealType mealType;
};

}}} // namespace foodRecommendationEngine::app::food
