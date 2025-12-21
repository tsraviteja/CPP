#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "Item.h"

namespace foodRecommendationEngine { namespace app { namespace client {

namespace engineDataType {

struct RecommendedFoodItem
{
    RecommendedFoodItem(){}
    RecommendedFoodItem(const RecommendedFoodItem &other)
        : item(other.item),
          averageRating(other.averageRating),
          averageSentimentalScore(other.averageSentimentalScore),
          averageCompositeScore(other.averageCompositeScore) 
    {}
    
    std::shared_ptr<foodRecommendationEngine::app::food::Item> item;
    double averageRating = 0;
    double averageSentimentalScore = 0;
    double averageCompositeScore = 0;  // average of rating and sentimentalScore
};

static const std::map<std::string, double> SentementalScore{
    {"good", 3},
    {"very good", 3.5},
    {"good taste", 3.5},
    {"tasty", 4},
    {"delicious", 4},
    {"not good", -3},
    {"not tasty", -3.5},
    {"bad taste", -4},
};

const int MAXIMUM_RECOMMENDING_FOOD_ITEM = 10;
const double HIGHEST_AVERAGE_RATING = 3.8;

}}}} //namespace foodRecommendationEngine::app::client::engineDataType
