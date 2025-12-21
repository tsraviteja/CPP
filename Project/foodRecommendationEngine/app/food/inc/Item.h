#pragma once


#include "FoodDataType.h"

namespace foodRecommendationEngine { namespace app { namespace food {

class Item
{
public:
    explicit Item();
    explicit Item(const foodItem &item);

    /**
     * @name Item.h methods
     * @{
     */

    u_int32_t getItemId();
    std::string getItemName();
    double getItemPrice();
    bool getItemIsAvailable();
    MealType getItemMealType();
    void setItemId(const u_int32_t &itemId);
    void setItemName(const std::string &name);
    void setItemPrice(const double &price);
    void setItemIsAvailable(const bool &isAvailable);
    void setItemMealType(const MealType &mealType);

    /**
     * @}
     */

private:
    foodItem item_;
};

}}} //namespace foodRecommendation::app::food
