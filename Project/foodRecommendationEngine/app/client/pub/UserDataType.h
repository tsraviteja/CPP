#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "Item.h"

namespace foodRecommendationEngine { namespace app { namespace client {

namespace dataType{

enum UserType
{
    ADMIN = 1,
    CHEF = 2,
    EMPLOYEE = 3,
    MIN = ADMIN,
    MAX = EMPLOYEE
};

static const std::map<UserType, std::string> UserTypeLiteralForm
{
    {UserType::ADMIN, "Admin"},
    {UserType::CHEF, "Chef"},
    {UserType::EMPLOYEE, "Employee"}
};

struct UserCredentailData
{
    u_int32_t id;
    std::string password;
};

struct UserData
{
    u_int32_t id;
    std::string name;
    std::string password;
    UserType role;
};

enum NotificationType
{
    ITEM_ADDED = 0,
    ITEM_UPDATED = 1,
    ITEM_DELETED = 2
};

struct FeedbackData
{
    int employeeId;
    int itemId;
    std::string comment;
    double rating;
    std::string momRecipe;
};

struct RollOutMenuItemData
{
    int itemId;
    foodRecommendationEngine::app::food::MealType mealType;
};

struct EmployeeResponse
{
    int itemId;
    int totalVotes;
    std::string mealType;
};

struct DialyMenuItemData
{
    std::string dailyMenuItemId;
    int itemId;
    std::string mealType;
};

}}}}  //namespace foodRecommendationEngine::app::client::dataType
