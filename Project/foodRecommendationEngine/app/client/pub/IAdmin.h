#pragma once

#include <iostream>

#include "FoodDataType.h"
#include "Item.h"
#include "UserDataType.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class IAdmin
{
public:
    /**
     * Destrucctor
     */
    virtual ~IAdmin() {}

    /**
     * @brief Set the Admin Id
     * 
     * @param id [in] - Admin id
     */
    virtual void setId(const uint32_t &id) = 0;

    /**
     * @brief Get admin Id
     * 
     * @return uint32_t [out] - return admin Id
     */
    virtual uint32_t getId() = 0;

    /**
     * @brief Add's user
     * 
     * @param UserData [in] - user details
     * @return bool [out] - true if successfully user is added otherwise false
     */
    virtual bool addUser(
      const foodRecommendationEngine::app::client::dataType::UserData &data) = 0;

    /**
     * @brief Delete's user
     * 
     * @param id [in] - id of the user to be deleted
     * @return bool [out] - true if successfully user is deleted otherwise false
     */
    virtual bool deleteUser(const uint32_t &id) = 0;

    /**
     * @brief Add's the food item to menu
     * 
     * @param item [in] - food to be added in menuItem
     * @return bool [out] - true if successfully item is added to menu otherwise false
     */
    virtual bool addMenuItem(
      const foodRecommendationEngine::app::food::foodItem &item) = 0;

    /**
     * @brief Update's the food item in menu
     * 
     * @param item [in] - item to be updated in menuItem
     * @return bool [out] - true if successfully item is updated in menu otherwise false
     */
    virtual bool updateMenuItem(
      const foodRecommendationEngine::app::food::foodItem &item) = 0;

   /**
     * @brief Delete's the food item from menu
     * 
     * @param itemId [in] - itemId to be delete from menuItem
     * @return bool [out] - true if successfully item is deletedfrom menu otherwise false
     */
    virtual bool deleteMenuItem(const uint32_t &itemId) = 0;


    /**
     * @brief Get's the Menu List for view
     * 
     * @return foodRecommendationEngine::app::food::MenuList [out] - Menu List
     */
    virtual std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() = 0;

};
}}} // namespace foodRecommendationEngine::app::client
