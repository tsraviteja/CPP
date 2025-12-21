#pragma once

#include "Engine.h"
#include "Handler.h"
#include "IChef.h"

namespace foodRecommendationEngine { namespace app { namespace client {
class Chef : public IChef
{
public:
    explicit Chef(std::shared_ptr<IHandler> handler, std::shared_ptr<IEngine> engine);

    /**
     * @{
     * @file IChef methods
     */

    void setId(const int &Id) override;
    int getId() override;
    std::vector<engineDataType::RecommendedFoodItem> 
        getRecommendedItemsFromEngine(const foodRecommendationEngine::app::food::MealType &mealType) override;
    bool rollOutDialyMenuItem(const DataType::RollOutMenuItemData &rollOutMenuItemData) override;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> viewMenuList() override;
    std::vector<DataType::EmployeeResponse> viewEmployeeResponse() override;

    /**
     * @}
     */

    int getCountOfItemInMenu();
    void setMenuItemList(const nlohmann::ordered_json &jsonData);
    void setEmployeeResponse(const nlohmann::ordered_json &jsonData);
    std::string getMealTypeLiteral(const foodRecommendationEngine::app::food::MealType &mealType);
    Server::RequestMessage getDailyMenuRequestMessage(const DataType::RollOutMenuItemData &rollOutMenuItemData);

private:
    int id_;
    std::shared_ptr<IEngine> engine_;
    std::shared_ptr<IHandler> handler_;
    std::vector<std::shared_ptr<
    foodRecommendationEngine::app::food::Item>> menuItemList_;
    std::vector<DataType::EmployeeResponse> employeeResponse_;
};

}}} // namespace foodRecommendationEngine::app::client
