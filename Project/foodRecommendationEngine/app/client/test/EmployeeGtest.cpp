#include <gtest/gtest.h>

#include "Employee.h"
#include "Engine.h"
#include "IMockHandler.h"

namespace Server = foodRecommendationEngine::app::server;

using Employee = foodRecommendationEngine::app::client::Employee;
using IMockHandler = foodRecommendationEngine::app::client::IMockHandler;
using MealType = foodRecommendationEngine::app::food::MealType;

const uint32_t USER_ID = 1048;

const uint32_t ITEM_ID = 101;
const MealType mealType = MealType::BREAKFAST;


////////////////////////////////////////////
//
// class GivenAnEmployee
//
////////////////////////////////////////////

class GivenAnEmployee : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::shared_ptr<Employee> employee_;
    std::shared_ptr<IMockHandler> mockHandler_;
    std::string responseOne_;
    std::string responseTwo_;
    std::string responseThree_;
    std::string responseFour_;
    Server::ResponseMessage responseJsonData_;
};

void GivenAnEmployee::SetUp()
{
    mockHandler_ = std::make_shared<IMockHandler>();
    employee_ = std::make_shared<Employee>(mockHandler_);

    responseOne_ = R"({
                    "status_code": 200,
                    "body": [
                        {
                            "itemId": 101,
                            "itemName": "idly",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 102,
                            "itemName": "masala dosa",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 103,
                            "itemName": "set dosa",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 104,
                            "itemName": "tomoto rice",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 105,
                            "itemName": "rice samber",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        }
                    ]
                })";

    responseTwo_ = R"({
                    "status_code": 200,
                    "body": [
                        {
                            "itemId": 106,
                            "itemName": "vada",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 107,
                            "itemName": "puri",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 108,
                            "itemName": "kichidi",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 109,
                            "itemName": "mango lasi",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        },
                        {
                            "itemId": 110,
                            "itemName": "butter milk",
                            "price": 45,
                            "isAvailable": 1,
                            "mealType": "BreakFast"
                        }
                    ]
                })";

    responseFour_ = R"({
                        "status_code": 404,
                        "error_message": "Failed to get the data as it is not exists!!!"
                    })";

    responseThree_ = R"json({
                        "status_code": 200,
                        "body": [
                            {
                                "count(itemId)": 10
                            }
                        ]
                    })json";
}

void GivenAnEmployee::TearDown() {}

/************** Tests viewMenuList method *************/
TEST_F(GivenAnEmployee, WhenViewMenuListIsCalled_ThenEmptyMenuListIsReturnedForZeroCountOfItem)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFour_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto menuList = employee_->viewMenuList();

    EXPECT_EQ(0, menuList.size());
}

TEST_F(GivenAnEmployee, WhenViewMenuListIsCalled_ThenMenuListIsReturnedForNonZeroCountOfItem)
{
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseOne_);
    auto responseJsonDataTwo = Server::ResponseMessage::parse(responseTwo_);
    auto responseJsonDataThree = Server::ResponseMessage::parse(responseThree_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataThree))
        .WillOnce(::testing::Return(responseJsonDataOne))
        .WillOnce(::testing::Return(responseJsonDataTwo));

    auto menuList = employee_->viewMenuList();

    EXPECT_EQ(10, menuList.size());
}
