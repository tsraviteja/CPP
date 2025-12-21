#include <gtest/gtest.h>

#include "Admin.h"
#include "IMockHandler.h"

namespace Server = foodRecommendationEngine::app::server;

using Admin = foodRecommendationEngine::app::client::Admin;
using FoodItem = foodRecommendationEngine::app::food::foodItem;
using IMockHandler = foodRecommendationEngine::app::client::IMockHandler;
using MealType = foodRecommendationEngine::app::food::MealType;
using UserData = foodRecommendationEngine::app::client::dataType::UserData;
using UserType = foodRecommendationEngine::app::client::dataType::UserType;

const uint32_t USER_ID = 1048;
const std::string USER_NAME = "rahul";
const std::string PASSWORD = "rahul@123";
const UserType USER_TYPE = UserType::EMPLOYEE;

const uint32_t ITEM_ID = 101;
const std::string ITEM_NAME = "Rava idly";
const double PRICE = 45.0;
const bool AVAILABILITY = true;
const MealType mealType = MealType::BREAKFAST;


////////////////////////////////////////////
//
// class GivenAnAdmin
//
////////////////////////////////////////////

class GivenAnAdmin : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::shared_ptr<Admin> admin_;
    FoodItem item_;
    std::shared_ptr<IMockHandler> mockHandler_;
    std::string responseOne_;
    std::string responseTwo_;
    std::string responseThree_;
    std::string responseFour_;
    std::string responseFive_;
    std::string responseSix_;
    std::string responseSeven_;
    std::string responseEight_;
    std::string responseNine_;
    Server::ResponseMessage responseJsonData_;
    UserData userData_;
};

void GivenAnAdmin::SetUp()
{
    mockHandler_ = std::make_shared<IMockHandler>();
    admin_ = std::make_shared<Admin>(mockHandler_);
    userData_.id = USER_ID;
    userData_.name = USER_NAME;
    userData_.password = PASSWORD;
    userData_.role = USER_TYPE;

    item_.id = ITEM_ID;
    item_.name = ITEM_NAME;
    item_.price = PRICE;
    item_.isAvailable = AVAILABILITY;
    item_.mealType = mealType;

    responseOne_ = R"({
                    "status_code": 201,
                    "success_message" : "Creation is Successful!"
                    })";

    responseTwo_ = R"({
                    "status_code": 400,
                    "success_message" : "Failed execute the post request!"
                    })";

    responseThree_ = R"({
                    "status_code": 200,
                    "success_message" : "Deleted is Successful!"
                    })";

    responseFour_ = R"({
                    "status_code": 400,
                    "success_message" : "Failed execute the delete request!"
                    })";

    responseFive_ = R"({
                    "status_code": 200,
                    "success_message" : "Update is Successful!"
                    })";

    responseSix_ = R"({
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

    responseSeven_ = R"({
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

    responseEight_ = R"json({
                        "status_code": 200,
                        "body": [
                            {
                                "count(itemId)": 10
                            }
                        ]
                    })json";

    responseNine_ = R"({
                        "status_code": 404,
                        "error_message": "Failed to get the data as it is not exists!!!"
                    })";

    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);
}

void GivenAnAdmin::TearDown() {}

/************** Test for setId and getId methods *************/
TEST_F(GivenAnAdmin, WhenGetIdIsCalled_ThenReturnsAdmminId)
{
    admin_->setId(USER_ID);
    auto adminId = admin_->getId();

    EXPECT_EQ(USER_ID, adminId);
}

/************** Tests addUser method *************/
TEST_F(GivenAnAdmin, WhenAddUserIsCalledWithValidUserData_ThenReturnsTrue)
{
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->addUser(userData_);

    EXPECT_TRUE(response);
}

TEST_F(GivenAnAdmin, WhenAddUserIsCalledWithValidUserDataAlreadyExists_ThenReturnsFalse)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseTwo_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->addUser(userData_);

    EXPECT_FALSE(response);
}

/************** Tests deleteUser method *************/
TEST_F(GivenAnAdmin, WhenDeleteUserIsCalledWithExistsUseId_ThenReturnsTrue)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseThree_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->deleteUser(USER_ID);

    EXPECT_TRUE(response);
}

TEST_F(GivenAnAdmin, WhenDeleteUserIsCalledWithNonExistsUseId_ThenReturnsFalse)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFour_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->deleteUser(USER_ID);

    EXPECT_FALSE(response);
}

/************** Tests addMenuItem method *************/
TEST_F(GivenAnAdmin, WhenAddMenuItemIsCalledWithValidFoodItemData_ThenReturnsTrue)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->addMenuItem(item_);

    EXPECT_TRUE(response);
}

TEST_F(GivenAnAdmin, WhenAddMenuItemIsCalledWithValidFoodItemDataWhichIsAlreadyExists_ThenReturnsFalse)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseTwo_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->addMenuItem(item_);

    EXPECT_FALSE(response);
}

/************** Tests updateMenuItem method *************/
TEST_F(GivenAnAdmin, WhenUpdateMenuItemIsCalledWithValidFoodItemData_ThenReturnsTrue)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFive_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    item_.price = 55.0;
    auto response = admin_->updateMenuItem(item_);

    EXPECT_TRUE(response);
}

/************** Tests deleteMenuItem method *************/
TEST_F(GivenAnAdmin, WhenDeleteMenuItemIsCalledWithFoodItemId_ThenReturnsTrue)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseThree_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->deleteMenuItem(item_.id);

    EXPECT_TRUE(response);
}

TEST_F(GivenAnAdmin, WhenDeleteMenuItemIsCalledWithNonExistsingFoodItemId_ThenReturnsFalse)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFour_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto response = admin_->deleteMenuItem(item_.id);

    EXPECT_FALSE(response);
}

/************** Tests getCountOfItemInMenu method *************/
TEST_F(GivenAnAdmin, WhenGetCountOfItemInMenuIsCalled_ThenCorrectTotalCountOfItemIsReturned)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseEight_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto countOfItem = admin_->getCountOfItemInMenu();

    EXPECT_EQ(10, countOfItem);
}

TEST_F(GivenAnAdmin, WhenGetCountOfItemInMenuIsCalled_ThenCountOfZeroItemIsReturnedForEmptyMenuList)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseNine_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto countOfItem = admin_->getCountOfItemInMenu();

    EXPECT_EQ(0, countOfItem);
}

/************** Tests viewMenuList method *************/
TEST_F(GivenAnAdmin, WhenViewMenuListIsCalled_ThenEmptyMenuListIsReturnedForZeroCountOfItem)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseNine_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto menuList = admin_->viewMenuList();

    EXPECT_EQ(0, menuList.size());
}

TEST_F(GivenAnAdmin, WhenViewMenuListIsCalled_ThenMenuListIsReturnedForNonZeroCountOfItem)
{
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseSix_);
    auto responseJsonDataTwo = Server::ResponseMessage::parse(responseSeven_);
    auto responseJsonDataThree = Server::ResponseMessage::parse(responseEight_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataThree))
        .WillOnce(::testing::Return(responseJsonDataOne))
        .WillOnce(::testing::Return(responseJsonDataTwo));

    auto menuList = admin_->viewMenuList();

    EXPECT_EQ(10, menuList.size());
}
