#include "mockGetUserChoice.h"
#include "mockInstgramJsonFileHandling.h"
#include "mockInstagramUser.h"
#include "Instagram.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

class GivenLoginPage : public ::testing::Test
{
protected:
    nlohmann::ordered_json userData;

    void SetUp() override
    {
        userData = {
            {"Instagramusers", nlohmann::ordered_json::array({{{"username", "ravi"},
                                                               {"password", "1233"},
                                                               {"secretquestion", "What was your childhood name"},
                                                               {"secretanswer", "ravi"}}})}};
    }

    void TearDown() override {}
};

TEST_F(GivenLoginPage, whenNonExistingUserTriesSigin)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, takeInputForPassword(_)).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, getUserName()).WillOnce(Return("Ravi"));
    EXPECT_CALL(instagramUser, getUserPassword()).WillOnce(Return("1234"));
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));

    bool isValidUser = miniInstgram.signin();
    ASSERT_FALSE(isValidUser);
}

TEST_F(GivenLoginPage, whenExistingUserTriesSigin)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, takeInputForPassword(_)).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, getUserName()).WillOnce(Return("ravi"));
    EXPECT_CALL(instagramUser, getUserPassword()).WillOnce(Return("1233"));
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));
    EXPECT_CALL(userChoice, getUserChoice(1, 4)).WillOnce(Return(4));

    bool isValidUser = miniInstgram.signin();
    ASSERT_TRUE(isValidUser);
}

TEST_F(GivenLoginPage, whenExistingUserTriesSignUp)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, getUserName()).WillOnce(Return("ravi"));
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));

    bool isUserSignUpSuccess = miniInstgram.signup();
    ASSERT_FALSE(isUserSignUpSuccess);
}

TEST_F(GivenLoginPage, whenNonUserTriesSignUp)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, takeInputForPassword(_)).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, takeInputForSecretQuestion()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, takeInputForSecretAnswer()).WillOnce(Invoke([]() {}));

    EXPECT_CALL(instagramUser, getUserName()).Times(2).WillRepeatedly(Return("Rahul"));
    EXPECT_CALL(instagramUser, getUserPassword()).Times(1).WillRepeatedly(Return("1233"));
    EXPECT_CALL(instagramUser, getSecretQuestion()).Times(1).WillRepeatedly(Return("What was your childhood name"));
    EXPECT_CALL(instagramUser, getSecretAnswer()).Times(1).WillRepeatedly(Return("ravi"));

    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));
    EXPECT_CALL(instagramFileHandling, writeInstagramJsonFileData(_, _)).WillOnce(Return(true));

    bool isUserSignUpSuccess = miniInstgram.signup();
    ASSERT_TRUE(isUserSignUpSuccess);
}

TEST_F(GivenLoginPage, whenNonExitingUserTriesForForgotPassword)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, getUserName()).WillOnce(Return("Rahul"));
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));

    bool passwordUpdateSuccess = miniInstgram.forgotpassword();
    ASSERT_FALSE(passwordUpdateSuccess);
}

TEST_F(GivenLoginPage, whenExitingUserTriesForForgotPassword)
{
    MockGetUserChoice userChoice;
    MockInstagramJsonFileHandling instagramFileHandling;
    MockInstagramUser instagramUser;
    Instagram miniInstgram(&instagramFileHandling, &userChoice, &instagramUser);

    EXPECT_CALL(instagramUser, takeInputForUserName()).WillOnce(Invoke([]() {}));
    EXPECT_CALL(instagramUser, setSecretQuestion(_)).WillOnce(Return());
    EXPECT_CALL(instagramUser, takeInputForSecretAnswer()).WillOnce(Invoke([]() {}));

    EXPECT_CALL(instagramUser, takeInputForPassword(_)).WillRepeatedly(Invoke([]() {}));

    EXPECT_CALL(instagramUser, takeConfirmpassword()).WillRepeatedly(Invoke([]() {}));

    EXPECT_CALL(instagramUser, getSecretAnswer()).WillOnce(Return("ravi"));
    EXPECT_CALL(instagramUser, getUserName()).Times(2).WillRepeatedly(Return("ravi"));
    EXPECT_CALL(instagramUser, getUserPassword()).Times(1).WillOnce(Return("1235"));
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).WillOnce(Return(userData));
    EXPECT_CALL(instagramFileHandling, writeInstagramJsonFileData(_, _)).WillOnce(Return(true));

    bool passwordUpdateSuccess = miniInstgram.forgotpassword();
    ASSERT_TRUE(passwordUpdateSuccess);
}
