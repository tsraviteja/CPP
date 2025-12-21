#pragma once

#include "IMenuItem.h"

namespace foodRecommendationEngine { namespace app { namespace food {

class MenuItem : public IMenuItem
{
public:
    explicit MenuItem();

    /**
     * @{
     */

    bool addItemToMenu(const foodItem &item) override;
    bool deleteItemFromMenu(const uint32_t &itemId) override;
    std::vector<std::shared_ptr<Item>>  getMenuList() override;
    bool updateItemInMenu(const foodItem &item) override;

    /**
     * @}
     */

protected:
    bool isItemAlreadyPresent(const uint32_t &itemId);

private:
    std::vector<std::shared_ptr<Item>> menuList_;
};
}}}
