#pragma once

namespace foodRecommendationEngine { namespace app { namespace client {

namespace choice
{
enum UserChoice
{
    ADMIN = 1,
    CHEF = 2,
    EMPOLYEE = 3,
    USER_EXIT = 4,
    USER_MIN = ADMIN,
    USER_MAX = USER_EXIT
};

enum AdminChoice
{
    ADD_USER = 1,
    DELETE_UESR = 2,
    ADD_MENU_ITEM = 3,
    UPDATE_MENU_ITEM = 4,
    DELETE_MENU_ITEM = 5,
    DISPLAY_MENU_ITEM = 6,
    ADMIN_EXIST = 7,
    ADMIN_MIN = ADD_USER,
    ADMIN_MAX = ADMIN_EXIST
};

enum ChefChoice
{
    VIEW_MENU_ITEM = 1,
    RECOMMENDED_ITEMS_FROM_ENGINE = 2,
    ROLL_OUT_DAILY_MENU_ITEM = 3,
    VIEW_EMPLOYEE_RESPONSE = 4,
    CHEF_EXIT = 5,
    CHEF_MIN = VIEW_MENU_ITEM,
    CHEF_MAX = CHEF_EXIT
};

enum EmployeeChoice
{
    VIEW_MENU = 1,
    VIEW_DAILY_MENU = 2,
    PROVIDE_FEED_BACK = 3,
    VOTE_FOR_DAILY_MENU = 4,
    EMPOLYEE_EXIST = 5,
    EMPLOYEE_MIN = VIEW_MENU,
    EMPLOYEE_MAX = EMPOLYEE_EXIST
};

enum Option
{
    YES = 1,
    NO = 2
};

}}}} // namespace foodRecommendationEngine::app::client::choice
