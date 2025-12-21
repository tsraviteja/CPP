#include <gtest/gtest.h>

#include "Notification.h"
#include "IMockHandler.h"


namespace Server = foodRecommendationEngine::app::server;

using Notification = foodRecommendationEngine::app::client::Notification;
using FoodItem = foodRecommendationEngine::app::food::foodItem;
using IMockHandler = foodRecommendationEngine::app::client::IMockHandler;

const uint32_t USER_ID = 1048;
const std::string ITEM_NAME = "masala dosa";

////////////////////////////////////////////
//
// class GivenANotification
//
////////////////////////////////////////////

class GivenANotification : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::string itemName_;
    std::shared_ptr<Notification> notification_;
    std::shared_ptr<IMockHandler> mockHandler_;
    std::string responseOne_;
    std::string responseTwo_;
    std::string responseThree_;
    std::string responseFour_;
    std::string responseFive_;
    std::string responseSix_;
    std::string responseSeven_;
    Server::ResponseMessage responseJsonData_;
};

void GivenANotification::SetUp()
{
    itemName_ = "masala dosa";
    mockHandler_ = std::make_shared<IMockHandler>();
    notification_ = std::make_shared<Notification>(mockHandler_);

    responseOne_ = R"({
                        "status_code": 200,
                        "body": [
                            {
                                "id": 1045
                            },
                            {
                                "id": 1046
                            }
                        ]
                    })";

    responseTwo_ = R"({
                    "status_code": 201,
                    "success_message" : "Creation is Successful!"
                    })";

    responseThree_ = R"({
                    "status_code": 200,
                    "success_message" : "Deleted is Successful!"
                    })";

    responseFour_ = R"({"status_code": 200,
                        "body": [
                            {
                                "message": "Item masala dosa is added into the menu"
                            }
                        ]
                    })";

    responseFive_ = R"({
                        "status_code": 404,
                        "error_message": "Failed to get the data as it is not exists!!!"
                    })";

    responseSix_ = R"({
                    "status_code": 400,
                    "success_message" : "Failed execute the post request!"
                    })";

    responseSeven_ = R"({
                    "status_code": 400,
                    "success_message" : "Failed execute the delete request!"
                    })";
}

void GivenANotification::TearDown() {}

/********************* Tests for notifyEmployee method**************************/
TEST_F(GivenANotification, WhenNotifyEmployeeIsCalledForItemAdded_ThenTrueIsReturnedForNotifyingAllEmployee)
{
    auto notificationType = DataType::NotificationType::ITEM_ADDED;
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseOne_);
    auto responseJsonDataTwo = Server::ResponseMessage::parse(responseTwo_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataOne))
        .WillRepeatedly(::testing::Return(responseJsonDataTwo));

    auto response = notification_->notifyEmployee(notificationType, itemName_);
    EXPECT_TRUE(response);
}

TEST_F(GivenANotification, WhenNotifyEmployeeIsCalledForItemUpdated_ThenTrueIsReturnedForNotifyingAllEmployee)
{
    auto notificationType = DataType::NotificationType::ITEM_UPDATED;
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseOne_);
    auto responseJsonDataTwo = Server::ResponseMessage::parse(responseTwo_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataOne))
        .WillRepeatedly(::testing::Return(responseJsonDataTwo));

    auto response = notification_->notifyEmployee(notificationType, itemName_);
    EXPECT_TRUE(response);
}

TEST_F(GivenANotification, WhenNotifyEmployeeIsCalledForItemDeleted_ThenTrueIsReturnedForNotifyingAllEmployee)
{
    auto notificationType = DataType::NotificationType::ITEM_DELETED;
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseFive_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataOne));

    auto response = notification_->notifyEmployee(notificationType, itemName_);
    EXPECT_FALSE(response);
}

TEST_F(GivenANotification, WhenNotifyEmployeeIsCalledForAnyNotification_ThenFalseIsReturnedIfNoEmployeeIsPresent)
{
    auto notificationType = DataType::NotificationType::ITEM_ADDED;
    auto responseJsonDataOne = Server::ResponseMessage::parse(responseOne_);
    auto responseJsonDataTwo = Server::ResponseMessage::parse(responseTwo_);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonDataOne))
        .WillRepeatedly(::testing::Return(responseJsonDataTwo));

    auto response = notification_->notifyEmployee(notificationType, itemName_);
    EXPECT_TRUE(response);
}

/********************* Tests for getNotification method **************************/
TEST_F(GivenANotification, 
    WhenGetNotificationIsCalledForAnEmployee_ThenNotificationMessageIsReturnedIfNotificationIsPresent)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFour_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->getNotification(USER_ID);
    EXPECT_EQ("Item masala dosa is added into the menu\n", response);
}

TEST_F(GivenANotification, 
    WhenGetNotificationIsCalledForAnEmployee_ThenEmptyNotificationMessageReturnedIfNotificationIsNotPresent)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFive_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->getNotification(USER_ID);
    EXPECT_TRUE(response.empty());
}

/********************* Tests for deleteNotification method **************************/
TEST_F(GivenANotification, 
    WhenDeleteNotificationIsCalledForAnEmployee_ThenNotificationMessageIsDeletedAndReturnsTrue)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseThree_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->deleteNotification(USER_ID);
    EXPECT_TRUE(response);
}

TEST_F(GivenANotification, 
    WhenDeleteNotificationIsCalledForAnEmployee_ThenFalseReturnedIfNoNotifiactionFoundForDelete)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseSeven_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->deleteNotification(USER_ID);
    EXPECT_FALSE(response);
}

/********************* Tests for getAllEmployeeId method **************************/
TEST_F(GivenANotification, 
    WhenGetAllEmployeeIdIsCalledForAnEmployee_ThenAllEmployeeIdsReturned)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->getAllEmployeeId();
    EXPECT_FALSE(response.empty());
}

TEST_F(GivenANotification, 
    WhenGetAllEmployeeIdIsCalledForAnEmployee_ThenNoEmployeeIdsReturnedIfEmployeeDoesNotExists)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFive_);

    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_))
        .WillOnce(::testing::Return(responseJsonData_));

    auto response = notification_->getAllEmployeeId();
    EXPECT_TRUE(response.empty());
}

/********************* Tests for setResponse method **************************/
TEST_F(GivenANotification, 
    WhenSetResponseIsCalledForAnEmployee_ThenResponseIsSetIfJsonDataHasBody)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFour_);
    std::string response;
    notification_->setResponse(response, responseJsonData_);
    EXPECT_FALSE(response.empty());
}

TEST_F(GivenANotification, 
    WhenSetResponseIsCalledForAnEmployee_ThenResponseIsEmptyIfJsonDataNotHasBody)
{
    responseJsonData_ = Server::ResponseMessage::parse(responseFive_);
    std::string response;
    notification_->setResponse(response, responseJsonData_);
    EXPECT_TRUE(response.empty());
}

class GivenANotificationMessageParams : public GivenANotification,
                                        public ::testing::WithParamInterface<std::tuple<DataType::NotificationType,
                                                std::string, std::string>>
{
public:
    GivenANotificationMessageParams() {}
    virtual void SetUp() override;
};

void GivenANotificationMessageParams::SetUp()
{
    GivenANotification::SetUp();
}

TEST_P(GivenANotificationMessageParams, WhenGetNoTificationMessageIsCalled_ThenCorrectMessageIsReturned)
{
    auto notificationMessage = notification_->getNotificationMessage(std::get<0>(GetParam()),
                                                                     std::get<1>(GetParam()));
    EXPECT_EQ(std::get<2>(GetParam()), notificationMessage);
}


INSTANTIATE_TEST_CASE_P(
    GetNotificationMessage, GivenANotificationMessageParams,
    ::testing::Values(
        std::make_tuple(DataType::NotificationType::ITEM_ADDED, ITEM_NAME, "Item masala dosa is added into the menu"),
        std::make_tuple(DataType::NotificationType::ITEM_UPDATED, ITEM_NAME, "Item masala dosa is updated in menu please check"),
        std::make_tuple(DataType::NotificationType::ITEM_DELETED, ITEM_NAME, "Item masala dosa is deleted in menu please check")
));
