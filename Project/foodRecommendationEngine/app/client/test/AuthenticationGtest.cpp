#include <gtest/gtest.h>

#include "Authentication.h"
#include "IMockHandler.h"

namespace Server = foodRecommendationEngine::app::server;

using Authentication = foodRecommendationEngine::app::client::Authentication;
using IMockHandler = foodRecommendationEngine::app::client::IMockHandler;
using UserCredentailData = foodRecommendationEngine::app::client::dataType::UserCredentailData;
using UserType = foodRecommendationEngine::app::client::dataType::UserType;

////////////////////////////////////////////
//
// class GivenAnAunthentication
//
////////////////////////////////////////////

class GivenAnAunthentication : public ::testing::Test
{
public:
    virtual void SetUp() override;
    virtual void TearDown() override;

protected:
    std::shared_ptr<Authentication> authentication_;
    std::shared_ptr<IMockHandler> mockHandler_;
    std::string responseOne_;
    std::string responseTwo_;
    Server::ResponseMessage responseJsonData_;
    UserCredentailData userCredentailDataOne_;
    UserCredentailData userCredentailDataTwo_;
    UserCredentailData userCredentailDataThree_;
    UserCredentailData userCredentailDataFour_;
};

void GivenAnAunthentication::SetUp()
{
    mockHandler_ = std::make_shared<IMockHandler>();
    authentication_ = std::make_shared<Authentication>(mockHandler_);

    userCredentailDataOne_.id = 1048;
    userCredentailDataOne_.password = "ravi@123";

    userCredentailDataTwo_.id = 1049;
    userCredentailDataTwo_.password = "raghu@123";

    userCredentailDataThree_.id = 1050;
    userCredentailDataThree_.password = "rahul@123";

    userCredentailDataFour_.id = 1051;
    userCredentailDataFour_.password = "ravi@123";

    responseOne_ = R"({
                        "status_code": 200,
                        "body": [
                            {
                                "id": 111,
                                "password": "",
                                "role": ""
                            }
                        ]
                    })";

    responseTwo_ = R"({
                        "status_code": 404,
                        "error_message": "Failed to get the data as it is not exists!!!"
                    })";
}

void GivenAnAunthentication::TearDown() {}

/*************************** Tests Login method ********************/
TEST_F(GivenAnAunthentication, WhenLoginIsCalledWithValidCrendentialandAndAdminRole_ThenTrueReturns)
{
    UserType userType = UserType::ADMIN;
    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);
    responseJsonData_["body"][0]["id"] = userCredentailDataOne_.id;
    responseJsonData_["body"][0]["password"] = userCredentailDataOne_.password;
    responseJsonData_["body"][0]["role"] = foodRecommendationEngine::app::client::dataType::UserTypeLiteralForm.at(userType);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto result = authentication_->login(userCredentailDataOne_.id,
                                         userCredentailDataOne_.password,
                                         userType);
    EXPECT_TRUE(result);
}

TEST_F(GivenAnAunthentication, WhenLoginIsCalledWithValidCrendentialandAndChefRole_ThenTrueReturns)
{
    UserType userType = UserType::CHEF;
    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);
    responseJsonData_["body"][0]["id"] = userCredentailDataTwo_.id;
    responseJsonData_["body"][0]["password"] = userCredentailDataTwo_.password;
    responseJsonData_["body"][0]["role"] = foodRecommendationEngine::app::client::dataType::UserTypeLiteralForm.at(userType);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto result = authentication_->login(userCredentailDataOne_.id,
                                         userCredentailDataOne_.password,
                                         userType);
    EXPECT_TRUE(result);
}

TEST_F(GivenAnAunthentication, WhenLoginIsCalledWithValidCrendentialandAndEmployeeRole_ThenTrueReturns)
{
    UserType userType = UserType::EMPLOYEE;
    responseJsonData_ = Server::ResponseMessage::parse(responseOne_);
    responseJsonData_["body"][0]["id"] = userCredentailDataThree_.id;
    responseJsonData_["body"][0]["password"] = userCredentailDataThree_.password;
    responseJsonData_["body"][0]["role"] = foodRecommendationEngine::app::client::dataType::UserTypeLiteralForm.at(userType);
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto result = authentication_->login(userCredentailDataOne_.id,
                                         userCredentailDataOne_.password,
                                         userType);
    EXPECT_TRUE(result);
}

TEST_F(GivenAnAunthentication, WhenLoginIsCalledWithInValidCrendentialandAndEmployeeRole_ThenFalseReturns)
{
    UserType userType = UserType::EMPLOYEE;
    responseJsonData_ = Server::ResponseMessage::parse(responseTwo_);
    
    EXPECT_CALL(*mockHandler_, handleRequest(::testing::_)).WillOnce(::testing::Return(responseJsonData_));
    auto result = authentication_->login(userCredentailDataOne_.id,
                                         userCredentailDataOne_.password,
                                         userType);
    EXPECT_FALSE(result);
}
