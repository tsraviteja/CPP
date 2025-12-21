#include "MenuItem.h"

#include <algorithm>

#include "Logger.h"

using Logger = foodRecommendationEngine::framework::logger::Logger;

namespace foodRecommendationEngine { namespace app { namespace food {


MenuItem::MenuItem()
{
    Logger::debug("MenuItem constructed");
}

bool MenuItem::addItemToMenu(const foodItem &item)
{
    Logger::debug("MenuItem::addItemToMenu - entering");
    auto result = false;
    if (isItemAlreadyPresent(item.id))
    {
        auto itemData = std::make_shared<Item>(item);
        menuList_.push_back(itemData);
        result = true;
    }
    Logger::debug("MenuItem::addItemToMenu - exiting");
    return result;
}

bool MenuItem::deleteItemFromMenu(const uint32_t &itemId)
{
    Logger::debug("MenuItem::deleteItemFromMenu - entering");
    auto result = false;
    menuList_.erase(std::remove_if(menuList_.begin(), menuList_.end(),
                            [&](const std::shared_ptr<Item> item)
                            {
                                if (item->getItemId() == itemId)
                                {
                                    result = true;
                                    return result;
                                }
                                return false;
                            }));
    Logger::debug("MenuItem::deleteItemFromMenu - exiting");
    return result;
}

std::vector<std::shared_ptr<Item>> MenuItem::getMenuList()
{
    Logger::debug("MenuItem::getMenuList - entering");
    Logger::debug("MenuItem::getMenuList - exiting");
    return menuList_;
}

bool MenuItem::updateItemInMenu(const foodItem &item)
{
    Logger::debug("MenuItem::updateItemInMenu - entering");
    auto result = false;
    for (auto &foodItem : menuList_)
    {
        if (foodItem->getItemId() == item.id)
        {
            foodItem->setItemIsAvailable(item.isAvailable);
            foodItem->setItemName(item.name);
            foodItem->setItemMealType(item.mealType);
            foodItem->setItemPrice(item.price);
            result = true;
        }
    }
    Logger::debug("MenuItem::updateItemInMenu - exiting");
    return result;
}

bool MenuItem::isItemAlreadyPresent(const uint32_t &itemId)
{
    Logger::debug("MenuItem::isItemAlreadyPresent - entering");
    auto isItemPresent = true;
    for (auto &item : menuList_)
    {
        if (item->getItemId() == itemId)
        {
            isItemPresent = false;
        }
    }
    Logger::debug("MenuItem::isItemAlreadyPresent - exiting");
    return isItemPresent;
}

}}} //namespace foodRecommendation::app::food
