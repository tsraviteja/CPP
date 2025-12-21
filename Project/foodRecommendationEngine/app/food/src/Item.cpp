#include "Item.h"

#include "Logger.h"

using Logger = foodRecommendationEngine::framework::logger::Logger;

namespace foodRecommendationEngine { namespace app { namespace food {

//****************************************************/
//****************** Constructor *********************/
//****************************************************/

Item::Item()
{
    Logger::debug("Item constructed");
}

Item::Item(const foodItem &item)
    :  item_(item)
{
    Logger::debug("Item constructed");
}


//****************************************************/
//************** IItem public methods ****************/
//****************************************************/

u_int32_t Item::getItemId()
{
    Logger::debug("Item::getItemId - entring");
    Logger::debug("Item::getItemId - exiting");
    return item_.id;
}

std::string Item::getItemName()
{
    Logger::debug("Item::getItemName - entring");
    Logger::debug("Item::getItemName - exiting");
    return item_.name;
}

double Item::getItemPrice()
{
    Logger::debug("Item::getItemPrice - entring");
    Logger::debug("Item::getItemPrice - exiting");
    return item_.price;
}

bool Item::getItemIsAvailable()
{
    return item_.isAvailable;
}

MealType Item::getItemMealType()
{
    return item_.mealType;
}

void Item::setItemMealType(const MealType &mealType)
{
    item_.mealType = mealType;
}

void Item::setItemIsAvailable(const bool &isAvailable)
{
    item_.isAvailable = isAvailable;
}

void Item::setItemId(const u_int32_t &id)
{
    Logger::debug("Item::setItemId - entring");
    item_.id = id;
    Logger::debug("Item::setItemId - exiting");
}

void Item::setItemName(const std::string &name)
{
    Logger::debug("Item::setItemName - entring");
    item_.name = name;
    Logger::debug("Item::setItemName - exiting");
}

void Item::setItemPrice(const double &price)
{
    Logger::debug("Item::setItemPrice - entring");
    item_.price = price;
    Logger::debug("Item::setItemPrice - exiting");
}

}}} //namespace foodRecommendation::app::food
