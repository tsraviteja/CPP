#pragma once

#include <iostream>
#include <vector>

#include "EngineDataType.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class IEngine
{
public:
    /**
     * Destructor
     */
    virtual ~IEngine() {}

    /**
     * @brief Get's Recommendation Food Item
     * 
     * @param mealType [in] - mealType for recommendation
     * @return std::vector<dataType::RecommendedFoodItem>
     * [out] - vector of recommended Food Item
     */
    virtual std::vector<engineDataType::RecommendedFoodItem> getRecommendedFoodItems(const std::string &mealType) = 0;

};

}}} // namespace foodRecommendationEngine::app::client
